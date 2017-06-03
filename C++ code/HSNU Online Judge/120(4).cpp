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
vector<int>S;
void Insert(const int idx,const int v)
{
	S.push_back(int());
	for(int i=S.size()-1;i>idx;i--)S[i]=S[i-1];
	S[idx]=v;
}
int main()
{
	int cnt=0;
	N=GetN();
	S.push_back(1),S.push_back(2);
	for(int sz=2;sz<N;sz++)
	{
//		for(int i=0;i<sz;i++)printf(" %d",S[i]);puts("");
		int l=-1,r=sz,ml,mr,v;
		while(l+2<r)
		{
			ml=(2*l+r)/3,mr=(l+2*r)/3;
			assert(++cnt<=7777);
			v=Med3(sz+1,S[ml],S[mr]);
			if(v==sz+1)l=ml,r=mr;
			else if(v==S[ml])r=ml;
			else l=mr;
		}
		if(r-l==2)
		{
			if(l==-1)
			{
				assert(++cnt<=7777);
				v=Med3(sz+1,S[0],S[1]);
				assert(v!=S[1]);
				if(v==sz+1)Insert(1,sz+1);
				else Insert(0,sz+1);
			}
			else
			{
				assert(++cnt<=7777);
				v=Med3(sz+1,S[l],S[l+1]);
				assert(v!=S[l]);
				if(v==sz+1)Insert(l+1,sz+1);
				else Insert(l+2,sz+1);
			}
		}
		else
		{
//			printf("(%d,%d)\n",l,r);
			Insert(r,sz+1);
		}
	}
	Answer(S[N/2]);
	return 0;
}
