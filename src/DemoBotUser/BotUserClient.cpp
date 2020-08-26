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

#include "BotUserClient.h"

#include <Discord/Objects/Message.h>
#include <Discord/Patches/ChannelPatch.h>
#include <Discord/Patches/GuildPatch.h>
#include <Discord/Patches/GuildMemberPatch.h>
#include <Discord/Promise.h>

BotUserClient::BotUserClient(Ui_MainWindow& window_layout, QObject* parent)
	: Discord::Client("botuser", parent)
	, window_layout_ref_(window_layout)
{
	connect(this, &Client::onMessageCreate, this, &BotUserClient::handleMessage);
	connect(this, &Client::onReady, this, &BotUserClient::onConnected);
}

void BotUserClient::handleMessage(const Discord::Message& message)
{
	QList<QListWidgetItem*> selected_guild_items =
		window_layout_ref_.list_widget_guilds->selectedItems();
	if (selected_guild_items.length() != 1)
		return;

	QList<QListWidgetItem*> selected_channel_items =
		window_layout_ref_.list_widget_channels->selectedItems();
	if (selected_channel_items.length() != 1)
		return;

	QListWidgetItem* guild_item = selected_guild_items[0];
	QListWidgetItem* channel_item = selected_channel_items[0];
	getChannel(message.channelId()).then(
		[this, channel_item, guild_item, message](const Discord::Channel& c)
	{
		if (c.guildId() != guild_item->data(Qt::UserRole).toULongLong())
			return;
		if (c.id() != channel_item->data(Qt::UserRole).toULongLong())
			return;

		QListWidgetItem* item = new QListWidgetItem;
		item->setData(Qt::UserRole, message.id());
		item->setText(message.author().username() + ": " + message.content());
		window_layout_ref_.list_widget_messages->addItem(item);

		getUserAvatarPixmap(message.author(),
			Discord::Client::AvatarImageSupportedExtension::PNG).then(
			[item](const QPixmap& p)
		{
			item->setIcon(p);
		});
	});
}

void BotUserClient::onConnected(const Discord::User& /*user*/,
		const QList<Discord::Channel>& /*private_channels*/,
		const QList<Discord::Guild>& guilds)
{
	Q_FOREACH(const Discord::Guild& _g, guilds)
	{
		getGuild(_g.id()).then(
			[&](const Discord::Guild& g)
		{
			QListWidgetItem* item = new QListWidgetItem;
			item->setData(Qt::UserRole, g.id());
			window_layout_ref_.list_widget_guilds->addItem(item);

			getGuildIconPixmap(g,
				Discord::Client::IconImageSupportedExtension::PNG).then(
				[item](const QPixmap& p)
			{
				QSize icon_size = item->listWidget()->iconSize().expandedTo(
					p.size());

				item->setIcon(p);
				item->listWidget()->setIconSize(icon_size);
			});
		});
	}
}
