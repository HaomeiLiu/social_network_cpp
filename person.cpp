
#include "person.h"
#include "date.h"
#include "misc.h"

Person::Person(){
    // I'm already done! 
    set_person();
}


Person::~Person(){
    delete birthdate;
    // DONE: complete the method!
    delete email;
    delete phone;
}


Person::Person(string fname, string lname, string bdate, string email, string phone){
    // DONE: Complete this method!
    // phone and email strings are in full version
    // cout << "Constructor of Person\n";
    f_name = fname;
    l_name = lname;
    birthdate = new Date(bdate);
    string type = email.substr(1,email.find(')')-1);
    string temp = email.substr(email.find(')')+2).c_str();
    this->email = new Email(type, temp);
    type = phone.substr(1,phone.find(')')-1);
    temp = phone.substr(phone.find(')')+2).c_str();
    this->phone = new Phone(type, temp);
}


Person::Person(string filename){
    set_person(filename);
}


void Person::set_person(){
    // prompts for the information of the user from the terminal
    // first/last name can have spaces!
    // date format must be "M/D/YYYY"
    // We are sure user enters info in correct format.
    // DONE: complete this method!
    
    string temp;
    string type;

    std::cout << "First Name: ";
    // pay attention to how we read first name, as it can have spaces!
    std::getline(std::cin,f_name);

	cout << "Last Name: ";
    std::getline(std::cin,l_name);

    cout << "Birthdate (M/D/YYYY): ";
    std::getline(std::cin,temp);
    // pay attention to how we passed argument to the constructor of a new object created dynamically using new command
    birthdate = new Date(temp); 

    cout << "Type of email address: ";
    // code here
    std::getline(std::cin,type);
    cout << "Email address: ";
    // code here
    std::getline(std::cin,temp);
    email = new Email(type, temp);

    cout << "Type of phone number: ";
    // code here
    std::getline(std::cin,type);
    cout << "Phone number: ";
    // code here
    std::getline(std::cin,temp);
    // code here
    phone = new Phone(type, temp);
}


void Person::set_person(string filename){
    // reads a Person from a file
    // Look at person_template files as examples.     
    // Phone number in files can have '-' or not.
    // DONE: Complete this method!
    ifstream infile;
    infile.open(filename);
    string line, type, temp;
    getline(infile, line);
    f_name = line;
    getline(infile, line);
    l_name = line;
    getline(infile, line);
    birthdate = new Date(line);
    getline(infile, line);
    type = line.substr(1,line.find(')')-1);
    temp = line.substr(line.find(')')+1).c_str();
    phone = new Phone(type, temp);
    getline(infile, line);
    type = line.substr(1,line.find(')')-1);
    temp = line.substr(line.find(')')+1).c_str();
    email = new Email(type, temp);
}


bool Person::operator==(const Person& rhs){
    // DONE: Complete this method!
    // Note: you should check first name, last name and birthday between two persons
    // refer to bool Date::operator==(const Date& rhs)
    if((f_name == rhs.f_name) &&
        (l_name == rhs.l_name) &&
        (*birthdate == *(rhs.birthdate))){
            return true;
    }
    else{
        return false;
    }
}

bool Person::operator!=(const Person& rhs){ 
    // DONE: Complete this method!
    return !(*this == rhs);
}


void Person::print_person(){
    // Already implemented for you! Do not change!
	cout << l_name <<", " << f_name << endl;
	birthdate->print_date("Month D, YYYY");
    email->print();
    phone->print();
    for(auto i=friends.begin(); i!=friends.end(); ++i){
        cout << IDName((*i)->l_name, (*i)->f_name) << endl;
    }
}

void Person::addFriend(Person* newFriend){
    friends.push_back(newFriend);
}

string Person::getFName(){
    return f_name;
}

string Person::getLName(){
    return l_name;
}

void Person::save_person(ofstream &outfile){
    outfile << l_name <<", " << f_name << endl;
    outfile << birthdate->get_date() << endl;
    outfile << email->get_contact("full") << endl;
    outfile << phone->get_contact("full") << endl;
    for(auto i=friends.begin(); i!=friends.end(); ++i){
        outfile << IDName((*i)->l_name, (*i)->f_name) << endl;
    }
    outfile << "------------------------\n";
}
