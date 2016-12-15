#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QDateTime>
#include "src/ilugbot.h"


class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);

signals:

public slots:

private:
    ILugBot *bot;

};

#endif // CONTROLLER_H
