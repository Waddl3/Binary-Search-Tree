#ifndef BST_H
#define BST_H
// Modified for CSCI 220 Fall 15
// Updated Fall 21

#include "BinaryTree.h"
#include "RuntimeExceptions.h"

template <typename E>
class SearchTree {									// a binary search tree
public: 											// public types
    typedef typename E::Key K;						// a key
    typedef typename E::Value V;					// a value
    class Iterator;									// an iterator/position

    SearchTree(): T(), n(0)
    { T.addRoot(); T.expandExternal(T.root()); }	// create the super root

	int size() const {								// number of entries
		return n;
	}; 	

	bool empty() const {							// is the tree empty?
		size() == 0;
	}

    Iterator find(const K& k) {
		TPos v = finder(k, root());					// search from virtual root
		if (!v.isExternal()) return Iterator(v);	// found it
		else return end();							// didn't find it
	  }

    Iterator insert(const K& k, const V& x)			// insert (k,x)
    { TPos v = inserter(k, x); return Iterator(v); }

    void erase(const K& k) { //throw(NonexistentElement) {
		TPos v = finder(k, root());					// search from virtual root
		if (v.isExternal())							// not found?
		  throw NonexistentElement("Erase of nonexistent");
		eraser(v);									// remove it
	  }

    void erase(Iterator& p)							// remove entry at p
    { eraser(p.v); }

    Iterator begin() {
		TPos v = root();							// start at virtual root
		while (!v.isExternal()) v = v.left();		// find leftmost node
		return Iterator(v.parent());
	}

    Iterator end()									// iterator to end entry
    { return Iterator(T.root()); }					// return the super root

  protected:										// local utilities
    typedef BinaryTree<E> BinaryTree;				// linked binary tree
    typedef typename BinaryTree::Position TPos;		// position in the tree

    TPos root() const { return T.root().left(); }	// left child of super root

    TPos finder(const K& k, TPos v){
		//TPos finder(const K & k, TPos & v) {
			if (v.isExternal()) return v;			// key not found
		if (k < (*v).key()) 
			return finder(k, v.left());				// search left subtree
		else if ((*v).key() < k) 
			return finder(k, v.right());			// search right subtree
		else 
			return v;								// found it here
	  }
	/* this version alows duplicates
    TPos inserter(const K& k, const V& x) {
		TPos v = finder(k, root());					// search from virtual root
		while (!v.isExternal())						// key already exists?
		  v = finder(k, v.right());					// look further
		T.expandExternal(v);						// add new internal node
		(*v).setKey(k); (*v).setValue(x);			// set entry
// operator -> is not overloaded
//		v->setKey(k); v->setValue(x);				// set entry
		n++;										// one more entry
		return v;									// return insert position
	}
	*/

	// no duplicates -- modified by T. Vo
	TPos inserter(const K& k, const V& x) {
		TPos v = finder(k, root());					// search from virtual root
		if (!v.isExternal())						// key already exists?
			(*v).setValue(x);						// replace value
		else
		{
			T.expandExternal(v);					// add new internal node
			(*v).setKey(k); (*v).setValue(x);		// set entry
			n++;									// one more entry
		}
		return v;									// return insert position
	}

	TPos eraser(TPos& v) {
		TPos w;
		if (v.left().isExternal()) w = v.left();	// remove from left
		else if (v.right().isExternal()) 
			w = v.right();							// remove from right
		else {										// both internal?
		  w = v.right();							// go to right subtree
		  do { w = w.left(); } while (!w.isExternal());	// get leftmost node
		  TPos u = w.parent();
		  (*v).setKey((*u).key()); 
		  (*v).setValue((*u).value());				// copy w's parent to v
		}
		n--;										// one less entry
		return T.removeAboveExternal(w);			// remove w and parent
	  }
// not needed here
 //   TPos restructure(const TPos& v); 				// restructure
      	// throw(BoundaryViolation);
  
private: 											// member data
    BinaryTree T;									// the binary tree
    int n;											// number of entries

public:
    // ...insert Iterator class declaration here
    class Iterator {	                      		// an iterator/position
    private:
      TPos v;										// which entry
    public:
      Iterator(const TPos& vv) : v(vv) { }			// constructor

      const E& operator*() const { return *v; }		// get entry (read only)

      E& operator*() { return *v; }					// get entry (read/write)

      bool operator==(const Iterator& p) const		// are iterators equal?
	  { return v == p.v; }

	  Iterator& operator++( ){
		TPos w = v.right();
		if (!w.isExternal()) {						// have right subtree?
		  do { v = w; w = w.left(); }				// move down left chain
		  while (!w.isExternal());
		}
		else {
		  w = v.parent();							// get parent
		  while (v == w.right())					// move up right chain
			{ v = w; w = w.parent(); }
		  v = w;									// and first link to left
		}
		return *this;
	  }

      friend class SearchTree;						// give search tree access
    };
  };
#endif