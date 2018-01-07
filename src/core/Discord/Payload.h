#pragma once
#include "Discord/Opcode.h"

#include <QtCore/QJsonObject>
#include <QtCore/QString>

QDISCORD_NAMESPACE_BEGIN

struct Payload
{
	QJsonValue event_data;
	QString event_name;

	Opcode opcode;

	int sequence_number;
};

QDISCORD_NAMESPACE_END