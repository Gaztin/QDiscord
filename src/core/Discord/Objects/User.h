#pragma once
#include "Discord.h"

#include <QtCore/QString>

class QJsonObject;

QDISCORD_NAMESPACE_BEGIN

class User
{
public:
	explicit User(const QJsonObject& data);

	const QString& username() const { return username_; }
	const QString& discriminator() const { return discriminator_; }
	const QString& avatar() const { return avatar_; }
	const QString& email() const { return email_; }
	
	snowflake_t id() const { return id_; }
	
	bool bot() const { return bot_; }
	bool mfaEnabled() const { return mfa_enabled_; }
	bool verified() const { return verified_; }

	operator QJsonObject() const;

private:
	QString username_;
	QString discriminator_;
	QString avatar_;
	QString email_;
	
	snowflake_t id_;
	
	bool bot_;
	bool mfa_enabled_;
	bool verified_;
};

QDISCORD_NAMESPACE_END