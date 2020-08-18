#include "EmbedDialog.h"

EmbedDialog::EmbedDialog(EmbedsClient* client, QWidget* parent)
	: QDialog(parent)
{
	ui_.setupUi(this);

	connect(ui_.combo_box_guilds, static_cast<void(QComboBox::*)(int)>(
		&QComboBox::currentIndexChanged),
		[this, client](int index)
	{
		QVariant d = ui_.combo_box_guilds->itemData(index, Qt::UserRole);

		ui_.combo_box_channels->clear();
		ui_.combo_box_channels->setEnabled(d.isValid());

		if (d.isValid())
		{
			client->getGuildChannels(d.toULongLong()).then(
				[this](const QList<Discord::Channel>& cs)
			{
				Q_FOREACH(const Discord::Channel c, cs)
				{
					ui_.combo_box_channels->addItem(c.name(), c.id());
				}
			});
		}
	});

	client->getCurrentUserGuilds().then(
		[this, client](const QList<Discord::Guild>& gs)
	{
		Q_FOREACH(const Discord::Guild& g, gs)
		{
			ui_.combo_box_guilds->addItem(g.name(), g.id());
		}
	});
}

snowflake_t EmbedDialog::channelId() const
{
	return ui_.combo_box_channels->currentData(Qt::UserRole).toULongLong();
}

Discord::Embed EmbedDialog::embed() const
{
	Discord::Embed e;
	e.setTitle(ui_.text_edit_title->toPlainText());
	e.setDescription(ui_.text_edit_description->toPlainText());

	Discord::EmbedFooter footer;
	footer.setText(ui_.text_edit_footer->toPlainText());
	e.setFooter(footer);

	Discord::EmbedImage image;
	image.setUrl(ui_.line_edit_image->text());
	e.setImage(image);

	Discord::EmbedImage thumbnail;
	thumbnail.setUrl(ui_.line_edit_thumbnail->text());
	e.setThumbnail(thumbnail);

	return e;
}
