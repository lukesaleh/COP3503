#pragma once
#include <iostream>
#include <vector>
#include "leaker.h"
using namespace std;
template <typename T>

class LinkedList {
public:
	struct Node {
		T data;
		Node* next;
		Node* prev;
	};
	LinkedList();
	LinkedList(const LinkedList<T>& list);
	LinkedList<T>& operator=(const LinkedList<T>& rhs);
	~LinkedList();
	void Clear();
	void AddHead(const T& data);
	void AddTail(const T& data);
	unsigned int NodeCount() const;
	void AddNodesHead(const T* data, unsigned int count);
	void AddNodesTail(const T* data, unsigned int count);
	void PrintForward() const;
	void PrintReverse() const;
	Node* Head();
	const Node* Head() const;
	Node* Tail();
	const Node* Tail() const;
	Node* GetNode(unsigned int index);
	const Node* GetNode(unsigned int index) const;
	const T& operator[](unsigned int index) const;
	T& operator[](unsigned int index);
	Node* Find(const T& data);
	const Node* Find(const T& data) const;
	void FindAll(vector<Node*>& outData, const T& value) const;
	void InsertBefore(Node* node, const T& data);
	void InsertAfter(Node* node, const T& data);
	void InsertAt(const T& data, unsigned int index);
	bool operator==(const LinkedList<T>& rhs) const;
	bool RemoveHead();
	bool RemoveTail();
	unsigned int Remove(const T& data);
	bool RemoveAt(unsigned int index);
	void PrintForwardRecursive(const Node* node) const;
	void PrintReverseRecursive(const Node* node) const;
private:
	unsigned int nodeCount;
	Node* head;
	Node* tail;
};
template <typename T>
void LinkedList<T>::Clear() {
	nodeCount = 0;
	Node* nodeCheck;
	nodeCheck = head;
	head = nullptr;
	tail = nullptr;
	Node* tempNode;
	while (nodeCheck != nullptr) {
		tempNode = nodeCheck->next;
		delete nodeCheck;
		nodeCheck = tempNode;
	}
}
template <typename T>
LinkedList<T>::LinkedList() {
	nodeCount = 0;
	head = nullptr;
	tail = nullptr;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
	this->nodeCount = 0;
	this->head = nullptr;
	this->tail = nullptr;
	for (int i = 0; i < (int)list.nodeCount; i++) {
		AddTail(list.GetNode(i)->data);
	}
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
	Clear();
	for (int i = 0; i < (int)rhs.nodeCount; i++) {
		AddTail(rhs.GetNode(i)->data);
	}
	return *this;
}

template <typename T>
LinkedList<T>::~LinkedList() {
	Clear();
}

template<typename T>
void LinkedList<T>::AddHead(const T& data) {
	Node* headNode = new Node();
	headNode->data = data;
	headNode->next = nullptr;
	headNode->prev = nullptr;
	if (head == nullptr) {
		head = headNode;
		tail = headNode;
		head->next = nullptr;
		head->prev = nullptr;
	}
	else {
		head->prev = headNode;
		if (nodeCount == 1) {
			tail->prev = headNode;
		}
		headNode->next = head;
		head = headNode;
	}

	nodeCount++;
}

template<typename T>
void LinkedList<T>::AddTail(const T& data) {
	Node* tailNode = new Node();
	tailNode->data = data;
	tailNode->next = nullptr;
	tailNode->prev = nullptr;
	if (tail == nullptr) {
		head = tailNode;
		tail = tailNode;
		tail->next = nullptr;
		tail->prev = nullptr;
		tailNode->next = nullptr;
		tailNode->prev = nullptr;
	}
	else {
		tailNode->prev = tail;
		tail->next = tailNode;
		tailNode->next = nullptr;
		tail = tailNode;
	}
	nodeCount++;
}

template<typename T>
unsigned int LinkedList<T>::NodeCount() const {
	return this->nodeCount;
}

template<typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count) {
	for (int i = (int)count - 1; i >= 0; i--) {
		AddHead(data[i]);
	}
}

template<typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count) {
	for (int i = 0; i < (int)count; i++) {
		AddTail(data[i]);
	}
}

template<typename T>
void LinkedList<T>::PrintForward() const {
	Node* printer = head;
	while (printer != nullptr) {
		cout << printer->data << endl;
		printer = printer->next;
	}
}

template<typename T>
void LinkedList<T>::PrintReverse() const {
	Node* printer = tail;
	while (printer != nullptr) {
		cout << printer->data << endl;
		printer = printer->prev;
	}
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() {
	return head;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const {
	return head;
}


template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() {
	return tail;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const {
	return tail;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) {
	if (index >= nodeCount) {
		throw out_of_range("Out of range!");
	}
	else {
		unsigned int count = 0;
		Node* iterator = head;
		while (count < index) {
			iterator = iterator->next;
			count++;
		}
		return iterator;
	}
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {
	if (index >= nodeCount) {
		throw out_of_range("Out of range!");
	}
	else {
		unsigned int count = 0;
		Node* counter = head;
		while (count < index) {
			counter = counter->next;
			count++;
		}
		return counter;
	}
}

template <typename T>
const T& LinkedList<T>::operator[] (unsigned int index) const {
	Node* output = nullptr;
	if (index >= nodeCount) {
		throw out_of_range("Out of range!");
	}
	else {
		output = GetNode(index);
	}
	return output->data;
}
template <typename T>
T& LinkedList<T>::operator[] (unsigned int index) {
	Node* output = nullptr;
	if (index > nodeCount) {
		throw out_of_range("Out of range!");
	}
	else {
		output = GetNode(index);
	}
	return output->data;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) {
	Node* iterator = head;
	bool found = false;
	while (!found && iterator->next != nullptr) {
		if (iterator->data == data) {
			found = true;
		}
		else {
			iterator = iterator->next;
		}
	}
	if (found) {
		return iterator;
	}
	else {
		return nullptr;
	}

}
template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const {
	Node* iterator = head;
	bool found = false;
	while (!found && iterator->next != nullptr) {
		if (iterator->data == data) {
			found = true;
		}
		else {
			iterator = iterator->next;
		}
	}
	if (found) {
		return iterator;
	}
	else {
		return nullptr;
	}

}

template <typename T>
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const {
	Node* check = head;
	for (int i = 0; i < (int)nodeCount; i++) {
		if (check->data == value) {
			outData.push_back(check);
		}
		check = check->next;
	}
}

template <typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data) {
	nodeCount++;
	Node* nodeInsert = new Node();
	nodeInsert->data = data;
	nodeInsert->next = node;
	nodeInsert->prev = node->prev;
	node->prev->next = nodeInsert;
	node->prev = nodeInsert;
}

template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data) {
	nodeCount++;
	Node* nodeInsert = new Node();
	nodeInsert->data = data;
	nodeInsert->prev = node;
	nodeInsert->next = node->next;
	node->next = nodeInsert;
	node->next->prev = nodeInsert;

}

template <typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index) {
	if (index > nodeCount) {
		throw out_of_range("Out of range!");
	}
	else if (index == nodeCount) {
		Node* insertNode = new Node();
		insertNode->data = data;
		tail->next = insertNode;
		insertNode->prev = tail;
		insertNode->next = nullptr;
		tail = insertNode;
	}
	else {
		Node* insertNode = new Node();
		Node* iterator = head;
		unsigned int counter = 0;
		insertNode->data = data;

		while (counter < index) {
			iterator = iterator->next;
			counter++;
		}
		insertNode->prev = iterator->prev;
		insertNode->next = iterator;
		if (iterator->prev != nullptr) {
			iterator->prev->next = insertNode;
		}
		else {
			head = insertNode;
		}
		iterator->prev = insertNode;
	}
	nodeCount++;
}

template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const {
	Node* iterator = head;
	bool equalCheck = true;
	for (int i = 0; i < (int)nodeCount; i++) {
		if (iterator->data != rhs.GetNode(i)->data) {
			equalCheck = false;
		}
		iterator = iterator->next;
	}
	return equalCheck;
}

template <typename T>
bool LinkedList<T>::RemoveHead() {
	if (head == nullptr) {
		return false;
	}
	else if (head->next == nullptr) {
		Node* headTemp = head;
		delete headTemp;
		head = nullptr;
		tail = nullptr;
		nodeCount--;
		return true;
	}
	else {
		Node* headTemp = head;
		headTemp->next->prev = nullptr;
		head = head->next;
		delete headTemp;
		nodeCount--;
			return true;
	}

}

template<typename T>
bool LinkedList<T>::RemoveTail() {
	if (tail == nullptr) {
		return false;
	}
	else if (tail->prev == nullptr) {
		Node* temp = tail;
		delete temp;
		head = nullptr;
		tail = nullptr;
		nodeCount--;
		return true;
	}
	else {
		Node* temp = tail;
		temp->prev->next = nullptr;
		tail = tail->prev;
		delete temp;
		nodeCount--;
		return true;
	}
}

template <typename T>
bool LinkedList<T>::RemoveAt(unsigned int index) {
	if (index >= nodeCount) {
		return false;
	}
	else {
		Node* iterator = head;
		unsigned int counter = 0;
		while (counter < index) {
			iterator = iterator->next;
			counter++;
		}
		if (iterator->prev == nullptr) {
			iterator->next->prev = nullptr;
		}
		else if (iterator->next == nullptr) {
			iterator->prev->next = nullptr;
		}
		else {
			iterator->prev->next = iterator->next;
			iterator->next->prev = iterator->prev;
		}
		delete iterator;
		nodeCount--;
		return true;
	}
}

template <typename T>
unsigned int LinkedList<T>::Remove(const T& data) {
	Node* check = head;
	Node* temp;
	unsigned int output = 0;
	while (check != nullptr) {
		temp = check->next;
		if (check->data == data) {
			if (check->prev == nullptr) {
				check->next->prev = nullptr;
			}
			else if (check->next == nullptr) {
				check->prev->next = nullptr;
			}
			else {
				check->prev->next = check->next;
				check->next->prev = check->prev;
			}
			delete check;
			nodeCount--;
			output++;
		}
		check = temp;
	}
	return output;
}

template <typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const {
	if (node == nullptr) {
		return;
	}
	else {
		cout << node->data << endl;
		PrintForwardRecursive(node->next);
	}
}

template <typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const {
	if (node == nullptr) {
		return;
	}
	else {
		cout << node->data << endl;
		PrintReverseRecursive(node->prev);
	}
}





