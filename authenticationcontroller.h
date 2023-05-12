#pragma once

#include <QObject>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

class AuthenticationController : public QObject {
    Q_OBJECT

public:
    void authenticate(const QString& username, const QString& password);

signals:
    void authenticationRequested(const QString& username, const QString& password);

    void authenticationResult(const bool& result);

private:
    std::queue<bool> resultQueue;
    std::mutex resultMutex;
    std::condition_variable resultReady;
};

