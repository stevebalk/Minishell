#include <stdio.h>
#include <unistd.h>


void print_bits(unsigned char octet)
{
	int	i;
	unsigned char bit;

	i = 7;
	while (i >= 0 )
	{
		bit = (octet >> i & 1) + '0';
		write(1, &bit, 1);
		i--;
	}
}

int main(void)
{
	printf("--- start ---\n");
	int number = 10;
	print_bits(number);
	printf("   Number: %i\n", number);
	
	printf("\nSet Unset or Toggle Bit n\n");
	number |=  (1 << 0);
	print_bits(number);
	printf("   Number: %i   settet bit nr: 0 (right) to 1   \"number |=  (1 << 0)\" \n", number);

	number &= ~(1 << 0);
	print_bits(number);
	printf("   Number: %i   settet bit nr: 0 (right) to 0   \"number &= ~(1 << 0)\" \n", number);

	number ^=  (1 << 0);
	print_bits(number);
	printf("   Number: %i   toggle bit nr: 0 (right)        \"number ^=  (1 << 0)\" \n", number);

	number ^=  (1 << 0);
	print_bits(number);
	printf("   Number: %i   toggle bit nr: 0 (right)        \"number ^=  (1 << 0)\" \n", number);


	printf("\nBit-Masks\n");
	// Bit Masken
	number |= (0001);
	print_bits(number);
	printf("   Number: %i   settet bit nr: 0 (right) to 1   \"number |=  (0001)\" \n", number);

	number &= ~(0001);
	print_bits(number);
	printf("   Number: %i   settet bit nr: 0 (right) to 0   \"number &= ~(0001)\" \n", number);

	number ^= (0001);
	print_bits(number);
	printf("   Number: %i   toggle bit nr: 0 (right)        \"number ^=  (0001)\" \n", number);

	number ^= (0001);
	print_bits(number);
	printf("   Number: %i   toggle bit nr: 0 (right)        \"number ^=  (0001)\" \n", number);
	printf("\n");

	printf("\n\nDiverses\n");
	int g_flags = 7;
	int index = 2;
	print_bits(g_flags);
	printf("   g_flags: %i   \n", g_flags);
	printf("(g_flags & (1 << index)) != 0   -- index: %i     result: %i\n   --> return 1 if bit of position index is settet    0 if not settet\n\n", index, (g_flags & (1 << index)) != 0);
	
	printf("(1 << %i (index)    printed: ", index);fflush(stdout);
	print_bits(1 << index);
	printf("\n");
	print_bits(g_flags);
	printf(" & ");fflush(stdout);
	print_bits(1 << 2);
	printf(" == ");fflush(stdout);
	print_bits((g_flags & (1 << 2)));
	printf("\n");
	print_bits((0b00000111 & 0b00000100));
	printf("\n");
	
	return 0;
}