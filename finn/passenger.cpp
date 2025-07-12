#include "passenger.h"
#include<QDebug>
passenger::passenger()
{

}
void passenger::setpassenger(QString newid,QString newname,QString newpassword,QString newrank,QString newnickname)
{
    id=newid;
    name=newname;
    password=newpassword;
    rank=newrank;
    nickname=newnickname;
}
void passenger::show()
{
    qDebug()<<"id="<<id<<"name="<<name<<"password="<<password<<"rank="<<rank<<"nickname="<<nickname;
}
QString passenger::getid()
{
    return id;
}
QString passenger::getname()
{
    return name;
}
QString passenger::getpassword()
{
    return password;
}
QString passenger::getrank()
{
    return rank;
}
QString passenger::getnickname()
{
    return nickname;
}
