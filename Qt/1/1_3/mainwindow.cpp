#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_add_clicked()
{
    QString text = ui->textEdit_1->toPlainText();
    ui->textEdit_2->insertPlainText(text);
}


void MainWindow::on_pushButton_replace_clicked()
{
    QString text = ui->textEdit_1->toPlainText();
    ui->textEdit_2->setPlainText(text);
}


void MainWindow::on_pushButton_insert_clicked()
{
    ui->textEdit_2->setHtml("<font color='green'>Hello</font>");
}

