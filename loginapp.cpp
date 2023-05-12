#include "loginapp.h"

#include "authenticationcontroller.h"
#include "loginview.h"
#include "logincontroller.h"

#include <QLocale>
#include <QTranslator>

LoginApp::LoginApp(int &argc, char **argv)
: QApplication(argc, argv)
{
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "LoginAdvancedApp_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            installTranslator(&translator);
            break;
        }
    }
}

int LoginApp::Run() {
    srand(time(nullptr));

    AuthenticationController authController;
    LoginView view;
    LoginController controller(&view, &authController);

    controller.start();

    view.show();

    const int result = exec();

    controller.stop();

    return result;
}

