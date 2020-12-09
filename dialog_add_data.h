#ifndef DIALOG_ADD_DATA_H
#define DIALOG_ADD_DATA_H

#include <QDialog>
#include "userdatas.h"

namespace Ui {
class Dialog_add_data;
}

class Dialog_add_data : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_add_data(UserDatas *user_p, QWidget *parent = nullptr, bool change = false);
    ~Dialog_add_data();

private slots:
    void on_btn_add_ok_clicked();

    void on_btn_add_cancel_clicked();

private:
    Ui::Dialog_add_data *ui;
    UserDatas *user_p;

    bool is_change;
};

#endif // DIALOG_ADD_DATA_H
