#include <bits/stdc++.h>
using namespace std;


class StudentRecord{
private:
    string studentName;
    string rollNumber;

public:
    string get_studentName() {
        return studentName;
    }
    void set_studentName(string Name) {
        studentName = Name;
    }
    string get_rollNumber() {
        return rollNumber;
    }
    void set_rollNumber(string rollnum) {
        rollNumber = rollnum;
    }
};

class Node{
	private:
		Node* next;
		StudentRecord* element;
	public:
    Node()
    {
        next=nullptr;
        element = nullptr;
    }
	    Node* get_next() {
	        return next; 
	    }
	    StudentRecord* get_element() {
	        return element; 
	    }

	    void set_next(Node* value){
	    	next = value;
	    }
	    void set_element(StudentRecord* student){
	    	element = student;
	    }

};

class Entity {
private:
    string name;
    Node* iterator;

public:
Entity()
{
    iterator = nullptr;
}
    string get_name() {
        return name;
    }
    void set_name(string Name) {
        name = Name;
    }
    Node* get_iterator() {
        return iterator;
    }
    void set_iterator(Node* iter) {
        iterator = iter;
    }
};
vector<StudentRecord*> studentsss;
vector<StudentRecord> students;

class LinkedList : public Entity {
    // Implement LinkedList members here
    public:

        LinkedList()
        {
            set_iterator(nullptr);
        }
        void add_student(StudentRecord student){
            Node* neww= new Node;
            StudentRecord* addstd = new StudentRecord;
            addstd->set_studentName(student.get_studentName());
            addstd->set_rollNumber(student.get_rollNumber());
            studentsss.push_back(addstd);
            students.push_back(*addstd);
            neww->set_element(studentsss[studentsss.size()-1]);
            neww->set_next(nullptr);
            Node* point = get_iterator();
            if(point == nullptr)
            {
                set_iterator(neww);
            }
            else{
            while(point->get_next() != nullptr)
            {
                point = point->get_next();
            }
            point->set_next(neww);
            }
        

        }

        void delete_student(string studentName){
            Node* search = get_iterator();
            if( search == nullptr)
            {
                cout<<"linklist not found \n";
                return;

            }
            Node* prev = nullptr;
            int ispresent = 0;
            if(search->get_element()->get_studentName()==studentName)
            {
                ispresent = 1;
            
                Node* tempo = search->get_next();
                set_iterator(tempo);
                delete search;
            }
            else
            {
                prev = search;
                search = search->get_next();
            while(search != nullptr)
            {
                if(search->get_element()->get_studentName() == studentName)
                {
                    ispresent = 1;
                    
                    Node* tempptr = search->get_next();
                    
                    prev->set_next(tempptr);
                    delete search;
                    break;
                }
                prev = search;
                search = search->get_next();
            }
            }

            if(ispresent == 0)
            {
                cout<<"student not found"<<endl;
            }

            
        }
};

vector<LinkedList> EntityArray;

void addinLinkedList(string club1, StudentRecord* stdptr)
{
    LinkedList club;
    int temp = 0;

    int k=0;
    for( auto j : EntityArray)
            {
                
                if(j.get_name()== club1)
                {
                    club=j;
                    temp = 1;
                    break;

                }

                k++;
            }

    if(temp == 0)
            {
                LinkedList cc;
                cc.set_name(club1);
                Node* stud = new Node;
                stud->set_element(stdptr);
                stud->set_next(nullptr);
                cc.set_iterator(stud);
                EntityArray.push_back(cc);
            }

    else if(temp == 1)
    {
        Node* iter = club.get_iterator();
        int exists = 0;
        while(iter->get_next()!= nullptr)
        {   //CODE TO CHECK FOR DUPLICATE ENTRIES BY ROLL NUMBER
           /* string inproll = stdptr->get_rollNumber();
            string itroll = iter->get_element()->get_rollNumber();
            

           // cout<<itroll<<"\n"<<inproll<<endl;
            if(itroll == inproll)
            {
                exists = 1;
                break;
            }*/
            iter = iter->get_next();
        }

        if(exists == 0 && iter->get_element()->get_rollNumber() == (stdptr->get_rollNumber()))
        {
            exists = 1;
        }

        if(exists == 0)
        {
             Node* newstd = new Node;
                newstd->set_element(stdptr);
                newstd->set_next(nullptr);

            iter->set_next(newstd);
        }

       /* else if(exists == 1)
        {
            cout<<"student already exists in list"<<endl;
        }*/
    }
}



void read_input_file(string file_path){

    ifstream file_pointer;

    file_pointer.open(file_path);

    string line;

    while(getline(file_pointer,line))
    {
        stringstream s(line);
        string stdrec;
        
        StudentRecord* sc = new StudentRecord;
        getline(s,stdrec,',');
        

        sc->set_studentName(stdrec);

        getline(s,stdrec,',');
        
        sc->set_rollNumber(stdrec);
        
        studentsss.push_back(sc);
        students.push_back(*sc);

        StudentRecord* stdptr = studentsss[studentsss.size()-1];

        
        string branch;

        getline(s,branch,',');
        addinLinkedList(branch,stdptr);
        string ign;
        getline(s,ign,'[');
       
        string cb;
        getline(s,cb,']');

        stringstream cbl(cb);
        int i =0;
       
        string club1;
        while(getline(cbl,club1,','))
        {
           
            addinLinkedList(club1,stdptr);
            
            i++;

            
        };

        getline(s,ign,',');
        string hostel;
        getline(s,hostel,',');
        addinLinkedList(hostel,stdptr);
      
        getline(s,ign,'[');

       
        string soci;
        getline(s,soci,']');

        stringstream socil(soci);
        i =0;
       
        string soci1;
        while(getline(socil,soci1,','))
        {
           
            addinLinkedList(soci1,stdptr);
           
            i++;
            
        };

    };



};

/* int main()
{
    read_input_file("details.txt");
   
   return 0;


} 

*/
