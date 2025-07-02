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
    sdlWidget->surface = sdlWidget->loadImage(fileName.toStdString());
    sdlWidget->updateRenderer(sdlWidget->surface);
    MainWindow::setWindowTitle(fileName); // Set the window title to the file name
}

