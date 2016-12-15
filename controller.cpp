#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
    qsrand(QDateTime::currentMSecsSinceEpoch());
    bot = new ILugBot(this);
    qDebug() << bot->botfather();
}
