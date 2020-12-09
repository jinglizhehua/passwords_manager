#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qpushbutton.h>
#include "userdatas.h"
#include "database.h"
#include <QSqlQueryModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(UserDatas *user_p, QWidget *parent = nullptr);
    ~MainWindow();
    bool is_change_user();

private slots:
    void on_action_change_password_triggered();

    void on_action_change_user_triggered();

    void on_btn_add_clicked();

    void on_action_exit_triggered();

    void on_btn_delete_clicked();

    void on_btn_change_clicked();

    void on_lineEdit_find_textEdited(const QString &arg1);

private:
    void query_init();
    void creat_table();
    void update_show_data();
private:
    Ui::MainWindow *ui;
    UserDatas *user_p;
    bool change_user_flag;
    QSqlQueryModel *model;
};
#endif // MAINWINDOW_H
