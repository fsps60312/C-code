#include<bits/stdc++.h>
using namespace std;
int T,P,Q,X[11],Y[11];
struct Ans
{
	int x,y;
	Ans(){}
	Ans(const int &x,const int &y):x(x),y(y){}
};
vector<Ans>ANS;
void PutTri(const int &sz,int &x,int &y)
{
	ANS.push_back(Ans(x-=X[sz]/2,y+=Y[sz]));
	ANS.push_back(Ans(x+=X[sz],y));
	ANS.push_back(Ans(x-=X[sz]/2,y-=Y[sz]));
}
int main()
{
//	freopen("in.txt","r",stdin);
//	while(
	scanf("%d",&T);//==1)
	{
		while(T--)
		{
			ANS.clear();
			scanf("%d%d%d%d",&P,&Q,&X[1],&Y[1]);
			int x=X[1],y=Y[1];
			ANS.push_back(Ans(x,y));
			if(P==0&&Q==0){ANS.push_back(Ans(x-=X[1],y-=Y[1]));ANS.push_back(Ans(x+=X[1]<<1,y)),ANS.push_back(Ans(x-=X[1],y+=Y[1]));goto finishline;}
			Y[1]>>=1;
			for(int i=2;i<=max(P,Q);i++)X[i]=X[i-1]>>1,Y[i]=Y[i-1]>>1;
			for(int i=max(P,Q)-1;i>=1;i--)X[i]=X[i+1]<<1,Y[i]=Y[i+1]<<1;
			ANS.push_back(Ans(x-=X[1],y-=Y[1]<<1));
			ANS.push_back(Ans(x+=X[P],y));
			for(int sz=P;sz>=2;sz--)
			{
				PutTri(sz,x,y);
				ANS.push_back(Ans(x+=X[sz],y));
			}
			PutTri(1,x,y);
			for(int sz=2;sz<=Q;sz++)
			{
				ANS.push_back(Ans(x+=X[sz],y));
				PutTri(sz,x,y);
			}
			ANS.push_back(Ans(x+=X[Q],y));
			ANS.push_back(Ans(x-=X[1],y+=Y[1]<<1));
			finishline:;
			for(int i=1;i<ANS.size();i++)printf("(%d,%d)(%d,%d)\n",ANS[i-1].x,ANS[i-1].y,ANS[i].x,ANS[i].y);
			puts("");
		}
	}
	return 0;
}
