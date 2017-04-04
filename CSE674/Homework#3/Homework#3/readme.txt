Philip D. Geramian
497307163
CSE-674 F2016
Homework #3: Binary Search Tress and KD Trees (K=2)
readme.txt

Compilation Line:
$ g++ -std=c++11 *.cpp -o HW3

For this assignment we had to make both a Binary Search Tree and a KD Tree (K=2). These 
two data structures are interesting in different ways. With a BST, we can easily store 
and find data in an organized way. Everything to the left has a key that is smaller, and 
everything to the right has a key that is larger. With the KD Tree we made a design that 
provided for when K=2, a 2D Tree. This is useful as it allows us to have less opportunity 
to have two items that share the same key, although the possibility is still there. In 
class Dr. Lee mentioned that 2D trees could be useful for mapping in real life, an 
interesting concept, as this provides a real world example. On a side note, for me the 
KD Delete was the hardest part of the assignment and that one part took me longer than the 
rest of the assignment, lots of reading and research had to be done in order for me to 
get the result I got.

The Binary Search Tree I have developed has the following public member functions:
    BST();
    	--Creates an empty BST.
    void insert(int key, int value);
    	--Inserts the Key and Value into the proper position of the BST
    void insert(BSTNode* node);
    	--Inserts the BSTNode into the proper position of the BST
    bool deleteKey(int key);
    	--Deletes the first node in the BST to have the provided key and keeps the 
    	structure of the tree. Returns true if successful
    BSTNode* search(int key);
    	--Searches the BST for the first node with the provided key, returns 
    	NULL if not found
    int height();
    	--Returns the height of the BST
    void show(std::string filename);
    	--Creates a .DOT file that can be used in GraphViz to show the tree visually
    BSTNode* getHead();
    	--Returns the head of the BST to allow for functionality of some of the test cases

The KD Tree (K=2) I have developed has the following public member functions:
    KDTree();
    	--Creates an empty 2D Tree
    void insert(int x, int y, int value);
    	--inserts X, Y, and Value into the proper position of the 2D Tree
    void insert(KDNode* node);
    	--Inserts the KDNode in the proper position of the 2D Tree
    void deleteKey(int x, int y);
    	--Deletes the first node in the 2D Tree to have the provided X and Y values
    KDNode* search(int x, int y);
    	--Searches the 2D Tree for the first node with the provided X & Y, returns NULL 
    	if not found
    int height();
    	--Returns the height of the 2D Tree
    void show(std::string filename);
    	--Creates a .DOT file that can be used in GraphViz to show the tree visually
    KDNode* getHead();
    	--Returns the head of the 2D Tree to allow for functionality of some of the test 
    	cases

Developed Using:
Xcode 6.4 with Apple LLVM version 7.0.2 (clang-700.1.81)
Tested with both OSX (Apple LLVM version 7.0.2 (clang-700.1.81)) 
and Ubuntu 16.04 (gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.2))

References:
	http://stackoverflow.com/questions/14765155/how-can-i-easily-format-my-data-table-in-c
	http://www.cplusplus.com/reference/cmath/
	"Data Structures and Other Objects Using C++" - M. Main & W. Savitch 4th Ed.
	https://en.wikipedia.org/wiki/K-d_tree
	https://en.wikipedia.org/wiki/Binary_search_tree
	DOT Language Document provided by Dr. Lee
	DOT Guide provided by Dr. Lee
	http://graphviz.org/
	Piazza
	KD Delete Document provided by Dr. Lee
	http://www.geeksforgeeks.org/k-dimensional-tree-set-3-delete/
	trifort.org
	Class notes provided by Dr. Lee