#pragma once

#include "authenticationcontroller.h"
#include "loginview.h"

#include <QObject>
#include <QMessageBox>

class LoginController : public QObject {
    Q_OBJECT
public:
    LoginController(LoginView* view, AuthenticationController* authController, QObject* parent = nullptr);

    ~LoginController();

    void start();

    void stop();

private:
    void handleRequest(const QString& username, const QString& password);

    void handleRequests();

    void handleResult(const bool& result);

    void handleResults();

private:

    LoginView* view;
    AuthenticationController* authController;

    std::queue<std::pair<QString, QString>> requestQueue;
    std::mutex requestMutex;
    std::condition_variable requestReady;
    std::thread requestThread;

    std::queue<bool> resultQueue;
    std::mutex resultMutex;
    std::condition_variable resultReady;
    std::thread resultThread;

    bool stopping = false;

signals:
    void messageResult(const bool& result);
};
