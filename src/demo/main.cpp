#include "TestBotClient.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QMainWindow>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	QMainWindow window;

	window.show();
	QString token = QInputDialog::getText(nullptr, "QDiscord", "Token");

	TestBotClient client;
	client.connectBot(token);

	return app.exec();
}