#pragma once
#include "Discord/Objects/Attachment.h"
#include "Discord/Objects/Embed.h"
#include "Discord/Objects/Reaction.h"
#include "Discord/Objects/Role.h"
#include "Discord/Objects/User.h"

#include <QtCore/QDateTime>
#include <QtCore/QString>

class QJsonObject;

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

class Message
{
public:
	explicit Message(const QJsonObject& data);

	const QList<User>& mentions() const { return mentions_; }
	const QList<Role>& mentionRoles() const { return mention_roles_; }
	const QList<Attachment>& attachments() const { return attachments_; }
	const QList<Embed>& embeds() const { return embeds_; }
	const QList<Reaction>& reactions() const { return reactions_; }
	
	const QDateTime& timestamp() const { return timestamp_; }
	const QDateTime& editedTimestamp() const { return edited_timestamp_; }
	const QString& content() const { return content_; }
	const QString& webhookId() const { return webhook_id_; }
	
	const User& author() const { return author_; }
	const MessageType& type() const { return type_; }
	
	snowflake_t id() const { return id_; }
	snowflake_t channelId() const { return channel_id_; }
	snowflake_t nonce() const { return nonce_; }
	
	bool tts() const { return tts_; }
	bool mentionEveryone() const { return mention_everyone_; }
	bool pinned() const { return pinned_; }

private:
	QList<User> mentions_;
	QList<Role> mention_roles_;
	QList<Attachment> attachments_;
	QList<Embed> embeds_;
	QList<Reaction> reactions_;
	
	QDateTime timestamp_;
	QDateTime edited_timestamp_;
	QString content_;
	QString webhook_id_;
	
	User author_;
	MessageType type_;
	
	snowflake_t id_;
	snowflake_t channel_id_;
	snowflake_t nonce_;
	
	bool tts_;
	bool mention_everyone_;
	bool pinned_;
};

QDISCORD_NAMESPACE_END