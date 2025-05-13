// Высоцкая И.Д.
#pragma once // директива в С++, для предотвращения многократного включения одного и того же заголовочного файла
#include <iostream>
#include <stdexcept>

using namespace std;

/// Шаблонный класс узел двусвязного списка
template <typename T>
class Node
{
public:
	T data; // элемент списка
	Node<T>* prev; // предыдущий узел
	Node<T>* next; // следующий узел

	/// Конструктор узла списка
	/// T data - элемент списка
	Node(T data)
	{
		this->data = data;
		this->next = this->prev = nullptr;
	}
};

/// Шаблонный класс двусвязный список
template <typename T>
class DoubleList {
private:
	Node<T>* head; // первый узел списка
	Node<T>* tail; // последний узел списка
	size_t Size; // размер списка
public:

	/// Правило пяти: если явно определяется один из следующих пяти специальных методов класса, скорее всего, 
	/// нужно явно определить и остальные четыре: деструктор, конструктор копирования, оператор присваивания копированием, 
	/// конструктор перемещения, оператор присваивания перемещением.
	
	/// Коструктор по умолчанию (пустой список с 0 размером)
	DoubleList()
	{
		this->head = this->tail = nullptr;
		this->Size = 0;
	}

	/// Конструктор копирования
	/// const DoubleList<T>& lst - копируемый список
	DoubleList(const DoubleList<T>& lst)
	{
		Node<T>* curr = lst.head;
		while (curr)
		{
			PushBack(curr->data); // вставляем в конец
			curr = curr->next; //ипереходим на следующий
		}
	}

	/// Конструктор перемещения
	/// (DoubleList<T>&& lst - перемещаемый список
	/// noexcept : head(lst.head), tail(lst.tail), Size(lst.Size) - перемещение
	DoubleList(DoubleList<T>&& lst) noexcept : head(lst.head), tail(lst.tail), Size(lst.Size)
	{
		lst.head = lst.tail = nullptr;
		lst.Size = 0;
	}

	/// Оператор присваивания копированием
	/// const DoubleList<T>& lst - копируемый список
	DoubleList<T>& operator =(const DoubleList<T>& lst)
	{
		if (this != &lst) // проверка на самокопирование
		{
			return DoubleList(lst);
		}
		return *this;
	}

	/// Оператор присваивания перемещением
	/// DoubleList<T>&& lst - перемещаемый список
	DoubleList<T>& operator =(DoubleList<T>&& lst)
	{
		if (this != &lst) // проверка на самокопирование
		{
			return DoubleList(lst);
		}
		return *this;
	}

	/// Деструктор
	~DoubleList()
	{
		while (head != nullptr)
		{
			PopFront();
		}
	}

	/// Получение размера списка
	size_t GetSize() const
	{
		return Size;
	}

	/// Получение узла списка
	/// size_t i - индекс узла списка
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

	/// Получение элемента в узле списка
	/// Бросается исключение, если индекс за пределами
	/// size_t i - индекс узла списка
	T& At(size_t i)
	{
		Node<T>* res = GetAt(i);
		if (!res)
		{
			throw out_of_range("Индекс за пределами списка");
		}
		return res->data;
	}

	/// Перегрузка оператора [] (получение элемента узла списка)
	/// size_t i - индекс узла списка
	T& operator [](size_t i)
	{
		return At(i);
	}

	/// Удаление определённого узла
	/// Node<T>* node - узел списка
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

	/// Добавление элемента в начало списка
	/// const T& elem - элемент, который нужно вставить
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

	/// Добавление элемента в конец списка
	/// const T& elem - элемент, который нужно вставить
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

	/// Вставка элемента по индексу
	/// Бросается исключение, если индекс за пределами
	/// const T& elem - элемент, который нужно вставить, size_t i - индекс
	void PushAt(const T& elem, size_t i)
	{
		if (i > Size)
		{
			throw out_of_range("Индекс за пределами списка");
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

	/// Удаление элемента из начала списка
	/// Бросается исключение, если список пустой
	void PopFront()
	{
		if (head == nullptr)
		{
			throw underflow_error("Пустой список");
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

	/// Удаление элемента из конца списка
	/// Бросается исключение, если список пустой
	void PopBack()
	{
		if (tail == nullptr)
		{
			throw underflow_error("Пустой список");
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

	/// Удаление узла списка по индексу
	/// Бросается исключение, если индекс за пределами
	/// size_t i - индекс
	void PopAt(size_t i)
	{
		if (i >= Size)
		{
			throw out_of_range("Индекс за пределами списка");
		}
		Pop(GetAt(i));
	}

	/// Очистка списка
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