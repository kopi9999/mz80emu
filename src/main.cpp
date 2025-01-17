#include <stdio.h>

extern "C" {
	#include "test.h"
}

int main()
{
	printf("\nPlaceholder: %d\n\n", test());
}

//test jocha