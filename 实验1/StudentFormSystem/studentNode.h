#ifndef STUDENTNODE_H
#define STUDENTNODE_H
//程序名：studentnode.h
//      程序功能：定义链式结构的结点类
//          作者：huyuliang
//          日期：2021.10.17
//          版本：1.0
//      修改内容：无
//      修改日期：
//      修改作者：
//
//
//
#include<string.h>

//用模板定义的学生节点类
template<class T>
struct studentNode {
    //模板 学号 指针
    T data;
    studentNode<T>* next;

    studentNode()
    {
        T data = T();
        next = 0;
    }
    ~studentNode(){}
};

//交换两个节点除指针外的数据
template<class T>
void swapNode(studentNode<T>* a, studentNode<T>* b)
{
    studentNode<T>* t = new studentNode<T>();
    t->data = a->data; a->data = b->data; b->data = t->data;
}


#endif // STUDENTNODE_H
