#include "userdatas.h"

#include <QDebug>

UserDatas::UserDatas()
{
    ;
}

UserDatas::UserDatas(const QString &name)
{
    this->name = name;
}

QString& UserDatas::GetName()
{
    return this->name;
}

void UserDatas::SetName(const QString &name)
{
    this->name = name;
}

void UserDatas::printName()
{
    qDebug() << this->name;
}

QVector<QString> UserDatas::get_data_buff()
{
    return this->data_buff;
}

void UserDatas::set_data_buff(QVector<QString> buff)
{
    this->data_buff = buff;
}

