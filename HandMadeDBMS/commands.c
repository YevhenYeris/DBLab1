#pragma once
#include "commands.h"
#include "stdio.h"
#include "structs.h"

#define CAPACITY 100
#define GCA 36

char Cfl[] = "C.fl";
char Bfl[] = "B.fl";
char Cind[] = "C.ind";
char Bind[] = "B.ind";

INDEXEDRECORD Indeces[CAPACITY];

void Get_M(int m)
{
	FILE* fl = fopen(Cind, "r");
	INDEXEDRECORD rec = { .id = 0, .address = 0 };
	int pos = 0;

	/*while (!feof(fl))
	{
		INDEXEDRECORD tempRec = { .id = 0, .address = 0 };
		fread(&tempRec, sizeof(INDEXEDRECORD), 1, fl);

		if (tempRec.id == m)
		{
			rec = tempRec;
			break;
		}
	}
	fclose(fl);*/

	for (int i = 0; i < CAPACITY; ++i)
	{
		if (Indeces[i].id == m)
		{
			rec = Indeces[i];
			break;
		}
	}

	if (rec.id != 0)
	{
		pos = rec.address;

		fl = fopen(Cfl, "r");
		fseek(fl, pos, SEEK_SET);
		CRECORD crd = { .active = 0, {.CT_ID = 0, .CT_NAME = 0} };
		fread(&crd, sizeof(CRECORD), 1, fl);
		fclose(fl);

		if (crd.active == 0)
		{
			printf("CT_ID = %d\nCT_NAME = %s\n", crd.record.CT_ID, crd.record.CT_NAME);
		}
	}
}

void Get_S(int m, int s)
{

}

void Del_M(int m)
{
	FILE* fl = fopen(Cind, "r");
	INDEXEDRECORD rec = { .id = 0, .address = 0 };
	int pos = 0;

	while (!feof(fl))
	{
		INDEXEDRECORD tempRec = { .id = 0, .address = 0 };
		fread(&tempRec, sizeof(INDEXEDRECORD), 1, fl);

		if (tempRec.id == m)
		{
			rec = tempRec;
			break;
		}
	}
	fclose(fl);

	if (rec.id != 0)
	{
		pos = rec.address;

		fl = fopen(Cfl, "r");
		fseek(fl, pos, SEEK_SET);
		CRECORD crd = { .active = 0, {.CT_ID = 0, .CT_NAME = 0} };
		fread(&crd, sizeof(CRECORD), 1, fl);
		crd.active = 1;
		fclose(fl);

		fl = fopen(Cfl, "w");
		fseek(fl, pos, SEEK_SET);
		fwrite(&crd, sizeof(CRECORD), 1, fl);
		fclose(fl);

		if (crd.active == 1)
		{
			printf("CT_ID = %d\nCT_NAME = %s\ndeleted\n", crd.record.CT_ID, crd.record.CT_NAME);
		}
	}

	AddGarbage(pos);
}

void Del_S(int m, int s)
{

}

void Update_M(int m)
{

}

void Update_S(int m, int s)
{

}

void Insert_M()
{
	COUNTRY cntr = {.CT_ID = 0, .CT_NAME = 0};
	scanf("%d", &cntr.CT_ID);
	scanf("%s", &cntr.CT_NAME);

	CRECORD crec = { .active = 0, .record = cntr };

	FILE* fl = fopen(Cfl, "r");
	fseek(fl, 0L, SEEK_END);
	int pos = ftell(fl);
	fclose(fl);

	fl = fopen(Cfl, "a");
	fwrite(&crec, sizeof(CRECORD), 1, fl);
	fclose(fl);

	INDEXEDRECORD indr = { .id = cntr.CT_ID, .address = pos };
	/*fl = fopen(Cind, "a");
	fwrite(&indr, sizeof(INDEXEDRECORD), 1, fl);
	fclose(fl);*/

	//SortInd();
	//int a = 0;
}

void Insert_S(int m, int s)
{

}

void Clear(INDEXEDRECORD arr[100])
{
	INDEXEDRECORD rec = { .id = 0, .address = 0 };
	for (int i = 0; i < 100; ++i)
	{
		arr[i] = rec;
	}
}

void SortInd()
{
	INDEXEDRECORD records[100];
	Clear(records);
	INDEXEDRECORD rec = { .id = 0, .address = 0 };

	FILE* fl = fopen(Cind, "r");
	fread(records, sizeof(INDEXEDRECORD), 100, fl);
	Quicksort(records, 0, 99);
	fclose(fl);

	fl = fopen(Cind, "w");
	fwrite(records, sizeof(INDEXEDRECORD), 100, fl);
	fclose(fl);
}

void Quicksort(INDEXEDRECORD number[100], int first, int last)
{
	int i, j, pivot;
	INDEXEDRECORD temp;

	if (first < last) {
		pivot = first;
		i = first;
		j = last;

		while (i < j) {
			while (number[i].id <= number[pivot].id && i < last)
				i++;
			while (number[j].id > number[pivot].id)
				j--;
			if (i < j) {
				temp = number[i];
				number[i] = number[j];
				number[j] = temp;
			}
		}

		temp = number[pivot];
		number[pivot] = number[j];
		number[j] = temp;
		Quicksort(number, first, j - 1);
		Quicksort(number, j + 1, last);

	}
}

int Find(INDEXEDRECORD arr[100], int N, int targ)
{
	/*int mid = N / 2;

	if (arr[mid].id == targ)
		return arr[mid].address;
	
	if (arr[mid].id > targ)
	{
		return Find(arr, mid, targ);
	}

	if (arr[mid].id < targ)
	{
		INDEXEDRECORD temp[100];
		int ti = 0;
		for (int i = mid + 1; i < 100; ++i)
		{
			temp[ti] = arr[i];
			++ti;
		}
		return Find(temp, 100, targ);
	}*/

	int first = 0;
	int last = N - 1;
	int middle = (first + last) / 2;

	while (first <= last) {
		if (arr[middle].id < targ)
			first = middle + 1;
		else if (arr[middle].id == targ) {
			return arr[middle].id;
		}
		else
			last = middle - 1;

		middle = (first + last) / 2;
	}
	if (first > last)
		printf("Not found! %d isn't present in the list.\n", targ);
}

void AddGarbage(int pos)
{
	int bin = 0;
	FILE* fl = fopen(Cfl, "r");
	for (int i = 0; i < 36; ++i)
	{
		int temp = 0;
		fseek(fl, i, SEEK_SET);
		fread(&temp, sizeof(int), 1, fl);
		if (temp == 0)
		{
			fclose(fl);
			bin = temp;
			break;
		}
	}

	if (bin != 0)
	{
		fl = fopen(Cfl, "w");
		fseek(fl, bin, SEEK_SET);
		fwrite(&pos, sizeof(int), 1, fl);
		fclose(fl);
	}
}

void FillFiles()
{
	FILE* fl = fopen(Cfl, "w");
	short garbage[36] = { 0, 0, 0, 0, 0, 0, 0, 0, 0,
						 0, 0, 0, 0, 0, 0, 0, 0, 0,
						 0, 0, 0, 0, 0, 0, 0, 0, 0,
						 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	fwrite(garbage, sizeof(short), 36, fl);
	fclose(fl);

	fl = fopen(Cind, "w");
	fclose(fl);

	fl = fopen(Bfl, "w");
	fwrite(garbage, sizeof(short), 36, fl);
	fclose(fl);

	fl = fopen(Bind, "w");
	fclose(fl);
}

void Init()
{
	FillFiles();

	FILE* fl = fopen(Cind, "r");
	fread(Indeces, sizeof(INDEXEDRECORD), CAPACITY, fl);
	fclose(fl);
}*/