#include "widget.h"
#include "ui_widget.h"
#include"studentlist.h"
#include"studentlist.cpp"
#include<QMessageBox>
#include<QFileDialog>
#include<QElapsedTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    stulist=0;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initWidget(studentNode<studentMes>* p)
{

    //列表控件初始化
    //设置列数
    ui->tableWidget->setColumnCount(5);

    //设置水平表头
    QStringList qsl;
    qsl<<"学号"<<"姓名"<<"性别"<<"出生日期"<<"健康情况";
    ui->tableWidget->setHorizontalHeaderLabels(qsl);

    if(p!=0)
    {
        ui->tableWidget->setRowCount(1);
        ui->tableWidget->setItem(0,0,new QTableWidgetItem(p->data.num ));
        ui->tableWidget->setItem(0,1,new QTableWidgetItem(p->data.name));
        ui->tableWidget->setItem(0,2,new QTableWidgetItem(p->data.sex));
        ui->tableWidget->setItem(0,3,new QTableWidgetItem(p->data.birthday));
        ui->tableWidget->setItem(0,4,new QTableWidgetItem(p->data.health));
        return;
    }
    //设置行数
    ui->tableWidget->setRowCount(stulist->listlength());
    QElapsedTimer timer;
    timer.start();
    QVector<studentNode<studentMes>*> vec;
    stulist->getList(vec);
    //设置正文
    for(int i=0;i<vec.size() ;i++)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(vec.at(i)->data.num ));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(vec.at(i)->data.name));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(vec.at(i)->data.sex));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(vec.at(i)->data.birthday));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(vec.at(i)->data.health));
    }

    if(filename!="")
        stulist->writeFile(filename);
     qDebug()<<"更新窗口时间为"<<timer.elapsed()/1000.0<<"s"<<endl;
}


void Widget::on_pushButton_add_clicked()
{
    if(checkIsEmpty(filename,"请先选择文件进行操作")) return;
    QString num=ui->lineEdit_num->text();
    if(checkIsEmpty(num,"添加的学生学号不能为空！")) return;
    QString name=ui->lineEdit_name->text();
    QString sex=ui->lineEdit_sex->text();
    QString birthday=ui->lineEdit_birthday->text();
    QString health=ui->lineEdit_health->text();
    //学生学号不能重复
    if(stulist->findstudent(num)!=0)
    {
        QMessageBox::critical(this,"错误","要添加学生的学号已经存在");return;
    }
    studentMes studentmes(num,name,sex,birthday,health);
    stulist->addstudent(studentmes);
    initWidget(0);
}

void Widget::on_pushButton_sch_clicked()
{
    if(checkIsEmpty(filename,"请先选择文件进行操作")) return;
    QString findnum=ui->lineEdit_findnum->text();

    studentNode<studentMes>* p=stulist->findstudent(findnum);
    if(p==0){
        QMessageBox::critical(this,"错误","要查找学生的学号不存在");return;
    }
    initWidget(p);
}

void Widget::on_pushButton_display_clicked()
{
    if(checkIsEmpty(filename,"请先选择文件进行操作")) return;
    initWidget(0);
}

void Widget::on_pushButton_del_clicked()
{
    if(checkIsEmpty(filename,"请先选择文件进行操作")) return;
    QString findnum=ui->lineEdit_findnum->text();

    if(!stulist->deletestudent(findnum))
    {
         QMessageBox::critical(this,"错误","要删除学生的学号不存在");return;
    }

    initWidget(0);

}

void Widget::on_pushButton_modify_clicked()
{
    if(checkIsEmpty(filename,"请先选择文件进行操作")) return;
    QString modifynum=ui->lineEdit_modifynum->text();
    QString num=ui->lineEdit_num->text();
    QString name=ui->lineEdit_name->text();
    QString sex=ui->lineEdit_sex->text();
    QString birthday=ui->lineEdit_birthday->text();
    QString health=ui->lineEdit_health->text();
    studentMes studentmes(num,name,sex,birthday,health);
    if(!stulist->modifystudent(modifynum,studentmes))
    {
        QMessageBox::critical(this,"错误","在学号栏输入要修改学生的正确的学号");return;
    }
    initWidget(0);
}

void Widget::on_pushButton_sort_clicked()
{
    QElapsedTimer timer;
    timer.start();
    if(checkIsEmpty(filename,"请先选择文件进行操作")) return;
    stulist->sortstudent();
     qDebug()<<"排序完成。排序时间为"<<timer.elapsed()/1000.0<<"s"<<endl;
    initWidget(0);

}

void Widget::on_pushButton_clicked()
{
    if(stulist!=0){delete stulist;stulist=0;}
    stulist=new studentList<studentMes>;
    QString path=QFileDialog::getOpenFileName(this,"打开文件","d:\\Qtproject");
    ui->lineEdit->setText(path);
    //path.remove(0,74);
    filename=path;
    stulist->readFile(filename);
    initWidget(0);
}

void Widget::on_pushButton_insert_clicked()
{
    if(checkIsEmpty(filename,"请先选择文件进行操作！")) return;
    QString insertpos=ui->lineEdit_insertpos->text();
    if(!checkIsznum(insertpos,"插入的位置号必须是正整数！")) return;
    QString num=ui->lineEdit_num->text();
    if(checkIsEmpty(num,"插入的学生学号不能为空！")) return;
    //学生学号不能重复
    if(stulist->findstudent(num)!=0)
    {
        QMessageBox::critical(this,"错误","要插入学生的学号已经存在");return;
    }
    QString name=ui->lineEdit_name->text();
    QString sex=ui->lineEdit_sex->text();
    QString birthday=ui->lineEdit_birthday->text();
    QString health=ui->lineEdit_health->text();
    studentMes studentmes(num,name,sex,birthday,health);
    stulist->insertstudent(insertpos.toInt(),studentmes);
    initWidget(0);
}

//输入框 错误信息
bool Widget::checkIsEmpty(QString str,QString mes)
{
    if(str=="") {
        QMessageBox::critical(this,"错误",mes);return true;
    }
    return false;
}

bool Widget::checkIsznum(QString str,QString mes)
{
    int x=str.toInt();
    if(x<=0){
        QMessageBox::critical(this,"错误",mes);
        return false;
    }
    return true;
}
