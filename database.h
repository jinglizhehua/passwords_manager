#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QString>
#include <QtDebug>

class DataBase
{
public:
    DataBase();
    DataBase(QWidget *parent, const QString &link, const QString &file);
    ~DataBase();
    QSqlDatabase& getDataBase();
    void close();

public:
    bool insert(QString table, QString cols[], QString values[], int length);
    bool remove(QString table, QString where_col, QString where_value);
    bool remove(QString table, QString where_cols[], QString where_values[], int length);
    bool update(QString table, QString col, QString value, QString where_col, QString where_value);
    bool update(QString table, QString cols[], QString values[], int length1, QString where_cols[], QString where_values[], int length2);
    QSqlQuery select(QString table, QString cols[] = new QString[1]{"*"}, int length = 1);
    QString select_where(QString table, QString col, QString where_col, QString where_value);

private:
    QSqlDatabase db;
    QSqlQuery query;
};

bool creatConection(const QString &link, const QString &db_file);
void closeConection(const QString &link);

#endif // DATABASE_H
