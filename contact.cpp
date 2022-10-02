#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<stdexcept>
#include<sstream>
#include<exception>
#include<stdexcept>
#include "contact.h"

using namespace std;

void Contact::setfname(string firstName) {this->fname = firstName;};
void Contact::setlname(string lastName) {this->lname = lastName;};
void Contact::setemail(string e) {this->email = e;};
void Contact::setprimaryPhone(string p) {this->primaryPhone = p;};
void Contact::setcity(string ci) {this->city = ci;};
void Contact::setcountry(string co) {this->country = co;};
void Contact::setisFav(bool fav) {this->isFav = fav;};

string Contact::getfname() {return fname;};
string Contact::getlname() {return lname;};
string Contact::getemail() {return email;};
string Contact::getprimaryPhone() {return primaryPhone;};
string Contact::getcity() {return city;};
string Contact::getcountry() {return country;};
bool Contact::getisFav() {return isFav;};