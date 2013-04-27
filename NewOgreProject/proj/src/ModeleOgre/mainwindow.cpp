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

    /** Partie Widget*/
    myApp = new AppWidget();
    Mainbox->addWidget( myApp,0,0,6,6);


    /** Partie Centre et Poids Global*/
    QLabel* GravCenter = new QLabel("Centre de gravite :");
    QLabel* Poids = new QLabel("Poids total :");
    GravTot = new QLabel("");
    PoidsTot = new QLabel("");

    hbox->addWidget(GravCenter);
    hbox->addWidget(GravTot);
    hbox->addWidget(Poids);
    hbox->addWidget(PoidsTot);

    Mainbox->addLayout( hbox , 7 , 0 , 1, 6);

    /** Partie Centre et Poids de la pièce actuelle*/
    QLabel* piece1 = new QLabel("Piece en");
    QLabel* piece2 = new QLabel("cours :");

    QHBoxLayout *ligne1 = new QHBoxLayout();
    QHBoxLayout *ligne2 = new QHBoxLayout();
    QLabel* pieceCenter = new QLabel("Centre : ");
    GravPiece = new QLabel("");
    QLabel* piecePoids = new QLabel("Poids : ");
    PoidsPiece = new QLabel("");
    ligne1->addWidget(pieceCenter);ligne1->addWidget(GravPiece);
    ligne2->addWidget(piecePoids);ligne2->addWidget(PoidsPiece);

    /** Partie Distance*/
    QPushButton* distanceButton = new QPushButton("distance to");

    QHBoxLayout *ligne3 = new QHBoxLayout();
    QLabel* distance = new QLabel("Distance : ");
    Distant = new QLabel("");
    ligne3->addWidget(distance);ligne3->addWidget(Distant);

    vbox->addWidget(piece1);vbox->addWidget(piece2);
    vbox->addWidget(new QLabel(" "));vbox->addWidget(new QLabel(" "));
    vbox->addLayout(ligne1);vbox->addLayout(ligne2);
    vbox->addWidget(new QLabel(" "));
    vbox->addWidget(new QLabel(" "));
    vbox->addWidget(distanceButton);vbox->addLayout(ligne3);
    vbox->addWidget(new QLabel(" "));

    Mainbox ->addLayout( vbox , 0 ,8 ,6,2);

    centralWidget()->setLayout( Mainbox );
}

/*****************************************************************************/

void MainWindow::PrintTot(char *myGrav , char *myPoids )
{
    GravTot->setText(myGrav);
    PoidsTot->setText(myPoids);
}

/*****************************************************************************/

void MainWindow::PrintPiece(char *myGrav , char *myPoids )
{
    GravPiece->setText(myGrav);
    PoidsPiece->setText(myPoids);
}

/*****************************************************************************/

void MainWindow::PrintDist(char *dist)
{
    Distant->setText(dist);
}

/*****************************************************************************/

void MainWindow::on_actionQuitter_triggered()
{
    this->close();
}

void MainWindow::on_actionCharger_triggered()
{
    QString filename = QFileDialog::getOpenFileName(
        this,
        tr("Open XML file"),
        QDir::currentPath(),
        tr("XML files (*.xml);;All files (*.*)") );
    if( !filename.isNull() )
    {
        std::string myName="";
        QByteArray Arr = filename.toAscii();
        for(int i=0;i<Arr.size();i++)
        {
            myName+=Arr[i];
        }
        myApp->getScene()->ClearFuselages();
        LoadModel(*myApp->getScene(),myName);
        myApp->getScene()->CalculateGravityCenter();
    }
}
