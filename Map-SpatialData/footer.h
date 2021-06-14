#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QDebug>
#include <QCheckBox>
#include <QRadioButton>
#include <QPushButton>
#include <QTextEdit>
#include "Types.h"
class Footer : public QWidget
{
        Q_OBJECT

public:
        explicit Footer(QWidget *parent = nullptr);
        ~Footer();
        void SetMessagebox(const QString &query);


public slots :
        void SetQuery(const QString query);
        void SetMessagebox(const QString &query, const Application::Types::DataSet &id,
                           const Application::Types::DataSet &name, const Application::Types::DataSet &location);


private:

        QHBoxLayout *panel;
        QTextEdit *textedit;
        int index = 0;

};

