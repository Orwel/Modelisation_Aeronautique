#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer::singleShot( 500, this, SLOT(initWindow()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWindow()
{
    QGridLayout* Mainbox = new QGridLayout();
        QVBoxLayout *vbox = new QVBoxLayout();
        QHBoxLayout *hbox = new QHBoxLayout();

        //myOgre = new OgreWidget();
        //Mainbox->addWidget( myOgre,0,0,6,6);
        myApp = new AppWidget();
        Mainbox->addWidget( myApp,0,0,6,6);

        QLabel* GravCenter = new QLabel("Centre de gravite :");
        QLabel* Poids = new QLabel("Poids total :");
        QLabel* GravLine = new QLabel("");
        QLabel* PoidsLine = new QLabel("");

        hbox->addWidget(GravCenter);
        hbox->addWidget(GravLine);
        hbox->addWidget(Poids);
        hbox->addWidget(PoidsLine);

        Mainbox->addLayout( hbox , 7 , 0 , 1, 6);

        GravLine->setText("(0,0,0)");

        QLabel* piece1 = new QLabel("En attente ");
        QLabel* piece2 = new QLabel("de solution");

        QHBoxLayout *ligne1 = new QHBoxLayout();
        QHBoxLayout *ligne2 = new QHBoxLayout();
        QLabel* pieceCenter = new QLabel("Centre : ");
        QLabel* piCenRes = new QLabel("");
        QLabel* piecePoids = new QLabel("Poids : ");
        QLabel* piPoRes = new QLabel("");
        ligne1->addWidget(pieceCenter);ligne1->addWidget(piCenRes);
        ligne2->addWidget(piecePoids);ligne2->addWidget(piPoRes);

        QPushButton* distanceButton = new QPushButton("distance to");

        QHBoxLayout *ligne3 = new QHBoxLayout();
        QLabel* distance = new QLabel("Distance : ");
        QLabel* disValue = new QLabel("");
        ligne3->addWidget(distance);ligne3->addWidget(disValue);

        QLabel* vide0 = new QLabel(" ");
        QLabel* vide1 = new QLabel(" ");
        QLabel* vide2 = new QLabel(" ");
        QLabel* vide3 = new QLabel(" ");
        QLabel* vide4 = new QLabel(" ");

        vbox->addWidget(piece1);vbox->addWidget(piece2);
        vbox->addWidget(vide0);vbox->addWidget(vide1);vbox->addWidget(vide2);
        vbox->addLayout(ligne1);vbox->addLayout(ligne2);
        vbox->addWidget(vide4);
        vbox->addWidget(distanceButton);vbox->addLayout(ligne3);
        vbox->addWidget(vide3);

        Mainbox ->addLayout( vbox , 0 ,8 ,6,2);

        centralWidget()->setLayout( Mainbox );

}
