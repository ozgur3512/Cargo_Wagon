#include <iostream> 
#include <fstream>
#include <stdlib.h>

#include "linkedList.h"

using namespace std;

int main(int argc, char* argv[]) {
	system("clear");// make this line as comment if you are compiling on Linux or Mac
	//system("cls"); // make this line as comment if you are compiling on Windows

    LinkedList newLinkedList;
    
    ifstream infile(argv[1]); 
    
    
    string new_string ="";
    int in = 1;
    Node* p = newLinkedList.head;
    cout<<newLinkedList.head<<endl;
    
    while (getline(infile, new_string)){
        char a=new_string[0];

        if(in){
            newLinkedList.head=new Node(a);
            p = newLinkedList.head;
            in=0;
        }
        else{
            p->set_next(new Node(a));
            p = p->get_next();

        }
        


        
        
    }
    
        
   
    
    cout<<endl;
    cout<<"Readed letters in linked list: ";
    newLinkedList.printList();

    newLinkedList.reorderList();
    cout<<"After reordering: ";
    newLinkedList.printList();

    newLinkedList.removeDublicates();
    cout<<"After removing dublicates: ";
    newLinkedList.printList();
    
    newLinkedList.reverseList();
    cout<<"Reversed list: ";
    newLinkedList.printList();


    return EXIT_SUCCESS;
}
/* @Author
Student Name: Özgür Seferoðlu
Student ID : 150190068
Date: 26.10.2021 */
