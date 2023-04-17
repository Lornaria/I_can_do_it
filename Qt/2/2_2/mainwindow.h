#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_add_clicked();

    void on__delete_clicked();

    void on_checkBox_icons_stateChanged(int arg1);

    void on_pushButton_up_clicked();

    void on_pushButton_down_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
};
#endif // MAINWINDOW_H
