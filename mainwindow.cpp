#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SdlWidget.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QWindow>
#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // Create and set the SDL widget as the central widget
    SdlWidget* sdlWidget = new SdlWidget(this);
    setCentralWidget(sdlWidget);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    SdlWidget* sdlWidget = qobject_cast<SdlWidget*>(centralWidget());
    sdlWidget->startup = false; // Set startup to false to indicate that the widget is no longer in the startup phase
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Images (*.png *.xpm *.jpg *.bmp)"));
    sdlWidget->surface = sdlWidget->loadImage(fileName.toStdString());
    sdlWidget->updateRenderer(sdlWidget->surface); // Update the renderer with the new surface
    MainWindow::setWindowTitle(fileName); // Set the window title to the file name
}

