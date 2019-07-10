#include <user_config.h>
#include <SmingCore.h>

#ifndef WIFI_SSID
#define WIFI_SSID "" // Put you SSID and Password here
#define WIFI_PWD ""
#endif

#define SENSOR_1 5  // D1 - GPIO_5
#define SENSOR_2 4  // D2 - GPIO_4
#define SENSOR_3 14 // D5 - GPIO_14
#define SENSOR_4 12 // D6 - GPIO_12

HttpServer server;

void onIndex(HttpRequest &request, HttpResponse &response)
{
	response.setContentType(MIME_HTML);
	response.sendString("Server is running.");
}

float getWaterLevel()
{
	bool sensor1 = !digitalRead(SENSOR_1);
	bool sensor2 = !digitalRead(SENSOR_2);
	bool sensor3 = !digitalRead(SENSOR_3);
	bool sensor4 = !digitalRead(SENSOR_4);
	if (sensor1)
	{
		if (sensor2)
		{
			if (sensor3)
			{
				if (sensor4)
				{
					return 100.00;
				}
				return 75.00;
			}
			return 50.00;
		}
		return 25.00;
	}
}

void send_json_waterLevel(HttpRequest &request, HttpResponse &response)
{
	JsonObjectStream *stream = new JsonObjectStream();
	JsonObject &json = stream->getRoot();

	json["water_level"] = getWaterLevel();

	response.sendDataStream(stream, MIME_JSON);
}

void startWebServer()
{
	server.listen(80);
	server.paths.set("/", onIndex);
	server.paths.set("/api/water_level", send_json_waterLevel);

	Serial.println("\r\n=== WEB SERVER STARTED ===");
	Serial.println(WifiStation.getIP());
	Serial.println("==============================\r\n");
}

void gotIP(IPAddress ip, IPAddress netmask, IPAddress gateway)
{
		startWebServer();
}
void readToSerial()
{
	Serial.print("\r\nSensor 1: ");
	Serial.println(!digitalRead(SENSOR_1));

	Serial.print("\r\nSensor 2: ");
	Serial.println(!digitalRead(SENSOR_2));

	Serial.print("\r\nSensor 3: ");
	Serial.println(!digitalRead(SENSOR_3));
	
	Serial.print("\r\nSensor 4: ");
	Serial.println(!digitalRead(SENSOR_4));

}
Timer procTimer;
void init()
{
	pinMode(SENSOR_1, INPUT);
	pullup(SENSOR_1); //Default in 3,3V

	pinMode(SENSOR_2, INPUT);
	pullup(SENSOR_2); //Default in 3,3V

	pinMode(SENSOR_3, INPUT);
	pullup(SENSOR_3); //Default in 3,3V

	pinMode(SENSOR_4, INPUT);
	pullup(SENSOR_4); //Default in 3,3V

	procTimer.initializeMs(1000, readToSerial).start();

	Serial.begin(SERIAL_BAUD_RATE); // 115200 by default
	Serial.systemDebugOutput(true); // Enable debug output to serial

	WifiStation.enable(true);
	WifiStation.config(WIFI_SSID, WIFI_PWD);
	WifiAccessPoint.enable(false);

	// Run our method when station was connected to AP
	WifiEvents.onStationGotIP(gotIP);

	//Change CPU freq. to 160MHZ
	System.setCpuFrequency(eCF_160MHz);
	Serial.print("New CPU frequency is:");
	Serial.println((int)System.getCpuFrequency());
}
