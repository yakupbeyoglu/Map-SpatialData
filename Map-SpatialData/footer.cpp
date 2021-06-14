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

void Footer::SetMessagebox(const QString &query) {
        textedit->insertPlainText(QString::number(index)+".Query = " + query+'\n');
        index++;
}

void Footer::SetMessagebox(const QString &query, const Application::Types::DataSet &id,
                           const Application::Types::DataSet &name, const Application::Types::DataSet &location) {

        textedit->insertPlainText(QString::number(index)+".Query = " + query+"\n Result :\n");

       QStringList list;
       int size = 0;
       if(!id.empty()){
               for(auto &l:id){
                        list.push_back(l.id+" ");
               }
       }
       if(!name.empty()) {
               if(!list.empty())
                       for(int i=0 ;i<list.size();i++)
                                list[i]= list[i]+" "+ name[i].name;
               else
                       for(auto &l:name){
                               list.push_back(l.name+" ");
                       }
       }
       if(!location.empty()) {
               if(!list.empty())
                       for(int i=0 ;i<list.size();i++)
                                list[i]= list[i]+" ("+ QString::number(location[i].point.x) + ','
                                         + QString::number(location[i].point.y) + ')';
               else
                       for(auto &l:location)
                               list.push_back('(' + QString::number(l.point.x) + ','
                                              + QString::number(l.point.y) + ')');
      }

       for(auto &l : list) {
                        textedit->insertPlainText(l + "\n");
       }

       textedit->insertPlainText("\n\n");


}

void Footer::SetQuery(const QString query) {
        SetMessagebox(query);

}
