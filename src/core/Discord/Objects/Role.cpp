#include "Role.h"

#include <QtCore/QJsonObject>

QDISCORD_NAMESPACE_BEGIN

Role::Role(const QJsonObject& data)
	: name_(data["name"].toString())
	, id_(data["id"].toString().toULongLong())
	, color_(data["color"].toInt())
	, position_(data["position"].toInt())
	, permissions_(data["permissions"].toInt())
	, hoist_(data["hoist"].toBool())
	, managed_(data["managed"].toBool())
	, mentionable_(data["mentionable"].toBool())
{
}

Role::operator QJsonObject() const
{
	QJsonObject data;
	data["name"] = name_;
	data["id"] = QString::number(id_);
	data["color"] = color_;
	data["position"] = position_;
	data["permissions"] = permissions_;
	data["hoist"] = hoist_;
	data["managed"] = managed_;
	data["mentionable"] = mentionable_;

	return data;
}

QDISCORD_NAMESPACE_END