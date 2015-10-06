#include <stdio.h>

int main() {
	printf("PART A\n");
	unsigned long long x = 0b1111111;
	unsigned long long y = 0b10;
	
	unsigned long long mask1 = 0b1100011;
	
	unsigned long long first = x & mask1;
	unsigned long long mask2 = y << 2;
	unsigned long long ansa = first | mask2;	

	printf ("%llu\n\n",ansa);

	printf("PART B\n");
	unsigned long long bx = 0b1000;
	unsigned long long maskb = 0b0000;
	unsigned long long ansb = bx & maskb;
	printf("%llu\n\n",ansb);

return 0;
}
