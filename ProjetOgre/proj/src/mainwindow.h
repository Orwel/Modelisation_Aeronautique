#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "ogrewidget.h"
#include "piecedialog.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    OgreWidget *ogreWidget;
    PieceDialog* maPiece;

private slots:
    void initWindow();
};

#endif // MAINWINDOW_H
