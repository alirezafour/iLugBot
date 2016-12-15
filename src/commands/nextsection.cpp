#include "nextsection.h"

NextSection::NextSection() : Command ("NextSection")
{
    command_description = QString(tr("این کامند جلسه بعدی لاگ را نمایش میدهد"));

}

void NextSection::Answer(const QJsonObject &obj, const QString &params)
{
    QString msg = tr("");

    //TODO: Fix me
    //write what this command wants to do

    SendMessage(obj,msg);
}
