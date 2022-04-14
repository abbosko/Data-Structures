#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>

using namespace std;


template <typename keytype>

class Treap {
private:
struct TreapNode {
    keytype key;
    float priority;
    TreapNode *left, *right;
    int leftCount=0;

};

TreapNode *root;
int length;


void printInorder(TreapNode *p){
    if (p == NULL) {
    return;
    }
    printInorder(p->left);
    cout << p->key << " ";
    
    printInorder(p->right);
}

TreapNode* newNode(keytype key, float priority)
{
    TreapNode* temp = new TreapNode;
    temp->key = key;
    temp->priority = priority;
    temp->left = NULL;
    temp->right = NULL;
    temp->leftCount = 0;
    return temp;
}


TreapNode* copyHelp(TreapNode *c)
{
  if(c==NULL){
    return NULL;
 }

        TreapNode* node=new TreapNode;
        node = newNode(c->key,c->priority);

        node->left=copyHelp(c->left);
        node->right=copyHelp(c->right);
        
        return node;
}

void rightRotate(TreapNode *&root){
  
    root->leftCount -= (root->left->leftCount +1);
    TreapNode* leftR = root->left;
    TreapNode* rightR = root->left->right;

 
    leftR->right = root;
    root->left = rightR;
    root = leftR;

    }
    
void leftRotate(TreapNode *&root){
    TreapNode* rightR = root->right;
    TreapNode* leftR = root->right->left;
 
   rightR->left = root;
   root->right = leftR;
   root =rightR;
   root->leftCount += root->left->leftCount +1;
    }

int rank(TreapNode *root, keytype key){
  int rank = 1;
  while (root) {
    if (key < root->key)  {             // move to left subtree
      root = root->left;                // moving left doesn't change rank bc smaller so not adding previous node
    }
    else if (key > root->key) {     // move to right subtree and all all left counts (items before)
      rank += 1 + root->leftCount;  // add one for node were passing
      root = root->right;
    }
    else {
      return rank + root->leftCount; // returns rank that we calculated plus the left count of node
    }
  }
  return 0; // not found
}

TreapNode* select(TreapNode *root, int rank){

 if (root == NULL){
     return 0;
 }

int leftNum;
 leftNum = root->leftCount;

 if (leftNum > rank){           // if lefCount is greater than rank, then current node is at a higher rank so go left
     return select(root->left, rank);
 }
 else if (leftNum < rank){      // if leftCount is smaller than rank then need to move right to go higher, 
     return select(root->right, rank - leftNum -1); // remove 1 for current node, and subtract leftCount 
 }

 else return root;
}

TreapNode* insert(keytype k, float p, TreapNode* root) {
     if (root == NULL) {
     return newNode(k,p);
      
        }
        
        if (k < root->key) {        // new node is less than root, so go left, add to left count on way down
            root->leftCount++;
            root->left =  insert(k,p, root->left);                              
            if (root->left != NULL && root->left->priority < root->priority) {  // if heap order violated
             rightRotate(root);
        }
    }
        else {
         root->right = insert(k,p, root->right);
            if (root->right != NULL && root->right->priority < root->priority) { // heap order violated
                 leftRotate(root);
            }
        }
return root;
    }

TreapNode* remove(keytype key, TreapNode *root)
{
   
    if (root == NULL) {            // base case
    return root;
}
 
    if (key < root->key){       // go left, removing on that side so subtract from left count
        root->leftCount--;
        root->left = remove(key, root->left);
        }

    else if (key > root->key){      // go right
        root->right = remove(key, root->right);

    }
  
    else if (root->left == NULL){               // if no left child
        TreapNode *temp = new TreapNode;   
        temp=root->right;
        delete(root);
        root = temp;          // Make right child as root
    }
 

    else if (root->right == NULL){
        TreapNode *temp = new TreapNode;
        temp= root->left;
        delete(root);
        root = temp;            // make left child root
    }
 
    else if (root->left->priority > root->right->priority){     // if heap order violation
        leftRotate(root);
        root->leftCount--;
        root->left = remove(key, root->left);
    }
    
    else{   
        rightRotate(root);
        root->right = remove(key, root->right);
    }
 
    return root;
}

TreapNode* maxVal(TreapNode* node)
{
    while (node->right!= NULL) {
        node = node->right;
    }
 
    return node;
}

TreapNode* minVal(TreapNode* node)
{
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

TreapNode* findSuccessor(TreapNode* root, keytype key)
{
    TreapNode* succ = new TreapNode;
   // keytype successVal = key;
    succ = NULL;

    while(1){
        if (key < root->key){
            succ = root;
          // successVal = root->key;
            root=root->left;
            
        }
        else if (key > root->key){      
            root=root->right;
        }

        else {
            if (root->right != NULL){
                succ = minVal(root->right);     // find min val of right subtree
               // successVal = root->key;
            }
            break;
        }
        if (root == NULL){
            return NULL;
        }
        
    }
    return succ;

}

TreapNode* findPredecessor(TreapNode* root, keytype key)
{
    TreapNode* pred = new TreapNode;
    pred = NULL;

    while(1){
        if (key < root->key){
            root=root->left;
        }
        else if (key > root->key){
            pred = root;
            root=root->right;
        }

        else {
            if (root->left != NULL){
                pred = maxVal(root->left);  // find max of left subtree
            }
            break;
        }
        if (root == NULL){
            return NULL;
        }
        
    }
    return pred;
}


public:
Treap(){  
    root = NULL;  
     length =0;                       // default constructor where tree is empty
    }

Treap(keytype k[], float p[], int s){          
     // root = new TreapNode;
      root = newNode(k[0],p[0]);
      root->leftCount=0;
        for (int i=1; i < s; i++) {  
           //  TreapNode *temp = new TreapNode;                              // loop of inserts
               insert(k[i],p[i]);
        }
        length=s;
    }
    
void DestructHelper(TreapNode* Tree)
{
   if (Tree != NULL)
   {
      DestructHelper(Tree->left);
      DestructHelper(Tree->right);
      delete Tree;
   }
}

~Treap()
{
   DestructHelper(root);
}

Treap(const Treap &src) {
      root = copyHelp(src.root);
      length = src.length;
 
}

Treap& operator=(const Treap  &src){  
     root = copyHelp(src.root);
     length = src.length;
     return *this;
}

    
float search(keytype k){

    TreapNode *temp = new TreapNode;

    temp = root;
    

   while(true){

    if (temp->key == k){       // if root is key  return
        return temp->priority;  
        }
       
        else {
        if (temp->key > k && temp->left !=NULL){
            temp=temp->left;
        }
            
        else if (temp->key < k && temp->right != NULL){
                 temp = temp->right;       // search right

        }
        else {
                return -1;
            }
        }
   }
     
}

void insert(keytype k, float p){
         root = insert(k,p, root);
         length++;
   
      }
    
void insert(keytype k){

        root =  insert(k,rand()/(1.0 *RAND_MAX), root);
         length++;
    }

int remove(keytype k){

        if (search(k) == -1){               
            return 0;
        }

        root = remove(k, root);
       
        length--;
        
        return 1;
    }

int rank(keytype k){
        return rank(root, k);       // position of key in sorted list, if equal either position works
    }        
   
keytype select(int pos){
        TreapNode *find= new TreapNode;        // Returns the key after k in the tree. If the key has
        find= select(root,pos-1);

        if (find == NULL){
            return 0;
        }
        else {
            return find->key;
        }
    }   
    
keytype successor(keytype k){
        TreapNode *successor= new TreapNode;        // Returns the key after k in the tree. If the key has
        successor = NULL;                           // no successor, return k.
       successor  =  findSuccessor(root,k);
        //cout << successor->key;

        if (successor == NULL){
            return k;
        }

        return successor->key;
    }

keytype predecessor(keytype k){
        TreapNode *predecessor= new TreapNode;
        predecessor = NULL;
        predecessor = findPredecessor(root,k);
        if (predecessor == NULL){
            return k;
        }
        return predecessor->key;
    }

int size(){
    return length;
}

void preorder(TreapNode *root){
    if (root == NULL){
    return; }
 
    cout << root->key << " ";
 
    preorder(root->left);
    preorder(root->right);

}
void preorder() {
    preorder(root);
    cout << endl;
}

void inorder(){
    printInorder(root);
    cout << endl;
   
}

void postorder(TreapNode *root){
    if (root == NULL) {
    return; }
    
    postorder(root->left);
    postorder(root->right);
    cout << root->key << " ";
}
void postorder() {
    postorder(root);
    cout << endl;
}


};

