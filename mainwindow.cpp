#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SDLContainer.h"
#include "SDLWidget.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QWindow>
#include <QLayout>
#include <QTimer>
#include <iostream>
#include <fstream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    menuRecent = new QMenu(tr("Recent Files"), this);
    ui->setupUi(this);
    ui->menuFile->addMenu(menuRecent);
    connect(menuRecent, &QMenu::triggered, this, &MainWindow::handleRecentFileAction); // Anytime an action is triggered in the recent files menu (click one of the recent files), call handleRecentFileAction
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionConvert_Image, &QAction::triggered, this, &MainWindow::convertImage);
}

MainWindow::~MainWindow()
{
    delete ui;
    saveRecentSet(); // Save recent files before closing
}

void MainWindow::openFile()
{
    
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Images (*.png *.xpm *.jpg *.bmp)"));
    if (!fileName.isEmpty()) {
        SDLContainer::loadImage(fileName.toStdString());
        MainWindow::setWindowTitle(fileName); // Set the window title to the file name
        recentFiles.insert(fileName.toStdString());
        updateRecentFileMenu();
        SDLContainer::render();
        // Add the file to the recent files list
        
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
            if (extension == "bmp") 
            {
                SDL_SaveBMP(SDLContainer::surface.get(), fileName.toStdString().c_str());
                std::cout << "Converting to BMP format" << std::endl;
            } 
            else if (extension == "jpg" || extension == "jpeg") {
                IMG_SaveJPG(SDLContainer::surface.get(), fileName.toStdString().c_str(), 100);
                std::cout << "Converting to JPEG format" << std::endl;
            } 
            else if (extension == "png") {
                IMG_SavePNG(SDLContainer::surface.get(), fileName.toStdString().c_str());
                std::cout << "Converting to PNG format" << std::endl;
            }
        }
    
}

void MainWindow::updateRecentFileMenu()
{
    menuRecent->clear(); // Clear the existing actions in the menu
    for (const std::string &file : recentFiles) 
    {
        QAction *action = new QAction(QString::fromStdString(file), this);
        action->setData(QString::fromStdString(file));
        menuRecent->addAction(action);
    }
}

void MainWindow::fillRecentSet()
{
    std::ifstream file("recent_files.txt");
    std::string line;
    while (std::getline(file, line)) {
        recentFiles.insert(line);
    }
}

void MainWindow::saveRecentSet()
{
    std::ofstream file("recent_files.txt");
    for (const auto &string : recentFiles) {
        file << string << std::endl;
    }
}

void MainWindow::handleRecentFileAction(QAction *action)
{
    std::cout << "Recent file action triggered: " << action->data().toString().toStdString() << std::endl;
    SDLContainer::loadImage(action->data().toString().toStdString());
    MainWindow::setWindowTitle(action->data().toString()); // Set the window title to the file name
    SDLContainer::render();
}
