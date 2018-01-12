#include "TestBotClient.h"

#include <Discord/Message.h>
#include <Discord/Promise.h>

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
		getChannel(message.channel_id).then([=](
				const Discord::Channel& channel){
			sendMessage(channel.id, QString("Channel name is '%1'").arg(
				channel.name));

		}).otherwise([=](){
			sendMessage(message.channel_id, QString(
				"Failed to get channel by ID: %1").arg(message.channel_id));
		});
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
	else if (message.content.startsWith("!react "))
	{
		QStringList args = message.content.split(' ');
		if (!args.empty())
		{
			QString emoji = args[1];
			QRegExp rx("<:*:*>");
			rx.setPatternSyntax(QRegExp::Wildcard);
			if (rx.exactMatch(emoji))
			{
				emoji.remove(0, 2);
				emoji.remove(emoji.length() - 1, 1);
				addReaction(message.channel_id, message.id, emoji);
			}
		}
	}
	else if (message.content.startsWith("!removereactions "))
	{
		QStringList args = message.content.split(' ');
		if (args.size() == 2)
		{
			QString message_id = args[1];
			removeAllReactions(message.channel_id, message_id.toULongLong());
		}
	}
	else if (message.content == "!trigger")
	{
		triggerTypingIndicator(message.channel_id);
	}

#ifdef QT_DEBUG
	qDebug("[%s]: %s", qPrintable(message.author.username),
		qPrintable(message.content));
#endif
}