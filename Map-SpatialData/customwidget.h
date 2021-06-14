#pragma once
#include <QtWidgets>
#include <QVector>
#include <QPixmap>
#include "sidewidget.h"

#include "Types.h"
class CustomWidget : public QWidget
{
        Q_OBJECT

public:
   explicit CustomWidget(QWidget *parent = nullptr) : QWidget{parent} {
           this->setMouseTracking(true);
           this->setMinimumSize(700,700);



   }

   ~CustomWidget() {

   }

   void paintEvent(QPaintEvent *) override {
           QPixmap pixmap;
           pixmap.load("/home/yakup/git/Map-SpatialData/Map-SpatialData/Assets/lefke-image.jpg");
           QPixmap crossicon;
           crossicon.load(crosslocation);
           QPainter painter(this);
           painter.drawPixmap(0,0,pixmap);
          // mainwidget->setStyleSheet("background-image:\"/home/yakup/git/Map-SpatialData/Map-SpatialData/Assets/lefke-image.jpg\";");
           painter.setPen(QPen{Qt::blue, 3, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin});

           if(showbusses)
                   for(auto &l : bussesrectangles){
                       painter.drawEllipse(l);
                   }

            painter.setPen(QPen{Qt::darkYellow, 3, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin});

            if(showpassangers)
                    for(auto &l : passengerrectangles){
                        painter.drawEllipse(l);
                    }

            painter.setPen(QPen{Qt::green, 3, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin});

            if(showcovrage)
                    for(auto &l:checkcovarege)
                            painter.drawEllipse(l);

            if(clicked.size() > 0 && clickstatus) {
              if(clicked.size() < 2)
                       for(auto &p:clicked){
                               painter.drawPixmap(p,crossicon);

                       }
              else {
                      clickrectangle = QRect(clicked.at(0),clicked.at(1));
                      painter.setPen(QPen{Qt::black, 3, Qt::DashDotLine, Qt::SquareCap, Qt::MiterJoin});

                      painter.drawRect(clickrectangle);

              }

            }

        }

   void mouseMoveEvent(QMouseEvent *event)override {
           qDebug()<< event->pos();
           QPoint p(event->pos().x(), event->pos().y());
           emit MouseLocation(p);
   }
   void mousePressEvent(QMouseEvent *event) override {
      m_mousePos = event->pos();
      if(event->button() == Qt::LeftButton && clickstatus) {
              if(clicked.size() >= 2)
                      clicked.remove(0);
              clicked.push_back(QPoint(m_mousePos.x(),m_mousePos.y()));


      }
      else if (event->button() == Qt::RightButton){
              clicked.clear();
      }
      update();
   }
public slots:
   void SetBusses(Application::Types::DataSet busses);
   void SetPassenger(Application::Types::DataSet passenger);
   void SetCovarage(Application::Types::DataSet covarages);
   void BusStateChange(bool state);
   void PassengerStateChange(bool state);
   void SetClickStatus(bool state);
signals:
  void MouseLocation(QPoint point);


private:

   QPoint m_mousePos;
   Application::Types::DataSet bussesdata;
   Application::Types::DataSet passengersdata;
   QVector<QRect> bussesrectangles;
   QVector<QRect> passengerrectangles;
   QVector<QRect> checkcovarege;
   QVector<QPoint> clicked;
   QRect clickrectangle;
   bool showcovrage = false;
   bool showbusses = true;
   bool showpassangers = true;
   const QString crosslocation="/home/yakup/git/Map-SpatialData/Map-SpatialData/Assets/cross.png";
   bool clickstatus = false;
};

