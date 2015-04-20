//Class CDAL

//------------------------------------------------------------------------------------
// Node Private Functions 
//------------------------------------------------------------------------------------

bool isArrayEmpty(): This is the private function that is used to determine if the array list that is stored in the node is empty. If arrayTail index pointer equals -1 then true is returned else false.
int arraySize(): This is the private function that is used to get the integer value of the number of elements that are stored in the array list. The temp the int value for arrayTail + 1 is returned as the list size.
bool isArrayFull(): This is the private function that is used to check if the array list that is stored in the node is full if the arrayTail index pointer + 1 equals the maximum array capacity which is 50 then true is returned else false is returned.

//------------------------------------------------------------------------------------
// List Private Functions 
//------------------------------------------------------------------------------------

int linkSize(): This is the private function that is used to get the integer value of the number of nodes that are stored in the list list. A node pointer is set the the head of the list and each time another node is found a int counter increments by one. When the end of the list is found the counter value is returned.
void linkListResize(): This is the private function that is used to reduce the size of the linked list of nodes. If a certain number of empty nodes are in the list then this function is used to reduce the number of nodes in the list by half. The list is traversed until the first empty node is found, then every proceeding node is erased.

//------------------------------------------------------------------------------------
// Constructor/Destructor/Overloaded Operators 
//------------------------------------------------------------------------------------

CDAL(): This is the default constructor this method is supposed to create an instance of the class SSLL at set head, tail pointer to NULL, and the int listTail which keeps track of the actual list size is set to -1 all indication an empty instance.
CDAL(const CDAL& src): This is the method for the copy constructor. Head will be set to NULL and *this = src will call the overloaded equals operator.
~CDAL(): This method calls the clear function and deletes the head and tail pointer;
CDAL& operator=(const CDAL& src): This is the overloaded equals operator and instance of CDAL src will be passed into the function as const and will be used to set the current class instance to its values. If &src equals this checking for self-assignment then nothing is done and *this is returned. Otherwise, the clear method is called and the current class instance is cleared out and then each value in src is then set to the current class instance. Finally, *this is returned.
￼
T& operator[](int i): This is the overloaded [] operator that will return the address of a value at a specific index int i. The first thing that this function should check is if the list is empty, if it is empty then an domain_error exception should be thrown. The next check should be if int i is equal to head index if so then return the head->data value. The next check if is int i is equal to the tail index, if so then return the tail->data value. For all other cases the function traverse the linked list to find the node index is located in then the array list inside the node is accessed with int i, once the index is found then return the currentNode->data value.
const T& operator[](int i): This is the overloaded [] operator that will return the address of a value at a specific index int I to an immutable const value. The first thing that this function should check is if the list is empty, if it is empty then a domain_error exception should be thrown. The next check should be if int i is equal to head index if so then return the head->data value. The next check if is int i is equal to the tail index, if so then return the tail->data value. For all other cases the function traverse the linked list to find the node index is located in then the array list inside the node is accessed with int i, once the index is found then return the currentNode->data value.

//------------------------------------------------------------------------------------
// Member Functions
//------------------------------------------------------------------------------------

T replace(const T& element, int position): This function is used to replace a value in the list with the value element at position that is passed into the function. The first part of this function checks if the list is empty, if so then a domain_error exception is thrown. The second check is if the int position is outside the range of index values possible for negative values and values that are beyond the end of the max list index, if so then an out_of_range exception is thrown. The next check is if the value for position between 0 and 50 indicating the element is located at the head node, if so, the old value that is in head->dataArray[i] is saved and element is save into head->dataArray[i] then the old value is returned. The next check is if the value for position is equal to linkSize()-1 or the tail node, if so the old value that is in tail->dataArray[i] is saved and element is save into tail->dataArray[1] then the old value is returned. For all other cases the linked list will be traverse until the node number matches between a strat index and end index value incrementing by 50 for each node, once the node is found then the old value that is in the currentNode->dataArray[i] is saved then replaced with new element and the old value is returned.

void insert(const T& element, int position): This function is used to insert a value in the list with the value element at position that is passed into the function. The first part of this function checks if the list is empty, if so then a domain_error exception is thrown. The second check is if the int position is outside the range of index values possible for negative values and values that are beyond the end of the max list index, if so then an out_of_range exception is thrown. The next check is if the value for position between 0 and 50 indicating the element is located at the head node, if so, The last element in the array is saved and then the new element is save in the position that was passed in the entire list is then shifted to the right. The next check is if the value for position is equal to linkSize()-1 or the tail node, if so the old value that is in tail- >dataArray[i] is saved and element is save into tail->dataArray[1] then the old value is returned
    and the entire list of element is shifted to the right. For all other cases the linked list will be traverse
    until the node number matches between a start index and end index value incrementing by 50 for each node, once
    the node is found then the old value that is in the currentNode- >dataArray[i] is saved then replaced with new 
    element and the old value is returned.

void push_front(const T& element): This function the used to add values to the front of the list the first check is to see if the list is empty, if so, then a new node is create with element and the head and tail is set to point to newNode and set the element to be the first index of the array in the node. If the list is not empty the then the new node that was created to contain element will be placed in the front of the list by accessing the head node and then inserting the new element into the first position in the list then return the old element then by shifting all the element in the list to the right by one handling overflow element by resetting as the first element in the list and repeating the shift until the end of the list is reached.

void push_back(const T& element): This function the used to add values to the back of the list the first check is to see if the list is empty, if so, then a new node is create with element and the head and tail is set to point to newNode. The element is the set to be the list index of the array in the node. If the list is not empty the then the new node that was created to contain element will be placed in the back of the list by accessing the last node and then inserting the new element into the last position in the list then return the old element.

T pop_front(): In this function the first element in the list will be removed from the front of the list and returned. The first check is to see if the list is empty, if so, throw an exception domain_error. For all other cases the head->dataArray[i] will be saved to element and returned and the all the elements in the list will be shifted to the left by one.

T pop_back():In this function the first element in the list will be removed from the front of the list and returned. The first check is to see if the list is empty, if so, throw an exception domain_error. For all other cases the tail->dataArray[arrayTail] will be saved to element and returned and the listTail pointer index will be reduced by one.

T remove(): In this function the element in the list will be removed from the position of the list and returned. The first check is to see if the list is empty, if so, throw an exception domain_error. The second check is if the position that was passed in is an invalid index, if so, throw the exception out_of_range. For all other cases the currentNode->data will be saved to element and returned and the node will be deleted from the list.

T item_at(): In this function the element in the list located at position will be returned by value. The first check is to see if the list is empty, if so, throw an exception domain_error. The second check is if the position that was passed in is an invalid index, if so, throw the exception out_of_range. If position equals 0 then the value from head->data is returned. If position equal siz() – 1, then the value from tail->data is returned. For all other cases the list is traversed and the currentNode->data will be saved to element and returned.

T is_empty(): This function return if tail == NULL if this is true then the list is empty else the list has element.

T size(): In this function the number of element is the list will be returned. A currentNode pointer will point to the head of the list and then the list will be traversed and till NULL is reached meaning the end of the list is reached. An int counter will be incremented every time a node is traversed the counter will be incremented and then when the end of list is reach the counter is returned.

T clear(): In this function all the dynamically allocated pointers and nodes will be deleted. A node pointer is set to head and the list will be traversed deleting every node along the way until the end of the list is reached.

bool conatins(const T& element, bool(*ftpr)(const T& a, const T& b)) const():: In this function that take in a T element and a function pointer to a function that compare element of type T and returns true if they are equal or false if not. The list will start from the beginning and search every element in the list if one of the element in the list match the item that was passed into the function then true is returned. If the end of the list is reached without a match then false is returned.

std::ostream& print(std::ostream& out) const: In this function all the element will be printed to the console. If the list is empty then <Empty List> will be printed, else the list will start from the beginning and print eer element out [1, 2, 3, ...] until the end of the list.

//------------------------------------------------------------------------------------ 
// CDAL_Iter Class 
//------------------------------------------------------------------------------------

Class CDAL_Iter : public std::iterator<std::forward_iterator_tag, T>

Explicit CDAL_Iter(Node* start): This is the constructor for the iterator that takes in a node
and set is to the class variable here.

CDAL_Iter(const CDAL_Iter& src): This is the copy constructor for the iterator that takes in an object of type SSLL_Iter src and then copies all the data to the current class.

reference operator*() const: This is the * overloaded operator and when called dereferences the item and returns the value at that position in the list.

pointer operator->() const: This is the -> overloaded operator that grants access to the elements functions and values.

self_references operator=(const CDAL_Iter& src): This is the is the = overloaded operator that is used to set two instances of CDAL_Iter to each other. This function is called form the copy constructor.

self_reference operator++(): This is the ++ overloaded operator that is used to increment the location in the list the item instance is point to here = here->next then return *this.

self_type operator++(int): This is the ++ overloaded operator that is used to increment the location in the list the item instance is point to.
￼
bool operator==( const CDAL_Iter& src): This is the == overloaded operator that is used to compare two nodes of similar types to see if they are equal, is so, then true is returned, if not, false is returned.

bool operator!=( const CDAL_Iter& src): This is the == overloaded operator that is used to compare two nodes of similar types to see if they are not equal, is so, then true is returned, if not, false is returned.

//------------------------------------------------------------------------------------ 
// Const SSLL_Iter Class 
//------------------------------------------------------------------------------------

Class Const_CDAL_Iter : public std::iterator<std::forward_iterator_tag, T> explicit Const_CDAL_Iter(Node* start): This is the constructor for the iterator that takes in a node and set is to the class variable here.

Const_CDAL_Iter(const CDAL_Iter& src): This is the copy constructor for the iterator that takes in an object of type SSLL_Iter src and then copies all the data to the current class.

reference operator*() const: This is the * overloaded operator and when called dereferences the item and returns the value at that position in the list.

pointer operator->() const: This is the -> overloaded operator that grants access to the elements functions and values.

self_references operator=(const Const_CDAL_Iter& src): This is the is the = overloaded operator that is used to set two instances of CDAL_Iter to each other. This function is called form the copy constructor.

self_reference operator++(): This is the ++ overloaded operator that is used to increment the location in the list the item instance is point to here = here->next then return *this.

self_type operator++(int): This is the ++ overloaded operator that is used to increment the location in the list the item instance is point to.

bool operator==( const Const_CDAL_Iter& rhs): This is the == overloaded operator that is used to compare two nodes of similar types to see if they are equal, is so, then true is returned, if not, false is returned.

bool operator!=( const Const_CDAL_Iter& rhs): This is the == overloaded operator that is used to compare two nodes of similar types to see if they are not equal, is so, then true is returned, if not, false is returned.