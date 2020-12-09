#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog_login.h"
#include "dialog_change_password.h"
#include "dialog_add_data.h"
#include "database.h"

#include <QTableView>

MainWindow::MainWindow(UserDatas *user_p, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->user_p = user_p;
    change_user_flag = false;
    this->model = new QSqlQueryModel;

    ui->tableView_data->setSelectionBehavior(QAbstractItemView::SelectRows);    //一次选一行
    //ui->tableView_data->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自适应列宽
    ui->tableView_data->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);    //列宽适配内容
    ui->tableView_data->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->lineEdit_find->setClearButtonEnabled(true);


    query_init();
    creat_table();
    update_show_data();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::is_change_user()
{
    bool tmp = change_user_flag;
    change_user_flag = false;
    return tmp;
}

void MainWindow::on_action_change_password_triggered()
{
    Dialog_change_password dlg_change_pw(this->user_p, this);
    dlg_change_pw.exec();
}

void MainWindow::on_action_change_user_triggered()
{
    change_user_flag = true;
    this->close();
}

void MainWindow::on_btn_add_clicked()
{
    Dialog_add_data dlg_add_data(this->user_p, this);
    if(dlg_add_data.exec() == QDialog::Accepted)
    {
        update_show_data();
    }
}

void MainWindow::query_init()
{
    this->model->setHeaderData(0, Qt::Horizontal, "项目");
    this->model->setHeaderData(1, Qt::Horizontal, "账户");
    this->model->setHeaderData(2, Qt::Horizontal, "密码");
    this->model->setHeaderData(3, Qt::Horizontal, "备注");
}

void MainWindow::creat_table()
{
    DataBase db(this, "data", "data.db");
    QSqlQuery query(db.getDataBase());
    QString sql = QString("CREATE table if not exists " + user_p->GetName() + "(") +
                            "\"id\"      INTEGER NOT NULL UNIQUE,"          +
                            "\"item\"     TEXT NOT NULL,"                   +
                            "\"account\"  TEXT NOT NULL,"                   +
                            "\"password\" TEXT NOT NULL,"                   +
                            "\"note\"     INTEGER,"                         +
                            "PRIMARY KEY(\"id\" AUTOINCREMENT))";
    if(!query.exec(sql))
    {
        qDebug() << query.lastError() << sql;
    }
}

void MainWindow::update_show_data()
{
    DataBase db(this, "data", "data.db");
    model->setQuery("select item,account,password,note from " + user_p->GetName(), db.getDataBase());
    this->query_init();
    ui->tableView_data->setModel(model);
    ui->tableView_data->show();
}

void MainWindow::on_action_exit_triggered()
{
    close();
}

void MainWindow::on_btn_delete_clicked()
{
    QItemSelectionModel *model_selection = ui->tableView_data->selectionModel();
    QModelIndexList indexList = model_selection->selectedIndexes();

    DataBase db(this, "data", "data.db");
    QString values[4];
    for(int i = 0; i < indexList.size(); i += 4)
    {
        int row = indexList[i].row();
        for(int j = 0; j < 4; ++ j)
        {
            values[j] = this->model->data(model->index(row, j)).toString();
        }
        db.remove(this->user_p->GetName(), new QString[4]{"item", "account", "password", "note"}, values, 4);
    }
    update_show_data();
}

void MainWindow::on_btn_change_clicked()
{
    int row = ui->tableView_data->currentIndex().row();
    if(row < 0)
    {
        QMessageBox::warning(this, "warning", "未选中项目！", QMessageBox::Ok);
        return;
    }
    QVector<QString> buff;
    for(int i = 0; i < 4; ++ i)
    {
        QString tmp = this->model->data(model->index(row, i)).toString();
        buff.append(tmp);
    }
    this->user_p->set_data_buff(buff);

    Dialog_add_data dlg_add_data(this->user_p, this, true);
    if(dlg_add_data.exec() == QDialog::Accepted)
    {
        update_show_data();
    }
}

void MainWindow::on_lineEdit_find_textEdited(const QString &arg1)
{
    //qDebug() << arg1;
    if(arg1 == "")
    {
        update_show_data();
        return;
    }

    DataBase db(this, "data", "data.db");
    QString sql = "select item,account,password,note from " + user_p->GetName()
            + " where item like '%" + arg1 + "%' or note like '%" + arg1 + "%'";
    //qDebug() << sql;
    model->setQuery(sql, db.getDataBase());
    ui->tableView_data->setModel(model);
    ui->tableView_data->show();
}
