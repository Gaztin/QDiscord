#include "MainWindow.h"
#include "EmbedsClient.h"

#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	qputenv("QT_QPA_PLATFORM_PLUGIN_PATH", ".");

	QApplication app(argc, argv);
	MainWindow window;

	window.show();

	return app.exec();
}