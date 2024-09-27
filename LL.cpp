#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//DO NOT ADD ANY CONSTANTS OR FUNCTIONS TO ANY CLASS

// Templated Node class
// Normal node except that each node can hold a pair <T,int>
// where the first value is templated and the second value is the frequency
// (or quantity) of the first
// For example, if T was a string then it would hold string,int
template <class T>
class Node {
public:
  Node( const T& data ); //Node Constructor - Assume each quan
  pair<T,int>& GetData(); //Node Data Getter
  void SetData( const pair<T,int>& ); //Node Data Setter
  Node<T>* GetNext(); //Node m_next getter
  void SetNext( Node<T>* next ); //Node m_next setter
private:
  pair <T,int> m_data; //Holds templated data
  Node<T>* m_next; //Pointer to next node
};

template <class T>
Node<T>::Node( const T& data ) {
  m_data = make_pair(data,1);
  m_next = nullptr;
}

template <class T>
pair<T,int>& Node<T>::GetData() {
   return m_data;
}

template <class T>
void Node<T>::SetData( const pair<T,int>& data ) {
   m_data = data;
}

template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

//Templated Linked List class
template <class T>
class LL {
 public:
  // Name: LL() (Linked List) - Default Constructor
  // Desc: Used to build a new linked list
  // Preconditions: None
  // Postconditions: Creates a new linked list where m_head points to nullptr
  LL();
  // Name: ~LL() - Destructor
  // Desc: Used to destruct a LL
  // Preconditions: There is an existing LL with at least one node
  // Postconditions: A LL is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
 ~LL();
  // Name: LL (Copy Constructor)
  // Desc: Creates a copy of existing LL
  //       Requires a LL - REQUIRED to be implemented even if not used
  // Preconditions: Source LL exists
  // Postconditions: Copy of source LL
  LL(const LL&);
  // Name: operator= (Overloaded Assignment Operator)
  // Desc: Makes two LL of the same type have identical number of nodes and values
  // Preconditions: Requires two linked lists of the same templated type
  //                REQUIRED to be implemented even if not used
  // Postconditions: Two idenetical LL
  LL<T>& operator= (const LL&);
  // Name: Find
  // Desc: Iterates through LL and returns node if data found
  // Preconditions: LL Populated
  // Postconditions: Returns nullptr if not found OR Node pointer if found
  Node<T>* Find(const T& data);
  // Name: Insert
  // Desc: Either inserts a node to the linked list OR increments frequency of first
  //       Takes in data. If "first" (of pair) NOT in list, adds node
  //       If "first" (of pair) is already in list, increments quantity
  //       Inserts "first" in order with no duplicates
  // Preconditions: Requires a LL.
  // Postconditions: Node inserted in LL based on first value (or quantity incremented)
  void Insert(const T&);
  // Name: RemoveAt
  // Desc: Removes a node at a particular position based on data passed (matches first)
  // Preconditions: LL with at least one node. 
  // Postconditions: Removes first node with passed value (in first)
  void RemoveAt(const T&);
  // Name: Display
  // Desc: Display all nodes in linked list
  // Preconditions: Outputs the LL
  // Postconditions: Displays the pair in each node of LL 
  void Display();
  // Name: GetSize
  // Desc: Returns the size of the LL
  // Preconditions: Requires a LL
  // Postconditions: Returns m_size
  int GetSize();
  // Name: operator<< (Overloaded << operator)
  // Desc: Returns the ostream of the data in each node
  // Preconditions: Requires a LL
  // Postconditions: Returns an ostream with the data from each node on different line
  template <class U>
  friend ostream& operator<<(ostream& output, const LL<U>&);
  // Name: Overloaded [] operator
  // Desc: When passed an integer, returns the data at that location
  // Precondition: Existing LL
  // Postcondition: Returns pair from LL using []
  pair<T,int>& operator[] (int x);//Overloaded [] operator to pull data from LL
private:
  Node <T> *m_head; //Node pointer for the head
  int m_size; //Number of nodes in queue
};
//*****************************************************************
//Implement LL here

// Name: LL() (Linked List) - Default Constructor
// Desc: Used to build a new linked list
// Preconditions: None
// Postconditions: Creates a new linked list where m_head points to nullptr
template <class T>
LL<T>::LL(){
  m_head = nullptr;
  m_size = 0;
}

// Name: ~LL() - Destructor
// Desc: Used to destruct a LL
// Preconditions: There is an existing LL with at least one node
// Postconditions: A LL is deallocated (including dynamically allocated nodes)
//                 to have no memory leaks!
template <class T>
LL<T>::~LL(){
  //iterate through and delete each node
  Node<T> *curr = m_head;
  while(curr != nullptr){
    m_head = curr;
    curr = curr->GetNext();
    delete m_head;
  }

  //cleanup
  m_head = NULL;
  m_size = 0;
}

// Name: LL (Copy Constructor)
// Desc: Creates a copy of existing LL
//       Requires a LL - REQUIRED to be implemented even if not used
// Preconditions: Source LL exists
// Postconditions: Copy of source LL
template <class T>
LL<T>::LL(const LL& linkedL){ 
  //iterate through the linked list
  Node<T>* curr = linkedL.m_head;
  Node<T> *prev = new Node(curr->GetData().first);
  prev->SetData(make_pair(curr->GetData().first, curr->GetData().second));
  m_head = prev;
  //node prev contains the data of first node curr
  
  //curr contains the data that will be copied over 
  //curr iterates one by one creating new nodes with data
  //prev keeps track of previous node to set the next to the newly created node (nextNode)
  while(curr->GetNext() != nullptr){
    curr = curr->GetNext();
    Node<T> *nextNode = new Node(curr->GetData().first);
    nextNode->SetData(make_pair(curr->GetData().first, curr->GetData().second));
    prev->SetNext(nextNode);
    nextNode->SetNext(nullptr);
    m_size++;
    prev = prev->GetNext();
  }
  
}

// Name: operator= (Overloaded Assignment Operator)
// Desc: Makes two LL of the same type have identical number of nodes and values
// Preconditions: Requires two linked lists of the same templated type
//                REQUIRED to be implemented even if not used
// Postconditions: Two idenetical LL
template <class T>
LL<T>& LL<T>::operator= (const LL& other){
  Node<T>* curr = m_head;
  //prevent self assignment
  if (this == &other){
    return *this;
  }
  //clear out data
  while(curr != nullptr){
    m_head = curr;
    curr = curr->GetNext();
    delete m_head;
  }
  //reset member variables
  m_head = nullptr;
  m_size = 0;

  //set curr to m_head to iterate through other and copy over the data
  curr = other.m_head;
  while(curr != nullptr){
    //ensures the frequency gets copied over
    for(int i = 0; i < curr->GetData().second; i++){
      Insert(curr->GetData().first);
    }
    curr = curr->GetNext();
  }
  return *this;
}

// Name: Find
// Desc: Iterates through LL and returns node if data found
// Preconditions: LL Populated
// Postconditions: Returns nullptr if not found OR Node pointer if found
template <class T>
Node<T>* LL<T>::Find(const T& data){
  //check if string is the same
  Node<T>* curr = m_head;
  while(curr != nullptr){
    if (curr->GetData().first == data){
      return curr;
    }
    curr = curr->GetNext();
  }
  //the word is not in the linked list yet
  return nullptr;
}

// Name: Insert
// Desc: Either inserts a node to the linked list OR increments frequency of first
//       Takes in data. If "first" (of pair) NOT in list, adds node
//       If "first" (of pair) is already in list, increments quantity
//       Inserts "first" in order with no duplicates
// Preconditions: Requires a LL.
// Postconditions: Node inserted in LL based on first value (or quantity incremented)
template <class T>
void LL<T>::Insert(const T& data){
  //check if the word already exists then update its frequency  
  if(Find(data) != nullptr){
    Node<T>* foundNode = Find(data);
    
    foundNode->SetData(make_pair(foundNode->GetData().first, foundNode->GetData().second + 1));
  }
  //first word being added 
  else if (m_size == 0){
    Node<T>* temp = new Node(data);
    m_head = temp;
    temp->SetNext(nullptr);
    m_size++;
    return;
  }
  //second word being added
  else if(m_size == 1){
    Node<T>* temp = new Node(data);
    Node<T>* curr = m_head;
    //new word needs to go second
    if (curr->GetData().first < temp->GetData().first){
      curr->SetNext(temp);
      temp->SetNext(nullptr);
    }
    //new word needs to go first
    else{
      m_head = temp;
      temp->SetNext(curr);
      curr->SetNext(nullptr);
    }
    m_size++;
    return;
  }
  //if the word is not yet in the linked list but isnt the first or second entry
  else if (Find(data) == nullptr){
    Node<T>* temp = new Node(data);
    Node<T>* prev = m_head;
    Node<T>* curr = m_head;
    while(curr != nullptr){
      prev = curr;
      curr = curr->GetNext();
      //placing in the middle
      if (prev->GetData().first > temp->GetData().first){
        m_head = temp;
        temp->SetNext(prev);
        m_size++;
        return;
      }
      //placing in the beginning
      else if (prev->GetData().first < temp->GetData().first && temp->GetData().first < curr->GetData().first){
        prev->SetNext(temp);
        temp->SetNext(curr);
        m_size++;
        return;
      }
      //placing at the end
      else if(curr->GetData().first < temp->GetData().first && curr->GetNext() == nullptr){
        curr->SetNext(temp);
        temp->SetNext(nullptr);
        m_size++;
        return;
      }
    }
  }
}

// Name: RemoveAt
// Desc: Removes a node at a particular position based on data passed (matches first)
// Preconditions: LL with at least one node. 
// Postconditions: Removes first node with passed value (in first)
template <class T>
void LL<T>::RemoveAt(const T& data){
  Node<T>* curr = m_head;
  Node<T>* prev = m_head;
  //if the first word has to be removed
  if (curr->GetData().first == data){
    curr = curr->GetNext();
    delete prev;
    m_size--;
    m_head = curr;
    return;
  }
  //iterate through to find word in order to delete it
  while(curr->GetNext() != nullptr){
    prev = curr;
    curr = curr->GetNext();
    if (curr->GetData().first == data){
      prev->SetNext(curr->GetNext());
      delete curr;
      m_size--;
      return;
    }
  }
}

// Name: Display
// Desc: Display all nodes in linked list
// Preconditions: Outputs the LL
// Postconditions: Displays the pair in each node of LL 
template <class T>
void LL<T>::Display(){
  //cout the word and it's frequency
  Node<T>* curr = m_head;
  while(curr != nullptr){
    cout << curr->GetData().first << ":" << curr->GetData().second << endl;
    curr = curr->GetNext();
  }
  cout << "END" << endl;
}

// Name: GetSize
// Desc: Returns the size of the LL
// Preconditions: Requires a LL
// Postconditions: Returns m_size
template <class T>
int LL<T>::GetSize(){
  return m_size;
}

// Name: operator<< (Overloaded << operator)
// Desc: Returns the ostream of the data in each node
// Preconditions: Requires a LL
// Postconditions: Returns an ostream with the data from each node on different line
template <class U>
ostream& operator<<(ostream& output, const LL<U>& myLL){
  //cout the data and frequency for every node in the LL
  Node<U> *curr = myLL.m_head;
  while (curr != nullptr){
    cout << curr->GetData().first;
    cout << ':' << curr->GetData().second << endl;
    curr = curr->GetNext();
  }
  return output;
}

// Name: Overloaded [] operator
// Desc: When passed an integer, returns the data at that location
// Precondition: Existing LL
// Postcondition: Returns pair from LL using []
template <class T>
pair<T,int>& LL<T>::operator[] (int x){ //Overloaded [] operator to pull data from LL
  int count = 0;
  Node<T>* curr = m_head;
  //returning the first node
  if(x == 0){
    return m_head->GetData();
  }
  
  //go through linked list and return the data of the inputed value
  while(curr->GetNext() != nullptr){
    if(count == x){
      return curr->GetData();
    }
    curr = curr->GetNext();
    count++;
  }
  return curr->GetData();
}
