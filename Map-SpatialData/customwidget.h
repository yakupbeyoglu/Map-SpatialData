#pragma once
#include <QtWidgets>
#include <QVector>
class CustomWidget : public QWidget
{
   QPoint m_mousePos;
   QVector<QRect> rectangles;
   QVector<QRect> storagerectangles;

public:
   explicit CustomWidget(QWidget *parent = nullptr) : QWidget{parent} {
           this->setMouseTracking(true);
           this->setMinimumSize(700,700);
   }
   void paintEvent(QPaintEvent *) override {

           QPainter painter(this);
           painter.setPen(QPen{Qt::black, 3, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin});

            for(auto &l : rectangles){
                painter.drawEllipse(l);
            }

           //painter.drawRect(r2);
        }

   void mousePressEvent(QMouseEvent *event) override {
      m_mousePos = event->pos();
      if(event->button() == Qt::LeftButton)
          rectangles.push_back(QRect{QPoint(m_mousePos.x(),m_mousePos.y()), QSize(100,100)});
      else if (event->button() == Qt::RightButton){
              storagerectangles = rectangles;
              rectangles.clear();
      }
      update();
   }
};

