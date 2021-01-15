#ifndef DBWINDOW_H
#define DBWINDOW_H


#include <QMessageBox>
#include <QMainWindow>
#include "DBConnection.h"
#include <QPushButton>

namespace Ui {
class DBWindow;
}

class DBWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit DBWindow(QWidget *parent = nullptr);
    ~DBWindow();
   void SetLabelConnectionStatus();
private slots:

    void on_connectBtn_clicked();

private:

    DBConnection* dbConnection;
    Ui::DBWindow *ui;
};

#endif // DBWINDOW_H
