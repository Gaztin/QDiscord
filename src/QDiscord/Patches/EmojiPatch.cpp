#include "EmojiPatch.h"

#include <QtCore/QJsonArray>
#include <QtCore/QList>

QDISCORD_NAMESPACE_BEGIN

void EmojiPatch::setName(const QString& name)
{
	data_["name"] = name;
}

void EmojiPatch::setRoles(const QList<snowflake_t>& roles)
{
	QJsonArray roles_array;

	for (snowflake_t role : roles)
	{
		roles_array.append(QString::number(role));
	}

	data_["roles"] = roles_array;
}

QDISCORD_NAMESPACE_END