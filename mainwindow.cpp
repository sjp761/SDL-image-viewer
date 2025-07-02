#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QWindow>
#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    SdlWidget* sdlWidget = qobject_cast<SdlWidget*>(centralWidget());
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Images (*.png *.xpm *.jpg *.bmp)"));
    SDL_Surface* surface = sdlWidget->loadImage(fileName.toStdString());
    if (!surface) {
        QMessageBox::critical(this, tr("Error"), tr("Could not load image: %1").arg(SDL_GetError()));
        return;
    }
    sdlWidget->updateRenderer(surface);
    SDL_FreeSurface(surface);
    sdlWidget->update();
    std::cout << "Image loaded and renderer updated." << std::endl;
}

