#include "widget.h"
#include "ui_widget.h"

#include <qbutt_col.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


    qbutt_col *bu = new qbutt_col(this);
    bu->set_pic("/home/red/open/123.png");//m_2.png m_backdrop.png  /home/red/open/github/qt_hur/pic/m_one/m_2.png
    bu->set_col_foreground({0x808080,0x101010,0xff0000});
    bu->update();
    bu->show();

}

Widget::~Widget()
{
    delete ui;
}

