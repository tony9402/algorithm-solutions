// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/lru-cache/submissions/329445622
class LRUCache {
public:
    int capacity;
    list< pair<int,int> > lruList;     // key, value pair
    unordered_map< int, list<pair<int,int>>::iterator > hash;   // key to <key,val> iterator map

    void moveToFront( int key, int value ) {
	    // erase and add a new entry to front
        lruList.erase( hash[key] ); // this is O(1) since we are using iterator
        lruList.push_front( make_pair(key, value) );
        hash[key] = lruList.begin();
    }
public:
    LRUCache( int capacity ) {
        this->capacity = capacity;
    }

    int get( int key ) {
        if( hash.find(key) == hash.end() )
            return -1;
		// move the key, value pair to front
        int value = (*hash[key]).second;
        moveToFront( key, value );
        return (*hash[key]).second;
    }

    void put( int key, int value ) {
        if( hash.find(key) != hash.end() ) {
            // when key is already in hash
            moveToFront( key, value );
        } else {
		    // add to the cache
            lruList.push_front( make_pair( key, value ) );
            hash[key] = lruList.begin();
            if( hash.size() > capacity ) {
                // erase
                hash.erase( lruList.back().first );
                lruList.pop_back();
            }
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

/* Solution Description
*/
