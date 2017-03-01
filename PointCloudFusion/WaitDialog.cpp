#include "WaitDialog.h"

WaitDialog::WaitDialog(QDialog *parent) : QDialog(parent)
{
    label = new QLabel(this);
    this->setFixedSize(200,200);
    setWindowOpacity(0.5);
    this->setWindowFlags(Qt::Dialog|Qt::CustomizeWindowHint);

    //取消对话框标题
    //this->setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);

    //取消对话框标题和边框
    //this->setAutoFillBackground(true);
    this->setContentsMargins(0,0,0,0);
    label->setContentsMargins(0,0,0,0);
    /*Qpalette palette ;
     * palette.setBrush(QPalette::Background,QBrush("E:/qml/imgdialog/loading.gif")));
     * this->setPalette(palette);*/
    movie = new QMovie(":/images/loading0.gif");
    //label->setMovie(movie);
    label->setText("sfadfadfadfadf");
    label->show();
    movie->start();
}

WaitDialog::~WaitDialog()
{
    delete label;
    delete movie;
}
