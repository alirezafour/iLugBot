#include "ilugbot.h"

#include "src/commands/nextsection.h"


ILugBot::ILugBot(QObject *parent) : QObject(parent), last_update_id(0)
{

  Command::bot_ref = this;
  this->key = QString("304847086:AAG78MmOvNjQSJ_xUO40P-ida0-cDTkiECc");
  this->bot_name = QString("@myTelegramTesterBot");
  this->kCommandFormat = QRegularExpression("^/(\\w+)(?:"+bot_name+")?(?:\\s+(.*))?$");

  QTimer *timer = new QTimer(this);
  timer->start(1000);

  QObject::connect(timer,SIGNAL(timeout()),this,SLOT(Request()));

  //add your command classes to the Vector
  //commands.push_back(new TestCommand());

  commands.push_back(new NextSection());

}

ILugBot::~ILugBot() {
  for(int i=0;i<commands.length();i++){
    delete commands[i];
  }
}

void ILugBot::AnswerMessage(const QJsonObject &obj) {
  QJsonObject message = obj["message"].toObject();
  QString text = message["text"].toString();
  QRegularExpressionMatch match = kCommandFormat.match(text);
  QString command = match.captured(1).trimmed();
  QString params = match.captured(2).trimmed();
  if(command == "help"){
    qDebug() << tr("Sending help") << help();
    SendMessage(help(),message,false);
    return;
//  }else if(command == "botfather"){
//    SendMessage(botfather(),message);
//    return;
  }
  foreach(Command * c, commands){
    if(c->isCommand(command)){
      c->Answer(obj,params);
      return;
    }
  }
}

void ILugBot::SendMessage(const QString &msg_text, const QJsonObject &msg_struct,bool html)
{
  QString req = "https://api.telegram.org/bot"+key+"/sendMessage?chat_id="
      + QString::number(msg_struct["chat"].toObject()["id"].toInt())
      + "&text=" + msg_text + "&reply_to_message_id="
      + QString::number(msg_struct["message_id"].toInt())+"&parse_mode="+(html?"HTML":"Markdown");
  //qDebug() << req;
  request.setUrl(QUrl(req));
  QNetworkReply * reply = manager.get(request);
  QObject::connect(reply,SIGNAL(finished()),this,SLOT(HandleOut()));
}

QString ILugBot::botfather()
{
  QString botfather = tr("help - این کامند ها قابل استفاده است.\n");
  foreach(Command *c, commands){
    botfather += c->BotFather()+"\n";
  }
  return botfather;
}

QString ILugBot::help()
{
  QString helpString = tr("*دستورات:*\n");
  foreach(Command * c, commands){
    helpString += "• "+c->Help()+"\n";
  }
  return helpString;
}

void ILugBot::Request() {
  QString reqUrl = "https://api.telegram.org/bot"+key+"/getUpdates?offset=" + QString::number(last_update_id);
  //qDebug() << req;
  request.setUrl(QUrl(reqUrl));
  QNetworkReply * reply = manager.get(request);
  QObject::connect(reply,SIGNAL(finished()),this,SLOT(HandleIn()));
}

void ILugBot::HandleIn() {
  QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());
  QJsonObject json = QJsonDocument::fromJson(reply->readAll()).object();
  if(json["ok"].toBool()){
    qsrand(QDateTime::currentMSecsSinceEpoch());
    QJsonArray result = json["result"].toArray();
    foreach(QJsonValue value, result){
      QJsonObject obj = value.toObject();
      int update_id = obj["update_id"].toInt();
      //qDebug() << value << last_update_id << update_id;
      if(last_update_id <= update_id){
        //qDebug() << "answering";
        AnswerMessage(obj);
      }
      last_update_id = qMax(last_update_id,update_id+1);
    }
  }
  delete reply;
}

void ILugBot::HandleOut()
{
  QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());
  delete reply;
}
