
#include "network.h"
#include <limits>
#include "misc.h"
#include <fstream>
#include <dirent.h>

Network::Network(){
    head = NULL;
    tail = NULL;
    count = 0;
}


Network::Network(string fileName){
    // DONE: complete this method!
    // Implement it in one single line!
    // You may need to implement the load method before this!
    loadDB(fileName);
}

Network::~Network(){
    // DONE: Complete this method
    // Destructure delete all the Person
    std::cout << "Destructor\n";
    Person* ptr = head;
    Person* temp;
    while(ptr!=NULL){
        temp = ptr->next;
        delete ptr;
        ptr = temp;
    }
    std::cout << "Destructor out\n";
}


void Network::push_front(Person* newEntry){
    // Adds a new Person (newEntry) to the front of LL
    newEntry->prev = NULL;
    newEntry->next = head;

    if (head != NULL)
        head->prev = newEntry;
    else
        tail = newEntry;
    
    head = newEntry;
    count++;
}


void Network::push_back(Person* newEntry){
    // DONE: Complete this method!
    // Adds a new Person (newEntry) to the back of LL
    newEntry->next = NULL;
    newEntry->prev = tail;
    if(tail!=NULL){
        tail->next = newEntry;
    }
    else{
        head = newEntry;
    }
    tail = newEntry;
    count++;
}


void Network::printDB(){
    // Don't change this method
    // Note: Notice that we don't need to update this even after adding to Person attributes
    // This is a feature of OOP, classes are supposed to take care of themselves!
    std::cout << "Number of persons: " << count << endl;
    std::cout << "------------------------" << endl;
    Person* ptr = head;
    while(ptr != NULL){
        ptr->print_person();
        std::cout << "------------------------" << endl;
        ptr = ptr->next;
    }
}


void Network::saveDB(string filename){
    // DONE: Complete this method!
    // Saves the netwrok in file <filename>
    // Note: The format of the output file is very abstract, just raw data
    // Look at studentDB.db as a template
    // Note: notice the intentional flaw in this code, as compared to the note mentioned in printDB, 
    // now the one who is responsible for implementing Network should be aware of implementation of Person, not good! You will fix this in PA2. 
    ofstream outfile;
    outfile.open(filename.c_str());
    Person* ptr = head;
    while(ptr != NULL){
        ptr->save_person(outfile);
        ptr = ptr->next;
    }
}


void Network::loadDB(string filename){
    // DONE: Complete this method!
    // Loads the netwrok from file <filename>
    // The format of the input file is similar to saveDB
    // Look at network studentDB.txt as a template
    // Phone number can be with dashes or without them
    // You need to use the following constructor of the Person class, Person::Person(fname, lname, bdate, email, phone)
    
    Person* ptr = head;
    while(head != NULL){
        ptr = head->next;
        delete head;
        head = ptr;
        count--;
    }
    head = NULL;
    tail = NULL;
    ifstream infile;
    infile.open(filename.c_str());
    string buff, fname, lname, bdate, email, phone;
    
    // DONE: Decalre other vairiable if needed

    while(getline(infile, buff)){
        lname = buff.substr(0, buff.find(','));
        fname = buff.substr(buff.find(',')+2);
        getline(infile, bdate);
        // DONE: read email and phone
        getline(infile, email);
        getline(infile, phone);
        
        // this line is to read the dash line
        getline(infile, buff);
        while(buff != "------------------------"){
            getline(infile, buff);
        }
        // DONE: use the constructor Person::Person(fname, lname, bdate, email, phone) to modify the following line
        Person* newEntry = new Person(fname, lname, bdate, email, phone);
        
        this->push_back(newEntry);
    }
    tail = ptr;

    // load friends
    infile.close();
    infile.open(filename.c_str());
    int line_count = 0;
    ptr = head;
    while(getline(infile, buff)){
        if(buff != "------------------------"){
            if(line_count < 4){
                line_count++;
            }
            else{
                // friends
                Person* new_friend = search(buff);
                if(new_friend != NULL){
                    ptr->addFriend(new_friend);
                }
                else{
                    std::cout << "Error in adding friend " << buff << endl;
                }
            }
        }
        else{
            if(ptr != tail){
                line_count = 0;
                ptr = ptr->next;
            }
        }
    }
}

Person* Network::search(string fname, string lname, string bdate){
    // DONE: Complete this method!
    // Search the Network for the given fname, lname, bdate
    // You may create a new person, say searchEntry, with fname, lname and bdate. Think about what Person constructor will be helpful with these arguments.
    // And use == overloaded operator between two persons
    // if found, returns a pointer to it, else returns NULL
    // Don't forget to delete allocated memory.
    Person* searchEntry = new Person(fname, lname, bdate, "(null) null","(null) 000");
    Person* ptr = head;
    while(ptr != NULL){
        if(*ptr == *searchEntry){
            delete searchEntry;
            return ptr;
        }
        ptr = ptr->next;
    }
    delete searchEntry;
    return NULL;
}

bool Network::remove(string fname, string lname, string bdate){
    // DONE: Complete this method! Follow these steps:
    // Create a new person with the the give arguments as you do in search
    // Search if this person exists using search method. If it does not exist just return false! Else, remove the person from LL, make the other connections connected
    // Don't forget to delete allocated memory, change count and returning values!
    Person* removeEntry = search(fname, lname, bdate);
    if(removeEntry != NULL){
        // Edge case: remove is head
        if(removeEntry == head){
            head = removeEntry->next;
            head->prev = NULL;
        }
        else if(removeEntry == tail){
            tail = removeEntry->prev;
            tail->next = NULL;
        }
        else{
            Person* prevEntry = removeEntry->prev;
            Person* nextEntry = removeEntry->next;
            prevEntry->next = nextEntry;
            nextEntry->prev = prevEntry;
        }
        delete removeEntry;
        count--;
        return true;
    }
    else{
        return false;
    }

}

void Network::showMenu(){
    // DONE: Complete this method!
    // All the prompts are given to you, 
    // You should add code before, between and after prompts!

    int opt;
    while(1){
        std::cout << "\033[2J\033[1;1H";
        printMe("banner"); // from misc library

        std::cout << "Select from below: \n";
        std::cout << "1. Load network database \n";
        std::cout << "2. Save network database \n";
        std::cout << "3. Add a new person \n";
        std::cout << "4. Search \n";
        std::cout << "5. Remove a person \n";
        std::cout << "6. Print database \n";
        std::cout << "7. Add friends \n";
        std::cout << "8. Friends recommendation \n";
        
        std::cout << "\nSelect an option ... ";
        
        if (std::cin >> opt) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Wrong option! " << endl;
            return;
        }
        
        // You may need these variables! Add more if you want!
        string fname, lname, fileName, bdate;
        std::cout << "\033[2J\033[1;1H";

        if (opt==1){
            // DONE: Complete me!
            std::cout << "Loading network database \n";
            // DONE: print all the files in this same directory that have ".db" format
            // Take a look into sample_files.cpp 
            // This code references sample_files.cpp
            DIR *dir;
            struct dirent *ent;
            char targetFolderAddr[] = "./";
            if ((dir = opendir ("./")) != NULL) {
                while ((ent = readdir (dir)) != NULL) {
                    if(has_db_extension(ent->d_name)){
                        std::cout << ent->d_name << endl;
                    }
                } 
                closedir (dir);
            }
            else{
                std::cout << ("No .db directory!");
            }            
            std::cout << "Enter the name of the load file: "; 
            std::cin >> fileName;
            // If file with name FILENAME does not exist: 
            ifstream f(fileName.c_str());
            if(!f.good()){
                std::cout << "File FILENAME does not exist!" << endl;
            }
            else{
                loadDB(fileName);
                // If file is loaded successfully, also print the count of persons in it: 
                std::cout << "Network loaded from " << fileName << " with " << count << " persons \n";
            }
            
        }
        else if (opt==2){
            // DONE: Complete me!
            std::cout << "Saving network database \n";
            std::cout << "Enter the name of the save file: ";
            std::cin >> fileName;
            saveDB(fileName);
            std::cout << "Network saved in " << fileName << endl;
        }
        else if (opt == 3){
            // DONE: Complete me!
            // DONE: use push_front, and not push_back 
            // Add a new person ONLY if it does not exists!
            std::cout << "Adding a new person \n";
            Person* newEntry = new Person();
            if(Network::search(newEntry->f_name, newEntry->l_name, newEntry->birthdate->get_date()) == NULL){
                push_front(newEntry);
            }
            else{
                std::cout << "Person existed in database\n";
            }
        }
        else if (opt == 4){
            // DONE: Complete me!
            std::cout << "Searching: \n";
            std::cout << "First Name: ";
            std::cin >> fname;
            std::cout << "Last Name: ";
            std::cin >> lname;
            std::cout << "Birthdate (M/D/YYYY): ";
            std::cin >> bdate;
            // if found: print person's firstname, lastname, bdate, email, phone using print_person()
            if(search(fname, lname, bdate) != NULL){
                Person* foundEntry = search(fname, lname, bdate);
                foundEntry->print_person();
            }
            // if not, cout << "Not found! \n";
            else{
                std::cout << "Not found! \n";
            }
        }
        else if (opt==5){
            // DONE: Complete me!
            std::cout << "Removing a person \n";
            std::cout << "First name: ";
            std::cin >> fname;
            std::cout << "Last name: ";
            std::cin >> lname;
            std::cout << "Birthdate (M/D/YYYY): "; 
            std::cin >> bdate;
            if(remove(fname, lname, bdate)){
                std::cout << "Remove Successful! \n";
            }
            else{
                std::cout << "Person not found! \n";
            }
            // if found, cout << "Remove Successful! \n";
            // if not found: cout << "Person not found! \n";
        }
        else if (opt==6){
            // DONE: Complete me!
            printDB();
        }
        else if(opt==7){
            string id1, id2;
            std::cout << "Adding friends: \n";
            std::cout << "Person 1 ID: ";
            std::cin >> id1;
            Person* person1 = search(id1);
            if(person1 == NULL){
                std::cout << "Person is not found! \n";
            }
            else{
                std::cout << "Person 2 ID: ";
                std::cin >> id2;
                Person* person2 = search(id2);
                if(person2 == NULL){
                    std::cout << "Person is not found! \n";
                }
                else{
                    person1->addFriend(person2);
                    person2->addFriend(person1);
                }
            }

        }
        else if(opt==8){
            std::cout << "Friends Recommendation: \n";
            std::cout << "Input level k: ";
            int k;
            std::cin >> k;
            friends_recommendation(k);
        }
        else
            std::cout << "Nothing matched!\n";
        
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\n\nPress Enter key to go back to main menu ... ";
        string temp;
        std::getline (std::cin, temp);
        std::cout << "\033[2J\033[1;1H";
    }
}

bool Network::has_db_extension(char const *name)
{
    size_t len = strlen(name);
    return len > 4 && strcmp(name + len - 3, ".db") == 0;
}

Person* Network::search(string queryid){
    Person* ptr = head;
    while(ptr != NULL){
        if(IDName(ptr->getLName(), ptr->getFName()) == queryid){
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;    
}

void Network::friends_recommendation(int k){
    Person* ptr = head;
    while((ptr != tail) && (ptr != NULL)){
        // Perform BFS
        vector<Person*> visited;
        vector<Person*> recommended;
        queue<Person*> q;
        int depth = 0;
        visited.push_back(ptr);
        for(auto i = (ptr->friends).begin(); i != (ptr->friends).end(); ++i){
            visited.push_back(*i);
            q.push(*i);
        }
        depth++;
        while((!q.empty()) && (depth <= k)){
            Person* p = q.front();
            for(auto j = (p->friends).begin(); j != (p->friends).end(); ++j){
                if(std::find(visited.begin(), visited.end(), *j) != visited.end()){
                    // 
                }
                else{
                    q.push(*j);
                    visited.push_back(*j);
                    recommended.push_back(*j);
                }
            }
            depth++;
            q.pop();
        }
        cout << "For " << ptr->getLName() << ", " << ptr->getFName() << ": \n";
        for(auto i = recommended.begin(); i != recommended.end(); ++i){
            cout << IDName((*i)->getLName(), (*i)->getFName()) << endl;
        }
        cout << "------\n";
        ptr = ptr->next;
    }
}




