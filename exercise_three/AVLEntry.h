#ifndef AVLENTRY_H
#define AVLENTRY_H
// Updated Fall 21 

template <typename E>
class AVLEntry : public E {				    // an AVL entry
private:
    int ht;						            // node height

protected:						            
    typedef typename E::Key K;				// key type
    typedef typename E::Value V;			// value type
    int height() const { return ht; }		// get height
    void setHeight(int h) { ht = h; }		// set height

public:						
    AVLEntry(const K& k = K(), const V& v = V())	// constructor
        : E(k, v), ht(0) { }

    template <typename T>
    friend class AVLTree;				// allow AVLTree access
};
#endif
