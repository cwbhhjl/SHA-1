// SHA1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

void display();

int main(int argc, char** argv)
{
	if (argc <= 2)
	{
		display();
		return 0;
	}

	if (argc==3)
	{
		if (strcmp(argv[2],"-add"))
		{
			sha1(argv[2]);
		}
	}
	

    return 0;
}


void display()
{
	printf_s("\n");
	printf_s("//SHA-1计算工具\n");
	printf_s("\n");
	printf_s("命令：\n");
	printf_s("		-path	file|dir\n");
}

