#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SdlWidget.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QWindow>
#include <iostream>
#include <SDL2/SDL_image.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // Create and set the SDL widget as the central widget
    SdlWidget* sdlWidget = new SdlWidget(this);
    setCentralWidget(sdlWidget);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionConvert_Image, &QAction::triggered, this, &MainWindow::convertImage);
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

void MainWindow::convertImage()
{
    SdlWidget* sdlWidget = qobject_cast<SdlWidget*>(centralWidget());
    QString fileName = QFileDialog::getSaveFileName(
        this,
        tr("Convert"),
        "",
        tr("BMP (*.bmp);;JPEG (*.jpg *.jpeg);;PNG (*.png)")
    );
    if (!fileName.isEmpty()) {
        QFileInfo fileInfo(fileName);
        QString extension = fileInfo.suffix().toLower();
        
        if (extension == "bmp") {
            IMG_SavePNG(sdlWidget->surface, fileName.toStdString().c_str());
            std::cout << "Converting to BMP format" << std::endl;
        } else if (extension == "jpg" || extension == "jpeg") {
            IMG_SaveJPG(sdlWidget->surface, fileName.toStdString().c_str(), 100);
            std::cout << "Converting to JPEG format" << std::endl;
        } else if (extension == "png") {
            IMG_SavePNG(sdlWidget->surface, fileName.toStdString().c_str());
            std::cout << "Converting to PNG format" << std::endl;
        }
    }


}
