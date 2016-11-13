#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include "connsql.h"
#include <QLabel>
#include <QMenu>
#include <QAction>
#include <QToolBar>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    int recordNum;
    Ui::MainWindow *ui;
    ConnSQL *conn;
    QSqlTableModel *tableAll;
    QLabel *msgLabel;
    QLabel *locationLabel;
    QLabel *recordSumLabel;
    QMenu *help;
    QMenu *file;
    QAction *aboutAction;
    QAction *explainAction;
    QAction *addRecordAction;
    QAction *aboutQtAction;
    void aboutQt();
    void createActions();
    void createMenus();
    void createToolsBar();
    void createStatusBar();
    void updateStatusBar();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_refBtn_clicked();
    void on_addBtn_clicked();
    void on_delBtn_clicked();
    void on_saveBtn_clicked();
    void on_pushButton_clicked();
    void about();
    void explain();
};

#endif // MAINWINDOW_H
