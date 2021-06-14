#include "customwidget.h"

void CustomWidget::SetBusses(Application::Types::DataSet busses) {
        bussesdata = busses;
        for(auto &l:bussesdata) {
                bussesrectangles.push_back(QRect{QPoint(l.point.x-5,l.point.y-3), QSize(10,10)});
        }
        update();
}

void CustomWidget::SetPassenger(Application::Types::DataSet passenger){
        passengersdata = passenger;
        for(auto &l:passengersdata) {
                passengerrectangles.push_back(QRect{QPoint(l.point.x-5,l.point.y-3), QSize(10,10)});
        }


}

void CustomWidget::BusStateChange(bool state) {
        showbusses = state;
        update();
}

void CustomWidget::PassengerStateChange(bool state) {
        showpassangers = state;
        update();

}
