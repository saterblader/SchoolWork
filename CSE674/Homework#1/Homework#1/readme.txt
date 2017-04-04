Philip D. Geramian
497307163
CSE-674 F2016
Homework #1: Linked List
readme.txt

For this assignment we had to make both a singly and doubly linked list. These two data 
structures are very useful as we can store as much data as we could need simply by 
inserting nodes as needed. 

A singly linked list contains a pointer of type single node, which contains a pointer to 
another single node (the "next" one), as well as storing the data we are trying to place 
into this data structure. With the singly linked list we are able to take these single 
nodes and "string them together" to form a list by having their pointers point towards 
the next item in the list, with the exception that the last element points at NULL

A doubly linked list contains a pointer of the the type double node which in similar 
fashion has a pointer to another double node and the data to store the value we wish to 
place inside our data structure, but it also contains a second pointer to another instance
 of type double node to point at the previous element of the type double node. With a 
doubly linked list, we take these instances of double node and again string them together,
 with the first element having its previous pointer pointing to NULL, and the last element
 having it's next pointer also pointing to NULL.
 
For my implementation of "Team of Four" I work my way though the given list and remove the
 four elements/ pointers I wish to apply the process to, I then run that list of four 
through a member function called sort, which applies a sort to them so that they are 
sorted from lowest to highest. Once this is done I put them onto a temporary list that 
holds my sorted teams until I finish the list that I was sorting, then I assign the 
temporary list back to the input list.

For my implementation of "Reverse" I work my way to the end of the list and remove that 
element and place in onto a temporary list to hold my pointers in the reverse order. I 
continue to do this until my original list is empty at which point I reassign my temporary
 list back to my input list.
 
For my implementation of "Shuffle" I take my input list and remove the second half of 
nodes and assign them to a temporary list, and then I work my way through the original 
list, inserting the current value of my temp list into position on the original list.

My code does all of this via pointer modification, this can be seen by the member 
functions that I implemented on both list, void insert(DoubleNode* pointer); DoubleNode* 
remove_current_node(); and void insert(SingleNode* pointer); SingleNode* 
remove_current_node(); These four functions allow me to take my current item on the list 
and remove it as its original pointer and then also allows me to insert a preexisting 
pointer of the specific node type into the next postion in the list.

References:
	"Data Structures and Other Objects Using C++" - M. Main & W. Savitch 4th Ed.
	Bubblesort - Wikipedia.org
	"Algorithms Unlocked" - T. Cormen 
	Class notes provided by Dr. Lee
	
Compilation Line:
$ g++ DoubleList.cpp DoubleNode.cpp SingleList.cpp SingleNode.cpp main.cpp -Wall -o HW1
Developed Using:
Xcode 6.4 with Apple LLVM version 6.1.0 (clang-602.0.53) (based on LLVM 3.6.0svn)