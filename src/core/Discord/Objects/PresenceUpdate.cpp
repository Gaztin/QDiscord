#include "PresenceUpdate.h"

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>

QDISCORD_NAMESPACE_BEGIN

PresenceUpdate::PresenceUpdate(const QJsonObject& data)
	: status_(data["status"].toString())
	, game_(data["game"].toObject())
	, user_(data["user"].toObject())
	, guild_id_(data["guild_id"].toString().toULongLong())
{
	QJsonArray roles_array = data["roles"].toArray();
	for (QJsonValue role_value : roles_array)
	{
		roles_.append(role_value.toString().toULongLong());
	}
}

QDISCORD_NAMESPACE_END