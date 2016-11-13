#include "mainwindow.h"
#include "qdelegate.h"
#include "ui_mainwindow.h"
#include <QtSql>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainLayout->setStretchFactor(ui->leftLayout, 5);
    ui->mainLayout->setStretchFactor(ui->rightLayout, 1);

    //建立数据库连接
    conn = new ConnSQL(QString::fromStdString("localhost"),
                       QString::fromStdString("dbsql"),
                       QString::fromStdString("dbsql"),
                       QString::fromStdString("dbsql"));

    //建立主窗口表格
    tableAll = new QSqlTableModel(this, QSqlDatabase::database("QMYSQL"));
    tableAll->setTable("Student");

    //不开启手动Submit将不能批量添加记录
    tableAll->setEditStrategy(QSqlTableModel::OnManualSubmit);


    //设置表头，默认为数据表属性列名
    tableAll->setHeaderData(0, Qt::Horizontal, "学号");
    tableAll->setHeaderData(1, Qt::Horizontal, "姓名");
    tableAll->setHeaderData(2, Qt::Horizontal, "性别");
    tableAll->setHeaderData(3, Qt::Horizontal, "年龄");
    tableAll->setHeaderData(4, Qt::Horizontal, "所属系");

    tableAll->select();

    createActions();
    createMenus();
    createToolsBar();
    createStatusBar();

    //限制对性别属性的值
    QDelegate *sex_dt = new QDelegate(this);
    sex_dt->SetDeleteType("QComboBox");
    sex_dt->SetDeleteValue(QStringList()<<QObject::tr("男").toLocal8Bit()
                           <<QString::fromLocal8Bit("女"));
    ui->tableView->setItemDelegateForColumn(2, sex_dt);

    ui->tableView->setModel(tableAll);

    //实现选择行而不是单元格
    //限制只能单行选择
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);



    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
}

MainWindow::~MainWindow()
{
    //删除ui及其子窗口部件
    delete ui;
}

void MainWindow::createActions() {
    //添加记录
    addRecordAction = new QAction(tr("添加"), this);
    addRecordAction->setStatusTip(tr("支持批量添加新记录"));
    connect(addRecordAction, SIGNAL(triggered()), this, SLOT(on_addBtn_clicked()));
    //关于
    aboutAction = new QAction(QIcon(":/images/about.png"), tr("&关于"), this);
    aboutAction->setStatusTip(tr("About me"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
    //关于Qt
    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    //使用说明
    explainAction = new QAction(QIcon(":/images/help.png"),tr("&使用说明"), this);
    explainAction->setStatusTip(tr("使用说明"));
    connect(explainAction, SIGNAL(triggered()), this, SLOT(explain()));

}

void MainWindow::createMenus() {    //控制菜单栏项
    file = menuBar()->addMenu(tr("&文件"));
    file->addAction(addRecordAction);

    help = menuBar()->addMenu(tr("&帮助"));
    help->addAction(explainAction);
    help->addAction(aboutAction);
    help->addAction(aboutQtAction);

}

void MainWindow::createToolsBar() {    //控制工具栏项
    ui->mainToolBar->addAction(explainAction);
    ui->mainToolBar->addAction(aboutAction);
}

void MainWindow::createStatusBar() {
    recordSumLabel = new QLabel;
    recordSumLabel->setText("共"
                            +QString::number(tableAll->rowCount())
                            +"条记录");

//    locationLabel = new QLabel(QString::number(ui->tableView->currentIndex().row()));

//    statusBar()->addWidget(locationLabel);
//    statusBar()->addWidget(recordSumLabel, 1);
    statusBar()->addWidget(recordSumLabel);
}


void MainWindow::updateStatusBar() {    //更新状态栏
    recordSumLabel->setText("共 "
                            +QString::number(tableAll->rowCount())
                            +" 条记录");
}

void MainWindow::on_refBtn_clicked()
{
    updateStatusBar();
    tableAll->select();
}

void MainWindow::on_addBtn_clicked()
{
    int rowNum = tableAll->rowCount();
    qDebug()<<tableAll->rowCount();
    tableAll->insertRow(rowNum);
    ui->tableView->setCurrentIndex(tableAll->index(tableAll->rowCount() - 1, 0));
    qDebug()<<tableAll->rowCount();

}

void MainWindow::on_delBtn_clicked()
{
    int curRow = ui->tableView->currentIndex().row();
    tableAll->removeRow(curRow);
    tableAll->submitAll();

    ui->tableView->setCurrentIndex(tableAll->index(tableAll->rowCount()-1, 0));
    updateStatusBar();
    tableAll->select();

}

void MainWindow::on_saveBtn_clicked()
{
    tableAll->database().transaction();
    if (tableAll->submitAll()) {
        tableAll->database().commit();
    } else {
        tableAll->database().rollback();
    }
    updateStatusBar();

}

void MainWindow::on_pushButton_clicked()
{
    updateStatusBar();
    tableAll->revertAll();
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About"),
                tr("<h2>第三次数据库实验</h2>"
                   "<p>作者：卢洪利</p>"
                   "<p>基于Qt/C++，你可以使用这部分代码而不需经过我的允许</p>"));
}

void MainWindow::explain()
{
    QMessageBox::about(this, tr("使用说明"),
                       tr("<ul>"
                          "<li>可以批量添加记录，点击保存后生效</li>"
                          "<li>可以撤销还没有保存的新增记录</li>"
                          "<li>小心删除，删除立即生效，不可恢复</li>"
                          "</ul>"));
}
