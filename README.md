# About
QDiscord is an interface for the [Discord API](https://discordapp.com/developers/), written in C++ using the [Qt](https://www.qt.io/) toolkit for cross-platform compability.

# Prerequisites
1. Qt 5.x ([link](https://www.qt.io/download-qt-installer))
2. OpenSSL 1.0.2x ([link](https://www.openssl.org/source/))

# Building
1. Run the bash script `init.sh` and enter the location of any dependant libraries. This script will also fetch the [premake](https://premake.github.io/) executable we'll later use to generate our project files.<br>
![](https://i.imgur.com/Jlg2qzD.png)<br>
(If you're requested directories for system versions you don't wish to build for, you may leave the responses blank)

2. Change to the "src" directory and run the bash script `generate.sh`. This gives us the project files we can finally use to compile the library.<br>
![](https://i.imgur.com/0odjNNJ.png)<br>
(If you're on Windows and wish to use Visual Studio 2015 instead of 2017 (default), pass the argument "vs2015" to the generate script)

3. Build the project using the generated project files.
