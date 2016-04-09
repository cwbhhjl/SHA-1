#include "stdafx.h"

uint32_t leftRotateUInt32(uint32_t num, uint32_t i) {
	i %= 32;
	
	num = (num << i) | (num >> (32 - i));

	return num;
}