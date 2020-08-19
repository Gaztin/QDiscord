#pragma once
#include "Discord/Objects/Overwrite.h"
#include "Discord/Objects/User.h"

#include <QtCore/QList>
#include <QtCore/QString>

class QJsonObject;

QDISCORD_NAMESPACE_BEGIN

enum class ChannelType
{
	GUILD_TEXT = 0,
	DM,
	GUILD_VOICE,
	GROUP_DM,
	GUILD_CATEGORY,
};

class Channel
{
public:
	explicit Channel(const QJsonObject& data);

	const QList<Overwrite>& permissionOverwrites() const
		{ return permission_overwrites_; }
	const QList<User>& recipients() const { return recipients_; }
	
	const QString& name() const { return name_; }
	const QString& topic() const { return topic_; }
	const QString& icon() const { return icon_; }
	
	ChannelType type() const { return type_; }
	
	snowflake_t id() const { return id_; }
	snowflake_t guildId() const { return guild_id_; }
	snowflake_t ownerId() const { return owner_id_; }
	snowflake_t applicationId() const { return application_id_; }
	snowflake_t lastMessageId() const { return last_message_id_; }
	snowflake_t parentId() const { return parent_id_; }
	
	int position() const { return position_; }
	int bitrate() const { return bitrate_; }
	int userLimit() const { return user_limit_; }
	int rateLimitPerUser() const { return rate_limit_per_user_; }
	bool nsfw() const { return nsfw_; }

	operator QJsonObject() const;

private:
	QList<Overwrite> permission_overwrites_;
	QList<User> recipients_;
	
	QString name_;
	QString topic_;
	QString icon_;
	
	ChannelType type_;
	
	snowflake_t id_;
	snowflake_t guild_id_;
	snowflake_t owner_id_;
	snowflake_t application_id_;
	snowflake_t last_message_id_;
	snowflake_t parent_id_;
	
	int position_;
	int bitrate_;
	int user_limit_;
	int rate_limit_per_user_;
	bool nsfw_;
};

QDISCORD_NAMESPACE_END