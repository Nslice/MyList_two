#ifndef MY_LIST_H_INCLUDED_
#define MY_LIST_H_INCLUDED_

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
	int size;

	List(const List&) = delete;      //не точно
	List& operator=(const List&) = delete;
public:
	List();
	~List();

	int get_size() const { return size; }
	bool empty() const { return !size; }

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
	void removeAt(int index);
	Type& operator[](int index);
	const Type& operator[](int index) const;
};

template<typename Type>
List<Type>::List() : head(nullptr), tail(nullptr), size(0) {}

template<typename Type>
List<Type>::~List()
{
	clear();
}

template<typename Type>
Type& List<Type>::front()
{
	if (!size)
		throw std::exception("list iterator not deferencable");
	return head->data;
}
template<typename Type>
const Type& List<Type>::front() const
{
	if (!size)
		throw std::exception("list iterator not deferencable");
	return head->data;
}

template<typename Type>
Type& List<Type>::back()
{
	if (!size)
		throw std::exception("list iterator not deferencable");
	return tail->data;
}
template<typename Type>
const Type& List<Type>::back() const
{
	if (!size)
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
	size++;
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
	size++;
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
	size--;
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
	size--;
}

template<typename Type>
void List<Type>::clear()
{
	while (size)
		pop_front();
}

template<typename Type>
void List<Type>::insertAt(const Type& data, int index)
{
	if (index < 0 || index > size) throw std::out_of_range("Invalid index");

	if (!index)
		push_front(data);
	else if (index == size)
		push_back(data);
	else
	{
		Node* need;
		if (index >= size / 2)
		{
			need = tail;
			for (int i = 0; i < (size - index); i++)
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
		size++;
	}	
}

template<typename Type>
void List<Type>::removeAt(int index)
{
	if (index < 0 || index >= size) throw std::out_of_range("Invalid index");

	if (!index)
		pop_front();
	else if (index == size - 1)
		pop_back();
	else
	{
		Node* need;
		if (index >= size / 2)
		{
			need = tail;
			for (int i = 0; i < (size - index); i++)
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
		size--;
	}
}

template<typename Type>
Type& List<Type>::operator[](int index)
{
	if (index < 0 || index >= size) throw std::out_of_range("Invalid index");

	Node* need;
	if (index >= size / 2)
	{
		need = tail;
		for (int i = 0; i < (size - index - 1); i++)
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
	if (index < 0 || index >= size) throw std::out_of_range("Invalid index");

	Node* need;
	if (index >= size / 2)
	{
		need = tail;
		for (int i = 0; i < (size - index - 1); i++)
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