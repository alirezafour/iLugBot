#include "command.h"

#include "ilugbot.h"

ILugBot * Command::bot_ref = nullptr;

Command::Command(const QString &command_name, QObject *parent)
  : QObject(parent),
    command_name(command_name)
{}

bool Command::isCommand(const QString &msg)
{
  QString m = msg.toLower();
  if(m==command_name){
    used_command = command_name;
    return true;
  }
  foreach(QString ac, alias_commands){
    if(m==ac){
      used_command = ac;
      return true;
    }
  }
  return false;
}

bool Command::isAliasCommand(const QString &msg)
{


  return false;
}

void Command::SendMessage(const QJsonObject &obj, const QString &msg_text)
{
  if(bot_ref!=nullptr){
    bot_ref->SendMessage(msg_text,obj["message"].toObject());
  }
}

QString Command::Help()
{
  return QString("/%1 _%3_ \t\t `%2`").arg(command_name,command_description,command_params);
}

QString Command::BotFather()
{
  return command_name+" - "+command_description;
}
