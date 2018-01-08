#pragma once
#include "Discord/Emoji.h"

QDISCORD_NAMESPACE_BEGIN

struct Reaction
{
	Emoji emoji;

	int count;

	bool me;
};

QDISCORD_NAMESPACE_END