#ifndef CONTACT_H
#define CONTACT_H

#include<iostream>
using namespace std;

class Contact
{
	private:
		string fname;
		string lname;
		string email;
		string primaryPhone;
		string city;
		string country;
		bool isFav;

	public:
		Contact() {};
		Contact(string firstname, string lastname, string email_add, string primary_Phone, string city_add, string country_add, bool isFavorite): fname(firstname), lname(lastname), email(email_add), primaryPhone(primary_Phone), city(city_add), country(country_add), isFav(isFavorite) {};

		void setfname(string f);
		void setlname(string l);
		void setemail(string e);
		void setprimaryPhone(string p);
		void setcity(string ci);
		void setcountry(string co);
		void setisFav(bool fav);

		string getfname();
		string getlname();
		string getemail();
		string getprimaryPhone();
		string getcity();
		string getcountry();
		bool getisFav();

		//friend class ContactBST;
		
};

#endif