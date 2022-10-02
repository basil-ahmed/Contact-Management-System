
//=================================================================================
// Name         : DS Assignment # 3 
// Author       : Basil Ahmed
// Version      : 1.0
// Date Created : 04-18-2022
// Date Modified: -
// Description  : Contact Management System using BST Tree in C++
// Copyright © 2022 Khalid Mengal and Mai Oudah. All rights reserved.
//=================================================================================
#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<stdexcept>
#include<sstream>
#include<exception>
#include<stdexcept>
#include<random>
#include<fstream>

#include "contactbst.h"
#include "contact.h"

//==========================================================
void listCommands()
{
	cout<<"----------------------------------"<<endl;
	cout<<"import <path>      :Import contacts from a CSV file"<<endl
		<<"export <path>      :Export contacts to a CSV file"<<endl
		<<"add                :Add a new contact"<<endl
		<<"edit <key>         :Update a contact's details"<<endl
		<<"del <key>          :Delete a contact"<<endl
		<<"searchFor <key>    :Search for a contact"<<endl
		<<"markfv <key>       :Mark as favourite"<<endl
		<<"unmarkfv <key>     :Unmark as favourite"<<endl
		<<"printASC           :Print contacts in ascending order"<<endl
		<<"printDES           :Print contacts in descending order"<<endl
		<<"printfv            :Print all favourite contacts"<<endl
		<<"help               :Display the available commands"<<endl
		<<"exit               :Exit the program"<<endl;
}
//==========================================================

int main(void)
{
	ContactBST myContactBST;
	string user_input;
	string command;
	string key;

	while(true)
	{
		listCommands();
		cout<<">";

		getline(cin,user_input);

		// parse userinput into command and parameter(s)
		stringstream sstr(user_input);
		getline(sstr,command,' ');
		getline(sstr,key);
		
		Node* root = myContactBST.getRoot();	//get the root of the tree
		cout<<"----------------------------------"<<endl;
		if (command =="import")	cout<<myContactBST.importCSV(root, key)<<endl;
		else if (command == "export")	cout<<myContactBST.exportCSV(root, key)<<endl;
		else if (command =="add" or command=="a") 
		{ 
			string temp_fname;
			string temp_lname;
			string temp_email;
			string temp_primaryPhone;
			string temp_city;
			string temp_country;
			string temp_isFav;

			cout<<"Please enter the details of the contact:"<<endl;
			cout<<"First Name: "; cin>>temp_fname;
			cout<<"Last Name: "; cin>>temp_lname;
			cout<<"Email: "; cin>>temp_email;
			cout<<"Phone#: "; cin>>temp_primaryPhone;
			cout<<"City: "; cin>>temp_city;
			cout<<"Country: "; cin>>temp_country;
			cout<<"Do you want to add the contact in your favourites (y/n): "; cin>>temp_isFav;


			string tempKey = temp_fname + " " + temp_lname;
			Contact* temp_contact;

			if (temp_isFav == "y")
			{
				temp_contact = new Contact(temp_fname, temp_lname, temp_email, temp_primaryPhone, temp_city, temp_country, true);
			}
			else if (temp_isFav == "n")
			{
				temp_contact = new Contact(temp_fname, temp_lname, temp_email, temp_primaryPhone, temp_city, temp_country, false);
			}
			else
			{
				cout<<"Wrong Choice!!"<<endl;
			}
			myContactBST.insert_helper(tempKey, temp_contact);

			cout<<"Contact "<<temp_fname<<" "<<temp_lname<<" has successfully been added!"<<endl;
		}
		else if (command =="edit" or command=="e")	cout<<(myContactBST.update(root, key)==nullptr ? "Contact record not found":"The contact record has successfully been updated")<<endl;
		else if (command =="del" or command=="d")	myContactBST.remove_helper(key);
		else if (command =="searchFor")	
		{
			Node* temp_ptr = myContactBST.search(root, key);

			if (temp_ptr == nullptr) 
			{
				cout<<"Contact record not found"<<endl;
			}
			else
			{
				cout<<temp_ptr->getData()->size()<<" records found:"<<endl;

		        for (int i = 0; i < temp_ptr->getData()->size(); ++i)
		        {
		            cout<<temp_ptr->getData()->at(i).getfname()<<" "<<temp_ptr->getData()->at(i).getlname()<<", "<<temp_ptr->getData()->at(i).getemail()<<", "<<temp_ptr->getData()->at(i).getprimaryPhone()<<", "<<temp_ptr->getData()->at(i).getcity()<<", "<<temp_ptr->getData()->at(i).getcountry()<<endl;
		        }

			}
		}
		else if (command =="markfv" or command=="m")	cout<<(myContactBST.markFav(root, key)==false ? "Contact record not found":" ")<<endl;
		else if (command =="unmarkfv" or command=="u")	cout<<(myContactBST.unmarkFav(root, key)==false ? "Contact record not found":" ")<<endl;
		else if( command =="printASC")	myContactBST.printASC(root);
		else if( command =="printDES")	myContactBST.printDES(root);
		else if( command =="printfv")	myContactBST.printFav(root);
		else if( user_input == "help") listCommands();
		else if( user_input == "exit") {return EXIT_SUCCESS;}
		else cout<<"Invalid command !!!"<<endl;

	}

	return 0;
}

//==========================================================