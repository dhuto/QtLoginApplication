#include "loginview.h"

LoginView::LoginView(QWidget *parent) 
: QWidget(parent)
{
    setFixedSize(300, 200);

    usernameLineEdit = new QLineEdit(this);
    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    loginButton = new QPushButton("Login", this);

    layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Username", this));
    layout->addWidget(usernameLineEdit);
    layout->addWidget(new QLabel("Password", this));
    layout->addWidget(passwordLineEdit);
    layout->addWidget(loginButton);

    messageBox = new QMessageBox(this);

    connect(loginButton, &QPushButton::clicked, this, &LoginView::onLoginClicked);
}

void LoginView::onLoginClicked()
{
    emit loginRequested(usernameLineEdit->text(), passwordLineEdit->text());
}

void LoginView::handleResult(const bool& result) {
    if (result) {
        // Show a success message to the user
        QMessageBox::information(messageBox, "Success", "Operation succeeded!");
    } else {
        // Show an error message to the user
        QMessageBox::warning(messageBox, "Error", "An error occurred during the operation.");
    }
}