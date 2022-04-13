#pragma once
#include <iostream>
#include<iomanip>
#include<fstream>
#include<cstring>
#include<stdlib.h>
#include <windows.h>
#include<direct.h>
using namespace std;
#include "Student.h"
#include"List.h"


int get_length(int x) {
	int leng = 0;
	while (x) {
		x /= 10;
		leng++;
	}
	return leng;
}

//menu�����ж�Ӧ��8������
void exit() {
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "��лʹ�ñ�ϵͳ,��ӭ�´�ʹ��" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	system("pause");
	exit(0);
}

void del()
{
	fstream file, file1;
	cout << "�밴��������Ӧ��ĸ�����в�������a��ɾ��ȫ��ѧ�� ��b��ɾ���ض�ѧ��" << endl;
	char chio;
	cin >> chio;
	if (chio == 'a') {
		file.open("student.dat", ios::out | ios::binary);//ɾ��ȫ������ 
		cout << "ɾ��ȫ��ѧ������Ϣ�ɹ�" << endl;
		file.close();

	}
	else if (chio == 'b') {
		file.open("student.dat", ios::binary | ios::in);//���ļ�
		file1.open("middle.dat", ios::binary | ios::out);//���м��ļ�
		if (!file)
		{
			cout << "�޷����ļ���student.dat";
			exit(0);
		}
		if (!file1)
		{
			cout << "�޷����ļ���middle.dat";
			exit(0);
		}
		int deleId;
		stu p;
		cout << "������Ҫɾ����ѧ��:";
		cin >> deleId;

		while (!file.eof())//ѭ��������Ҫɾ����ѧ��֮���ѧ����Ϣ�����м��ļ�
		{
			file.read((char*)&p, sizeof(p));
			if (file.fail())
				break;
			if (p.sutId == deleId) {

				continue;
			}

			file1.write((char*)&p, sizeof(p));

		}
		file.close();
		file1.close();
		file.open("student.dat", ios::out | ios::binary);//�ı�򿪷�ʽ
		file1.open("middle.dat", ios::in | ios::binary);
		while (!file1.eof())//���м��ļ�����ԭ�ļ�
		{
			file1.read((char*)&p, sizeof(p));
			if (file1.fail())
				break;
			file.write((char*)&p, sizeof(p));
		}
		file.close();
		file1.close();
		cout << "ɾ���ɹ���" << endl;
		file1.open("middle.dat", ios::binary | ios::out);//�м��ļ�ɾ��ȫ������ 
		file1.close();
	}
	else { cout << "������Ч��ĸ,�뷵�ز˵����в���" << endl; }

}

void edit()
{
	fstream student;
	stu Student;              //��Ϊ�޸����ݵ���תվ 
	int mId;
	char mSex;
	student.open("student.dat", ios::in | ios::out | ios::binary);
	if (!student)
	{
		cout << "���ܴ��ļ���student.dat";
		exit(0);
	}
	int editid, ID;
	cout << "������Ҫ�޸����ݵ�ѧ����ѧ��:";
	cin >> editid;
	student.seekp(0L, ios::beg);
	long  current_position = 0;   //��ȡ�޸�ѧ�����ݵ�λ�� 
	int bulr = 0;               //�ж��Ƿ��ҵ���Ҫ�޸ĵ�ѧ��
	while (!student.eof())
	{
		student.read((char*)&Student, sizeof(Student));
		current_position += student.tellg();
		student.seekg(current_position - sizeof(Student), ios::beg);

		ID = Student.sutId;
		if (editid == ID)
		{
			bulr = 1;           //�ж��Ƿ��ҵ���Ҫ�޸ĵ�ѧ��
			cout << "����:";
			cout << Student.name << endl;

			cout << "ѧ��:";
			cout << Student.sutId << endl;
			cout << "����:";
			cout << Student.age << endl;
			if (Student.sex == 'm') {
				cout << "�Ա�:��  " << endl;
			}
			if (Student.sex == 'f') {
				cout << "�Ա�:Ů  " << endl;
			}
			cout << "������Ҫ�޸ĵ���Ϣ:" << endl;
			cout << "ѧ��(������9λ����):";
			while (1) {
				cin >> mId;
				if (get_length(mId) == 9)break;
				else {
					cout << "�㲢δ������ȷ��ѧ�Ÿ�ʽ�����������롣" << endl;
				}
			}
			Student.sutId = mId;

			cout << "����" << endl;
			cin >> Student.name;
			cout << "����:" << endl;
			cin >> Student.age;
			cout << "�Ա�" << endl;
			//�ж������Ա�Ĵ�����ĸ�Ƿ�Ϲ�
			while (1) {
				cin >> mSex;
				if (mSex == 'm' || mSex == 'f')break;
				else {
					cout << "�㲢δ����m��f��Ϊ��ѧ�����Ա����������롣" << endl;
				}
			}
			Student.sex = mSex;


			student.write((char*)&Student, sizeof(Student));

			break;
		}
	}
	cout << endl;
	cout << "�޸����" << endl;
	student.close();
}

void search()
{
	fstream student;
	stu Student;
	student.open("student.dat", ios::in | ios::binary);
	if (!student) {
		cout << "���ܴ��ļ���student.dat";
		exit(0);
	}
	int key, hole;

	cout << "������Ҫ��ѯ��ѧ����ѧ��:";
	cin >> key;
	student.read((char*)&Student, sizeof(Student));
	while (!student.eof())
	{
		hole = Student.sutId;
		if (hole == key)
		{
			cout << "����:";
			cout << Student.name << endl;
			cout << "ѧ��:";
			cout << Student.sutId << endl;
			cout << "����:";
			cout << Student.age << endl;
			if (Student.sex == 'm') {
				cout << "�Ա�:��  " << endl;
			}
			if (Student.sex == 'f') {
				cout << "�Ա�:Ů  " << endl;
			}
		}
		cout << endl;
		student.read((char*)&Student, sizeof(Student));
	}
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "~~~~~~����ʾ�����з���������ѯ��ѧ������Ϣ~~~~~~~~~." << endl
		<< "��δ��ʾ��ѧ����Ϣ���ʾϵͳû��������ѯѧ������Ϣ." << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cin.ignore();
	student.close();

}
void sort()
{
	cout << "��ӭʹ��ѧ��������" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~ " << endl
		<< "�������Ժ�Ϊ���ݽ�������?" << endl << "����ѧ�Ž����밴��s��" << endl
		<< "����ѧ�������밴��d��" << endl << "~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;
	char chio;
	cin >> chio;
	//ͨ����������������
	List sortList;
	sortList.createList();
	sortList.sortList(chio);
	sortList.saveList();
	cout << "����ɹ�" << endl;
	sortList.displayList();
}
void show()
{
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~ " << endl
		<< "��ӭʹ����ʾѧ������" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~ " << endl
		<< "����������ʾȫ��ѧ��\n������ʾ�ض�ѧ��Ⱥ��?" << endl << "��ʾȫ��ѧ���밴��s��" << endl
		<< "��ʾ�ض�ѧ��Ⱥ���밴��d��" << endl << "~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;
	List showList;
	char chio, sortchio;
	cin >> chio;
	showList.createList();
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~ " << endl
		<< "�������Ժ�Ϊ���ݽ�������?" << endl << "����ѧ�Ž����밴��s��" << endl
		<< "����ѧ�������밴��d��" << endl << "~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;
	cin >> sortchio;
	showList.sortList(sortchio);
	if (chio == 's') {
		showList.displayList();
	}
	if (chio == 'd') {
		int showClass;
		cout << "Ŀǰֻ�ܲ����ض��༶���������ض��༶����ѧ��ǰ��λ��" << endl;
		cin >> showClass;
		showList.displayList(showClass);
		cout << "��������з�����������Ϣ" << endl;
		showList.~List();

	}
}
void clear()
{
	cout << "����������������" << endl;
	system("cls");
}

void exportStuList()
{
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "��ӭʹ�õ����ļ����ܣ������ܻὫѧ����Ϣ����Ϊһ��txt�ĵ�" << endl
		<< "~~~~~~~~~~~~�����ļ�ǰ����ѡ��ѧ�������������~~~~~~~~~~~~~" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	sort();
	fstream inFile;
	ofstream outFile;
	inFile.open("student.dat", ios::in || ios::out || ios::binary);
	outFile.open("../OutFile.txt");
	if (!inFile) {
		cout << "���ܴ��ļ���student.dat";
		exit(0);
	}
	if (!outFile) {
		cout << "���ܴ��ļ���OutFile.txt";
		exit(0);
	}
	stu source;
	outFile << left << setw(9) << "������";
	outFile << left << setw(12) << "ѧ�ţ�";
	outFile << left << setw(4) << "�Ա�";
	outFile << left << setw(4) << "���䣺" << endl;
	while (!inFile.eof()) {
		inFile.read((char*)&source, sizeof(source));
		if (inFile.fail())
			break;

		outFile << left << setw(9) << source.name;
		outFile << left << setw(12) << source.sutId;
		if (source.sex == 'm')
			outFile << left << setw(4) << "��   ";
		if (source.sex == 'f')
			outFile << left << setw(4) << "Ů   ";
		outFile << left << setw(4) << source.age << endl;
	}
	inFile.close();
	outFile.close();
	cout << "�����ɹ�����ǰ���鿴��Ÿ�Ӧ�ó�����ļ����ҵ���Ϊ��OutFile.txt���ĵ����ļ�" << endl;
}

void importStuList()
{
	fstream  importTarget;
	string fileName;
	cout << "��ӭʹ�õ��빦�ܣ��ù���Ŀǰֻ֧�ֵ������и�ϵͳ�ó���dat�ļ�" << endl << "һ����˵��ϵͳ���е�dat�ļ����ϵͳԴ��洢����ͬ�ļ���" << endl;
	cout << "�����뵼���ļ���·����" << endl;
	cin >> fileName;
	importTarget.open("student.dat", ios::app || ios::binary);         //ʹ��app�������
	if (!importTarget) {
		cout << "�޷����ļ���student.dat";
		exit(0);
	}
	List importList;                        //����List������ļ�д��
	importList.createList(fileName);
	importList.saveList(fileName);
	importTarget.close();
	cout << "����ɹ�" << endl;
}

void add()
{
	fstream student;
	int mId;
	char mSex;

	student.open("student.dat", ios::app | ios::binary);
	if (!student) {
		cout << "���ܴ��ļ���student.dat";
		exit(0);
	}
	int count;
	cout << "����������Ӽ�λѧ��������?" << endl; //��ȷ�����ѧ������ 
	cin >> count;
	stu* studentToAdd;
	studentToAdd = new stu[count];  //��������һ���ṹ��������ڴ� 
	for (int i = 0; i < count; i++)
	{
		cout << "������� " << i + 1 << " ��ѧ��������:";
		cin.get();
		cin.getline(studentToAdd[i].name, 20);
		cout << "������� " << i + 1 << " ��ѧ����ѧ��(ѧ�Ÿ�ʽΪ9λ����):";
		//�ж�����ѧ�ŵĸ�ʽ�Ƿ�Ϲ�
		while (1) {
			cin >> mId;
			if (get_length(mId) == 9)break;
			else {
				cout << "�㲢δ������ȷ��ѧ�Ÿ�ʽ�����������롣" << endl;
			}
		}
		studentToAdd[i].sutId = mId;
		cout << "������� " << i + 1 << " ��ѧ�����Ա� ��������m, Ů������f ��:";  //�������ĵ�����2��3���ֽ���ɣ��޷����ɵ��ַ���������m��fָ����
		//�ж������Ա�Ĵ�����ĸ�Ƿ�Ϲ�
		while (1) {
			cin >> mSex;
			if (mSex == 'm' || mSex == 'f')break;
			else {
				cout << "�㲢δ����m��f��Ϊ��ѧ�����Ա����������롣" << endl;
			}
		}
		studentToAdd[i].sex = mSex;
		cout << "������� " << i + 1 << " ��ѧ��������:";
		cin >> studentToAdd[i].age;

		student.write((char*)&studentToAdd[i], sizeof(studentToAdd[i]));  //�������� 
	}
	cout << "�����������.";
	cout << endl;
	delete[]studentToAdd;
	student.close();
}