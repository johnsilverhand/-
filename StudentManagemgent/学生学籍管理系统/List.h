#pragma once
#include"Student.h"
#include <iostream>
using namespace std;
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>

//建立链表节点的结构体

struct stuNode
{
	stu stuData;
	stuNode* next;
};
//链表的作用主要用于查找学生，分类显示，学生排序等。
//将头节点作为私有数据成员
class List
{
public:
	List() { head = new stuNode; head->next = NULL; }//初始化头节点
	void Clear();//清空链表
	void createList();//创造链表
	void createList(string File);//创造链表:用于导入功能
	void sortList(char chio);//链表排序
	void saveList();//将链表的数据存储会dat文件中
	void saveList(string File);//将链表的数据存储会dat文件中：用于导入功能
	void displayList();//显示链表中的数据
	void displayList(int classForDisplay);//重载函数显示链表中特定班级的学生数据
	stuNode* getHead() { return head; }//获取头节点
	~List() { Clear(); delete head; head = NULL; };//析构函数
private:
	stuNode* head;//头节点
};