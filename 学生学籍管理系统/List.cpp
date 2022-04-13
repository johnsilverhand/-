#include "List.h"
#include<stdlib.h>
#include<fstream>
#include<iomanip>

int get_class(int x){  //��ȡ�༶��
	int class_stu;
	class_stu = x / 100;
	return class_stu;
}

void List::Clear(){
	stuNode* p0;
	if (head==NULL){
		return;
	}
	p0 = head->next;
	while (p0!=NULL){
		head->next = p0->next;
		delete p0;
		p0 = head->next;
	}
}
void List::createList() {
	stuNode* p, * q;
	p = new stuNode;
	head->next=p;
	q = new stuNode;
	p->next = NULL;
	//q = head;
	//q->next;
	
		//��ڵ��������
		fstream student;
		stu Student;
		student.open("student.dat", ios::in | ios::binary);
		if (!student) {
			cout << "���ܴ��ļ���student.dat";
			exit(0);
		}
		student.read((char*)&Student, sizeof(Student));
		while (!student.eof())
		{	
			//�ڵ�任
			p->stuData=Student;
			q = p;
			p = new stuNode;
			q->next = p;
			student.read((char*)&Student, sizeof(Student));
			}
		q->next = NULL;
		cin.ignore();
		student.close();	
		
}
void List::createList(string File)//���ڵ��빦��
{
	stuNode* p, * q;
	p = new stuNode;
	head->next = p;
	q = new stuNode;
	p->next = NULL;
	//q = head;
	//q->next;

		//��ڵ��������
	fstream student;
	stu Student;
	student.open(File, ios::in | ios::binary);
	if (!student) {
		cout << "���ܴ��ļ�";
		exit(0);
	}
	student.read((char*)&Student, sizeof(Student));
	while (!student.eof())
	{
		//�ڵ�任
		p->stuData = Student;
		q = p;
		p = new stuNode;
		q->next = p;
		student.read((char*)&Student, sizeof(Student));
	}
	q->next = NULL;
	cin.ignore();
	student.close();
}
void List::sortList(char chio)
{
	if (head == NULL){
		return;
	}
	if (head->next == NULL){
		return;
	}
	if (chio == 's') {        //ѧ�Ž���
		
		
		stuNode* temp_pre = head;
		stuNode* p_pre = head;
		stuNode* ex;
		//ѡ������
		for (stuNode* temp = head->next; temp != NULL; temp = temp->next){
			p_pre = temp;
			for (stuNode* p = temp->next; p != NULL; p = p->next){
				if (temp->stuData.sutId < p->stuData.sutId){
					//������޸�ָ��Ľ�����ʽ
					if (temp->next == p){      //temp��pΪ���ڽ��
						temp->next = p->next;
						p->next = temp;
						temp_pre->next = p;
					}
					else{                    //һ�����
						temp_pre->next = p;
						p_pre->next = p->next;//key step 
						p->next = temp->next;
						temp->next = p_pre->next;
						p_pre->next = temp;
					}
					ex = temp;
					temp = p;
					p = temp;
				}
				p_pre = p;
			}
			temp_pre = temp;	
		}
	}
	if (chio == 'd') {        //����

		stuNode* temp_pre = head;
		stuNode* p_pre = head;
		stuNode* ex;
		//ѡ������
		for (stuNode* temp = head->next; temp != NULL; temp = temp->next) {
			p_pre = temp;
			for (stuNode* p = temp->next; p != NULL; p = p->next) {
				if (temp->stuData.sutId > p->stuData.sutId) {
					//������޸�ָ��Ľ�����ʽ
					if (temp->next == p) {      //temp��pΪ���ڽ��
						temp->next = p->next;
						p->next = temp;
						temp_pre->next = p;
					}
					else {                    //һ�����
						temp_pre->next = p;
						p_pre->next = p->next;//key step 
						p->next = temp->next;
						temp->next = p_pre->next;
						p_pre->next = temp;
					}
					ex = temp;
					temp = p;
					p = temp;
				}
				p_pre = p;
			}
			temp_pre = temp;
		}
	}
}
void List::saveList() {
	fstream student;
	student.open("student.dat", ios::out | ios::binary);//ˢ��ԭ�ı�����
	if (!student) {
		cout << "���ܴ��ļ���student.dat";
		exit(0);
	}
	stuNode* traverseList = head->next;
	while (traverseList != NULL)
	{

		student.write((char*)&traverseList->stuData, sizeof(traverseList->stuData));
		traverseList = traverseList->next;
	}
	student.close();
}

void List::saveList(string File)  //File�����𵽱�ʶ���ã���������ʶ��Ӧ�õ����ĸ����غ���
{
	fstream student;
	student.open("student.dat", ios::app | ios::binary);//��ˢ��ԭ�ı�����
	if (!student) {
		cout << "���ܴ��ļ���student.dat";
		exit(0);
	}
	stuNode* traverseList = head->next;
	while (traverseList != NULL)
	{

		student.write((char*)&traverseList->stuData, sizeof(traverseList->stuData));
		traverseList = traverseList->next;
	}
	student.close();
}

void List::displayList()
{
	stuNode* traverseList = head->next;
	cout << left << setw(9) << "������";
	cout << left << setw(12) << "ѧ�ţ�";
	cout << left << setw(4) << "�Ա�";
	cout << left << setw(4) << "���䣺" << endl;
	while (traverseList!=NULL)
	{
		if (traverseList->stuData.sex == 'm') {
			cout << left << setw(9) << traverseList->stuData.name
				<< left << setw(12) << traverseList->stuData.sutId 
				<< "��   "
				<< left << setw(4) << traverseList->stuData.age<<endl;
				

		}
		if (traverseList->stuData.sex == 'f') {
			cout << left << setw(9) << traverseList->stuData.name
				<< left << setw(12) << traverseList->stuData.sutId
				<< "Ů   "
				<< left << setw(4) << traverseList->stuData.age << endl;
		}
		traverseList = traverseList->next;
	};
}
void List::displayList(int classForDisplay)
{
	stuNode* traverseList = head->next;
	cout << left << setw(9) << "������";
	cout << left << setw(12) << "ѧ�ţ�";
	cout << left << setw(4) << "�Ա�";
	cout << left << setw(4) << "���䣺" << endl;
	while (traverseList != NULL){
		if (get_class(traverseList->stuData.sutId) == classForDisplay)
		{
			if (traverseList->stuData.sex == 'm') {
				cout << left << setw(9) << traverseList->stuData.name
					<< left << setw(12) << traverseList->stuData.sutId
					<< "��    "
					<< left << setw(4) << traverseList->stuData.age << endl;


			}
			if (traverseList->stuData.sex == 'f') {
				cout << left << setw(9) << traverseList->stuData.name
					<< left << setw(12) << traverseList->stuData.sutId
					<< "Ů    "
					<< left << setw(4) << traverseList->stuData.age << endl;
			}
		}
		traverseList = traverseList->next;
	}
}