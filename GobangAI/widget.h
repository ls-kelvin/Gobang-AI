#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "form.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void on_pushButton_AI_clicked();
    void on_pushButton_human_clicked();
    void change();
private:
    Ui::Widget *ui;
    Form f;
};
#endif // WIDGET_H
