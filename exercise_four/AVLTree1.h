#ifndef AVLTREE_H
#define AVLTREE_H
// Updated Fall 21
// Should work reasonably well.
// Report bugs and possible fixes for extra credit.

#include "AVLEntry.h"
#include "bst1.h"

template <typename E>					        // an AVL tree
class AVLTree : public SearchTree< AVLEntry<E> > {
public:
    typedef AVLEntry<E> AVLEntry;			    // an entry
    typedef typename SearchTree<AVLEntry>::Iterator Iterator; // an iterator

protected:
    typedef typename AVLEntry::Key K;			// a key
    typedef typename AVLEntry::Value V;			// a value
    typedef SearchTree<AVLEntry> ST;			// a search tree
    typedef typename ST::TPos TPos;			    // a tree position

public:
    AVLTree() : ST() { }			            // constructor
    
    Iterator insert(const K& k, const V& x)	// insert (k,x)
    {
        TPos v = ST::inserter(k, x);				// insert in base tree
        setHeight(v);					// compute its height
        rebalance(v);					// rebalance if needed
        return Iterator(v);
    }

    void erase(const K& k)	                    // remove key k entry
    {
        TPos v = ST::finder(k, ST::root());		// find in base tree
        if (Iterator(v) == ST::end())			// not found?
            throw NonexistentElement("Erase of nonexistent");
        TPos w = ST::eraser(v);					    // remove it
        rebalance(w);					        // rebalance if needed
    }

    void erase(Iterator p) {			        // remove entry at p
        ST::eraser(p.v);
    }

protected:
    int height(TPos v) const			        // node height utility
    {
        return (v.isExternal() ? 0 : (*v).height());
    }

    void setHeight(TPos v)				        // set height utility
    {
        int hl = height(v.left());
        int hr = height(v.right());
        (*v).setHeight(1 + std::max(hl, hr));	// max of left & right
    }

    bool isBalanced(const TPos& v) const		// is v balanced?
    {
        int bal = height(v.left()) - height(v.right());
        return ((-1 <= bal) && (bal <= 1));
    }

    TPos tallGrandchild(const TPos& z) const	// get tallest grandchild
    {
        TPos zl = z.left();
        TPos zr = z.right();
        if (height(zl) >= height(zr))			// left child taller
            if (height(zl.left()) >= height(zl.right()))
                return zl.left();
            else
                return zl.right();
        else 						// right child taller
            if (height(zr.right()) >= height(zr.left()))
                return zr.right();
            else
                return zr.left();

    }

    void rebalance(const TPos& v)			    // rebalance utility
    {
        TPos z = v;
        while (!(z == ST::root())) {			// rebalance up to root
            z = z.parent();
            setHeight(z);					    // compute new height
            if (!isBalanced(z)) {				// restructuring needed
                TPos x = tallGrandchild(z);
                z = ST::restructure(x);				// trinode restructure
                setHeight(z.left());			// update heights
                setHeight(z.right());
                setHeight(z);
            }
        }
    }

};

#endif