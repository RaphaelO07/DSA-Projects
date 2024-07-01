#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

// Forward declarations
class MetroStop;
class MetroLine;
class AVLNode;

// MetroStop class
class MetroStop
{
private:
    std::string stopName;
    MetroStop *nextStop;
    MetroStop *prevStop;
    MetroLine *line;
    int fare;

public:
    MetroStop(std::string name, MetroLine *metroLine, int fare);

    // Getter methods
    std::string getStopName() const;
    MetroStop *getNextStop() const;
    MetroStop *getPrevStop() const;
    MetroLine *getLine() const;
    int getFare() const;

    // Setter methods
    void setNextStop(MetroStop *next);
    void setPrevStop(MetroStop *prev);
};

MetroStop::MetroStop(std::string name, MetroLine *metroLine, int fare)
{
    stopName = name;
    nextStop = nullptr;
    prevStop = nullptr;
    line = metroLine;
    this->fare = fare;
}

std::string MetroStop::getStopName() const
{
    return stopName;
}

MetroStop *MetroStop::getNextStop() const
{
    return nextStop;
}

MetroStop *MetroStop::getPrevStop() const
{
    return prevStop;
}

MetroLine *MetroStop::getLine() const
{
    return line;
}

int MetroStop::getFare() const
{
    return fare;
}

void MetroStop::setNextStop(MetroStop *next)
{
    nextStop = next;
}

void MetroStop::setPrevStop(MetroStop *prev)
{
    prevStop = prev;
}

// MetroLine class
class MetroLine
{
private:
    std::string lineName;
    MetroStop *node;

public:
    MetroLine(std::string name);

    // Getter methods
    std::string getLineName() const;
    MetroStop *getNode() const;

    // Setter methods
    void setNode(MetroStop *node);

    void populateLine(std::string filename);

    // helper function
    void printLine() const;
    int getTotalStops() const;
};

MetroLine::MetroLine(std::string name)
{
    lineName = name;
    node = nullptr;
}

std::string MetroLine::getLineName() const
{
    return lineName;
}

MetroStop *MetroLine::getNode() const
{
    return node;
}

void MetroLine::setNode(MetroStop *node)
{
    this->node = node;
}

void MetroLine::printLine() const
{
    MetroStop *stop = node;
    while (stop != nullptr)
    {
        cout << stop->getStopName() << endl;
        stop = stop->getNextStop();
    }
}

int MetroLine::getTotalStops() const
{
    int n = 0;
    MetroStop *sn = node;

    while (sn != nullptr)
    {
        n++;
        sn = sn->getNextStop();
    }

    return n;
}

void MetroLine::populateLine(std::string filename)
{
    ifstream fileptr;
    fileptr.open(filename);
    string railname = "";

    for (int i = 0; i < filename.size() - 5; i++)
    {
        railname += i;
    }

    if (railname == lineName)
    {
        cout << "correct line name";
    }

    string line;
    // MetroStop* prevnode = nullptr;

    while (getline(fileptr, line))
    {
        vector<string> words;
        string name = "";
        stringstream s(line);

        string word;
        while (getline(s, word, ' '))
        {
            words.push_back(word);
        }

        int fare = stoi(words[words.size() - 1]);
        words.pop_back();

        for (auto i : words)
        {
            name = name + i;
            name = name + " ";
        }
        string finalname = "";

        for (int i = 0; i < name.size() - 1; i++)
        {
            finalname = finalname + name[i];
        }

        name = finalname;

        MetroStop *node = new MetroStop(name, this, fare);
        MetroStop *cur = this->getNode();
        if (cur == nullptr)
        {
            this->setNode(node);
        }

        else
        {
            while (cur->getNextStop() != nullptr)
            {
                cur = cur->getNextStop();
            }
            cur->setNextStop(node);
            node->setPrevStop(cur);
        }

        //  cout << cur->getLine()->getLineName() << " " << cur->getStopName() << " " << cur->getFare() << endl;
    }
    fileptr.close();

    // rail->printLine();
}

// AVLNode class
class AVLNode
{
private:
    std::string stopName;
    std::vector<MetroStop *> stops;
    AVLNode *left;
    AVLNode *right;
    AVLNode *parent;

public:
    AVLNode(std::string name);

    // Getter methods
    std::string getStopName() const;
    const std::vector<MetroStop *> &getStops() const;
    AVLNode *getLeft() const;
    AVLNode *getRight() const;
    AVLNode *getParent() const;

    // Setter methods
    void addMetroStop(MetroStop *metroStop);
    void setLeft(AVLNode *left);
    void setRight(AVLNode *right);
    void setParent(AVLNode *parent);
};

AVLNode::AVLNode(std::string name)
{
    stopName = name;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

std::string AVLNode::getStopName() const
{
    return stopName;
}

const std::vector<MetroStop *> &AVLNode::getStops() const
{
    return stops;
}

AVLNode *AVLNode::getLeft() const
{
    return left;
}

AVLNode *AVLNode::getRight() const
{
    return right;
}

AVLNode *AVLNode::getParent() const
{
    return parent;
}

void AVLNode::setLeft(AVLNode *left)
{
    this->left = left;
}

void AVLNode::setRight(AVLNode *right)
{
    this->right = right;
}

void AVLNode::setParent(AVLNode *parent)
{
    this->parent = parent;
}

void AVLNode::addMetroStop(MetroStop *metroStop)
{
    stops.push_back(metroStop);
}

// AVLTree class
class AVLTree
{
    // Define your AVLTree implementation here.
private:
    AVLNode *root;

public:
    // constructor not in template
    AVLTree() : root(nullptr) {}

    // getter methods
    AVLNode *getRoot() const;

    // setter methods
    void setRoot(AVLNode *root);

    // helper functions
    int height(AVLNode *node);
    int balanceFactor(AVLNode *node);
    void rotateLeft(AVLNode *node);
    void rotateRight(AVLNode *node);
    void balance(AVLNode *node);
    int stringCompare(string s1, string s2);
    void insert(AVLNode *node, MetroStop *metroStop);
    void populateTree(MetroLine *metroLine);
    void inOrderTraversal(AVLNode *node);
    int getTotalNodes(AVLNode *node);
    AVLNode *searchStop(string stopName);
};

AVLNode *AVLTree::getRoot() const
{
    return root;
}

void AVLTree::setRoot(AVLNode *root)
{
    this->root = root;
}

int AVLTree::height(AVLNode *node)
{
    if (node == nullptr)
    {
        return 0;
    }

    int lH = height(node->getLeft());
    int rH = height(node->getRight());
    return 1 + max(lH, rH);
}

int AVLTree::stringCompare(string s1, string s2)
{
    // use strcmp

    char *c1 = new char[s1.length() + 1];
    strcpy(c1, s1.c_str());

    char *c2 = new char[s2.length() + 1];
    strcpy(c2, s2.c_str());

    int result = strcmp(c1, c2);
    return result;
}

int AVLTree::balanceFactor(AVLNode *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return height(node->getLeft()) - height(node->getRight());
}

void AVLTree::rotateLeft(AVLNode *node)
{

    AVLNode *r = node->getRight();
    AVLNode *rl = r->getLeft();

    r->setLeft(node);
    r->setParent(node->getParent());

    node->setParent(r);
    node->setRight(rl);

    if (rl != nullptr)
    {
        rl->setParent(node);
    }

    if (r->getParent() == nullptr)
    {
        root = r;
    }
    else if (r->getParent()->getLeft() == node)
    {
        r->getParent()->setLeft(r);
    }
    else
    {
        r->getParent()->setRight(r);
    }
}

void AVLTree::rotateRight(AVLNode *node)
{

    AVLNode *r = node->getLeft();
    AVLNode *rl = r->getRight();

    r->setRight(node);
    r->setParent(node->getParent());

    node->setParent(r);
    node->setLeft(rl);

    if (rl != nullptr)
    {
        rl->setParent(node);
    }

    if (r->getParent() == nullptr)
    {
        root = r;
    }
    else if (r->getParent()->getLeft() == node)
    {
        r->getParent()->setLeft(r);
    }
    else
    {
        r->getParent()->setRight(r);
    }
}

void AVLTree::balance(AVLNode *node)
{
    // while(node) {
    int balance = balanceFactor(node);
    if (balance > 1)
    {
        if (balanceFactor(node->getLeft()) < 0)
        {
            rotateLeft(node->getLeft());
        }
        rotateRight(node);
    }
    if (balance < -1)
    {
        if (balanceFactor(node->getRight()) > 0)
        {
            rotateRight(node->getRight());
        }
        rotateLeft(node);
    }
    //   node = node->getParent();
    //}
}

void AVLTree::insert(AVLNode *node, MetroStop *metroStop)
{
    if (!root)
    {
        root = new AVLNode(metroStop->getStopName());
        root->addMetroStop(metroStop);
        return;
    }
    int comp = stringCompare(metroStop->getStopName(), node->getStopName());
    if (comp < 0)
    {
        if (node->getLeft())
        {
            insert(node->getLeft(), metroStop);
        }
        else
        {
            AVLNode *newNode = new AVLNode(metroStop->getStopName());
            newNode->addMetroStop(metroStop);
            node->setLeft(newNode);
            newNode->setParent(node);
        }
    }
    else if (comp > 0)
    {
        if (node->getRight())
        {
            insert(node->getRight(), metroStop);
        }
        else
        {
            AVLNode *newNode = new AVLNode(metroStop->getStopName());
            newNode->addMetroStop(metroStop);
            node->setRight(newNode);
            newNode->setParent(node);
        }
    }
    else
    {
        node->addMetroStop(metroStop);
    }
    balance(node);
}

void AVLTree::populateTree(MetroLine *metroLine)
{
    MetroStop *stop = metroLine->getNode();
    while (stop)
    {
        if (!root)
        {
            root = new AVLNode(stop->getStopName());
            root->addMetroStop(stop);
        }
        else
        {
            insert(root, stop);
        }
        stop = stop->getNextStop();
    }
}

void AVLTree::inOrderTraversal(AVLNode *node)
{
    if (node == nullptr)
    {
        return;
    }
    inOrderTraversal(node->getLeft());
    cout << node->getStopName() << endl;
    inOrderTraversal(node->getRight());
}

int AVLTree::getTotalNodes(AVLNode *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return 1 + getTotalNodes(node->getLeft()) + getTotalNodes(node->getRight());
}

AVLNode *AVLTree::searchStop(string stopName)
{
    AVLNode *cur = root;
    while (cur)
    {
        int comp = stringCompare(stopName, cur->getStopName());
        if (comp < 0)
            cur = cur->getLeft();

        else if (comp > 0)
            cur = cur->getRight();
        else
            return cur;
    }
    return nullptr;
}

// Trip class
class Trip
{
private:
    MetroStop *node;
    Trip *prev;

public:
    Trip(MetroStop *metroStop, Trip *previousTrip);

    // Getter methods
    MetroStop *getNode() const;
    Trip *getPrev() const;
};

Trip::Trip(MetroStop *metroStop, Trip *previousTrip)
{
    node = metroStop;
    prev = previousTrip;
}

MetroStop *Trip::getNode() const
{
    return node;
}

Trip *Trip::getPrev() const
{
    return prev;
}

// Exploration class is a queue that stores unexplored Trip objects
class Exploration
{
private:
    std::queue<Trip *> trips;

public:
    Exploration();

    // Getter methods
    std::queue<Trip *> getTrips() const;

    // Setter methods
    void enqueue(Trip *trip);
    Trip *dequeue();
    bool isEmpty() const;
};

Exploration::Exploration()
{
}

std::queue<Trip *> Exploration::getTrips() const
{
    return trips;
}

void Exploration::enqueue(Trip *trip)
{
    trips.push(trip);
}

Trip *Exploration::dequeue()
{
    if (trips.empty())
    {
        return nullptr;
    }
    Trip *trip = trips.front();
    trips.pop();
    cout << "Dequeued: " << trip->getNode()->getStopName() << endl;
    return trip;
}

bool Exploration::isEmpty() const
{
    return trips.empty();
}

class Path
{
private:
    std::vector<MetroStop *> stops;
    int totalFare;

public:
    Path();

    // Getter methods
    std::vector<MetroStop *> getStops() const;
    int getTotalFare() const;

    // Setter methods
    void addStop(MetroStop *stop);
    void setTotalFare(int fare);

    // helper functions
    void printPath() const;
};

Path::Path()
{
    totalFare = 0;
}

std::vector<MetroStop *> Path::getStops() const
{
    return stops;
}

int Path::getTotalFare() const
{
    return totalFare;
}

void Path::addStop(MetroStop *stop)
{
    stops.push_back(stop);
}

void Path::setTotalFare(int fare)
{
    totalFare = fare;
}

void Path::printPath() const
{
    for (auto stop : stops)
    {
        cout << stop->getStopName() << endl;
    }
}

// PathFinder class
class PathFinder
{
private:
    AVLTree *tree;
    std::vector<MetroLine *> lines;

public:
    PathFinder(AVLTree *avlTree, const std::vector<MetroLine *> &metroLines);
    void createAVLTree();
    Path *findPath(std::string origin, std::string destination);

    // Getter methods
    AVLTree *getTree() const;
    const std::vector<MetroLine *> &getLines() const;
};

PathFinder::PathFinder(AVLTree *avlTree, const std::vector<MetroLine *> &metroLines)
{
    tree = avlTree;
    lines = metroLines;
}

AVLTree *PathFinder::getTree() const
{
    return tree;
}

const std::vector<MetroLine *> &PathFinder::getLines() const
{
    return lines;
}

void PathFinder::createAVLTree()
{
    for (auto line : lines)
    {
        tree->populateTree(line);
    }
}

Path *PathFinder::findPath(std::string origin, std::string destination)
{
   
    // Distances map to store shortest distance (fare) to each station
    std::map<std::string, int> distances;
    
    // Previous stations map to reconstruct the shortest path
    std::map<std::string, std::string> prev_stations;
    
    // Priority queue to store stations based on their cumulative fare
    std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, std::greater<std::pair<int, std::string>>> pq;
    
    // Initialization
    for (auto& line : lines) {
        MetroStop* stop = line->getNode();
        while (stop) {
            distances[stop->getStopName()] = INT_MAX;
            stop = stop->getNextStop();
        }
    }
    distances[origin] = 0;
    pq.push({0, origin});
    
    while (!pq.empty()) {
        int curr_fare = pq.top().first;
        std::string curr_station = pq.top().second;
        pq.pop();
        
        // If we reached the destination, break
        if (curr_station == destination) break;

        // Explore neighbors (i.e., next and previous stops)
        AVLNode* node = tree->searchStop(curr_station);
        for (auto& stop : node->getStops()) {
            if (stop->getNextStop() && distances[stop->getNextStop()->getStopName()] > curr_fare + abs( stop->getNextStop()->getFare()- stop->getFare())) {
                distances[stop->getNextStop()->getStopName()] = curr_fare + abs( stop->getNextStop()->getFare()- stop->getFare());
                prev_stations[stop->getNextStop()->getStopName()] = curr_station;
                pq.push({distances[stop->getNextStop()->getStopName()], stop->getNextStop()->getStopName()});
            }
            
            if (stop->getPrevStop() && distances[stop->getPrevStop()->getStopName()] > curr_fare + abs( stop->getPrevStop()->getFare()- stop->getFare())) {
                distances[stop->getPrevStop()->getStopName()] = curr_fare + abs( stop->getPrevStop()->getFare() - stop->getFare());
                prev_stations[stop->getPrevStop()->getStopName()] = curr_station;
                pq.push({distances[stop->getPrevStop()->getStopName()], stop->getPrevStop()->getStopName()});
            }
        }
    }
    
    // Reconstruct the path
    Path* path = new Path();
    std::string station = destination;
    while (station != origin) {
        path->addStop(tree->searchStop(station)->getStops()[0]);  // Adding the first stop with the given name
        station = prev_stations[station];
    }
    path->addStop(tree->searchStop(origin)->getStops()[0]);  // Adding the origin station
    path->setTotalFare(distances[destination]);
    
    return path;
}

vector<MetroLine *> lines;

// int main()
// {
// }


