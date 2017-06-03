#include"interactive/120.h"
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cassert>
using namespace std;
//int GetN(){return 5;}
//int BSE[]={2,5,4,3,1};
//bool InRange(int o,int a,int b){return (a<=o&&o<=b)||(b<=o&&o<=a);}
//int Med3(int _a,int _b,int _c)
//{
//	int a=BSE[_a-1],b=BSE[_b-1],c=BSE[_c-1];
//	if(InRange(a,b,c))return _a;
//	if(InRange(b,a,c))return _b;
//	if(InRange(c,a,b))return _c;
//	assert(0);
//}
//int Answer(int v)
//{
//	printf("v=%d\n",v);
//	puts(v==4?"AC":"WA");
//}
int N;
bool Cmp(int a,int b)
{
	if(a==b)return false;
	if(a>b)return !Cmp(b,a);
	if(a==1)
	{
		if(b==2)return true;
		int v=Med3(b,1,2);
		return v!=1;
	}
	else if(a==2)
	{
		int v=Med3(1,2,b);
		return v==2;
	}
	else
	{
		if(Cmp(1,a))
		{
			int v=Med3(1,a,b);
			return v==a;
		}
		else
		{
			int v=Med3(b,a,1);
			return v!=a;
		}
	}
}
int S[1500];
int main()
{
	int cnt=0;
	N=GetN();
	for(int i=0;i<N;i++)S[i]=i+1;
	nth_element(S,S+N/2,S+N,Cmp);
	Answer(S[N/2]);
	return 0;
}
