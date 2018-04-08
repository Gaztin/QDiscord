#pragma once
#include "GeneratedFiles/ui_MainWindow.h"
#include "EmbedsClient.h"

class MainWindow : public QMainWindow
{
public:
	MainWindow(QWidget* parent = nullptr);

	void logIn();

private:
	Ui_MainWindow ui_;

	EmbedsClient discord_client_;
};