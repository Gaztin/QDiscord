#pragma once
#include "GeneratedFiles/ui_MainWindow.h"
#include "TestBotClient.h"

class MainWindow : public QMainWindow
{
public:
	MainWindow(QWidget* parent = nullptr);

	void logIn();

private:
	Ui_MainWindow ui_;

	TestBotClient discord_client_;
};