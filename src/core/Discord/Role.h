#pragma once
#include "Discord.h"

#include <QtCore/QString>

QDISCORD_NAMESPACE_BEGIN

struct Role
{
	QString name;

	snowflake_t id;

	int color;
	int position;
	int permissions;

	bool hoist;
	bool managed;
	bool mentionable;
};

QDISCORD_NAMESPACE_END