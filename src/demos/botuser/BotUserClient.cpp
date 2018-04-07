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
		getGuild(_g.id()).then([&](const Discord::Guild& g)
			{
				QListWidgetItem* item = new QListWidgetItem;
				QByteArray bytes = g.icon().toLocal8Bit();
				QPixmap pixmap;
				pixmap.loadFromData(QByteArray::fromBase64(bytes), "PNG");

				item->setIcon(pixmap);

#ifdef QT_DEBUG
				qDebug("Guild : %s\n  Icon size: %d x %d\n", qPrintable(g.name()), pixmap.width(), pixmap.height());
#endif

				window_layout_ref_.list_widget->addItem(item);
			}
		);
	}
}

void BotUserClient::onMessageCreate(const Discord::Message& message)
{
}