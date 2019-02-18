#include <stdio.h>

int fahr=0;
float celcius;

#define INFERIOR 0
#define SUPERIOR 300
#define PASSO 20
	
int main()
{
	while (fahr <= SUPERIOR)
	{
		celcius= (5.0 / 9.0) * (fahr - 32 );
		printf("%3d\t%6.2f\n",fahr,celcius);
		fahr=fahr + PASSO;
	}
	return 0;
}