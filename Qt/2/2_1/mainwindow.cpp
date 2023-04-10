#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "parsetext.h"

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


void MainWindow::on_plainTextEdit_textChanged()
{
    QString txt = ui->plainTextEdit->toPlainText();
    int pos = 0;
    while(1){
        int posStart = txt.indexOf("#@", pos);
        if(posStart == -1){
            return;
        }
        pos = posStart + 1;
        int posEnd = txt.indexOf("@", posStart + 2); //возможно будет тот же считываться
        int space = txt.indexOf(" ", posStart);
        if((posEnd < space || space == -1) && posEnd != -1){
            ParseText parseText(txt.mid(posStart + 2, posEnd - posStart - 2));
            QString answer = parseText.parse();
            txt.remove(posStart, posEnd - posStart + 1);
            txt.insert(posStart, answer);
            ui->plainTextEdit->setPlainText(txt);
            ui->plainTextEdit->moveCursor(QTextCursor::EndOfLine);
        }
    }
}

