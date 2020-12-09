#include "dialog_add_data.h"
#include "ui_dialog_add_data.h"
#include "database.h"

#include <QMessageBox>

Dialog_add_data::Dialog_add_data(UserDatas *user_p, QWidget *parent, bool change) :
    QDialog(parent),
    ui(new Ui::Dialog_add_data)
{
    ui->setupUi(this);
    this->user_p = user_p;
    this->is_change = change;

    QVector<QString> buff = this->user_p->get_data_buff();
    if(change)
    {
        ui->lineEdit_item->setText(buff[0]);
        ui->lineEdit_account->setText(buff[1]);
        ui->lineEdit_password->setText(buff[2]);
        ui->lineEdit_note->setText(buff[3]);
    }
}

Dialog_add_data::~Dialog_add_data()
{
    delete ui;
}

void Dialog_add_data::on_btn_add_ok_clicked()
{
    QString item, account, password, note;
    item     = ui->lineEdit_item->text();
    account  = ui->lineEdit_account->text();
    password = ui->lineEdit_password->text();
    note     = ui->lineEdit_note->text();
    if(item.trimmed() == QString(""))
    {
        QMessageBox::warning(this, "warning", "项目不能为空！", QMessageBox::Ok);
        return;
    }
    if(account.trimmed() == QString(""))
    {
        QMessageBox::warning(this, "warning", "账号不能为空！", QMessageBox::Ok);
        return;
    }
    if(password.trimmed() == QString(""))
    {
        QMessageBox::warning(this, "warning", "密码不能为空！", QMessageBox::Ok);
        return;
    }

    DataBase db(this, "data", "data.db");
    if(!this->is_change)
    {
        db.insert(this->user_p->GetName(), new QString[4]{"item", "account", "password", "note"},
                                           new QString[4]{item, account, password, note}, 4);
    }
    else
    {
        QVector<QString> buff = this->user_p->get_data_buff();
        db.update(this->user_p->GetName(), new QString[4]{"item", "account", "password", "note"},
                                           new QString[4]{item, account, password, note}, 4,
                                           new QString[4]{"item", "account", "password", "note"},
                                           new QString[4]{buff[0], buff[1], buff[2], buff[3]}, 4);
    }
    accept();
}

void Dialog_add_data::on_btn_add_cancel_clicked()
{
    close();
}
