#pragma once
#include "Discord.h"

#include <QtCore/QString>

QDISCORD_NAMESPACE_BEGIN

enum class ActivityType
{
	GAME,
	STREAMING,
	LISTENING,
};

struct ActivityTimestamps
{
	int start;
	int end;
};

struct ActivityParty
{
	QString id;
	int current_size;
	int max_size;
};

struct ActivityAssets
{
	QString large_image;
	QString large_text;
	QString small_imgae;
	QString small_text;
};

struct Activity
{
	QString name;
	QString url;
	QString details;
	QString state;

	ActivityTimestamps timestamps;
	ActivityParty party;
	ActivityAssets assets;

	ActivityType type;

	snowflake_t application_id;
};

QDISCORD_NAMESPACE_END