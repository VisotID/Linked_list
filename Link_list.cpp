// Высоцкая И.Д.
#include <iostream>
#include "Link_list.h"
#include <cassert>

void test()
{
	//тест конструктора по умолчанию
	DoubleList<int> lst;
	assert(lst.GetSize() == 0);

	//тест вставки в конец (0 1 2)
	for (size_t i = 0; i < 3; i++)
	{
		lst.PushBack(i);
		assert(lst.GetSize() == i + 1);
		assert(lst[i] == i);
	}

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
}