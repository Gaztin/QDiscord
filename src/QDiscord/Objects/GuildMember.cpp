#include "GuildMember.h"

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>

QDISCORD_NAMESPACE_BEGIN

GuildMember::GuildMember(const QJsonObject& data)
	: joined_at_(QDateTime::fromString(data["joined_at"].toString(),
		Qt::ISODate))
	, nick_(data["nick"].toString())
	, user_(data["user"].toObject())
	, deaf_(data["deaf"].toBool())
	, mute_(data["mute"].toBool())
{
	QJsonArray roles_array = data["roles"].toArray();
	for (QJsonValue role_value : roles_array)
	{
		roles_.append(role_value.toString().toULongLong());
	}
}

QDISCORD_NAMESPACE_END