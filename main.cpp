#include "mainwindow.h"
#include "dialog_login.h"
#include "database.h"
#include "userdatas.h"

#include <QApplication>
#include <QDialog>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UserDatas currentuser;

    while(true)
    {
        Dialog_login dlg_login(&currentuser);
        if(dlg_login.exec() == QDialog::Accepted)
        {
            MainWindow w(&currentuser);
            w.show();
            a.exec();
            if(!w.is_change_user())
                break;
        }
        else
            break;
    }
    return 0;
}
