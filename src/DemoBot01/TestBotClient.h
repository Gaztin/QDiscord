#pragma once
#include <Discord/Client.h>

class TestBotClient : public Discord::Client
{
public:
	TestBotClient(QObject* parent = nullptr);

protected:
	void handleMessage(const Discord::Message& message);
};