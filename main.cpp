#include "project.h"
int main()				//main funtion for program execution
{
	int usercount;
	long int temp,temp1;	//arbitrary variables to take input from file
	ifstream customers;
	customers.open("customers.txt",ios::in);
	while(!customers.eof())		//loop to initialise usercount
	{
		customers>>temp;
		customers>>temp;
		string s;
		customers>>s>>s;
		customers>>temp1;
	}
	usercount = temp; 
	bool active=true;		//bool value indicates the running of whole program
	system("clear");
	while(active)	//the main interface starts
	{
		system("clear");
		cout<<"         		  **************************             "<<endl;
		cout<<"         		  *WELCOME TO BOMBAY BAZAAR*             "<<endl;
		cout<<"         		  **************************             "<<endl<<endl<<endl;	
		cout<<"CONTINUE AS:   "<<endl;
		cout<<"1.  CUSTOMER"<<endl;
		cout<<"2.  ADMIN"<<endl;
		cout<<"3.  MART MANAGER"<<endl;
		cout<<"4.  EXIT"<<endl<<endl<<endl;
		int user_response;
		cout<<"ENTER YOUR CHOICE:"<<endl;
		user_response=validinput(4);		//function to check the input is valid or not and to extract the useful quantity
		if(user_response==0)				//function returns 0 if response is invalid
		{
			continue;
		}
		if(user_response==1)
		{	
			system("clear");
			bool cust_bool=true;	//bool indicating customer is active
			while(cust_bool)		//loop runs till the user remains active
			{
				system("clear");
				cout<<"         		  **************************             "<<endl;
				cout<<"         		  *    WELCOME CUSTOMER    *             "<<endl;
				cout<<"         		  **************************             "<<endl<<endl<<endl;	
				cout<<"1.LOGIN"<<endl;
				cout<<"2.SIGNUP"<<endl;
				cout<<"3.BACK"<<endl<<endl<<endl;
				int cust_response;	
				cout<<"ENTER YOUR CHOICE:"<<endl;
				cust_response=validinput(3);
				if(!cust_response)
				{
					continue;
				}
				if(cust_response==1)
				{	
					system("clear");
					cout<<"PLEASE ENTER YOUR ID:\t";
					int id;														//takes the input of customer's id
					cin>>id;				//as id cannot be more than usercount
					if(id>0&&id<=usercount)
					{	
						cout<<"PLEASE ENTER YOUR PASSWORD:"<<endl;
						string inputpassword;										//takes the input of customer's password
						cin>>inputpassword;
						Users active;												//object to signify active user
						if(active.validlogincustomer(id,inputpassword))				//the function returns true if password and id match
						{
							bool authentic_cust=true;								//bool indicating valid customer is active
							while(authentic_cust)
							{
								system("clear");
								cout<<"         		  **********";
								string temp=active.name;
								int j;
								j=temp.length();
								for(;j>0;j--)
								{
									cout<<"*";
								}
								cout<<"             "<<endl;
								cout<<"         		  *WELCOME "<<active.name<<"*             "<<endl;
								cout<<"         		  **********";
								j=temp.length();
								for(;j>0;j--)
									cout<<"*";
								cout<<"             "<<endl<<endl<<endl;
								cout<<"WHAT DO YOU WANT TO DO:"<<endl;	
								cout<<"1.BUY A PRODUCT"<<endl;
								cout<<"2.KNOW /INCREASE THE ACCOUNT BALANCE"<<endl;
								cout<<"3.CHANGE YOUR PASSWORD"<<endl;
								cout<<"4.KNOW MY TRANSACTIONS"<<endl;
								cout<<"5.KNOW THE MERCHANTS AND THEIR RANKING"<<endl;
								cout<<"6.LOGOUT"<<endl<<endl<<endl;
								int cust_choice;
								cout<<"ENTER YOUR CHOICE:"<<endl;	
								cust_choice=validinput(6);
								if(cust_choice==0)
								{
									continue;
								}
								if(cust_choice==1)
								{	
									while(true)
									{
										system("clear");
										cout<<"PLEASE SELECT A CATEGORY:"<<endl;		//user can select any product he wants
										cout<<"1.MOBILE PHONES"<<endl;
										cout<<"2.LAPTOP"<<endl;
										cout<<"3.REFRIGERATORS"<<endl;
										cout<<"4.AIR CONDITIONER"<<endl;
										cout<<"5.CAMERA"<<endl;
										cout<<"6.WASHING MACHINE"<<endl;
										cout<<"7.BACK"<<endl;
										int cust_product_choice;
										cout<<"ENTER YOUR CHOICE:"<<endl;	
										cust_product_choice=validinput(7);
										if(cust_product_choice==7)
										{
											break;
										}	
										if(!cust_product_choice)
											continue;
										Products selected_prod;		//object to signify the selected product type
										selected_prod.buy_product(cust_product_choice,active);	//the called function performs further transactions
									}
								}
								if(cust_choice==2)
								{
									active.modifyaccountbalance();	//function enables user to view/modify account balance
								}
								if(cust_choice==3)
								{	
									while(true)
									{
										if(!active.updatepassword())		//the function returns true if password is updated successfully
										{
											int resp;
											cout<<"ENTER 1 TO RETRY/0 TO SKIP"<<endl;
											cin>>resp;
											if(resp==1)
												continue;					//allows the user to retry
											else
												break;	
										}
										break;
									}	
									cout<<"YOU HAVE BEEN LOGGED OUT...PLEASE SIGNIN WITH NEW PASSWORD TO CONTINUE"<<endl;
									cout<<"PLEASE ENTER A CHARACTER TO CONTINUE"<<endl;
									string temp;
									cin>>temp;
									break;
								}
								if(cust_choice==4)
								{
									active.viewtransactions();			//user can view the transactions
									cout<<"PRESS ANY CHARACTER TO CONTINUE"<<endl;
									char resp;
									cin>>resp;	
								}
								if(cust_choice==5)
								{
									printmallranks();
								}
								if(cust_choice==6)
									break;
							}
						}
						else 
						{
							system("clear");				//if login id/password is incorrect
							cout<<"WRONG ID OR PASSWORD"<<endl;
							cout<<"PRESS ANY CHARACTER TO CONTINUE"<<endl;
							char resp;cin>>resp;
						}
					}
					else 
					{
						cout<<"YOUR ID DOES NOT MATCH OUR RECORD....ENTER A CHARACTER TO CONTINUE";
						string s;
						cin>>s;
					}	 
				}
				else if(cust_response==2)
				{
					system("clear");
					cout<<"         		  **************************             "<<endl;
					cout<<"         		  *     SIGNUP WINDOW      *             "<<endl;
					cout<<"         		  **************************             "<<endl<<endl<<endl;	
					cout<<"ENTER YOUR NAME"<<endl;
					string name;
					cin>>name;
					cout<<"ENTER YOUR PASSWORD"<<endl;
					string pass,pass1;
					cin>>pass;
					cout<<"RENTER YOUR PASSWORD"<<endl;
					cin>>pass1;
					if(pass==pass1)										//if two passwords are same 
					{
						Users new_cust;									//object to signify new customer 
						new_cust.signup(name,pass,usercount);			//function does the work of signing up
						continue;
					}
					else 
						cout<<"PASSWORD MISMATCH"<<endl;				//if two password are not same
						cout<<"PLEASE ENTER A CHARACTER TO CONTINUE"<<endl;
						string temp;
						cin>>temp;
					}
				else if(cust_response==3)							//customer chooses to go back
					break;
			}
		}
		if(user_response==2)										
		{	
			Users admin;											//object to signify the active administrator
			system("clear");
			while(true)
			{
				system("clear");
				cout<<"         		  **************************             "<<endl;
				cout<<"         		  *     WELCOME ADMIN      *             "<<endl;
				cout<<"         		  **************************             "<<endl<<endl<<endl;
				cout<<"1.LOGIN"<<endl;
				cout<<"2.BACK"<<endl<<endl<<endl;
				int admin_response;
				cout<<"ENTER YOUR CHOICE:"<<endl;	
				admin_response=validinput(2);
				if(admin_response==0)
				{
					 continue;
				}
				if(admin_response==2)
					break;
				else
				{	
					system("clear");
					cout<<"ENTER YOUR PASSWORD"<<endl;
					string password;
					cin>>password;									//takes the password for authentication
					if(admin.validloginadmin(password))				//returns true if the password is correct
					{
						system("clear");
						while(true)
						{	
							system("clear");
							cout<<"HI ADMIN, WHAT WOULD YOU LIKE TO DO"<<endl<<endl<<endl;
							cout<<"1.SUGGEST A PRODUCT"<<endl;
							cout<<"2.LOGOUT"<<endl<<endl<<endl;
							int admin_choice;
							cout<<"ENTER YOUR CHOICE:"<<endl;	
							admin_choice=validinput(2);
							if(admin_choice==0)
							{
								continue;
							}
							if(admin_choice==1)
							{		
								while(true)
								{
									system("clear");
									string productnew;
									cout<<"ENTER THE PRODUCT TYPE"<<endl<<endl<<endl;
									cout<<"1.MOBILE PHONES"<<endl;
									cout<<"2.LAPTOP"<<endl;
									cout<<"3.REFRIGERATORS"<<endl;
									cout<<"4.AIR CONDITIONER"<<endl;
									cout<<"5.CAMERA"<<endl;
									cout<<"6.WASHING MACHINE"<<endl;
									cout<<"7.BACK"<<endl<<endl<<endl;
									int product_choice;
									cout<<"ENTER YOUR CHOICE:"<<endl;	
									product_choice=validinput(7);
									if(product_choice==0)
									{
										continue;
									}
									if(product_choice==7)
										break;
									else
									{
										cout<<"ENTER THE NAME"<<endl;
										cin>>productnew;					//takes the input of name of product
										Products newproduct;				//object of product class to represent the new product
										newproduct.addnew(product_choice,productnew);	//the function performs the work of product addition
										cout<<"PRODUCT SUCCESSFULLY ADDED"<<endl;
										cout<<"PRESS 1 TO ADD MORE/0 TO EXIT"<<endl;
										int temp;
										cin>>temp;
										if(temp)
										{
											continue;
										}		
										else
											break;
									}
								}
							}
							else 
								break;
						}
					}
					else 
					{
						cout<<endl<<endl<<"WRONG PASSWORD"<<endl;
						cout<<"ENTER A CHARACTER TO CONTINUE"<<endl;
						string temp;
						cin>>temp;
						break;
					}
				}
			}
		}		
		if(user_response==3)
		{
			Mall martmanager;							//object to signify the active mall
			while(true)
			{
			system("clear");
			cout<<"         		  **************************             "<<endl;
			cout<<"         		  *  WELCOME MART MANAGER  *             "<<endl;
			cout<<"         		  **************************             "<<endl<<endl<<endl;	
		
			cout<<"1.LOGIN"<<endl;
			cout<<"2.BACK"<<endl<<endl<<endl;
			int manager_response;
			cout<<"ENTER YOUR CHOICE:"<<endl;	
			manager_response=validinput(2);
			if(manager_response==0)
			{
				continue;
			}
			if(manager_response==2)
			{
				system("clear");
				break;
			}
			if(manager_response==1)
			{
				system("clear");
				cout<<"ENTER YOUR MART ID: "<<endl;
				int id;				//as id can only be upto 3.
				id=validinput(3);
				if(id)
				{
					cout<<"ENTER YOUR PASSWORD: "<<endl;
					string inputpass;
					cin>>inputpass;
					if(martmanager.validloginmart(id,inputpass))			//returns true if martmanager is valid
					{	
						while(true)
						{
							system("clear");
							cout<<"         	 	  **********";
							string temp=martmanager.mallname;
							int j;
							j=temp.length();
							for(;j>0;j--)
							{
								cout<<"*";
							}
							cout<<"             "<<endl;
							cout<<"         		  *WELCOME "<<martmanager.mallname<<"*             "<<endl;
							cout<<"         		  **********";
							j=temp.length();
							for(;j>0;j--)
								cout<<"*";
							cout<<"             "<<endl<<endl<<endl;
							cout<<"What would you like to do: "<<endl;
							cout<<"1.  VIEW TRANSACTIONS"<<endl;
							cout<<"2.  VIEW THE PRODUCTS DEALING WITH"<<endl;
							cout<<"3.  NEW PRODUCTS"<<endl;
							cout<<"4.  MODIFY BUY OR SELL PRICE(IF YOU WANT TO STOP DEALING WITH A PRODUCT, CHANGE ITS SELL PRICE TO 0)"<<endl;
							cout<<"5.  VIEW NET INCOME"<<endl;
							cout<<"6.  LOGOUT"<<endl<<endl<<endl;
							int manager_choice;
							cout<<"ENTER YOUR CHOICE:"<<endl;	
							manager_choice=validinput(6);
							if(manager_choice==0)
							{
								continue;
							}	
							if(manager_choice==1)
							{
								martmanager.viewbills();			//manager can view his transactions so far
							}
							if(manager_choice==2)
							{
								cout<<"SELECT THE TYPE OF PRODUCT DO YOU WANT TO SEE:"<<endl<<endl;
								cout<<"1.MOBILE PHONES"<<endl;
								cout<<"2.LAPTOP"<<endl;
								cout<<"3.REFRIGERATORS"<<endl;
								cout<<"4.AIR CONDITIONER"<<endl;
								cout<<"5.CAMERA"<<endl;
								cout<<"6.WASHING MACHINE"<<endl;
								int type;
								cin>>type;
								martmanager.viewproducts(type);
							}
							if(manager_choice==3)
							{
								cout<<"SELECT THE TYPE OF PRODUCT DO YOU WANT TO SEE:"<<endl<<endl;
								cout<<"1.MOBILE PHONES"<<endl;
								cout<<"2.LAPTOP"<<endl;
								cout<<"3.REFRIGERATORS"<<endl;
								cout<<"4.AIR CONDITIONER"<<endl;
								cout<<"5.CAMERA"<<endl;
								cout<<"6.WASHING MACHINE"<<endl;
								int type;
								cin>>type;
								martmanager.viewnewproducts(type);
							}	
							if(manager_choice==4)
							{
								while(true)
								{
									system("clear");
									cout<<"SELECT THE TYPE OF PRODUCT WHOSE PRICE YOU WANT TO EDIT:"<<endl<<endl;
									cout<<"1.MOBILE PHONES"<<endl;
									cout<<"2.LAPTOP"<<endl;
									cout<<"3.REFRIGERATORS"<<endl;
									cout<<"4.AIR CONDITIONER"<<endl;
									cout<<"5.CAMERA"<<endl;
									cout<<"6.WASHING MACHINE"<<endl;
									cout<<"7.BACK"<<endl;
									int type=0;
									cout<<"ENTER YOUR CHOICE:"<<endl;	
									type=validinput(7);
									if(type==0)
									{
									continue;
									}
									if(type==7) 
										break;
									else
									{
										martmanager.editproducts(type);
										cout<<"PRODUCT SUCCESSFULLY EDITED"<<endl;
										cout<<"PRESS ANY CHARACTER TO CONTINUE"<<endl;
										char temp;
										cin>>temp;
									}
								}
							}
							if(manager_choice==5)
							{
								cout<<"YOUR NET INCOME UPTO DATE IS:"<<endl<<martmanager.returnincome()<<endl<<endl;
								cout<<"PRESS ANY CHARACTER TO CONTINUE"<<endl;
								char temp;
								cin>>temp;
							}
							if(manager_choice==6)
							{
								break;
							}
						}
					}
					else
					{
						cout<<"WRONG ID OR PASSWORD"<<endl<<endl<<"PRESS ANY CHARACTER TO CONTINUE"<<endl;
						char temp;
						cin>>temp;
					}	
				}
			}
		}
	}
		if(user_response==4) 
			break;
	}
	system("clear");
	cout<<endl<<endl<<endl<<endl<<endl;
	cout<<"         		  **************************             "<<endl;
	cout<<"         		  *        MADE BY         *             "<<endl;
	cout<<"         		  **************************             "<<endl<<endl<<endl;	
	cout<<"         		  Sheshansh Agrawal 150050027"<<endl<<endl;
	cout<<"         		  Chitwan Saharia   150050011"<<endl<<endl<<endl<<endl;

}
