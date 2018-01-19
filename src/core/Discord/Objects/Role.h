#pragma once
#include "Discord.h"

#include <QtCore/QString>

class QJsonObject;

QDISCORD_NAMESPACE_BEGIN

class Role
{
public:
	explicit Role(const QJsonObject& data);

	const QString& name() const { return name_; }
	
	snowflake_t id() const { return id_; }
	
	int color() const { return color_; }
	int position() const { return position_; }
	int permissions() const { return permissions_; }
	
	bool hoist() const { return hoist_; }
	bool managed() const { return managed_; }
	bool mentionable() const { return mentionable_; }

private:
	QString name_;
	
	snowflake_t id_;
	
	int color_;
	int position_;
	int permissions_;
	
	bool hoist_;
	bool managed_;
	bool mentionable_;
};

QDISCORD_NAMESPACE_END