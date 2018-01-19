#pragma once
#include "Discord/Objects/Activity.h"
#include "Discord/Objects/User.h"

#include <QtCore/QList>
#include <QtCore/QString>

class QJsonObject;

QDISCORD_NAMESPACE_BEGIN

class PresenceUpdate
{
public:
	explicit PresenceUpdate(const QJsonObject& data);

	const QList<snowflake_t>& roles() const { return roles_; }
	
	const QString& status() const { return status_; }
	
	const Activity& game() const { return game_; }
	const User& user() const { return user_; }
	
	snowflake_t guildId() const { return guild_id_; }

private:
	QList<snowflake_t> roles_;
	
	QString status_;
	
	Activity game_;
	User user_;
	
	snowflake_t guild_id_;
};

QDISCORD_NAMESPACE_END