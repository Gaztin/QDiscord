#include "TestBotClient.h"

#include <Discord/Message.h>

TestBotClient::TestBotClient(QObject* parent)
	: Discord::Client("test-bot")
{
}

void TestBotClient::onReady(const Discord::User& user,
		const QList<Discord::Channel>& private_channels,
		const QList<Discord::Guild>& guilds)
{
#ifdef QT_DEBUG
	qDebug("onReady()");
#endif
}

void TestBotClient::onMessageCreate(const Discord::Message& message)
{
	if (message.content == "!test")
	{
		sendMessage(message.channel_id, "This is a test message");
	}
	else if (message.content.startsWith("!img "))
	{
		QStringList args = message.content.split(' ');
		args.pop_front();

		QStringList new_messages;
		while (!args.empty())
		{
			// Remove start and end tags ('<' and '>')
			QString emoji = args[0];
			emoji.remove(0, 1);
			emoji.remove(emoji.length() - 1, 1);

			// Parse the emoji ID
			QStringList split_emoji = emoji.split(':');
			if (split_emoji.size() == 3)
			{
				new_messages.append(QString(
					"https://cdn.discordapp.com/emojis/%1.png").arg(
						split_emoji[2]));
			}

			args.pop_front();
		}

		if (!new_messages.empty())
		{
			sendMessage(message.channel_id, new_messages.join('\n'));
		}
	}

#ifdef QT_DEBUG
	qDebug("[%s]: %s", qPrintable(message.author.username),
		qPrintable(message.content));
#endif
}