#pragma once
#include "Discord/Objects/User.h"

class QJsonObject;

QDISCORD_NAMESPACE_BEGIN

class Webhook
{
public:
	explicit Webhook(const QJsonObject& data);

	const QString& name() const { return name_; }
	const QString& avatar() const { return avatar_; }
	const QString& token() const { return token_; }

	const User& user() const { return user_; }

	snowflake_t id() const { return id_; }
	snowflake_t guildId() const { return guild_id_; }
	snowflake_t channelId() const { return channel_id_; }

	operator QJsonObject() const;

private:
	QString name_;
	QString avatar_;
	QString token_;

	User user_;

	snowflake_t id_;
	snowflake_t guild_id_;
	snowflake_t channel_id_;
};

QDISCORD_NAMESPACE_END