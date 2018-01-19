#pragma once
#include "Discord.h"

#include <QtCore/QJsonObject>

QDISCORD_NAMESPACE_BEGIN

class Patch
{
public:
	operator QJsonObject() const { return data_; }

protected:
	QJsonObject data_;
};

QDISCORD_NAMESPACE_END