#include "dialog_change_password.h"
#include "ui_dialog_change_password.h"
#include "database.h"

#include <QtDebug>

Dialog_change_password::Dialog_change_password(UserDatas *user_p, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_change_password)
{
    ui->setupUi(this);
    this->user_p = user_p;
}

Dialog_change_password::~Dialog_change_password()
{
    delete ui;
}

void Dialog_change_password::on_btn_change_pw_ok_clicked()
{
    QString s1, s2;
    s1 = ui->lineEdit_new_pw->text();
    s2 = ui->lineEdit_confirm_pw->text();
    if(s1 != s2)
    {
        QMessageBox::warning(this, "warning", "两次密码输入不一致！", QMessageBox::Ok);
        ui->lineEdit_new_pw->clear();
        ui->lineEdit_confirm_pw->clear();
        ui->lineEdit_new_pw->setFocus();
    }
    else if(s1.trimmed() == QString(""))
    {
        QMessageBox::warning(this, "warning", "密码不能为空！", QMessageBox::Ok);
        ui->lineEdit_new_pw->clear();
        ui->lineEdit_confirm_pw->clear();
        ui->lineEdit_new_pw->setFocus();
    }
    else
    {
        DataBase db(this, "user", "users.db");
        if(db.update("user", "password", s1, "name", this->user_p->GetName()))
        {
            QMessageBox::information(nullptr, "提示", QString("用户") + this->user_p->GetName() + "密码修改成功！", QMessageBox::Ok);
            accept();
        }
    }

}
