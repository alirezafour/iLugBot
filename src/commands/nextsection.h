#ifndef NEXTSECTION_H
#define NEXTSECTION_H
#include "../command.h"


class NextSection : public Command
{
public:
    NextSection();

    virtual void Answer(const QJsonObject &obj, const QString &params);
};

#endif // NEXTSECTION_H
