// SHA1.cpp : �������̨Ӧ�ó������ڵ㡣
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
	printf_s("//SHA-1���㹤��\n");
	printf_s("\n");
	printf_s("���\n");
	printf_s("		-path	file|dir\n");
}

