#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <fstream>
#include <sstream>
#include <map>
#include <cassert>
#include <unordered_map>
using namespace std;

class PhoneRecord {
private:
    string name;
    string organisation;
    vector<string> phoneNumbers;

public:
    // Constructor
    PhoneRecord(const string& n, const string& org, const vector<string>& numbers)
        : name(n), organisation(org), phoneNumbers(numbers) {}

    // Getter methods
    string getName() const {
        return name;
    }

    string getOrganisation() const {
        return organisation;
    }

    vector<string> getPhoneNumbers() const {
        return phoneNumbers;
    }
};

class HashTableRecord {
private:
    int key;
    PhoneRecord* element; // Pointer to PhoneRecord
    HashTableRecord* next;

public:
    // Constructor
    HashTableRecord(int k, PhoneRecord* rec)
        : key(k), element(rec), next(nullptr) {}

    // Getter methods
    int getKey() const {
        return key;
    }

    PhoneRecord* getRecord() const {
        return element;
    }

    HashTableRecord* getNext() const {
        return next;
    }

    void setNext(HashTableRecord* nxt) {
        next = nxt;
    }
};

class PhoneBook {
private:
    static const int HASH_TABLE_SIZE = 263;
    HashTableRecord* hashTable[HASH_TABLE_SIZE];

public:
    // Constructor
    PhoneBook() {
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            hashTable[i] = nullptr;
        }
    }

    // Add your own implementation for hashing
    long long computeHash(const string& str)
    {
        const int p = 1000000007;
        long long x = 1;
        const int m = 263;
        long long h = static_cast<int>(str[0]) ;

        for (int i = 1;i<str.size();i++)
        {
            x = x*m;
            h = h + ( ((long long)str[i])*(x%p));

        }

        h = (h%m);
        return h;

    }

    
    // Add your own implementation for adding a contact
    void addContact(const PhoneRecord* record)
        {
            string s = record->getName();
            stringstream name(s);
            string parts;
            PhoneRecord* newrec = new PhoneRecord(s,record->getOrganisation(),record->getPhoneNumbers());

            vector<PhoneRecord*> checker = fetchContacts(new string(s));
            {
                for(auto i : checker)
                {
                    if(i->getName()==s && i->getOrganisation()==newrec->getOrganisation() && i->getPhoneNumbers()==newrec->getPhoneNumbers())
                    {
                    cout<<"repeated contact\n";
                    return;
                    }
                }
            }
           while(getline(name,parts,' '))
            {
                int h = computeHash(parts);
                
                HashTableRecord* rec = new HashTableRecord(h,newrec);

                if(hashTable[h]==nullptr)
                {
                    hashTable[h]= rec;
                    continue;
                }

                else
                {
                    HashTableRecord* ptr = hashTable[h];
                    while(ptr->getNext()!= nullptr)
                    {
                        ptr = ptr->getNext();
                    }

                    ptr->setNext(rec);

                }

                
            }
        }

    // Add your own implementation for deleting a contact
    bool deleteContact(const string* searchName)
    {
        vector<PhoneRecord*> searcher = fetchContacts(searchName);

        if(searcher.empty())
        {
            return false;
        }

        PhoneRecord* first= searcher[0];
        stringstream name(first->getName());
        string nn;
        int present = 0;
        while(getline(name,nn,' '))
        {
            int ha = computeHash(nn);
            HashTableRecord* ptr = hashTable[ha];
            
            if(ptr==nullptr)
            {
                continue;
            }
            else if(ptr->getRecord()==first)
            {
                hashTable[ha]=hashTable[ha]->getNext();
                delete ptr;
                present = 1;
                continue;
            }
            if(ptr->getNext()!=nullptr)
            {  
                HashTableRecord* prev = ptr;
                ptr = ptr->getNext();
                while(ptr!=nullptr)
                {
                    if(ptr->getRecord()==first)
                    { 
                        prev->setNext(ptr->getNext());
                        delete ptr;
                        present = 1;
                        break;
                    }
                    prev = ptr;
                    ptr = ptr->getNext();
                }

            }
        }
        if(present == 0)
        {
            return false;
        }

        else
        {
            return true;
        }

    }

    // Add your own implementation for fetching contacts
    vector<PhoneRecord*> fetchContacts(const string* query)
    {
    unordered_map<PhoneRecord*, int> recordCount;
    vector<PhoneRecord*> result;
    stringstream nn(*query);
    string word;


    while(getline(nn,word,' ')) {
        int hash = computeHash(word);
        HashTableRecord* cur = hashTable[hash];
        while (cur) {
            string gg = " " + word;
            string lol = word + " ";
            string mam = " " + word + " ";
            string ll = word;
            int zig = cur->getRecord()->getName().find(gg);
            zig = zig + (gg.size());
            int gig = cur->getRecord()->getName().find(lol);
            
            
            if ((cur->getRecord()->getName().find(lol) != string::npos && gig == 0)|| (cur->getRecord()->getName().find(gg) != string::npos && zig == cur->getRecord()->getName().size()) || (cur->getRecord()->getName().find(mam) != string::npos) || (cur->getRecord()->getName() == ll) ) {
                
                recordCount[cur->getRecord()]++;
            }
            cur = cur->getNext();
        }
    }

    
    vector<PhoneRecord*> temp;
   
    map<int,vector<PhoneRecord*>> sorted;

    for(auto i : recordCount)
    {
        sorted[i.second].push_back(i.first);
    }

    for(auto i : sorted)
    {
        int k = i.second.size();
        for(int j = k-1; j >=0;j-- )
        {
            temp.push_back(i.second[j]);
    }
    }
    for(int i = temp.size()-1;i>=0;i--)
    {
        result.push_back(temp[i]);
    }

    return result;



    }

    // Add your own implementation for counting records pointing to a contact
    int countRecordsPointingTo(const PhoneRecord* record) const
    {
           /* string name = record->getName();
            stringstream b(name);
            string wor;
            int occur=0;
            while(getline(b,wor,' '))
            {
                int k = computeHash(wor);

                HashTableRecord* ptr = hashTable[k];

                while(ptr!=nullptr)
                {
                    if(ptr->getRecord()==record)
                    {
                        occur++;
                    }

                    ptr= ptr->getNext();
                }

            }

            return occur;*/

            int oc=0;
            for(int i=0;i<HASH_TABLE_SIZE;i++)
            {
                if(hashTable[i]!=nullptr)
                {
                    HashTableRecord* pt = hashTable[i];
                    
                    while(pt!=nullptr)
                    {
                        if(pt->getRecord()==record)
                        {
                            oc++;
                        }
                        pt = pt->getNext();
                        
                    }

                }

                
            }
            return oc;
    }

    // Add your own implementation for reading records from a file
    void readRecordsFromFile(const string& filename)
        {
            ifstream file_pointer;

            file_pointer.open(filename);

            string line;

            while(getline(file_pointer,line))
            {
                stringstream s(line);
                string peoplerec;
                
                string name;
                getline(s,peoplerec,',');
                

                name = peoplerec;
                vector<string>num;

                while(getline(s,peoplerec,','))
                {
                    num.push_back(peoplerec);
                }
                string organisation = num[num.size()-1];
                num.pop_back();

                PhoneRecord* newphnrec = new PhoneRecord(name,organisation,num);

                addContact(newphnrec);

                delete newphnrec;
                
                
            



            };
        }

    // Destructor
   /*~PhoneBook(){
    for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
        HashTableRecord* now = hashTable[i];
        while (now != nullptr) {
            HashTableRecord* temp = now;
            now = now->getNext();
            PhoneRecord* ptr = temp->getRecord();
            delete (ptr); 
            delete temp;
        }
    }

   }*/

 
};

/*int main()
{
    PhoneBook phone;
    phone.readRecordsFromFile("Details.txt");
    return 0;

}*/


       