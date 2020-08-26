/*
 * Copyright (c) 2020 Sebastian Kylander https://gaztin.com/
 *
 * This software is provided 'as-is', without any express or implied warranty. In no event will
 * the authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose, including commercial
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the
 *    original software. If you use this software in a product, an acknowledgment in the product
 *    documentation would be appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as
 *    being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

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
