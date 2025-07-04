#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SDLContainer.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QWindow>
#include <QLayout>
#include <QTimer>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    centralWidget()->setLayout(new QVBoxLayout);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionConvert_Image, &QAction::triggered, this, &MainWindow::convertImage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Images (*.png *.xpm *.jpg *.bmp)"));
    if (!fileName.isEmpty()) {
        SDLContainer::loadImage(fileName.toStdString());
        MainWindow::setWindowTitle(fileName); // Set the window title to the file name
    }
}


void MainWindow::convertImage()
{
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
            SDL_SaveBMP(SDLContainer::surface, fileName.toStdString().c_str());
            std::cout << "Converting to BMP format" << std::endl;
        } else if (extension == "jpg" || extension == "jpeg") {
            IMG_SaveJPG(SDLContainer::surface, fileName.toStdString().c_str(), 100);
            std::cout << "Converting to JPEG format" << std::endl;
        } else if (extension == "png") {
            IMG_SavePNG(SDLContainer::surface, fileName.toStdString().c_str());
            std::cout << "Converting to PNG format" << std::endl;
        }
        }
}

void MainWindow::addSDLWidget()
{
    if (SDLContainer::embedded) {
        centralWidget()->layout()->addWidget(QWidget::createWindowContainer(SDLContainer::embedded, this));
        printf("SDL widget added to layout successfully\n");
        
        // Start a timer to continuously render SDL content - program does not work without this
        QTimer* renderTimer = new QTimer(this);
        connect(renderTimer, &QTimer::timeout, []() {
            SDLContainer::render();
        });
        renderTimer->start(16); // ~60 FPS
        
    } else {
        printf("Error: Cannot add SDL widget - embedded is null\n");
    }
}
