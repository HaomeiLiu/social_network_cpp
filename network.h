
#ifndef NETWORK_H
#define NETWORK_H

#include "person.h"
#include "date.h"
#include "misc.h"
// You may need to add more libraries 
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <string>
#include <queue> 

using namespace std;

class Network{

    private:
        // head pointed to the first element (node) of the linked list
        Person* head;
        // tail pointed to the last element (node) of the linked list
        Person* tail;
        int count; 
        Person* search(string fname, string lname, string bdate);
        // II
        Person* search(string queryid);

    public:
        Network();
        Network(string fileName);
        ~Network();
        void push_front(Person* newEntry);
        void push_back(Person* newEntry);
        bool remove(string fname, string lname, string bdate);
        void saveDB(string filename);
        void loadDB(string filename);
        void printDB();
        void showMenu();
        bool has_db_extension(char const *name);
        // II
        void friends_recommendation(int k);
};

#endif
