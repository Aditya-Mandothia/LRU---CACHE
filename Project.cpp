#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    string key;
    int val;

    Node(string key, int val)
    {
        this->key = key;
        this->val = val;
    }
};

class LRUCache
{
public:
    int maxSize;
    list<Node> l;
    unordered_map<string, list<Node>::iterator> m;

    LRUCache(int maxSize)
    {
        this->maxSize = maxSize > 1 ? maxSize : 1; // minimum size is 1.
    }

    void insertKeyValue(string key, int value)
    {
        // 2 cases

        if (m.count(key) != 0)
        {
            // if present in map replace the old value with the new value.
            auto it = m[key];
            it->val = value;
        }
        else
        {
            // if not present in map,
            // we will check whether the cache is full or not
            // and if it is full we will remove the LEAST RECENTLY USED ITEM
            if (l.size() == maxSize)
            {
                Node last = l.back();
                m.erase(last.key); // to remove from hashmap
                l.pop_back();      // remove from Linked List
            }

            Node n(key, value);
            l.push_front(n);
            m[key] = l.begin();
        }
    }

    int *getValue(string key)
    {
        if(m.count(key)!=0){
            auto it = m[key];
            int val = it->val;

            l.push_front(*it); //pushing the node at it address at the front of DLL
            l.erase(it);

            m[key]=l.begin();
            return &l.begin()->val;
        }

        return NULL;
    }

    string mostRecentKey()
    {
        return l.front().key;
    }

};

int main()
{   
    LRUCache lru(3);
    lru.insertKeyValue("Mango",10);
    lru.insertKeyValue("Apple",20);
    lru.insertKeyValue("Guava",30);

    cout<<lru.mostRecentKey()<<endl;

    


    return 0;
}