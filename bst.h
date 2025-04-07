#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    // static successor function
    static Node<Key, Value>* successor(Node<Key, Value>* current); // TODO
    // delete subtree -- recursive function
    void deleteSubtree(Node<Key,Value>* current);
    // isbalancedhelper -- recursive function
    int isBalancedHelper(Node<Key,Value>* current) const;


protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    current_ = NULL;

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return current_ == rhs.current_;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return current_ != rhs.current_;

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    current_ = successor(current_);
    return (*this);
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
    root_ = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
    Node<Key, Value>* current = root_;

    // Check if tree is empty
    if(empty()){
      Node<Key, Value>* newNode = new Node<Key,Value>(keyValuePair.first, keyValuePair.second, NULL);
      root_ = newNode;
      // leave the function
      return;
    }

    // While true
    while(true){
      // if keys are equal 
      if(keyValuePair.first == current->getKey()) {
        // update value of key
        current->setValue(keyValuePair.second);
        // leave the loop and function
        break;
      }
      // if current node's key is larger
      else if(keyValuePair.first < current->getKey()) {
        // check if left subtree is NULL
        if(current->getLeft()==NULL){
          // create new node (DYNAMIC ALLOCATION)
          Node<Key, Value>* newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, current);
          // set current node (newNode's parent)'s left node
          current->setLeft(newNode);

          // leave the loop and function
          break;
        }
        // recurse to left subtree
        else {
          current = current->getLeft();
        }
      }
      // if current node's key is smaller
      else {
        // check if right subtree is NULL
        if(current->getRight()==NULL){
          // create new node (DYNAMIC ALLOCATION)
          Node<Key, Value>* newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, current);
          // set current node (newNode's parent)'s right node
          current->setRight(newNode);

          // leave the loop and function
          break;
        }
        // recurse to right subtree
        else {
          current = current->getRight();
        }
      }
    }
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    // key does not exist
    Node<Key, Value>* remove = internalFind(key);
    if(remove == NULL){
      return;
    }

    // --- CASE 1: NO CHILDREN
    if(remove->getLeft()==NULL && remove->getRight()==NULL){
      // Set parent's pointer to this node as NULL
      Node<Key, Value>* removeParent = remove->getParent();
      if(removeParent==NULL){
        root_ = NULL;
      }
      else if(removeParent->getKey() >remove->getKey()){
        removeParent->setLeft(NULL);
      } else {
        removeParent->setRight(NULL);
      }
      // remove node
      delete remove;
      return;
    }


    // --- CASE 2 AND 3: ONE CHILD
    if(remove->getLeft()==NULL || remove->getRight()==NULL){
      // --- CASE 2: left child only
      if(remove->getRight()==NULL){
        // promote child
        Node<Key,Value>* child = remove->getLeft();
        nodeSwap(remove, child);
      }
      // --- CASE 3: right child only
      else if(remove->getLeft()==NULL){
        // promote child
        Node<Key,Value>* child = remove->getRight();
        nodeSwap(remove, child);
      }

      // fix the relations

      // variables
      Node<Key,Value>* removeParent = remove->getParent();
      Node<Key,Value>* leftChild = remove->getLeft();
      Node<Key,Value>* rightChild = remove->getRight();

      if(rightChild!=NULL && leftChild!=NULL){
        removeParent->setLeft(leftChild);
        leftChild->setParent(removeParent);
        removeParent->setRight(rightChild);
        rightChild->setParent(removeParent);
      }
      else if(rightChild!=NULL){
        removeParent->setRight(rightChild);
        rightChild->setParent(removeParent);
        removeParent->setLeft(NULL);
      }
      else if(leftChild!=NULL) {
        removeParent->setLeft(leftChild);
        leftChild->setParent(removeParent);
        removeParent->setRight(NULL);
      }
      else {
        removeParent->setLeft(NULL);
        removeParent->setRight(NULL);
      }
      delete remove;
      return;

    }


    // --- CASE 4: TWO CHILDREN
    // two children
    if(remove->getLeft()!=NULL && remove->getRight()!=NULL) {
      // promote predecessor
      nodeSwap(remove, predecessor(remove));
    }

    // variables
    Node<Key,Value>* removeParent = remove->getParent();
    Node<Key,Value>* leftChild = remove->getLeft();
    Node<Key,Value>* rightChild = remove->getRight();

      // remove has left child
      if(leftChild!=NULL){
        // if remove is the root
        if(removeParent==NULL){
          root_ = leftChild;
          leftChild->setParent(removeParent);
        }
        // remove is left child
        if(removeParent->getLeft()==remove){
          removeParent->setLeft(leftChild);
          leftChild->setParent(removeParent);
        }
        // remove is right child
        else {
          removeParent->setRight(leftChild);
          leftChild->setParent(removeParent);
        }
      }
      // remove has right child
      else if(rightChild!=NULL){
        // if remove is the root
        if(removeParent==NULL){
          root_ = rightChild;
          rightChild->setParent(removeParent);
        }
        // remove is left child
        if(removeParent->getLeft()==remove){
          removeParent->setLeft(rightChild);
          rightChild->setParent(removeParent);
        }
        // remove is right child
        else {
          removeParent->setRight(rightChild);
          rightChild->setParent(removeParent);
        }
      }
      // otherwise, no child
      else {
        /*
        // if remove is the root
        if(removeParent==NULL){
          root_ = NULL;
        }*/
        // remove is left child
        if(removeParent->getLeft()==remove){
          removeParent->setLeft(NULL);
        }
        // remove is right child
        else {
          removeParent->setRight(NULL);
        }
      }

    delete remove;
}


template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    // if left child exists
    if(current->getLeft()!=NULL){
      current = current->getLeft();
      // predecessor = rightmost node
      while(current->getRight()!=NULL){
        current = current->getRight();
      }
      return current;
    }
    // if left child does not exist
    else {
      current = current->getParent();
      // if you get to root, there is no predecessor
      if(current==NULL){
        return NULL;
      }
      // if you get to root, there is no predecessor
      while(current->getParent()!=NULL && current->getParent()->getLeft()==current){
        current = current->getParent();
      }
      return current->getParent();
    }
}

// added helper function: successor
template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
    // TODO
    if(current==NULL){
      return NULL;
    }
    // if right child exists
    if(current->getRight()!=NULL){
      current = current->getRight();
      // predecessor = leftmost node
      while(current->getLeft()!=NULL){
        current = current->getLeft();
      }
      return current;
    }
    // if right child does not exist
    else {
      //current = current->getParent();
      // if you get to root, there is no successor
      if(current==NULL){
        return NULL;
      }
      
      // if you get to root, there is no successor
      while(current->getParent()!=NULL && current->getParent()->getRight()==current){
        current = current->getParent();
      }
      return current->getParent();
    }
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    deleteSubtree(root_);
    root_ = NULL;
}


// added helper function: delete subtree -- recursive function
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::deleteSubtree(Node<Key,Value>* current){
  if(current==NULL){
    return;
  }
  deleteSubtree(current->getLeft());
  deleteSubtree(current->getRight());
  delete current;
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    // return NULL if tree is empty
    if(empty()){
      return NULL;
    }

    Node<Key, Value>* current = root_;
    while(current->getLeft()!=NULL){
      current = current->getLeft();
    }
    return current;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    Node<Key, Value>* current = root_;

    // Check if subtree is empty
    if(empty()){
      return NULL;
    }

    // While true
    while(true){
      // key does not exist
      if(current==NULL){
        return NULL;
      }
      // if keys are equal, found the node!
      else if(key == current->getKey()){
        return current;
      }
      // if current node's key is larger
      else if(key < current->getKey()) {
        current = current->getLeft();
      }
      // if current node's key is smaller
      else {
        current = current->getRight();
      }
    }
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    return isBalancedHelper(root_) != -1;
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::isBalancedHelper(Node<Key,Value>* current) const
{
  // Path ends here
  if(current==NULL){
    return 0;
  }
  
  int leftDepth = isBalancedHelper(current->getLeft());
  if(leftDepth == -1){
    return -1;
  }
  int rightDepth = isBalancedHelper(current->getRight());
  if(rightDepth == -1){
    return -1;
  }

  if(std::abs(leftDepth-rightDepth) > 1){
    return -1;
  }

  return std::max(leftDepth, rightDepth) + 1;
}


template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
