#include <stdio.h>
#include <vector>

int main()
{
	FILE* fin = stdin;
	
	int dayCount = 0, day = 0;
	
	fscanf(fin, " %d", &dayCount);
	
	int width = 0, height = 0, floors = 0, count = 0;
	int curW = 0, curH = 0, curF = 0, curTime = 0, cur = 0;
	int minW = 0, minH = 0, minF = 0, minTime = 0;
	
	for(day = 1; day <= dayCount; ++day)
	{
		fscanf(fin, " %d %d %d %d", &width, &height, &floors, &count);
		
		minTime = 987654321;
		
		for(cur = 1; cur <= count; ++cur)
		{
			fscanf(fin, " %d %d %d", &curW, &curH, &curF);
			curTime = curW + curH + (2*(curF - 1));
			if(curTime < minTime)
			{
				minW = curW;
				minH = curH;
				minF = curF;
				minTime = curTime;
			}
			curTime = (width - curW) + curH + (2*(curF - 1));
			if(curTime < minTime)
			{
				minW = curW;
				minH = curH;
				minF = curF;
				minTime = curTime;
			}
			curTime = curW + (height - curH) + (2*(curF - 1));
			if(curTime < minTime)
			{
				minW = curW;
				minH = curH;
				minF = curF;
				minTime = curTime;
			}
			curTime = (width - curW) + (height - curH) + (2*(curF - 1));
			if(curTime < minTime)
			{
				minW = curW;
				minH = curH;
				minF = curF;
				minTime = curTime;
			}
		}
		
		printf("Day #%d: %d %d %d %d\n", day, minW, minH, minF, minTime);
	}
	
	return 0;
}
