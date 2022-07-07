#ifndef STUDENTLIST_H
#define STUDENTLIST_H


//程序名：studentlist.h
//      程序功能：定义学生健康管理系统的链表类以及相关函数（新建，添加，插入，删除，修改，排序
//               ，查询，输出以及文件的写入和读取）
//          作者：huyuliang
//          日期：2021.10,17
//          版本：1.0
//      修改内容：无
//      修改日期：
//      修改作者：
//
//
//
#include"studentMes.h"
#include"studentNode.h"
#include<QString>
#include<iostream>
using namespace std;

//用模板定义的链表类
template<class T>
class studentList
{
private:
    //头指针
    studentNode<T>* head;

    //将文件读入的QByteArray数据类型转化为QString
    QString byteArrayToUnicode(const QByteArray &array);

public:


    studentList();

    ~studentList();

        //2------向学生健康表添加新的学生信息
        void addstudent(T studentmes);

        //3------向学生健康表插入新的学生信息（按位置号来描述插入点）
        bool insertstudent(int pos, T studentmes);

        //4------在健康表删除指定学生的信息（按学号操作）
        bool deletestudent(QString num);

        //5------为某个学生修改身体状况信息（按学号操作）
        bool modifystudent(QString findnum,T studentmes);

        //6------按学生的学号排序并显示结果
        void sortstudent();

        //7------在健康表中查询学生信息（按学生学号来进行查找）
        studentNode<T>* findstudent(QString num);

        //8------在屏幕中输出全部学生信息
        void displaylist();

        //9------从文件中读取所有学生健康表信息
        void writeFile(QString filename);

        //10------向文件写入所有学生健康表信息
        bool readFile(QString filename);


        void getList(QVector<studentNode<T>*>& vec);

        //其他辅助函数

        //比较两个数字字符串的大小
        int comparenum(QString a, QString b);

        //求出链表的长度
        int listlength();

};


#endif // STUDENTLIST_H
