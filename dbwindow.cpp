#include "dbwindow.h"
#include "ui_dbwindow.h"

DBWindow::DBWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DBWindow)
{

    ui->setupUi(this);
    SetLabelConnectionStatus();
    this->dbConnection =new DBConnection();
}

DBWindow::~DBWindow()
{
    delete dbConnection;
    delete ui;
}

void DBWindow::SetLabelConnectionStatus()
{
 ui->lblConnectionStatus->text() = this->dbConnection == nullptr ? "Database not Connected" : "Database Connected";
}
void DBWindow::on_connectBtn_clicked()
{
    bool valid = true;
    if(ui->txtStringConnection->text() == "")
    {
        if(ui->txtServerName->text()!="")
        this->dbConnection->SetServerName(ui->txtServerName->text());
        else
        {
            valid=false;
            QMessageBox::information(this,"Check the field","Server name is empty");
            ui->txtServerName->focusWidget();
        }

        if(ui->txtDBName->text()!="")
            this->dbConnection->SetDataBaseName(ui->txtDBName->text());
        else
        {
            valid=false;
             QMessageBox::information(this,"Check the field","Database name is empty");
             ui->txtDBName->focusWidget();
        }
    }
    else
    {
        dbConnection->SetConnectionString(ui->txtStringConnection->text());
    }

    if(valid)
    {
        if(ui->txtDBName->text() != "" && this->ui->txtServerName->text() != "")
        {
            this->dbConnection->SetServerName(ui->txtServerName->text());
            this->dbConnection->SetDataBaseName(ui->txtDBName->text());

            if(this->dbConnection->EnsureDBCreated())
            {
                SetLabelConnectionStatus();
            }
        }
        else if(this->dbConnection->GetDatabaseName() == "")
        {
            QMessageBox::information(this,"check the field","Database name is empty");
            ui->txtDBName->focusWidget();
        }
        else if(dbConnection->GetServerName() =="")
        {
            ui->txtServerName->focusWidget();
            QMessageBox::information(this,"Check the field","Server name is empty");
        }
    }

}
