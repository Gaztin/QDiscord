#pragma once
#include "Discord/Objects/User.h"

#include <QtCore/QDateTime>
#include <QtCore/QList>
#include <QtCore/QString>

class QJsonObject;

QDISCORD_NAMESPACE_BEGIN

class GuildMember
{
public:
	explicit GuildMember(const QJsonObject& data);

	const QList<snowflake_t>& roles() const { return roles_; }
	
	const QDateTime& joinedAt() const { return joined_at_; }
	const QString& nick() const { return nick_; }
	
	const User& user() const { return user_; }
	
	bool deaf() const { return deaf_; }
	bool mute() const { return mute_; }

private:
	QList<snowflake_t> roles_;
	
	QDateTime joined_at_;
	QString nick_;
	
	User user_;
	
	bool deaf_;
	bool mute_;
};

QDISCORD_NAMESPACE_END