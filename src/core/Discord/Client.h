#pragma once
#include "Discord.h"

#include <QtCore/QObject>

QDISCORD_NAMESPACE_BEGIN

class Client : public QObject
{
public:
	Client(QObject* parent = nullptr);
};

QDISCORD_NAMESPACE_END