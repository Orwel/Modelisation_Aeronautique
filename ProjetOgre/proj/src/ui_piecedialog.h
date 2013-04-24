/********************************************************************************
** Form generated from reading UI file 'piecedialog.ui'
**
** Created: Tue Apr 23 06:02:58 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PIECEDIALOG_H
#define UI_PIECEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PieceDialog
{
public:
    QWidget *testWidget;

    void setupUi(QDialog *PieceDialog)
    {
        if (PieceDialog->objectName().isEmpty())
            PieceDialog->setObjectName(QString::fromUtf8("PieceDialog"));
        PieceDialog->resize(207, 353);
        testWidget = new QWidget(PieceDialog);
        testWidget->setObjectName(QString::fromUtf8("testWidget"));
        testWidget->setGeometry(QRect(10, 10, 181, 331));

        retranslateUi(PieceDialog);

        QMetaObject::connectSlotsByName(PieceDialog);
    } // setupUi

    void retranslateUi(QDialog *PieceDialog)
    {
        PieceDialog->setWindowTitle(QApplication::translate("PieceDialog", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PieceDialog: public Ui_PieceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PIECEDIALOG_H
