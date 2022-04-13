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

//menu函数中对应的8个函数
void exit() {
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "感谢使用本系统,欢迎下次使用" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	system("pause");
	exit(0);
}

void del()
{
	fstream file, file1;
	cout << "请按操作所对应字母来进行操作：（a）删除全部学生 （b）删除特定学生" << endl;
	char chio;
	cin >> chio;
	if (chio == 'a') {
		file.open("student.dat", ios::out | ios::binary);//删除全部内容 
		cout << "删除全部学生的信息成功" << endl;
		file.close();

	}
	else if (chio == 'b') {
		file.open("student.dat", ios::binary | ios::in);//打开文件
		file1.open("middle.dat", ios::binary | ios::out);//打开中间文件
		if (!file)
		{
			cout << "无法打开文件：student.dat";
			exit(0);
		}
		if (!file1)
		{
			cout << "无法打开文件：middle.dat";
			exit(0);
		}
		int deleId;
		stu p;
		cout << "请输入要删除的学号:";
		cin >> deleId;

		while (!file.eof())//循环将除了要删除的学生之外的学生信息存入中间文件
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
		file.open("student.dat", ios::out | ios::binary);//改变打开方式
		file1.open("middle.dat", ios::in | ios::binary);
		while (!file1.eof())//将中间文件存入原文件
		{
			file1.read((char*)&p, sizeof(p));
			if (file1.fail())
				break;
			file.write((char*)&p, sizeof(p));
		}
		file.close();
		file1.close();
		cout << "删除成功！" << endl;
		file1.open("middle.dat", ios::binary | ios::out);//中间文件删除全部内容 
		file1.close();
	}
	else { cout << "输入无效字母,请返回菜单进行操作" << endl; }

}

void edit()
{
	fstream student;
	stu Student;              //作为修改数据的中转站 
	int mId;
	char mSex;
	student.open("student.dat", ios::in | ios::out | ios::binary);
	if (!student)
	{
		cout << "不能打开文件：student.dat";
		exit(0);
	}
	int editid, ID;
	cout << "请输入要修改数据的学生的学号:";
	cin >> editid;
	student.seekp(0L, ios::beg);
	long  current_position = 0;   //获取修改学生数据的位置 
	int bulr = 0;               //判断是否找到所要修改的学生
	while (!student.eof())
	{
		student.read((char*)&Student, sizeof(Student));
		current_position += student.tellg();
		student.seekg(current_position - sizeof(Student), ios::beg);

		ID = Student.sutId;
		if (editid == ID)
		{
			bulr = 1;           //判断是否找到所要修改的学生
			cout << "姓名:";
			cout << Student.name << endl;

			cout << "学号:";
			cout << Student.sutId << endl;
			cout << "年龄:";
			cout << Student.age << endl;
			if (Student.sex == 'm') {
				cout << "性别:男  " << endl;
			}
			if (Student.sex == 'f') {
				cout << "性别:女  " << endl;
			}
			cout << "请输入要修改的信息:" << endl;
			cout << "学号(请输入9位整数):";
			while (1) {
				cin >> mId;
				if (get_length(mId) == 9)break;
				else {
					cout << "你并未输入正确的学号格式，请重新输入。" << endl;
				}
			}
			Student.sutId = mId;

			cout << "姓名" << endl;
			cin >> Student.name;
			cout << "年龄:" << endl;
			cin >> Student.age;
			cout << "性别：" << endl;
			//判断输入性别的代替字母是否合规
			while (1) {
				cin >> mSex;
				if (mSex == 'm' || mSex == 'f')break;
				else {
					cout << "你并未输入m或f作为该学生的性别，请重新输入。" << endl;
				}
			}
			Student.sex = mSex;


			student.write((char*)&Student, sizeof(Student));

			break;
		}
	}
	cout << endl;
	cout << "修改完毕" << endl;
	student.close();
}

void search()
{
	fstream student;
	stu Student;
	student.open("student.dat", ios::in | ios::binary);
	if (!student) {
		cout << "不能打开文件：student.dat";
		exit(0);
	}
	int key, hole;

	cout << "请输入要查询的学生的学号:";
	cin >> key;
	student.read((char*)&Student, sizeof(Student));
	while (!student.eof())
	{
		hole = Student.sutId;
		if (hole == key)
		{
			cout << "姓名:";
			cout << Student.name << endl;
			cout << "学号:";
			cout << Student.sutId << endl;
			cout << "年龄:";
			cout << Student.age << endl;
			if (Student.sex == 'm') {
				cout << "性别:男  " << endl;
			}
			if (Student.sex == 'f') {
				cout << "性别:女  " << endl;
			}
		}
		cout << endl;
		student.read((char*)&Student, sizeof(Student));
	}
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "~~~~~~已显示出所有符合你所查询的学生的信息~~~~~~~~~." << endl
		<< "若未显示出学生信息则表示系统没有您所查询学生的信息." << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cin.ignore();
	student.close();

}
void sort()
{
	cout << "欢迎使用学生排序功能" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~ " << endl
		<< "请问您以何为根据进行排序?" << endl << "根据学号降序请按‘s’" << endl
		<< "根据学号升序请按‘d’" << endl << "~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;
	char chio;
	cin >> chio;
	//通过链表进行排序操作
	List sortList;
	sortList.createList();
	sortList.sortList(chio);
	sortList.saveList();
	cout << "排序成功" << endl;
	sortList.displayList();
}
void show()
{
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~ " << endl
		<< "欢迎使用显示学生功能" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~ " << endl
		<< "请问您是显示全部学生\n还是显示特定学生群体?" << endl << "显示全部学生请按‘s’" << endl
		<< "显示特定学生群体请按‘d’" << endl << "~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;
	List showList;
	char chio, sortchio;
	cin >> chio;
	showList.createList();
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~ " << endl
		<< "请问您以何为根据进行排序?" << endl << "根据学号降序请按‘s’" << endl
		<< "根据学号升序请按‘d’" << endl << "~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;
	cin >> sortchio;
	showList.sortList(sortchio);
	if (chio == 's') {
		showList.displayList();
	}
	if (chio == 'd') {
		int showClass;
		cout << "目前只能查找特定班级，请输入特定班级（即学号前七位）" << endl;
		cin >> showClass;
		showList.displayList(showClass);
		cout << "已输出所有符合条件的信息" << endl;
		showList.~List();

	}
}
void clear()
{
	cout << "即将进行清屏操作" << endl;
	system("cls");
}

void exportStuList()
{
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "欢迎使用导出文件功能，本功能会将学生信息导出为一个txt文档" << endl
		<< "~~~~~~~~~~~~导出文件前，请选择学生名单如何排序~~~~~~~~~~~~~" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	sort();
	fstream inFile;
	ofstream outFile;
	inFile.open("student.dat", ios::in || ios::out || ios::binary);
	outFile.open("../OutFile.txt");
	if (!inFile) {
		cout << "不能打开文件：student.dat";
		exit(0);
	}
	if (!outFile) {
		cout << "不能打开文件：OutFile.txt";
		exit(0);
	}
	stu source;
	outFile << left << setw(9) << "姓名：";
	outFile << left << setw(12) << "学号：";
	outFile << left << setw(4) << "性别：";
	outFile << left << setw(4) << "年龄：" << endl;
	while (!inFile.eof()) {
		inFile.read((char*)&source, sizeof(source));
		if (inFile.fail())
			break;

		outFile << left << setw(9) << source.name;
		outFile << left << setw(12) << source.sutId;
		if (source.sex == 'm')
			outFile << left << setw(4) << "男   ";
		if (source.sex == 'f')
			outFile << left << setw(4) << "女   ";
		outFile << left << setw(4) << source.age << endl;
	}
	inFile.close();
	outFile.close();
	cout << "导出成功！请前往查看存放该应用程序的文件夹找到名为”OutFile.txt“的导出文件" << endl;
}

void importStuList()
{
	fstream  importTarget;
	string fileName;
	cout << "欢迎使用导入功能，该功能目前只支持导入运行该系统得出的dat文件" << endl << "一般来说该系统运行的dat文件与该系统源码存储在相同文件夹" << endl;
	cout << "请输入导入文件的路径名" << endl;
	cin >> fileName;
	importTarget.open("student.dat", ios::app || ios::binary);         //使用app进行添加
	if (!importTarget) {
		cout << "无法打开文件：student.dat";
		exit(0);
	}
	List importList;                        //利用List类进行文件写入
	importList.createList(fileName);
	importList.saveList(fileName);
	importTarget.close();
	cout << "导入成功" << endl;
}

void add()
{
	fstream student;
	int mId;
	char mSex;

	student.open("student.dat", ios::app | ios::binary);
	if (!student) {
		cout << "不能打开文件：student.dat";
		exit(0);
	}
	int count;
	cout << "请问你想添加几位学生的数据?" << endl; //先确定添加学生个数 
	cin >> count;
	stu* studentToAdd;
	studentToAdd = new stu[count];  //建立开辟一个结构体数组的内存 
	for (int i = 0; i < count; i++)
	{
		cout << "请输入第 " << i + 1 << " 个学生的姓名:";
		cin.get();
		cin.getline(studentToAdd[i].name, 20);
		cout << "请输入第 " << i + 1 << " 个学生的学号(学号格式为9位数字):";
		//判断输入学号的格式是否合规
		while (1) {
			cin >> mId;
			if (get_length(mId) == 9)break;
			else {
				cout << "你并未输入正确的学号格式，请重新输入。" << endl;
			}
		}
		studentToAdd[i].sutId = mId;
		cout << "请输入第 " << i + 1 << " 个学生的性别（ 男则输入m, 女则输入f ）:";  //由于中文单字由2或3个字节组成，无法看成单字符，故先用m和f指代。
		//判断输入性别的代替字母是否合规
		while (1) {
			cin >> mSex;
			if (mSex == 'm' || mSex == 'f')break;
			else {
				cout << "你并未输入m或f作为该学生的性别，请重新输入。" << endl;
			}
		}
		studentToAdd[i].sex = mSex;
		cout << "请输入第 " << i + 1 << " 个学生的年龄:";
		cin >> studentToAdd[i].age;

		student.write((char*)&studentToAdd[i], sizeof(studentToAdd[i]));  //存入数据 
	}
	cout << "数据输入完毕.";
	cout << endl;
	delete[]studentToAdd;
	student.close();
}