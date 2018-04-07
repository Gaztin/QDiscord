#include "BotUserClient.h"

#include <Discord/Objects/Message.h>
#include <Discord/Patches/ChannelPatch.h>
#include <Discord/Patches/GuildPatch.h>
#include <Discord/Patches/GuildMemberPatch.h>
#include <Discord/Promise.h>

BotUserClient::BotUserClient(Ui_MainWindow& window_layout, QObject* parent)
	: Discord::Client("botuser")
	, window_layout_ref_(window_layout)
{
}

void BotUserClient::onReady(const Discord::User& user,
		const QList<Discord::Channel>& private_channels,
		const QList<Discord::Guild>& guilds)
{
	Q_FOREACH(const Discord::Guild& _g, guilds)
	{
		getGuild(_g.id()).then(
			[&](const Discord::Guild& g)
		{
				QListWidgetItem* item = new QListWidgetItem;
				window_layout_ref_.list_widget->addItem(item);
#ifdef QT_DEBUG
				qDebug("Guild: %s\n", qPrintable(g.name()));
#endif
				getGuildIconPixmap(g,
					Discord::Client::IconImageSupportedExtension::PNG).then(
					[item](const QPixmap& p)
				{
					item->setIcon(p);
#ifdef QT_DEBUG
					qDebug("  Icon size: %d x %d\n", p.width(), p.height());
#endif
					QSize icon_size = p.size().expandedTo(
						item->listWidget()->iconSize());
					item->listWidget()->setIconSize(icon_size);
				});
		});
	}
}

void BotUserClient::onMessageCreate(const Discord::Message& message)
{
}