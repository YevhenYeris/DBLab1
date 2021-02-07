#include "main.h"
#include "country.h"
#include "brand.h"

int main()
{
	Init();
	//Clear_M();
	//Clear_S();

	while (1)
	{
		char command[] = "";
		scanf("%s", command);
		ParseCommand(command);
	}

	return 0;
}

void ParseCommand(char command[])
{
	if (!strcmp("get-m", command))
	{
		int m = 0;
		scanf("%d", &m);
		CRECORD crd = Get_M(m);

		printf("CT_ID=%d;CT_NAME=%s\n", crd.record.CT_ID, crd.record.CT_NAME);
	}
	if (!strcmp("get-s", command))
	{
		int m = 0;
		int s = 0;
		scanf("%d%d", &m, &s);
		BRECORD brd = Get_S(m, s);
		if (brd.active)
			printf("BR_ID=%d;BR_NAME=%s\n", brd.record.BR_ID, brd.record.BR_NAME);
		else
			printf("record is not present\n");
	}
	if (!strcmp("del-m", command))
	{
		int m = 0;
		scanf("%d", &m);
		Del_M(m);
	}
	if (!strcmp("del-s", command))
	{
		int m = 0;
		int s = 0;
		scanf("%d%d", &m, &s);
		Del_S(m, s);
	}
	if (!strcmp("update-m", command))
	{
		int m = 0;
		scanf("%d%d", &m);
		Update_M(m);
	}
	if (!strcmp("update-s", command))
	{
		int m = 0;
		int s = 0;
		scanf("%d%d", &m, &s);
		Update_S(m, s);
	}
	if (!strcmp("insert-m", command))
	{
		Insert_M();
	}
	if (!strcmp("insert-s", command))
	{
		int m = 0;
		int s = 0;
		scanf("%d%d", &m, &s);
		Insert_S(m, s);
	}
	if (!strcmp("clear-m", command))
	{
		Clear_M();
	}
	if (!strcmp("clear-s", command))
	{
		Clear_S();
	}
	if (!strcmp("calc-m", command))
	{
		int res = Calc_M();
		printf("%d\n", res);
	}
	if (!strcmp("calc-s", command))
	{
		int m = -1;
		scanf("%m", &m);
		int res = Calc_S(m);
		printf("%d\n", res);
	}
}

/*void FillFiles()
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
}*/

void Init()
{
	InitMaster();
}