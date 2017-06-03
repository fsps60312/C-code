#include<cstdio>
using namespace std;
int T,A,B,C,N;
void solve()
{
	int loc;
	printf("0");
	if(C==3)
	{
		static int bse[6]={0,3,1,4,2,5};
		for(int i=1;i<6;i++)printf(" %d",bse[i]);
		B-=2,C-=3;
		loc=5;
	}
	else if(C%3==1)
	{
		int cnt=(C-1)/3;
		loc=0;
		for(int i=0;i<=cnt;i++,C--)printf(" %d",loc+=3);
		printf(" %d",loc-=2);B--;
		for(int i=1;i<=cnt;i++,C--)printf(" %d",loc-=3);
		printf(" %d",loc+=1);A--;
		for(int i=1;i<=cnt;i++,C--)printf(" %d",loc+=3);
		printf(" %d",loc+=2);B--;
	}
	else if(C%3==2)
	{
		int cnt=(C-2)/3;
		loc=0;
		for(int i=0;i<=cnt;i++,C--)printf(" %d",loc+=3);
		printf(" %d",loc-=1);A--;
		for(int i=1;i<=cnt;i++,C--)printf(" %d",loc-=3);
		printf(" %d",loc-=1);A--;
		for(int i=0;i<=cnt;i++,C--)printf(" %d",loc+=3);
	}
	else
	{
		int cnt=(C-3)/3;
		loc=0;
		for(int i=0;i<=cnt;i++,C--)printf(" %d",loc+=3);
		printf(" %d",loc+=1);A--;
		for(int i=0;i<=cnt;i++,C--)printf(" %d",loc-=3);
		printf(" %d",loc+=1);A--;
		for(int i=0;i<=cnt;i++,C--)printf(" %d",loc+=3);
	}
	for(;A>1;A--)printf(" %d",loc+=1);
	if(B%2==0)
	{
		int cnt=B/2;
		for(int i=0;i<cnt;i++,B--)printf(" %d",loc+=2);
		printf(" %d",loc+=1);A--;
		for(int i=0;i<cnt;i++,B--)printf(" %d",loc-=2);
	}
	else
	{
		int cnt=B/2;
		for(int i=0;i<=cnt;i++,B--)printf(" %d",loc+=2);
		printf(" %d",loc-=1);A--;
		for(int i=0;i<cnt;i++,B--)printf(" %d",loc-=2);
	}
	puts("");
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d%d%d",&A,&B,&C);
			N=A+B+C+1;
			solve();
		}
	}
	return 0;
}
//01234567890
//012123
//03312424
//03314225
//044135226
//05514623737
//05516427338
//066157248339
