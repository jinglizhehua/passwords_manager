#include "dialog_login.h"
#include "ui_dialog_login.h"
#include "database.h"

#include <QMessageBox>
#include <QtDebug>

Dialog_login::Dialog_login(UserDatas *user_p, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_login)
{
    ui->setupUi(this);
    this->user_p = user_p;
    create_table();

    //setWindowFlags(Qt::FramelessWindowHint | windowFlags());    //去掉标题栏
    ui->lineEdit_username->setFocus();
}

Dialog_login::~Dialog_login()
{
    delete ui;
}

void Dialog_login::create_table()
{
    DataBase db(this, "user", "users.db");
    QSqlQuery query(db.getDataBase());
    QString sql = QString("CREATE table if not exists user(") +
                            "\"id\"        INTEGER NOT NULL UNIQUE,"        +
                            "\"name\"      TEXT NOT NULL UNIQUE,"           +
                            "\"password\"  TEXT NOT NULL,"                  +
                            "PRIMARY KEY(\"id\" AUTOINCREMENT))";
    if(!query.exec(sql))
    {
        qDebug() << query.lastError() << sql;
    }
}

void Dialog_login::on_btn_login_login_clicked()
{
    DataBase db(this, "user", "users.db");

    //查询数据
    QString pw = db.select_where("user", "password", "name", ui->lineEdit_username->text());
    if(pw.isNull())
    {
        QMessageBox::warning(this, "warning", "用户不存在！", QMessageBox::Yes);
        ui->lineEdit_username->clear();
        ui->lineEdit_password->clear();
        ui->lineEdit_username->setFocus();
    }
    else if(pw == ui->lineEdit_password->text())
    {
        *this->user_p = UserDatas(ui->lineEdit_username->text());
        accept();
    }
    else
    {
        QMessageBox::warning(this, "warning", "密码错误！", QMessageBox::Yes);
        ui->lineEdit_password->clear();
        ui->lineEdit_password->setFocus();
    }
}

void Dialog_login::on_btn_login_reg_clicked()
{
    DataBase db(this, "user", "users.db");
    QString pw = db.select_where("user", "password", "name", ui->lineEdit_username->text());
    if(pw.isNull())
    {
        QString s1 = ui->lineEdit_username->text();
        QString s2 = ui->lineEdit_password->text();
        if(!db.insert("user", new QString[2]{"name", "password"}, new QString[2]{s1, s2}, 2))
        {
            QMessageBox::warning(this, "warning", "数据库出错！", QMessageBox::Ok);
            return;
        }
        *this->user_p = UserDatas(ui->lineEdit_username->text());

        accept();
        QMessageBox::information(this, "提示", QString(ui->lineEdit_username->text()) + "用户已成功注册！", QMessageBox::Ok);
    }
    else
    {
        QMessageBox::warning(this, "warning", "用户已存在！", QMessageBox::Yes);
        ui->lineEdit_username->clear();
        ui->lineEdit_username->setFocus();
    }
}
