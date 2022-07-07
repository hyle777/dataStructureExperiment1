//程序名：studentlist.cpp
//      程序功能：实现学生健康管理系统的各功能对应的相关函数（新建，添加，插入，删除，修改，排序
//                 ，查询，输出以及文件的写入和读取）
//          作者：huyuliang
//          日期：2021.10,17
//          版本：1.0
//      修改内容：无
//      修改日期：
//      修改作者：
//
//
//
#include"studentlist.h"
#include<QString>
#include<QDebug>
#include<QFile>
#include<QTextCodec>

//////////////////////////////////////////////////////////////////////////////
//    默认构造函数
//    函数功能：将表头指针初始化为空
//函数参数：无
//参数返回值：无
template<class T>
studentList<T>::studentList() { head = 0; }

//////////////////////////////////////////////////////////////////////////////
//    析构函数
//    函数功能：将链表空间释放，遍历每个节点 delete
//函数参数：无
//参数返回值：无
template<class T>
studentList<T>::~studentList()
{
    studentNode<T>* p=head;
    while (p != 0){
        studentNode<T>* q = p->next;
        delete p;
        p=q;
    }
}

//////////////////////////////////////////////////////////////////////////////
//  添加学生函数
//  函数功能：2------向学生健康表添加新的学生信息 头插法
//函数参数：
//       num 学生学号
//       student 学生的其他信息
//参数返回值：无
template<class T>
void studentList<T>::addstudent(T studentmes)
{
    //节点申请空间
    studentNode<T>* p = new studentNode<T>();
    p->data = studentmes;
    //头插法
    p->next = head;
    head = p;
}

//////////////////////////////////////////////////////////////////////////////
//  插入学生函数
//  函数功能：3------向学生健康表插入新的学生信息（按位置号来描述插入点）
//函数参数：
//       num 学生学号
//		 pos 插入的位置号
//       student 学生的其他信息
//参数返回值：
//       true  插入成功
//       false 插入失败
template<class T>
bool studentList<T>::insertstudent(int pos, T studentmes)
{
    //序号为pos的位置插入
    //节点申请空间
    studentNode<T>* newnode = new studentNode<T>();
    newnode->data = studentmes;

    //第一个位置插入 特殊处理
    if (pos == 1) { this->addstudent(studentmes); return true; }

    studentNode<T>* p = head;

    //可插入的最大位置
    int maxpos = listlength() + 1;
    if (pos > maxpos) return false;

    //pos=maxpos+1-pos;
    //找到pos位置前面的节点
    for (int i = 1; i < pos-1&&p->next!=0; i++) p = p->next;
    newnode->next = p->next;
    p->next = newnode;
    return true;
}

//////////////////////////////////////////////////////////////////////////////
//  删除学生函数
//  函数功能：4------在健康表删除指定学生的信息（按学号操作）
//函数参数：
//       num 学生学号
//参数返回值：
//		 true  删除成功
//      false  删除失败
template<class T>
bool studentList<T>::deletestudent(QString num)
{
    studentNode<T>* p = head;
    if(p==0) return false;
    //删除的是头节点 特殊处理
    if (p->data.num==num) { head = head->next; delete p; return true;}
    p = head->next;
    studentNode<T>* q = head;
    while (p != 0)
    {
        if (p->data.num==num) {
            q->next = p->next;
            delete p;
            return true;
        }
        p = p->next;
        q = q->next;
    }
    return false;
}

//////////////////////////////////////////////////////////////////////////////
//  修改学生信息函数
//  函数功能：5------为某个学生修改身体状况信息（按学号操作）
//函数参数：
//       num 学生学号
//       newnum 学生的新学号
//       student 学生的新信息
//参数返回值：
//       true  修改成功
//       false 修改失败，该学生不存在
template<class T>
bool studentList<T>::modifystudent(QString findnum,T studentmes)
{
    studentNode<T>* p = head;
    while (p != 0)
    {
        if (p->data.num==findnum) {
            p->data=studentmes;
            return true;
        }
        p = p->next;
    }
    return false;
}





//////////////////////////////////////////////////////////////////////////////
//  排序函数
//  函数功能：6------按学生的学号排序（按学号从小到大）冒泡排序
//函数参数：无
//参数返回值：无
template<class T>
void studentList<T>::sortstudent()
{
    studentNode<T>* p = head;
    //冒泡排序
    while (p->next != 0)
    {
        studentNode<T>* q = p->next;
        while (q!= 0)
        {
            //p的学号大于q的学号 交换两个节点的数据
            if (comparenum(p->data.num, q->data.num) == 1) swapNode(p, q);
            q = q->next;
        }
        p = p->next;
    }
}

//////////////////////////////////////////////////////////////////////////////
//  查找函数
//  函数功能：7------在健康表中查询学生信息（按学生学号来进行查找）
//函数参数：
//       num 学生学号
//参数返回值：
//  0:空指针 找不到
//  p:要找的学生节点的地址
template<class T>
studentNode<T>* studentList<T>::findstudent(QString num)
{
    studentNode<T>* p = head;
    while (p != 0)
    {
        if (p->data.num==num) {
            return p;
        }
        p = p->next;
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////
//  显示函数
//  函数功能：8------在屏幕中输出全部学生信息
//函数参数：无
//参数返回值：无
template<class T>
void studentList<T>::displaylist()
{
    qDebug()<< "\t学号\t"<< "姓名\t" << "出生年月日\t" << "性别\t" << "身体状况" << endl;
    studentNode<T>* p = head;
    while (p != 0)
    {
        qDebug() <<"\t"<< p->num <<"\t"<< p->data << endl;
        p = p->next;
    }
}

template<class T>
void studentList<T>::getList(QVector<studentNode<T>*>& vec)
{
    studentNode<T>* p=head;
    while(p!=0)
    {
        vec.push_back(p);
        p=p->next;
    }

}

//////////////////////////////////////////////////////////////////////////////
//  文件写入学生信息函数
//  函数功能：9------从文件中读取所有学生健康表信息
//函数参数：无
//参数返回值：无
template<class T>
void studentList<T>::writeFile(QString filename)
{
    QFile file(filename);
    file.open(QIODevice::WriteOnly);
    studentNode<T>* p = head;
    QString str;
    while (p != 0)
    {
        str=str+p->data.num+" "+p->data.name+" "+p->data.sex+" "+p->data.birthday+" "
                +p->data.health+"\n";
        p=p->next;
    }
    file.write(str.toLocal8Bit());
    file.close();
}

//////////////////////////////////////////////////////////////////////////////
//  文件读取学生信息函数
//  函数功能：10------向文件读取所有学生健康表信息
//函数参数：无
//参数返回值：
//       true 读取成功
//      false 读取失败
template<class T>
bool studentList<T>::readFile(QString filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug()<<"文件打开失败！"<<endl;
        return false;}

    //读取文件的一行
    QByteArray con=file.readLine();
    //格式转换 不然会出现中文乱码的现象
    QString str=byteArrayToUnicode(con);

    if(str=="") return true;
    T data;
    //初始化头节点和尾节点
    data.init(str);
    addstudent(data);
    studentNode<T>* tail = head;


    con=file.readLine();
    str=byteArrayToUnicode(con);
    while(str!=""&&str!="\n")
    {
    data.init(str);
    //尾插入法
    studentNode<T>* newnode = new studentNode<T>();
    newnode->data = data;
    newnode->next = 0;
    tail->next = newnode;
    tail = newnode;
    con=file.readLine();
    str=byteArrayToUnicode(con);
    }


    return true;
}


//////////////////////////////////////////////////////////////////////////////
//  比较函数
//  函数功能：笔记两个学号的大小顺序
//函数参数：
//       a 字符串a
//       b 字符串b
//参数返回值：
//     1： 表示a>b
//     0： 表示a=b
//    -1： 表示a<b
template<class T>
int studentList<T>::comparenum(QString a, QString b)
{
    if (a.length() > b.length()) return 1;
    if (a.length() < b.length()) return -1;
    for (int i = 0; a[i] != 0; i++)
    {
        if (a[i] > b[i]) return 1;
        if (a[i] < b[i]) return -1;
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////
//  求链表长度函数
//  函数功能：求出链表的长度
//函数参数：无
//参数返回值：
//       cnt 链表的长度
template<class T>
int studentList<T>::listlength()
{
    studentNode<T>* p = head;
    int cnt = 0;
    while (p != 0)
    {
        cnt++;
        p = p->next;
    }
    return cnt;
}

template<class T>
QString studentList<T>::byteArrayToUnicode(const QByteArray &array)
{
    // state用于保存转换状态，它的成员invalidChars，可用来判断是否转换成功
    // 如果转换成功，则值为0，如果值大于0，则说明转换失败
    QTextCodec::ConverterState state;
    // 先尝试使用utf-8的方式把QByteArray转换成QString
    QString text = QTextCodec::codecForName("UTF-8")->toUnicode(array.constData(), array.size(), &state);
    // 如果转换时无效字符数量大于0，说明编码格式不对
    if (state.invalidChars > 0)
    {
        // 再尝试使用GBK的方式进行转换，一般就能转换正确(当然也可能是其它格式，但比较少见了)
        text = QTextCodec::codecForName("GBK")->toUnicode(array);
    }
    return text;
}
