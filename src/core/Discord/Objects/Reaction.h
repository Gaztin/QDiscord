#pragma once
#include "Discord/Objects/Emoji.h"

class QJsonObject;

QDISCORD_NAMESPACE_BEGIN

class Reaction
{
public:
	explicit Reaction(const QJsonObject& data);

	const Emoji& emoji() const { return emoji_; }
	
	int count() const { return count_; }
	
	bool me() const { return me_; }

private:
	Emoji emoji_;

	int count_;
	
	bool me_;
};

QDISCORD_NAMESPACE_END