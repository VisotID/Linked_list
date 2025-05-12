// �������� �.�.
#include <iostream>
#include "Link_list.h"
#include <cassert>

void test()
{
	//���� ������������ �� ���������
	DoubleList<int> lst;
	assert(lst.GetSize() == 0);

	//���� ������� � ����� (0 1 2)
	for (size_t i = 0; i < 3; i++)
	{
		lst.PushBack(i);
		assert(lst.GetSize() == i + 1);
		assert(lst[i] == i);
	}

	//���� ������������ �����������
	DoubleList<int> lstc(lst);
	assert(lstc.GetSize() == lst.GetSize());
	for (size_t i = 0; i < lstc.GetSize(); i++)
	{
		assert(lstc[i] == lst[i]);
	}

	//���� ��������� ������������ ������������
	DoubleList<int> lstoc = lstc;
	assert(lstoc.GetSize() == lstc.GetSize());
	for (size_t i = 0; i < lstoc.GetSize(); i++)
	{
		assert(lstoc[i] == lstc[i]);
	}

	//���� ������������ �����������
	DoubleList<int> lstm(move(lstc));
	assert(lstc.GetSize() == 0);
	assert(lstm.GetSize() == 3);
	for (size_t i = 0; i < lstm.GetSize(); i++)
	{
		assert(lstm[i] == i);
	}

	//���� ��������� ������������ ������������
	DoubleList<int> lstom = move(lstm);
	assert(lstm.GetSize() == 0);
	assert(lstom.GetSize() == 3);
	for (size_t i = 0; i < lstom.GetSize(); i++)
	{
		assert(lstom[i] == i);
	}

	//���� ��������� ���� ������ �� �������
	for (size_t i = 0; i < lstom.GetSize(); i++)
	{
		assert(lstom.GetAt(i)->data == i);
	}

	//���� ��������� �������� � ���� ������ �� �������
	for (size_t i = 0; i < lstom.GetSize(); i++)
	{
		assert(lstom.At(i) == i);
	}

	//���� ������� � ������ (2 1 0)
	DoubleList<int> lstfpu;
	for (size_t i = 0; i < 3; i++)
	{
		lstfpu.PushFront(i);
		assert(lstfpu.GetSize() == i + 1);
		assert(lstfpu[0] == i);
	}

	//���� ������� �� �������
	lstfpu.PushAt(6, 3); // ������� � ����� (2 1 0 6)
	assert(lstfpu.GetSize() == 4);
	assert(lstfpu[3] == 6);

	lstfpu.PushAt(9, 0); // ������� � ������ (9 2 1 0 6)
	assert(lstfpu.GetSize() == 5);
	assert(lstfpu[0] == 9);

	lstfpu.PushAt(10, 2); // ������� � �������� (9 2 10 1 0 6)
	assert(lstfpu.GetSize() == 6);
	assert(lstfpu[2] == 10);

	//���� �������� ���� ������ �� ������
	DoubleList<int> voidlst; // ������ ������
	assert(voidlst.GetSize() == 0);
	lstfpu.PopFront(); // (2 10 1 0 6)
	assert(lstfpu.GetSize() == 5);
	assert(lstfpu[0] == 2);
	voidlst.PushBack(5); // (5)
	voidlst.PopFront(); // �������� �� ������ � 1 ���������
	assert(voidlst.GetSize() == 0);

	//���� �������� ���� ������ �� �����
	voidlst.PushBack(5); // (5)
	voidlst.PopBack(); // �������� �� ������ � 1 ���������
	assert(voidlst.GetSize() == 0);
	lstfpu.PopBack(); // (2 10 1 0)
	assert(lstfpu.GetSize() == 4);
	assert(lstfpu[3] == 0);

	//���� �������� ���� ������ �� �������
	voidlst.PushBack(5); // (5)
	voidlst.PopAt(0); // �������� �� ������ � 1 ���������
	assert(voidlst.GetSize() == 0);

	lstfpu.PopAt(0); // �������� �� ������ (10 1 0)
	assert(lstfpu.GetSize() == 3);
	assert(lstfpu[0] == 10);
	lstfpu.PopAt(2); // �������� �� ����� (10 1)
	assert(lstfpu.GetSize() == 2);
	assert(lstfpu[1] == 1);

	//���� ������� ������
	voidlst.Clear(); // ������� ������� ������
	assert(voidlst.GetSize() == 0);
	lstfpu.Clear(); // ������� ������
	assert(lstfpu.GetSize() == 0);
}