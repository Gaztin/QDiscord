#include "TestBotClient.h"

#include <Discord/Objects/Message.h>
#include <Discord/Patches/ChannelPatch.h>
#include <Discord/Patches/GuildPatch.h>
#include <Discord/Patches/GuildMemberPatch.h>
#include <Discord/Promise.h>

TestBotClient::TestBotClient(QObject* parent)
	: Discord::Client("test-bot")
{
	connect(this, &Client::onMessageCreate, this, &TestBotClient::handleMessage);
}

void TestBotClient::handleMessage(const Discord::Message& message)
{
	if (message.content() == "!test")
	{
		getChannel(message.channelId()).then([=](
				const Discord::Channel& channel) {
			createMessage(channel.id(), QString("Channel name is '%1'").arg(
				channel.name())).then([=]
					(const Discord::Message& message) {
				listGuildEmojis(channel.guildId()).then([=]
						(const QList<Discord::Emoji>& emojis) {
					if (!emojis.empty()) {
						createReaction(message.channelId(), message.id(), QString(":%1:%2")
							.arg(emojis.first().name()).arg(emojis.first().id()));
					}
				});
			});
		}).otherwise([=](){
			createMessage(message.channelId(), QString(
				"Failed to get channel by ID: %1").arg(message.channelId()));
		});
	}
	else if (message.content().startsWith("!img "))
	{
		QStringList args = message.content().split(' ');
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
			createMessage(message.channelId(), new_messages.join('\n'));
		}
	}
	else if (message.content().startsWith("!react "))
	{
		QStringList args = message.content().split(' ');
		if (!args.empty())
		{
			QString emoji = args[1];
			QRegExp rx("<:*:*>");
			rx.setPatternSyntax(QRegExp::Wildcard);
			if (rx.exactMatch(emoji))
			{
				emoji.remove(0, 2);
				emoji.remove(emoji.length() - 1, 1);
				createReaction(message.channelId(), message.id(), emoji);
			}
		}
	}
	else if (message.content().startsWith("!removereactions "))
	{
		QStringList args = message.content().split(' ');
		if (args.size() == 2)
		{
			QString message_id = args[1];
			deleteAllReactions(message.channelId(), message_id.toULongLong());
		}
	}
	else if (message.content() == "!trigger")
	{
		triggerTypingIndicator(message.channelId());
	}
	else if (message.content().startsWith("!modify "))
	{
		QStringList args = message.content().split(' ');
		if (args.length() >= 5)
		{
			if (args[1] == "channel")
			{
				snowflake_t channel_id = args[2].toULongLong();
				Discord::ChannelPatch patch;

				for (int i = 3; (i + 1) < args.length(); i += 2)
				{
					if (args[i] == "name")
					{
						patch.setName(args[i + 1]);
					}
					else if (args[i] == "nsfw")
					{
						if (args[i + 1] == "true")
							patch.setNsfw(true);
						else if (args[i + 1] == "false")
							patch.setNsfw(false);
					}
					else if (args[i] == "topic")
					{
						patch.setTopic(args[i + 1]);
					}
				}

				modifyChannel(channel_id, patch);
			}
			else if (args[1] == "guild")
			{
				snowflake_t guild_id = args[2].toULongLong();
				Discord::GuildPatch patch;

				for (int i = 3; (i + 1) < args.length(); i += 2)
				{
					if (args[i] == "name")
					{
						patch.setName(args[i + 1]);
					}
				}

				modifyGuild(guild_id, patch);
			}
			else if (args[1] == "member")
			{
				QStringList ids = args[2].split(',');
				if (ids.length() == 2)
				{
					snowflake_t guild_id = ids[0].toULongLong();
					snowflake_t user_id = ids[1].toULongLong();
					Discord::GuildMemberPatch patch;

					for (int i = 3; (i + 1) < args.length(); i += 2)
					{
						if (args[i] == "nick")
						{
							patch.setNick(args[i + 1]);
						}
						else if (args[i] == "roles")
						{
							QStringList roles = args[i + 1].split(',');
							QList<snowflake_t> role_ids;
							for (const QString& role : roles)
								role_ids.append(role.toULongLong());

							patch.setRoles(role_ids);
						}
					}

					modifyGuildMember(guild_id, user_id, patch);
				}
			}
		}
	}
	else if (message.content() == "!embed")
	{
		QList<Discord::EmbedField> fields;
		for (int i = 0; i < 9; ++i)
		{
			Discord::EmbedField field;
			field.setDisplayInline(true);
			field.setName(QString("Name %1").arg(i));
			field.setValue(QString("Value %1").arg(i));
			fields.append(field);
		}

		Discord::Embed embed;
		embed.setTitle("Title");
		embed.setDescription("Description");
		embed.setFields(fields);

		createMessage(message.channelId(), embed);
	}
	else if (message.content().startsWith("!roles "))
	{
		getChannel(message.channelId()).then(
			[this, message](const Discord::Channel& channel)
			{
				getGuildRoles(channel.guildId()).then(
					[this, message](const QList<Discord::Role>& guild_roles)
					{
						QStringList echo = { "Mentioned roles were:" };

						for (snowflake_t mentioned_role_id : message.mentionRoles())
						{
							for (const Discord::Role& guild_role : guild_roles)
							{
								if (guild_role.id() == mentioned_role_id)
								{
									echo.append("<@&" + QString::number(mentioned_role_id) + ">");
								}
							}
						}

						createMessage(message.channelId(), echo.join(' '));
					}
				);
			}
		);
	}

#ifdef QT_DEBUG
	qDebug("[%s]: %s", qPrintable(message.author().username()),
		qPrintable(message.content()));
#endif
}
