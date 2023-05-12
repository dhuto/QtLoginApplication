#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

class LoginView : public QWidget {
    Q_OBJECT

public:
    LoginView(QWidget *parent = nullptr);

signals:
    void loginRequested(const QString& username, const QString& password);

private slots:
    void onLoginClicked();

public slots:
    void handleResult(const bool& result);

private:
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;
    QVBoxLayout *layout;
    QMessageBox *messageBox;
};
