#include <iostream> // used for inputting and outputting text
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h> // used for printing functions
#include <stdlib.h> // used for generating random values
#include <time.h> // used for measuring runtime

using namespace std;

int DynamicKnapSack(int, int, vector<int>&);
int findMax(int, int);

int* memberCapacities; // Stores the current test's family member's capacities
int numItems; // Stores the current tests's numItems
int numMembers; // Stores the current test's numMembers
int totalPrice; // Stores the total price of all familyMembers

int* val;
int* wt;

int main(int argc, char* argv[]) {

	int numTests = 0;
	string line;
	ifstream myfilein;
	ofstream myfileout;
	myfilein.open("shopping.txt");

	if (myfilein.is_open()) {
		// Get number of tests from file
		myfilein >> numTests;
		myfileout.open("results.txt");

		// Loop through each number of tests
		for (int i = 0; i < numTests; i++) {
			// Reset test variables
			numItems = 0;
			numMembers = 0;
			totalPrice = 0;
			int** pickedItems;

			// Get numItems and numMembers from current test. Also populate val and wt arrays and memberCapacities
			myfilein >> numItems; 
			val = new int[numItems];
			wt = new int[numItems];
			for (int j = 0; j < numItems; j++) {
				myfilein >> val[j] >> wt[j];
				//printf("Value: %d  Weight: %d\n", val[j], wt[j]);
			}
			myfilein >> numMembers; 
			memberCapacities = new int[numMembers]; 
			pickedItems = new int*[numMembers];

			for (int j = 0; j < numMembers; j++) { 
				myfilein >> memberCapacities[j]; 
			}

			// Goes through each member, gets their max price and adds it to totalPrice
			for (int j = 0; j < numMembers; j++) {
				int currW = memberCapacities[j]; // Capacity from current member
				vector<int> itemIndices;
				int currPrice = DynamicKnapSack(numItems, currW, itemIndices);
				//printf("MemberCapacity: %d Price: %d\n", currW, currPrice);
				pickedItems[j] = new int[itemIndices.size()+1];
				pickedItems[j][0] = itemIndices.size();
				for (int k = 1; k < itemIndices.size()+1; k++) {
					//printf("%d ", itemIndices[k]);
					pickedItems[j][k] = itemIndices[itemIndices.size()-k]+1;
				}
				itemIndices.clear();
				totalPrice += currPrice;
			}
			//printf("\nTotal Price: %d\n", totalPrice);
			myfileout << "Test Case " << i + 1 << endl;
			myfileout << "Total Price " << totalPrice << endl;
			myfileout << "Member Items" << endl;
			for (int j = 0; j < numMembers; j++) {
				int size = pickedItems[j][0];
				myfileout << "\t" << j + 1 << ": ";
				for (int k = 1; k < size + 1; k++) {
					myfileout << pickedItems[j][k] << " ";
				}
				myfileout << endl;
			}
			// clear dynamic arrays
			delete[] val;
			delete[] wt;
			delete[] memberCapacities;
			for (int j = 0; j < numMembers; j++) {
				delete[] pickedItems[j];
			}
			delete[] pickedItems;
		}
		myfilein.close();
		myfileout.close();
	}
	return 0;
}

int findMax(int a, int b) {
	if (a > b) {
		return a;
	}
	return b;
}

/*
Dynamic KnapSack algorithm. Takes in an size of n and weight of W. Outputs the highest value achievable. Utilizes bottom up method in order to speed up search.
*/
int DynamicKnapSack(int n, int W, vector<int> &itemIndices) { // n is index of array
	int i, w;
	int** BuTable = new int*[n + 1];
	for (int i = 0; i < n + 1; i++) {
		BuTable[i] = new int[W + 1];
	}

	for (i = 0; i <= n; i++) {
		for (w = 0; w <= W; w++) {
			if (i == 0 || w == 0)
				BuTable[i][w] = 0;
			else if (wt[i - 1] <= w)
				BuTable[i][w] = findMax(val[i - 1] +
					BuTable[i - 1][w - wt[i - 1]], BuTable[i - 1][w]);
			else
				BuTable[i][w] = BuTable[i - 1][w];
		}
	}

	// Go through items chosen in the bottom up table and find the ones chosen by member
	w = W;
	int result = BuTable[n][W];
	for (i = n; i > 0 && result > 0; i--) {
		if(!(result == BuTable[i - 1][w])){
			itemIndices.push_back(i - 1);
			result = result - val[i - 1];
			w = w - wt[i - 1];
		}
	}

	return BuTable[n][W];
}