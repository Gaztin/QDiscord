#pragma once
#include <Discord/Client.h>

class EmbedsClient : public Discord::Client
{
public:
	EmbedsClient(QObject* parent = nullptr);
};