// SHA1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"



int main()
{
	uint8_t* data = NULL; 
	FILE* file = NULL;
	uintmax_t fileSize = 0;
	errno_t err = fopen_s(&file,"D:\\PortableApp\\Aero Adjuster\\ColorHelper.dll", "rb");

	if (err)
	{
		printf_s("can't open file.\n");
	}
	else
	{
		fseek(file, 0, SEEK_END);
		fileSize = ftell(file);
		fseek(file, 0, SEEK_SET);

		uint16_t rem = (fileSize * 8 + 1) % 512;
		uint16_t need;

		if (rem == 448)
		{
			need = 0;//判断条件进不去
		}

		if (rem > 448)
		{
			need = (961 - rem) / 8;
		}
		if (rem < 448)
		{
			need = (449 - rem) / 8;
		}

		data = (uint8_t*)calloc((fileSize + need + 8), sizeof(uint8_t));

		fread_s(data, fileSize, 1, fileSize, file);

		data[fileSize] = 0x80;

		for (uint16_t i = 1; i < need; i++)
		{
			data[fileSize + i] = 0x00;
		}

		uint8_t lengthData[8];

		for (uint8_t i = 0; i < 8; i++)
		{
			data[fileSize + need + i] = (fileSize >> (8 * (7 - i))) & 0xFF;
		}
	}

	sha1FileInit(data);

	getchar();
    return 0;
}

