#include "logincontroller.h"

LoginController::LoginController(LoginView* view, AuthenticationController* authController, QObject* parent = nullptr)
    : QObject(parent), view(view), authController(authController)
{
    QObject::connect(view, &LoginView::loginRequested,
                        this, &LoginController::handleRequest);
    QObject::connect(authController, &AuthenticationController::authenticationResult,
                        this, &LoginController::handleResult);
    QObject::connect(this, &LoginController::messageResult,
                        view, &LoginView::handleResult);
}

LoginController::~LoginController()
{
    stop();
}

void LoginController::start() 
{
    requestThread = std::thread(&LoginController::handleRequests, this);
    resultThread = std::thread(&LoginController::handleResults, this);
}

void LoginController::stop() 
{
    stopping = true;
    requestReady.notify_one();
    resultReady.notify_one();
    requestThread.join();
    resultThread.join();
}

void LoginController::handleRequest(const QString& username, const QString& password)
{
    std::unique_lock<std::mutex> lock(requestMutex);
    requestQueue.push(std::make_pair(username, password));
    lock.unlock();
    requestReady.notify_one();
}

void LoginController::handleRequests() 
{
    while(!stopping) {
        std::unique_lock<std::mutex> lock(requestMutex);
        requestReady.wait(lock, [&]{ return !requestQueue.empty() || stopping; });
        if(stopping) return;
        auto request = requestQueue.front();
        requestQueue.pop();
        lock.unlock();

        authController->authenticate(request.first, request.second);
    }
}

void LoginController::handleResult(const bool& result) 
{
    std::unique_lock<std::mutex> lock(resultMutex);
    resultQueue.push(result);
    lock.unlock();
    resultReady.notify_one();
}

void LoginController::handleResults() 
{
    while(!stopping) {
        std::unique_lock<std::mutex> lock(resultMutex);
        resultReady.wait(lock, [&]{ return !resultQueue.empty() || stopping; });
        if(stopping) return;
        auto result = resultQueue.front();
        resultQueue.pop();
        lock.unlock();

        emit messageResult(result);
    }
}