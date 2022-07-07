#ifndef STUDENTMES_H
#define STUDENTMES_H
#include<QString>
//学生信息的结构
struct studentMes {
    //姓名、出生日期、性别、身体状况
    QString num;//学号
    QString name;
    QString sex;
    QString birthday;
    QString health;

    studentMes(){}

    studentMes(QString num,QString name,QString sex,QString birthday,QString health)
    {
        this->num=num;
        this->name=name;
        this->sex=sex;
        this->birthday=birthday;
        this->health=health;
    }


    studentMes& operator=(studentMes& x) {
        num=x.num;
        name=x.name;
        birthday=x.birthday;
        sex=x.sex;
        health=x.health;
        return *this;
    }

    bool stop(QChar c)
    {
        if(c==' '||c=='\t') return true;
        return false;
    }

    void init(QString str)
    {
        QString t="";
        int i=0;
        while(stop(str[i])&&str[i]!='\n') i++;
        while(!stop(str[i])&&str[i]!='\n'){
            t+=str[i];i++;
        }
        this->num=t;
        t="";

        while(stop(str[i])&&str[i]!='\n') i++;
        while(!stop(str[i])&&str[i]!='\n'){
            t+=str[i];i++;
        }
        this->name=t;
        t="";

        while(stop(str[i])&&str[i]!='\n') i++;
        while(!stop(str[i])&&str[i]!='\n'){
            t+=str[i];i++;
        }
        this->sex=t;
        t="";

        while(stop(str[i])&&str[i]!='\n') i++;
        while(!stop(str[i])&&str[i]!='\n'){
            t+=str[i];i++;
        }
        this->birthday=t;
        t="";

        while(stop(str[i])&&str[i]!='\n') i++;
        while(!stop(str[i])&&str[i]!='\n'){
            t+=str[i];i++;
        }
        this->health=t;
//        if(str!="\n"){
//        this->num=str.mid(0,str.indexOf(' '));
//        str.remove(0,str.indexOf(' ')+1);}
//        if(str!="\n"){
//        this->name=str.mid(0,str.indexOf(' '));
//        str.remove(0,str.indexOf(' ')+1);}
//        if(str!="\n"){
//        this->sex=str.mid(0,str.indexOf(' '));
//        str.remove(0,str.indexOf(' ')+1);}
//        if(str!="\n"){
//        this->birthday=str.mid(0,str.indexOf(' '));
//        str.remove(0,str.indexOf(' ')+1);}
//        if(str!="\n"){
//        this->health=str.mid(0,str.indexOf(' '));
//        str.remove(0,str.indexOf(' ')+1);}
    }

};
#endif // STUDENTMES_H
