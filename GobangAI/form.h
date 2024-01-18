#ifndef FORM_H
#define FORM_H

#include "chessai.h"
#include <cstring>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    gameplayer player;
    ~Form();

private:
    Ui::Form *ui;
    chessAI ai;
    vector<::pos> log;
    const int interval=36;
    const int x_start=400-interval*7;
    const int x_end=400+interval*7;
    const int y_start=300-interval*7;
    const int y_end=300+interval*7;
    QPoint chesspoint[15][15];
    ::pos place_pos;
    gameturn turn;
    gamestate state;
    int piece_num;
    // QWidget interface
protected:
    void initial();
    void chess_place(int x,int y);
    void check_end();
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
signals:
    void change();
public slots:
    void on_pushButton_start_clicked();
    void on_pushButton_back_clicked();
    void on_pushButton_return_clicked();
};






#endif // FORM_H
