#include "sidewidget.h"

SideWidget::SideWidget(QWidget *parent) : QWidget(parent)
{
        vlayout = new QVBoxLayout();
        /*        QVBoxLayout *featurelayout;

        QCheckBox *busstops;
        QCheckBox *passenger;

        QLabel *ActiveLabel;*/
        activelabel = new QLabel(this);
        activelabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        activelabel->setText("Active Features");
        activelabel->setMaximumWidth(400);
        activelabel->setAlignment(Qt::AlignHCenter);
        activelabel->setMaximumHeight(20);

        featurelayout = new QVBoxLayout();
        busstops = new QCheckBox("Bus Stops");
        passenger = new QCheckBox("Passenger");
        busstops->setCheckState(Qt::CheckState::Checked);
        passenger->setCheckState(Qt::CheckState::Checked);

        featurelayout->addWidget(activelabel);
        featurelayout->addWidget(busstops);
        featurelayout->addWidget(passenger);

        activeregionlabel = new QLabel();
        activeregionlabel->setText("Active Region");
        activeregionlabel->setMaximumWidth(400);
        activeregionlabel->setMaximumHeight(20);
        activeregionlabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

        activeregionlabel->setAlignment(Qt::AlignHCenter);

        wholearea = new QRadioButton("Whole Area");
        selectedbox = new QRadioButton("Selected Box");
        selectedpolygon = new QRadioButton("Selected Polygon");


         featurelayout->addWidget(activeregionlabel);
         featurelayout->addWidget(wholearea);
         featurelayout->addWidget(selectedbox);
         featurelayout->addWidget(selectedpolygon);


         submitrangequery = new QPushButton("Submit Range Query");
         submitpointquery = new QPushButton("Submit Point Query");
         checkcoverage = new QPushButton("Check Coverage");

         featurelayout->addWidget(submitrangequery);
         featurelayout->addWidget(submitpointquery);
         featurelayout->addWidget(checkcoverage);

        /*        QLabel *activeregionlabel;

        QRadioButton *wholearea;
        QRadioButton *selectedbox;
        QRadioButton * selectedpolygon;*/


        this->setMinimumSize(300,750);
        QPalette pal = this->palette();
        pal.setColor(QPalette::Background, Qt::gray);
        this->setAutoFillBackground(true);
        this->setPalette(pal);

        x = new QLineEdit(this);
        y = new QLineEdit(this);

        x->setMaximumWidth(100);
        y->setMaximumWidth(100);
        x->setReadOnly(true);
        y->setReadOnly(true);


        pointbox = new QHBoxLayout();
        coordinates = new QLabel("Current Coordinates");
        coordinates->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        coordinates->setMaximumWidth(400);
        coordinates->setMaximumHeight(20);
        coordinates->setAlignment(Qt::AlignHCenter);

        //pointbox->addWidget(coordinates);
        pointbox->addWidget(x);
        pointbox->addWidget(y);
        pointbox->setAlignment(Qt::AlignHCenter);

        coordinatelayout = new QVBoxLayout();
        coordinatelayout->addWidget(coordinates);
        coordinatelayout->addLayout(pointbox);

        vlayout->addLayout(featurelayout);
        vlayout->addLayout(coordinatelayout);
        wholearea->setChecked(true);
        setLayout(vlayout);
        connect(busstops,SIGNAL(stateChanged(int)),this,SLOT(busstopschanged(int)));
        connect(passenger,SIGNAL(stateChanged(int)),this,SLOT(passengerschanged(int)));
        connect(wholearea, SIGNAL(clicked(bool)),this, SLOT(GetAllPoints(bool)));



}
SideWidget::~SideWidget(){
        delete activelabel;
        delete x;
        delete y;
}
void SideWidget::GetCoordination(const QPoint &point) {
        SetCoordination(point);
}
void SideWidget::GetAllPoints(bool state) {
        qDebug()<<"gene basdik";
        bool busstate = false;
        bool passengerstate = false;
        if(state) {
                if(busstops->checkState())
                        busstate=  true;
                if(passenger->checkState())
                        passengerstate = true;

                emit wholeareaselection(busstate, passengerstate);
        }
}

void SideWidget::SetCoordination(const QPoint &point) {
        x->setText(QString::number(point.x()));
        y->setText(QString::number(point.y()));

}

void SideWidget::busstopschanged(int state) {
        emit buseventcall(state);
        if(wholearea->isChecked())
                emit wholeareaselection(busstops->checkState(), passenger->checkState());
}
void SideWidget::passengerschanged(int state) {
        emit passengereventcall(state);
        if(wholearea->isChecked())
                emit wholeareaselection(busstops->checkState(), passenger->checkState());


}
