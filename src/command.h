#ifndef COMMAND_H
#define COMMAND_H

#include <QJsonObject>
#include <QObject>

class ILugBot;

class Command:public QObject
{
  Q_OBJECT
public:
  Command(const QString &command_name, QObject *parent=0);

  QString command_name;
  QString command_description;
  QString command_params;
  QString used_command;
  QStringList alias_commands;

  static ILugBot * bot_ref;

  virtual bool isCommand(const QString &msg);
  virtual bool isAliasCommand(const QString &msg);
  virtual void Answer(const QJsonObject &obj, const QString &params)=0;
  void SendMessage(const QJsonObject &obj,const QString &msg_text);
  QString Help();
  QString BotFather();
};

#endif // COMMAND_H
