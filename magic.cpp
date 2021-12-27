#include <stdio.h>

#define TRUE 1
#define FALSE 0

int main()
{
	FILE* fin = stdin;
	int x, y;
	long o, answer, a;
	
	bool possible;
	
	for(;;)
	{
		fscanf(fin, " %d %d", &x, &y);
		
		if(x == 0 && y == 0)
			break;
		
		answer = -1;
		possible = TRUE;
		
		if(x == 0)
			possible = FALSE;
		
		for(o = 1; possible && o <= 10; ++o)
		{
			a = (o * x);
			//if(a >= 144)
			if(a > 144 || a < 0)
			{
				possible = FALSE;
				break;
			}
			a = (a + y);
			//if(a > 144 || (a % x) != 0)
			if(a > 144 || a < 0 || (a % x) != 0)
			{
				possible = FALSE;
				break;
			}
			a = (a / x);
			//if(a >= 144)
			if(a > 144 || a < 0)
			{
				possible = FALSE;
				break;
			}
			a = (a - o);
			//if(a >= 144)
			if(a > 144 || a < 0)
			{
				possible = FALSE;
				break;
			}
			answer = a;
		}
		
		if(possible)
		{
			printf("The number left over is %d.\n", answer);
		}
		else
		{
			printf("The trick is too difficult to do.\n");
		}
	}
	return 0;
}
