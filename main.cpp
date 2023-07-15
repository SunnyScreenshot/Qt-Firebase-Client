#include "widget.h"
#include <string>
#include <QApplication>
#include "firebase/analytics.h" // 运行失败，则先链接 analytics，再链接 app
#include "firebase/app.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if 0
    firebase::AppOptions options;
    options.set_api_key("AIzaSyBgfOVnwyrG6-Ull9Wotf1ptKi6a6BHF3A");
    options.set_app_id("1:401172726150:web:ef53f936e6b5ff6ebfec07");
    options.set_project_id("qt-test-4cf7b");
//    options.set_messaging_sender_id("012345678901");

    firebase::App* app = firebase::App::Create(options);  // exe crashed.
//    firebase::analytics::Initialize(app);
#else

    // ERROR: Unable to load Firebase app options ([google-services-desktop.json, google-services.json] are missing or malforme -> root: GoogleService-Info.plist
    firebase::App* app = firebase::App::Create();
#endif

    Widget w;
    w.show();

    return a.exec();
}
