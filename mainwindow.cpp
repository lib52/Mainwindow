#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include <QSplitter>
#include <QMessageBox>

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
        on_sellCancelBtn_clicked();

        ui->sellModelComboBox->setEnabled(true);


        ui->sellModelComboBox->clear();


    }
    else{
        ui->sellModelComboBox->setEnabled(true);

        QSqlQueryModel *model = new QSqlQueryModel(this);
        model->setQuery(QString("select name from brand where factory ='%1' ").arg(arg1));
        ui->sellModelComboBox->setModel(model);
        ui->sellCancelBtn->setEnabled(true);
    }
}

void MainWindow::on_sellModelComboBox_currentIndexChanged(const QString &arg1)
{
    ui->sellAmountSpinBox->setValue(0);
    ui->sellAmountSpinBox->setEnabled(false);

    ui->sellTotalLineEdit->clear();
    ui->sellTotalLineEdit->setEnabled(false);

    QSqlQuery query;
    query.exec(QString("select price,last from brand where name ='%1' and factory ='%2' ").
               arg(arg1).arg(ui->sellFactoryComboBox->currentText()));
    query.next();

    ui->sellPriceLineEdit->setEnabled(true);
    ui->sellPriceLineEdit->setReadOnly(true);
    ui->sellPriceLineEdit->setText(query.value(0).toString());

    int num = query.value(1).toInt();
    if(num==0){
        QMessageBox::information(this,tr("warning"),tr("all have been sold out"),QMessageBox::Ok);

    }
    else{
        ui->sellAmountSpinBox->setEnabled(true);
        ui->sellAmountSpinBox->setMaximum(num);
        ui->sellLastLabel->setText(tr("Remain:")+QString::number(num));
    }
}

void MainWindow::on_sellAmountSpinBox_valueChanged(int arg1)
{
    int max = ui->sellAmountSpinBox->maximum();


    ui->sellLastLabel->setText(tr("Remain:")+QString::number(max-arg1));

    int total = ui->sellPriceLineEdit->text().toInt()*arg1;
    ui->sellTotalLineEdit->setText(QString::number(total));
}

void MainWindow::on_sellCancelBtn_clicked()
{
    ui->sellFactoryComboBox->setCurrentIndex(0);
    ui->sellModelComboBox->clear();
    //ui->sellModelComboBox->clearEditText();
    //ui->sellModelComboBox->setModel(Q_NULLPTR);
    //ui->sellModelComboBox->setCurrentText("");
}

void MainWindow::on_sellOkBtn_clicked()
{
    int num = ui->sellAmountSpinBox->value();
    if(num==0) return;
    QString factory = ui->sellFactoryComboBox->currentText();
    QString model = ui->sellModelComboBox->currentText();

    int remain = ui->sellAmountSpinBox->maximum()-num;

    QSqlQuery query;
    query.exec(QString("select sell from brand where factory ='%1' and name ='%2' ").arg(factory).arg(model));
    query.next();

    int sell = query.value(0).toInt();
    sell = sell+ num;

    bool result=query.exec(
                QString("update brand set sell='%1' ,last ='%2' where name = '%3' and factory ='%4'")
               .arg(sell).arg(remain).arg(model).arg(factory)
               );
    query.next();

    if(result){
        QSqlDatabase::database().commit();
        QMessageBox::information(this,"warning","Buy car successfully!",QMessageBox::Ok);

        //
        //
        on_sellCancelBtn_clicked();
    }
    else
    {
        QSqlDatabase::database().rollback();
        QMessageBox::information(this,"error","Fail to buy car!",QMessageBox::Ok);
    }


}

//
