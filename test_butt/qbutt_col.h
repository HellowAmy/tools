#ifndef QBUTT_COL_H
#define QBUTT_COL_H

#include <QWidget>
#include <QColor>
#include <QPainter>
#include <QPushButton>

//!
//! 功能：图片变色三态按钮
//! 用法：传入一张PNG图片（推荐黑白图片），传入三态RGB颜色，触发三态时根据RGB颜色改变图片颜色
//! 原理：保留PNG图片每个点位的颜色信息和透明度，如果点为不透明，根据三态RGB颜色改变点为颜色
//! 注意：前景指有颜色的像素点，背景指透明的像素点
//!
class qbutt_col : public QPushButton
{
    Q_OBJECT
public:
    struct status
    {
        QColor normal;
        QColor enter;
        QColor press;
    };

public:
    explicit qbutt_col(QWidget *parent = nullptr);
    bool set_pic(QString pic);              //设置图片
    void set_col_foreground(status col);    //设置图片变化颜色

protected:
    //绘图事件
    void paintEvent(QPaintEvent *event) override;

    //触发事件
    void enterEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void ch_col_point(QColor);
    void ch_col_status();

private:
    bool _paint_fore = false;
    status _fore;
    QPixmap _pix;
    QVector<QVector<int>> _vec_alpha;
};

#endif // QBUTT_COL_H
