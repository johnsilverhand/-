#pragma once
#include"Student.h"
#include <iostream>
using namespace std;
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>

//��������ڵ�Ľṹ��

struct stuNode
{
	stu stuData;
	stuNode* next;
};
//�����������Ҫ���ڲ���ѧ����������ʾ��ѧ������ȡ�
//��ͷ�ڵ���Ϊ˽�����ݳ�Ա
class List
{
public:
	List() { head = new stuNode; head->next = NULL; }//��ʼ��ͷ�ڵ�
	void Clear();//�������
	void createList();//��������
	void createList(string File);//��������:���ڵ��빦��
	void sortList(char chio);//��������
	void saveList();//����������ݴ洢��dat�ļ���
	void saveList(string File);//����������ݴ洢��dat�ļ��У����ڵ��빦��
	void displayList();//��ʾ�����е�����
	void displayList(int classForDisplay);//���غ�����ʾ�������ض��༶��ѧ������
	stuNode* getHead() { return head; }//��ȡͷ�ڵ�
	~List() { Clear(); delete head; head = NULL; };//��������
private:
	stuNode* head;//ͷ�ڵ�
};