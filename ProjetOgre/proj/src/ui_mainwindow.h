/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue Apr 23 06:02:58 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionSauvegarder;
    QAction *actionCharger;
    QAction *actionCr_er;
    QAction *actionSauvegarder_2;
    QAction *actionTop;
    QAction *actionBottom;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuPi_ces;
    QMenu *menuBiblioth_que;
    QMenu *menuCam_ra;
    QMenu *menuA_propos;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(631, 490);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionSauvegarder = new QAction(MainWindow);
        actionSauvegarder->setObjectName(QString::fromUtf8("actionSauvegarder"));
        actionCharger = new QAction(MainWindow);
        actionCharger->setObjectName(QString::fromUtf8("actionCharger"));
        actionCr_er = new QAction(MainWindow);
        actionCr_er->setObjectName(QString::fromUtf8("actionCr_er"));
        actionSauvegarder_2 = new QAction(MainWindow);
        actionSauvegarder_2->setObjectName(QString::fromUtf8("actionSauvegarder_2"));
        actionTop = new QAction(MainWindow);
        actionTop->setObjectName(QString::fromUtf8("actionTop"));
        actionBottom = new QAction(MainWindow);
        actionBottom->setObjectName(QString::fromUtf8("actionBottom"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 631, 25));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuPi_ces = new QMenu(menuBar);
        menuPi_ces->setObjectName(QString::fromUtf8("menuPi_ces"));
        menuBiblioth_que = new QMenu(menuBar);
        menuBiblioth_que->setObjectName(QString::fromUtf8("menuBiblioth_que"));
        menuCam_ra = new QMenu(menuBar);
        menuCam_ra->setObjectName(QString::fromUtf8("menuCam_ra"));
        menuA_propos = new QMenu(menuBar);
        menuA_propos->setObjectName(QString::fromUtf8("menuA_propos"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuPi_ces->menuAction());
        menuBar->addAction(menuBiblioth_que->menuAction());
        menuBar->addAction(menuCam_ra->menuAction());
        menuBar->addAction(menuA_propos->menuAction());
        menuFile->addAction(actionCharger);
        menuFile->addAction(actionSauvegarder);
        menuFile->addAction(actionExit);
        menuPi_ces->addAction(actionCr_er);
        menuPi_ces->addAction(actionSauvegarder_2);
        menuCam_ra->addAction(actionTop);
        menuCam_ra->addAction(actionBottom);

        retranslateUi(MainWindow);
        QObject::connect(actionExit, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "Quitter", 0, QApplication::UnicodeUTF8));
        actionSauvegarder->setText(QApplication::translate("MainWindow", "Sauvegarder", 0, QApplication::UnicodeUTF8));
        actionCharger->setText(QApplication::translate("MainWindow", "Charger", 0, QApplication::UnicodeUTF8));
        actionCr_er->setText(QApplication::translate("MainWindow", "Cr\303\251er", 0, QApplication::UnicodeUTF8));
        actionSauvegarder_2->setText(QApplication::translate("MainWindow", "Sauvegarder", 0, QApplication::UnicodeUTF8));
        actionTop->setText(QApplication::translate("MainWindow", "Top", 0, QApplication::UnicodeUTF8));
        actionBottom->setText(QApplication::translate("MainWindow", "Bottom", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "Fichier", 0, QApplication::UnicodeUTF8));
        menuPi_ces->setTitle(QApplication::translate("MainWindow", "Pi\303\250ces", 0, QApplication::UnicodeUTF8));
        menuBiblioth_que->setTitle(QApplication::translate("MainWindow", "Biblioth\303\250que", 0, QApplication::UnicodeUTF8));
        menuCam_ra->setTitle(QApplication::translate("MainWindow", "Cam\303\250ra", 0, QApplication::UnicodeUTF8));
        menuA_propos->setTitle(QApplication::translate("MainWindow", "A propos", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
