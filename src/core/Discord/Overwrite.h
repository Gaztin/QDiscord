#pragma once
#include "Discord.h"

#include <QtCore/QString>

QDISCORD_NAMESPACE_BEGIN

struct Overwrite
{
	QString type;

	snowflake_t id;

	int allow;
	int deny;
};

QDISCORD_NAMESPACE_END