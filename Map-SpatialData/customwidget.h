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

        }

   void mouseMoveEvent(QMouseEvent *event)override {
           qDebug()<< event->pos();
           QPoint p(event->pos().x(), event->pos().y());
           emit MouseLocation(p);
   }
   void mousePressEvent(QMouseEvent *event) override {
      m_mousePos = event->pos();
      if(event->button() == Qt::LeftButton)
          bussesrectangles.push_back(QRect{QPoint(m_mousePos.x(),m_mousePos.y()), QSize(100,100)});
      else if (event->button() == Qt::RightButton){
      }
      update();
   }
public slots:
   void SetBusses(Application::Types::DataSet busses);
   void SetPassenger(Application::Types::DataSet passenger);
   void BusStateChange(bool state);
   void PassengerStateChange(bool state);
signals:
  void MouseLocation(QPoint point);


private:

   QPoint m_mousePos;
   Application::Types::DataSet bussesdata;
   Application::Types::DataSet passengersdata;
   QVector<QRect> bussesrectangles;
   QVector<QRect> passengerrectangles;
   bool showbusses =true;
   bool showpassangers = true;
};

