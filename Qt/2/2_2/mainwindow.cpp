#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QStringList list = {"C++", "Python", "Java", "C#", "PHP", "JavaScript"};
    model = new QStandardItemModel(list.size(), 1, this);
    for (int i = 0; i < model->rowCount(); ++i) {
        QModelIndex index = model->index(i, 0);
        QString str = list[i];
        model->setData(index, str, Qt::DisplayRole);
        model->setData(index, QIcon(QDir::toNativeSeparators(QApplication::applicationDirPath()) + "/Icons/" + str + ".png"), Qt::DecorationRole);
    }

    ui->listView->setModel(model);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_add_clicked()
{
    model->appendRow(new QStandardItem(QIcon(QDir::toNativeSeparators(QApplication::applicationDirPath()) + "/Icons/default.png"),"NoName"));
}


void MainWindow::on__delete_clicked()
{
    int row = ui->listView->currentIndex().row();
    model->removeRow(row);
}


void MainWindow::on_checkBox_icons_stateChanged(int arg1)
{
    if(ui->checkBox_icons->isChecked()){
        ui->listView->setViewMode(QListView::IconMode);
    }
    else{
        ui->listView->setViewMode(QListView::ListMode);
    }
}

