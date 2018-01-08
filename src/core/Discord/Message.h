#pragma once
#include "Discord/Attachment.h"
#include "Discord/Embed.h"
#include "Discord/Reaction.h"
#include "Discord/Role.h"
#include "Discord/User.h"

#include <QtCore/QDateTime>
#include <QtCore/QString>

QDISCORD_NAMESPACE_BEGIN

enum class MessageType
{
	DEFAULT = 0,
	RECIPIENT_ADD,
	RECIPIENT_REMOVE,
	CALL,
	CHANNEL_NAME_CHANGE,
	CHANNEL_ICON_CHANGE,
	CHANNEL_PINNED_MESSAGE,
	GUILD_MEMBER_JOIN,
};

struct Message
{
	QList<User> mentions;
	QList<Role> mention_roles;
	QList<Attachment> attachments;
	QList<Embed> embeds;
	QList<Reaction> reactions;

	QDateTime timestamp;
	QDateTime edited_timestamp;
	QString content;
	QString webhook_id;

	User author;

	MessageType type;

	snowflake_t id;
	snowflake_t channel_id;
	snowflake_t nonce;

	bool tts;
	bool mention_everyone;
	bool pinned;
};

QDISCORD_NAMESPACE_END