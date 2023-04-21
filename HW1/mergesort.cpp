#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void PrintArray(int*, int);
void Merge(int*, int, int, int);
void Merge_Sort(int*, int, int);

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
			Merge_Sort(arr, 0, arrSize-1);
			PrintArray(arr, arrSize);
			
			delete arr;
		}
	}
	return 0;
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

