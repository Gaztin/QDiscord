#pragma once
#include <Discord/Client.h>

#include "GeneratedFiles/ui_MainWindow.h"

class BotUserClient : public Discord::Client
{
public:
	BotUserClient(Ui_MainWindow& window_layout, QObject* parent = nullptr);

	void handleNewMessage(const Discord::Message& message);

protected:
	virtual void onReady(const Discord::User& user,
		const QList<Discord::Channel>& private_channels,
		const QList<Discord::Guild>& guilds) override;
	virtual void onMessageCreate(const Discord::Message& message) override;

private:
	Ui_MainWindow& window_layout_ref_;
};