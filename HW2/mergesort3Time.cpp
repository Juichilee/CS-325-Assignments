#include <iostream> // used for inputting and outputting text
#include <fstream> // used for inputting file
#include <string> // used for getline function
#include <stdio.h> // used for printing functions
#include <stdlib.h> // used for generating random values
#include <time.h> // used for measuring runtime

using namespace std;

void PrintArray(int*, int); // Prints the given array
void Merge3(int*, int, int, int, int); // Sorts and merges back together the 3 parts of the array determined by bot, mid1, mid2, and top values
void Merge_Sort3(int*, int, int); // Recursively splits array into 3 parts and then calls merge3 to piece them back together
void RandomArrayGenerator(int*, int); // Generates an array of size n filled with random values

int main(int argc, char* argv[]){
	int numArr = 0;
	int arrSize = 0; 
	int* arr;	

	int numArrays = 0;
	cout <<"How many random arrays would you like to generate?"<< endl;
	cin >> numArrays;

	if(cin.fail()){
		cout << "Input is not an integer." << endl;
		return 0;
	}
	for(int i = 0; i < numArrays; i++){
	
		srand(time(NULL));

		cout << "\nInput size n of the array to be generated."<< endl;
		cin >> arrSize;
	
		if(cin.fail()){
			cout << "Input is not an integer." << endl;
			return 0;
		}
	
		arr = new int[arrSize]; // generate new array
	
		RandomArrayGenerator(arr, arrSize);

		clock_t start = clock();
		Merge_Sort3(arr, 0, arrSize);
		clock_t end = clock();
	
		PrintArray(arr, arrSize);	
		
		double elapsed = double(end - start)/CLOCKS_PER_SEC;	
		printf("Seconds: %f\n", elapsed);
		
		delete arr;	
	}
	return 0;
}

/**
 Takes in an array and a desired array size. Fills the array with random numbers between 0 and 10000
**/
void RandomArrayGenerator(int* arr, int arrSize){	
	
	for(int i = 0; i < arrSize; i++){
		int randNumber = rand()%10001; // generate random number betwen 0 and 10000
		arr[i] = randNumber;	
	}	
}

/**
 Takes in an array and 4 ints specifying the bot, mid1, mid2, and top indices. Creates 3 temporary arrays to hold the 3 parts of the array
and then starts repeatedly looking for the smallest value among the 3 arrays, placing them back into the original array and incrementing
its index each time. 
**/
void Merge3(int *nums, int bot, int mid1, int mid2, int top) {

	int n1 = mid1 - bot;
	int n2 = mid2 - mid1;
	int n3 = top - mid2;
	
	int Arr1[n1], Arr2[n2], Arr3[n3];

	for(int i = 0; i < n1; i++){
		Arr1[i] = nums[bot + i];
	}
	for(int j = 0; j < n2; j++){
		Arr2[j] = nums[mid1 + j];
	}
	for(int k = 0; k < n3; k++){
		Arr3[k] = nums[mid2 + k];
	}
	
	int i = 0, j = 0, k = 0, l = bot;
	
	// Starts searching for smallest values among all 3 arrays. Stops once all the values in smallest array have been used.
	while(i < n1 && j < n2 && k < n3){
		if(Arr1[i] < Arr2[j]){
			if(Arr1[i] < Arr3[k]){
				nums[l++] = Arr1[i++];
			}else{
				nums[l++] = Arr3[k++];
			}
		}else{
			if(Arr2[j] <= Arr3[k]){
				nums[l++] = Arr2[j++];
			}else{
				nums[l++] = Arr3[k++];
			}
		}
	}

	// Searches for smallest values in the remaining 2 arrays whose values have not been all used. 
	while(i < n1 && j < n2){
		if(Arr1[i] < Arr2[j]){
			nums[l++] = Arr1[i++];
		}else{
			nums[l++] = Arr2[j++];
		}
	}

	while(j < n2 && k < n3){
		if(Arr2[j] < Arr3[k]){
			nums[l++] = Arr2[j++];
		}else{
			nums[l++] = Arr3[k++];
		}
	}

	while(i < n1 && k < n3){
		if(Arr1[i] < Arr3[k]){
			nums[l++] = Arr1[i++];
		}else{
			nums[l++] = Arr3[k++];
		}
	}

	// Fills in remaining values in the last array whose values have not been all used. 
	while(i < n1){
		nums[l++] = Arr1[i++];
	}
	
	while(j < n2){
		nums[l++] = Arr2[j++];
	}
	
	while(k < n3){
		nums[l++] = Arr3[k++];
	}	
}

/**
 Takes in an array and two ints indicating a bot and top index. Splits array into 3 parts depending on bot and top and
recursively calls itself on each of the 3 parts. Calls on Merge3 at the end to merge itself in the end. 
**/
void Merge_Sort3(int *nums, int bot, int top) {
	if(top - bot < 2){ // Base case is if two or one indices are left
		return;
	}
	int mid1 = bot + ((top - bot)/3);
	int mid2 = bot + 2 * ((top - bot)/3) + 1;
	Merge_Sort3(nums, bot, mid1); // Call f
	Merge_Sort3(nums, mid1, mid2);
	Merge_Sort3(nums, mid2, top);
	Merge3(nums, bot, mid1, mid2, top);
}

void PrintArray(int* arr, int arrSize){
	//cout <<"Printing array. Array Size: " << arrSize;
	for(int i = 0; i < arrSize; i++){
		
		cout << arr[i] << " ";
	}
	cout << endl;
}

