#pragma once
#include "Discord.h"

#include <QtCore/QString>

class QJsonObject;

QDISCORD_NAMESPACE_BEGIN

class Overwrite
{
public:
	explicit Overwrite(const QJsonObject& data);

	operator QJsonObject() const;

	const QString& type() const { return type_; }
	
	snowflake_t id() const { return id_; }
	
	int allow() const { return allow_; }
	int deny() const { return deny_; }

private:
	QString type_;
	
	snowflake_t id_;
	
	int allow_;
	int deny_;
};

QDISCORD_NAMESPACE_END