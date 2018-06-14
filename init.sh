#!/bin/bash

PREMAKE_VERSION="5.0.0-alpha12"
uname_s=$(uname -s)
uname_m=$(uname -m)
os=""
machine_type=""

# Linux system
if [ "$uname_s" == "Linux" ]; then
	os="linux"

# Max OS X system
elif [ "$uname_s" == "Darwin" ]; then
	os="osx"

# Assume Windows
else
	os="windows"
fi


# x64 machine
if [ "$uname_m" == "x86_64" ]; then
	machine_type="x64"

# x86 machine
else
	machine_type="x86"
fi


# Generate directories
$(mkdir -p "tmp" "bin" "bin/x86" "bin/x64")


# Qt (x86) directory
qtdir_x86=""
if [ true ]; then
	echo -n "Enter your local Qt (x86) directory and press ENTER: "
	read -e qtdir_x86
	echo -n $qtdir_x86 >"tmp/.qtdir_x86"
fi

# Qt (x64) directory
qtdir_x64=""
if [ "$machine_type" == "x64" ]; then
	echo -n "Enter your local Qt (x64) directory and press ENTER: "
	read -e qtdir_x64
	echo -n $qtdir_x64 >"tmp/.qtdir_x64"
fi

# OpenSSL (x86) directory
ssldir_x86=""
if [ true ]; then
	echo -n "Enter your local OpenSSL (x86) directory and press ENTER: "
	read -e ssldir_x86
	echo -n $ssldir_x86 >"tmp/.ssldir_x86"
fi

# OpenSSL (x64) directory
ssldir_x64=""
if [ "$machine_type" == "x64" ]; then
	echo -n "Enter your local OpenSSL (x64) directory and press ENTER: "
	read -e ssldir_x64
	echo -n $ssldir_x64 >"tmp/.ssldir_x64"
fi


# Copy Qt (x86) DLLs
if [ -n "$qtdir_x86" ]; then
	if [ "$os" == "windows" ]; then
		$(cp "$qtdir_x86/plugins/platforms/qwindows.dll" "bin/x86/")
		$(cp "$qtdir_x86/bin/Qt5Core.dll" "bin/x86/")
		$(cp "$qtdir_x86/bin/Qt5Cored.dll" "bin/x86/")
		$(cp "$qtdir_x86/bin/Qt5Gui.dll" "bin/x86/")
		$(cp "$qtdir_x86/bin/Qt5Guid.dll" "bin/x86/")
		$(cp "$qtdir_x86/bin/Qt5Network.dll" "bin/x86/")
		$(cp "$qtdir_x86/bin/Qt5Networkd.dll" "bin/x86/")
		$(cp "$qtdir_x86/bin/Qt5WebSockets.dll" "bin/x86/")
		$(cp "$qtdir_x86/bin/Qt5WebSocketsd.dll" "bin/x86/")
		$(cp "$qtdir_x86/bin/Qt5Widgets.dll" "bin/x86/")
		$(cp "$qtdir_x86/bin/Qt5Widgetsd.dll" "bin/x86/")
	fi
fi

# Copy Qt (x64) DLLs
if [ -n "$qtdir_x64" ]; then
	if [ "$os" == "windows" ]; then
		$(cp "$qtdir_x64/plugins/platforms/qwindows.dll" "bin/x64/")
		$(cp "$qtdir_x64/bin/Qt5Core.dll" "bin/x64/")
		$(cp "$qtdir_x64/bin/Qt5Cored.dll" "bin/x64/")
		$(cp "$qtdir_x64/bin/Qt5Gui.dll" "bin/x64/")
		$(cp "$qtdir_x64/bin/Qt5Guid.dll" "bin/x64/")
		$(cp "$qtdir_x64/bin/Qt5Network.dll" "bin/x64/")
		$(cp "$qtdir_x64/bin/Qt5Networkd.dll" "bin/x64/")
		$(cp "$qtdir_x64/bin/Qt5WebSockets.dll" "bin/x64/")
		$(cp "$qtdir_x64/bin/Qt5WebSocketsd.dll" "bin/x64/")
		$(cp "$qtdir_x64/bin/Qt5Widgets.dll" "bin/x64/")
		$(cp "$qtdir_x64/bin/Qt5Widgetsd.dll" "bin/x64/")
	fi
fi

# Copy OpenSSL (x86) DLLs
if [ -n "$ssldir_x86" ]; then
	if [ "$os" == "windows" ]; then
		$(cp "$ssldir_x86/bin/libeay32.dll" "bin/x86/")
		$(cp "$ssldir_x86/bin/ssleay32.dll" "bin/x86/")
	fi
fi

# Copy OpenSSL (x64) DLLs
if [ -n "$ssldir_x64" ]; then
	if [ "$os" == "windows" ]; then
		$(cp "$ssldir_x64/bin/libeay32.dll" "bin/x64/")
		$(cp "$ssldir_x64/bin/ssleay32.dll" "bin/x64/")
	fi
fi


# Windows setup
if [ "$os" == "windows" ]; then
	# Download premake executable
	$(curl -L -o "tmp/premake5.zip" "https://github.com/premake/premake-core/releases/download/v$PREMAKE_VERSION/premake-$PREMAKE_VERSION-windows.zip")
	$(unzip -u -q "tmp/premake5.zip" -d "bin")

# Linux setup
elif [ "$os" == "linux" ]; then
	# Determine whether we need to build from source or not
	if [ "$arch" == "x86_64" ]; then
		# Download premake executable
		$(curl -L -o "tmp/premake5.tar.gz" "https://github.com/premake/premake-core/releases/download/v$PREMAKE_VERSION/premake-$PREMAKE_VERSION-linux.tar.gz")
		$(tar -xvzf "tmp/premake5.tar.gz" -C "bin")
	else
		# Download premake source package
		$(curl -L -o "tmp/premake5-src.zip" "https://github.com/premake/premake-core/releases/download/v$PREMAKE_VERSION/premake-$PREMAKE_VERSION-src.zip")
		$(unzip -o "tmp/premake5-src.zip" -d "tmp")

		# Build premake
		echo "Building premake from source.."
		$(make -C "tmp/premake-$PREMAKE_VERSION/build/gmake.unix/")
		$(cp "tmp/premake-$PREMAKE_VERSION/bin/release/premake5" "bin/")
	fi

# Mac OS X setup
elif [ "$os" == "osx" ]; then
	# Download premake executable
	$(curl -L -o "tmp/premake5.tar.gz" "https://github.com/premake/premake-core/releases/download/v$PREMAKE_VERSION/premake-$PREMAKE_VERSION-macosx.tar.gz")
	$(tar -xvzf "tmp/premake5.tar.gz" -C "bin")
fi

git submodule update --init