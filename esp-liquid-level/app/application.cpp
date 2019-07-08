#include <user_config.h>
#include <SmingCore.h>

#ifndef WIFI_SSID
#define WIFI_SSID "" // Put you SSID and Password here
#define WIFI_PWD ""
#endif

HttpServer server;

void onIndex(HttpRequest &request, HttpResponse &response)
{
	response.setContentType(MIME_HTML);
	response.sendString("Server is running.");
}

void startWebServer()
{
	server.listen(80);
	server.paths.set("/", onIndex);

	Serial.println("\r\n=== WEB SERVER STARTED ===");
	Serial.println(WifiStation.getIP());
	Serial.println("==============================\r\n");
}

void gotIP(IPAddress ip, IPAddress netmask, IPAddress gateway)
{
		startWebServer();
}

void init()
{
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
