////////////////////////////////////////////////////
//Author: Kenan Tarik Tufekci
//Date: 04/20/2015
//Title: CDAL Header
///////////////////////////////////////////////////

#ifndef _CDAL_H_
#define _CDAL_H_
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <iterator>

namespace cop3530 {
	template <typename T>
	class CDAL {
	private:
		struct Node {	//This is the node struct
			T* dataArray;
			Node* next;
			int arrayHead;
			int arrayTail;
			Node(T data){	//This is the node constructor
				this->dataArray = new T[50];	//each node contains a 50 element T array
				this->next = NULL;
				this->arrayHead = 0;
				this->arrayTail = 0;
				this->dataArray[0] = data;
			}

			~Node(){	//This is the node destructor
				delete[] dataArray;
			}

			bool isArrayEmpty(){	//This checks is the array is empty
				return (arrayTail == -1);	//If arrayTail is -1 then array is empty
			}

			bool isArrayFull(){		//This checks if the array is full
				return ((arrayHead + arrayTail + 1) == 50);	//If the array index is full
			}

			int arraySize(){	//This function returns the array size
				return(head + tail + 1);
			}
		}; // end struct Node

		Node* tail;
		Node* head;
		int listTail;

		int linkSize(){		//This function returns the number of nodes in the list
			int count = 0;		//The count variable is used and the value that will determine linked list size
			Node* currentNode = this->head;
			while (currentNode != NULL){	//travese the list
				++count;						//Strating from the head and traversing the 
				currentNode = currentNode->next;		//list until NULL the count will be incremented by 1
			}
			return count;	//Return the link count value
		}

		void linkListResize(){	//This function is used to resize the linked list
			int filledNodes = size() / 50;	//This is the value for filled nodes
			int blankNodes = linkSize() - filledNodes;	//This is the value of blank nodes in the list
			if (blankNodes > filledNodes) {	//If the the number of blank nodes if greater than filled nodes
				int totalNode = blankNodes / 2;	//This is the value of total blank divided by two
				int nodeCount = size() / 50;	//The node count is total number of elements divided by 50
				if (size() % 50 == 0) {	//If the total element count mod 50 == 0
					--nodeCount;	//decrement the node count
				}
				nodeCount += totalNode;	//The node count plus equlas totalNode value
				Node* currentNode = head;
				for (int i = 0; i < nodeCount; ++i) {	//Traverse the list
					currentNode = currentNode->next;
				}
				tail = currentNode;	//Th tail eaquals the current Node
				currentNode = currentNode->next;	//Current node equal current node next
				Node* nextNode = NULL;
				while (currentNode != NULL) {	//Traverse the list
					nextNode = currentNode->next;	// next Node equals current Node next
					delete currentNode;	//The current node is deleted
					currentNode = NULL;	//The the currentNode now eqauls NULL
					currentNode = nextNode; //The current Node now equals nextNode
				}
				tail->next = NULL;	//The tail next equals NULL
			}
		}


	public:
		//--------------------------------------------------
		// Constructors/Destructor/Overloaded Operators
		//--------------------------------------------------	
		CDAL(){	//This is the default constructor
			this->head = NULL;
			this->tail = NULL;
			this->listTail = -1;
		}

		//--------------------------------------------------
		CDAL(const CDAL& src){	//This is the copy constructor
			head = NULL;
			*this = src;
		}

		//--------------------------------------------------
		~CDAL(){	//This is the destructor
			clear();
			delete head;
			delete tail;
		}

		//--------------------------------------------------
		CDAL& operator=(const CDAL& src){	//This is the overloaded equals operator
			Node* currentNode = src.head;
			if (&src == this) // check for self-assignment
				return *this;// do nothing
			else{
				clear();	//delete all data
				while (currentNode != NULL){	//Traverse the list
					for (int i = 0; i <= currentNode->arrayTail; ++i){	//Traverse the array
						push_back(currentNode->dataArray[i]);	//make all the values equal to src
					}
					currentNode = currentNode->next;
				}
				return *this; //Return the newly created this
			}
		}

		//--------------------------------------------------
		T& operator[](int position){	//This is the overloaded [] operator
			if (is_empty()){
				throw std::domain_error("The list is empty");
			}
			else if (position >= size() || position < 0) {     //If invalid position 
				throw std::out_of_range("Not valid index"); //throws exception
			}
			else {
				int num = position / 50;     //Location of link to find element at
				int i = position % 50;       //Location of index in link locate
				Node * currentNode = head;
				for (int i = 0; i < num; ++i) {     //Traverse list
					currentNode = currentNode->next; //Step through the list until correct link
				}
				T& element = currentNode->dataArray[i]; //Save the value at the location 
				return element;	//Return the element
			}
		}

		//--------------------------------------------------
		T const& operator[](int position) const{	//This is the const overloaded [] operator
			if (is_empty()){
				throw std::domain_error("The list is empty");
			}
			if (position >= size() || position < 0) {     //If invalid position 
				throw std::out_of_range("Not valid index"); //throws exception
			}
			else {
				int num = position / 50;     //Location of link to find element at
				int i = position % 50;       //Location of index in link locate
				Node * currentNode = head;
				for (int i = 0; i < num; ++i) {     //Traverse list
					currentNode = currentNode->next; //Step through the list until correct link
				}
				T const& element = currentNode->dataArray[i]; //Save the value at the location 
				return element;	//Return the element
			}
		}

		//--------------------------------------------------
		// Member Functions
		//--------------------------------------------------
		T replace(const T& element, int position){	//This function is used to replace a value in the list
			int indexStart = 0;
			int indexEnd = 50;
			Node* currentNode = head;

			if (is_empty()){	//If the list is empty throw an exception
				throw std::domain_error("The list is empty");	//Throw exception
			}
			else if (position < 0 || position > listTail + 1){	//If the positon is outside the range of index values
				throw std::out_of_range("Invalid Index");	//Throw exception
			}
			else if (position >= 0 && position < 50){	//If position is between
				T item = head->dataArray[position];		//The old element in node's array[position] is saved
				head->dataArray[position] = element;	//The new element is placed in the dataArray[position]
				return item;	//The old element is returned

			}
			else if (position >= ((linkSize() * 50) - 50) && position < (linkSize() * 50)){	// If is in the tail node
				T item = tail->dataArray[position % 50];	//The old element in node's array[position] is saved	
				tail->dataArray[position % 50] = element;	//The new element is placed in the dataArray[position]
				return item;	//The old element is returned
			}
			else{	//If the element is between head and tail nodes
				while (currentNode != NULL){	//traverse the list 
					indexStart += 50;	//This is track the index values start
					indexEnd += 50;		//This will track the index values end
					currentNode = currentNode->next;
					if (position >= indexStart && position < indexEnd){	//If position is between the two index values
						T item = currentNode->dataArray[position % 50];	//The old element in node's array[position] is saved
						currentNode->dataArray[position % 50] = element;	//The new element is placed in the dataArray[position]
						return item;	//The old element is returned
					}
				}
			}
		}

		//--------------------------------------------------
		void insert(const T& element, int position){	//This is the function used to insert an element in position
			Node* currentNode = head;
			Node* newNode = NULL;
			int tailLink = ((listTail / 50) + 1);
			int startIndex = 0;
			int endIndex = 50;
			T overFlowElement;
			if (position > (listTail + 1) || position < 0){
				throw std::out_of_range("Invalid index");
			}
			if (is_empty()){
				newNode = new Node(element);
				head = newNode;
				tail = newNode;
				listTail = 0;
			}
			else if (listTail == -1 && linkSize() >= 1){
				currentNode->dataArray[0] = element;
				++listTail;
				++currentNode->arrayTail;
				tail = head;
			}
			else{
				while (currentNode != NULL){
					if (position >= startIndex && position < endIndex){
						break;
					}
					startIndex += 50;
					endIndex += 50;
					currentNode = currentNode->next;
				}
				if (currentNode->isArrayFull() == false){
					T* newArrayList = new T[50];
					for (int i = 0; i < (position % 50); ++i){
						newArrayList[i] = currentNode->dataArray[i];
					}
					newArrayList[position % 50] = element;
					overFlowElement = currentNode->dataArray[currentNode->arrayTail];
					++currentNode->arrayTail;
					for (int i = (position % 50); i < currentNode->arrayTail; ++i){
						newArrayList[i + 1] = currentNode->dataArray[i];
					}
					delete[] currentNode->dataArray;
					currentNode->dataArray = newArrayList;
					++listTail;
					return;
				}
				else{
					T* newArrayList = new T[50];
					for (int i = 0; i < (position % 50); ++i){
						newArrayList[i] = currentNode->dataArray[i];
					}
					newArrayList[position % 50] = element;
					overFlowElement = currentNode->dataArray[currentNode->arrayTail];
					for (int i = (position % 50); i < currentNode->arrayTail; ++i){
						newArrayList[i + 1] = currentNode->dataArray[i];
					}
					delete[] currentNode->dataArray;
					currentNode->dataArray = newArrayList;
					currentNode = currentNode->next;

					if (currentNode == NULL){
						newNode = new Node(overFlowElement);
						tail->next = newNode;	//The tail next now points to newNode
						tail = tail->next;	//Tail wil now poin to tail next
						++listTail;	//increment the listTail by one
					}
					else{
						while (currentNode != NULL){
							if (currentNode->next == NULL){
								T* newArrayList = new T[50];
								if (currentNode->isArrayFull()){
									for (int i = 0; i < currentNode->arrayTail; ++i){
										newArrayList[i + 1] = currentNode->dataArray[i];
									}
									newArrayList[0] = overFlowElement;
									overFlowElement = currentNode->dataArray[currentNode->arrayTail];
									delete[] currentNode->dataArray;
									currentNode->dataArray = newArrayList;
									newNode = new Node(overFlowElement);
									++listTail;
									currentNode->next = newNode;
									tail = newNode;
									return;
								}
								else{
									T* newArrayList = new T[50];
									newArrayList[0] = overFlowElement;
									for (int i = 0; i <= currentNode->arrayTail; ++i){
										newArrayList[i + 1] = currentNode->dataArray[i];
									}
									delete[] currentNode->dataArray;
									currentNode->dataArray = newArrayList;
									++currentNode->arrayTail;
									++listTail;
									return;
								}
							}
							else if (currentNode->isArrayFull() == false){
								T* newArrayList = new T[50];
								for (int i = 0; i <= currentNode->arrayTail; ++i){
									newArrayList[i + 1] = currentNode->dataArray[i];
								}
								newArrayList[0] = overFlowElement;
								delete[] currentNode->dataArray;
								currentNode->dataArray = newArrayList;
								++currentNode->arrayTail;
								++listTail;
								if (currentNode->arrayTail == 3){
									currentNode = currentNode->next;
									tail = currentNode;
									return;
								}
								else{
									tail = currentNode;
									return;
								}
							}
							else{
								T* newArrayList = new T[50];
								for (int i = 0; i < currentNode->arrayTail; ++i){
									newArrayList[i + 1] = currentNode->dataArray[i];
								}
								newArrayList[0] = overFlowElement;
								overFlowElement = currentNode->dataArray[currentNode->arrayTail];
								delete[] currentNode->dataArray;
								currentNode->dataArray = newArrayList;
								currentNode = currentNode->next;
							}
						}
					}
				}
			}
		}

		//--------------------------------------------------
		void push_front(const T& element){	//Insert the value at the front of the list
			insert(element, 0);
		}

		//--------------------------------------------------
		void push_back(const T& element){	//Insert the element at the back of the list
			Node* newNode;
			Node* currentNode = head;
			int count = 1;
			if (is_empty()){	//If the list is empty
				newNode = new Node(element);	//A new node is created
				head = newNode;	//head equals the new node
				tail = newNode;	//head equals the new node
				listTail = 0;	//increment the listTail now equals zero
			}
			else if (listTail == -1 && linkSize() >= 1){	//If the list is empty but there is still nodes in the list
				currentNode->dataArray[0] = element;	// The very fist position in the dataArray[0] = element
				++listTail;	//increment the listTail by one
				++currentNode->arrayTail;	//Increment the arrayTail by one
				tail = head;	// tail now points to the head node
			}
			else if (tail->next == NULL && tail->isArrayFull() == true){	//If the current array is full
				newNode = new Node(element);	//Create a new node for the element
				tail->next = newNode;	//The tail next now points to newNode
				tail = tail->next;	//Tail wil now poin to tail next
				++listTail;	//increment the listTail by one
			}
			else{	//If the current array is not full
				if (tail->isArrayFull() == false){	//If the tail node's array is not full
					++listTail;	//increment the listTail by one
					++tail->arrayTail;	//Increment the arrayTail by one
					tail->dataArray[listTail % 50] = element; //The tail value at dataArray[position%50] = element 
					if ((tail->arrayTail + 1) == 50){	//If the array tail now equals 50
						if (tail->next != NULL){	//If the the tail next is not NULL
							tail = tail->next;	//tail will now point to tail next
						}
					}
				}
			}
		}

		//--------------------------------------------------
		T pop_front(){	//Remove the first element in the list and return the value
			Node* currentNode = head;
			Node* previousNode = NULL;
			T element;
			if (currentNode != NULL){
				element = currentNode->dataArray[0];
			}
			int count = 0;
			if (is_empty() || listTail == -1){	//If the list is empty or listTail is -1
				throw std::domain_error("The list is empty");	//Throw exception
			}
			else if (listTail >= 0 && listTail < 50){	//If the list is only in one node
				T element = head->dataArray[0];	//the old element is saved
				if (head->arrayTail == 0){	//If there is only one element in the array
					listTail = -1;	//listTail now equals -1 indicating an empty array
					head->arrayTail = -1;	//arraytail now equals one indicating an empty array
					linkListResize();
					return element;	//Return the old element
				}
				else{	//if there is more than one but less than 50 elements
					for (int i = 0; i < head->arrayTail; ++i){	//Shift all the elements in the array
						head->dataArray[i] = head->dataArray[i + 1];
					}
					--listTail;	//decrement the listTail by one
					--head->arrayTail;	//decrement the arrayTail by one  
					linkListResize();
					return element;	//return the olf element
				}
			}
			else{	//If the listtail spans more than one node
				while (currentNode != NULL){	//traverse the list
					if (currentNode->next == NULL){	//If the current node next is NULL
						for (int i = 0; i < currentNode->arrayTail; ++i){	//Shift all the elements in the array
							currentNode->dataArray[i] = currentNode->dataArray[i + 1];
						}
						--listTail;	//decrement the arrayTail by one
						if (currentNode->arrayTail == 0){	//if the current array tail now equals 0
							currentNode->arrayTail = -1; //Set the array tail to -1 indicating an empty array
							tail = previousNode;	//The tail now points to the previous node
							linkListResize();
							return element;	//return the old element
						}
						else{	//if there is stillm more elements in the array
							--currentNode->arrayTail;	//decrement the array tail by one
							linkListResize();
							return element;	//return the old value
						}
						previousNode = currentNode;
						currentNode = currentNode->next;
					}
					else if (currentNode->next->isArrayEmpty()){	//If the current array next's array is empty
						for (int i = 0; i < currentNode->arrayTail; ++i){	//shift all the elements in the array
							currentNode->dataArray[i] = currentNode->dataArray[i + 1]; 
						}
						--listTail;	//decrement the arrayTail by one
						if (currentNode->arrayTail == 0){	//if the current array tail now equals 0
							currentNode->arrayTail = -1;	//Set the array tail to -1 indicating an empty array
							tail = previousNode;	//The tail now points to the previous node
							linkListResize();
							return element;	//return the old element
						}
						else{
							--currentNode->arrayTail;	//decrement the array tail by one
							linkListResize();
							return element;	//return the old value
						}
					}
					else{	//For all other cases
						for (int i = 0; i < currentNode->arrayTail; ++i){	//shift all the elements in the array
							currentNode->dataArray[i] = currentNode->dataArray[i + 1];
						}
						previousNode = currentNode;
						currentNode = currentNode->next;
						previousNode->dataArray[previousNode->arrayTail] = currentNode->dataArray[0];
					}
				}
			}
		}

		//--------------------------------------------------
		T pop_back(){	//Remove the first element in the list and return the value
			Node* currentNode = head;
			Node* previousNode = NULL;
			if (is_empty()){	//If the list is empty
				throw std::domain_error("The list is empty");	//Throw an exception
			}
			else if (listTail >= 0 && listTail < 50){	//If the list is only in one node
				T element = head->dataArray[listTail];	//the old element is saved
				if (head->arrayTail == 0){	//If there is only one element in the array
					listTail = -1;	//listTail now equals -1 indicating an empty array
					head->arrayTail = -1;	//arraytail now equals one indicating an empty array
					return element;		//return the old element
				}
				else{
					--listTail;		//decrement the arrayTail by one
					--head->arrayTail;		//decrement the arrayTail by one
					linkListResize();
					return element;		//return the old element
				}
			}
			else if (listTail >= ((linkSize() * 50) - 50) && listTail < (linkSize() * 50)){
				int count = 0;
				while (currentNode != NULL){	//Traverse the list
					++count;
					previousNode = currentNode;
					currentNode = currentNode->next;
					if (count == linkSize() - 1){	//If count is equal to link list size - 1
						T element = currentNode->dataArray[listTail % 50];	//the old element is saved
						if (currentNode->arrayTail == 0){	//If there is only one element in the array
							--listTail;	//decrement the arrayTail by one
							currentNode->arrayTail = -1;	//arraytail now equals one indicating an empty array
							if (count == (listTail / 50) + 1){	//If count equals listTail / 50 + 1
								tail = previousNode;	//tail now points to previousNode
								linkListResize();
								return element;	//return the old element
							}
						}
						else{
							--listTail;	//decrement the arrayTail by one
							--currentNode->arrayTail;	//decrement the arrayTail by one
							linkListResize();
							return element;	//return the old element
						}
					}
				}
			}
			else{	//For all other cases
				int count = 0;
				while (currentNode != NULL){	//Traverse the list
					++count;
					previousNode = currentNode;
					currentNode = currentNode->next;
					if (listTail >= ((count * 50) - 50) && listTail < (count * 50)){
						T element = previousNode->dataArray[listTail % 50];	//the old element is saved
						--listTail;	//decrement the arrayTail by one
						if (currentNode->arrayTail == 0){	//If there is only one element in the array
							currentNode->arrayTail = -1;	//arraytail now equals one indicating an empty
							tail = previousNode;	//tail now points to previousNode
							linkListResize();
							return element;	//return the old element
						}
						else{
							--previousNode->arrayTail;	//decrement the previous node's tail by one
							linkListResize();
							return element;	//return the old element
						}

					}
				}
			}
		}

		//--------------------------------------------------
		T remove(int position){	//Remove an element at position 
			Node* currentNode = head;
			Node* previousNode = NULL;
			Node* delNode = NULL;
			bool isShifted = false;
			int startIndex = 0;
			int endIndex = 50;
			T element;
			T overFlowElement;
			int count = 0;
			if (is_empty()){	//If the list is empty
				throw std::domain_error("The list is empty");	//Throw an exception
			}
			else if (position > listTail || position < 0){	//If the position is outside the range of the list
				throw std::out_of_range("Invalid index");	//Throw an exception
			}
			else if (position == 0){	//If the the position is 0
				linkListResize();
				return pop_front();	//Pop off the front element and return the value
			}
			else if (position == listTail){	//If the position eqaul the tail
				linkListResize();
				return pop_back();	 //Pop back the element 
			}
			else if (((listTail / 50) + 1) == 1){	//If listTail divided by 50 + 1 == 1
				element = currentNode->dataArray[position % 50];	//the old element is saved
				for (int i = (position % 50); i < currentNode->arrayTail; ++i){	
					currentNode->dataArray[i] = currentNode->dataArray[i + 1];
				}
				if (currentNode->arrayTail == 0){	//If there is only one element in the array
					head->arrayTail = -1;	//arraytail now equals one indicating an empty
					listTail = -1;	//listTail now equals -1 indicating an empty array
					linkListResize();
					return element;	//return the old element
				}
				else{
					--head->arrayTail;	//decrement the arrayTail by one
					--listTail;	//decrement the arrayTail by one
					linkListResize();
					return element;	//return the old element
				}
			}
			else{	//For all other cases
				while (currentNode != NULL){	//Traverse the list
					if (position >= startIndex && position < endIndex){
						break;	//Once the node is located break
					}
					startIndex += 50;	//Increment the start index by 50
					endIndex += 50;		//Increment the end index by 50
					previousNode = currentNode;
					currentNode = currentNode->next;
				}
				while (currentNode != NULL){
					if (currentNode->next == NULL || currentNode->next->isArrayEmpty() == true){
						if (isShifted){
							for (int i = 0; i < currentNode->arrayTail; ++i){	//Shift the elements in the array
								currentNode->dataArray[i] = currentNode->dataArray[i + 1];
							}
							if (currentNode->arrayTail == 0){	//If there is only one element in the array
								currentNode->arrayTail = -1;	//arraytail now equals one indicating an empty
								--listTail;	//decrement the arrayTail by one
								tail = previousNode;	//tail now points to previous node
								linkListResize();
								return element;	//return the old element
							}
							else{
								--currentNode->arrayTail;	//decrement the arrayTail by one
								--listTail;	//decrement the arrayTail by one
								linkListResize();
								return element;	//return the old element
							}
						}
						else{
							element = currentNode->dataArray[position % 50];	//The old element is saved
							for (int i = (position % 50); i < currentNode->arrayTail; ++i){	//Shift the elements in the array
								currentNode->dataArray[i] = currentNode->dataArray[i + 1];
							}
							if (currentNode->arrayTail == 0){	//If there is only one element in the array
								currentNode->arrayTail = -1;	//arraytail now equals one indicating an empty
								--listTail;	//decrement the arrayTail by one
								tail = previousNode;	//tail now points to previous node
								linkListResize();
								return element;	//return the old element
							}
							else{
								--currentNode->arrayTail;	//decrement the arrayTail by one
								--listTail;	//decrement the arrayTail by one
								linkListResize();
								return element;	//return the old element
							}
						}
					}
					else if (currentNode->next->isArrayEmpty() == false){	//If the current node next's array is not empty
						if (isShifted){
							for (int i = 0; i < currentNode->arrayTail; ++i){	//Shift the elements in the array
								currentNode->dataArray[i] = currentNode->dataArray[i + 1];
							}
							previousNode = currentNode;
							currentNode = currentNode->next;
							overFlowElement = currentNode->dataArray[0];	//The over flow element is saved
							previousNode->dataArray[previousNode->arrayTail] = overFlowElement;	//The overflow element is now saved in the previous node's array
						}
						else{
							element = currentNode->dataArray[position % 50];	//The old element is saved
							for (int i = (position % 50); i < currentNode->arrayTail; ++i){	//Shift the elements in the array
								currentNode->dataArray[i] = currentNode->dataArray[i + 1];
							}
							previousNode = currentNode;
							currentNode = currentNode->next;
							overFlowElement = currentNode->dataArray[0];	//The over flow element is saved
							previousNode->dataArray[previousNode->arrayTail] = overFlowElement;	//The overflow element is now saved in the previous node's array
							isShifted = true;
						}
					}
				}
			}
		}

		//--------------------------------------------------
		T item_at(int position) const{	//Return the item in the list at position
			if (is_empty()){
				throw std::domain_error("The list is empty");
			}
			else if (position >= size() || position < 0) {     //If invalid position 
				throw std::out_of_range("Invalid index"); //throws exception
			}
			else {
				int num = position / 50;     //Location of link to find element at
				int i = position % 50;       //Location of index in link locate
				Node * currentNode = head;
				for (int i = 0; i < num; ++i) {     //Traverse list
					currentNode = currentNode->next; //Step through the list until correct link
				}
				T element = currentNode->dataArray[i]; //Save the value at the location 
				return element;	//Return the element
			}
		}

		//--------------------------------------------------
		bool is_empty() const{	//Check if the list is empty
			return (tail == NULL);	//If tail points to NULL this means the list is empty
		}

		//--------------------------------------------------
		int size() const{	//Return the size of the complete array list
			return (listTail + 1);	//Return list tail plus 1
		}

		//--------------------------------------------------
		void clear(){	//Deletes all the element and links in the list
			Node* delNode = head;
			while (delNode != NULL){	//Traverse the list
				head = head->next;	//list until NULL the count will be incremented by 1
				delete delNode;	// delete the delNode
				delNode = head;	//delnode pointer now points to new head
			}
			head = NULL;	//head is set to NULL indicating an empty list
			tail = NULL;	//tail is set to NULL indicating an empty list
		}

		//--------------------------------------------------
		bool contains(const T& element, bool(*fptr)(const T& a, const T& b)) const{	//contains check is the vlaue is present
			Node* currentNode = head;
			while (currentNode != NULL){	//Traverse the list
				for (int i = 0; i <= currentNode->arrayTail; ++i){ //Traverse the array
					if (fptr(currentNode->dataArray[i], element)){	//if same char is a function pointer
						return true;	//If the values are the same return true
					}
				}
				currentNode = currentNode->next;
			}
			return false;	//If the char are not the same return false
		}

		//--------------------------------------------------
		std::ostream& print(std::ostream& out) const{	//This function prints out the list
			Node* currentNode = head;
			int count = 0;
			if (is_empty() || listTail < 0){	//If the list is empty print out empty list
				std::cout << "<Empty List>\n\n" << std::endl;
			}
			else{	//If the list is not empty
				out << "[";
				while (currentNode != NULL){	//Traverse the list printing each node's data 
					++count;
					if (currentNode->isArrayEmpty() == false){
						for (int i = 0; i <= currentNode->arrayTail; ++i){
							if (count == 1 && i == 0){	//If this is the last node in the list
								std::cout << currentNode->dataArray[i];
							}
							else{
								std::cout << ", " << currentNode->dataArray[i];
							}
						}
					}
					currentNode = currentNode->next;
				}
				std::cout << "]\n\n";
			}
			return out;	//Return the final string for print
		}

		//--------------------------------------------------
		// CDAL_Iter CLass
		//--------------------------------------------------
		class CDAL_Iter : public std::iterator<std::forward_iterator_tag, T>{
		public:
			typedef T value_type;
			typedef std::ptrdiff_t difference_type;
			typedef T& reference;
			typedef T* pointer;
			typedef std::forward_iterator_tag iterator_category;
			typedef CDAL_Iter self_type;
			typedef CDAL_Iter& self_reference;

		private:
			Node* here;     //Saves the passed in Node to here
			int index;		//Saves the passed in index value

		public:

			//--------------------------------------------------
			explicit CDAL_Iter(Node* start, int i) : here(start), index(i) {}   //This is the constructor that sets here and index node to start of list

			//--------------------------------------------------
			CDAL_Iter(const CDAL_Iter& src) : here(src.here), index(src.index) {}  //This is the copy constructor

			//--------------------------------------------------
			reference operator*() const {   //This is the *overloaded operator that derefences iterators data values
				return here->dataArray[index];
			}

			//--------------------------------------------------
			pointer operator->() const {   //This is the ->overloaded operator that grants access to memeber functions
				return &(here->dataArray[index]);
			}

			//--------------------------------------------------
			self_reference operator=(const CDAL_Iter& src) {  //This is =overloaded operator to copy contents
				this->here = src.here;
				this->index = src.index;
				return *this;
			}

			//--------------------------------------------------
			self_reference operator++() {   //This is ++overloaded operator preincrements iterator
				++index;
				if (index % 50 == 0){
					here = here->next;
					index = 0;
				}
				return *this;
			}

			//--------------------------------------------------
			self_type operator++(int) {  //This is ++overloaded operator postincrements iterator
				self_type temp(*this);
				++(*this);
				return temp;
			}

			//--------------------------------------------------
			bool operator==(const CDAL_Iter& rhs) const {  //This is ==overloaded operator that checks two iterators for equality
				return (this->here == rhs.here && this->index == rhs.index);
			}

			//--------------------------------------------------
			bool operator!=(const CDAL_Iter& rhs) const {    //This is !=overloaded operator that checks two iterators for inequality
				return (this->here != rhs.here && this->index != rhs.index);
			}
		}; // end CDAL_Iter

		//--------------------------------------------------
		// Const CDAL_Iter Class
		//--------------------------------------------------
		class Const_CDAL_Iter : public std::iterator<std::forward_iterator_tag, T>{
		public:
			typedef T value_type;
			typedef std::ptrdiff_t difference_type;
			typedef const T& reference;
			typedef const T* pointer;
			typedef std::forward_iterator_tag iterator_category;
			typedef Const_CDAL_Iter self_type;
			typedef Const_CDAL_Iter& self_reference;

		private:
			Node* here;		//Saves the passed in Node to here
			int index;		//Saves the passed in index value
		public:
			//--------------------------------------------------
			explicit Const_CDAL_Iter(Node* start, int i) : here(start), index(i)  {}   //This is the constructor that sets here and index node to start of list

			//--------------------------------------------------
			Const_CDAL_Iter(const Const_CDAL_Iter& src) : here(src.here), index(src.index) {}    //This is the copy constructor

			//--------------------------------------------------
			reference operator*() const {       //This is the *overloaded operator that derefences iterators data value
				return here->dataArray[index];
			}

			//--------------------------------------------------
			pointer operator->() const {    //This is the ->overloaded operator that grants access to memeber functions
				return &(here->dataArray[index]);
			}

			//--------------------------------------------------
			self_reference operator=(const CDAL_Iter& src) { //This is =overloaded operator to copy contents
				this->here = src.here;
				this->index = src.index;
				return *this;
			}

			//--------------------------------------------------
			self_reference operator++() {   //This is ++overloaded operator preincrements iterator
				++index;
				if (index % 50 == 0){
					here = here->next;
					index = 0;
				}
				return *this;
			}

			//--------------------------------------------------
			self_type operator++(int) {  //This is ++overloaded operator preincrements iterator
				self_type temp(*this);
				++(*this);
				return temp;
			}

			//--------------------------------------------------
			bool operator==(const Const_CDAL_Iter& rhs) const {  //This is ==overloaded operator that checks two iterators for equality
				return (this->here == rhs.here && this->index == rhs.index);
			}

			//--------------------------------------------------
			bool operator!=(const Const_CDAL_Iter& rhs) const {   //This is !=overloaded operator that checks two iterators for inequality
				return (this->here != rhs.here && this->index != rhs.index);
			}
		}; // end Const_SSLL_Iter

		typedef std::size_t size_type;
		typedef T value_type;
		typedef CDAL_Iter iterator;
		typedef Const_CDAL_Iter const_iterator;

		iterator begin() { return CDAL_Iter(head, 0); }    //This returns the iterator's pointer to start of the list
		iterator end() { return CDAL_Iter(tail->next, listTail); }    //This returns the iterator's pointer to end of the list
		const_iterator begin() const { return Const_CDAL_Iter(head, 0); }   //This returns the const iterator's pointer to start of the list
		const_iterator end() const { return Const_CDAL_Iter(tail->next, listTail); }     //This returns the const iterator's pointer to end of the list
	}; //end class CDAL
} // end namespace cop3530
#endif // _CDAL_H_
