#include "GuildMemberPatch.h"

#include <QtCore/QJsonArray>
#include <QtCore/QList>

QDISCORD_NAMESPACE_BEGIN

void GuildMemberPatch::addRole(snowflake_t role)
{
	QJsonObject::const_iterator role_iterator = data_.find("roles");
	QJsonArray roles_array;
	if (role_iterator != data_.constEnd())
	{
		roles_array = role_iterator->toArray();
	}

	roles_array.append(QString::number(role));
	data_["role"] = roles_array;
}

void GuildMemberPatch::setRoles(const QList<snowflake_t>& roles)
{
	QJsonArray roles_array;
	for (snowflake_t role : roles)
	{
		roles_array.append(QString::number(role));
	}

	data_["role"] = roles_array;
}

void GuildMemberPatch::setNick(const QString& nick)
{
	data_["nick"] = nick;
}

void GuildMemberPatch::setChannelId(snowflake_t channel_id)
{
	data_["channel_id"] = QString::number(channel_id);
}

void GuildMemberPatch::setMute(bool mute)
{
	data_["mute"] = mute;
}

void GuildMemberPatch::setDeaf(bool deaf)
{
	data_["deaf"] = deaf;
}

QDISCORD_NAMESPACE_END