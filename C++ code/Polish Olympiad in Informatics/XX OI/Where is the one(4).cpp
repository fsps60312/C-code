//#define SELF
#ifndef SELF
#include"cgdzlib.h"
#endif
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
#ifdef SELF
int GRADER_DATA[101];
int inicjuj()
{
	int n=100;
	for(int i=1;i<=n;i++)GRADER_DATA[i]=i;
	random_shuffle(GRADER_DATA+1,GRADER_DATA+n+1);
//	printf("s:");for(int i=1;i<=n;i++)printf(" %d",GRADER_DATA[i]);puts("");
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
	printf("k=%d, result: ",k);
	puts(GRADER_DATA[k]==1?"AC":"WA");
	if(GRADER_DATA[k]!=1)system("pause");
}
#endif
void Merge(vector<int>&ans,vector<int>*a,vector<int>*b,const int small_base)
{
	if(a->empty()||b->empty()){ans=(a->empty()?*b:*a);return;}
	if(a->size()<b->size())swap(a,b);
	if(a->size()!=b->size())
	{
		int dis=0;
		const int af=a->front(),bf=b->front(),abound=(int)a->size()-1;
		for(int i=1;i<abound;i++)if(f(af,bf,small_base*(1+i*2))){dis=i;break;}
		if(dis!=0)reverse(b->begin(),b->end());
		ans.reserve(a->size()+b->size());
		ans.push_back(af);
		const vector<int>&va=*a,&vb=*b;
		for(int i=1;i<=abound;i++)ans.push_back(vb[i-1]),ans.push_back(va[i]);
	}
	else
	{
		if((int)b->size()>=2)
		{
			do_it_again:;
			int fdis0=0,fdis1=0,bdis0=0,bdis1=0;
			const int af=a->front(),ab=a->back(),b0=(*b)[0],b1=(*b)[1],asz=(int)a->size();
			for(int i=0;i<asz;i++)
			{
				const int dis=small_base*(1+i*2);
				if(!fdis0&&f(af,b0,dis))fdis0=i;
				if(!fdis1&&f(af,b1,dis))fdis1=i;
				if(!bdis0&&f(ab,b0,dis))bdis0=i;
				if(!bdis1&&f(ab,b1,dis))bdis1=i;
			}
			if(fdis0==0&&fdis1!=0){}
			else if(bdis0==0&&bdis1!=0)reverse(a->begin(),a->end());
			else{reverse(b->begin(),b->end());goto do_it_again;}
		}
		ans.reserve(a->size()+b->size());
		const vector<int>&va=*a,&vb=*b; 
		const int asz=va.size();
		for(int i=0;i<asz;i++)ans.push_back(va[i]),ans.push_back(vb[i]);
	}
}
void Sort(vector<int>&ans,const vector<int>&s,const int small_base)
{
	if((int)s.size()<=1){ans=s;return;}
	vector<int>a,b;a.reserve(s.size()),b.reserve(s.size());
	const int ssz=s.size();
	for(int i=0;i<ssz;i++)
	{
		(f(s[0],s[i],small_base*2)?a:b).push_back(s[i]);
	}
	vector<int>sa,sb;
	Sort(sa,a,small_base*2),Sort(sb,b,small_base*2);
	Merge(ans,&sa,&sb,small_base);
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
		vector<int>s;s.reserve(n);
		for(int i=1;i<=n;i++)s.push_back(i);
		vector<int>ans;
		Sort(ans,s,1);
		if(n==1)odpowiedz(1);
		else odpowiedz(g(ans.front(),ans.back())?ans.back():ans.front());
	}
	return 0;
}
