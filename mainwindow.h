#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void openFile();
    QMenu* menuRecent;
    void convertImage();
    Ui::MainWindow *getUi() const { return ui; }
    void updateRecentFileMenu();
    std::set<std::string> recentFiles;
    void fillRecentSet();
    void saveRecentSet();


public slots:
    void handleRecentFileAction(QAction* action);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
