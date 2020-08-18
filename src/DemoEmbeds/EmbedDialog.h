#pragma once
#include "GeneratedFiles/ui_EmbedDialog.h"
#include "EmbedsClient.h"

#include <Discord/Objects/Embed.h>

class EmbedDialog : public QDialog
{
public:
	EmbedDialog(EmbedsClient* client, QWidget* parent = nullptr);

	snowflake_t channelId() const;
	Discord::Embed embed() const;

	void testfunc(int i) {}

private:
	Ui_EmbedDialog ui_;
};
