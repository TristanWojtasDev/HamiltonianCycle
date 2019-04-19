//Program Name: Hamiltonian Path Program
//Programmer Name: Tristan Wojtas
//Description: Finds if there is a hamiltonian path from an undirected graph
//Date Created:4/18/19
#include <iostream>
#include <cstdlib>
#include<fstream>
#include<string>
#include<vector>
#include<ostream>
using namespace std;

class AdjacencyMatrix
{
private:
	int n;
	int **adj;
	bool *visited;
public:
	AdjacencyMatrix(int n)//Constructor
	{
		this->n = n;
		visited = new bool[n];
		adj = new int*[n];
		for (int i = 0; i < n; i++)
		{
			adj[i] = new int[n];
			for (int j = 0; j < n; j++)
			{
				adj[i][j] = 0;
			}
		}
	}

	//Description:Adds edges to the adjacency matrix 2d array
	//Pre-condition:No edges
	//Post-condition:Edges with origin and destination are added
	void add_edge(int origin, int destin)
	{
		if (origin > n || destin > n || origin < 0 || destin < 0)
		{
			cout<< "Unavailable edge!\n";
		}
		else
		{
			adj[origin - 1][destin - 1] = 1;
		}
	}

	//Description:Displays the original input of the graph
	//Pre-condition:Takes information read in main
	//Post-condition:Prints it to screen
	void displayInput(vector<int>first, vector<int>second, int size, int number) {

		cout << "Graph " << number << " Input" << endl;
		cout << n << " " << size << endl;
		for (int i = 0; i < size; i++) {
			cout << first[i] << " " << second[i] << endl;
		}
		cout << endl;
	}

	//Description:Displays vertices only
	//Pre-condition:Takes vertice information from main
	//Post-condition:Prints it to screen
	void displayVertices(int number) {
		
		cout << "Graph " << number << " Vertices:" << endl;
		for (int i = 1; i <= n; i++)
			cout << i << endl;
		cout << endl;
	}

	//Description:Displays edges only
	//Pre-condition:Takes edge information from main
	//Post-condition:Prints it to screen
	void displayEdges(vector<int>first, vector<int>second, int size, int number) {
			 
		cout << "Graph " << number << " Edges:" << endl;
		for (int i = 0; i < size; i++) {
			cout << first[i] << " " << second[i] << endl;
		}
		cout << endl;
	}

	//Description:Displays adjacency matrix
	//Pre-condition: Takes adjacency matrix
	//Post-condition:Prints it to screen in 2D
	void displayAdjacency()
	{
		cout<< "Adjacency Matrix: " << endl;
		int i, j;
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
				cout << adj[i][j] << "  ";
			cout << endl;
		}
		cout << endl;
	}

	//Description:Checks to see if vertex can be added at position
	//Pre-condition:Takes in vertex information path array and position
	//Post-condition:Returns true if vertex can be added
	bool isSafe(int v, int path[], int pos)
	{
		if (adj[path[pos - 1]][v] == 0)
			return false;
		for (int i = 0; i < pos; i++)
			if (path[i] == v)
				return false;
		return true;
	}

	//Description: Recursive function to solve hamiltonian cycle
	//Pre-condition:Takes path array and position
	//Post-condition: Send path to hamCycle function to print
	bool hamCycleUtil(int path[], int pos)
	{
		if (pos == 1) {
			int a = (n - (n - 1));
			cout << "Adding Vertex " <<a<<endl;
		}
		if (pos == n) {
			if (adj[path[pos - 1]][path[0]] == 1) {
				cout << "Adding Vertex " << path[1]<< endl;
				return true;
			}
			else
				return false;
		}
		for (int v = 0; v < n; v++) {
			int temp = 0;
			int temp2 = 0;
			if (isSafe(v, path, pos)) {
				path[pos] = v;
				cout << "Adding Vertex " << v+1 << endl;
				temp = v + 1;
				cout << "Adding Edge " << v << " " << v + 1 << endl;
				if (hamCycleUtil(path, pos + 1) == true)
					return true;
				path[pos] = -1;
				temp2 = v;
				cout << "Removing Vertex " << v+1 << endl;
				cout << "Removing Edge " << temp2 << " " << temp << endl;
	
			}
		}
		return false;
	}

	//Description:Solves hamiltonian cycle problem by sending to recursive helper
	//Pre-condition:Takes size of 2d array needed creates it and sends to recursive fcn
	//Post-condition:Prints result if not possible
	bool hamCycle(int graphNumber)
	{
		cout << "Graph " << graphNumber << " Path Build: " << endl;
		int *path = new int[n];
		for (int i = 0; i < n; i++)
			path[i] = -1;
		path[0] = 0;
		if (hamCycleUtil(path, 1) == false) {
			cout << "\nNo Hamiltonian Cycle" << endl;
			return false;
		}
		printSolution(path);
		return true;
	}

	//Description: Prints hamiltonian cycle
	//Pre-condition:Takes path
	//Post-condition:Prints to screen
	void printSolution(int path[])
	{
		cout << "\nHamiltonian cycle" << endl;
		for (int i = 0; i < n; i++)
			cout << path[i]+1<< " ";
		cout << path[0]+1 << endl;
		cout << endl << endl;
	}
};

//Description:Main declares variables, opens file, reads data, calls functions
//Pre-condition:Need a graph text file
//Post-condition:Prints result to screen
int main()
{
	//Main variable declarations
	ifstream inFile;
	int nodes, origin, destin, edges;
	int graphNumber = 1;
	string inputFile, graph, number;

	cout << "Enter input file: " << endl;
	cin >> inputFile;
	inFile.open(inputFile.c_str());

	if (!inFile) {
		cout << "Unable to open file";
		exit(1);
	}

	//Loop through file
	while (!inFile.eof()) {

		inFile >> nodes;
		AdjacencyMatrix am(nodes);
		inFile >> edges;
		inFile >> graph;
		inFile >> number;
		vector<int>first;
		vector<int>second;
		for (int i = 0; i < edges; i++)
		{
			inFile >> origin;
			inFile >> destin;

			if ((origin == -1) && (destin == -1))
				break;
			am.add_edge(origin, destin);
			am.add_edge(destin, origin);
			first.push_back(origin);
			second.push_back(destin);
		}
		am.displayInput(first, second, edges, graphNumber);
		am.displayVertices(graphNumber);
		am.displayEdges(first, second, edges, graphNumber);
		am.displayAdjacency();
		am.hamCycle(graphNumber);
		graphNumber++;
	}
	system("pause");
	return 0;
}