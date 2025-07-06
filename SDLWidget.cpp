#include "SDLWidget.h"
#include "SDLContainer.h"
#include <QVBoxLayout>
#include <QResizeEvent>

SDLWidget::SDLWidget(QWidget *parent)
{
    this->setLayout(new QVBoxLayout(this));
    this->layout()->addWidget(QWidget::createWindowContainer(SDLContainer::embedded, this));
}

SDLWidget::~SDLWidget()
{
    //blank (for now at least)
}

void SDLWidget::paintEvent(QPaintEvent *event)
{
    SDLContainer::render();
}

void SDLWidget::resizeEvent(QResizeEvent *event)
{
    SDLContainer::resize(width(), height());
}
