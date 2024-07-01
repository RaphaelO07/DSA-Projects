#include <bits/stdc++.h>
using namespace std;


class IndexEntry
{
private:
    string word;
    vector<pair<string, int>> chapter_word_counts;

public:
    IndexEntry(string word_val) : word(word_val) {}

    void setWord(string word_val)
    { 
        word = word_val;
    }

    string getWord()
    { 
        return word;
    }

    void setChapterWordCounts(vector<pair<string, int>> chapter_word_counts_val)
    { 
        chapter_word_counts = chapter_word_counts_val;
    }

    vector<pair<string, int>> getChapterWordCounts()
    { 
        return chapter_word_counts;
    }
};

class HybridNode
{
public:
    string key;
    string element;
    HybridNode *parent;
    HybridNode *left_child;
    HybridNode *right_child;
    HybridNode *next_node;
    string color = "red";

    HybridNode(string key_val, string element_val) : key(key_val), element(element_val), parent(nullptr), left_child(nullptr), right_child(nullptr), next_node(nullptr) {}

    bool isleftchild() { return this == parent->left_child; }

    HybridNode *uncle()
    {
        if (parent == nullptr or parent->parent == nullptr)
            return nullptr;

        if (parent->isleftchild())
            return (*((*parent).parent)).right_child;
        else
            return (*((*parent).parent)).left_child;
    }

    HybridNode *sibling()
    {
        
        if (parent == nullptr)
            return nullptr;

        if (isleftchild())
            return parent->right_child;

        return parent->left_child;
    }

    void downmover(HybridNode *newparent)
    {
        if (parent != nullptr)
        {
            if (isleftchild())
            {
                parent->left_child = newparent;
            }
            else
            {
                parent->right_child = newparent;
            }
        }
        newparent->parent = parent;
        parent = newparent;
    }

    bool ischildred()
    {
        return (left_child != nullptr and left_child->color == "red") or
               (right_child != nullptr and right_child->color == "red");
    }
};

class WordInfo
{
public:
    std::string word;
    std::map<std::string, int> histogram; 

    WordInfo(std::string w) : word(w) {}

    void addOccurrence(const std::string &chapter, int occurrence_count = 1)
    {
        histogram[chapter] += occurrence_count;
    }
};

class MRU
{
public:
    unordered_map<string, WordInfo *> histo;
    WordInfo *mostrecent;

    void addinhisto(HybridNode *wordzz)
    {
        WordInfo *occur = histo[wordzz->key];
        if (occur == nullptr)
        {
            occur = new WordInfo(wordzz->key);
            histo[wordzz->key] = occur;
        }

        histo[wordzz->key]->addOccurrence(wordzz->element);
        mostrecent = occur;
        return;
    }
};

MRU all_words;

class RedBlackTree
{
private:
    HybridNode *root;

    void swapColors(HybridNode *x1, HybridNode *x2)
    {
        string temp;
        temp = (*x1).color;
        (*x1).color = x2->color;
        x2->color = temp;
    }

    void swapValues(HybridNode *u, HybridNode *v)
    {
        string temp;
        string temp2;
        temp = u->key;
        temp2 = u->element;
        u->key = v->key;
        u->element = v->element;
        v->key = temp;
        v->element = temp2;
    }

    HybridNode *BSTInsert(HybridNode *root, HybridNode *newNode, int *p, HybridNode **address)
    {

        if (!root)
        {
            all_words.addinhisto(newNode);
            return newNode;
        }
        if ((*root).key == newNode->key)
        {
            all_words.addinhisto(newNode);
            delete newNode;
            newNode = nullptr;
            *p = 0;
            *address = root;
            return root;
        }

        if (newNode->key < (*root).key)
        {
            (*root).left_child = BSTInsert((*root).left_child, newNode, p, address);
            (*((*root).left_child)).parent = root;
        }
        else if (newNode->key > (*root).key)
        {
            (*root).right_child = BSTInsert((*root).right_child, newNode, p, address);
            (*root).right_child->parent = root;
        }

        return root;
    }

    void leftRotate(HybridNode *x)
    {
        HybridNode *y = (*x).right_child;
        (*x).right_child = y->left_child;

        if (y->left_child)
            (*(y->left_child)).parent = x;

        y->parent = x->parent;

        if (!x->parent)
            root = y;
        else if (x == (*(x->parent)).left_child)
            (*(x->parent)).left_child = y;
        else
            (*(x->parent)).right_child = y;

        y->left_child = x;
        x->parent = y;
    }

    void rightRotate(HybridNode *y)
    {
        HybridNode *x = y->left_child;
        y->left_child = (*x).right_child;

        if ((*x).right_child)
            (*((*x).right_child)).parent = y;

        x->parent = y->parent;

        if (!y->parent)
            root = x;
        else if (y == (*(y->parent)).left_child)
            y->parent->left_child = x;
        else
            (*(y->parent)).right_child = x;

        x->right_child = y;
        y->parent = x;
    }

    void fixViolations(HybridNode *z)
    {
        HybridNode *parent = nullptr;
        HybridNode *grandparent = nullptr;

        while ((z != root) && (z->color != "black") && (z->parent->color == "red"))
        {
            parent = z->parent;
            grandparent = parent->parent;

            if (parent == grandparent->left_child)
            {
                HybridNode *uncle = (*grandparent).right_child;

                if (uncle && (*uncle).color == "red")
                {
                    (*grandparent).color = "red";
                    parent->color = "black";
                    uncle->color = "black";
                    z = grandparent;
                }
                else
                {
                    if (z == parent->right_child)
                    {
                        leftRotate(parent);
                        z = parent;
                        parent = z->parent;
                    }
                    rightRotate(grandparent);
                    swap(parent->color, (*grandparent).color);
                    z = parent;
                }
            }
            else
            {
                HybridNode *uncle = (*grandparent).left_child;

                if (uncle && uncle->color == "red")
                {
                    (*grandparent).color = "red";
                    parent->color = "black";
                    (*uncle).color = "black";
                    z = grandparent;
                }
                else
                {
                    if (z == parent->left_child)
                    {
                        rightRotate(parent);
                        z = parent;
                        parent = z->parent;
                    }
                    leftRotate(grandparent);
                    swap(parent->color, (*grandparent).color);
                    z = parent;
                }
            }
        }

        (*root).color = "black";
    }


    HybridNode *successor(HybridNode *x)
    {
        HybridNode *temp = x;

        while (temp->left_child != nullptr)
            temp = (*temp).left_child;

        return temp;
    }

 
    HybridNode *replacernode(HybridNode *x)
    {
        
        if (x->left_child != nullptr and (*x).right_child != nullptr)
            return successor(x->right_child);

       
        if ((*x).left_child == nullptr and x->right_child == nullptr)
            return nullptr;

        
        if (x->left_child != nullptr)
            return x->left_child;
        else
            return (*x).right_child;
    }

    HybridNode *minimumValueNode(HybridNode *node)
    {
        while (node->left_child)
            node = node->left_child;
        return node;
    }

    void fixDeleteViolations(HybridNode *x)
    {
        if (x == root)
            
            return;

        HybridNode *sibling = x->sibling(), *parent = x->parent;
        if (sibling == nullptr)
        {
            
            fixDeleteViolations(parent);
        }
        else
        {
            if ((*sibling).color == "red")
            {
                
                parent->color = "red";
                (*sibling).color = "black";
                if ((*sibling).isleftchild())
                {
                    
                    rightRotate(parent);
                }
                else
                {
                    
                    leftRotate(parent);
                }
                fixDeleteViolations(x);
            }
            else
            {
                if ((*sibling).ischildred())
                {
                    
                    if ((*sibling).left_child != nullptr and (*((*sibling).left_child)).color == "red")
                    {
                        if ((*sibling).isleftchild())
                        {
                            
                            (*(sibling->left_child)).color = sibling->color;
                            (*sibling).color = parent->color;
                            rightRotate(parent);
                        }
                        else
                        {
                            
                            (*((*sibling).left_child)).color = parent->color;
                            rightRotate(sibling);
                            leftRotate(parent);
                        }
                    }
                    else
                    {
                        if ((*sibling).isleftchild())
                        {
                            
                            (*(sibling->right_child)).color = parent->color;
                            leftRotate(sibling);
                            rightRotate(parent);
                        }
                        else
                        {
                            
                            (*((*sibling).right_child)).color = (*sibling).color;
                            (*sibling).color = parent->color;
                            leftRotate(parent);
                        }
                    }
                    parent->color = "black";
                }
                else
                {
                   
                    sibling->color = "red";
                    if ((*parent).color == "black")
                        fixDeleteViolations(parent);
                    else
                        parent->color = "black";
                }
            }
        }
    }

     bool deleter(HybridNode *v)
    {
        HybridNode *u = replacernode(v);

        bool uvBlack = ((u == nullptr or u->color == "black") and (v->color == "black"));
        HybridNode *parent = v->parent;

        if (u == nullptr)
        {
           
            if (v == root)
            {
                
                root = nullptr;
            }
            else
            {
                if (uvBlack)
                {
                    
                    fixDeleteViolations(v);
                }
                else
                {
                    
                    if (v->sibling() != nullptr)
                        
                        (*(v->sibling())).color = "red";
                }

                
                if (v->isleftchild())
                {
                    (*parent).left_child = nullptr;
                }
                else
                {
                    parent->right_child = nullptr;
                }
            }
            delete v;
            return true;
        }

        if (v->left_child == nullptr or v->right_child == nullptr)
        {
            
            if (v == root)
            {
                
                v->key = u->key;
                v->element = (*u).element;
                v->left_child = (*v).right_child = nullptr;
                delete u;
            }
            else
            {
               
                if ((*v).isleftchild())
                {
                    parent->left_child = u;
                }
                else
                {
                    parent->right_child = u;
                }
                delete v;
                (*u).parent = parent;
                if (uvBlack)
                {
                   
                    fixDeleteViolations(u);
                }
                else
                {
                   
                    u->color = "black";
                }
            }
            return true;
        }

        swapValues(u, v);
        deleter(u);

        return true;
    }

public:
    RedBlackTree() : root(nullptr) {}

    void inordermaker(HybridNode *x, vector<IndexEntry> &result, int tc, vector<string> cnames)
    {

        if (x == nullptr)
        {
            return;
        }

        inordermaker(x->left_child, result, tc, cnames);
        WordInfo *lol = all_words.histo[x->key];
        IndexEntry *neww = new IndexEntry(x->key);
        vector<pair<string, int>> counts;
        
        for (auto y : cnames)
        {
            pair<string, int> pairs;
            auto itt = lol->histogram.find(y);
            if (itt == lol->histogram.end())
            {
                pairs = make_pair(y, 0);
            }
            else
            {
                pairs = *itt;
            }

            counts.push_back(pairs);
        }

        neww->setChapterWordCounts(counts);
        result.push_back(*neww);
        inordermaker((*x).right_child, result, tc, cnames);
    }

    void visualizeTree(HybridNode *root, std::ofstream &outFile)
    {
        if (root == nullptr)
            return;

       
        outFile << "  " << (*root).key << " [color=" << ((*root).color == "red" ? "red" : "black") << ", fontcolor=white];\n";

        
        if ((*root).left_child != nullptr)
        {
            outFile << "  " << (*root).key << " -> " << (*root).left_child->key << ";\n";
            visualizeTree((*root).left_child, outFile);
        }

        
        if ((*root).right_child != nullptr)
        {
            outFile << "  " << (*root).key << " -> " << (*root).right_child->key << ";\n";
            visualizeTree((*root).right_child, outFile);
        }
    }

    HybridNode *getRoot()
    {
        return root;
    }

    void setRoot(HybridNode *node)
    {
        root = node;
    }

    HybridNode *insert(string key, string element)
    {
        HybridNode *newNode = new HybridNode(key, element);
        int k = 1;
        int *p = &k;
        HybridNode **address = &newNode;
        root = BSTInsert(root, newNode, p, address);
        if (*p == 1)
        {
            newNode->color = "red";
            fixViolations(newNode);
            return newNode;
        }
        else
        {
            return *address;
        }
    }

   
    bool deleteNode(string key)
    {
        HybridNode *v = search(key);
        if (!v)
        {
           
            return false;
        }
        else
        {
            bool result = deleter(v);
            return result;
        }
    }

    vector<HybridNode *> traverseUp(HybridNode *node)
    {
        vector<HybridNode *> path;
        while (node)
        {
            path.push_back(node);
            node = node->parent;
        }
        return path;
    }

    vector<HybridNode *> traverseDown(HybridNode *node, string bit_sequence)
    {
        vector<HybridNode *> path;
        for (char bit : bit_sequence)
        {
            path.push_back(node);
            if (bit == '1' && (*node).left_child != nullptr)
                node = node->left_child;

            else if (bit == '0' && node->right_child != nullptr)
                node = (*node).right_child;

            else
            {
                cout << "sequence too long";
                break;
            }
        }
        return path;
    }

    vector<HybridNode *> preOrderTraversal(HybridNode *node, int depth)
    {
        vector<HybridNode *> result;
        if (node == nullptr || depth < 0)
        {
            return result;
        }

        
        result.push_back(node);

        
        vector<HybridNode *> left_result = preOrderTraversal(node->left_child, depth - 1);
        result.insert(result.end(), left_result.begin(), left_result.end());

      
        vector<HybridNode *> right_result = preOrderTraversal(node->right_child, depth - 1);
        result.insert(result.end(), right_result.begin(), right_result.end());

        return result;
    }
    HybridNode *search(string key)
    {
        HybridNode *node = root;
        while (node)
        {
            if (key < node->key)
                node = (*node).left_child;
            else if (key > (*node).key)
                node = node->right_child;
            else
                return node;
        }
        return nullptr;
    }

    int blackheight(HybridNode *node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        int left_black_height = blackheight(node->left_child);

        int right_black_height = blackheight(node->right_child);
        if (left_black_height != right_black_height)
        {
            cout << " tree is not correct. error at" << node->key << endl;
            //return -1;
        }

        return left_black_height + (node->color == "black" ? 1 : 0);
    }

    int getblackdepth(HybridNode *node)
    {
        int depth = 0;
        while (node)
        {
            if (node->color == "black")
                depth++;
            node = node->parent;
        }
        return depth;
    }
};



class Lexicon
{
private:
    RedBlackTree red_black_tree; 
    int total_chapters;
    vector<string> chapnames;

public:
    Lexicon() {}

    void setRedBlackTree(RedBlackTree tree)
    { 
        red_black_tree = tree;
    }

    RedBlackTree getRedBlackTree()
    { 
        return red_black_tree;
    }

    void readChapters(vector<string> chapter_names)
    {
        total_chapters = chapter_names.size();

        for (auto j : chapter_names)
        {
            string i;
            if (j.size() >= 4 && j.substr(j.size() - 4) == ".txt")
            {
                i = j.substr(0, j.size() - 4);
            }
            else
            {
                i = j;
            }
            chapnames.push_back(i);
            ifstream chapters(j);

            string line;
            vector<string> words;
            while (getline(chapters, line))
            {
                std::string word;
                stringstream lines(line);
                while (getline(lines, word, ' '))
                {

                    if (!word.empty() && ispunct(word.front()))
                    {
                        word.erase(word.begin());
                    }

                    if (!word.empty() && std::ispunct(word.back()))
                    {
                        word.pop_back();
                    }

                    if (!word.empty())
                    {

                        words.push_back(word);
                        word.clear();
                    }
                }

                for (auto ka : words)
                {

                    transform(ka.begin(), ka.end(), ka.begin(), ::tolower);

                    red_black_tree.insert(ka, i);
                }
            }
        }

        pruneRedBlackTree();
    }

    vector<IndexEntry> buildIndex()
    {
        vector<IndexEntry> result;
        red_black_tree.inordermaker(red_black_tree.getRoot(), result, total_chapters, chapnames);

        return result;
    }

    void pruneRedBlackTree()
    {
        for (auto wordss : all_words.histo)
        {
            int count = 0;
            for (auto chaps : wordss.second->histogram)
            {
                if (chaps.second > 0)
                {
                    count++;
                }
            }

            if (count >= total_chapters)
            {
                red_black_tree.deleteNode(wordss.first);
        
            }
        }
    }
};
