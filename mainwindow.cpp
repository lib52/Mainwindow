#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include <QSplitter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(750,500);
    ui->stackedWidget->setCurrentIndex(0);
    QSqlQueryModel *factoryModel =  new QSqlQueryModel(this);
    factoryModel->setQuery("select name from factory");

    ui->sellFactoryComboBox->setModel(factoryModel);

    QSplitter *splitter = new QSplitter(ui->saleManagePage);
    splitter->resize(700,360);

    splitter->addWidget(ui->toolBox);
    splitter->addWidget(ui->dailyList);

    splitter->setStretchFactor(0,1);
    splitter->setStretchFactor(1,1);

    createMenuBar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMenuBar()
{
    manageMenu = menuBar()->addMenu(tr("Car Manage"));
    passwordMenu = menuBar()->addMenu(tr("Edit Password"));

    manageAction = new QAction(tr("Brand Msg"),this);
    chartAction = new QAction(tr("Sale Statistics"),this);
    quitAction = new QAction(tr("Quit"),this);

    manageMenu->addAction(manageAction);
    manageMenu->addAction(chartAction);
    manageMenu->addSeparator();
    manageMenu->addAction(quitAction);

    connect(manageAction,SIGNAL(triggered(bool)),this,SLOT(on_manageMenuItem_clicked()));
    connect(chartAction,SIGNAL(triggered(bool)),this,SLOT(on_chartMenuItem_clicked()));
    connect(quitAction,SIGNAL(triggered(bool)),this,SLOT(on_quitMenuItem_clicked()));
}

void MainWindow::on_manageMenuItem_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_chartMenuItem_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_quitMenuItem_clicked()
{
    this->close();
}

void MainWindow::on_sellFactoryComboBox_currentIndexChanged(const QString &arg1)
{
    if(arg1=="please select brand"){
        //on_sellCancelBtn_clicked();
    }
    else{
        ui->sellModelComboBox->setEnabled(true);

        QSqlQueryModel *model = new QSqlQueryModel(this);
        model->setQuery(QString("select name from brand where factory ='%1' ").arg(arg1));
        ui->sellModelComboBox->setModel(model);
        ui->sellCancelBtn->setEnabled(true);
    }
}
