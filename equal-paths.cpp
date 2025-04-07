#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <algorithm>
#endif

#include "equal-paths.h"
using namespace std;

// You may add any prototypes of helper functions here
int pathLength(Node* root){
  if(root==NULL){
    return 0;
  }
  return std::max(pathLength(root->left), pathLength(root->right)) + 1;
}


bool equalPaths(Node * root)
{
  if(root==NULL){
    return true;
  }
  else if(root->left==NULL && root->right==NULL){
    return true;
  }
  else if(root->left==NULL){
    return equalPaths(root->right);
  }
  else if(root->right==NULL){
    return equalPaths(root->left);
  }
  else {
    return pathLength(root->left) == pathLength(root->right) && equalPaths(root->left) && equalPaths(root->right);
  }

}

