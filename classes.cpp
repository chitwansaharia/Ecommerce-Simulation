#include "project.h"
bool Users::updatepassword()
{
	cout<<"ENTER THE PRESENT PASSWORD"<<endl;
	string oldpassword;
	cin>>oldpassword;
	if(oldpassword==password)
	{
		cout<<"ENTER NEW PASSWORD"<<endl;
		string newpassword;
		cin>>newpassword;
		cout<<"RENTER YOUR PASSWORD"<<endl;    
		string reenterpass;
		cin>>reenterpass;
		if(reenterpass==newpassword)			//To check that the user enters the same password twice
		{
			fstream fin("customers.txt",ios::in);
			fstream fout("temp.txt",ios::out);
			string s;
			for(int i=0;i<id-1;i++)
			{	
				getline(fin,s,'\n');
				fout<<s<<"\n";
			}
			fout<<type<<"\t"<<id<<"\t"<<name<<"\t"<<newpassword<<"\t"<<credit<<endl;
			getline(fin,s,'\n');
			while(!fin.eof())
			{	
				getline(fin,s,'\n');			//Transfers the updated information to temp.txt and then renames it to customers.txt
				fout<<s<<"\n";
			}
			remove("customers.txt");
			rename("temp.txt","customers.txt");
			cout<<"..........PASSWORD UPDATED........"<<endl;
			return true;
		}
		else
		{
			cout<<"PASSWORD MISMATCH"<<endl;
			return false;
		}
							
							
	}
	else 
	{
		cout<<"WRONG PASSWORD"<<endl;
		return false;
	}
}

void Users::modifyaccountbalance()
{
	cout<<"YOUR ACCOUNT BALANCE IS:  "<<credit<<endl;
	cout<<"DO YOU WANT TO MODIFY IT (PRESS 1 TO PROCEED ELSE PRESS 0)"<<endl;
	int custresponse;
	cin>>custresponse;
	if(custresponse==0)
	{
		return;
	}	
	else
	{
		cout<<"ENTER YOUR BOMBAY BAZAAR PASSWORD TO COMFIRM"<<endl;			//Modification only possible if password entered is correct
		string inputpass;
		cin>>inputpass;							
		if(inputpass==password)
		{	
			string dummy;
			cout<<"ENTER THE NAME OF BANK"<<endl;					//Only dummy entries of bank name, account number and password are being done
			cin>>dummy;				
			cout<<"ENTER THE ACCOUNT NUMBER"<<endl;
			cin>>dummy;
			cout<<"ENTER THE PASSWORD"<<endl;
			cin>>dummy;
			cout<<"ENTER THE AMOUNT OF MONEY TO CREDIT"<<endl;
			long int surplus;
			cin>>surplus;
			credit+=surplus;
			fstream fin("customers.txt",ios::in);
			fstream fout("temp.txt",ios::out);
			for(int i=0;i<id-1;i++)
			{	
				getline(fin,dummy,'\n');
				fout<<dummy<<"\n";
			}
			fout<<type<<"\t"<<id<<"\t"<<name<<"\t"<<password<<"\t"<<credit<<endl;
			getline(fin,dummy,'\n');
			while(!fin.eof())
			{	
				getline(fin,dummy,'\n');
				fout<<dummy<<"\n";
			}
			remove("customers.txt");
			rename("temp.txt","customers.txt");
			cout<<"..........ACCOUNT UPDATED........"<<"PRESS ANY CHARACTER TO CONTINUE"<<endl;
			char temp;
			cin>>temp;
		}
		else
		{
			cout<<"INCORRECT PASSWORD"<<endl;
			cout<<"ENTER ANY CHARACTER TO PROCEED"<<endl;
			string temp;
			cin>>temp;
		}		
	}
}

int Users::returnid()			//as id and credit are private variables
{
	return id;
}

long int Users::returncredit()
{
	return credit;
}	
		
bool Users::validloginadmin(string s)
{
	fstream fin("admin.txt",ios::in);
	string str;
	fin>>str;
	if(s==str)
	{
		return true;
	}
	else
	{
		return false;
	}
}			
bool Users::validlogincustomer(int id,string inputpassword)//for checking the validity of the customer
{	
	ifstream customer("customers.txt",ios::in);
	customer.seekg(0);
	while(!customer.eof())
	{
		customer>>type;
		customer>>this->id;
		customer>>name;
		customer>>password;
		customer>>credit;
		if(type==1&&this->id==id&&password==inputpassword)
		{	
			return true;
		}
	}
	return false;
	customer.close();
}

bool Users::deductcredit(long int amount)//for deducting the credit to complete the transaction
{										//returns false if deduction not possible because of lack of cash in account
	if(credit>=amount)
	{
		credit-=amount;
		fstream fin("customers.txt",ios::in);
		fstream fout("temp.txt",ios::out);
		string s;
		for(int i=0;i<id-1;i++)
		{	
			getline(fin,s,'\n');
			fout<<s<<"\n";
		}
		fout<<type<<"\t"<<id<<"\t"<<name<<"\t"<<password<<"\t"<<credit<<endl;
		getline(fin,s,'\n');
		while(!fin.eof())
		{	
			getline(fin,s,'\n');			//writes the modifications into temp.txt and then renames it to customers.txt
			fout<<s<<"\n";
		}
		remove("customers.txt");
		rename("temp.txt","customers.txt");
		return true;
	}
	else 
	{
		return false;
	}		
}
		
void Users::signup(string name,string pass,int &usercount)//for signing up of customer
{
	ofstream customer("customers.txt",ios::app);
	cout<<"ENTER THE AMOUNT YOU WANT TO INSERT IN YOUR ACCOUNT"<<endl;
	long int credit;cin>>credit;
	customer<<endl<<1<<"\t"<<++usercount<<"\t"<<name<<"\t"<<pass<<"\t"<<credit;
	system("clear");
	cout<<"SUCCESSFUL SIGNUP......PLEASE LOGIN TO CONTINUE......YOUR LOGIN ID IS :"<<usercount<<endl;
	cout<<"ENTER ANY CHARACTER TO CONTINUE"<<endl;
	char ch;cin>>ch;
	
	customer.close();
}

bool Mall::validloginmart(int id,string inputpass)//for checking password for mart managers
{
	ifstream malls("malls.txt",ios::in);
	malls.seekg(0);
	while(!malls.eof())							//takes line by line input from text file and compares with entered data
	{
		malls>>mallid;
		malls>>mallname;
		malls>>password;
		malls>>income;
		if(mallid==id&&password==inputpass)
		{	
			return true;
		}
	}
	return false;
	malls.close();
}

long int Mall::returnincome()							//As income is a private variable
{
	return income;	
}

void Products::buy_product(int type,Users active )		//function to buy the products
{
			
	int i;
	fstream mall("malls.txt",ios::in);
	Mall mal[3];
	mall.seekg(0);
	string temp1;
	long int temp2;
	for(i=0;i<3;i++)
	{
		mall>>mal[i].mallid>>mal[i].mallname>>temp1>>temp2;
	}
	fstream prod("products.txt",ios::in|ios::out);
	cout<<"ENTER THE PRICE RANGE"<<endl;
	int lowerlimit,upperlimit;
	cout<<"ENTER THE LOWER LIMIT(>0)"<<endl;
	while(true)
	{
	cin>>lowerlimit;
	if(lowerlimit<=0) 
	{
	cout<<"TRY AGAIN, LOWER LIMIT SHOULD BE >0"<<endl;
	continue;
	}
	else 
		break;
	}
	cout<<"ENTER THE UPPER LIMIT"<<endl;
	cin>>upperlimit;
	string s1;
	prod.seekg(0);
	for( i=0;i<(type-1);i++)
	{
		getline(prod,s1,'-');
	}										//coming to the type of product desired in malls.txt
	
	
	int procount=0;
	ifstream prod_count("products.txt",ios::in);
	for( i=0;i<(type-1);i++)
	{
		getline(prod_count,s1,'-');
	}
	while(!prod_count.eof())						
	{                                 
		prod_count>>id>>name;
		if(id)
		{	
			if(id==-1){break;}
			procount++;
			for(i=0;i<3;i++)
			{
				prod_count>>buyprice[i]>>sellprice[i];
			}
		}
	}																		// count the number of products
	prod_count.close();
	
	
	long int * pr;									//USING DYNAMIC MEMORY ALLOCATION TO STORE PRODUCTS' DETAILS
	long int * bp;
	pr=new long int[procount];
	bp=new long int[procount];		
	int j=0;
	int c[100];
	i=0;
	int count=0;
	while(!prod.eof())						
	{                                 
		prod>>id>>name;
		if(id)
		{
			if(id==-1){break;}
			for(i=0;i<3;i++)
			{
				prod>>buyprice[i]>>sellprice[i];
			}
			long int minimum=0;							
			for(i=0;i<3;i++)
			{
				if(sellprice[i]!=0)
				{
					minimum=sellprice[i];						//to initialise the minimumprice to the first non-zero element
					break;
				}
			}
			
			for(i=0;i<3;i++)
			{
				if(sellprice[i]!=0&&sellprice[i]<=minimum)			//spanning accross the mall prices and finding minimum among the non-zero price
				{												//as zero sell price indicates that mall does not want to sell that product
					minimum=sellprice[i];
					c[j]=i;
				}
			}
			pr[j]=minimum;
			bp[j]=buyprice[c[j]];
			j++;
			if(minimum>=lowerlimit&&minimum<=upperlimit)				//the range check and printing the products in the desired range
			{	
				count++;
				cout<<id<<"\t"<<name<<"\t"<<endl;
				cout<<"BEST BUY FROM: "<<mal[c[j-1]].mallname<<" AT "<<minimum<<endl<<endl;
			}
		}
		else
		{
			break;
		}	 
				
	}
	prod.close();
	fstream prod1("products.txt",ios::in);
	prod1.seekg(0);
	if(count)
	{
		for( i=0;i<(type-1);i++)
		{
			getline(prod1,s1,'-');
		}	
		cout<<"ENTER THE PRODUCT ID OF THE PRODUCT YOU WANT TO PURCHASE/PRESS 0 to RETURN BACK"<<endl;
		int desiredid;
		cin>>desiredid;
		if(desiredid==0)
		{	
			return ; 
		}		
		else 
		{
			while(id!=desiredid)
			{
				prod1>>id>>name;
				for(i=0;i<3;i++)
				{
					prod1>>buyprice[i]>>sellprice[i];
				}
				if(id==desiredid)
					break;
			}						//Now printing details of the desired product
			cout<<"YOU OPTED FOR:"<<endl;
			cout<<id<<"\t"<<name<<"\t"<<"COST"<<"\t"<<pr[id-1]<<endl;
			cout<<"ENTER YOUR PASSWORD TO CONFIRM:"<<endl;
			string inputpass;
			cin>>inputpass;
			if(!active.validlogincustomer(active.returnid(),inputpass))
			{
				cout<<"WRONG PASSWORD"<<endl<<"ENTER A CHARACTER TO CONTINUE"<<endl;
				string tempchar;
				cin>>tempchar;
				return ;
			}	
			else if(active.deductcredit(pr[id-1]))
			{	
			mal[c[id-1]].increasecredit(pr[id-1]-bp[id-1]);
			cout<<"TRANSACTION SUCCESSFUL PRESS ANY CHARACTER TO PROCEED"<<endl;
			char ch;
			cin>>ch;
			ifstream bill("bill.txt",ios::in);
			bill.seekg(0);
			string temp;
			int billcount;
			long int n=1;
			while(!bill.eof())
			{
				string s;
				bill>>n>>s>>n>>s>>n>>n;
			}
			billcount =n;
			bill.close();
			fstream bill1("bill.txt",ios::out|ios::app);
			bill1<<id<<"\t"<<name<<"\t"<<pr[id-1]<<"\t"<<mal[c[id-1]].mallname<<"\t"<<active.returnid()<<"\t"<<++billcount<<endl;
			{
				//FOR PRINTING THE BILL ON SCREEN
				system("clear");
				cout<<"         	  **********";
				string temp=mal[c[id-1]].mallname;
				int j;
				j=temp.length()+7;
				for(;j>0;j--)
				{
					cout<<"*";
				}
				cout<<"             "<<endl;
				cout<<"         	  *        "<<mal[c[id-1]].mallname<<"       *"<<endl;
				cout<<"         	  **********";
				j=temp.length()+7;
				for(;j>0;j--)
				{
					cout<<"*";
				}
				cout<<"             "<<endl<<endl<<endl;
				cout<<"INVOICE NUMBER: "<<billcount<<endl<<endl;
				cout<<"ID OF THE BUYER:  "<<active.returnid()<<endl<<endl;
				cout<<"NAME OF BUYER:  "<<active.name<<endl<<endl;
				cout<<"NAME OF THE PRODUCT PURCHASED:  "<<name<<endl<<endl;
				cout<<"PRICE OF THE PRODUCT PURCHASED:  "<<pr[id-1]<<endl<<endl;
				cout<<"NEW CREDIT OF THE CUSTOMER:  "<<active.returncredit()<<endl<<endl<<endl;
			}
			cout<<"PRESS ANY CHARACTER TO RETURN"<<endl;
			cin>>ch;
				
		}
			else
			{
				cout<<endl<<endl<<endl<<endl<<"NOT ENOUGH CASH FOR THIS ITEM"<<endl<<endl<<"PRESS ANY CHARACTER TO CONTINUE"<<endl;;
				char c1;
				cin>>c1;
			}
			prod1.close();
		}	
	}
	else
	{
		char i;
		cout<<"SORRY,NO PRODUCT IN THIS PRICE RANGE"<<endl;
		cout<<	"PRESS ANY CHARACTER TO CONTINUE"<<endl;
		cin>>i;
	}
}

void Products::addnew(int j,string productnew)	//function to add new product
{
	int i;
	int l;
	ifstream productnew2("products.txt",ios::in);
	ofstream productnew1("pro.txt",ios::out);
	string ss;
	for(i=0;i<(j-1);i++)
	{
		getline(productnew2,ss,'-');
		productnew1<<ss<<"-";
	}
	int temp=0;
	int a;	
	string s="abc";
	while(s[0]!='-')
	{	
		getline(productnew2,s,'\n');
		if(s[0]!='-')
		{
			productnew1<<s<<endl;
			temp++;
		}
		else 
		{
			l=s.length();
			break;
		}
	}
	productnew1<<++temp<<"\t"<<productnew<<"\t"<<0<<"\t"<<0<<"\t"<<0<<"\t"<<0<<"\t"<<0<<"\t"<<0<<endl<<"-";
	productnew2.seekg(-l,ios::cur);
	while(!productnew2.eof())
	{
		getline(productnew2,ss,'\n');
		productnew1<<ss<<endl;
	}
	
	remove("products.txt");
	rename("pro.txt","products.txt"	);
}

void Users::viewtransactions()
{
	ifstream transaction("bill.txt",ios::in);
	int count =0;
	long int n,billcount;
	while(!transaction.eof())
	{
		string s;
		transaction>>n>>s>>n>>s>>n>>n;
	}
	billcount =n;
	int i=0;
	transaction.seekg(0,ios::beg);
	transaction.close();
	transaction.open("bill.txt",ios::in);
	while(i<(billcount+1))
	{
		i++;
		int productid,custid,invno;
		string prodname,mallname;
		long int price;
		transaction>>productid>>prodname>>price>>mallname>>custid>>invno;
		if(custid==this->id)
		{	
			cout<<"INVOICE NUMBER   "<<invno<<endl;
			cout<<"PRODUCT NAME: "<<prodname<<endl;
			cout<<"PURCHASE PRICE: "<<price<<endl;
			cout<<"MALL NAME:  "<<mallname<<endl<<endl<<endl;
			count++;
		}	
	}
	if(!count)
	{
		cout<<"YOU HAVE NO TRANSACTIONS UPTILL NOW"<<endl;
	}						
}

void Mall::viewbills()
{
	ifstream transaction("bill.txt",ios::in);
	int count =0;
	long int n,billcount;
	while(!transaction.eof())
	{
		string s;
		transaction>>n>>s>>n>>s>>n>>n;
	}
	billcount =n;
	int i=0;
	transaction.close();
	transaction.open("bill.txt",ios::in);
	while(i<(billcount+1))
	{
		i++;
		int productid,custid,invno;
		string prodname,mallname;
		long int price;
		transaction>>productid>>prodname>>price>>mallname>>custid>>invno;
		cout<<endl;
		if(mallname==this->mallname)
		{
			cout<<"INVOICE NUMBER:   "<<invno<<endl;
			cout<<"CUSTOMER ID:      "<<custid<<endl;
			cout<<"PRODUCT NAME:     "<<prodname<<endl;
			cout<<"PURCHASE PRICE: "<<price<<endl<<endl<<endl;
			count++;
		}	
	}
	if(!count)
	{
		cout<<endl<<endl<<endl<<"YOU HAVE NO TRANSACTIONS UPTILL NOW"<<endl<<endl<<endl;
	}
	cout<<"ENTER A CHARACTER TO CONTINUE"<<endl;
	char t1;
	cin>>t1;
}					
							
void Mall::increasecredit(long int n)
{
	income+=n;
	long int n1;
	string s;
	ifstream mall1("malls.txt",ios::in);
	ofstream  mall2("malls1.txt",ios::out);
	for(int i=0;i<(mallid-1);i++)
	{
		getline(mall1,s,'\n');
		mall2<<s<<endl;
	}
	mall1>>mallid>>mallname>>password>>n1;
	mall2<<mallid<<"\t"<<mallname<<"\t"<<password<<"\t"<<income;
	while(!mall1.eof())
	{
		getline(mall1,s,'\n');
		mall2<<s<<endl;
	}
	remove("malls.txt");
	rename("malls1.txt","malls.txt");
}


void Mall::viewnewproducts(int type)
{
	ifstream products("products.txt",ios::in);
	int i=0;
	string s1;
	for( i=0;i<(type);i++)
	{
		getline(products,s1,'-');
	}
	products.close();
	ofstream temp1("temp.txt",ios::out);
	temp1<<s1;
	temp1<<endl<<0;
	temp1.close();
	ifstream temp("temp.txt",ios::in); 
	temp.seekg(0);
	int tempid=5;						
	long int buyprices[3],sellprices[3];
	string name;int count =0;
	temp>>tempid>>name;
	while(tempid!=0&&!temp.eof())
	{						
		for(i=0;i<3;i++)
		{		
			temp>>buyprices[i]>>sellprices[i];
		}		
		if(buyprices[mallid-1]==0)
		{	count++;
			cout<<tempid<<". "<<name<<endl<<endl;	
		}
		temp>>tempid>>name;
	}
	if(!count)
	{
		cout<<"NO NEW PRODUCTS IN THIS TYPE"<<endl;
	}	
	remove("temp.txt");
	temp.close();
	cout<<"ENTER A CHARACTER TO CONTINUE"<<endl;
	char t1;
	cin>>t1;	
}

void Mall::viewproducts(int type)
{
	ifstream products("products.txt",ios::in);
	int i=0;
	string s1;
	for( i=0;i<(type);i++)
	{
		getline(products,s1,'-');
	}
	products.close();
	ofstream temp1("temp.txt",ios::out);
	temp1<<s1;
	temp1<<endl<<0;
	temp1.close();
	ifstream temp("temp.txt",ios::in); 
	temp.seekg(0);
	int tempid=5;
	long int buyprices[3],sellprices[3];
	string name;int count=0;
	temp>>tempid>>name;
	while(tempid!=0&&!temp.eof())
	{	
		for(i=0;i<3;i++)
		{		
			temp>>buyprices[i]>>sellprices[i];
		}		
		if(buyprices[mallid-1]!=0) 
		{
			count++;
			cout<<tempid<<". "<<name<<endl<<"Buy price:  "<<buyprices[mallid-1]<<endl<<"Sell price:  "<<sellprices[mallid-1]<<endl<<endl;	
		}
		temp>>tempid>>name;
	}
	remove("temp.txt");
	temp.close();
	if(!count)
	{
		cout<<"YOU ARE PRESENTLY DEALING WITH NO PRODUCT OF THIS TYPE"<<endl;
	}
	
	cout<<"ENTER A CHARACTER TO CONTINUE"<<endl;
	char t1;
	cin>>t1;
}

void Mall::editproducts(int type)
{
	ifstream prod_read("products.txt",ios::in);	
	ofstream temp("temp.txt",ios::out);
	string temp1;	int i=1;			
	while(type-1)
	{
		getline(prod_read,temp1,'-');
		temp<<temp1<<"-";
		type--;
	}
	int editid;
	long int newbuyprice;
	long int newsellprice;
	cout<<"ENTER THE ID OF PRODUCT YOU WANT TO EDIT: "<<endl;
	cin>>editid;
	cout<<"ENTER THE NEW BUY PRICE OF THE PRODUCT:  "<<endl;
	cin>>newbuyprice;
	cout<<"ENTER THE NEW SELL PRICE OF THE PRODUCT: "<<endl;
	cin>>newsellprice;	
	int tempid;
	string name;
	long int buyprices[3],sellprices[3];
	while(i<editid)
	{
		getline(prod_read,temp1,'\n');
		temp<<temp1<<endl;
		i++;
	}	
	prod_read>>tempid>>name;
	for(i=0;i<3;i++)
	{		
		prod_read>>buyprices[i]>>sellprices[i];
	}	
	buyprices[mallid-1]=newbuyprice;
	sellprices[mallid-1]=newsellprice;
	temp<<tempid<<"\t"<<name<<"\t";
	for(i=0;i<3;i++)
	{		
		temp<<buyprices[i]<<"\t"<<sellprices[i]<<"\t";
	}
	
	while(!prod_read.eof())
	{
		getline(prod_read,temp1,'\n');
		temp<<temp1<<endl;
	}	
	remove("products.txt");
	rename("temp.txt","products.txt");
		

}

int validinput(int type_num)								//returns the single digit integer inputted if valid else 0
{
	string input;
	cin>>input;
	if(input.length()!=1)
	 {cout<<"PLEASE ENTER A VALID INPUT."<<endl<<endl;
		cout<<"ENTER A CHARACTER TO GO BACK."<<endl;
		string temp;
		cin>>temp;
	 return 0;}
	else 
	{
	if((int)(input[0]-48)>type_num)	
	{		
		cout<<"PLEASE ENTER A VALID INPUT."<<endl<<endl;
		cout<<"ENTER A CHARACTER TO GO BACK."<<endl;
		string temp;
		cin>>temp;
		return 0;
	}	
	else return (int)(input[0]-48);	
	}
	
}

void printmallranks()
{
	system("clear");
	ifstream malls("malls.txt",ios::in);
	string names[3],dummy;
	long int incomes[3];
	int i=0;
	for(i=0;i<3;i++)
	{
		malls>>dummy>>names[i]>>dummy>>incomes[i];
	}						//Now sorting according to their incomes
	for(i=0;i<2;i++)		//This may seem illegitimate because we are using for loop to repeat a code just 2 times
	{						//But it is for generalising as for n merchants, the loop would run n-1 times.
		for(int j=0;j<2;j++)
		{
			if(incomes[j]<incomes[j+1])
			{
				long int temp;
				string temp1;
				temp=incomes[j];
				incomes[j]=incomes[j+1];
				incomes[j+1]=temp;
				temp1=names[j];
				names[j]=names[j+1];
				names[j+1]=temp1;
			}
		}
	}						//Now we have to print all the merchants
	int ranks[3];
	ranks[0]=1;
	for(i=1;i<3;i++)		//alloting ranks to merchants, 2 merchants with same income are given same ranks
	{
		if(incomes[i]==incomes[i-1])
			ranks[i]=ranks[i-1];
		else
			ranks[i]=i+1;
	}
	for(i=0;i<3;i++)
	{
		cout<<"RANK : "<<ranks[i]<<endl;
		cout<<"NAME : "<<names[i]<<endl<<endl;
	}
	cout<<endl<<"ENTER A CHARACTER TO PROCEED"<<endl;
	string stray;
	cin>>stray;		
}


								
						
	
					
			

