#include "MainWindow.h"

#include "LogInDialog.h"
#include "EmbedDialog.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, discord_client_(this)
{
	ui_.setupUi(this);

	connect(ui_.action_about_qt, &QAction::triggered, &QApplication::aboutQt);
	connect(ui_.action_log_in, &QAction::triggered, this, &MainWindow::logIn);
	connect(ui_.action_new_embed, &QAction::triggered, this,
		&MainWindow::newEmbed);
}

void MainWindow::logIn()
{
	LogInDialog log_in_dialog(this);
	if (log_in_dialog.exec() == QDialog::Accepted)
	{
		discord_client_.login(log_in_dialog.token());
	}
}

void MainWindow::newEmbed()
{
	EmbedDialog embed_dialog(&discord_client_, this);
	if (embed_dialog.exec() == QDialog::Accepted)
	{
		discord_client_.createMessage(embed_dialog.channelId(),
			embed_dialog.embed());
	}
}
