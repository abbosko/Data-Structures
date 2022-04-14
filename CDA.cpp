#include <iostream>
#include <cstdlib>



using namespace std;

template <typename elmtype>
class CDA {
    private:

    int size=0;
    int capacity=0;
    elmtype *data;
    int *arraytwo;      //shadow array containing indexs of arraythree in index of data data array
    int *arraythree;     // shadow array contains index of original in order of appearance
    int front=0;
    int back=0;
    elmtype initVal;
    bool dataInitialized= false;
    int thirdarraysize=0;       // keeps track of number of valid data items


public: 

CDA(){
    size=0;
    capacity=1;
    data = new elmtype[capacity]; 
    dataInitialized=false;
    front=0;
    back=0;                                       
}

CDA(int s) {
    size = s;
    capacity = s;
    data = new elmtype[capacity];                             
    front=0;
    back=size-1;    //0 based
    dataInitialized=false;
}

CDA(int s, elmtype init) {
    size = s;
    capacity = s;
    front=0;
    back= size-1;
    dataInitialized=true;
    data = new elmtype[capacity];                              // initalize to init in constant time-> 2 shadow arrays         
    arraytwo = new int[capacity];                            // initalize it when subscript operator is called, if user didnt put in data(index not in other arrays), return the init value, never actually initialize entire array
    arraythree = new int[capacity];
    thirdarraysize=0;
    initVal= init;

}


~CDA() {   
if (dataInitialized) {  
    delete[]  data;             // need to do capacity check before calling destructor, delete[]-> deletes array, delete->deletes one elment type   
    delete[] arraytwo;
    delete[] arraythree;  
}    
       
else {
        delete[] data;
}
}

CDA(const CDA <elmtype> &src) {

    size = src.size;
    capacity = src.capacity;
    dataInitialized = src.dataInitialized;
    front=src.front;
    back=src.back;
    initVal =src.initVal;
    data = new elmtype[capacity];
    if (src.dataInitialized==true) {
        arraytwo = new int[capacity];
        arraythree = new int[capacity];
       // initVal=src.initVal;
        thirdarraysize = src.thirdarraysize;

    }

    for( int i=0; i<capacity; i++) {
        data[i]= src.data[i];
        if (src.dataInitialized== true) {
            arraytwo[i]= src.arraytwo[i];
            arraythree[i]=src.arraythree[i];
           // thirdarraysize = src.thirdarraysize;
        }
    }
}

elmtype& operator=(const CDA<elmtype>  &src){                     // assignment operator
    capacity=src.capacity;
    size=src.size;
    dataInitialized = src.dataInitialized;
    front = src.front;
    back=src.back;
    initVal =src.initVal;
    data = new elmtype[capacity];

    if (src.dataInitialized==true){
         arraytwo = new int[capacity];
         arraythree = new int[capacity];
        //initVal = src.initVal;
        thirdarraysize=src.thirdarraysize;
    }
    for(int i=0; i<capacity; i++){
        data[i]=src.data[i];
        if ( dataInitialized == true){
            arraytwo[i]= src.arraytwo[i];
            arraythree[i]= src.arraythree[i];
        }
    }

}


elmtype& operator[](int i){
   int idx = (front + i) % capacity;        // front of array plus the offset of desired index % capacity to make circular
 
   if (i <= size -1 && i>=0) {                                        
                                                                        
       if(dataInitialized) {                                       
           if (thirdarraysize > 0 && thirdarraysize >= arraytwo[idx] && arraythree[arraytwo[idx]]== i)  {  // checking if arrays point back to each other, then data is valid
             return data[idx]; 
             }
            else {  
            arraytwo[i] = thirdarraysize;           // set up pointers and initialize value
            data[idx] = initVal;
            arraythree[thirdarraysize] =i;
            thirdarraysize++;  
                                            
       return data[idx];  
       }                 
   }
   else {
   return data[idx];

   }
   }
   else {
       cout << "ERROR: OUT OF BOUNDS" << endl;
   }
}

void AddEnd(elmtype v){                           
    if (capacity==size) {                           // if array full double the size 
        capacity= capacity * 2; 
        
        if (dataInitialized== false) {                  // if not initialized copy original array and put in new data array with double capacity
        elmtype *temp = new elmtype[capacity];
        for(int i = 0; i < size; i++){
					temp[i] = data[(front + i) % (capacity/2)];
				}	
        
            data = temp;
            front=0;         // reset front and back pointers
            back = size -1;                
        }
    
     if (dataInitialized==true) {               // if want data intialized need to modidy all 3 arrays for doubling capacity
    
    elmtype *temp1 = new elmtype[capacity];
    int *temp2 = new int[capacity];                        
    int *temp3= new int[capacity];   
      for(int i=0; i< size; i++) {
          if ((arraythree[arraytwo[i]] == i) && arraytwo[i] < thirdarraysize){      // if valid data
            temp1[i]= data[((front +i)) % capacity]; // copy in data
             temp2[i] = arraytwo[i];        // copy arraytwo
             temp3[i]=arraythree[i];        // copy arraythree
          }
        else {
            temp1[(front + i) % capacity] = initVal;        // if non-valid data, initialize
            arraytwo[i] = thirdarraysize;                   // set up shadow arrays to point to each other
            arraythree[thirdarraysize] =i;
            thirdarraysize++; 
        }
      }
        data = temp1;
        front = 0;
        back = size -1;
    } 
    front = 0;      // reset front and back pointers
    back = back +1;

    }
    else {                                                          // if capacity does not need to be doubled
        if ((back ==capacity -1 && front !=0) || front ==back){     // if at end of array make circular
            back=0;                                                 

        }
        else {                          // otherwise back can just be pushed back one
        back= back +1; }
    }
   
   // in all instances 
    
    size++;         // add to size of array and put new value as last value in array
    data[back]=v;

    if (dataInitialized) {              // if array is supposed to be initialized, set shadow arrays
    arraytwo[back]= thirdarraysize;         
    arraythree[thirdarraysize]=back;
    thirdarraysize++;

    }
}

void AddFront(elmtype v){
if (capacity == size){              // if capacity needs to be doubled

    if (dataInitialized==false){
        capacity = capacity * 2;
     elmtype *temp1= new elmtype[capacity];            
     for(int i=0; i< size; i++) {  
         temp1[i]= data[(front +i) % (capacity /2)] ;                   // same process in add back 
        }
        front =0;
        data = temp1;
        back = size -1;
    }


if (dataInitialized==true) {  
    capacity= capacity * 2; 
     elmtype *temp1= new elmtype[capacity];                  
    int *temp2 = new int[capacity];                        
    int *temp3= new int[capacity];   
      for(int i=0; i< size; i++) {
          if ((arraythree[arraytwo[(front + i) % size]] == (front + i) % size) && arraytwo[(front + i) % size] < thirdarraysize){
            temp1[i]= data[((front +i)) % capacity];
             temp2[i] = arraytwo[i];
             temp3[i]=arraythree[i];
          }
        else {
          
            temp1[(front + i) % capacity] = initVal;
            arraytwo[i] = thirdarraysize;
            arraythree[thirdarraysize] =i;
            thirdarraysize++; 
            }
            
        }
        data = temp1;
        front =0;
        back = size -1;
    }
}

if (front ==0){
    front = capacity -1;
}
else {
    front = front -1;
}
size++;
data[front]= v;


if (dataInitialized) {
    arraytwo[front]= thirdarraysize;
    arraythree[thirdarraysize]=back;
    thirdarraysize++;

}
}

void DelEnd() {
    if (back ==0) {
        back = capacity -1;
    }
    else {
        back= back -1;  // just move back pointer 
    }
    size--;

    if (size <= (capacity * .25))  {    // if size is less than or equal 25% capacity resize
            capacity = capacity /2; 
            elmtype *temp1= new elmtype[capacity];
            for(int i=0; i<size; i++) {
                temp1[i]=data[(front + i) % (capacity*2)];
            }
            data=temp1;
			front = 0;
			back = size-1;
			return;
    }
}
void DelFront(){

    if (size -1 == front) {
        front =0;
    }
    else {
        front+=1;
    }
    size--;
   if (size <= (capacity * .25))  {
            capacity = capacity /2; 
            elmtype *temp1=new elmtype[capacity];
            for(int i=0; i<capacity; i++) {
                temp1[i]=data[(front + i) % (capacity*2)];
            }
            data=temp1;
            front = 0;
			back = size-1;
    }
}
   
int Length() {
    return size;
}
int Capacity(){
    return capacity;
} 

elmtype Select(int k){
   
   
    if (front ==back){
        return data[front];                         // error cases
    }
    // else if (k<1 || k> size -1) {
    //     cout << "Invalid k";
    //     return 0;
    // }


    //srand(time(NULL));
    int pivot = rand() % size;
   
    CDA <elmtype> temp1;
    CDA <elmtype> temp2;
    CDA <elmtype> temp3;                   // if index not initialized use initialized value, also use in comparisons

if (dataInitialized==false) {
    for(int i=0; i<size; i++) {
        if (data[(front +i) % capacity]< data[pivot]) {
            temp1.AddEnd(data[(front +i) % capacity]);
        
        }
        else if(data[(front +i) % capacity]==data[pivot]){
            temp2.AddEnd(data[(front +i) % capacity]);
        
        }
        else {
            temp3.AddEnd(data[(front +i) % capacity]);
       
        }
    }
}

else if (dataInitialized) {
     for(int i=0; i<size; i++) {
            if (thirdarraysize > 0 && thirdarraysize >= arraytwo[i] && arraythree[arraytwo[i]]== i){
                 if (data[(front +i) % capacity]< data[pivot]) {
                     temp1.AddEnd(data[(front +i) % capacity]);
                    }
                else if(data[(front +i) % capacity]==data[pivot]){
                     temp2.AddEnd(data[(front +i) % capacity]);
                    }
                else {
                    temp3.AddEnd(data[(front +i) % capacity]);
                    }
    }
        else {
        arraytwo[i] = thirdarraysize;
        data[(front + i) % capacity] = initVal;
        arraythree[thirdarraysize]=i;
        thirdarraysize++;  

                 if(data[(i+ front) % capacity] < data[pivot]){
					temp1.AddEnd(data[(i+ front) % capacity]);
						}
				else if(data[(i+ front) % capacity] == data[pivot]){
					temp2.AddEnd(data[(front +i) % capacity]);
						}
				else {
					temp3.AddEnd(data[(i+ front) % capacity]);	
						}

    }
}        
}

    if (k<=temp1.Length()){
        return temp1.Select(k);
    }
    else if (k <=(temp1.Length() + temp2.Length())) { 
        return data[pivot];
        }
    else { 
        return temp3.Select(k- temp1.Length()-temp2.Length());}
  }


void Sort(){
   if (size <= 1) return;  
   int a1pass = size /2;                          
   int a2pass = size - (size/2);
   CDA a1(a1pass);
   CDA a2(a2pass);
   for (int i = 0; i < size/2; i++){        // copy in first half of data
      a1[i] = data[(i+front) % capacity];
   }
   for (int i = size/2; i<size; i++){       // copy second half
      a2[i-size/2] = data[(i+front) % capacity];
   }
   a1.Sort();   // continue recursively
   a2.Sort();
   
   int n1 = size/2;
   int n2 = size-(size/2);
   int p1 = 0;
   int p2 = 0;
   int i = 0;
   while (p1 < n1 && p2 < n2) {
      data[i++] = a1[p1]<a2[p2] ? a1[p1++] : a2[p2++];
   }
   while (p1 < n1) {
       data[i++] = a1[p1++];
       }
   while (p2 < n2) {
       data[i++] = a2[p2++];
   }
   front =0;
   back =size -1;

 }

int Search(elmtype e) {

    for(int i=0; i<size; i++) {
        
        if (data[(i+front)% capacity]==e){
            return i;
        }
    }
    return -1;
}


int BinSearch(elmtype e){

    int left=0;
    int right= size-1;
    
    while (left <=right) {
    int mid = (left + right) /2;
    if ( data[mid] == e) {
        return mid;
    }

    else if(data[mid] < e){
        left = mid +1;
    }

    else {
        right = mid -1;
    }
    }

    if ( data[left] > e) {
        return ~left;
    }
    else {
        return ~size;
    }
}
      
};
