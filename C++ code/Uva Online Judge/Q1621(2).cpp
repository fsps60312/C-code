#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int N;
vector<int>ANS;
void assert(bool legal)
{
	if(legal)return;
	for(;;)printf("E");
}
void solve(int a,int b,int c)
{
	int A=a,B=b,C=c;
	int loc;
	ANS.clear();
	if(C==3)
	{
		static int bse[6]={0,3,1,4,2,5};
		for(int i=0;i<6;i++)ANS.push_back(bse[i]);
		B-=2,C-=3;
		loc=5;
	}
	else if(C%3==1)
	{
		int cnt=(C-1)/3;
		ANS.push_back(0);
		loc=0;
		for(int i=0;i<=cnt;i++,C--)ANS.push_back(loc+=3);
		ANS.push_back(loc-=2);B--;
		for(int i=1;i<=cnt;i++,C--)ANS.push_back(loc-=3);
		ANS.push_back(loc+=1);A--;
		for(int i=1;i<=cnt;i++,C--)ANS.push_back(loc+=3);
		ANS.push_back(loc+=2);B--;
	}
	else if(C%3==2)
	{
		int cnt=(C-2)/3;
		ANS.push_back(0);
		loc=0;
		for(int i=0;i<=cnt;i++,C--)ANS.push_back(loc+=3);
		ANS.push_back(loc-=1);A--;
		for(int i=1;i<=cnt;i++,C--)ANS.push_back(loc-=3);
		ANS.push_back(loc-=1);A--;
		for(int i=0;i<=cnt;i++,C--)ANS.push_back(loc+=3);
	}
	else
	{
		int cnt=(C-3)/3;
		ANS.push_back(0);
		loc=0;
		for(int i=0;i<=cnt;i++,C--)ANS.push_back(loc+=3);
		ANS.push_back(loc+=1);A--;
		for(int i=0;i<=cnt;i++,C--)ANS.push_back(loc-=3);
		ANS.push_back(loc+=1);A--;
		for(int i=0;i<=cnt;i++,C--)ANS.push_back(loc+=3);
	}
	assert(C==0);
	for(;A>1;A--)ANS.push_back(loc+=1);
	if(B%2==0)
	{
		int cnt=B/2;
		for(int i=0;i<cnt;i++,B--)ANS.push_back(loc+=2);
		ANS.push_back(loc+=1);A--;
		for(int i=0;i<cnt;i++,B--)ANS.push_back(loc-=2);
	}
	else
	{
		int cnt=B/2;
		for(int i=0;i<=cnt;i++,B--)ANS.push_back(loc+=2);
		ANS.push_back(loc-=1);A--;
		for(int i=0;i<cnt;i++,B--)ANS.push_back(loc-=2);
	}
	assert(A==0&&B==0&&C==0&&ANS.size()==N);
}
void VarifyAns(int a,int b,int c)
{
	int A=0,B=0,C=0;
	for(int i=1,v;i<ANS.size();i++)
	{
		v=ANS[i]-ANS[i-1];
		switch(v)
		{
			case -1:
			case 1:A++;break;
			case -2:
			case 2:B++;break;
			case -3:
			case 3:C++;break;
			default:assert(0);
		}
	}
	assert(A==a&&B==b&&C==c);
	sort(ANS.begin(),ANS.end());
	for(int i=0;i<ANS.size();i++)assert(ANS[i]==i);
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	int T,A,B,C;
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			if(scanf("%d%d%d",&A,&B,&C)!=3)assert(0);
			assert(A>=3&&B>=3&&C>=3);
			N=A+B+C+1;
			solve(A,B,C);
			printf("%d",ANS[0]);
			for(int i=1;i<ANS.size();i++)printf(" %d",ANS[i]);
			puts("");
			VarifyAns(A,B,C);
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
