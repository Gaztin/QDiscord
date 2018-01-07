#include <Discord/Client.h>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	QMainWindow window;

	Discord::Client client;

	window.show();

	return app.exec();
}