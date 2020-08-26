#pragma once
#include "GeneratedFiles/ui_MainWindow.h"
#include "BotUserClient.h"

class MainWindow : public QMainWindow
{
public:
	MainWindow(QWidget* parent = nullptr);

	void logIn();

private:
	Ui_MainWindow ui_;

	BotUserClient discord_client_;
};
