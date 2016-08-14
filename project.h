#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>  //only for clearing the interface when we want
using namespace std;
class Users
{
		int type;
		string password;
		int id;
		long int credit;
		public:
		string name;
		bool updatepassword();			
		void modifyaccountbalance();
		int returnid();
		long int returncredit();
		bool deductcredit(long int amount);
		bool validloginadmin(string s);
		bool validlogincustomer(int id,string inputpassword);
		void signup(string name,string pass,int &usercount);
		void viewtransactions();
};
class Mall
{
		string password;
		long int income;
		public:
		string mallname;
		int mallid;
		void increasecredit(long int n);
		bool validloginmart(int id,string inputpass);
		long int returnincome();
		void viewbills();
		void viewproducts(int type);
		void viewnewproducts(int type);
		void editproducts(int type);
};
class Products
{
		int id;
		string name;
		long int buyprice[3];
		long int sellprice[3];
		public:
		void buy_product(int type,Users active);
		void addnew(int j,string productnew);
};
void printmallranks();
int validinput(int type_num);



