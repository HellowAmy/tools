#include "qbutt_col.h"

qbutt_col::qbutt_col(QWidget *parent) : QPushButton(parent)
{

}

bool qbutt_col::set_pic(QString pic)
{
    _paint_fore = _pix.load(pic);
    if(_paint_fore)
    {
        QImage img = _pix.toImage();
        _vec_alpha.resize(img.width());
        for(int w=0;w<img.width();w++)
        {
            _vec_alpha[w].resize(img.height());
            for(int h=0;h<img.height();h++)
            {
                _vec_alpha[w][h] = img.pixelColor(w, h).alpha();
            }
        }
        this->resize(img.size());
    }
    return _paint_fore;
}

void qbutt_col::set_col_foreground(status col)
{
    _fore = col;
    ch_col_point(_fore.normal);
}

void qbutt_col::paintEvent(QPaintEvent *event)
{
    if(_paint_fore)
    {
        QPainter *show = new QPainter(this);
        show->drawPixmap(0,0,_pix);
        show->end();
    }
    else QPushButton::paintEvent(event);
}

void qbutt_col::enterEvent(QEvent *event)
{
    ch_col_point(_fore.enter);
    QPushButton::enterEvent(event);
}

void qbutt_col::mousePressEvent(QMouseEvent *event)
{
    ch_col_point(_fore.press);
    QPushButton::mousePressEvent(event);
}

void qbutt_col::leaveEvent(QEvent *event)
{
    ch_col_point(_fore.normal);
    QPushButton::leaveEvent(event);
}

void qbutt_col::mouseReleaseEvent(QMouseEvent *event)
{
    ch_col_point(_fore.enter);
    QPushButton::mouseReleaseEvent(event);
}

void qbutt_col::ch_col_point(QColor col)
{
    if(_paint_fore)
    {
        QImage img = _pix.toImage(); //载入
        for (int w=0;w<img.width();w++)
        {
            for (int h=0;h<img.height();h++)
            {
                if(_vec_alpha[w][h] > 0)
                {
                    col.setAlpha(_vec_alpha[w][h]);
                    img.setPixelColor(w,h,col);
                }
            }
        }
        _pix = QPixmap::fromImage(img); //保存
        this->update();
    }
}
