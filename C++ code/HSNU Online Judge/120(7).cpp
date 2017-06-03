#include"interactive/120.h"
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cassert>
#include<map>
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
//////////////////////////////////////////////////
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
int Rand()
{
	static unsigned seed=20151103;
	seed=seed*0xdefaced+230734;
	seed+=seed>>3;
	return seed&0x7fffffff;
}
int S[1500];
void Sort(const int l,const int r)
{
	if(l==r)return;
//	printf("(%d,%d)",l,r);
//	for(int i=l;i<=r;i++)printf("%d",S[i]);puts("");
	int ml,mr;
	do{ml=l+Rand()%(r-l+1),mr=l+Rand()%(r-l+1);}while(ml==mr);
	ml=S[ml],mr=S[mr];
	if(!Cmp(ml,mr))swap(ml,mr);
	vector<int>s[3];
	for(int i=l;i<=r;i++)
	{
		if(S[i]==ml)s[0].push_back(S[i]);
		else if(S[i]==mr)s[2].push_back(S[i]);
		else
		{
			int v=Med3(ml,S[i],mr);
			if(v==ml)s[0].push_back(S[i]);
			else if(v==S[i])s[1].push_back(S[i]);
			else s[2].push_back(S[i]);
		}
	}
//	for(int d=0;d<3;d++)
//	{
//		for(int i=0;i<s[d].size();i++)printf("%d",s[d][i]);
//		putchar(',');
//	}puts("");
	int idx=l-1,now=l;
	for(int d=0;d<3;d++)
	{
		for(int i=0;i<s[d].size();i++)S[++idx]=s[d][i];
		if(N/2<=idx){Sort(now,idx);return;}
		now=idx+1;
	}
	assert(0);
}
int main()
{
	int cnt=0;
	N=GetN();
	for(int i=0;i<N;i++)S[i]=i+1;
	Sort(0,N-1);
	Answer(S[N/2]);
	return 0;
}
