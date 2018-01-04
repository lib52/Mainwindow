#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
