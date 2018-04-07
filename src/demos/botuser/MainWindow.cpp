#include "MainWindow.h"

#include "LogInDialog.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, discord_client_(ui_, this)
{
	ui_.setupUi(this);

	connect(ui_.action_about_qt, &QAction::triggered, &QApplication::aboutQt);
	connect(ui_.action_log_in, &QAction::triggered, this, &MainWindow::logIn);
}

void MainWindow::logIn()
{
	LogInDialog log_in_dialog(this);
	if (log_in_dialog.exec() == QDialog::Accepted)
	{
		discord_client_.login(log_in_dialog.token());
	}
}