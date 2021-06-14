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

class Footer : public QWidget
{
        Q_OBJECT

public:
        explicit Footer(QWidget *parent = nullptr);
        ~Footer();
        void Setmessagebox(const QString &query);

public slots :
        void SetQuery(const QString query);


private:

        QHBoxLayout *panel;
        QTextEdit *textedit;

};

