#include<cstdio>
#include<cassert>
#include<queue>
#include<cstring>
using namespace std;
void getmin(int &a,const int b){if(b<a)a=b;}
struct Type
{
	int D,LA,LB,RA,RB,BA,BB;
	Type(){}
	Type(int _D,int _LA,int _LB,int _RA,int _RB,int _BA,int _BB):D(_D),LA(_LA),LB(_LB),RA(_RA),RB(_RB),BA(_BA),BB(_BB){}
};
int DIST[2][4][4][4][4][3][3];
bool Valid(const int dist,const int LA,const int LB,const int RA,const int RB,const int BA,const int BB)
{
	if(dist%2==0)
	{
		if(LA>0&&LB>LA)return false;
		if(RA+BA>0&&RB+BB>RA+BA)return false;
		return true;
	}
	else
	{
		if(LA+BA>0&&LB+BB>LA+BA)return false;
		if(RA>0&&RB>RA)return false;
		return true;
	}
}
int Solve(const int _LA,const int _LB,const int _RA,const int _RB,const int _BA,const int _BB)
{
	if(_RA==0&&_RB==0)return 0;
	memset(DIST,-1,sizeof(DIST));
	queue<Type>q;
	DIST[0][_LA][_LB][_RA][_RB][_BA][_BB]=0;
	q.push(Type(0,_LA,_LB,_RA,_RB,_BA,_BB));
	while(!q.empty())
	{
		const Type t=q.front();q.pop();
		int &now_dist=DIST[t.D][t.LA][t.LB][t.RA][t.RB][t.BA][t.BB];
		if(now_dist>5)break;
		if(now_dist%2==1&&t.RA==0&&t.RB==0){return now_dist;}
		for(int i=0,sign=1;i<2;i++,sign*=-1)
		{
			int la=t.LA,lb=t.LB,ra=t.RA,rb=t.RB;
			int &va=(now_dist%2==0?ra:la),&vb=(now_dist%2==0?rb:lb);
			for(int j=-2;j<=2;j++)
			{
				for(int k=-2;k<=2;k++)
				{
					va+=sign*j,vb+=sign*k;
					int ba=t.BA-sign*j,bb=t.BB-sign*k;
					if(!(la<0||lb<0||ra<0||rb<0||ba+bb<1||ba+bb>2||ba<0||bb<0))
					{
						if(Valid(now_dist,la,lb,ra,rb,ba,bb))
						{
							int &dist=DIST[t.D^1][la][lb][ra][rb][ba][bb];
							if(dist==-1)
							{
								dist=now_dist+1;
								q.push(Type(t.D^1,la,lb,ra,rb,ba,bb));
							}
						}
					}
					va-=sign*j,vb-=sign*k;
				}
			}
			assert(la==t.LA&&lb==t.LB&&ra==t.RA&&rb==t.RB);
		}
	}
	return 100;
}
int LA,LB,RA,RB;
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d%d%d",&LA,&LB,&RA,&RB);
		int ANS=Solve(LA,LB,RA,RB,0,0);
		if(ANS==100)puts("Too hard!!!");
		else printf("Cracked in %d step(s)!!!\n",ANS);
	}
	return 0;
}
