# How to use

This repository has all the bits to make start of any [Sming](https://github.com/SmingHub/Sming) based project on Linux. To use it with [Visual Studio Code](https://code.visualstudio.com/) make sure you have both `ESP_HOME` and `SMING_HOME` environment variables set properly or VSCode C/C++ extension will not find included modules.

* VS Code [C/C++ extension](https://github.com/Microsoft/vscode-cpptools) integration
* Intellisense with help of GNU Global tools provided by [C++ Intellisense](https://github.com/austin-----/code-gnu-global) and [RunOnSave](https://github.com/emeraldwalk/vscode-runonsave) extensions
* Build, clean and flash tasks already defined in VS Code workspace settings

## How to compile the code

Again, make sure you have both `ESP_HOME` amd `SMING_HOME` environment variables set properly.
- Use this:
```
make
```

## How to upload the compiled code

- To upload your code, use this:
```
make flash
```

- **[Ubuntu]** If you don't have root privileges to access the USB port, use this:
```
sudo -E make flash
```