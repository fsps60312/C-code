#define SELF
#ifndef SELF
#include"cgdzlib.h"
#endif
#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
#ifdef SELF

int GRADER_DATA[10];
int inicjuj()
{
	int n=6;
	for(int i=1;i<=n;i++)GRADER_DATA[i]=i;
	random_shuffle(GRADER_DATA+1,GRADER_DATA+n+1);
	printf("s:");for(int i=1;i<=n;i++)printf(" %d",GRADER_DATA[i]);puts("");
	return n;
}
int f(int i,int j,int d)
{
	return (GRADER_DATA[i]-GRADER_DATA[j])%d==0;
}
int g(int i,int j)
{
	return GRADER_DATA[i]>GRADER_DATA[j];
}
void odpowiedz(int k)
{
	printf("k=%d\n",k);
	puts(GRADER_DATA[k]==1?"AC":"WA");
	if(GRADER_DATA[k]!=1)system("pause");
}
#endif
vector<int>Merge(vector<int>*a,vector<int>*b,const int small_base)
{
	if(a->empty()||b->empty())return a->empty()?*b:*a;
	if(a->size()<b->size())swap(a,b);
	if(a->size()!=b->size())
	{
		assert(a->size()==b->size()+1);
		int dis=-1;
		for(int i=(int)a->size()-2;i>=0;i--)if(f(a->front(),b->front(),small_base*(1+i*2))){dis=i;break;}
		assert(dis!=-1);
		if(dis!=0)reverse(b->begin(),b->end());
		vector<int>ans;
		ans.push_back(a->front());
		for(int i=1;i<(int)a->size();i++)ans.push_back((*b)[i-1]),ans.push_back((*a)[i]);
		return ans;
	}
	else
	{
		do_it_again:;
		int disf=-1,disb=-1;
		for(int i=(int)a->size();i>=0;i--)if(f(a->front(),b->front(),small_base*(1+i*2))){disf=i;break;}
		for(int i=(int)a->size();i>=0;i--)if(f(a->front(),b->back(),small_base*(1+i*2))){disb=i;break;}
		assert(disf!=-1&&disb!=-1);
		if(disf==0&&disb==0){if((int)b->size()>=2){swap(a,b);goto do_it_again;}}
		else if(disf==0){}
		else if(disb==0)reverse(b->begin(),b->end());
		else assert(0);
		vector<int>ans;
		for(int i=0;i<(int)a->size();i++)ans.push_back((*a)[i]),ans.push_back((*b)[i]);
		return ans;
	}
}
vector<int>Sort(const vector<int>&s,const int small_base)
{
	if((int)s.size()<=1)return s;
	vector<int>a,b;
	for(int i=0;i<(int)s.size();i++)
	{
		(f(s[0],s[i],small_base*2)?a:b).push_back(s[i]);
	}
	a=Sort(a,small_base*2),b=Sort(b,small_base*2);
	vector<int>ans=Merge(&a,&b,small_base);
	for(int i=0;i<(int)ans.size();i++)printf("%d ",ans[i]);puts("");
	return ans;
}
int main()
{
	int testcount=1;
	#ifdef SELF
	testcount=1000;
	#endif
	while(testcount--)
	{
		const int n=inicjuj();
		vector<int>s;
		for(int i=1;i<=n;i++)s.push_back(i);
		vector<int>ans=Sort(s,1);
		odpowiedz(g(ans.front(),ans.back())?ans.back():ans.front());
	}
	return 0;
}
