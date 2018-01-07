#pragma once
#include "Discord.h"

#include <QtCore/QString>

QDISCORD_NAMESPACE_BEGIN

enum class GameType
{
	GAME,
	STREAMING,
};

struct Game
{
	QString name;
	QString url;

	GameType type;
};

QDISCORD_NAMESPACE_END