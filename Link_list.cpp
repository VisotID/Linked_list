// Высоцкая И.Д.
#include <iostream>
#include "Link_list.h"
#include <cassert>


void test()
{
	//тест конструктора по умолчанию
	DoubleList<int> lst1; // пустой
	assert(lst1.GetSize() == 0);

	//тест вставки в конец (0 1 2)
	DoubleList<int> lst; // из нескольких элементов
	for (size_t i = 0; i < 3; i++)
	{
		lst.PushBack(i);
		assert(lst.GetSize() == i + 1);
		assert(lst[i] == i);
	}

	//тест итератора перехода на следующий элемент и итератора разыменования
	auto it = lst.begin(); // несколько элементов
	auto end = lst.end();
	assert(*it == 0);
	++it;
	++it;
	assert(*it == 2);

	auto it1 = lst1.begin(); // пустой
	auto end1 = lst1.end();
	assert(!(it1 != end1));
	++it1;
	assert(!(it1 != end1));


	DoubleList<int> lst2; // один элемент
	lst2.PushBack(7);

	auto it3 = lst2.begin(); // один элемент
	auto end3 = lst2.end();
	assert(*it3 == 7);
	++it3;
	assert(!(it3 != end3));

	// тест итератора сравнения
	assert(!(lst1.begin() != lst1.end())); // пустой
	auto it4 = lst.begin(); // несколько элементов
	++it4; // указывает на второй элемент
	auto it5 = lst.begin(); // указывает на первый элемент
	assert(it4 != it5); // не равны

	//тест конструктора копирования
	DoubleList<int> lstc(lst);
	assert(lstc.GetSize() == lst.GetSize());
	for (size_t i = 0; i < lstc.GetSize(); i++)
	{
		assert(lstc[i] == lst[i]);
	}

	//тест оператора присваивания копированием
	DoubleList<int> lstoc = lstc;
	assert(lstoc.GetSize() == lstc.GetSize());
	for (size_t i = 0; i < lstoc.GetSize(); i++)
	{
		assert(lstoc[i] == lstc[i]);
	}

	//тест конструктора перемещения
	DoubleList<int> lstm(move(lstc));
	assert(lstc.GetSize() == 0);
	assert(lstm.GetSize() == 3);
	for (size_t i = 0; i < lstm.GetSize(); i++)
	{
		assert(lstm[i] == i);
	}

	//тест оператора присваивания перемещением
	DoubleList<int> lstom = move(lstm);
	assert(lstm.GetSize() == 0);
	assert(lstom.GetSize() == 3);
	for (size_t i = 0; i < lstom.GetSize(); i++)
	{
		assert(lstom[i] == i);
	}

	//тест получения узла списка по индексу
	for (size_t i = 0; i < lstom.GetSize(); i++)
	{
		assert(lstom.GetAt(i)->data == i);
	}

	//тест получения элемента в узле списка по индексу
	for (size_t i = 0; i < lstom.GetSize(); i++)
	{
		assert(lstom.At(i) == i);
	}

	//тест вставки в начало (2 1 0)
	DoubleList<int> lstfpu;
	for (size_t i = 0; i < 3; i++)
	{
		lstfpu.PushFront(i);
		assert(lstfpu.GetSize() == i + 1);
		assert(lstfpu[0] == i);
	}

	//тест вставки по индексу
	lstfpu.PushAt(6, 3); // вставка в конец (2 1 0 6)
	assert(lstfpu.GetSize() == 4);
	assert(lstfpu[3] == 6);

	lstfpu.PushAt(9, 0); // вставка в начало (9 2 1 0 6)
	assert(lstfpu.GetSize() == 5);
	assert(lstfpu[0] == 9);

	lstfpu.PushAt(10, 2); // вставка в середину (9 2 10 1 0 6)
	assert(lstfpu.GetSize() == 6);
	assert(lstfpu[2] == 10);

	//тест удаления узла списка из начала
	DoubleList<int> voidlst; // пустой список
	assert(voidlst.GetSize() == 0);
	lstfpu.PopFront(); // (2 10 1 0 6)
	assert(lstfpu.GetSize() == 5);
	assert(lstfpu[0] == 2);
	voidlst.PushBack(5); // (5)
	voidlst.PopFront(); // удаление из списка с 1 элементом
	assert(voidlst.GetSize() == 0);

	//тест удаления узла списка из конца
	voidlst.PushBack(5); // (5)
	voidlst.PopBack(); // удаление из списка с 1 элементом
	assert(voidlst.GetSize() == 0);
	lstfpu.PopBack(); // (2 10 1 0)
	assert(lstfpu.GetSize() == 4);
	assert(lstfpu[3] == 0);

	//тест удаления узла списка по индексу
	voidlst.PushBack(5); // (5)
	voidlst.PopAt(0); // удаление из списка с 1 элементом
	assert(voidlst.GetSize() == 0);

	lstfpu.PopAt(0); // удаление из начала (10 1 0)
	assert(lstfpu.GetSize() == 3);
	assert(lstfpu[0] == 10);
	lstfpu.PopAt(2); // удаление из конца (10 1)
	assert(lstfpu.GetSize() == 2);
	assert(lstfpu[1] == 1);

	//тест очистки списка
	voidlst.Clear(); // очистка пустого списка
	assert(voidlst.GetSize() == 0);
	lstfpu.Clear(); // очистка списка
	assert(lstfpu.GetSize() == 0);

	// тесты на проверку бросания исключений
	DoubleList<int> lstiskl; // пустой список

	// тест на проверку бросания исключений для удаления элемента из начала пустого списка
	// в методах бросается исключение с помощью оператора throw, в коде ниже в секции try выполняется код, до тех пор пока 
	// не будет брошено исключение, тогда происходит переход в секцию catch, код в секции try далее не выполняется.
	// в данных тестах производится проверка на бросание исключения, если оно не будет брошено, программа аварийно завершится благодаря 
	// assert(false)
	try
	{
		lstiskl.PopFront();
		assert(false);
	}
	catch (const underflow_error&)
	{

	}

	// тест на проверку бросания исключений для удаления элемента из конца пустого списка
	try
	{
		lstiskl.PopBack();
		assert(false);
	}
	catch (const underflow_error&)
	{

	}

	// тест на проверку бросания исключений для удаления по индексу из пустого списка
	try
	{
		lstiskl.PopAt(4);
		assert(false);
	}
	catch (const out_of_range&)
	{

	}

	// тест на проверку бросания исключений для оператора []
	try
	{
		lstiskl[6];
		assert(false);
	}
	catch (const out_of_range&)
	{

	}

	// тест на проверку бросания исключений для вставки элемента по индексу в индекс за пределами списка
	try
	{
		lstiskl.PushAt(1,4);
		assert(false);
	}
	catch (const out_of_range&)
	{

	}
}