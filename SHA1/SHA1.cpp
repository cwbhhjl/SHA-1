#include "stdafx.h"

uint32_t h0 = 0x67452301;
uint32_t h1 = 0xEFCDAB89;
uint32_t h2 = 0x98BADCFE;
uint32_t h3 = 0x10325476;
uint32_t h4 = 0xC3D2E1F0;

uint32_t a, b, c, d, e, f, temp;

uint64_t messageLength;

uint32_t w[80] = { 0 };

void sha1Init(char* str) {
	
}