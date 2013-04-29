#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "appwidget.h"
#include "LoaderXML.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    AppWidget *myApp;

    QLabel *GravTot;
    QLabel *PoidsTot;
    QLabel *GravPiece;
    QLabel *PoidsPiece;
    QLabel *Distant;


private slots:
    void initWindow();

    void on_actionQuitter_triggered();

    void on_actionCharger_triggered();

public:
    void PrintTot(char *myGrav , char *myPoids );
    void PrintPiece(char *myGrav , char *myPoids );
    void PrintDist(char *myDist);


};

#endif // MAINWINDOW_H
