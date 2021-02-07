#include "brand.h"
#include "country.h"

#define CAPACITY 100
#define GCA 36

char Bfl[] = "B.fl";
char Bind[] = "B.ind";

MINDEX IndecesS[CAPACITY];   

int slavesCount = 0;

BRECORD Get_S(int m, int s)
{
	BRECORD brd = { .active = 1, .record = {.BR_ID = 0, .BR_NAME = 0, .CT_ID = 0}, .next = -1 };

	CRECORD crd = Get_M(m);
	int pos = crd.relpos;
	int num = crd.relnum;

	FILE* fl = fopen(Bfl, "r");
	fseek(fl, pos * sizeof(BRECORD) + sizeof(int), SEEK_SET);

	for (int i = 0; i < num; ++i)
	{
		fread(&brd, sizeof(BRECORD), 1, fl);
		if (brd.record.BR_ID == s)
		{
			return brd;
		}
	}

	BRECORD brde = { .active = 1, .record = {.BR_ID = 0, .BR_NAME = 0, .CT_ID = 0}, .next = -1 };
	return brde;
}

int Calc_S(int m)
{
	int res = 0;
	BRECORD brds[CAPACITY];
	ReadSlave(brds);

	if (m == -1)
	{
		for (int i = 0; i < slavesCount; ++i)
		{
			if (brds[i].active)
				++res;
		}
	}
	else
	{
		CRECORD crd = Get_M(m);
		int pos = crd.relpos;
		int num = crd.relnum;

		if (num > 0)
		{
			do
			{
				BRECORD brd = brds[pos];
				if (brd.active)
					++res;
				pos = brds[pos].next;
			} while (pos > -1);
		}
	}
	return res;
}

void Del_S(int m, int s)
{
	BRECORD brds[CAPACITY];
	ReadSlave(brds);

	CRECORD crd = Get_M(m);
	int pos = crd.relpos;
	int num = crd.relnum;

	BRECORD tempbrd = brds[pos];
	for (int i = 0; i < num; ++i)
		// Find seeked record (speeded up by using .next)
	{
		if (tempbrd.active && tempbrd.record.BR_ID == s)
			break;
		pos = tempbrd.next;
		tempbrd = brds[tempbrd.next];
	}

	brds[pos].active = 0;
	
	for (int i = 0; i < CAPACITY; ++i)
	{
		if (brds[i].active && brds[i].next == pos)
		{
			brds[i].next = brds[pos].next;
		}
	}

	if (crd.relpos == pos)
		DecRel(m, brds[pos].next);
	else
		DecRel(m, pos);

	WriteSlave(brds);
}

void Update_S(int m, int s)
{
	// Get related country
	CRECORD crd = Get_M(m);
	int pos = crd.relpos;
	int num = crd.relnum;

	// Read all brands
	BRECORD brds[CAPACITY];
	ReadSlave(brds);

	// Find seeked record (speeded up by using .next)
	BRECORD tempbrd = brds[pos];
	for (int i = 0; i < num; ++i)
	{
		if (tempbrd.active && tempbrd.record.BR_ID == s)
			break;
		pos = tempbrd.next;
		tempbrd = brds[tempbrd.next];
	}

	scanf("%s", &brds[pos].record.BR_NAME);

	// Update changes
	WriteSlave(brds);
}

void Insert_S(int m, int s)
{
	BRAND br = { .BR_ID = s, .BR_NAME = 0, .CT_ID = m };
	scanf("%s", &br.BR_NAME);

	BRECORD brd = { .active = 1, .record = br, .next = -1 };

	// Add brand to slave file
	FILE* fl = fopen(Bfl, "a");
	fwrite(&brd, sizeof(BRECORD), 1, fl);
	// Index of the new brand record
	int newPos = (ftell(fl) - sizeof(int)) / sizeof(BRECORD) - 1;
	fclose(fl);

	// Get the related country record
	CRECORD crd = Get_M(m);
	int Pos = crd.relpos;
	int pos = Pos;
	int num = crd.relnum;

	IncSlaveRecords(1);

	// Read records from the slave file
	BRECORD brds[CAPACITY];
	ReadSlave(brds);

	if (num > -1)
		// Find the index of the next brand record
	{
		BRECORD tempb = brds[pos];

		for (int i = 0; i < num; ++i)
		{
			if (i == num - 1)
				brds[pos].next = newPos;

			pos = tempb.next;
			tempb = brds[pos];
		}
	}

	// Increase the number of records and update the slave file
	WriteSlave(brds);

	if (num == 0)
		IncRel(m, newPos);
	else
		IncRel(m, Pos);
}

void Clear_S()
{
	slavesCount = 0;
	FILE* fl = fopen(Bfl, "w");
	fwrite(&slavesCount, sizeof(int), 1, fl);
	fclose(fl);

	fl = fopen(Bind, "w");
	fclose(fl);
}

void ReadSlave(BRECORD* brds)
{
	FILE* fl = fopen(Bfl, "r");
	fread(&slavesCount, sizeof(int), 1, fl);
	fread(brds, sizeof(BRECORD), CAPACITY, fl);
	fclose(fl);
}

void WriteSlave(BRECORD* brds)
{
	FILE* fl = fopen(Bfl, "w");
	fwrite(&slavesCount, sizeof(int), 1, fl);
	fclose(fl);

	fl = fopen(Bfl, "a");
	fwrite(brds, sizeof(BRECORD), slavesCount, fl);
	fclose(fl);
}

void IncSlaveRecords(int q)
{
	BRECORD brds[CAPACITY];
	ReadSlave(brds);
	slavesCount += q;
	WriteSlave(brds);
}