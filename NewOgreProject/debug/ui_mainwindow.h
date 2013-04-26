/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Fri Apr 26 08:45:28 2013
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
    QAction *actionQuitter;
    QAction *actionCharger;
    QAction *actionSauvegarder;
    QAction *actionAjouter;
    QAction *actionSauvegarder_2;
    QAction *actionAjouter_2;
    QAction *actionTop;
    QAction *actionBottom;
    QAction *actionAjouter_Section;
    QAction *actionTop_2;
    QAction *actionBottom_2;
    QAction *actionSauvegarder_Biblio;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFichier;
    QMenu *menuPi_ces;
    QMenu *menuBiblioth_que;
    QMenu *menuA_propos;
    QMenu *menuFuselage;
    QMenu *menuCam_ra_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(595, 487);
        actionQuitter = new QAction(MainWindow);
        actionQuitter->setObjectName(QString::fromUtf8("actionQuitter"));
        actionCharger = new QAction(MainWindow);
        actionCharger->setObjectName(QString::fromUtf8("actionCharger"));
        actionSauvegarder = new QAction(MainWindow);
        actionSauvegarder->setObjectName(QString::fromUtf8("actionSauvegarder"));
        actionAjouter = new QAction(MainWindow);
        actionAjouter->setObjectName(QString::fromUtf8("actionAjouter"));
        actionSauvegarder_2 = new QAction(MainWindow);
        actionSauvegarder_2->setObjectName(QString::fromUtf8("actionSauvegarder_2"));
        actionAjouter_2 = new QAction(MainWindow);
        actionAjouter_2->setObjectName(QString::fromUtf8("actionAjouter_2"));
        actionTop = new QAction(MainWindow);
        actionTop->setObjectName(QString::fromUtf8("actionTop"));
        actionBottom = new QAction(MainWindow);
        actionBottom->setObjectName(QString::fromUtf8("actionBottom"));
        actionAjouter_Section = new QAction(MainWindow);
        actionAjouter_Section->setObjectName(QString::fromUtf8("actionAjouter_Section"));
        actionTop_2 = new QAction(MainWindow);
        actionTop_2->setObjectName(QString::fromUtf8("actionTop_2"));
        actionBottom_2 = new QAction(MainWindow);
        actionBottom_2->setObjectName(QString::fromUtf8("actionBottom_2"));
        actionSauvegarder_Biblio = new QAction(MainWindow);
        actionSauvegarder_Biblio->setObjectName(QString::fromUtf8("actionSauvegarder_Biblio"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setAutoFillBackground(false);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 595, 25));
        menuFichier = new QMenu(menuBar);
        menuFichier->setObjectName(QString::fromUtf8("menuFichier"));
        menuPi_ces = new QMenu(menuBar);
        menuPi_ces->setObjectName(QString::fromUtf8("menuPi_ces"));
        menuBiblioth_que = new QMenu(menuBar);
        menuBiblioth_que->setObjectName(QString::fromUtf8("menuBiblioth_que"));
        menuA_propos = new QMenu(menuBar);
        menuA_propos->setObjectName(QString::fromUtf8("menuA_propos"));
        menuFuselage = new QMenu(menuBar);
        menuFuselage->setObjectName(QString::fromUtf8("menuFuselage"));
        menuCam_ra_2 = new QMenu(menuBar);
        menuCam_ra_2->setObjectName(QString::fromUtf8("menuCam_ra_2"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFichier->menuAction());
        menuBar->addAction(menuFuselage->menuAction());
        menuBar->addAction(menuPi_ces->menuAction());
        menuBar->addAction(menuBiblioth_que->menuAction());
        menuBar->addAction(menuCam_ra_2->menuAction());
        menuBar->addAction(menuA_propos->menuAction());
        menuFichier->addAction(actionCharger);
        menuFichier->addAction(actionSauvegarder);
        menuFichier->addAction(actionQuitter);
        menuPi_ces->addAction(actionAjouter);
        menuPi_ces->addAction(actionAjouter_2);
        menuPi_ces->addAction(actionSauvegarder_2);
        menuPi_ces->addAction(actionSauvegarder_Biblio);
        menuFuselage->addAction(actionAjouter_Section);
        menuCam_ra_2->addAction(actionTop_2);
        menuCam_ra_2->addAction(actionBottom_2);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionQuitter->setText(QApplication::translate("MainWindow", "Quitter", 0, QApplication::UnicodeUTF8));
        actionCharger->setText(QApplication::translate("MainWindow", "Charger", 0, QApplication::UnicodeUTF8));
        actionSauvegarder->setText(QApplication::translate("MainWindow", "Sauvegarder", 0, QApplication::UnicodeUTF8));
        actionAjouter->setText(QApplication::translate("MainWindow", "Cr\303\251er", 0, QApplication::UnicodeUTF8));
        actionSauvegarder_2->setText(QApplication::translate("MainWindow", "Sauvegarder", 0, QApplication::UnicodeUTF8));
        actionAjouter_2->setText(QApplication::translate("MainWindow", "Ajouter", 0, QApplication::UnicodeUTF8));
        actionTop->setText(QApplication::translate("MainWindow", "Top", 0, QApplication::UnicodeUTF8));
        actionBottom->setText(QApplication::translate("MainWindow", "Bottom", 0, QApplication::UnicodeUTF8));
        actionAjouter_Section->setText(QApplication::translate("MainWindow", "Ajouter Section", 0, QApplication::UnicodeUTF8));
        actionTop_2->setText(QApplication::translate("MainWindow", "Top", 0, QApplication::UnicodeUTF8));
        actionBottom_2->setText(QApplication::translate("MainWindow", "Bottom", 0, QApplication::UnicodeUTF8));
        actionSauvegarder_Biblio->setText(QApplication::translate("MainWindow", "Sauvegarder (Biblio)", 0, QApplication::UnicodeUTF8));
        menuFichier->setTitle(QApplication::translate("MainWindow", "Fichier", 0, QApplication::UnicodeUTF8));
        menuPi_ces->setTitle(QApplication::translate("MainWindow", "Pi\303\250ces", 0, QApplication::UnicodeUTF8));
        menuBiblioth_que->setTitle(QApplication::translate("MainWindow", "Biblioth\303\250que", 0, QApplication::UnicodeUTF8));
        menuA_propos->setTitle(QApplication::translate("MainWindow", "A propos", 0, QApplication::UnicodeUTF8));
        menuFuselage->setTitle(QApplication::translate("MainWindow", "Fuselage", 0, QApplication::UnicodeUTF8));
        menuCam_ra_2->setTitle(QApplication::translate("MainWindow", "Cam\303\251ra", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
