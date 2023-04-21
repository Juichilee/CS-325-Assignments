#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void PrintArray(int*, int);
void InsertionSort(int*, int);

int main(int argc, char* argv[]){
	int numArr = 0;
	int arrSize = 0; 
	int* arr;	

	fstream infile;
	infile.open("data.txt"); //file opener
	
	if(infile.is_open()){
				
		//begin file opening
		string line1;
		while(getline(infile, line1)){
			numArr++;
		}
		
		infile.close();
		infile.open("data.txt"); 
		
		for(int i = 0; i < numArr; i++){
			// Load integers in one line
			infile >> arrSize;
			arr = new int[arrSize];	
			for(int j = 0; j < arrSize; j++){
				infile >> arr[j];
			}			
			// Run sort algorithms
			InsertionSort(arr, arrSize);
			PrintArray(arr, arrSize);
			delete arr;
		}
	}
	return 0;
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
	//cout <<"Printing array. Array Size: " << arrSize;
	for(int i = 0; i < arrSize; i++){
		
		cout << arr[i] << " ";
	}
	cout << endl;
}
