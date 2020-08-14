#include "contact.h" 
// TODO: Add needed libraries! 

Email::Email(string type, string email_addr){
    // DONE: Complete me!
    this->type = type;
    this->email_addr = email_addr;
}


void Email::set_contact(){
    // DONE: Do not change the prompts!
	
    cout << "Enter the type of email address: ";
    // some code here
    cin >> type;
    cout << "Enter email address: ";
    // some code here
    cin >> email_addr;
    //Input validation: contains@
    while(!email_addr.find("@")){
        cout << "Error! Incorect input format!" << endl;
        cin >> email_addr;
    }
}


string Email::get_contact(string style){
    // Note: We have default argument in declaration and not in definition!
    // emaple: Email (USC): tommytrojan@usc.edu
    if(style=="full"){
        return "(" + type + ") " + email_addr;
    }
    else{ 
        return email_addr;
    }
}


void Email::print(){
    // Note: get_contact is called with default argument
	cout << get_contact("full") << endl;
}


Phone::Phone(string type, string num){
    //TODO: check if phone_num should be string or long int
    // DONE: It is possible that num includes "-" or not, manage it! 222-444-7898
    // DONE: Complete this method!

    /* Note: Modify the following code can help you implementing this function
     * This code has a bug, can you understand why?
    long int area_code = atoi(num.substr(0, 3).c_str());
    long int  number = atoi(num.substr(3).c_str()); 
    this->phone_num = area_code*10000000 + number; 
    */
   this->type = type;
   if(num.find("-")){
       phone_num = num.substr(0,num.find('-'));
       num = num.substr(num.find('-')+1).c_str();
       phone_num += num.substr(0, num.find('-'));
       num = num.substr(num.find('-')+1).c_str();
       phone_num += num.substr(0, num.find('-'));
   }
   else{
       phone_num = num;
   }
}


void Phone::set_contact(){
    // DONE: Complete this method
    // Use the same prompts as given!
	cout <<"Enter the type of phone number: ";
    cin >> type;
	cout << "Enter the phone number: ";
    string num;
    cin >> num;
    if(num.find("-")){
       phone_num = num.substr(0,num.find('-'));
       num = num.substr(num.find('-')+1).c_str();
       phone_num += num.substr(0, num.find('-'));
       num = num.substr(num.find('-')+1).c_str();
       phone_num += num.substr(0, num.find('-'));
   }
   else{
       phone_num = num;
   }
}


string Phone::get_contact(string style){
    // DONE: Complete this method, get hint from Email 
    // follow the format of this example: Phone (Office): 310-192-2847

    /* Note: Modify the following code can help you implementing this function
     * This code has a bug, can you understand it？
    int x1 = (phone_num/10000000);
	int x2 = ((phone_num)/10000)%1000;
	int x3 = phone_num%10000;
    */ 

   if(style == "full"){
       return "("+type+") "+phone_num.substr(0,3)+"-"+phone_num.substr(3,3)+"-"+phone_num.substr(6,4);
   }
   else{
       return phone_num.substr(0,3)+"-"+phone_num.substr(3,3)+"-"+phone_num.substr(6,4);
   }
}


void Phone::print(){
    // Note: get_contact is called with default argument
	cout << get_contact("full") << endl;
}


