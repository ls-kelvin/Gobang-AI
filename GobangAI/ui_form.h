/********************************************************************************
** Form generated from reading UI file 'form.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QPushButton *pushButton_start;
    QTextBrowser *textBrowser;
    QPushButton *pushButton_back;
    QPushButton *pushButton_return;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(80);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Form->sizePolicy().hasHeightForWidth());
        Form->setSizePolicy(sizePolicy);
        Form->setMinimumSize(QSize(800, 600));
        Form->setMaximumSize(QSize(800, 600));
        QPalette palette;
        QBrush brush(QColor(247, 238, 214, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        Form->setPalette(palette);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/title.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        Form->setWindowIcon(icon);
        pushButton_start = new QPushButton(Form);
        pushButton_start->setObjectName("pushButton_start");
        pushButton_start->setGeometry(QRect(690, 50, 93, 28));
        textBrowser = new QTextBrowser(Form);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(350, 560, 131, 41));
        QPalette palette1;
        QBrush brush1(QColor(0, 0, 0, 0));
        brush1.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(0, 0, 0, 255));
        brush2.setStyle(Qt::NoBrush);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        QBrush brush3(QColor(0, 0, 0, 255));
        brush3.setStyle(Qt::NoBrush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        QBrush brush4(QColor(0, 0, 0, 255));
        brush4.setStyle(Qt::NoBrush);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        textBrowser->setPalette(palette1);
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        font.setItalic(true);
        textBrowser->setFont(font);
        textBrowser->setStyleSheet(QString::fromUtf8("background-color:transparent;border-width:0;border-style:outset;"));
        pushButton_back = new QPushButton(Form);
        pushButton_back->setObjectName("pushButton_back");
        pushButton_back->setGeometry(QRect(690, 110, 93, 28));
        pushButton_return = new QPushButton(Form);
        pushButton_return->setObjectName("pushButton_return");
        pushButton_return->setGeometry(QRect(690, 180, 92, 28));

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Gobang", nullptr));
        pushButton_start->setText(QCoreApplication::translate("Form", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("Form", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:15pt; font-weight:700; font-style:italic;\">\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:9pt; font-weight:400; font-style:normal;\"><br /></p></body></html>", nullptr));
        pushButton_back->setText(QCoreApplication::translate("Form", "\346\202\224\346\243\213", nullptr));
        pushButton_return->setText(QCoreApplication::translate("Form", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
