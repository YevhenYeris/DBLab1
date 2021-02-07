#pragma once
#include "stdio.h"

typedef struct COUNTRY
{
	int CT_ID;
	char CT_NAME[3];
} COUNTRY;

typedef struct CRECORD
{
	int relpos;
	int relnum;
	COUNTRY record;
} CRECORD;

typedef struct MINDEX
{
	int active;
	int id;
	int address;
} MINDEX;

void Quicksort(MINDEX number[100], int first, int last);
int Find(MINDEX arr[100], int N, int targ);
void AddGarbage(int pos);
void InitMaster();
CRECORD Get_M(int m);
void Del_M(int m);
void Update_M(int m);
void Insert_M();
void Clear_M();
int Calc_M();
void IncRel(int m, int pos);
void DecRel(int m, int pos);
void AlterRelPos(int m, int pos);

void ReadMaster(CRECORD* crds);
void WriteMaster(CRECORD* crds);
void IncMasterRecords(int q);
int FindPosition(int ind);