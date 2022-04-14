#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include "Heap.cpp"



using namespace std;


template <typename keytype>
class FibHeap {
private:

struct FibNode {
    keytype key;
    int degree;
    FibNode *parent, *child, *next, *prev, *right; //(rightsibling)
};

FibNode *min;
FibNode *head;
FibNode *tail;


FibNode* newNode(keytype key, int degree){      // function to create new Fib Node given key and degree
    FibNode* temp = new FibNode;
    temp->key = key;
    temp->degree = degree;
    temp->parent = NULL;
    temp->child = NULL;
    temp->next = NULL;
   temp-> prev = NULL;
   temp->right = NULL;

    return temp;
}


public:
FibHeap(){  
    // min = new FibNode;
    // head = new FibNode;
    // tail = new FibNode;                       // default constructor, empty heap
    min = NULL;
    head = NULL;
    tail = NULL;
}


FibHeap(keytype k[], int s){            // loop of inserts, calls consolidate at end of construction
    // min = new FibNode;
    // head = new FibNode;
    // tail = new FibNode;

    min = newNode(k[0], 0);
    head=min;
    tail=min;
  
  for(int i=1; i< s; i++){
      insert(k[i]);
  }
  //heapSize =s;

    consolidate();

}  

FibHeap(const FibHeap <keytype> &src) {     // copy constructor
  

    head = copyNode(src.head);
     tail=copyNode(src.tail);
     min = copyNode(src.min);

    FibNode *ptr2 = head;
    while(ptr2 != NULL){
        ptr2 =  CopyHelper(ptr2);
        ptr2 = ptr2->next;
        }

   }



FibNode* CopyHelper(FibNode *root){     // helper function for copy constructor/assignment operator
    if (root == NULL){
    return NULL; }
 
   FibNode* node = copyNode(root);
  // if(node->child != NULL){
     node->child = CopyHelper(root->child);
 //if(node->child->right != NULL){
    node->right = CopyHelper(root->right);
    
   

   return node;

}

FibNode* copyNode(FibNode *curr){      // copy contents of node
    if(curr == NULL){

      return NULL;
    }
    FibNode *temp = new FibNode;
            temp->key = curr->key;
            temp->degree = curr->degree;
            temp->parent = curr->parent;
            temp->child = curr->child;
            temp->next = curr->next;
            temp-> prev = curr->prev;
            temp->right = curr->right;
    return temp;
}


FibHeap& operator=(const FibHeap<keytype>  &src){  // assignment operator
     FibNode *ptr1 = head;
    while(ptr1 != NULL){
        FibNode *netP = ptr1->next;
        DestructHelper(ptr1);
        ptr1 = netP;
    }
    
    head = NULL;
    tail= NULL;
    min = NULL;
 
    this->head = copyNode(src.head);
     this->tail=copyNode(src.tail);
     this->min = copyNode(src.min);
    // //this->min = src.min;
    //this->tail = srthisc.tail;
    // tail->next = NULL;
    // head->prev = NULL;
   
    FibNode *ptr = head;
    while(ptr != NULL){
        ptr =  CopyHelper(ptr);
        ptr = ptr->next;
        }
        return *this;

}

~FibHeap(){
    FibNode *ptr = head;            // destructor
    //FibNode *end = tail->next;
    while(ptr != NULL){             // iterate through root list 
        if(ptr->next == NULL){
            return;
        }
        FibNode *netP = ptr->next;
        DestructHelper(ptr);        // then go down into tree
        ptr = netP;
    }
head = NULL;
tail= NULL;
min = NULL;
    
}

void DestructHelper(FibNode *Tree){
    if (Tree == NULL){
        return;
    }
   
       if(Tree->child != NULL){             // destuctor like preorder
            DestructHelper(Tree->child);
         if(Tree->child->right != NULL){
            DestructHelper(Tree->right);
        }

   }
   delete Tree;
 // return;
//}

}

FibNode* link(FibNode *first, FibNode *second){         // link trees together 
        FibNode *smaller;              
        FibNode *bigger;              

        if(first->key < second->key){   //
            smaller = first;
            bigger = second;
        }
        else {
            smaller =second;
            bigger = first;
        }

        bigger->right = smaller->child;   // bigger tree's root right sibling is smaller trees child
        smaller->child = bigger;        // smaller become tree root
        bigger->parent =smaller;         // bigger tree becomes child of smaller tree
        smaller->degree++;              // two trees of same size = size +1

        return smaller;
}
void consolidate(){                     // called in extract min, 
    FibNode *arr[50] = {NULL};          // allocate pointer array 
    
    FibNode *curr = head;
    FibNode *nextC;
    int temp;
 

        while (curr!= NULL) {           // iterate through root list
            nextC = curr->next;
            temp = curr->degree;
            while(temp < 50 && arr[temp]!= NULL ){      // if already a tree of that size stored in array
                curr = link(arr[temp], curr);           // link together trees and 
                arr[temp]= NULL;                        // set current location to null b/c tree is now bigger 
                temp++;                                 // linking two trees of same size = tree of size +1 
            }

            arr[temp]= curr;           // if !NULL-> at next size, if NULL, at same size of tree
                                        //point to root of tree
            curr = nextC;
        }
      
        head = NULL;        // reset all pointers
        tail = NULL;
        min = NULL;
        curr = NULL;

        for(int i=0; i< 50; i++){

                if(arr[i] !=NULL){      // if were pointing to a binom tree
                 
                    if(head == NULL){       // if first element set all pointers to this element
                        head= arr[i];       // head is smallest size tree
                        min = arr[i];
                        curr = head;
                        head->prev =NULL;
                        head->next = NULL;

                    }
                    else {                      
                        curr->next = arr[i];        // next item in root list is next item in pointer array
                        arr[i]->prev= curr;         // 
                        arr[i]->next = NULL;        // putting at end of root list
                        if(arr[i]->key < min->key){         // update min pointer
                            min= arr[i];
                        }
                        curr = curr->next;      // next item in lis
                    }
        }
        }
        tail = curr;    // tail is last item in root list (biggest tree)
    
}


keytype peekKey(){
    if( min!= NULL){
    return min->key;
    }
}

keytype extractMin(){
  
FibNode *oldMin= new FibNode;       // create pointer to min
oldMin= min;


                                                        // if has no children, can just cut out of root list
if(oldMin->child == NULL){                              // if min has no child cut it out
        
   
    if(min == head){                                   // if min is head of list

           head = head->next;                          // set head to next item in root list
     }
    
    else if(min == tail){                              // if min tail
      
             tail->next = NULL;                       // move everything and set tail to previous item in list
            FibNode *hit=head;
            while(hit->next->next != NULL){
                hit=hit->next;
            }
            hit->next = NULL;
            tail->prev = hit->prev;
            tail = hit;
            tail->next = NULL;
           
     }
     else {                                     // if min in middle of list

            FibNode *prv=head;
            FibNode *curr = head->next;
            while ( curr != min) {
                curr=curr->next;
                prv=prv->next;
             
            }
        
            curr->next->prev= prv;
            prv->next = curr->next;

     }
    }

     
    else {                                                 // if min has children
                            
     FibNode *children = new FibNode;
     children = oldMin->child;                              // point to child
     while(children != NULL){                               // iterate through all children
        children->prev = tail;                              // add to end of root list
        tail->next = children;                    
        tail = children;                                     // update tail pointer
        tail->next = NULL;                                   
        children->parent = NULL;                             // cut off parent

           
            children= children->right;                      // go to next item in list 
     
        }
     // now that all children are cut off
        if(oldMin == head){                             // if min is head of list set head to next item in list
               
            head = head->next; 
            head->prev = NULL;
            tail->next = NULL;
        }
        else if(oldMin == tail){

            tail->next = NULL;                     // if min is tail, move everything and set tail to last prev item in list
            FibNode *hit=head;
            while(hit->next->next != NULL){
                hit=shit->next;
            }
            hit->next = NULL;
            tail->prev = hit->prev;
            tail = hit;
            tail->next = NULL;
        }
        else {                                   // if in middle of list, 
         
            FibNode *ptr = head;
            while( ptr != oldMin){              // iterate through list and break when hit min
                if(ptr->next != NULL){
                ptr = ptr->next; }
            }
            ptr->prev->next = ptr->next;          // cut out min
            if(ptr->next != NULL){
                ptr->next->prev = ptr->prev;
            }
                                  
        }
      }

      // after all, update new min pointer

     for(FibNode *ptr = head; ptr != NULL; ptr=ptr->next){
         if(ptr->key < min->key){
             min = ptr;
         }

     }
      
    consolidate();
 
    return oldMin->key;
}



void insert(keytype k){

    FibNode *temp = new FibNode;
    temp = newNode(k,0);

    if (min == NULL){       // if min is NULL, heap is empty so initialize all pointers to this value
        min = temp;
        head = temp;
        head->prev = NULL;
        tail = temp;
        tail->next = NULL;
       // min->prev = tail;
       // min->next = min;
       // head->prev = tail;
        //tail->next = head;

    }
    else if (k < min->key){         // if new key is less then the min, update min pointer and add to tail of list
        tail->next = temp;
        tail = tail->next;
        tail->next = NULL;
        //head->prev = tail;
        min = temp;
    }
    else {                          // otherwise just add to end of list
        tail->next = temp; 
        tail = tail->next;
       tail->next = NULL;
      head->prev = NULL;;
    }
}

void merge(FibHeap<keytype>&H2){            //add to end of root list
    tail->next = H2.head;
    if(H2.min->key < min->key){         // update min pointer
            min= H2.min;
   }
  
}

void  preorder(FibNode *root){
if (root == NULL){
    return; }
    
cout << root->key << " ";
 
preorder(root->child);
preorder(root->right);
}


void printKey(){                        
    FibNode *ptr = head;
    
    while(ptr != NULL){
        cout <<"B" << ptr->degree << endl;
        cout << ptr->key << " ";
        preorder(ptr->child);
        cout << endl;
        ptr = ptr->next;
        cout << endl;
    }

    cout << endl;
    
}



void mincheck(){
    cout << min->key;
}

};



