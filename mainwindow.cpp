#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
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
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Images (*.png *.xpm *.jpg *.bmp)"));
    QMessageBox::information(this, tr("File Selected"), fileName.isEmpty() ? tr("No file selected") : tr("Selected file: %1").arg(fileName));
}
