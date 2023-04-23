#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include <QFileDialog>
#include <QRegularExpression>

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


void MainWindow::on_pushButton_open_clicked()
{
    QString html;
    QString s = QFileDialog::getOpenFileName(this, "Open file", QDir::current().path(), tr("Html file (*.html *.htm)"));
    if (s.length() > 0){
        QFile file(s);
        if (file.open(QFile::ReadOnly | QFile::ExistingOnly)){
            QTextStream stream(&file);
            html = stream.readAll();
            file.close();
        }
    }
    if(html.isEmpty()){
        ui->lineEdit_t->clear();
        ui->lineEdit_usd->clear();
        ui->lineEdit_euro->clear();
        return;
    }

    QStringList data = getData(html);
    ui->lineEdit_t->setText(data[0]);
    ui->lineEdit_usd->setText(data[1]);
    ui->lineEdit_euro->setText(data[2]);
}

QStringList MainWindow::getData(const QString& html){
    QStringList list;
    QRegularExpression regex(R"(("temp":")(.+)(","tempFeelsLike"))");
    QRegularExpressionMatch match = regex.match(html);
    if (match.hasMatch()) {
        list.append(match.captured(2));
    }
    regex.setPattern(R"(("type":"USD","rate":)(\d+.\d+)(,"sign":))");
    match = regex.match(html);
    if (match.hasMatch()) {
        list.append(match.captured(2));
    }
    regex.setPattern(R"(("type":"EUR","rate":)(\d+.\d+)(,"sign":))");
    match = regex.match(html);
    if (match.hasMatch()) {
        list.append(match.captured(2));
    }
    return list;
}
