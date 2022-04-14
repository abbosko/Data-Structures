#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>

using namespace std;

template <typename elmtype>
class CDA {
    private:

    int size=0;
    int capacity=0;
    elmtype *data;
    int *arraytwo;
    int *arraythree;
    int front=0;
    int back=0;
    elmtype initVal;
    bool dataInitialized= false;
    int thirdarraysize=0;


    public: 

CDA(){
    size=0;
    capacity=1;
    data = new elmtype[capacity]; 
    dataInitialized=false;
    front=0;
    back=0;                                          // subscript operator check if addresses equal,  if equal check if initialized, yes = to default value
}

CDA(int s) {
    size = s;
    capacity = s;
    data = new elmtype[capacity];                             
    front=0;
    back=size-1;
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
   //if (capacity>= 2) {  
    delete[]  data;             // need to do capacity check before calling destructor, delete[]-> deletes array, delete->deletes one elment type   
    delete[] arraytwo;
    delete[] arraythree;  
}    
// else if (capacity ==1){
//     delete data;
//     delete arraytwo; 
//     delete arraythree;
//     }            
else {
    // if (capacity >=2 ) {
        delete[] data;
        //delete[] arraytwo;
        //delete arraythree;
    // }
    //  else if (capacity ==1){
    //     delete data;
    //  }

    /*}*/
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

    
                                           // if regualr constructors can jsut return 
      // return (*this);                                                 // if initialized check if valid data or not
}


elmtype& operator[](int i){
   int idx = (front + i) % capacity;
 // if (i <=size -1){
   if (i <= size && i>=0) {                                          // check if third array size > 0 && thirdsize>= secondarray[i] && third array[secondarray[i]])
                                                                       // no-> then element is not initialized then check if third array size >= second array[i], checks if second array pointer is pointing to third array  
       if(dataInitialized) {                                        // set thirdarray[thirdsize] = i then data[idx]= init
           if (thirdarraysize > 0 && thirdarraysize >= arraytwo[idx] && arraythree[arraytwo[idx]]== i)  {  
             return data[idx]; 
             }
            else {
              // cout << "4"; 
           // thirdarraysize++;     
            arraytwo[i] = thirdarraysize;
            data[idx] = initVal;
            arraythree[thirdarraysize] =i;
            thirdarraysize++;  
                                                                // need size for third array, dont need size for 2nd array-> should correspond to first array
       return data[idx];  
       }                 // check sizes
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
    // elmtype *temp1;  
    // int *temp2;
    // int *temp3;                           
    if (capacity==size) {
        capacity= capacity * 2; 
        
        if (dataInitialized== false) { 
        elmtype *temp = new elmtype[capacity];
        for(int i = 0; i < size; i++){
					temp[i] = data[(front + i) % (capacity/2)];
				}	
        
       data = temp;
       front=0;
       back = size -1; //((back + capacity) +1) % capacity
        //temp1 = new elmtype[capacity];                
        }
       // data[back]= v;
    
     if (dataInitialized==true) {
       // back = (back+1+ size) % size;
    elmtype *temp1 = new elmtype[capacity];
    int *temp2 = new int[capacity];                        
    int *temp3= new int[capacity];   
      for(int i=0; i< size; i++) {
          if ((arraythree[arraytwo[i]] == i) && arraytwo[i] < thirdarraysize){
            temp1[i]= data[((front +i)) % capacity];
             temp2[i] = arraytwo[i];
             temp3[i]=arraythree[i];
          }
        else {
          // temp1[i]= initVal;
            temp1[(front + i) % capacity] = initVal;
            arraytwo[i] = thirdarraysize;
            arraythree[thirdarraysize] =i;
            thirdarraysize++; 
        }
      }
      //  delete[] arraytwo;
       // delete[] arraythree;
      //  delete[] data;
        data = temp1;
       // size++;
        front = 0;
        back = size -1;
        // delete[] temp2;
        // delete[] temp3;
        // delete[] temp1;
        // if (size >0) {
        //     arraytwo[front]= thirdarraysize;  
        //     arraythree[thirdarraysize]= front;          
        // }
    } 
    front = 0;
    back = back +1;
    //cout << back<< endl;
    //data[back]= v;

    }
    else {
        if ((back ==capacity -1 && front !=0) || front ==back){
            back=0;

        }
        else {
        back= back +1; }
    }
   // data[back]=v;
    size++;
    data[back]=v;

    if (dataInitialized) {
    arraytwo[back]= thirdarraysize;
    arraythree[thirdarraysize]=back;
    thirdarraysize++;

    }
     // data[back]= v;
}

void AddFront(elmtype v){
    //elmtype *temp1; 
   // int *temp2;
   // int *temp3;

if (capacity == size){

    if (dataInitialized==false){
        capacity = capacity * 2;
        //front = (front -1) % capacity;
        //front= ((front + size) -1) % ca;
        //cout << front;
     elmtype *temp1= new elmtype[capacity];                                                                                               // third array[second[front + i % capacity]= secondarray[]
     for(int i=0; i< size; i++) {  
         temp1[i]= data[(front +i) % (capacity /2)] ;                                                  //(i + front) %(capacity /2)
            //temp1[i+size] = data[((front + i)+1) % (size)];     // thirdarray[secondarray]                            // same process in add back 
        }
        front =0;
       // back = size-1;
        data = temp1;
        back = size -1;
        //size++;
    }


if (dataInitialized==true) {  
    capacity= capacity * 2; 
     elmtype *temp1= new elmtype[capacity]; 
     //front= ((front + capacity) -1) % capacity;                          
    int *temp2 = new int[capacity];                        
    int *temp3= new int[capacity];   
      for(int i=0; i< size; i++) {
          if ((arraythree[arraytwo[(front + i) % size]] == (front + i) % size) && arraytwo[(front + i) % size] < thirdarraysize){
            temp1[i]= data[((front +i)) % capacity];
             temp2[i] = arraytwo[i];
             temp3[i]=arraythree[i];
          }
        else {
          // temp1[i]= initVal;
            temp1[(front + i) % capacity] = initVal;
            arraytwo[i] = thirdarraysize;
            arraythree[thirdarraysize] =i;
            thirdarraysize++; 

          //  dataInitialized = false;
          //  temp3[i]=initVal;
            }
            
        }
        data = temp1;
        front =0;
        back = size -1;

      //  front= ((front + size) -1) % size;
       // delete[] data;
        //size++;
       // delete[] temp1;
     //   arraytwo = temp2;
       // arraythree = temp3;
        // if (size >0) {
        //     arraytwo[front]= thirdarraysize;                    // WHAT DOES THIS DO?? 
        //     arraythree[thirdarraysize]= front;          
        // }
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
        back= back -1;
    }
    size--;
    // back = (back +capacity -1) % capacity;   
    // size = size -1;

    if (size <= (capacity * .25))  {
            capacity = capacity /2; 
            elmtype *temp1= new elmtype[capacity];
            for(int i=0; i<size; i++) {
                temp1[i]=data[(front + i) % (capacity*2)];
            }
            data=temp1;
			front = 0;
			back = size-1;
			return;
           // delete[] data;
           // delete[] temp1;
    }
}
void DelFront(){
   //front = (front + capacity + 1)% capacity;
  // size = size -1;
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
           // delete[] data;
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
//template <typename elmtype>
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
    //elmtype pivot = data[rand() % size];   
   // elmtype pivot = data[(front + rand() % size) % capacity] ;                //data[(front + rand() % size) % capacity];
    // int place=0;
    // int place2=0;
    // int place3=0;
   
    CDA <elmtype> temp1;
    CDA <elmtype> temp2;
    CDA <elmtype> temp3;                   // if index not initialized use initialized value, also use in comparisons

if (dataInitialized==false) {
    for(int i=0; i<size; i++) {
        if (data[(front +i) % capacity]< data[pivot]) {
            temp1.AddEnd(data[(front +i) % capacity]);
           // place++;
        }
        else if(data[(front +i) % capacity]==data[pivot]){
            temp2.AddEnd(data[(front +i) % capacity]);
           // place2++;
        }
        else {
            temp3.AddEnd(data[(front +i) % capacity]);
           // place3++;
        }
    }
}

else if (dataInitialized) {
     for(int i=0; i<size; i++) {
            if (thirdarraysize > 0 && thirdarraysize >= arraytwo[i] && arraythree[arraytwo[i]]== i){
                 if (data[(front +i) % capacity]< data[pivot]) {
                     temp1.AddEnd(data[(front +i) % capacity]);
                   //  place++;
                    }
                else if(data[(front +i) % capacity]==data[pivot]){
                     temp2.AddEnd(data[(front +i) % capacity]);
                    // place2++;
                    }
                else {
                    temp3.AddEnd(data[(front +i) % capacity]);
                   // place3++;
                    }
    }
        else {
        arraytwo[i] = thirdarraysize;
        data[(front + i) % capacity] = initVal;
        arraythree[thirdarraysize]=i;
        thirdarraysize++;  

                 if(data[(i+ front) % capacity] < data[pivot]){
					temp1.AddEnd(data[(i+ front) % capacity]);
                   // place++;
						}
				else if(data[(i+ front) % capacity] == data[pivot]){
					temp2.AddEnd(data[(front +i) % capacity]);
                   // place2++;
						}
				else {
					temp3.AddEnd(data[(i+ front) % capacity]);	
                   // place3++;
						}

    }
}        
}
// cout << "TEMP1 ";
// for (int i=0; i< temp1.Length();i++) cout << temp1[i] << " "; cout << endl;
// cout <<temp2.Length()
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
   int a1pass =size /2;                             // n = size a1= CDA a1.
   int a2pass = size - (size/2);
   CDA a1(a1pass);
   CDA a2(a2pass);
   for (int i = 0; i < size/2; i++)
      a1[i] = data[(i+front) % capacity];
   for (int i = size/2; i<size; i++)
      a2[i-size/2] = data[(i+front) % capacity];
   a1.Sort();
   a2.Sort();
   
   int n1 = size/2, n2 = size-(size/2);
   int p1 = 0, p2 = 0, i = 0;
   while (p1 < n1 && p2 < n2) 
      data[i++] = a1[p1]<a2[p2] ? a1[p1++] : a2[p2++];
   while (p1 < n1) data[i++] = a1[p1++];
   while (p2 < n2) data[i++] = a2[p2++];
   front =0;
   back =size -1;

 }

int Search(elmtype e) {

    for(int i=0; i<size; i++) {
        //  if (dataInitialized) {
        //    if (thirdarraysize > 0 && thirdarraysize >= arraytwo[i] && arraythree[arraytwo[i]]== i){
        //            if (data[(i+front)% capacity]==e){
        //                  return i;
        //            }
        //  }
        //  else {
        //      arraytwo[i] = thirdarraysize;
        //     data[front + i] = initVal;                                         // NEED TO CHECK IF INITALIZED DATA OR IF WE GET LUCKY
        //     arraythree[thirdarraysize] =i;
        //     thirdarraysize++; 
        //  }
        // }
       
        //else {
        
        if (data[(i+front)% capacity]==e){
            return i;
        }
   // }
    }
    //}
    return -1;
}
// int partition(elmtype arr[], int l, int r)
// {
//     int x = arr[r], i = l;
//     for (int j = l; j <= r - 1; j++) {
//         if (arr[j] <= x) {
//             swap(arr[i], arr[j]);
//             i++;
//         }
//     }
//     swap(arr[i], arr[r]);
//     return i;
// }
// elmtype kthSmallest(elmtype arr[], int l, int r, int k)
// {
//     // If k is smaller than number of
//     // elements in array
//     if (k > 0 && k <= r - l + 1) {
 
//         // Partition the array around last
//         // element and get position of pivot
//         // element in sorted array
//         int index = partition(arr, l, r);
 
//         // If position is same as k
//         if (index - l == k - 1)
//             return arr[index];
 
//         // If position is more, recur
//         // for left subarray
//         if (index - l > k - 1)
//             return kthSmallest(arr, l, index - 1, k);
 
//         // Else recur for right subarray
//         return kthSmallest(arr, index + 1, r,
//                             k - index + l - 1);
//     }
 
//     // If k is more than number of
//     // elements in array
//     //return ;
// }
// elmtype Select(int k){
//    return kthSmallest(data, front, back, k);
// }
int binarySearch(int l, int r, int x){
    if(x < data[(l + front) % capacity]){
          return ~0;
        }
    if(x > data[(r + front) % capacity]){
          return ~size;
        }

        if(r >= l){
          int middle = l + (r-l)/2;

          if(data[middle] == x) return middle;


          if(data[middle] > x) return binarySearch(l, middle - 1,x);


         else  return binarySearch(middle + 1, r, x);

            }

         return ~l;
      }

int BinSearch(elmtype e){
    //  return binarySearch(0, size - 1, e);

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



template <typename keytype>
class Heap {
private:
    CDA<keytype> heapArray; 
public:

int parent(int i){
    return (i-1) / 2;
}

int left(int i){
    return  2* i + 1;
}
int right(int i){
    return   2* i + 2;
}

void swap(int x, int y){
    keytype temp = heapArray[y];
    heapArray[y]= heapArray[x];
    heapArray[x] = temp;
}

void heapify(int i){
    int smallest= i;
    int leftN = left(i);
    int rightN = right(i);

    if (leftN <= heapArray.Length() -1  && heapArray[leftN] < heapArray[i]){            // if left child is smaller than current
        smallest = leftN;                                                               // set smallest to left child
    }
    else {
        smallest = i;                                                               // otherwise set current to smallest
    }

    if (rightN <=heapArray.Length()  - 1 && heapArray[rightN] < heapArray[smallest]){       // if right child smaller than current smallest, assign right to smallest
        smallest = rightN;
    }
    if (smallest != i){                                             // if current is not smallest than swap and continue through heap
        swap(i, smallest);
        heapify(smallest);
    }

}


Heap(){                         // default constructor, empty heap, nothing needed
}

Heap(const Heap <keytype> &src) {
        heapArray = src.heapArray;
}
Heap& operator=(const Heap<keytype>  &src){ 
 heapArray = src.heapArray;
 }

Heap(keytype k[], int s){       // heap constucted using O(n) bottom up heap building method with the array K containing s items of keytype  
for(int i=0; i<s; i++){
    heapArray.AddEnd(k[i]);
}

int start = ((heapArray.Length()-1) - 1)/2;     // start at parent of last child

for(int i= start; i>=0; i--){                  // interate till at root

        heapify(i);
    }
}

~Heap(){
}
keytype peekKey(){    
        return heapArray[0];
}

keytype extractMin(){        // if empty heap what should it return ??

    if (heapArray.Length() ==1){    // if only 1 element just return it
        return heapArray[0];
    }
    else {                          // otherwise save old min, set new min to last element, and heapify down, delete last element(min)
        keytype min = heapArray[0];
        heapArray[0] = heapArray[heapArray.Length() -1];
        heapify(0);
        heapArray.DelEnd();
        return min;                 // return old min
    }
} 

void insert(keytype k){
    heapArray.AddEnd(k);                    // add to end of heapArray

    int newPlace = heapArray.Length() - 1;  // start at last element

    while (newPlace!= 0 && heapArray[(newPlace - 1) / 2] > heapArray[newPlace]){        //while parent is larger than child     
            swap(newPlace, (newPlace - 1) / 2);             // swap with parent
            newPlace = (newPlace - 1) / 2;                  // compare with it's parent
    }

}

void printKey(){
    for(int i =0; i< heapArray.Length(); i++){
        cout << heapArray[i] << " ";
    }
    cout << endl;
}

};
