#include<vector>
#include<cassert>
using namespace std;
struct DiceState
{
	int top,type;
	DiceState(){}
	DiceState(const int _to,const int _ty):top(_to),type(_ty){}
}MOVE[24][4];
struct DiceBuilder
{
	struct Dice
	{
		int top,front,right,left,back,bottom;
		Dice():top(0),front(1),right(2),left(3),back(4),bottom(5){}
		Dice(const int _to,const int _fr,const int _ri,const int _le,const int _ba,const int _bo):top(_to),front(_fr),right(_ri),left(_le),back(_ba),bottom(_bo){}
		Dice Move(const int direction)
		{
			int tmp;
			switch(direction)
			{
				case 0:tmp=top,top=front,front=bottom,bottom=back,back=tmp;break;
				case 1:tmp=top,top=left,left=bottom,bottom=right,right=tmp;break;
				case 2:tmp=top,top=back,back=bottom,bottom=front,front=tmp;break;
				case 3:tmp=top,top=right,right=bottom,bottom=left,left=tmp;break;
				default:assert(0);break;
			}
			return (*this);
		}
		Dice Up()const{Dice ans=(*this);return ans.Move(0);}
		Dice Right()const{Dice ans=(*this);return ans.Move(1);}
		Dice Down()const{Dice ans=(*this);return ans.Move(2);}
		Dice Left()const{Dice ans=(*this);return ans.Move(3);}
	};
	Dice dice_type[24];
	int dice_idx[6][6];
	void BuildMOVE()
	{
		for(int i=0;i<24;i++)
		{
			Dice now,nxt;
			now=dice_type[i];
			for(int d=0;d<4;d++)
			{
				switch(d)
				{
					case 0:nxt=now.Up();break;
					case 1:nxt=now.Right();break;
					case 2:nxt=now.Down();break;
					case 3:nxt=now.Left();break;
					default:assert(0);break;
				}
				MOVE[i][d]=DiceState(nxt.top,dice_idx[nxt.top][nxt.front]);
				assert(MOVE[i][d].type!=-1);
			}
		}
	}
	void Build()
	{
		for(int i=0;i<36;i++)dice_idx[i/6][i%6]=-1;
		Dice *d=dice_type;
		d[0]=Dice();
		d[4]=d[0].Up();
		d[8]=d[0].Up().Up();
		d[12]=d[0].Down();
		d[16]=d[0].Left().Up();
		d[20]=d[0].Right().Up();
		for(int i=0;i<=20;i+=4)for(int j=1;j<=3;j++)d[i+j]=d[i+j-1].Left();
//		for(int i=0;i<24;i++)printf("(%d,%d)\n",d[i].top,d[i].front);
		for(int i=0;i<24;i++)
		{
			int &idx=dice_idx[d[i].top][d[i].front];
			assert(idx==-1),idx=i;
		}
		BuildMOVE();
	}
}DICEBUILDER;
