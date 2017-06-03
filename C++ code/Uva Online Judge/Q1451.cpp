#include<cstdio>
int T,N,L,C0,C1;
char DNA[100001];
struct Ratio
{
	int c0,c1;
	Ratio():c0(0),c1(0){}
	bool operator+=(int a){if(a)c1++;else c0++;}
	bool operator-=(int a){if(a)c1--;else c0--;}
	bool operator<(Ratio a)
	{
		if(!c0)return false;
		if(!a.c0)return true;
		return c1*a.c0<c0*a.c1;
	}
	Ratio operator-(Ratio a)
	{
		Ratio ans;
		ans.c0=c0-a.c0;
		ans.c1=c1-a.c1;
		return ans;
	}
}C,TC;
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%s",&N,&L,DNA);
		C=Ratio();
		for(int i=0;i<N;i++)DNA[i]-='0';
		for(int i=0;i<L;i++)C+=DNA[i];
		TC=Ratio();
		int l,r,ansi=0;
		Ratio ans=C;
		for(int l=0,r=L;r<N;r++)
		{
			if(TC<C-TC)
			{
				//printf("%d:TC:%d %d ,C:%d %d->",r,TC.c0,TC.c1,C.c0,C.c1);
				for(;l<r-L;l++)TC-=DNA[l],C-=DNA[l];
				if(ans<C)ans=C,ansi=l;
				//printf("TC:%d %d ,C:%d %d\n",TC.c0,TC.c1,C.c0,C.c1);
			}
			C+=DNA[r];
			if(ans<C)ans=C,ansi=l;
			TC+=DNA[r-L];
		}
		printf("%d %d\n",ansi+1,ansi+ans.c0+ans.c1);
	}
	return 0;
}
