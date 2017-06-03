#include<cstdio>
#include<cassert>
#include<queue>
#include<cstring>
using namespace std;
void getmin(int &a,const int b){if(b<a)a=b;}
struct Type
{
	int D,LA,LB,RA,RB;
	Type(){}
	Type(int _D,int _LA,int _LB,int _RA,int _RB):D(_D),LA(_LA),LB(_LB),RA(_RA),RB(_RB){}
};
int DIST[2][4][4][4][4];
int Solve(const int _LA,const int _LB,const int _RA,const int _RB)
{
	if(_RA==0&&_RB==0)return 0;
	memset(DIST,-1,sizeof(DIST));
	queue<Type>q;
	DIST[0][_LA][_LB][_RA][_RB]=0;
	q.push(Type(0,_LA,_LB,_RA,_RB));
	while(!q.empty())
	{
		const Type t=q.front();q.pop();
		int &now_dist=DIST[t.D][t.LA][t.LB][t.RA][t.RB];
		if(now_dist>5)return 10000;
		if(now_dist%2==1&&t.RA==0&&t.RB==0){return now_dist;}
		int sign=(now_dist%2==0?1:-1);
		int la=t.LA,lb=t.LB,ra=t.RA,rb=t.RB;
		for(int j=0;j<=2;j++)
		{
			for(int k=0;k<=2;k++)if(1<=j+k&&j+k<=2)
			{
				ra-=sign*j,rb-=sign*k,la+=sign*j,lb+=sign*k;
				if(!(la<0||lb<0||ra<0||rb<0||(ra&&rb>ra)||(la&&lb>la)))
				{
					int &dist=DIST[t.D^1][la][lb][ra][rb];
					if(dist==-1)
					{
						dist=now_dist+1;
						q.push(Type(t.D^1,la,lb,ra,rb));
					}
				}
				ra+=sign*j,rb+=sign*k,la-=sign*j,lb-=sign*k;
			}
		}
		assert(la==t.LA&&lb==t.LB&&ra==t.RA&&rb==t.RB);
	}
	assert(0);return -1;
}
int LA,LB,RA,RB;
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;
	scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d%d%d",&LA,&LB,&RA,&RB);
		assert(LA+RA==3&&LB+RB==3);
		int ANS=Solve(LA,LB,RA,RB);
		if(ANS==10000)puts("Too hard!!!");
		else printf("Cracked in %d steps!!!\n",ANS);
	}
	assert(scanf("%d",&testcount)!=1);
	return 0;
}
