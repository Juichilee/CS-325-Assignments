#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

void PrintArray(int*, int);
void Merge(int*, int, int, int);
void Merge_Sort(int*, int, int);
void RandomArrayGenerator(int*, int);

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
		Merge_Sort(arr, 0, arrSize-1);
		clock_t end = clock();
	
		PrintArray(arr, arrSize);	
		
		double elapsed = double(end - start)/CLOCKS_PER_SEC;	
		printf("Seconds: %f\n", elapsed);
		
		delete arr;	
	}
	return 0;
}

void RandomArrayGenerator(int* arr, int arrSize){	
	
	for(int i = 0; i < arrSize; i++){
		int randNumber = rand()%10001; // generate random number betwen 0 and 10000
		arr[i] = randNumber;	
	}	
}

void Merge(int *nums, int left, int mid, int right) {
	int i, j, lower_half, upper_half;
	int temp[(right - left) + 1];

	lower_half = left;  //What is this for?
	upper_half = mid + 1;  //What is this for?

						   //What does this loop do?
	for (i = 0; (lower_half <= mid) && (upper_half <= right); i++) {
		//What does this condition do?
		if (nums[lower_half] <= nums[upper_half]) {
			temp[i] = nums[lower_half];
			lower_half++;
		}
		//What does this condition do?
		else {
			temp[i] = nums[upper_half];
			upper_half++;
		}
	}

	//What does this condition and loop do?
	if (lower_half>mid)
		for (j = upper_half;j <= right;j++, i++)
			temp[i] = nums[j];
	//What does this else and loop do?
	else
		for (j = lower_half;j <= mid;j++, i++)
			temp[i] = nums[j];

	//What does this loop do?
	for (j = 0, i = left;i <= right;i++, j++)
		nums[i] = temp[j];
}

void Merge_Sort(int *nums, int left, int right) {
	int mid;
	if (left<right) {
		mid = (right + left) / 2;
		Merge_Sort(nums, left, mid);  //what does this call do?
		Merge_Sort(nums, mid + 1, right); //what does this call do?
		Merge(nums, left, mid, right);  //what does this call do?
	}
}

void PrintArray(int* arr, int arrSize){
	//cout <<"Printing array. Array Size: " << arrSize;
	for(int i = 0; i < arrSize; i++){
		
		cout << arr[i] << " ";
	}
	cout << endl;
}

