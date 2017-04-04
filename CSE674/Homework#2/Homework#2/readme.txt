Philip D. Geramian
497307163
CSE-674 F2016
Homework #2: Min-Heap Priority Queue & Leonardo Heap
readme.txt

Compilation Line:
$ g++ -std=c++11 *.cpp -o HW2

For this assignment we had to make both a min-heap priority queue and a leonardo heap. 
These two data structures are useful as they allow us to neatly store and organize data and 
allow for retrieval. 

The Min-Heap Priority Queue I have developed has the following public member functions:
    MinPriorityQueue(); 
    	-- Default constructor, creates an empty Min-Heap Priority Queue
    MinPriorityQueue(std::vector<std::pair<int,int> > vect);
    	-- Constructor to create a new Min-Heap Priority Queue based off a preexisting 
    	vector
    bool isEmpty();
    	-- Checks if our Min-Heap Priority Queue is empty or not
    std::vector<std::pair<int,int> > AllMinimum();
    	-- Finds all the Minimums in our Min-Heap Priority Queue
    std::vector<std::pair<int,int> > ExtractAllMin();
    	-- Extracts the Minimums in our Min-Heap Priority Queue
    void DecreaseKey(int position,int newKey);
    	-- Changes the value of a key to alter its priority 
    void PrintQueue();
    	-- Prints out the Min-Heap Priority Queue
    void Insert(std::pair<int,int> NewValue);
    	-- Inserts a given value into our Min-Heap Priority Queue
    std::vector<std::pair<int,int> > GetQueue();
    	-- Passes back our Min-Heap Priority Queue
    int GetSize();
    	-- Returns the size of our Min-Heap Priority Queue
    std::pair<int,int> GetPair(int index);
    	-- Returns a certain index from the Min-Heap Priority Queue

The Leonardo Heap I have developed has the following public member functions:
    LeonardoHeap();
    	-- Default constructor, sets # of comparisons to zero
    LeonardoHeap(std::vector<int> vect);
    	-- Constructor that accepts a vector to form our Leonardo Heap and sets # of 
    	comparisons to zero
    bool isEmpty();
    	-- Checks if the Leonardo Heap is empty
    void SmoothSort();
    	-- Preforms a Smooth Sort on the Leonardo Heap
    std::vector<int> GetHeap();
    	-- Returns the vector that holds the Leonardo Heap
    int GetSize();
    	-- Returns the size of the Leonardo Heap
    int GetComparisons();
    	-- Returns the number of comparisons done on the Leonardo Heap

Developed Using:
Xcode 6.4 with Apple LLVM version 7.0.2 (clang-700.1.81)
Tested with both OSX (Apple LLVM version 7.0.2 (clang-700.1.81)) 
and Ubuntu 16.04 (gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.2))

References:
	https://en.wikipedia.org/wiki/Smoothsort
	http://en.cppreference.com/w/cpp/algorithm/reverse
	"Algorithms Unlocked" - T. Cormen 
	trifort.org
	Class notes provided by Dr. Lee