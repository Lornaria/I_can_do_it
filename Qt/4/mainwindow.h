#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>
#include <QLabel>
#include <QPushButton>

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
    void on_pushButton_save_clicked();

    void on_pushButton_open_clicked();

    void on_pushButton_help_clicked();

//    void clickSwitch();

private:
    Ui::MainWindow *ui;

//    QPushButton *rusB, *enB;
//    QTranslator translater;

//    void switchLanguage(QString language);

};
#endif // MAINWINDOW_H
