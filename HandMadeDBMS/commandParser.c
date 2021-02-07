#pragma once
#include "commandParser.h"
#include "stdio.h"

void ParseCommand(char command[])
{
	if (!strcmp("get-m", command))
	{
		int m = 0;
		scanf("%d", &m);
		Get_M(m);
	}
	if (!strcmp("get-s", command))
	{
		int m = 0;
		int s = 0;
		scanf("%d%d", &m, &s);
		Get_S(m, s);
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
}