#include "About.h"
#include "ui_about.h"
#include <QDebug>

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
}

About::~About()
{
    delete ui;
}

void About::on_pushButton_clicked()
{
    this->close();
    qDebug()<<"关闭";
}
