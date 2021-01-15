#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DBConnection.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_actionOpen_SQL_Connection_triggered()
{

    if(dbWindow == nullptr)
    {
        dbWindow =  new DBWindow();
        this->dbWindow->show();
    }
    else
    {
        dbWindow->show();
    }
}
