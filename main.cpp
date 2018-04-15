#include "devices.h"
#include <QApplication>
//TicTacToeAsds
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Devices w;
    w.show();

    return a.exec();
}
