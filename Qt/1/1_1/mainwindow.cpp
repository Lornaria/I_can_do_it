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


void MainWindow::on_pushButton_findRoots_clicked()
{
    double a = ui->lineEdit_a->text().toDouble();
    double b = ui->lineEdit_b->text().toDouble();
    double c = ui->lineEdit_c->text().toDouble();
    double x1, x2, d;
    QString result;

    if(a == 0.0){
        x1 = -(c/b);
        result = "x=" + QString::number(x1);
        ui->label_result->setText(result);
        return;
    }

    d = b * b - 4 * a * c;
    if(d > 0){
        x1 = (-b - qSqrt(d))/(2 * a);
        x2 = (-b + qSqrt(d))/(2 * a);
        result = "x1=" + QString::number(x1) + ", x2=" + QString::number(x2);
        ui->label_result->setText(result);
    }
    else if(d == 0.0){
        x1= (-b/(2*a));
        result = "X=" + QString::number(x1);
        ui->label_result->setText(result);
    }
    else{
        ui->label_result->setText("Нет корней");
    }

}

