#include "devicesframe.h"
#include "serverui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*Devices w;
    w.show();*/
    ServerUI ui;
    ui.show();
    static int a_ret= a.exec();
    qDebug() << "a_ret" << a_ret;

    delete ui.bl1;
    delete ui.bl2;
    return a_ret;
}
