#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void insertion (int A[], int size){

	int i,j, key;
	for (j= 1; j<size; j++){
		key = A[j];
		//insert A[j] into the sorted sequence A[1..j-1]
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
	int n2 = r - q;			//length of subarray A[q+1..r]
// let L[1..n1+1] and R[1..n2+1] be new arrays
	int L[n1+1], R[n2+1];

	for (i=0; i< n1; i++){
		L[i] = B[p+i-1];
	}

	for (j=0; j< n2; j++){
		R[j] = B[q+j];
	}
//	Issue sentinel cards
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

	clock_t begin_insertion, end_insertion, begin_merge, end_merge;
	double insertion_exec_time;
	double merge_exec_time;
	int size,i,j,k,l,m,x,w,z;

	time_t seconds;
	time(&seconds);
	srand((unsigned int) seconds);

	printf("Input Array Size: ");
	scanf("%d", &size);
	int A[size];
	int B[size];	//copy for second sort method

	for (i=0; i< size; i++){		//populate with random integers
		A[i] = rand() % 1000;
	}

//DEBUGGING - Make sure the integers are randomly generated
	printf("The randomly generated values are:\n");
	for (j =0; j < size; j++){
		printf("%d\n", A[j]);
	}

// Copy the Random valued integer array
	for (z=0; z < size; z++){
		B[z] = A[z];
	}

//DEBUGGING - Make sure the vaues are copied correctly
//	printf("The copied values are:\n");
//	for (x =0; x < size; x++){
//		printf("%d\n", B[x]);
//	}

	begin_insertion = clock();									// start clock
	insertion(A,size);								// insertion sort
	end_insertion = clock();										// end clock
	insertion_exec_time = (double)(end_insertion-begin_insertion)/ CLOCKS_PER_SEC;	//calculate time (sec)

	printf("Insertion Sort Execution Time: %f seconds\n", insertion_exec_time);

//DEBUGGING - Make sure the values are sorted properly
	printf("The first 10 insertion-sorted values are:\n");
	for (w =0; w < 10; w++){
		printf("%d\n", A[w]);
	}

	begin_merge = clock();				//start clock
	merge_sort(B,1,size);					// merge sort
	end_merge = clock();					// end clock
	merge_exec_time = (double)(end_merge-begin_merge)/ CLOCKS_PER_SEC;

	printf("Merge Sort Execution Time: %f seconds\n", merge_exec_time);

//DEBUGGING - Make sure the values are sorted properly
	printf("The first 10 merge-sorted values are:\n");
	for (m =0; m < 10; m++){
		printf("%d\n", B[m]);
	}

	return(0);
}
