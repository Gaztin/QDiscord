#pragma once
#include "GeneratedFiles/ui_LogInDialog.h"

#include <Discord/Token.h>

class LogInDialog : public QDialog
{
public:
	LogInDialog(QWidget* parent = nullptr);

	Discord::Token token() const;

private slots:
	void onTokenTextChanged(const QString& text);

private:
	Ui_LogInDialog ui_;
};
