#ifndef SIDEWIDGET_H
#define SIDEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QDebug>
#include <QCheckBox>
#include <QRadioButton>
#include <QPushButton>

class SideWidget : public QWidget
{
        Q_OBJECT

public:
        explicit SideWidget(QWidget *parent = nullptr);
        ~SideWidget();
        void SetCoordination(const QPoint &point);

public slots :
        void GetCoordination(const QPoint &point);
        void busstopschanged(int state);
        void passengerschanged(int state);
        void GetAllPoints(bool state);
        void CovarageChanged();
        void SelectedBoxChanged(bool state);
signals :
        void buseventcall(int state);
        void passengereventcall(int state);
        void wholeareaselection(bool busstate, bool passengerstate);
        void CovaregeClicked();
        void SelectedBoxSelection(bool state);
private:
        QVBoxLayout *vlayout;

        QHBoxLayout *pointbox;

        QVBoxLayout *featurelayout;

        QCheckBox *busstops;
        QCheckBox *passenger;

        QLabel *activelabel;
        QLabel *activeregionlabel;

        QRadioButton *wholearea;
        QRadioButton *selectedbox;
        QRadioButton * selectedpolygon;

        QPushButton *submitrangequery;
        QPushButton *submitpointquery;
        QPushButton *checkcoverage;

        QLabel *coordinates;
        QVBoxLayout *coordinatelayout;
        QLineEdit *x;
        QLineEdit *y;

};

#endif // SIDEWIDGET_H
