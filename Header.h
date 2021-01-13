#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const int STRING_SIZE = 100;
class MyString
{
private:
	char strval[STRING_SIZE];  // c_string
	int strln;                 // length of string value
	int frequency;			// frequency of the strval

public:

	int getFrequency() const; //to be able to access frequency

	MyString() : strln(0), frequency(1) // default constructor
	{
		strcpy_s(strval, ""); //construct the strval and set all values to blank
	}

	MyString(char s[]);  // initialize string value to s

	// copy constructor
	MyString(const MyString& s);//write functions outside of the class using scope resolution operators (inline functions bad.)
	
	// modifier
	void ToUpper(); // change all letters into upper case

	// operators overload
	bool operator ==(MyString s) const; 
	bool operator >(MyString s) const;
	bool operator <(MyString s) const;
	MyString operator +(MyString s) const;
	MyString operator =(MyString s);
	MyString operator ++(int) {
		frequency += 1;
		return *this; //'this' means a pointer to an object so here we are return an object by dereferencing
	}

	char& operator [](int indx) {
		return strval[indx];
	}

	// file input/output functions
	friend ifstream& operator >>(ifstream& i, MyString& str); //friend function in order to access the private members of the class (strval arr, strln and frequency)
	friend ofstream& operator <<(ofstream& o, MyString str);
};

MyString::MyString(const MyString& s) { // copy constructor 
	strcpy_s(strval, s.strval);
	strln = s.strln;
	frequency = s.frequency;
}

void MyString::ToUpper() {  // getting toupper from the std lib and putting it into a loop to make strval arr upper case

	for (int i = 0; i < strln; i++)
		strval[i] = toupper(strval[i]);
}

int MyString::getFrequency() const {
	return frequency;
}

MyString::MyString(char c[]) {
	strcpy_s(strval, c);
	strln = strlen(c);
	frequency = 1;
}

bool MyString::operator ==(MyString s) const {

	return (strcmp(strval, s.strval) == 0);
}

bool MyString::operator < (MyString s) const {
	if (frequency == s.frequency)
		return (strcmp(strval, s.strval) == 1);
	else
		return (frequency < s.frequency);
}

bool MyString::operator > (MyString s) const {
	
	if (frequency == s.frequency)
		return (strcmp(strval, s.strval) == -1);
	else
		return (frequency > s.frequency);

}

MyString MyString::operator +(MyString s) const {
	
	char str[STRING_SIZE];

	strcpy_s(str, this->strval); //copy the object string into a local variable 
	strcat_s(str, " ");
	strcat_s(str, s.strval);

	return MyString(str);

}

MyString MyString::operator = (MyString s) {

	strcpy_s(strval, s.strval);
	strln = s.strln;
	frequency = s.frequency;
	return *this;

}

ifstream& operator >>(ifstream& i, MyString& str) {
	i >> str.strval;
	str.strln = strlen(str.strval);
	return i;
}

ofstream& operator <<(ofstream& o, MyString str) { 
	for (int i = 0; i < str.strln; i++)
		o << str.strval[i];
	for (int j = 0; j < 60 - str.strln; j++)
		o << ' ';
	if (str.frequency > 1)
		o << "\t" << str.frequency;  //for output purposes create a space based on strln and a tab before frequency as long as the frequency is greater than 1
	return o;
}
#endif
