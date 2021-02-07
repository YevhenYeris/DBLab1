#include "country.h"
#include "brand.h"

#define CAPACITY 100
#define GCA 36

int mastersCount = 0;

char Cfl[] = "C.fl";
char Cind[] = "C.ind";
char Cgb[] = "C.gb";

MINDEX IndecesM[CAPACITY];

CRECORD Get_M(int m)
{
	int pos = FindPosition(m);
	CRECORD crd = { .relpos = 0, .relnum = 0, {.CT_ID =-1, .CT_NAME = 0} };

	if (pos > -1)
		//If found
	{
		FILE* fl = fopen(Cfl, "r");
		fseek(fl, pos, SEEK_SET);
		fread(&crd, sizeof(CRECORD), 1, fl);
		fclose(fl);
	}

	return crd;
}

int Calc_M()
{
	int res = 0;

	for (int i = 0; i < mastersCount; ++i)
	{
		if (IndecesM[i].active)
			++res;
	}
	return res;
}

void Del_M(int m)
{
	CRECORD crd = Get_M(m);
	int pos = crd.relpos;
	int num = crd.relnum;

	BRECORD brds[CAPACITY];
	ReadSlave(brds);

	for (int i = 0; i < num; ++i)
		// Find seeked record (speeded up by using .next)
	{
		BRECORD tempbrd = brds[pos];
		Del_S(m, tempbrd.record.BR_ID);
		pos = tempbrd.next;
		tempbrd = brds[tempbrd.next];
	}
}

void Update_M(int m)
{
	int pos = FindPosition(m);

	// Read record
	FILE* fl = fopen(Cfl, "r");
	fseek(fl, pos, SEEK_SET);
	CRECORD crd = { .relpos = 0, .relnum = 0, {.CT_ID = 0, .CT_NAME = 0} };
	fread(&crd, sizeof(CRECORD), 1, fl);
	fclose(fl);

	// Update record
	COUNTRY cntr = { .CT_ID = crd.record.CT_ID, .CT_NAME = 0 };
	scanf("%s", &cntr.CT_NAME);
	crd.record = cntr;

	// Alter array
	CRECORD crds[CAPACITY];
	ReadMaster(crds);
	crds[(FindPosition(m) - sizeof(int)) / sizeof(CRECORD)] = crd;

	// Alter master file
	WriteMaster(crds);
}

void IncRel(int m, int pos)
{
	CRECORD tcrd = Get_M(m);
	CRECORD crd = { .relnum = tcrd.relnum + 1, .relpos = pos, .record = tcrd.record };

	int cpos = (FindPosition(m) - sizeof(int)) / sizeof(CRECORD);

	CRECORD crds[CAPACITY];
	ReadMaster(crds);

	crds[cpos] = crd;

	WriteMaster(crds);
}

void DecRel(int m, int pos)
{
	CRECORD tcrd = Get_M(m);
	CRECORD crd = { .relnum = tcrd.relnum - 1, .relpos = pos, .record = tcrd.record };

	int cpos = (FindPosition(m) - sizeof(int)) / sizeof(CRECORD);

	CRECORD crds[CAPACITY];
	ReadMaster(crds);

	crds[cpos] = crd;

	WriteMaster(crds);
}

void AlterRelPos(int m, int pos)
{

}

void Insert_M()
{
	COUNTRY cntr = { .CT_ID = 0, .CT_NAME = 0 };
	scanf("%d", &cntr.CT_ID);
	scanf("%s", &cntr.CT_NAME);

	CRECORD crec = { .record = cntr };

	// Get position
	FILE* fl = fopen(Cfl, "r");
	fseek(fl, 0L, SEEK_END);
	int pos = (ftell(fl) - sizeof(int)) / sizeof(CRECORD);
	fclose(fl);

	fl = fopen(Cfl, "a");
	fwrite(&crec, sizeof(CRECORD), 1, fl);
	fclose(fl);

	MINDEX ind = { .id = cntr.CT_ID, .address = pos, .active = 1 };
	for (int i = 0; i < CAPACITY; ++i)
	{
		if (!IndecesM[i].active)
		{
			IndecesM[i] = ind;
			break;
		}
	}
	IncMasterRecords(1);
}

void Clear_M()
{
	mastersCount = 0;
	FILE* fl = fopen(Cfl, "w");
	fwrite(&mastersCount, sizeof(int), 1, fl);
	fclose(fl);

	fl = fopen(Cind, "w");
	fclose(fl);

	fl = fopen(Cgb, "w");
	fclose(fl);
}

void InitMaster()
{
	FILE* fl = fopen(Cind, "r");
	fread(IndecesM, sizeof(MINDEX), CAPACITY, fl);
	fclose(fl);

	fl = fopen(Cgb, "w");
	fclose(fl);

	fl = fopen(Cfl, "r");
	fread(&mastersCount, sizeof(int), 1, fl);
	fclose(fl);
}

void AddGarbage(int pos)
{
	int garbage[GCA];
	FILE* fl = fopen(Cgb, "r");
	fread(garbage, sizeof(short), GCA, fl);
	fclose(fl);

	for (int i = 0; i < GCA; ++i)
	{
		if (garbage[i] == 0)
		{
			garbage[i] = pos;
			break;
		}
	}

	fl = fopen(Cgb, "w");
	fwrite(garbage, sizeof(short), GCA, fl);
	fclose(fl);

	/*for (int i = 0; i < GCA; ++i)
	{
		printf("%d ", garbage[i]);
	}*/
}

void ReadMaster(CRECORD* crds)
{
	FILE* fl = fopen(Cfl, "r");
	fread(&mastersCount, sizeof(int), 1, fl);
	fread(crds, sizeof(CRECORD), CAPACITY, fl);
	fclose(fl);

	return crds;
}

void WriteMaster(CRECORD* crds)
{
	FILE* fl = fopen(Cfl, "w");
	fwrite(&mastersCount, sizeof(int), 1, fl);
	fclose(fl);

	fl = fopen(Cfl, "a");
	fwrite(crds, sizeof(CRECORD), mastersCount, fl);
	fclose(fl);
}

int FindPosition(int ind)
{
	for (int i = 0; i < CAPACITY; ++i)
	{
		if (IndecesM[i].active && IndecesM[i].id == ind)
		{
			return sizeof(int) + IndecesM[i].address * sizeof(CRECORD);
		}
	}
	return -1;
}

void IncMasterRecords(int q)
{
	CRECORD crds[CAPACITY];
	ReadMaster(crds);
	mastersCount += q;
	WriteMaster(crds);
}