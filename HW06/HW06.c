#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void print_first_ten(int A[]){
  int i;
  for (i =0; i < 10; i++){
    printf("%d\n", A[i]);
  }
}

int quick_partition(int A[],int p,int r){
  int j,q,z;
  int x = A[r];               // pivot element
  int i = p-1;
  for (j=p; j < r; j++){
    if (A[j] <= x){           //partition elements less than x
                              // if greater than x then they are left where they are
      i++;
// exchange A[i] with A[j]
      q = A[j];
      A[j] = A[i];
      A[i] = q;
  }
}
  // exchange A[i+1] with A[r]
  z = A[r];
  A[r] = A[i+1];
  A[i+1] = z;
  return (i+1);
}

int randomized_partition(int A[], int p, int r){
  int q;
  int i = (rand() %(r-p)) + p;
  //exchange A[r] with A[i]
  q = A[i];
  A[i] = A[r];
  A[r] = q;

  return quick_partition(A,p,r);
}

void randomized_quicksort(int A[], int p, int r){
  int q;
  if (p<r){
    q = randomized_partition(A,p,r);
    randomized_quicksort(A,p,q-1);
    randomized_quicksort(A, q+1, r);
  }
}

void quicksort (int A[], int p, int r){
  int q;
  if (p < r){
    q = quick_partition(A,p,r);
    quicksort(A,p,q-1);
    quicksort(A,q+1,r);
  }
}

void insertion (int A[], int size){
  int i,j, key;
  for (j= 1; j<size; j++){
    key = A[j];
// insert A[j] into the sorted sequence A[1..j-1]
    i =j-1;
    while (i >=0 && A[i] > key){
      A[i+1] = A[i];
      i = i-1;
    }
    A[i+1] = key;
  }
}

void merge (int B[], int p, int q, int r){
  int i, j, k;
  int n1 = q - p + 1; //length of subarray A[p..q]
  int n2 = r - q;                 //length of subarray A[q+1..r]
// let L[1..n1+1] and R[1..n2+1] be new arrays
  int L[n1+1], R[n2+1];

  for (i=0; i< n1; i++){
    L[i] = B[p+i-1];
  }

  for (j=0; j< n2; j++){
    R[j] = B[q+j];
  }
//      Issue sentinel cards
  L[n1] = 9999999;
  R[n2] = 9999999;

  i = 0;
  j = 0;

  for (k = (p-1); k < r; k++){
    if (L[i] <= R[j]){
      B[k] = L[i];
      i = i + 1;
    }
    else{
      B[k] = R[j];
      j=j+1;
    }
  }
}

void merge_sort(int B[], int p, int r){

  if (p < r){
    int q = floor((p+r)/2);
    merge_sort(B, p, q);
    merge_sort(B, q+1, r);
    merge (B,p,q,r);
  }
}

int main(){

  clock_t begin_quick, end_quick, begin_rand1, end_rand1, begin_rand2, end_rand2, begin_merge, end_merge;
  double quick_time;
  double rand1_time;
  double rand2_time;
  double merge_time;
  int size,i,j,k,l,m,x,w,z;

  time_t seconds;
  time(&seconds);
  srand((unsigned int) seconds);

  printf("Input Array Size: ");
  scanf("%d", &size);
  int A[size];                      // Quick sort, sorted values
  int B[size];                      // Randomized quick sort, sorted values
  int C[size];                      // Randomized quick sort, unsorted values
  int D[size];                      // Merge sort, unsorted values

// FIRST PART OF ASSIGNMENT: QUICK SORT VS RANDOMIZED QUICK SORT - SORTED VALUES
  for (i=0; i< size; i++){          // Populate A with random integers
    A[i] = rand() % 1000;
  }

//DEBUGGING - Make sure the integers are randomly generated
  printf("The first 10 randomly generated values are:\n");
  print_first_ten(A);

  insertion(A,size);                // sort A
  printf("The first 10 Sorted values are:\n");
  print_first_ten(A);               // Show that Array was sorted properly

  for (z=0; z < size; z++){         // Copy the sorted values of A into B
    B[z] = A[z];
  }

// Now that A and B are sorted, we can pass them to quick sort and randomized quick sort
  begin_quick = clock();            // start clock
  quicksort(A,0, size-1);           // Quick sort the sorted values of A
  end_quick = clock();              // end clock
  quick_time = (double)(end_quick-begin_quick)/ CLOCKS_PER_SEC;
  printf("Quick Sort Execution Time: %f seconds\n", quick_time);
  printf("The first 10 Quick-Sorted values are:\n");
  print_first_ten(A);

  begin_rand1 = clock();            // start clock
  randomized_quicksort(B,0, size-1);// randomized quick sort
  end_rand1 = clock();              // end clock
  rand1_time = (double)(end_rand1-begin_rand1)/ CLOCKS_PER_SEC;
  printf("Randomized Quick Sort Execution Time: %f seconds\n", rand1_time);
  printf("The first 10 Randomized Quick-Sorted values are:\n");
  print_first_ten(B);

// SECOND PART OF ASSIGNMENT: RANDOMIZED QUICK SORT VS MERGE SORT - RANDOM VALUES

  for (i=0; i< size; i++){         //populate C with random integers
    C[i] = rand() % 1000;
  }
  //DEBUGGING - Make sure the integers are randomly generated
  printf("\nPART 2\n");
  printf("The first 10 randomly generated values are:\n");
  print_first_ten(C);

  for (z=0; z < size; z++){       // Copy the random valued integer array into D
    D[z] = C[z];
  }
// Leave array C and D populated with these unordered values

  begin_merge = clock();          //start clock
  merge_sort(C,1,size);           // merge sort
  end_merge = clock();            // end clock
  merge_time = (double)(end_merge-begin_merge)/ CLOCKS_PER_SEC;

  printf("Merge Sort Execution Time: %f seconds\n", merge_time);

//DEBUGGING - Make sure the values are sorted properly
  printf("The first 10 Merge-Sorted values are:\n");
  print_first_ten(C);

  begin_rand2 = clock();           //start clock
  randomized_quicksort(D,0,size-1);// randomized quick sort
  end_rand2 = clock();             // end clock
  rand2_time = (double)(end_rand2-begin_rand2)/ CLOCKS_PER_SEC;
  printf("Randomized Quick Sort Execution Time: %f seconds\n", rand2_time);

//DEBUGGING - Make sure the values are sorted properly
  printf("The first 10 Randomized Quick Sorted Values Are:\n");
  print_first_ten(D);

  return(0);
}
