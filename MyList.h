#ifndef MY_LIST_H_INCLUDED_
#define MY_LIST_H_INCLUDED_

#include <iostream>
#include <iomanip>
#include <string>
using std::string;

#include <iterator>


struct Student
{
	string name;
	string group;
	int year;

	friend std::ostream& operator<<(std::ostream& os, const Student& a)
	{
		using std::setw;
		os << setw(15) << a.name << setw(15) << a.group <<
			setw(8) << a.year;
		return os;
	}
};

//***********************************************************************************************

template<class Container>
class asso_insert_iterator : public std::iterator<std::output_iterator_tag, void, void, void, void>
{
protected:
	Container& container;
public:
	explicit asso_insert_iterator(Container& c) : container(c) {}

	asso_insert_iterator<Container>& operator=(const typename Container::value_type& value)
	{
		container.insert(value);
		return *this;
	}

	asso_insert_iterator<Container>& operator*() { return *this; }

	asso_insert_iterator<Container>& operator++() { return *this; }
	asso_insert_iterator<Container>& operator++(int) { return *this; }


};

template<class Container>
inline asso_insert_iterator<Container> asso_inserter(Container& c)
{
	return asso_insert_iterator<Container>(c);
}




//***********************************************************************************************




template<typename Type>
class List
{
private:
	struct Node
	{
		Type data;
		Node* pNext;
		Node* pPrev;

		Node(Type data = Type(), Node* pNext = nullptr, Node* pPrev = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
			this->pPrev = pPrev;
		}
	};

	Node* head;
	Node* tail;
	int _size;

	List(const List&) = delete;      //не точно
	List& operator=(const List&) = delete;
public:
	List();
	~List();

	inline int size() const { return _size; }
	inline bool empty() const { return !_size; }

	Type& front();
	const Type& front() const;
	Type& back();
	const Type& back() const;

	void push_back(const Type& data);
	void push_front(const Type& data);
	void pop_back();
	void pop_front();
	void clear();
	void insertAt(const Type& data, int index);
	//insertAt(List::iterator before, const T &value)
	void removeAt(int index);
	Type& operator[](int index);
	const Type& operator[](int index) const;
};

template<typename Type>
List<Type>::List() : head(nullptr), tail(nullptr), _size(0) {}

template<typename Type>
List<Type>::~List()
{
	clear();
}

template<typename Type>
Type& List<Type>::front()
{
	if (!_size)
		throw std::exception("list iterator not deferencable");
	return head->data;
}
template<typename Type>
const Type& List<Type>::front() const
{
	if (!_size)
		throw std::exception("list iterator not deferencable");
	return head->data;
}

template<typename Type>
Type& List<Type>::back()
{
	if (!_size)
		throw std::exception("list iterator not deferencable");
	return tail->data;
}
template<typename Type>
const Type& List<Type>::back() const
{
	if (!_size)
		throw std::exception("list iterator not deferencable");
	return tail->data;
}

template<typename Type>
void List<Type>::push_back(const Type& data)
{
	if (head == nullptr)
	{
		head = new Node(data);
		tail = head;
	}
	else
	{
		tail->pNext = new Node(data, nullptr, tail);
		tail = tail->pNext;
	}
	_size++;
}

template<typename Type>
void List<Type>::push_front(const Type& data)
{
	if (head == nullptr)
	{
		head = new Node(data);
		tail = head;
	}
	else
	{
		head->pPrev = new Node(data, head);
		head = head->pPrev;
	}
	_size++;
}

template<typename Type>
void List<Type>::pop_back()
{
	if (head == nullptr)
		return;

	if (head == tail)
	{
		delete head;
		head = tail = nullptr;
	}
	else
	{
		tail = tail->pPrev;
		delete tail->pNext;
		tail->pNext = nullptr;
	}
	_size--;
}

template<typename Type>
void List<Type>::pop_front()
{
	if (head == nullptr)
		return;

	if (head == tail)
	{
		delete head;
		head = tail = nullptr;
	}
	else
	{
		head = head->pNext;
		delete head->pPrev;
		head->pPrev = nullptr;
	}
	_size--;
}

template<typename Type>
void List<Type>::clear()
{
	while (_size)
		pop_front();
}

template<typename Type>
void List<Type>::insertAt(const Type& data, int index)
{
	if (index < 0 || index > _size) throw std::out_of_range("Invalid index");

	if (!index)
		push_front(data);
	else if (index == _size)
		push_back(data);
	else
	{
		Node* need;
		if (index >= _size / 2)
		{
			need = tail;
			for (int i = 0; i < (_size - index); i++)
				need = need->pPrev;
			need->pNext = need->pNext->pPrev = new Node(data, need->pNext, need);
		}
		else
		{
			need = head;
			for (int i = 0; i < index - 1; i++)
				need = need->pNext;
			need->pNext = need->pNext->pPrev = new Node(data, need->pNext, need);
		}
		_size++;
	}	
}

template<typename Type>
void List<Type>::removeAt(int index)
{
	if (index < 0 || index >= _size) throw std::out_of_range("Invalid index");

	if (!index)
		pop_front();
	else if (index == _size - 1)
		pop_back();
	else
	{
		Node* need;
		if (index >= _size / 2)
		{
			need = tail;
			for (int i = 0; i < (_size - index); i++)
				need = need->pPrev;
			Node* toDelete = need->pNext;
			need->pNext = toDelete->pNext;
			need->pNext->pPrev = need;
			delete toDelete;
		}
		else
		{
			need = head;
			for (int i = 0; i < (index - 1); i++)
				need = need->pNext;
			Node* toDelete = need->pNext;
			need->pNext = toDelete->pNext;
			need->pNext->pPrev = need;
			delete toDelete;
		}
		_size--;
	}
}

template<typename Type>
Type& List<Type>::operator[](int index)
{
	if (index < 0 || index >= _size) throw std::out_of_range("Invalid index");

	Node* need;
	if (index >= _size / 2)
	{
		need = tail;
		for (int i = 0; i < (_size - index - 1); i++)
			need = need->pPrev;
	}
	else
	{
		need = head;
		for (int i = 0; i < index; i++)
			need = need->pNext;
	}

	return need->data;
}

template<typename Type>
const Type& List<Type>::operator[](int index) const
{
	if (index < 0 || index >= _size) throw std::out_of_range("Invalid index");

	Node* need;
	if (index >= _size / 2)
	{
		need = tail;
		for (int i = 0; i < (_size - index - 1); i++)
			need = need->pPrev;
	}
	else
	{
		need = head;
		for (int i = 0; i < index; i++)
			need = need->pNext;
	}

	return need->data;
}


#endif // !MY_LIST_H_INCLUDED_