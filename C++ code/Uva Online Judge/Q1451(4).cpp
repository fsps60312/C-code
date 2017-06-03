#include<cstdio>
int T,N,L,C0,C1;
char DNA[100001];
struct Ratio
{
	int c0,c1;
	Ratio():c0(0),c1(0){}
	bool operator+=(int a){if(a)c1++;else c0++;}
	bool operator-=(int a){if(a)c1--;else c0--;}
	bool better(Ratio a)
	{
		if(!c0)return false;
		if(!a.c0)return true;
		return c1*a.c0<c0*a.c1;
	}
	bool operator<(Ratio a){return c1*a.c0<c0*a.c1;}
	bool operator==(Ratio a){return c1*a.c0==c0*a.c1;}
	bool operator<=(Ratio a){return c1*a.c0<=c0*a.c1;}
	Ratio operator-(Ratio a)
	{
		Ratio ans;
		ans.c0=c0-a.c0;
		ans.c1=c1-a.c1;
		return ans;
	}
}C,TC,MIN;
struct Ans
{
	int idx;
	Ratio r;
	void update(int l,Ratio tr)
	{
		if(r.better(tr)||(r==tr&&tr.c0+tr.c1<r.c0+r.c1))
		{
			//printf("%d(%d,%d)->%d(%d,%d)\n",idx,r.c0,r.c1,l,tr.c0,tr.c1);
			idx=l,r=tr;
		}
	}
}ANS;
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%s",&N,&L,DNA);
		C=Ratio();
		for(int i=0;i<N;i++)DNA[i]-='0';
		for(int i=0;i<L;i++)C+=DNA[i];
		MIN=TC=Ratio();
		int l,r;
		ANS.idx=0,ANS.r=C;
		for(l=0,r=L;r<N;r++)
		{
			C+=DNA[r];
			ANS.update(l,C);
			TC+=DNA[r-L];
			if(TC<=MIN)MIN=TC;
			//printf("TC:%d %d ,C:%d %d ,MIN:%d %d\n",TC.c0,TC.c1,C.c0,C.c1,MIN.c0,MIN.c1);
			while(MIN.c0+MIN.c1&&MIN<=C)
			{
				//printf("%d:TC:%d %d ,C:%d %d->",r,TC.c0,TC.c1,C.c0,C.c1);
				C=C-MIN;
				l+=MIN.c0+MIN.c1;
				MIN=TC=Ratio();
				for(int i=l;i<=r-L;i++)
				{
					TC+=DNA[i];
					if(TC<=MIN)MIN=TC;
				}
				//printf("TC:%d %d ,C:%d %d\n",TC.c0,TC.c1,C.c0,C.c1);
				ANS.update(l,C);
			}
		}
		printf("%d %d\n",ANS.idx+1,ANS.idx+ANS.r.c0+ANS.r.c1);
	}
	return 0;
}
