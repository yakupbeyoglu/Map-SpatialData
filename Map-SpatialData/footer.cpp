#include "footer.h"
Footer::Footer(QWidget *parent) : QWidget(parent)
{
        panel = new QHBoxLayout();
        textedit = new QTextEdit();
        panel->addWidget(textedit);
        setLayout(panel);
        textedit->setReadOnly(true);
        this->setMinimumWidth(700);
        QPalette pal = this->palette();
        pal.setColor(QPalette::Background, Qt::gray);
        this->setAutoFillBackground(true);
        this->setPalette(pal);

}

Footer::~Footer(){

}
void Footer::Setmessagebox(const QString &query) {
        textedit->insertPlainText(query);
}

void Footer::SetQuery(const QString query) {
        Setmessagebox(query);

}
