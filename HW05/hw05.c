#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Using a struct for the 'heap'
struct MaxHeap
{
	int size;
	int* array;
};

// In order to maintain the max-heap property, we call the procedure max-heapify
void max_heapify(struct MaxHeap* max_heap, int index){
	//root is at index 0
	// leftchild(i) = 2*i + 1
	// rightchild(i) = 2*i +2
	// parent(i) = (i-l)/2
	int largest = index;	   // initialize largest = index
	int left = (index <<1) +1; //left child = 2*index +1
	int right = (index+1) <<1; //right child = 2*index +2

	// Determine if left child of root exists and is > root
	if(left< max_heap->size && max_heap->array[left]> max_heap->array[index]){
		largest =left;
	}
	// Determine if right child of root exists and is > the largest so far
	if( right < max_heap->size && max_heap->array[right] > max_heap->array[largest]){
		largest =right;
	}
	if(largest != index){
		// Exchange A[i] with A[largest]
		int q = max_heap->array[largest];
		max_heap->array[largest] = max_heap->array[index];
		max_heap->array[index] = q;

   	max_heapify(max_heap, largest);
	}
}
// The procedure buildmaxheap goes through the remaining
// nodes of the tree and runs max_heapify on each one.
// Make sure to return struct!
struct MaxHeap* buildmaxheap(int* array, int size){

	int i;
	struct MaxHeap* max_heap = (struct MaxHeap*) malloc (sizeof(struct MaxHeap));
	max_heap->size = size;	//size of heap
	max_heap->array = array; // assign address to first element of array

//for i =  floor( A.length/2) down to 1
// max-heapify (array, i)

	for (i = (max_heap->size -2)/2; i>=0; --i){
		max_heapify(max_heap, i);
	}
	return max_heap;
}

void heap_sort(int* array, int size){
	struct MaxHeap* max_heap = buildmaxheap(array, size); //build
//for i = A.length downto 2
	while( max_heap->size >1){
// Exchange A[1] with A[i]
		int q = max_heap->array[0];
		max_heap->array[0] = max_heap->array[max_heap->size -1];
		max_heap->array[max_heap->size-1] = q;

// A.heap-size = A.heap-size - 1
		--max_heap->size;

		max_heapify(max_heap, 0);
	}
}

void merge(int B[], int p, int q, int r){
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

        clock_t begin_heapsort, end_heapsort, begin_merge, end_merge;
        double heapsort_exec_time;
        double merge_exec_time;
        int size,i,j,k,l,m,x,w,z;

        time_t seconds;
        time(&seconds);
        srand((unsigned int) seconds);

        printf("Input Array Size: ");
        scanf("%d", &size);
        int A[size];
        int B[size];    //copy for second sort method

        for (i=0; i< size; i++){                //populate with random integers
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
//      printf("The copied values are:\n");
//      for (x =0; x < size; x++){
//              printf("%d\n", B[x]);
//      }

        begin_heapsort = clock();       // start clock
        heap_sort(A, size);
        end_heapsort = clock();         // end clock
	// calculate time (sec)
	heapsort_exec_time = (double)(end_heapsort-begin_heapsort)/ CLOCKS_PER_SEC;
        printf("Heap Sort Execution Time: %f seconds\n", heapsort_exec_time);

//DEBUGGING - Make sure the values are sorted properly
        printf("The first 10 heap-sorted values are:\n");
        for (w =0; w < 10; w++){
                printf("%d\n", A[w]);
        }

        begin_merge = clock();                          //start clock
        merge_sort(B,1,size);                                   // merge sort
        end_merge = clock();                                    // end clock
        merge_exec_time = (double)(end_merge-begin_merge)/ CLOCKS_PER_SEC;

        printf("Merge Sort Execution Time: %f seconds\n", merge_exec_time);

//DEBUGGING - Make sure the values are sorted properly
        printf("The first 10 merge-sorted values are:\n");
        for (m =0; m < 10; m++){
                printf("%d\n", B[m]);
        }

        return(0);
}
