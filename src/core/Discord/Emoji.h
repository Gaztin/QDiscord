#pragma once
#include "Discord/Role.h"

#include <QtCore/QList>

QDISCORD_NAMESPACE_BEGIN

struct Emoji
{
	QList<Role> roles;

	QString name;

	snowflake_t id;

	bool require_colons;
	bool managed;
};

QDISCORD_NAMESPACE_END