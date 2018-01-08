#pragma once
#include "Discord.h"

#include <QtCore/QString>

QDISCORD_NAMESPACE_BEGIN

struct Attachment
{
	QString filename;
	QString url;
	QString proxy_url;

	snowflake_t id;

	int size;
	int height;
	int width;
};

QDISCORD_NAMESPACE_END