#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dbwindow.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class DBWindow;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

void on_actionOpen_SQL_Connection_triggered();

private:
    Ui::MainWindow *ui;
    DBWindow* dbWindow =nullptr;
};
#endif // MAINWINDOW_H
