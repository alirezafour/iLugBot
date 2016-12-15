#ifndef ILUGBOT_H
#define ILUGBOT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVector>
#include <QRegularExpression>

#include "src/command.h"

class ILugBot : public QObject
{
  Q_OBJECT
public:
  explicit ILugBot(QObject *parent = 0);
  virtual ~ILugBot();



  QString botfather();
  QString help();

  void SendMessage(const QString &msg_text, const QJsonObject &msg_struct, bool html=true);

private:
  int last_update_id;
  QNetworkRequest request;
  QNetworkAccessManager manager;
  QString key;// = "304847086:AAG78MmOvNjQSJ_xUO40P-ida0-cDTkiECc";
  QString bot_name;// = "@myTelegramTesterBot";
  QRegularExpression kCommandFormat;//QRegularExpression("^/(\\w+)(?:"+bot_name+")?(?:\\s+(.*))?$");

  QVector<Command*> commands;

  void AnswerMessage(const QJsonObject &obj);

private slots:
  void Request();
  void HandleIn();
  void HandleOut();
};

#endif // ILUGBOT_H
