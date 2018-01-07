#pragma once
#include "Discord/User.h"

#include <QtCore/QDateTime>
#include <QtCore/QList>
#include <QtCore/QString>

QDISCORD_NAMESPACE_BEGIN

struct GuildMember
{
	QList<snowflake_t> roles;

	QDateTime joined_at;
	QString nick;

	User user;

	bool deaf;
	bool mute;
};

QDISCORD_NAMESPACE_END