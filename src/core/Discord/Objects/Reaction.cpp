#include "Reaction.h"

#include <QtCore/QJsonObject>

QDISCORD_NAMESPACE_BEGIN

Reaction::Reaction(const QJsonObject& data)
	: emoji_(data["emoji"].toObject())
	, count_(data["count"].toInt())
	, me_(data["me"].toBool())
{
}

QDISCORD_NAMESPACE_END