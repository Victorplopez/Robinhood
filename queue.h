#ifndef _QUEUE
#define _QUEUE

#include "node.h"

template<class ItemType>
class Queue
{
private:
	Node<ItemType> *backPtr;
	Node<ItemType> *frontPtr;
public:
	Queue(); //Default Constructor
	Queue(const Queue<ItemType> &aQueue); //Copy Constructor
	~Queue();
	bool isEmpty()const;
	bool enqueue(const ItemType &newEntry);
	bool dequeue();
	ItemType peekFront() const;
};

template<class ItemType>
Queue<ItemType>::Queue()
{
	backPtr = NULL;
	frontPtr = NULL;
}

template<class ItemType>
Queue<ItemType>::Queue(const Queue<ItemType> &aQueue)
{
	Node<ItemType> *originalNodePtr = aQueue.frontPtr;

	if (originalNodePtr == NULL)
	{
		frontPtr = NULL;
		backPtr = NULL;
	}
	else
	{
		frontPtr = new Node<ItemType>(originalNodePtr->getItem(), NULL);
		Node<ItemType> *newNode;
		Node<ItemType> *curPtr = frontPtr;

		while (originalNodePtr->getNext() != NULL)
		{
			originalNodePtr = originalNodePtr->getNext();
			newNode = new Node<ItemType>(originalNodePtr->getItem(), NULL);
			curPtr->setNext(newNode);
			curPtr = curPtr->getNext();
		}
		backPtr = curPtr;
	}
}

template<class ItemType>
Queue<ItemType>::~Queue()
{
	delete[] frontPtr;
}

template<class ItemType>
bool Queue<ItemType>::isEmpty()const
{
	if (frontPtr == NULL)
		return true;
	else
		return false;
}

template<class ItemType>
bool Queue<ItemType>::enqueue(const ItemType &newEntry)
{
	Node<ItemType> *newNode = new Node<ItemType>(newEntry, NULL);
	if (isEmpty())
	{
		frontPtr = newNode;
		backPtr = newNode;
	}
	else
	{
		backPtr->setNext(newNode);
		backPtr = newNode;
	}
	return true;
}

template<class ItemType>
bool Queue<ItemType>::dequeue()
{
	Node<ItemType> *curPtr = frontPtr;

	if (isEmpty())
	{
		cout << "Empty List!" << endl;
		return false;
	}
	else
	{
		frontPtr = frontPtr->getNext();
		curPtr->setNext(NULL);
		delete(curPtr);
		return true;
	}
}

template<class ItemType>
ItemType Queue<ItemType>::peekFront() const
{
	if (isEmpty())
	{
		cout << "Empty List!" << endl;
		exit(1);
	}
	else
		return frontPtr->getItem();
}
#endif