#include "widget.h"
#include <QApplication>
//#include "analytics.h"
#include "firebase/analytics.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
