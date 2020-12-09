#include "database.h"

#include <QMessageBox>

DataBase::DataBase()
{
    ;
}

DataBase::DataBase(QWidget *parent, const QString &link, const QString &file)
{
    if(QSqlDatabase::contains(link))
        db = QSqlDatabase::database(link);
    else
        db = QSqlDatabase::addDatabase("QSQLITE", link);
    db.setDatabaseName(file);
    if(!db.open())
    {
        QMessageBox::warning(parent, "warning", "连接用户信息数据库失败！", QMessageBox::Yes);
        db = QSqlDatabase();
        return;
    }
    query = QSqlQuery(db);
}

DataBase::~DataBase()
{
    //qDebug() << "db over";
    if(db.isOpen())
        db.close();
    //query.finish();
}

QSqlDatabase& DataBase::getDataBase()
{
    return this->db;
}

void DataBase::close()
{
    if(db.isOpen())
        db.close();
    //query.finish();
}

bool DataBase::insert(QString table, QString cols[], QString values[], int length)
{
    QString sql = QString("insert into ") + table + " (";

    for(int i = 0; i < length; ++ i)
        sql += cols[i] + ",";
    sql = sql.left(sql.size() - 1);

    sql += ") values (";

    for(int i = 0; i < length; ++ i)
    {
        sql += QString("\"") + values[i] + "\",";
    }
    sql = sql.left(sql.size() - 1);
    sql += ")";

    if(!query.exec(sql))
    {

        qDebug() << query.lastError() << sql;
        return false;
    }
    return true;
}

bool DataBase::remove(QString table, QString where_col, QString where_value)
{
    where_value = QString("\"") + where_value + "\"";
    QString sql = QString("delete from ") + table + " where " + where_col + "=" + where_value;

    if(!query.exec(sql))
    {
        qDebug() << query.lastError() << sql;
        return false;
    }
    return true;
}

bool DataBase::remove(QString table, QString *where_cols, QString *where_values, int length)
{
    QString sql = QString("delete from ") + table + " where ";
    for(int i = 0; i < length; ++ i)
    {
        sql += where_cols[i] + "=\"" + where_values[i] + "\" and ";
    }
    sql = sql.left(sql.size() - 5);

    if(!query.exec(sql))
    {
        qDebug() << query.lastError() << sql;
        return false;
    }
    return true;
}

bool DataBase::update(QString table, QString col, QString value, QString where_col, QString where_value)
{
    value = QString("\"") + value + "\"";
    where_value = QString("\"") + where_value + "\"";
    QString sql = QString("update ") + table + " set " + col + "=" + value + " where " + where_col + "=" + where_value;
    query.exec(sql);
    if(!query.exec())
    {
        qDebug() << query.lastError() << sql;
        return false;
    }
    return true;
}

bool DataBase::update(QString table, QString *cols, QString *values, int length1, QString *where_cols, QString *where_values, int length2)
{
    QString sql = QString("update ") + table + " set ";
    for(int i = 0; i < length1; ++ i)
    {
        sql += cols[i] + "=\"" + values[i] + "\", ";
    }
    sql = sql.left(sql.size() - 2) + " where ";
    for(int i = 0; i < length2; ++ i)
    {
        sql += where_cols[i] + "=\"" + where_values[i] + "\" and ";
    }
    sql = sql.left(sql.size() - 5);

    if(!query.exec(sql))
    {
        qDebug() << query.lastError() << sql;
        return false;
    }
    return true;
}

/*
 * 返回query，用while(query.next) query.value()来读取数据
 * 默认cols为"*"，读取所有列
*/
QSqlQuery DataBase::select(QString table, QString cols[], int length)
{
    QString sql = "select ";
    for(int i = 0; i < length; ++ i)
    {
        sql += cols[i] + ",";
    }
    sql = sql.left(sql.size() - 1) + " from " + table;
    query.exec(sql);
    if(!query.exec())
    {
        qDebug() << query.lastError() << sql;
        return QSqlQuery();
    }
    return query;
}

QString DataBase::select_where(QString table, QString col, QString where_col, QString where_value)
{
    QString sql = "select " + col + " from " + table + " where " + where_col + "=\"" + where_value + "\"";
    query.exec(sql);
    if(!query.exec())
    {
        qDebug() << query.lastError() << sql;
        return QString();
    }
    if(query.next())
    {
        return query.value(0).toString();
    }
    else
    {
        return QString();
    }
}

