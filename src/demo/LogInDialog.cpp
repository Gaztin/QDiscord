#include "LogInDialog.h"

#include <QtWidgets/QPushButton>

LogInDialog::LogInDialog(QWidget* parent)
	: QDialog(parent)
{
	ui_.setupUi(this);

	connect(ui_.token_line_edit, &QLineEdit::textChanged, this,
		&LogInDialog::onTokenTextChanged);

	// Trigger text-changed slot once, initially
	onTokenTextChanged("");
}

Discord::Token LogInDialog::token() const
{
	QString token_base = ui_.token_line_edit->text();
	Discord::Token::Type type = Discord::Token::Type::BOT;

	if (ui_.oauth2_check_box->checkState() == Qt::Checked)
		type = Discord::Token::Type::OAUTH2_BEARER;

	Discord::Token token;
	token.generate(ui_.token_line_edit->text(), Discord::Token::Type::BOT);

	return token;
}

void LogInDialog::onTokenTextChanged(const QString& text)
{
	QPushButton* ok_button = ui_.button_box->button(QDialogButtonBox::Ok);
	if (ok_button)
	{
		ok_button->setDisabled(text.isEmpty());
	}
}