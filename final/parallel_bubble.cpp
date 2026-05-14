#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

void sequentialBubble(vector<int> &arr){
    int n= arr.size();
    for (int i =0; i<n-1; i++){
        bool swapped= false;
        for(int j=0; j< n-i-1; j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
                swapped=true;
            }
        }
        if (!swapped) break;
    }
}

void parallelBubble(vector<int> &arr){
    int n= arr.size();
    
    for (int phase=0; phase<n; phase++){
        if(phase%2==0){
            #pragma omp parallel for
            for (int i=0; i<n-1; i+=2){
                if(arr[i]>arr[i+1]){
                    swap(arr[i],arr[i+1]);
                }
            }
        } else{
            #pragma omp parallel for 
            for(int i=1; i<n-1; i+=2){
                if(arr[i]>arr[i+1]){
                    swap(arr[i],arr[i+1]);
                }
            }
        }
    }
}


int main(){
    int n;
    cout<<"Enter number of elements: ";
    cin>>n;

    vector<int> arr(n), arr_copy(n);

    cout<<"Enter elements: \n";
    for(int i= 0; i<n; i++){
        cin>>arr[i];
    }

    arr_copy=arr;

    double start= omp_get_wtime();
    sequentialBubble(arr);
    double end= omp_get_wtime();

    cout<<"Sequential Sorted array: ";
    for(int x: arr) cout<< x<< " ";
    cout<<"time sequential: "<<(end-start)<<" seconds\n";


    start= omp_get_wtime();
    parallelBubble(arr_copy);
    end= omp_get_wtime();

    cout<<"Parallel Sorted array: ";
    for(int x: arr_copy) cout<<x<<" ";
    cout<<"time parallel: "<<(end-start)<<" seconds";
}