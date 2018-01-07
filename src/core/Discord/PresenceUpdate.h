#pragma once
#include "Discord/Game.h"
#include "Discord/User.h"

#include <QtCore/QList>
#include <QtCore/QString>

QDISCORD_NAMESPACE_BEGIN

struct PresenceUpdate
{
	QList<snowflake_t> roles;

	QString status;

	Game game;
	User user;

	snowflake_t guild_id;
};

QDISCORD_NAMESPACE_END