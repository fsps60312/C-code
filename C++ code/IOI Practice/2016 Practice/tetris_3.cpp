#include "tetris.h"
#include<cassert>
int GRID;
void init(int n)
{
	GRID=0;
}
int position;
int rotation;
void new_figure(int figure_type)
{
	int &p=position,&r=rotation;
	if(figure_type==1)
	{
		p=r=0;
		return;
	}
	else if(figure_type==3)
	{
		switch(GRID)
		{
			case 0:
			{
				p=r=0;
				GRID=1;
			}break;
			case 1:
			{
				p=1,r=2;
				GRID=0;
			}break;
			case 2:
			{
				p=1,r=2;
				GRID=3;
			}break;
			case 3:
			{
				p=0,r=3;
				GRID=2;
			}break;
			case 4:
			{
				p=1,r=1;
				GRID=5;
			}break;
			case 5:
			{
				p=r=0;
				GRID=4;
			}break;
			default:assert(0);break;
		}
	}
	else if(figure_type==2)
	{
		switch(GRID)
		{
			case 0:
			{
				p=r=0;
				GRID=2;
			}break;
			case 1:
			{
				p=1,r=0;
				GRID=2;
			}break;
			case 2:
			{
				p=2,r=1;
				GRID=5;
			}break;
			case 3:
			{
				p=0,r=1;
				GRID=4;
			}break;
			case 4:
			{
				p=1,r=0;
				GRID=0;
			}break;
			case 5:
			{
				p=0,r=0;
				GRID=0;
			}break;
			default:assert(0);break;
		}
/*
0:
   
1:
*  
**
2:
**
3:
 **
4:
*
5:
  *
*/
	}
	else assert(0);
}
int get_position()
{
	return position;
}
int get_rotation()
{
	return rotation;
}
