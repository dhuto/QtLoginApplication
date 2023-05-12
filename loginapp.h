#pragma once

#include <QApplication>
#include <QObject>
#include <memory>

class LoginApp : public QApplication
{
    Q_OBJECT
public:
    LoginApp(int &argc, char **argv);

    int Run();
};
