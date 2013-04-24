#include "piecedialog.h"
#include "ui_piecedialog.h"

PieceDialog::PieceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PieceDialog)
{
    ui->setupUi(this);

    QTimer::singleShot( 500, this, SLOT(initPiece()));

}

PieceDialog::~PieceDialog()
{
    delete ui;
}


void PieceDialog::initPiece()
{
    QVBoxLayout *vbox = new QVBoxLayout();
    test = new OgreWidget();

    vbox->addWidget(test);

    ui->testWidget->setLayout(vbox);
}
