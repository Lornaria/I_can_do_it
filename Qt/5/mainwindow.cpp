#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include<QApplication>

#define RELEASE(p) if (p) {delete p; p = NULL;}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    l0 = new QLabel(this);
    bool rez = (l0 != NULL);
    l1 = new QLabel(this);
    rez &= (l1 != NULL);
    rusB = new QPushButton(this);
    rez &= (rusB != NULL);
    enB = new QPushButton(this);
    rez &= (enB != NULL);
    if (!rez) {
    qApp->quit();
    return;
    }
    l0->move(80, 550);
    l1->move(190, 550);
    rusB->move(80, 370);
    enB->move(80, 470);
    rusB->resize(200, 30);
    enB->resize(200, 30);
    switchLanguage(QLocale::system().name()); // устанавливаем язык системы
    connect(rusB, SIGNAL(clicked()), this, SLOT(clickSwitch()));
    connect(enB, SIGNAL(clicked()), this, SLOT(clickSwitch()));
}

MainWindow::~MainWindow()
{
    delete ui;
    RELEASE(l0);
    RELEASE(l1);
    RELEASE(rusB);
    RELEASE(enB);
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
    QString s = QFileDialog::getOpenFileName(this, "Open file", QDir::current().path(), tr("Text file (*.txt)"));
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


void MainWindow::on_pushButton_help_clicked()
{
    //:/help/help.txt
    QFile file(":/help/help.txt");
    file.open(QFile::ReadOnly);
    QTextStream stream(&file);
    QString str = stream.readAll();
    file.close();
    QMessageBox::information(this, "Help", str);
}

void MainWindow::switchLanguage(QString language)
{
    //translater.load("switchlang_" + language);
    translater.load(":/tr/QtLanguage_ru.qm");
    qApp->installTranslator(&translater);
    QString str = tr("Switch language on ");
    rusB->setText(str + "Русский");
    enB->setText(str + "English");
    QLabel *labels[] = {l0, l1};
    for (int i = 0; i < 2; i++){
        labels[i]->setText("This is l" + QString::number(i));
    }
}

void MainWindow::clickSwitch()
{
    QObject *obj = sender();
    if (obj == rusB)switchLanguage("ru");
    if (obj == enB)switchLanguage("en");
}
