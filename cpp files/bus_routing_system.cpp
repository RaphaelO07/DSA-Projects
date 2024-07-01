#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <string>

class Vehicle;

class Trip {
public:
    Trip(Vehicle* vehicle, std::string pick_up_location, std::string drop_location, int departure_time)
        : vehicle(vehicle), pick_up_location(pick_up_location), drop_location(drop_location), departure_time(departure_time), booked_seats(0) {}

    // Getter functions
    Vehicle* getVehicle() const {
        return vehicle;
    }

    std::string getPickUpLocation() const {
        return pick_up_location;
    }

    std::string getDropLocation() const {
        return drop_location;
    }

    int getDepartureTime() const {
        return departure_time;
    }

    int getBookedSeats() const {
        return booked_seats;
    }

    // Setter functions
    void setVehicle(Vehicle* v) {
        vehicle = v;
    }

    void setPickUpLocation(std::string location) {
        pick_up_location = location;
    }

    void setDropLocation(std::string location) {
        drop_location = location;
    }

    void setDepartureTime(int time) {
        departure_time = time;
    }

    void setBookedSeats(int seats) {
        booked_seats = seats;
    }


private:
    Vehicle* vehicle;
    std::string pick_up_location;
    std::string drop_location;
    int departure_time;
    int booked_seats;
};

class BinaryTreeNode {
public:
    BinaryTreeNode(int departuretime = 0, Trip* tripenodeptr = nullptr, BinaryTreeNode* parentptr = nullptr)
        : leftptr(nullptr), rightptr(nullptr), parentptr(parentptr), departuretime(departuretime), tripnodeptr(tripenodeptr) {}

    // Getter functions
    BinaryTreeNode* getLeftPtr() const {
        return leftptr;
    }

    BinaryTreeNode* getRightPtr() const {
        return rightptr;
    }

    BinaryTreeNode* getParentPtr() const {
        return parentptr;
    }

    int getDepartureTime() const {
        return departuretime;
    }

    Trip* getTripNodePtr() const {
        return tripnodeptr;
    }

    // Setter functions
    void setLeftPtr(BinaryTreeNode* left) {
        leftptr = left;
    }

    void setRightPtr(BinaryTreeNode* right) {
        rightptr = right;
    }

    void setParentPtr(BinaryTreeNode* parent) {
        parentptr = parent;
    }

    void setDepartureTime(int time) {
        departuretime = time;
    }

    void setTripNodePtr(Trip* trip) {
        tripnodeptr = trip;
    }

private:
    BinaryTreeNode* leftptr;
    BinaryTreeNode* rightptr;
    BinaryTreeNode* parentptr;
    int departuretime;
    Trip* tripnodeptr;
};

class TransportService {
public:
    TransportService(std::string name) : name(name), BSThead(nullptr) {}

    // Getter functions
    std::string getName() const {
        return name;
    }

    BinaryTreeNode* getBSTHead() const {
        return BSThead;
    }

    // Setter functions
    void setName(std::string service_name) {
        name = service_name;
    }

    void setBSTHead(BinaryTreeNode* node) {
        BSThead = node;
    }

    void addTrip(int key, Trip* trip){

         if(trip->getDropLocation()!=name)
        {
            std::cout<<"Drop location did not match";
            return;
        }
        else
        {
        if(BSThead == nullptr)
        {
            BSThead = new BinaryTreeNode(key,trip);
        }

        else
        {
            BinaryTreeNode* curnode = BSThead;
            BinaryTreeNode* prevnode = nullptr;

            while(curnode!=nullptr)
            {
                prevnode=curnode;
                if(key<=curnode->getDepartureTime())
                {
                    curnode=curnode->getLeftPtr();
                }

                else
                {
                    curnode=curnode->getRightPtr();
                }
            }

            BinaryTreeNode* neww = new BinaryTreeNode(key,trip,prevnode);

            if(key<=prevnode->getDepartureTime())
                {
                    prevnode->setLeftPtr(neww);
                }

                else
                {
                    prevnode->setRightPtr(neww);
                }
        }
        }
    }

private:
    std::string name;
    BinaryTreeNode* BSThead;
};



class Vehicle {
public:
    Vehicle(std::string vehicle_number, int seating_capacity)
        : vehicle_number(vehicle_number), seating_capacity(seating_capacity) {}

    // Getter functions
    std::string getVehicleNumber() const {
        return vehicle_number;
    }

    int getSeatingCapacity() const {
        return seating_capacity;
    }

    // Setter functions
    void setVehicleNumber(std::string number) {
        vehicle_number = number;
    }

    void setSeatingCapacity(int capacity) {
        seating_capacity = capacity;
    }

    void addTrip(Trip* trip) {
        trips.push_back(trip);
    }

    const std::vector<Trip*>& getTrips() const {
        return trips;
    }

private:
    std::string vehicle_number;
    int seating_capacity;
    std::vector<Trip*> trips;
};

class Location {
public:
    Location(std::string name) : name(name) {}

    // Getter functions
    std::string getName() const {
        return name;
    }

    TransportService* getServicePtr(std::string droplocation) const {

        TransportService* serptr = nullptr;
        for(auto i : serviceptrs)
        {
            if(i->getName()==droplocation)
            {
                serptr = i;
            }
        }
        return serptr;
    }

    // Setter functions
    void setName(std::string location_name) {
        name = location_name;
    }

    TransportService* setServicePtr(std::string droplocation) {
        
        TransportService* serptr = nullptr;
        for(auto i : serviceptrs)
        {
            if(i->getName()==droplocation)
            {
                serptr = i;
            }
        }

        if(serptr == nullptr)
        {
            serptr = new TransportService(droplocation);
            serviceptrs.push_back(serptr);
        }
        return serptr;
    }
    //////////do i have to push all trips or just with pick up loc?
    void addTrip(Trip* trip) {
         if(trip->getPickUpLocation()!=this->name)
        {
            return ;
        }
        else 
        {
            trips.push_back(trip);   //////
        }
    }

    std::vector<TransportService*> getservicevector(){
        return serviceptrs;
    }

private:
    std::string name;
    std::vector<TransportService* >serviceptrs;
    std::vector<Trip*> trips;
};

class BinaryTree {
protected:
    BinaryTreeNode* root;

public:
    BinaryTree() : root(nullptr) {}

    int getHeight() const {
        return getHeighttemp(root);

    }

    int getNumberOfNodes() const {
        return getnumberofnodestemp(root);
    }

    BinaryTreeNode* get_root()
    {
        return root;
    }

    void set_root(BinaryTreeNode* rr)
    {
        root = rr;
    }

    private:
    int getHeighttemp(BinaryTreeNode* node) const
    {
        if(node == nullptr)
        return 0;

        else
        {
            int leftheight = getHeighttemp(node->getLeftPtr());
            int rightheight = getHeighttemp(node->getRightPtr());

            if(leftheight>=rightheight)
            return (leftheight + 1);

            else
            return (rightheight + 1);
        }

    }

    int getnumberofnodestemp(BinaryTreeNode* node) const
    {
        if (node == nullptr)
        return 0;

        else
        {
            int leftnodes = getnumberofnodestemp(node->getLeftPtr());
            int righnodes = getnumberofnodestemp(node->getRightPtr());

            return ( leftnodes + righnodes + 1);
        }
    }
};

class BinarySearchTree : public BinaryTree {
private:
BinaryTreeNode* getmaxtemp(BinaryTreeNode* node) const
{

    if(node == nullptr)
    return nullptr;

    while(node->getRightPtr()!= nullptr)
    {
        node = node->getRightPtr();

    }

    return node;
}

BinaryTreeNode* getmintemp(BinaryTreeNode* node) const
{
    if(node == nullptr)
       return nullptr;

    while(node->getLeftPtr()!= nullptr)
    {
       node = node->getLeftPtr();
    }

    return node;
}

BinaryTreeNode* searchnodebykey(int key, BinaryTreeNode* node) const
{
    BinaryTreeNode* curnode = node;
    BinaryTreeNode* reqnode = nullptr;
        
    while(curnode!=nullptr)
    {
        if(curnode->getDepartureTime()== key)
        return curnode;

        else
        {    
            if(curnode->getDepartureTime() > key)
            {   
                reqnode = curnode;
                curnode = curnode->getLeftPtr();
            }

            else if (curnode->getDepartureTime() < key)
            {
                curnode= curnode->getRightPtr();
            }
                
        }
    }
    return reqnode;
}

public:
    BinarySearchTree() {}

    BinaryTreeNode* getElementWithMinimumKey() const {
         return getmintemp(root);
         
    }

    BinaryTreeNode* getElementWithMaximumKey() const {
        return getmaxtemp(root); 
    }

    BinaryTreeNode* searchNodeWithKey(int key) const {
        return searchnodebykey(key,root);
    }

    BinaryTreeNode* getSuccessorNode(BinaryTreeNode* node) const {
        if(node==nullptr)
        return nullptr;

        else if(node->getRightPtr()!= nullptr)
        return getmintemp(node->getRightPtr());

        else
        {
            BinaryTreeNode* p = node->getParentPtr();
            while(p != nullptr && node!=p->getLeftPtr())
            {
                node = p;
                p=p->getParentPtr();
            }

            return p;

        }
    }

    BinaryTreeNode* getSuccessorNodeByKey(int key) const {
        BinaryTreeNode* keynode = searchnodebykey(key,root);
       if(keynode->getDepartureTime()==key)
       return getSuccessorNode(keynode);

       else
       {
        std::cout<<"key not present in bst";
        return nullptr;
       }
    }

    BinaryTreeNode* getPredecessorNode(BinaryTreeNode* node) const {
        if(node==nullptr)
        return nullptr;
       
        if(node->getLeftPtr()!= nullptr)
        return getmaxtemp(node->getLeftPtr());
       
        else if (node->getLeftPtr()==nullptr)
        {
            BinaryTreeNode* p = node->getParentPtr();
            while(p != nullptr && node!=p->getRightPtr())
            {
                node = p;
                p=p->getParentPtr();
            }

            return p;

        }
    }

    BinaryTreeNode* getPredecessorNodeByKey(int key) const {
        BinaryTreeNode* keynode = searchnodebykey(key,root);
        if(keynode->getDepartureTime()==key)
       return getPredecessorNode(keynode);

       else
       {
        std::cout<<"key not present in bst";
        return nullptr;
       }
    }

    void remove_node(BinaryTreeNode* node){

        if(node == nullptr)
        return;

        BinaryTreeNode* parent = node->getParentPtr();

            if(parent == nullptr)
            {
                if(node->getLeftPtr()==nullptr && node->getRightPtr()==nullptr)
                {
                    delete node;
                    return;
                }

               else if(node->getLeftPtr()== nullptr || node->getRightPtr()== nullptr)
                {
                    BinaryTreeNode* onlychild;
                    if(node->getLeftPtr()!= nullptr)
                    {
                        onlychild = node->getLeftPtr();
                    }

                    else{
                        onlychild = node->getRightPtr();
                    }

                    onlychild->setParentPtr(nullptr);

                    delete node;
                    return;

                }

                else if(node->getLeftPtr()!= nullptr && node->getRightPtr()!= nullptr)
                {
                    
                    BinaryTreeNode* replacer = getSuccessorNode(node);

                    BinaryTreeNode* repparent = replacer->getParentPtr();

                    if(repparent==node)
                    {
                        replacer->setLeftPtr(node->getLeftPtr());

                        replacer->setParentPtr(nullptr);

                        node->getLeftPtr()->setParentPtr(replacer);
                    }

                    else
                    {
                        repparent->setLeftPtr(replacer->getRightPtr());
                        replacer->getRightPtr()->setParentPtr(repparent);

                        replacer->setLeftPtr(node->getLeftPtr());
                        node->getLeftPtr()->setParentPtr(replacer);

                        replacer->setRightPtr(node->getRightPtr());
                        node->getRightPtr()->setParentPtr(replacer);

                        replacer->setParentPtr(nullptr);
                    }

                    delete node;
                    return;
                }
                

            }


            if(parent!=nullptr)
            {
                if(node->getLeftPtr()==nullptr && node->getRightPtr()==nullptr)
                {
                    if(parent->getLeftPtr()==node)
                    parent->setLeftPtr(nullptr);

                    if(parent->getRightPtr()==node)
                    parent->setRightPtr(nullptr);

                    delete node;
                    return;

                }

                else if(node->getLeftPtr()== nullptr || node->getRightPtr()== nullptr)
                {
                    BinaryTreeNode* onlychild;
                    if(node->getLeftPtr()!= nullptr)
                    {
                        onlychild = node->getLeftPtr();
                    }

                    else{
                        onlychild = node->getRightPtr();
                    }

                    if(parent->getLeftPtr()==node)
                    {
                        parent->setLeftPtr(onlychild);
                        onlychild->setParentPtr(parent);
                    }

                    else if(parent->getRightPtr()==node)
                    {
                        parent->setRightPtr(onlychild);
                        onlychild->setParentPtr(parent);
                    }

                    delete node;
                    return;

                }

                 else if(node->getLeftPtr()!= nullptr && node->getRightPtr()!= nullptr)
                {
                    
                    BinaryTreeNode* replacer = getSuccessorNode(node);

                    BinaryTreeNode* repparent = replacer->getParentPtr();

                    if(repparent==node)
                    {
                        replacer->setLeftPtr(node->getLeftPtr());
                        node->getLeftPtr()->setParentPtr(replacer);

                        replacer->setParentPtr(parent);

                        if(parent->getLeftPtr()==node)
                        {
                            parent->setLeftPtr(replacer);
                        }

                        else if(parent->getRightPtr()==node)
                        {
                            parent->setRightPtr(replacer);
                        }

                    }

                    else
                    {
                        repparent->setLeftPtr(replacer->getRightPtr());
                        replacer->getRightPtr()->setParentPtr(repparent);

                        replacer->setLeftPtr(node->getLeftPtr());
                        node->getLeftPtr()->setParentPtr(replacer);

                        replacer->setRightPtr(node->getRightPtr());
                        node->getRightPtr()->setParentPtr(replacer);

                        replacer->setParentPtr(parent);

                        if(parent->getLeftPtr()==node)
                        {
                            parent->setLeftPtr(replacer);
                        }

                        else if(parent->getRightPtr()==node)
                        {
                            parent->setRightPtr(replacer);
                        }


                    }

                    delete node;
                    return;
                }
            }

    }



};

class TravelDesk {
public:
    void addTrip(std::string vehicle_number, int seating_capacity, std::string pick_up_location, std::string drop_location, int departure_time) {
        if(departure_time>2400||departure_time<0)
        {
            std::cout<<"invalid time";
            return;
        }
        
        
        Vehicle* vehicle = nullptr;
        int present = 0;
        int correctseats = 0;
        for(auto i : vehicles)
        {
            if(i->getVehicleNumber()==vehicle_number)
            {
                present = 1;
                vehicle = i;

                if(i->getSeatingCapacity()==seating_capacity)
                {
                    correctseats = 1;
                    break;
                }
            }

        }

        if(present == 0)
        {
            vehicle = new Vehicle(vehicle_number,seating_capacity);
            vehicles.push_back(vehicle);
            present = 1;
            correctseats = 1;
        }

        
        if(present == 0)
        {
            std::cout<<"vehicle was not created";
            return;
        }
        
        if(correctseats == 0)
        {
            std::cout<<"seating capacity of trip did not match the vehicle";
            return;
        }

        Trip* neww = new Trip(vehicle,pick_up_location,drop_location,departure_time);

        vehicle->addTrip(neww);

        int picklocpresent = 0;
        int droplocpresent = 0;
        Location* pick = nullptr;
        Location* drop = nullptr;
        for(auto i : locations)
        {
            if(pick_up_location==i->getName())
            {
                pick = i;
                picklocpresent = 1;
            }

            if(drop_location==i->getName())
            {
                drop = i;
                droplocpresent = 1;
            }

        }

        if(picklocpresent == 0)
        {
            pick = new Location(pick_up_location);
            locations.push_back(pick);
        }

        if(droplocpresent == 0)
        {
            drop = new Location(drop_location);
            locations.push_back(drop);
        }

        pick->addTrip(neww);
        drop->addTrip(neww);

        TransportService* servptr = pick->getServicePtr(drop_location);

        if(servptr == nullptr)
        {
            servptr = pick->setServicePtr(drop_location);
        }
        // Add the trip to the TransportService's BST
        servptr->addTrip(departure_time,neww);

    }

    std::vector<Trip*> showTrips(std::string pick_up_location, int after_time, int before_time) {
         Location* locptr = nullptr;
        std::vector<Trip*> reqtrips;

        if(before_time>2400 || after_time>2400 || before_time<0 || after_time<0)
        {
            std::cout<<"invalid time";
            return reqtrips;
        }
       

        if(after_time > before_time)
        {
            int temp = after_time;
            after_time = before_time;
            before_time = temp;
        }

        for(auto i : locations)
        {
            if(i->getName() == pick_up_location)
            {
                locptr = i;
                break;
            }
        }

        if(locptr == nullptr)
        {
            std::cout<<"location not found";
            return reqtrips;
        }

        std::vector<TransportService*> services = locptr->getservicevector();

        for( auto s : services)
        {
            if(s == nullptr)
            {
                continue;
            }

            BinaryTreeNode* treenode = s->getBSTHead();

            if(treenode == nullptr)
            {
                continue;
            }

            BinarySearchTree tree;
            tree.set_root(treenode);
            BinaryTreeNode* firsttrip = tree.searchNodeWithKey(after_time);


            while(firsttrip->getDepartureTime()>=after_time && firsttrip->getDepartureTime()< before_time)
            {
                reqtrips.push_back(firsttrip->getTripNodePtr());
                firsttrip = tree.getSuccessorNode(firsttrip);

                if(firsttrip == nullptr)
                {
                    break;
                }
            }

        }  


        return reqtrips; 


    }


    std::vector<Trip*> showTripsbydestination(std::string pick_up_location, std::string destination,int after_time, int before_time) {
        
        Location* locptr = nullptr;
        std::vector<Trip*> reqtrips;

        if(before_time>2400 || after_time>2400 || before_time<0 || after_time<0)
        {
            std::cout<<"invalid time";
            return reqtrips;
        }

        if(after_time > before_time)
        {
            int temp = after_time;
            after_time = before_time;
            before_time = temp;
        }

        for(auto i : locations)
        {
            if(i->getName() == pick_up_location)
            {
                locptr = i;
                break;
            }
        }

        if(locptr == nullptr)
        {
            std::cout<<"location not found";
            return reqtrips;
        }

        TransportService* ssptr = locptr->getServicePtr(destination);

         if(ssptr == nullptr || ssptr->getName()!=destination)
        {
            std::cout<<"service ptr not found";
            return reqtrips;
        }

        BinaryTreeNode* treenode = ssptr->getBSTHead();

        if(treenode == nullptr)
        {
            std::cout<<"no trips from this location";
            return reqtrips;
        }

        BinarySearchTree tree;
        tree.set_root(treenode);
        BinaryTreeNode* firsttrip = tree.searchNodeWithKey(after_time);

        while(firsttrip->getDepartureTime()>=after_time && firsttrip->getDepartureTime()< before_time)   //strictly less that before time.
        {
             reqtrips.push_back(firsttrip->getTripNodePtr());
             firsttrip = tree.getSuccessorNode(firsttrip);
        }

        return reqtrips;


    }

    Trip* bookTrip(std::string pick_up_location, std::string drop_location, std::string vehicle_number, int departure_time) {
        
        if(departure_time>2400||departure_time<0)
        {
            std::cout<<"invalid time";
            return nullptr;
        }

        Location* locptr = getLocation(pick_up_location);

         if(locptr == nullptr)
        {
            std::cout<<"location not found";
            return nullptr;
        }

        TransportService* ser = locptr->getServicePtr(drop_location);

        if(ser == nullptr)
        {
            std::cout<<"no service for this drop location";
            return nullptr;
        }

        BinaryTreeNode* tkey = ser->getBSTHead();

        if(tkey== nullptr)
        {
           std::cout<<"no trips";
           return nullptr;
        }

        BinarySearchTree tree;
        tree.set_root(tkey);
        BinaryTreeNode* tr;

        tr = tree.searchNodeWithKey(departure_time);

        if(tr==nullptr)
        {
            std::cout<<"no trip found";
            return nullptr;
        }

        if(tr->getDepartureTime()!= departure_time || tr->getTripNodePtr()->getVehicle()->getVehicleNumber()!=vehicle_number || tr->getTripNodePtr()->getDropLocation()!=drop_location)
        {
            std::cout<<"trip not found";
            return nullptr;
        }


        if(tr->getTripNodePtr()->getVehicle()->getSeatingCapacity()<=tr->getTripNodePtr()->getBookedSeats())
        {
            tree.remove_node(tr);
            std::cout<<"no seats";
            return nullptr;
        }

        else{
            int bookedseats = tr->getTripNodePtr()->getBookedSeats();

            tr->getTripNodePtr()->setBookedSeats(bookedseats + 1);
            Trip* tripnode = tr->getTripNodePtr();
            if(tr->getTripNodePtr()->getBookedSeats()==tr->getTripNodePtr()->getVehicle()->getSeatingCapacity())
            {
                tree.remove_node(tr);
            }

            return tripnode;

        }


    }
    Location* getLocation(std::string location){
        Location* loc = nullptr;
        for(auto i : locations)
        {
            if(i->getName()==location)
            {
                loc = i;
            }
        }

        return loc;
    }


    void readinputfromfile(std::string filename)
    {
    std::ifstream file_pointer;

    file_pointer.open(filename);

    std::string line;

    while(std::getline(file_pointer,line))
    {
        std::stringstream command(line);

        std::vector<std::string> func;
        std::string words;

        while(std::getline(command,words,' '))
        {
            if(words=="" || words[0]==' ')
            {
                continue;
            }

            func.push_back(words);

        }

        if(func[0]=="ADDTRIP")
        {
            int deptime = timestringtoint(func[5]);
            int seatcap = std::stoi(func[2]); 
            addTrip(func[1],seatcap,func[3],func[4],deptime);
        }

        else if(func[0]=="BOOKTRIP")
        {
            int dept = timestringtoint(func[4]);
            bookTrip(func[1],func[2],func[3],dept);
        }

        else if(func[0]=="SHOWTRIPS")
        {
            int aft = timestringtoint(func[2]);
            int bef = timestringtoint(func[3]);
            showTrips(func[1],aft,bef);
        }
        
        else if(func[0]=="SHOWTRIPSBYDESTINATION")
        {
            int a = timestringtoint(func[3]);
            int b = timestringtoint(func[4]);
            showTripsbydestination(func[1],func[2],a,b);
        }

        else
        {
            continue;
        }  

    }

    return;

    };

    int timestringtoint(std::string time)
    {
        std::stringstream s(time);
        
        std::string hour;
        std::string min;

        std::getline(s,hour,':');
        std::getline(s,min);

        int t = std::stoi(hour+min);

        return t;

    }

private:
    std::vector<Vehicle*> vehicles;
    std::vector<Location*> locations;
};




/*int main(){
    std::cout<<"hello";
}*/