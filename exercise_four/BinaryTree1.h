#ifndef BINARY_TREE_H
#define BINARY_TREE_H
// Modified for CSCI 220 Fall 13
// Updated Fall 21
// Added rotate and relink operations to support tri-node restructure

#include <list>
using namespace std;
  
//typedef int Elem;					// base element type
template <typename Elem>
class BinaryTree {
protected:
    // insert Node declaration here...
    struct Node {					// a node of the tree
      Elem    elt;					// element value
      Node*   par;					// parent
      Node*   left;					// left child
      Node*   right;				// right child
      Node() : elt(), par(NULL), left(NULL), right(NULL) { } // constructor
    };

public:
    // insert Position declaration here...
    class Position {					            // position in the tree
    private:
        Node* v;						            // pointer to the node
    public:
        Position(Node* _v = NULL) : v(_v) { }		// constructor
        Elem& operator*()					        // get element
        { return v->elt; }

        Position left() const				        // get left child
        { return Position(v->left); }

        Position right() const				        // get right child
        { return Position(v->right); }

        Position parent() const				        // get parent
        { return Position(v->par); }

        bool isRoot() const				            // root of the tree?
        { return v->par == NULL; }

        bool isExternal() const				        // an external node?
        { return v->left == NULL && v->right == NULL; }

        bool operator==(const Position& p) const    // compare two positions
        { return v == p.v; }

        bool operator!=(const Position& p) const    // compare two positions
        {
            return v != p.v;
        }

        friend class BinaryTree;			        // give tree access
    };

    typedef std::list<Position> PositionList;		// list of positions

 public:
    BinaryTree();					                // constructor
    int size() const ;					            // number of nodes
    bool empty() const;                             // is tree empty?

    Position root() const				            // get the root
	{ return Position(_root); }
	
	PositionList positions() const  			    // list of nodes
	{
		PositionList pl;
		preorder(_root, pl);					    // preorder traversal
		return PositionList(pl);				    // return resulting list
	}
	
	void addRoot();					                // add root to empty tree
    void expandExternal(const Position& p);		    // expand external node

    Position removeAboveExternal(const Position& p)	// remove p and parent
	{
		Node* w = p.v;  Node* v = w->par;			// get p's node and parent
		Node* sib = (w == v->left ?  v->right : v->left);
		if (v == _root) {					        // child of root?
		  _root = sib;					            // ...make sibling root
		  sib->par = NULL;
		}
		else {
		  Node* gpar = v->par;				        // w's grandparent
		  if (v == gpar->left) gpar->left = sib; 	// replace parent by sib
		  else gpar->right = sib;
		  sib->par = gpar;
		}
		delete w; delete v;					        // delete removed nodes
		n -= 2;						                // two fewer nodes
		return Position(sib);
  }

	// housekeeping functions omitted...
protected: 						// local utilities
    void preorder(Node* v, PositionList& pl) const;	// preorder utility

	// translate code from Java version
	void relink(Node* parent, Node* child, bool makeLeftChild)
	{
		child->par = parent;
		if (makeLeftChild)
			parent->left = child;
		else
			parent->right = child;
	}

public:
	// translate code from Java version
    /**
     * Rotates Position p above its parent.  Switches between these
     * configurations, depending on whether p is a or p is b.
     *          b                  a
     *         / \                / \
     *        a  t2             t0   b
     *       / \                    / \
     *      t0  t1                 t1  t2
     *  Caller should ensure that p is not the root.
     */
    void rotate(const Position& p)
	{
		Node* x = p.v;
		Node* y = x->par;						// we assume this exists
		Node* z = y->par;						// grandparent (possibly null)
		if (z == NULL)
		{
			_root = x;                          // x becomes root of the tree
			x->par = NULL;
		}
		else
			relink(z, x, y == z->left);			// x becomes direct child of z
		// now rotate x and y, including transfer of middle subtree
		if (x == y->left)
		{
			relink(y, x->right, true);			// x's right child becomes y's left
			relink(x, y, false);                // y becomes x's right child
		}
		else
		{
			relink(y, x->left, false);           // x's left child becomes y's right
			relink(x, y, true);                 // y becomes left child of x
		}
	}

private:
    Node* _root;					                // pointer to the root
    int n;						                    // number of nodes
  };

template <typename Elem>
BinaryTree<Elem>::BinaryTree()			            // constructor
    : _root(NULL), n(0) { }

template <typename Elem>
int BinaryTree<Elem>::size() const			        // number of nodes
    { return n; }

template <typename Elem>
bool BinaryTree<Elem>::empty() const			    // is tree empty?
    { return size() == 0; }

template <typename Elem>
void BinaryTree<Elem>::addRoot()			        // add root to empty tree
    { _root = new Node; n = 1; }

template <typename Elem>
void BinaryTree<Elem>::expandExternal(const Position& p) {
    Node* v = p.v;					                // p's node
    v->left = new Node;					            // add a new left child
    v->left->par = v;					            // v is its parent
    v->right = new Node;				            // and a new right child
    v->right->par = v;					            // v is its parent
    n += 2;						                    // two more nodes
 }

							// preorder traversal
template <typename Elem>
void BinaryTree<Elem>::preorder(Node* v, PositionList& pl) const {
    pl.push_back(Position(v));				// add this node
    if (v->left != NULL)					// traverse left subtree
        preorder(v->left, pl);
    if (v->right != NULL)					// traverse right subtree
        preorder(v->right, pl);
}
#endif