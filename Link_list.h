// �������� �.�.
#pragma once // ��������� � �++, ��� �������������� ������������� ��������� ������ � ���� �� ������������� �����
#include <iostream>
#include <stdexcept>

using namespace std;

/// ��������� ����� ���� ����������� ������
template <typename T>
class Node
{
public:
	T data; // ������� ������
	Node<T>* prev; // ���������� ����
	Node<T>* next; // ��������� ����

	/// ����������� ���� ������
	/// T data - ������� ������
	Node(T data)
	{
		this->data = data;
		this->next = this->prev = nullptr;
	}
};

/// ��������� ����� ���������� ������
template <typename T>
class DoubleList {
private:
	Node<T>* head; // ������ ���� ������
	Node<T>* tail; // ��������� ���� ������
	size_t Size; // ������ ������
public:

	/// ������� ����: ���� ���� ������������ ���� �� ��������� ���� ����������� ������� ������, ������ �����, 
	/// ����� ���� ���������� � ��������� ������: ����������, ����������� �����������, �������� ������������ ������������, 
	/// ����������� �����������, �������� ������������ ������������.
	
	/// ���������� �� ��������� (������ ������ � 0 ��������)
	DoubleList()
	{
		this->head = this->tail = nullptr;
		this->Size = 0;
	}

	/// ����������� �����������
	/// const DoubleList<T>& lst - ���������� ������
	DoubleList(const DoubleList<T>& lst)
	{
		Node<T>* curr = lst.head;
		while (curr)
		{
			PushBack(curr->data); // ��������� � �����
			curr = curr->next; //���������� �� ���������
		}
	}

	/// ����������� �����������
	/// (DoubleList<T>&& lst - ������������ ������
	/// noexcept : head(lst.head), tail(lst.tail), Size(lst.Size) - �����������
	DoubleList(DoubleList<T>&& lst) noexcept : head(lst.head), tail(lst.tail), Size(lst.Size)
	{
		lst.head = lst.tail = nullptr;
		lst.Size = 0;
	}

	/// �������� ������������ ������������
	/// const DoubleList<T>& lst - ���������� ������
	DoubleList<T>& operator =(const DoubleList<T>& lst)
	{
		if (this != &lst) // �������� �� ���������������
		{
			return DoubleList(lst);
		}
		return *this;
	}

	/// �������� ������������ ������������
	/// DoubleList<T>&& lst - ������������ ������
	DoubleList<T>& operator =(DoubleList<T>&& lst)
	{
		if (this != &lst) // �������� �� ���������������
		{
			return DoubleList(lst);
		}
		return *this;
	}

	/// ����������
	~DoubleList()
	{
		while (head != nullptr)
		{
			PopFront();
		}
	}

	/// ��������� ������� ������
	size_t GetSize() const
	{
		return Size;
	}

	/// ��������� ���� ������
	/// size_t i - ������ ���� ������
	Node<T>* GetAt(size_t i)
	{
		Node<T>* res = head;
		size_t n = 0;
		while (res && n < i)
		{
			res = res->next;
			n++;
		}
		return (n == i ? res : nullptr);
	}

	/// ��������� �������� � ���� ������
	/// ��������� ����������, ���� ������ �� ���������
	/// size_t i - ������ ���� ������
	T& At(size_t i)
	{
		Node<T>* res = GetAt(i);
		if (!res)
		{
			throw out_of_range("������ �� ��������� ������");
		}
		return res->data;
	}

	/// ���������� ��������� [] (��������� �������� ���� ������)
	/// size_t i - ������ ���� ������
	T& operator [](size_t i)
	{
		return At(i);
	}

	/// �������� ������������ ����
	/// Node<T>* node - ���� ������
	void Pop(Node<T>* node)
	{
		if (node == nullptr)
		{
			return;
		}
		if (node->prev != nullptr)
		{
			node->prev->next = node->next;
		}
		else
		{
			head = node->next;
		}
		if (node->next != nullptr)
		{
			node->next->prev = node->prev;
		}
		else
		{
			tail = node->prev;
		}
		delete node;
		Size--;
	}

	/// ���������� �������� � ������ ������
	/// const T& elem - �������, ������� ����� ��������
	void PushFront(const T& elem)
	{
		Node<T>* res = new Node<T>(elem);
		res->next = head;
		if (head != nullptr)
		{
			head->prev = res;
		}
		if (tail == nullptr)
		{
			tail = res;
		}
		head = res;
		Size++;
	}

	/// ���������� �������� � ����� ������
	/// const T& elem - �������, ������� ����� ��������
	void PushBack(const T& elem)
	{
		Node<T>* res = new Node<T>(elem);
		res->prev = tail;
		if (tail != nullptr)
		{
			tail->next = res;
		}
		if (head == nullptr)
		{
			head = res;
		}
		tail = res;
		Size++;
	}

	/// ������� �������� �� �������
	/// ��������� ����������, ���� ������ �� ���������
	/// const T& elem - �������, ������� ����� ��������, size_t i - ������
	void PushAt(const T& elem, size_t i)
	{
		if (i > Size)
		{
			throw out_of_range("������ �� ��������� ������");
		}
		if (i == 0)
		{
			PushFront(elem);
		}
		else if (i == Size)
		{
			PushBack(elem);
		}
		else
		{
			Node<T>* curr = GetAt(i);
			Node<T>* res = new Node<T>(elem);
			Node<T>* prev = curr->prev;
			res->next = curr;
			res->prev = prev;
			prev->next = res;
			curr->prev = res;
			Size++;
		}
	}

	/// �������� �������� �� ������ ������
	/// ��������� ����������, ���� ������ ������
	void PopFront()
	{
		if (head == nullptr)
		{
			throw underflow_error("������ ������");
		}
		Node<T>* res = head->next;
		if (res != nullptr)
		{
			res->prev = nullptr;
		}
		else
		{
			tail = nullptr;
		}
		delete head;
		head = res;
		Size--;
	}

	/// �������� �������� �� ����� ������
	/// ��������� ����������, ���� ������ ������
	void PopBack()
	{
		if (tail == nullptr)
		{
			throw underflow_error("������ ������");
		}
		Node<T>* res = tail->prev;
		if (res != nullptr)
		{
			res->next = nullptr;
		}
		else
		{
			head = nullptr;
		}
		delete tail;
		tail = res;
		Size--;
	}

	/// �������� ���� ������ �� �������
	/// ��������� ����������, ���� ������ �� ���������
	/// size_t i - ������
	void PopAt(size_t i)
	{
		if (i >= Size)
		{
			throw out_of_range("������ �� ��������� ������");
		}
		Pop(GetAt(i));
	}

	/// ������� ������
	void Clear()
	{
		Node<T>* curr = head;
		while (curr != nullptr)
		{
			Node<T>* next = curr->next;
			delete curr;
			curr = next;
		}
		head = tail = nullptr;
		Size = 0;
	}
};

void test();