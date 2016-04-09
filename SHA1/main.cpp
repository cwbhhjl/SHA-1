// SHA1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"



int main()
{
	uint8_t* rawData = NULL; 
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


		rawData = (uint8_t*)calloc((fileSize + need + 8), sizeof(uint8_t));

		fread_s(rawData, fileSize, 1, fileSize, file);
	}

	sha1FileInit(rawData);

	getchar();
    return 0;
}

