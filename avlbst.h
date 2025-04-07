#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    //HELPERS:
    void insertFix(AVLNode<Key, Value>* p, AVLNode<Key, Value>* n);
    void rotateLeft(AVLNode<Key, Value>* node);
    void rotateRight(AVLNode<Key, Value>* node);
    void removeFix(AVLNode<Key, Value>* n, int diff);
};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // COPIED FROM: binary search tree insert
    AVLNode<Key, Value>* current = static_cast<AVLNode<Key, Value>*>(this->root_);

    // variables
    AVLNode<Key,Value>* n;
    AVLNode<Key,Value>* p;
    int diff = 0;

    // Check if tree is empty
    if(this->root_==NULL){
      AVLNode<Key, Value>* newNode = new AVLNode<Key,Value>(new_item.first, new_item.second, NULL);
      this->root_ = newNode;
      // leave the function
      return;
    }

    // While true
    while(true){
      // if keys are equal 
      if(new_item.first == current->getKey()) {
        // update value of key
        current->setValue(new_item.second);
        // leave the function
        return;
      }
      // if current node's key is larger
      else if(new_item.first < current->getKey()) {
        // check if left subtree is NULL
        if(current->getLeft()==NULL){
          // create new node (DYNAMIC ALLOCATION)
          AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, current);
          // set current node (newNode's parent)'s left node
          current->setLeft(newNode);
          
          n = current->getLeft();
          p = current;
          diff--;

          // leave the loop
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
          AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, current);
          // set current node (newNode's parent)'s right node
          current->setRight(newNode);

          n = current->getRight();
          p = current;
          diff++;

          // leave the loop
          break;
        }
        // recurse to right subtree
        else {
          current = current->getRight();
        }
      }
    }

    // Process after inserting the node
    if(p->getBalance()==-1){
      p->updateBalance(diff);
    }
    else if(p->getBalance()==1){
      p->updateBalance(diff);
    }
    else {
      p->updateBalance(diff);
      // Call insertFix(p, n)
      insertFix(p, n);
    }
}

// HELPER: insertFix
template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* p, AVLNode<Key, Value>* n)
{
    if(p==NULL || p->getParent()==NULL){
      return;
    }

    // Grandparent node
    AVLNode<Key, Value>* g = p->getParent();

    // p is left child of g
    if(g->getLeft()==p){
      g->updateBalance(-1);

      int gBalance = g->getBalance();
      int nBalance = n->getBalance();

      if(gBalance==0){
        return;
      }
      else if(gBalance==-1){
        insertFix(g, p); // recurse
      }
      else if (gBalance==-2){
        // if zig-zig (n is left child of p)
        bool zigZig = p->getLeft()==n;
        if(zigZig){
          rotateRight(g);
          p->setBalance(0);
          g->setBalance(0);
        }
        // if zig-zag
        else {
          rotateLeft(p);
          rotateRight(g);
          // 3 cases within this
          if(nBalance==-1){
            p->setBalance(0);
            g->setBalance(1);
            n->setBalance(0);
          } else if(nBalance==0){
            p->setBalance(0);
            g->setBalance(0);
            n->setBalance(0);
          } else {
            //nBalance==1
            p->setBalance(-1);
            g->setBalance(0);
            n->setBalance(0);
          }
        }
      }
    }

    // p is right child of g
    if(g->getRight()==p){
      g->updateBalance(1);

      int gBalance = g->getBalance();
      int nBalance = n->getBalance();

      if(gBalance==0){
        return;
      }
      else if(gBalance==1){
        insertFix(g, p); // recurse
      }
      else if (gBalance==2){
        // if zig-zig (n is right child of p)
        bool zigZig = p->getRight()==n;
        if(zigZig){
          rotateLeft(g);
          p->setBalance(0);
          g->setBalance(0);
        }
        // if zig-zag
        else {
          rotateRight(p);
          rotateLeft(g);
          // 3 cases within this
          if(nBalance==1){
            p->setBalance(0);
            g->setBalance(-1);
            n->setBalance(0);
          } else if(nBalance==0){
            p->setBalance(0);
            g->setBalance(0);
            n->setBalance(0);
          } else {
            //nBalance==-1
            p->setBalance(1);
            g->setBalance(0);
            n->setBalance(0);
          }
        }
      }
    }
    
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    AVLNode<Key, Value>* p;
    int diff = 0;
    // COPIED FROM bst.h

    // key does not exist
    AVLNode<Key, Value>* remove = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));
    if(remove == NULL){
      return;
    }

    // --- CASE 1: NO CHILDREN
    if(remove->getLeft()==NULL && remove->getRight()==NULL){
      // Set parent's pointer to this node as NULL
      AVLNode<Key, Value>* removeParent = remove->getParent();
      if(removeParent==NULL){
        this->root_ = NULL;
      }
      else if(removeParent->getKey() >remove->getKey()){
        diff++;
        removeParent->updateBalance(diff);
        removeParent->setLeft(NULL);
      } else {
        diff--;
        removeParent->updateBalance(diff);
        removeParent->setRight(NULL);
      }
      // remove node
      delete remove;
      p = removeParent;

      // patch tree
      removeFix(p, diff);

      return;
    }


    // --- CASE 2 AND 3: ONE CHILD
    if(remove->getLeft()==NULL || remove->getRight()==NULL){      
      // --- CASE 2: left child only
      if(remove->getRight()==NULL){
        // update diff
        diff++;

        // promote child
        AVLNode<Key,Value>* child = remove->getLeft();
        nodeSwap(remove, child);
      }
      // --- CASE 3: right child only
      else if(remove->getLeft()==NULL){
        // update diff
        diff--;

        // promote child
        AVLNode<Key,Value>* child = remove->getRight();
        nodeSwap(remove, child);
      }

      // fix the relations

      // variables
      AVLNode<Key,Value>* removeParent = remove->getParent();
      AVLNode<Key,Value>* leftChild = remove->getLeft();
      AVLNode<Key,Value>* rightChild = remove->getRight();

      removeParent->updateBalance(diff);

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
      p = removeParent;

      // patch tree
      removeFix(p, diff);

      return;
    }

    // --- CASE 4: TWO CHILDREN
    if(remove->getLeft()!=NULL && remove->getRight()!=NULL){
      // two children
      if(remove->getLeft()!=NULL && remove->getRight()!=NULL) {
        // promote predecessor
        nodeSwap(remove, static_cast<AVLNode<Key, Value>*>(this->predecessor(remove)));
      }

      // variables
      AVLNode<Key,Value>* removeParent = remove->getParent();
      AVLNode<Key,Value>* leftChild = remove->getLeft();
      AVLNode<Key,Value>* rightChild = remove->getRight();

      //update diff
      if(removeParent->getLeft()==remove){
        diff++;
        removeParent->updateBalance(diff);
      } else if(removeParent->getRight()==remove){
        diff--;
        removeParent->updateBalance(diff);
      }

        // remove has left child
        if(leftChild!=NULL){
          // if remove is the root
          if(removeParent==NULL){
            this->root_ = leftChild;
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
            this->root_ = rightChild;
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
      p = removeParent;

      // patch tree
      removeFix(p, diff);

      return;
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* n, int diff){
  if(n==NULL){
    return;
  }

  // compute next recursive call arguments
  AVLNode<Key, Value>* p = n->getParent();
  int ndiff = 0;

  if(p!=NULL){
    // n is left child
    if(p->getLeft()==n){
      ndiff = 1;
    }
    // n is right child
    else {
      ndiff = -1;
    }
  }

  int nBalance = n->getBalance();
  n->updateBalance(diff);

  // diff = -1
  if(diff==-1){
    // CASE 1
    if(nBalance == -2){
      // c = taller of the children
      AVLNode<Key, Value>* c = n->getLeft();
      int cBalance = c->getBalance();

      // CASE 1A -- zig zig
      if(cBalance == -1){
        rotateRight(n);
        n->setBalance(0);
        c->setBalance(0);
        removeFix(p, ndiff);
      }
      // CASE 1B -- zig zig
      else if(cBalance == 0){
        rotateRight(n);
        n->setBalance(-1);
        c->setBalance(1);
        return;
      }
      // CASE 1C -- zig zag
      //  if(cBalance == 1)
      else{
        AVLNode<Key, Value>* g = c->getRight();
        if(g==NULL){
          return;
        }
        int gBalance = g->getBalance();

        rotateLeft(c);
        rotateRight(n);

        // cases
        if(gBalance==1){
          n->setBalance(0);
          c->setBalance(-1);
          g->setBalance(0);
        } else if(gBalance==0){
          n->setBalance(0);
          c->setBalance(0);
          g->setBalance(0);
        } else {
          // gBalance = -1
          n->setBalance(1);
          c->setBalance(0);
          g->setBalance(0);
        }
        removeFix(p, ndiff);
      }
    }
    // CASE 2
    else if(nBalance == -1){
      n->setBalance(-1);
      return;
    }
    // CASE 3
    // nBalance + diff == 0
    else {
      n->setBalance(0);
      removeFix(p, ndiff);
    }
  }

  // diff = 1
  if(diff==1){
    // CASE 1
    if(nBalance == 2){
      // c = taller of the children
      AVLNode<Key, Value>* c = n->getRight();
      int cBalance = c->getBalance();

      // CASE 1A -- zig zig
      if(cBalance == 1){
        rotateLeft(n);
        n->setBalance(0);
        c->setBalance(0);
        removeFix(p, ndiff);
      }
      // CASE 1B -- zig zig
      else if(cBalance == 0){
        rotateLeft(n);
        n->setBalance(1);
        c->setBalance(-1);
        return;
      }
      // CASE 1C -- zig zag
      // if(cBalance == -1)
      else {
        AVLNode<Key, Value>* g = c->getLeft();
        if(g==NULL){
          return;
        }
        int gBalance = g->getBalance();

        rotateRight(c);
        rotateLeft(n);

        // cases
        if(gBalance==1){
          n->setBalance(0);
          c->setBalance(-1);
          g->setBalance(0);
        } else if(gBalance==0){
          n->setBalance(0);
          c->setBalance(0);
          g->setBalance(0);
        } else {
          // gBalance = -1
          n->setBalance(1);
          c->setBalance(0);
          g->setBalance(0);
        }
        removeFix(p, ndiff);
      }
    }
    // CASE 2
    else if(nBalance == 1){
      n->setBalance(1);
      return;
    }
    // CASE 3
    // nBalance + diff == 0
    else {
      n->setBalance(0);
      removeFix(p, ndiff);
    }
  }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}

// HELPER: rotate left
template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* node){
  AVLNode<Key,Value>* child = node->getRight();

  // pointers that need to change in the future
  AVLNode<Key,Value>* a = node->getLeft();
  AVLNode<Key,Value>* b = child->getLeft();
  AVLNode<Key,Value>* c = child->getRight();

  nodeSwap(node, child);
  // change pointers
  // node
  child->setLeft(node);
  node->setParent(child);
  // C
  child->setRight(c);
  if(c!=NULL){
    c->setParent(child);
  }
  // A
  node->setLeft(a);
  if(a!=NULL){
    a->setParent(node);
  }
  // B
  node->setRight(b);
  if(b!=NULL){
    b->setParent(node);
  }
  
}

// HELPER: rotate right
template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* node){
   AVLNode<Key,Value>* child = node->getLeft();

  // pointers that need to change in the future
  AVLNode<Key,Value>* a = child->getLeft();
  AVLNode<Key,Value>* b = child->getRight();
  AVLNode<Key,Value>* c = node->getRight();

  nodeSwap(node, child);
  // change pointers
  // node
  child->setRight(node);
  node->setParent(child);
  // A
  child->setLeft(a);
  if(a!=NULL){
    a->setParent(child);
  }
  // B
  node->setLeft(b);
  if(b!=NULL){
    b->setParent(node);
  }
  // C
  node->setRight(c);
  if(c!=NULL){
    c->setParent(node);
  }
}

#endif
