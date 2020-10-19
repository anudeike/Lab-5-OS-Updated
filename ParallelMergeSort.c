#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SIZE 5

int array[SIZE];
int part = 0;

void fillArrayWithRandomNumbers(int arr[SIZE]) {
    for(int i = 0; i<SIZE; i++) array[i] = rand()%100;

    // set the random numbers to test
    array[0] = 15;
    array[1] = 478;
    array[2] = 345;
    array[3] = 121;
    array[4] = 1445;

}

void printArray(int arr[SIZE]) {
    for(int i = 0; i<SIZE; i++) printf("%5d", arr[i]);
    printf("\n");
}

typedef struct StartEndIndexes {
    int start;
    int end;
} StartEndIndexes;

// Runs mergesort on the array segment described in the
// argument. Spawns two threads to mergesort each half
// of the array segment, and then merges the results.

// create a merge function for bringing together two parts recursively
void merge(int low, int mid, int high){
  int n1 = mid - low + 1, n2 = high - mid, i, j; 
    
    int left[n1];
    int right[n2];
  
    // storing values in left part 
    for (i = 0; i < n1; i++) 
        left[i] = array[i + low]; 
  
    // storing values in right part 
    for (i = 0; i < n2; i++) 
        right[i] = array[i + mid + 1]; 
  
    int k = low;  
    i = j = 0; 
  
    // merge left and right in ascending order 
    while (i < n1 && j < n2) { 
        if (left[i] <= right[j]) 
            array[k++] = left[i++]; 
        else
            array[k++] = right[j++]; 
    } 
  
    // insert remaining values from left 
    while (i < n1) { 
        array[k++] = left[i++]; 
    } 
  
    // insert remaining values from right 
    while (j < n2) { 
        array[k++] = right[j++]; 
    } 
}

// function that will be passed as void pointer
void merge_sort(int low, int high) {
  // finding midpoint of array
    int mid = low + (high - low) / 2; 
    if (low < high) { 
  
        // calling first half 
        merge_sort(low, mid); 
  
        // calling second half 
        merge_sort(mid + 1, high); 
  
        // merging the two halves 
        merge(low, mid, high); 
    } 
}
void* mergeSort(void* args) {
    
    // chooses from the ythreads
    int thread_part = part++; 
  
    // find upper and lower
    int low = thread_part * (SIZE / 4); 
    int high = (thread_part + 1) * (SIZE / 4) - 1; 
  
    // evaluating mid point 
    int mid = low + (high - low) / 2; 
    if (low < high) { 
        merge_sort(low, mid); 
        merge_sort(mid + 1, high); 
        merge(low, mid, high); 
        } 
}

int main() {
  //srand(time(0));
    StartEndIndexes sei;
    sei.start = 0;
    sei.end = SIZE - 1;
        printf("Thread has been created: \n");
    // 1. Fill array with random numbers.
    fillArrayWithRandomNumbers(array);
    
    // 2. Print the array.
    printf("Raw Array: ");
    printArray(array);

    
    // 3. Create a thread for merge sort.
   
    pthread_t thread;
    pthread_create(&thread, NULL, mergeSort,&array);
    
    // 4. Wait for mergesort to finish.
           
    pthread_join(thread, NULL);
    merge(0, (SIZE / 2 - 1) / 2, SIZE / 2 - 1); 
    merge(SIZE / 2, SIZE/2 + (SIZE-1-SIZE/2)/2, SIZE - 1); 
    merge(0, (SIZE - 1)/2, SIZE - 1); 
    
    // 5. Print the sorted array.
      printf("Sorted array:   ");
   printArray(array);
}
