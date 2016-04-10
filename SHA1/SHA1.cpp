#include "stdafx.h"

uint32_t a, b, c, d, e, f, k, temp;

uint64_t dataLength;

List Date;

uint8_t* data = NULL;
uint32_t blockNum = 0;

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

void sha1FileInit(char* path)
{
	FILE* file = NULL;
	//errno_t err = fopen_s(&file, "D:\\PortableApp\\Aero Adjuster\\ColorHelper.dll", "rb");
	errno_t err = fopen_s(&file, path, "rb");
	uintmax_t fileSize = 0;

	if (err)
	{
		printf_s("\ncan't open file.\n");
		return;
	}
	else
	{
		//计算文件大小（字节数）
		fseek(file, 0, SEEK_END);
		fileSize = ftell(file);
		fseek(file, 0, SEEK_SET);

		uint16_t rem = (fileSize * 8 + 1) % 512;
		uint16_t need;

		//if (rem == 448)
		//{
		//	need = 0;//判断条件进不去
		//}

		//计算补长度所需的字节数
		if (rem > 448)
		{
			need = (961 - rem) / 8;
		}
		if (rem < 448)
		{
			need = (449 - rem) / 8;
		}

		//总长度就是原始字节数+补位长度+位长度信息长度
		uintmax_t newDataByteNum = fileSize + need + 8;

		data = (uint8_t*)calloc(newDataByteNum, sizeof(uint8_t));

		//原始位串信息读入
		fread_s(data, fileSize, 1, fileSize, file);

		fclose(file);

		//补位
		data[fileSize] = 0x80;

		for (uint16_t i = 1; i < need; i++)
		{
			data[fileSize + i] = 0x00;
		}

		//补位长度信息
		for (uint8_t i = 0; i < 8; i++)
		{
			data[fileSize + need + i] = ((fileSize * 8) >> (8 * (7 - i))) & 0xFF;
		}

		blockNum = newDataByteNum / 64;
	}
}

void sha1FileCal(void)
{
	uint32_t h0 = 0x67452301;
	uint32_t h1 = 0xEFCDAB89;
	uint32_t h2 = 0x98BADCFE;
	uint32_t h3 = 0x10325476;
	uint32_t h4 = 0xC3D2E1F0;

	if (data==NULL)
	{
		return;
	}

	//块处理
	for (uintmax_t i = 0; i < blockNum; i++)
	{
		uint32_t w[80] = { 0 };

		for (uint8_t j = 0; j < 64; j++)
		{
			w[j / 4] |= ((uint32_t)data[j + i * 64]) << (24 - (j % 4) * 8);
			//采用上面这种写法相对简洁，但注意它会比下面的switch写法多与一个 w[x] 按位或，所以这种情况下在进入到每个新数据块循环时，w[]数组必须置0

			/*switch (j%4)
			{
			case 0:
			temp0 = ((uint32_t)data[j + i * 64]) << 24;
			break;
			case 1:
			temp1 = ((uint32_t)data[j + i * 64]) << 16;
			break;
			case 2:
			temp2 = ((uint32_t)data[j + i * 64]) << 8;
			break;
			case 3:
			w[j/4] = ((uint32_t)data[j + i * 64]) | temp0 | temp1 | temp2;
			break;
			default:
			break;
			}*/
			//((uint32_t)data[j + i * 64]) << (24 - (j % 4) * 8);
		}

		for (uint8_t k = 16; k < 80; k++)
		{
			w[k] = leftRotateUInt32((w[k - 3] ^ w[k - 8] ^ w[k - 14] ^ w[k - 16]), 1);
		}

		a = h0; b = h1; c = h2; d = h3; e = h4;

		for (uint8_t l = 0; l < 80; l++)
		{
			if (0 <= l && l <= 19)
			{
				f = (b & c) | ((~b) & d);
				k = K1;
			}
			else if (20 <= l && l <= 39)
			{
				f = b ^ c ^ d;
				k = K2;
			}
			else if (40 <= l && l <= 59)
			{
				f = (b & c) | (b & d) | (c & d);
				k = K3;
			}
			else if (60 <= l && l <= 79)
			{
				f = b ^ c ^ d;
				k = K4;
			}

			temp = leftRotateUInt32(a, 5) + f + e + k + w[l];
			e = d;
			d = c;
			c = leftRotateUInt32(b, 30);
			b = a;
			a = temp;
		}

		h0 = h0 + a;
		h1 = h1 + b;
		h2 = h2 + c;
		h3 = h3 + d;
		h4 = h4 + e;;
	}

	free(data);

	printf_s("\nSHA-1 : %08X%08X%08X%08X%08X\n", h0, h1, h2, h3, h4);
}

void sha1(char* path)
{
	sha1FileInit(path);
	sha1FileCal();
}

