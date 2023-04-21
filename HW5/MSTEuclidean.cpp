#include <iostream> // used for inputting and outputting text
#include <fstream> // used for reading file
#include <stdio.h> // used for printing functions

using namespace std;

// struct for storing x and y of vertex
struct Vertex {
	int x;
	int y;
};

int calcEuclidDistance(Vertex, Vertex);
int minimKey(int* , bool*);
void primAlgo(int** graphWeights);
void printMSTWeight(int* , int**);

int numVertices = 0;
Vertex* vertices;  // Stores the vertices read in from file
int** graphWeights; // Stores the weights of each vertex to every other vertex

int main(int argc, char* argv[]) {

	int numTests;
	ifstream graphFile;
	graphFile.open("graph.txt");

	if (graphFile.is_open()) {
		
		graphFile >> numTests;

		for (int i = 0; i < numTests; i++) {

			printf("Test case %d: ", i + 1);
			graphFile >> numVertices;

			// Initialize vertices and graphWeights array
			vertices = new Vertex[numVertices]; 
			graphWeights = new int*[numVertices];

			// Read vertices from file and further set up graphWeights array
			for (int j = 0; j < numVertices; j++) {		
				int x, y;
				graphFile >> x >> y;
				vertices[j] = {x, y};
				graphWeights[j] = new int[numVertices]; 
			}

			// For each vertex, calculate distance to other vertices and assign to graphWeights
			for (int j = 0; j < numVertices; j++) {		
				for (int k = 0; k < numVertices; k++) {
					if (k == j) { // if comparing to the same vertex, set weight to 0 and continue
						graphWeights[j][k] = 0;
						continue;
					}
					graphWeights[j][k] = calcEuclidDistance(vertices[j], vertices[k]);
				}
			}

			// Run the prim algorithm with the newly constructed graphWeights
			primAlgo(graphWeights);

			// Delete dynamically allocated memory
			for (int j = 0; j < numVertices; j++) {  
				delete[] graphWeights[j];
			}
			delete[] vertices;
			delete[] graphWeights;
		}
	}
	return 0;
}

int calcEuclidDistance(Vertex from, Vertex to) {
	float x = to.x - from.x;
	float y = to.y - from.y;

	float fdist = pow(x, 2) + pow(y, 2);
	fdist = sqrt(fdist);
	return int(round(fdist));
}

int minimKey(int* key, bool* inSet) {
	int minDist = INT_MAX;
	int min_index = 0;
	for (int i = 0; i < numVertices; i++) {
		if (inSet[i] == false && key[i] < minDist) {
			minDist = key[i];
			min_index = i;
		}
	}
	return min_index;
}

// Takes in a 2D array of graph weights, creates a MST and prints the MST weight
void primAlgo(int** graphWeights) {
	int* parent = new int[numVertices]; // For storing the parent vertex of a vertex
	int* key = new int[numVertices]; // For storing the valid edges to pick mimimum weight from
	bool* inSet = new bool[numVertices]; // For storing if a vertex is in the MST or not

	// Initialize all vertices as max dist and false inSet
	for (int i = 0; i < numVertices; i++) {   
		key[i] = INT_MAX;
		inSet[i] = false;
	}

	key[0] = 0; // vertex 0 is picked as first
	parent[0] = -1; // first vertex cannot have a parent

	// Go through each vertex
	for (int i = 0; i < numVertices - 1; i++) {

		// Find the index of the vertex with the least distance and place into MST
		int chosenIdx = minimKey(key, inSet);
		inSet[chosenIdx] = true;

		// Update all choosable edges and parent indexes of adjacent vertices of the chosen vertex
		for (int j = 0; j < numVertices; j++) {
			if (graphWeights[chosenIdx][j] != 0 && inSet[j] == false && graphWeights[chosenIdx][j] < key[j]) {
				parent[j] = chosenIdx;
				key[j] = graphWeights[chosenIdx][j];
			}
		}
	}

	// Go through the constructed MST tree, add up all their weights, and print out
	printMSTWeight(parent, graphWeights);

	// Clear dynamically allocated arrays
	delete[] parent;
	delete[] key;
	delete[] inSet;
}

void printMSTWeight(int* parent, int** graphWeights) {
	int totalWeight = 0;
	for (int i = 1; i < numVertices; i++) {
		totalWeight += graphWeights[i][parent[i]];
	}
	printf("MST weight %d\n", totalWeight);
}