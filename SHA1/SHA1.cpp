#include "stdafx.h"

uint32_t h0 = 0x67452301;
uint32_t h1 = 0xEFCDAB89;
uint32_t h2 = 0x98BADCFE;
uint32_t h3 = 0x10325476;
uint32_t h4 = 0xC3D2E1F0;

uint32_t a, b, c, d, e, f, temp;

uint64_t messageLength;

uint32_t w[80] = { 0 };

List Date;

void sha1Init(const char* str) {
	uint32_t strLen = strlen(str);

	for (uint32_t i = strLen; i > 0; i--) 
	{
		listAdd(Date, str[strLen - i]);
	}

	listAdd(Date, 0x80);

	uint16_t rem = (strLen + 1)%512;
	uint16_t need;

	if (rem==448)
	{
		return;
	}

	if (rem > 448) 
	{
		need = 960 - rem;
	}
	else
	{
		need = 448 - rem;
	}

	for (uint16_t i = 0; i < need; i++)
	{
		listAdd(Date, 0x00);
	}
}