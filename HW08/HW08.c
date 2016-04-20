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

void counting_sort(int A[], int B[], int k, int size){
  int i,j;
  int C[k+1];                 // C[k+1] = [0...k]
// let C[0 to k] be new array
// c contains the number of each value
  for (i=0; i <= k; i++){
    C[i]=0;
  }
  for (j=0; j < size; j++){
    C[A[j]] = C[A[j]] + 1;
// C[i] now contains the number of elements equal to i.
  }
  for (i = 1; i <= k; i++){   // running sum
    C[i] = C[i] + C[i-1];
// C[i] now contains the number of elements less than or equal to i.
  }
  for (j = size-1; j >= 0; --j){
    B[C[A[j]]] = A[j];
    C[A[j]] = C[A[j]] - 1;
  }
}

int main(){

  clock_t begin_count, end_count, begin_merge, end_merge;
  double count_time;
  double merge_time;
  int size,i;
  int k =0;

  time_t seconds;
  time(&seconds);
  srand((unsigned int) seconds);

  printf("Input Array Size: ");
  scanf("%d", &size);
  int A[size];                      // Counting Sort
  int B[size];                      // Counting Sort Output Array
  int M[size];                      // Merge Sort

  for (i=0; i< size; i++){          // Populate A with random integers
    A[i] = rand() % 1000;
  }

//DEBUGGING - Make sure the integers are randomly generated
//  printf("The first 10 randomly generated values are:\n");
//  print_first_ten(A);

  for (i=0; i < size; i++){         // Copy the sorted values of A into M
    M[i] = A[i];
  }
// Determine the largest value k
  for (i=0; i < size; i++){
    if (A[i] > k){
      k = A[i];
    }
  }

  printf(" k = %d\n", k);

  begin_count = clock();            // start clock
  counting_sort(A, B, k, size);    // Counting Sort the values of A, then place into B
  end_count = clock();              // end clock
  count_time = (double)(end_count-begin_count)/ CLOCKS_PER_SEC;
  printf("Counting Sort Execution Time: %f seconds\n", count_time);
  printf("The first 10 Counting-Sorted values are:\n");
// Separate printing method due to the change in indices
// Print the firt 10 sorted values
    for (i = 1; i <= 10; i++){
        printf("%d\n", B[i]);
}

  begin_merge = clock();          //start clock
  merge_sort(M,1,size);           // merge sort the values of B
  end_merge = clock();            // end clock
  merge_time = (double)(end_merge-begin_merge)/ CLOCKS_PER_SEC;

  printf("Merge Sort Execution Time: %f seconds\n", merge_time);

//DEBUGGING - Make sure the values are sorted properly
  printf("The first 10 Merge-Sorted values are:\n");
  print_first_ten(M);

  return(0);
}
