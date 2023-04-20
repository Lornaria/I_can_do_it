#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include <QFileDialog>
//#include <QObject>


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


void MainWindow::on_pushButton_save_clicked()
{
    QString s = QFileDialog::getSaveFileName(this, "Save file", QDir::current().path(), tr("Text file (*.txt)"));
    if (s.length() > 0){
        int index = s.indexOf(".txt");
        QFile file(s);
        if (file.open(QFile::WriteOnly)){
            if (index != -1){
                QTextStream stream(&file);
                stream << ui->plainTextEdit->toPlainText();
            }
            file.close();
        }
    }
}


void MainWindow::on_pushButton_open_clicked()
{
    QString s = QFileDialog::getOpenFileName(this, "Заголовок окна",
    QDir::current().path(), tr("Text file (*.txt)"));
    if (s.length() > 0){
        int index = s.indexOf(".txt");
        QFile file(s);
        if (file.open(QFile::ReadOnly | QFile::ExistingOnly)){
            if (index != -1 && s.length() - 4 == index)
            {
                QTextStream stream(&file);
                ui->plainTextEdit->setPlainText(stream.readAll());
            }
            file.close();
        }
    }
}

