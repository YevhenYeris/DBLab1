#pragma once

typedef struct COUNTRY
{
	int CT_ID;
	char CT_NAME[3];
} COUNTRY;

typedef struct BRAND
{
	int BR_ID;
	int CT_ID;
	char BR_NAME[25];
} BRAND;

typedef struct CRECORD
{
	int active;
	COUNTRY record;
} CRECORD;

typedef struct BRECORD
{
	int active;
	BRAND record;
} BRECORD;

typedef struct INDEXEDRECORD
{
	int id;
	int address;
} INDEXEDRECORD;