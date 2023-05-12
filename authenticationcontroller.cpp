#include "authenticationcontroller.h"

void AuthenticationController::authenticate(const QString& username, const QString& password)
{
    // Simulate authentication by sleeping between 2 - 5 seconds
    std::this_thread::sleep_for(std::chrono::seconds((rand() % 5) + 1));

    // Generate a random authentication result
    bool result = (rand() % 2) == 0;

    // Add result to the result queue
    std::unique_lock<std::mutex> lock(resultMutex);
    resultQueue.push(result);
    lock.unlock();
    emit authenticationResult(result);
    resultReady.notify_one();
}
