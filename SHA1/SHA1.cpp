#include "stdafx.h"

uint32_t h0 = 0x67452301;
uint32_t h1 = 0xEFCDAB89;
uint32_t h2 = 0x98BADCFE;
uint32_t h3 = 0x10325476;
uint32_t h4 = 0xC3D2E1F0;

uint32_t a, b, c, d, e, f, temp;

uint64_t dataLength;

uint32_t w[80] = { 0 };

List Date;

void sha1StringInit(const char* str) {
	dataLength = strlen(str);

	//初始化数据
	for (uint32_t i = dataLength; i > 0; i--)
	{
		listAdd(Date, str[dataLength - i]);
	}

	listAdd(Date, 0x80);

	uint16_t rem = (dataLength + 1) % 512;
	uint16_t need;

	if (rem == 448)
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

	//补位
	for (uint16_t i = 0; i < need; i++)
	{
		listAdd(Date, 0x00);
	}

	uint8_t strLenData[8];

	for (uint8_t i = 0; i < 8; i++)
	{
		strLenData[i] = (dataLength >> (8 * (7 - i))) & 0xFF;
	}

	//补长度
	for (uint16_t i = 0; i < 8; i++)
	{
		listAdd(Date, strLenData[i]);
	}
}

void sha1FileInit(uint8_t* data)
{

}

