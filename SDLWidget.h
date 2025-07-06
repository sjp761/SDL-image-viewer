#ifndef SDLWIDGET_H
#define SDLWIDGET_H

#include <QWidget>

class SDLWidget : public QWidget
{
    Q_OBJECT

public:
     SDLWidget(QWidget *parent = nullptr);
    ~SDLWidget();
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

};

#endif // SDLWIDGET_H