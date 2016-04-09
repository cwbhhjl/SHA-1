// SHA1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"



int main()
{
	//uint8_t* data = NULL; 
	//FILE* file = NULL;
	//uintmax_t fileSize = 0;
	//uint32_t blockNum = 0;
	//uint32_t w[80] = { 0 };
	//
	//errno_t err = fopen_s(&file,"D:\\PortableApp\\Aero Adjuster\\ColorHelper.dll", "rb");

	//if (err)
	//{
	//	printf_s("can't open file.\n");
	//	return 0;
	//}
	//else
	//{
	//	//计算文件大小（字节数）
	//	fseek(file, 0, SEEK_END);
	//	fileSize = ftell(file);
	//	fseek(file, 0, SEEK_SET);

	//	uint16_t rem = (fileSize * 8 + 1) % 512;
	//	uint16_t need;

	//	//if (rem == 448)
	//	//{
	//	//	need = 0;//判断条件进不去
	//	//}

	//	//计算补长度所需的字节数
	//	if (rem > 448)
	//	{
	//		need = (961 - rem) / 8;
	//	}
	//	if (rem < 448)
	//	{
	//		need = (449 - rem) / 8;
	//	}

	//	//总长度就是原始字节数+补位长度+位长度信息长度
	//	uintmax_t newDataByteNum = fileSize + need + 8;

	//	data = (uint8_t*)calloc(newDataByteNum, sizeof(uint8_t));

	//	//原始位串信息读入
	//	fread_s(data, fileSize, 1, fileSize, file);

	//	//补位
	//	data[fileSize] = 0x80;

	//	for (uint16_t i = 1; i < need; i++)
	//	{
	//		data[fileSize + i] = 0x00;
	//	}

	//	//补位长度信息
	//	for (uint8_t i = 0; i < 8; i++)
	//	{
	//		data[fileSize + need + i] = ((fileSize * 8) >> (8 * (7 - i))) & 0xFF;
	//	}

	//	blockNum = newDataByteNum / 64;
	//	
	//	//块处理
	//	for (uintmax_t i = 0; i < blockNum; i++)
	//	{
	//		for (uint8_t j = 0; j < 64; j++)
	//		{
	//			w[j / 4] |= ((uint32_t)data[j + i * 64]) << (24 - (j % 4) * 8);
	//			/*switch (j%4)
	//			{
	//			case 0:
	//				temp0 = ((uint32_t)data[j + i * 64]) << 24;
	//				break;
	//			case 1:
	//				temp1 = ((uint32_t)data[j + i * 64]) << 16;
	//				break;
	//			case 2:
	//				temp2 = ((uint32_t)data[j + i * 64]) << 8;
	//				break;
	//			case 3:
	//				w[j/4] = ((uint32_t)data[j + i * 64]) | temp0 | temp1 | temp2;
	//				break;
	//			default:
	//				break;
	//			}*/
	//			//((uint32_t)data[j + i * 64]) << (24 - (j % 4) * 8);
	//		}

	//		for (uint8_t k = 16; k < 80; i++)
	//		{
	//			w[k] = leftRotateUInt32(w[k - 3] ^ w[k - 8] ^ w[k - 14] ^ w[k - 16], 1);
	//		}
	//		break;//测试用，只计算第一个块
	//	}
	//}

	//sha1FileInit(data);

	sha1FileCal();

	getchar();
    return 0;
}

