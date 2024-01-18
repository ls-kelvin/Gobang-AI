#include "form.h"
#include "ui_form.h"


Form::Form(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Form)
{
    ui->setupUi(this);
    for(int i=0;i<15;i++)
        for(int j=0;j<15;j++){
            chesspoint[i][j].setX(x_start+interval*j);
            chesspoint[i][j].setY(y_start+interval*i);
        }
    setMouseTracking(true);
    initial();
}

Form::~Form()
{
    delete ui;
}

void Form::initial()
{
    ai.chessboard.clear();
    log.clear();
    place_pos.first=-1;place_pos.second=-1;
    turn=P1;
    state=STOP;
    piece_num=0;
    ui->textBrowser->setText("");
}

void Form::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    pen.setWidth(1);
    pen.setCapStyle(Qt::SquareCap);
    pen.setJoinStyle(Qt::BevelJoin);
    painter.setPen(pen);
    //画棋盘
    int num=1;
    for(int i=x_start;i<=x_end;i+=interval){
        QLine line(i,y_start,i,y_end);
        painter.drawLine(line);
        painter.drawText(i-5,y_start-5,QString("%1").arg(num++));
    }
    num=1;
    for(int i=y_start;i<=y_end;i+=interval){
        QLine line(x_start,i,x_end,i);
        painter.drawLine(line);
        painter.drawText(x_start-20,i+5,QString("%1").arg(num++));
    }
    pen.setWidth(8);
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);
    painter.drawPoint(QPoint(400,300));
    pen.setWidth(5);
    painter.setPen(pen);
    QPoint points[]={QPoint(400-interval*4,300-interval*4),
                       QPoint(400+interval*4,300-interval*4),
                       QPoint(400-interval*4,300+interval*4),
                       QPoint(400+interval*4,300+interval*4)};
    painter.drawPoints(points,4);
    //画要下的棋子
    pen.setWidth(1);
    painter.setPen(pen);
    if(place_pos.first!=-1&&ai.chessboard.islegal(place_pos.first,place_pos.second)){
        if(turn==P1) painter.setBrush(QBrush(QColor(0,0,0,100)));
        else painter.setBrush(QBrush(QColor(255,255,255,100)));
        QPoint place_point=chesspoint[place_pos.first-1][place_pos.second-1];
        painter.drawEllipse(place_point.x()-15,place_point.y()-15,30,30);
    }
    //画已下的棋子
    for(int i=0;i<log.size();i++){
        QPoint pp=chesspoint[log[i].first-1][log[i].second-1];
        QRect r(pp.x()-15,pp.y()-15,30,30);
        if(i&1){
            painter.setBrush(QBrush(Qt::white));
            painter.drawEllipse(pp.x()-15,pp.y()-15,30,30);
            pen.setColor(Qt::black);
            painter.setPen(pen);
            painter.drawText(r,Qt::AlignCenter,QString("%1").arg(i+1));
        }
        else{
            painter.setBrush(QBrush(Qt::black));
            painter.drawEllipse(pp.x()-15,pp.y()-15,30,30);
            pen.setColor(Qt::white);
            painter.setPen(pen);
            painter.drawText(r,Qt::AlignCenter,QString("%1").arg(i+1));
        }
        if(i==log.size()-1){
            pen.setColor(Qt::blue);
            painter.setBrush(QBrush(Qt::NoBrush));
            painter.setPen(pen);
            painter.drawRect(r);
        }
    }
}

void Form::mouseMoveEvent(QMouseEvent *event)
{
    if(state==STOP)
        return;
    QPoint cursor_pos=event->pos();
    if(cursor_pos.x()>x_start-interval/2&&cursor_pos.x()<x_end+interval/2
        &&cursor_pos.y()>y_start-interval/2&&cursor_pos.y()<y_end+interval/2)
    {
        place_pos.second=(cursor_pos.x()-(x_start-interval/2))/interval+1;
        place_pos.first=(cursor_pos.y()-(y_start-interval/2))/interval+1;
    }
    else{place_pos.first=-1;}
    update();
}



void Form::mousePressEvent(QMouseEvent *event)
{
    if(!ai.chessboard.islegal(place_pos.first,place_pos.second))
        return;
    if(state==STOP)
        return;
    if(player==HUMAN){
        chess_place(place_pos.first,place_pos.second);
    }
    else if(player==AI){
        chess_place(place_pos.first,place_pos.second);
        ::pos ai_place=ai.getBestPlace();
        chess_place(ai_place.first,ai_place.second);
    }
}

void Form::check_end()
{
    int score=ai.chessboard.evaluate();
    qDebug()<<score;
    if(score==-100000){
        state=STOP;
        ui->textBrowser->setText("Black Win!");
    }
    else if(score==100000){
        state=STOP;
        ui->textBrowser->setText("White Win!");
    }
    if(piece_num==225){
        state=STOP;
        ui->textBrowser->setText("Draw!");
    }
}

void Form::chess_place(int x,int y)
{
    piece_num++;
    ai.chessboard.chess_state[x][y]=turn?WHITE:BLACK;
    turn=turn?P1:P2;
    log.push_back(::pos(x,y));
    this->repaint();
    check_end();
}


void Form::on_pushButton_start_clicked()
{
    initial();
    state=BEGIN;
    update();
}


void Form::on_pushButton_back_clicked()
{
    int tmp=2;
    if(log.size()<2)
        return;
    while(tmp--){
        ::pos last_pos=log.back();
        ai.chessboard.chess_state[last_pos.first][last_pos.second]=BLANK;
        log.pop_back();
        piece_num-=2;
    }
    state=BEGIN;
    ui->textBrowser->setText("");
    update();
}


void Form::on_pushButton_return_clicked()
{
    state=STOP;
    ai.chessboard.clear();
    place_pos={-1,-1};
    log.clear();
    this->hide();
    emit change();
}

