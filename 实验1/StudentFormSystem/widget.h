#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"studentMes.h"
#include"studentNode.h"
#include"studentlist.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void initWidget(studentNode<studentMes>* p);

    //异常判断
    //输入框为空
    bool checkIsEmpty(QString str,QString mes);
    //输入框为大于0的整数
    bool checkIsznum(QString str,QString mes);
private slots:
    void on_pushButton_add_clicked();

    void on_pushButton_sch_clicked();

    void on_pushButton_display_clicked();

    void on_pushButton_del_clicked();

    void on_pushButton_modify_clicked();

    void on_pushButton_sort_clicked();

    void on_pushButton_clicked();

    void on_pushButton_insert_clicked();

private:
    Ui::Widget *ui;
    studentList<studentMes> *stulist;
    QString filename;

};
#endif // WIDGET_H
