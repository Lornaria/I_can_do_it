#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>

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


void MainWindow::on_pushButton_clicked()
{
    double a = ui->lineEdit_a->text().toDouble();
    double b = ui->lineEdit_b->text().toDouble();
    double angle = ui->lineEdit_angle->text().toDouble();
    double result;
    if(ui->radioButton_radian->isChecked()) {
        result = a*a + b*b - (2 * a * b * qCos(angle));
        result = qSqrt(result);
    }
    else {
        angle = qDegreesToRadians(angle);
        result = a*a + b*b - (2 * a * b * qCos(angle));
        result = qSqrt(result);
    }
    ui->label_result->setText(QString::number(result));
}

