Philip D. Geramian
497307163
CSE-674 F2016
Homework #4: Graphs
readme.txt

Compilation Line:
$ g++ -std=c++11 *.cpp -o HW4

For this assignment we had to create a Graph class. For this class we were expected to be 
able to handle: weighted, unweighted, directed, undirected, and any combinations of those. 
We had to be able to read in our graphs from a CSV file that was formatted in a certain 
way that was disclosed to us. We also had to provide an implementation of Dijkstra 
algorithm that we could use on our graphs to find shortest paths and shortest distances 
from a given vertex to the rest of the vertices. Another task we had to do was be able to 
generate a DOT file that could be run through an interpreter so that we could see our 
graphs that we were storing in a graphical representation. Graphs as a data structure are 
important for many reasons. They allow us to see how to get from one point to another via 
traversal. I can see more so now after doing this assignment that the graph data structure 
is very useful and I could see myself making use of it again in the future.

	Graph();
		--Default constructor, makes an unweighted undirected graph instance
    Graph(std::string Filename,bool undirected=false);
    	--Makes a graph from a CSV file, if undirected is asserted, regardless of the 
    	input, the graph will be treated as an undirected graph and where weights are 
    	provided, the lower weight will win
    void setDirected();
    	--Set the mode of the graph to be directed (only changes private data that 
    	keeps track of this, will not alter the stored data)
    void setWeighted();
    	--Set the mode of the graph to be weighted (only changes private data that 
    	keeps track of this, will not alter the stored data)
    void insert_vertex(std::string v);
    	--Insert Vertex "v" into graph
    void remove_vertex(std::string v);
    	--Remove Vertex "v" from graph
    void insert_edge(std::string v1, std::string v2, int weight=1);
    	--Insert edge from "v1" to "v2" with weight (if provided) into graph
    void remove_edge(std::string v1, std::string v2);
    	--Remove edge from "v1" to "v2" in graph
    void show(std::string FileName, bool path=false, std::string color="black", int row=0);
    	--Generate the DOT file. If options are asserted will print the most expensive 
    	shortest path in the color from the row.
    void CreateGraphFromCSV(std::string Filename,bool undirected=false);
    	--Makes a graph from a CSV file, if undirected is asserted, regardless of the 
    	input, the graph will be treated as an undirected graph and where weights are 
    	provided, the lower weight will win. Will override existing data
    std::vector<int> Dijkstra(std::string startNode);
    	--Preform Dijkstra algorithm to all vertices from the provided vertex. Sets up 
    	private data to help find shortest path. Returns vector of shortest distances
    std::string getVertexName(int i);
    	--Return the name of the vertex
    int getSizeOfGraph();
    	--Get the number of vertexes in the graph
    std::vector<char> getPath(int i);
    	--Get the path of vertex i.

Developed Using:
Xcode 6.4 with Apple LLVM version 7.0.2 (clang-700.1.81)
Tested with both OSX (Apple LLVM version 7.0.2 (clang-700.1.81)) 
and Ubuntu 16.04 (gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.2))

References:
	"Algorithms Unlocked" - T. Cormen
	"Data Structures and Other Objects Using C++" - M. Main & W. Savitch 4th Ed.
	DOT Language Document provided by Dr. Lee
	DOT Guide provided by Dr. Lee
	http://graphviz.org/
	Piazza
	http://www.geeksforgeeks.org/greedy-algorithms-set-7-dijkstras-algorithm-for-adjacency-list-representation/
	trifort.org
	Class notes provided by Dr. Lee