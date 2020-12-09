#ifndef USERDATAS_H
#define USERDATAS_H

#include <QString>
#include <QVector>

class UserDatas
{
public:
    UserDatas();
    UserDatas(const QString &name);
    QString& GetName();
    void SetName(const QString &name);
    void printName();

    QVector<QString> get_data_buff();
    void set_data_buff(QVector<QString> buff);
private:
    QString name;
    QVector<QString> data_buff;
};

#endif // USERDATAS_H
