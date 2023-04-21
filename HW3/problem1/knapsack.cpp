#include <iostream> // used for inputting and outputting text
#include <stdio.h> // used for printing functions
#include <stdlib.h> // used for generating random values
#include <time.h> // used for measuring runtime

using namespace std;

void PrintResults(int, int, double, double, int, int); // Prints the results
void RandomArrayGenerator(int*, int*, int, int); // Generates an array of size n filled with random values
int RecursiveKnapSack(int, int);
int DynamicKnapSack(int, int);
int findMax(int, int);

int arrSize = 0;
int W; // the total capacity
int* val;
int* wt;
int** dTable;

int main(int argc, char* argv[]) {
	int numArr = 0;
	int numTests = 0;
	cout << "How many tests would you like to make?" << endl;
	cin >> numTests;

	if (cin.fail()) {
		cout << "Input is not an integer." << endl;
		return 0;
	}

	cout << "What is the maximum capacity(W) you would like to test?" << endl;
	cin >> W;

	if (cin.fail()) {
		cout << "Input is not an integer." << endl;
		return 0;
	}

	srand(time(NULL));

	for (int i = 1; i < numTests+1; i++) {

		// Initialize new arrays with new sizes
		int arrSize = i * 5;

		//Variables used to test changing n and W constants
		//W = i * 20; 
		//int arrSize = 75;
	    val = new int[arrSize];
		wt = new int[arrSize];

		// Populate val and wt with random values
		RandomArrayGenerator(val, wt, arrSize, W);
		/*
		for (int o = 0; o < arrSize; o++) {
			cout << "Value: " << val[o] << endl;
			cout << "Weight: " << wt[o] << endl;
		}
		*/
		// Generate and populate dTable with -1 values
		dTable = new int* [arrSize];
		for (int j = 0; j < arrSize; j++) {
			dTable[j] = new int[W + 1];
		}
		for (int k = 0; k < arrSize; k++) {
			for (int l = 0; l < W + 1; l++) {
				dTable[k][l] = -1;
			}
		}

		// Execute both algorithms and record their times
		clock_t t0, t1;
		t0 = clock();
		int result1 = RecursiveKnapSack(arrSize, W);
		//int result1 = 0;
		t0 = clock() - t0;

		double elapsed1 = (double(t0)) / CLOCKS_PER_SEC * 1000; // Time recorded in milliseconds

		t1 = clock();
		//int result2 = RecursiveKnapSack(arrSize, W);
		//int result2 = 0;
		int result2 = DynamicKnapSack(arrSize-1, W);
		t1 = clock() - t1;

		double elapsed2 = (double(t1)) / CLOCKS_PER_SEC * 1000;
		
		PrintResults(arrSize, W, elapsed1, elapsed2, result1, result2);

		// Cleanup dynamically allocated arrays
		delete[] val;
		delete[] wt;
		for (int m = 0; m < arrSize; m++) {
			delete[] dTable[m];
		}
		delete[] dTable;
	}
	return 0;
}

/**
 Takes in an array and a desired array size. Fills wt array with random weights from 0 to W. Fills the val array with random numbers between 0 and 100
**/
void RandomArrayGenerator(int* val, int* wt, int arrSize, int W) {

	for (int i = 0; i < arrSize; i++) {
		int wtRandNumber = rand() % (W + 1); // generate random weight less than or equal to W
		wt[i] = wtRandNumber;
		int valRandNumber = rand() % 1001; // generate a random value
		val[i] = valRandNumber;
	}
	
}

/**
Prints the results, including N, W, elapsed time for rec algorithm, elapsed time for dyn algorithm, result for rec algorithm, and result for dyn algorithm
**/
void PrintResults(int N, int W, double elapsed1, double elapsed2, int result1, int result2) {
	printf("N=%d  W=%d Rec_time=%f DP_time=%f max_Rec=%d max_DP=%d\n", N, W, elapsed1, elapsed2, result1, result2);
}

int findMax(int a, int b) {
	if (a > b) {
		return a;
	}
	return b;
}

/*
Recursive KnapSack algorithm. Takes in an size of n and weight of W. Outputs the highest value achievable. 
*/
int RecursiveKnapSack(int n, int W) {
	int result;
	if (n == 0 || W == 0) { // if no more items in bag or current capacity is 0, return 0
		 result = 0;
	}
	else if(wt[n-1] > W) { // otherwise, if the weight at the next position is greater than W, go to the next position in the bag with the same capacity
		result = RecursiveKnapSack(n - 1, W);
	}
	else {
		int temp1 = RecursiveKnapSack(n - 1, W); // Case if current item was not included into calculation
		int temp2 = val[n-1] + RecursiveKnapSack(n - 1, W - wt[n-1]); // Case if current item was included into calculation
		result = findMax(temp1, temp2); // Compare the two and return the max
	}
	return result;
}

/*
Dynamic KnapSack algorithm. Takes in an size of n and weight of W. Outputs the highest value achievable. Utilizes Memoization in order to speed up search.
*/
int DynamicKnapSack(int n, int W) {
	int result;
	if (n < 0) return 0;
	if (dTable[n][W] != -1) { // If the position in the dTable at n and W does not equal -1, return the current dTable value at n and W
		return dTable[n][W];
	}
	if (wt[n] > W) { // otherwise, if the weight at the next position is greater than W, go to the next position in the bag with the same capacity
		result = DynamicKnapSack(n - 1, W);
	}
	else {
		int temp1 = DynamicKnapSack(n - 1, W); // Case if current item was not included into calculation
		int temp2 = val[n] + DynamicKnapSack(n - 1, W - wt[n]); // Case if current item was included into calculation
		result = findMax(temp1, temp2); // Compare the two and return the max
	}

	dTable[n][W] = result; // Store in dTable the result 
	return result;
}