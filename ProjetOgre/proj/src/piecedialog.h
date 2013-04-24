#ifndef PIECEDIALOG_H
#define PIECEDIALOG_H

#include <QDialog>
#include "ogrewidget.h"

namespace Ui {
class PieceDialog;
}

class PieceDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit PieceDialog(QWidget *parent = 0);
    ~PieceDialog();
    
private:
    Ui::PieceDialog *ui;
    OgreWidget* test;

private slots:
    void initPiece();

};

#endif // PIECEDIALOG_H
