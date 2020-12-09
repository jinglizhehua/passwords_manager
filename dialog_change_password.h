#ifndef DIALOG_CHANGE_PASSWORD_H
#define DIALOG_CHANGE_PASSWORD_H

#include <QDialog>
#include "userdatas.h"

namespace Ui {
class Dialog_change_password;
}

class Dialog_change_password : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_change_password(UserDatas *user_p, QWidget *parent = nullptr);
    ~Dialog_change_password();

private slots:
    void on_btn_change_pw_ok_clicked();

private:
    Ui::Dialog_change_password *ui;
    UserDatas *user_p;
};

#endif // DIALOG_CHANGE_PASSWORD_H
