/*
 * Copyright (c) 2020 Sebastian Kylander https://gaztin.com/
 *
 * This software is provided 'as-is', without any express or implied warranty. In no event will
 * the authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose, including commercial
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the
 *    original software. If you use this software in a product, an acknowledgment in the product
 *    documentation would be appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as
 *    being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include "MainWindow.h"

#include "LogInDialog.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, discord_client_(ui_, this)
{
	ui_.setupUi(this);

	connect(ui_.action_about_qt, &QAction::triggered, &QApplication::aboutQt);
	connect(ui_.action_log_in, &QAction::triggered, this, &MainWindow::logIn);

	connect(ui_.list_widget_guilds, &QListWidget::itemSelectionChanged,
		[this]
	{
		ui_.list_widget_channels->clear();
		ui_.list_widget_messages->clear();

		QList<QListWidgetItem*> selected_items =
			ui_.list_widget_guilds->selectedItems();
		if (selected_items.length() == 1)
		{
			snowflake_t guild_id = selected_items[0]->data(
				Qt::UserRole).toULongLong();
			discord_client_.getGuildChannels(guild_id).then(
				[this](const QList<Discord::Channel>& cs)
			{
				Q_FOREACH(const Discord::Channel& c, cs)
				{
					QListWidgetItem* item = new QListWidgetItem;
					item->setData(Qt::UserRole, c.id());
					item->setText("#" + c.name());
					ui_.list_widget_channels->addItem(item);
				}
			});
		}
	});

	connect(ui_.list_widget_channels, &QListWidget::itemSelectionChanged,
		[this]
	{
		ui_.list_widget_messages->clear();

		QList<QListWidgetItem*> selected_items =
			ui_.list_widget_channels->selectedItems();
		if (selected_items.length() != 1)
			return;

		snowflake_t channel_id = selected_items[0]->data(
			Qt::UserRole).toULongLong();
		discord_client_.getChannelMessages(channel_id).then(
			[this](const QList<Discord::Message>& ms)
		{
			Q_FOREACH(const Discord::Message& m, ms)
			{
				discord_client_.handleMessage(m);
			}
		});
	});

	connect(ui_.line_edit_message, &QLineEdit::returnPressed,
		[this]
	{
		QList<QListWidgetItem*> selected_channel_items =
			ui_.list_widget_channels->selectedItems();
		if (selected_channel_items.length() != 1)
			return;

		snowflake_t channel_id = selected_channel_items[0]->data(
			Qt::UserRole).toULongLong();
		discord_client_.createMessage(channel_id, ui_.line_edit_message->text());
		ui_.line_edit_message->clear();
	});
}

void MainWindow::logIn()
{
	LogInDialog log_in_dialog(this);
	if (log_in_dialog.exec() == QDialog::Accepted)
	{
		discord_client_.login(log_in_dialog.token());
	}
}
