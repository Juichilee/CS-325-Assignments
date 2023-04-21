#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

void PrintArray(int*, int);
void InsertionSort(int*, int);
void RandomArrayGenerator(int*, int);

int main(int argc, char* argv[]){
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
		InsertionSort(arr, arrSize);
		clock_t end = clock();

		PrintArray(arr, arrSize);
		
		double elapsed = double(end - start)/CLOCKS_PER_SEC;
		printf("Seconds: %f\n", elapsed);
	
		delete arr; // free memory	
	}	
	return 0;
}

void RandomArrayGenerator(int* arr, int arrSize){	
	
	for(int i = 0; i < arrSize; i++){
		int randNumber = rand()%10001; // generate random number betwen 0 and 10000
		arr[i] = randNumber;	
	}	
}

void InsertionSort(int* arr, int arrSize){	
	int curr;
	for(int i = 1; i < arrSize; i++){
		curr = arr[i];
		int j = i - 1;
		while(j >= 0 && arr[j] > curr){
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = curr;
	}
}

void PrintArray(int* arr, int arrSize){
	for(int i = 0; i < arrSize; i++){
		
		cout << arr[i] << " ";
	}
	cout << endl;
}
