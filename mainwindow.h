#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QMenu *manageMenu;
    QMenu *passwordMenu;

    QAction *manageAction;
    QAction *chartAction;
    QAction *quitAction;

private slots:
    void on_manageMenuItem_clicked();
    void on_chartMenuItem_clicked();
    void on_quitMenuItem_clicked();

    void on_sellFactoryComboBox_currentIndexChanged(const QString &arg1);

    void on_sellModelComboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    void createMenuBar();
};

#endif // MAINWINDOW_H
