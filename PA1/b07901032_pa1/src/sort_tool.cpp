// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>
#include<cstdlib>

// Constructor
SortTool::SortTool() {}

// Self-defined swap
void swap(int& a, int& b){
    int tmp = a;
    a = b;
    b = tmp;
}

// Self-defined 
int random(int a, int b){
    srand(time(NULL));
    return a+rand()%(b-a);
}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    for(int i=1; i<data.size(); i++){
        int k = data[i];
        int j = i-1;
        for(; j>=0 && data[j]>k; j--){
            data[j+1]=data[j];
        }
        data[j+1] = k;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}

int SortTool::RandomPartition(vector<int>& data, int low, int high){
    int i = random(low, high);
    swap(data[high], data[i]);
    return Partition(data, low, high);
}

// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    if(low<high){
        int q=RandomPartition(data, low, high);
        QuickSortSubVector(data, low, q-1);
        QuickSortSubVector(data, q+1, high);
    }
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    // Hint : Textbook page 171
    int x = data[high];
    int i = low-1;
    for(int j=low; j<high; j++){
        if(data[j]<=x){
            i++;
            swap(data[i], data[j]);
        }
    }
    swap(data[i+1], data[high]);
    return i+1;
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if(low<high){
        int q=(low+high)/2;
        MergeSortSubVector(data, low, q);
        MergeSortSubVector(data, q+1, high);
        Merge(data, low, q, q+1, high);
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int n = middle1 - low + 1;
    int m = high - middle2 +1;
    vector<int> L(n+1, 0), R(m+1, 0);
    for(int i=0; i<n; i++) L[i]=data[low+i];
    for(int i=0; i<m; i++) R[i]=data[middle2+i];
    L[n] = 2147483647;
    R[m] = 2147483647;
    int i = 0, j = 0;
    for(int k = low; k < high+1; k++){
        if(L[i] <= R[j]) data[k] = L[i++];
        else data[k] = R[j++];
    }
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int l = 2*(root+1);
    int r = 2*(root+1)+1;
    int largest = (l<=heapSize && data[l-1]>data[root]) ? l-1 : root;
    largest = (r<=heapSize && data[r-1]>data[largest]) ? r-1 : largest;
    if(largest != root){
        swap(data[root], data[largest]);
        MaxHeapify(data, largest);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for(int i=(heapSize-1)/2; i>-1; i--) MaxHeapify(data, i);
}
