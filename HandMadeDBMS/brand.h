#pragma once

typedef struct BRAND
{
	int BR_ID;
	int CT_ID;
	char BR_NAME[25];
} BRAND;

typedef struct BRECORD
{
	int active;
	int next;
	BRAND record;
} BRECORD;

BRECORD Get_S(int m, int s);
void Del_S(int m, int s);
void Update_S(int m, int s);
void Insert_S(int m, int s);
void Clear_S();
int Calc_S();

void ReadSlave(BRECORD* crds);
void WriteSlave(BRECORD* crds);
void IncSlaveRecords(int q);