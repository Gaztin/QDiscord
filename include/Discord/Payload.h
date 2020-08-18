#pragma once
#include <QtCore/QJsonObject>
#include <QtCore/QString>

QDISCORD_NAMESPACE_BEGIN

enum class PayloadOpcode
{
	DISPATCH = 0,
	HEARTBEAT,
	IDENTIFY,
	STATUS_UPDATE,
	VOICE_STATE_UPDATE,
	VOICE_SERVER_PING,
	RESUME,
	RECONNECT,
	REQUEST_GUILD_MEMBERS,
	INVALID_SESSION,
	HELLO,
	HEARTHBEAT_ACK,
};

struct Payload
{
	QJsonValue event_data;
	QString event_name;

	PayloadOpcode opcode;

	int sequence_number;
};

QDISCORD_NAMESPACE_END