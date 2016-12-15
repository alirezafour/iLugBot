#include <QCoreApplication>
#include <QDebug>
#include <QDateTime>
#include "controller.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qsrand(QDateTime::currentMSecsSinceEpoch());
    Controller ctr;

    return a.exec();
}
