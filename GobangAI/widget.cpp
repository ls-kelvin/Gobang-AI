#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(&f,SIGNAL(change()),this,SLOT(change()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_human_clicked()
{
    this->hide();
    f.show();
    f.player=HUMAN;
}

void Widget::change()
{
    this->show();
}


void Widget::on_pushButton_AI_clicked()
{
    this->hide();
    f.show();
    f.player=AI;
}

