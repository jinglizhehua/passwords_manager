#ifndef DIALOG_LOGIN_H
#define DIALOG_LOGIN_H

#include <QDialog>
#include "userdatas.h"

namespace Ui {
class Dialog_login;
}

class Dialog_login : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_login(UserDatas *user_p, QWidget *parent = nullptr);
    ~Dialog_login();

    void create_table();

private slots:
    void on_btn_login_login_clicked();

    void on_btn_login_reg_clicked();

private:
    Ui::Dialog_login *ui;
    UserDatas *user_p;
};

#endif // DIALOG_LOGIN_H
