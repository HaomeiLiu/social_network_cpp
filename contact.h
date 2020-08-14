#ifndef CONTACT_H
#define CONTACT_H

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
// DONE: You may need to add other libraries here!
using namespace std;


class Contact {
    // DONE: private or protected? Look at its children!
protected:	
	string type;
public:
    // the following functions are pure virtual functions
	virtual void print() = 0;
    virtual string get_contact(string style="full") = 0;
	virtual void set_contact() = 0;
};


class Email: public Contact{
private:
    string email_addr;
public:
    Email(string type, string email_addr);
    // DONE: Complete me!
    void print();
    string get_contact();
    string get_contact(string);
    void set_contact();
};


class Phone: public Contact{
private:
    // DONE: modify dataType! Can int store 10 digit phone-number? 
	string phone_num; 
public:
    Phone(string type, string phone_number);
    // DONE: Complete me!
    void print();
    string get_contact();
    string get_contact(string);
    void set_contact();
};

#endif
