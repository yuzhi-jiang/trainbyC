#include<iostream>
#include<stdio.h> 
#include<string>
#include<fstream>
using namespace std;
const int MAX = 500;
/*
每本图书的信息包括ISBN号、书名 、单价、库存量

请设计程序，至少完成书店图书的初始数据录入、修改单价或库存、按书名关键字查询图书等功能。
实验步骤
1、编写图书信息类
2、编写图书销售管理员
3、编写销售类中的函数，实现初始数据的录入（写文件）；
4、编写销售类中的函数，当输入书名关键字时，可输出书名中包含此关键字的所有图书信息。
5、编写销售类中的函数，输入ISBN号时，可修改此图书的库存（或单价）
6、编写主函数，显示主菜单，根据用户的选择，调用销售管理员的相关代码完成指定的功能；
7、测试程序。
*/
fstream shu;
void init(){
	shu.open("book.dat", ios::in | ios::out | ios::binary);
}
class Book{
	friend class XS;
public:
	string isbn;
	string name;
	double price;
	unsigned long nums;
	Book(){
	}
	Book(string isbn, string name, double price, unsigned long nums) :isbn(isbn),
		name(name), price(price), nums(nums){
	}
	void print(){
		printf("isbn:%-5s  书名:%-5s   价格:%-5.lf   库存:%lu\n", isbn, name, price, nums);
	}
	void rxiuprice(double price_){
		price = price_;
	}
	void rxiunums(unsigned long num){
		nums = num;
	}
};
int gethang(){
	int num = 0;
	shu.seekg(0, ios::end);
	num = shu.tellg() / sizeof(Book);
	return num;
}
class XS{//销售类 
	Book p[MAX];
public:
	static unsigned long totalbooks;
	void addbook(){
		string isbn;
		string name;
		double price;
		unsigned long nums;
		cout << "输入书籍的信息:" << endl;;
		cin >> isbn >> name >> price >> nums;
		Book book(isbn, name, price, nums);
		totalbooks++;
		shu.seekp((totalbooks - 1)*sizeof(Book), ios::beg);
		shu.write((char*)&book, sizeof(Book));
		shu.flush();
		cout << "size = " << totalbooks << endl;
		cout << "添加成功" << endl;
	}
	void showbook(){
		cout << "请输入书名：";
		string name;
		cin >> name;

		shu.seekg(0, ios::end);
		totalbooks = shu.tellg() / sizeof(Book);
		shu.seekg(0);
		for (int i = 0; i<totalbooks; ++i){
			Book book;
			shu.read((char*)&book, sizeof(Book));
			if (book.name == name){
				book.print();
			}
		}
	}
	void showallbook(){
		shu.seekg(0, ios::end);
		cout << "书本数 " << shu.tellg() / sizeof(Book) << endl;
		totalbooks = shu.tellg() / sizeof(Book);
		shu.seekg(0);
		for (int i = 0; i<totalbooks; ++i){
			Book book;
			shu.read((char*)&book, sizeof(Book));
			book.print();
		}		
	}
	void cinbisn(){
		shu.seekg(0, ios::end);
		int size = shu.tellg() / sizeof(Book);
		cout << "size=" << size << endl;
		string bisn;
		cout << "输入ISBN码：";
		cin >> bisn;
		Book book;
		shu.seekg(0);
		int  i = 0;
		for ( i= 0; i < size;++i)
		{
			shu.read((char*)&book, sizeof(Book));
				if (book.isbn == bisn){
					break;
				}
		}
		cout << "i=" << i << "book is " << book.isbn << "name =" << book.name << endl;
		cout << "1.修改单价\n2.修改库存" << endl;
		int cina;
		cin >> cina;
		if (cina == 1){
			double prince = 0;
			cout << "修改单价为:";
			cin >> prince;
			book.rxiuprice(prince);
			shu.seekp(sizeof(Book)*i, ios::beg);
			shu.write((char*)&book, sizeof(Book));
			shu.flush();
			cout << "修改单价成功" << endl;
		}
		else if (cina == 2){
			unsigned long nums;
			cout << "修改库存为:";
			cin >> nums;
			book.rxiunums(nums);
			shu.seekp(sizeof(Book)*i, ios::beg);
			shu.write((char*)&book, sizeof(Book));
				shu.flush();
			cout << "修改库存成功" << endl;
		}
		else
		{
			cout << "输入错误不发生修改" << endl;
		}
	}
};
unsigned long XS::totalbooks = 0;

int main(){
	init();
	if (shu.fail()){
		cout << "打开文件失败" << endl;
		exit(0);
	}
	XS xs;
	shu.seekg(0, ios::end);
	xs.totalbooks = shu.tellg() / sizeof(Book);
	cout << "size= " << xs.totalbooks << endl;
	int ch;
	while (true)
	{
		cout << "-----------------------菜单------------------------|" << endl;
		cout << "|               1.添加书本                         |" << endl;
		cout << "|               2.修改书籍                         |" << endl;
		cout << "|               3.查找书籍                         |" << endl;
		cout << "|               4.显示所有书籍                     |" << endl;
		cout << "|               5.保存并退出程序                   | " << endl;
		cout << "|--------------------------------------------------|" << endl;
		cout << "输入选项:";
		cin >> ch;
		switch (ch)
		{
		case 1:
			xs.addbook();
			cout << "size= " << xs.totalbooks << endl;
			break;
		case 2:
			xs.cinbisn();
			break;
		case 3:
			xs.showbook();
			break;
		case 4:
			xs.showallbook();
			break;
		case 5:
			shu.flush();
			shu.close();
			return 0;
		default:
			break;
		}
	}
	shu.close();
	return 0;
}
