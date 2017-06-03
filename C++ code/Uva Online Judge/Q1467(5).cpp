#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstdarg>
#include<iostream>
#define max(a,b) (a>b?a:b)
#define pos(a) max(0,a)
using namespace std;
void getmin(int &a,int b) {if(b<a)a=b;}
int T,N,M1,M2,I1,I2;
struct Job
{
	int t,d;
	Job(int a,int b):t(a),d(b){}
};
vector<Job> JOB;
bool cmpJOB(Job a,Job b)
{
	if(a.d!=b.d)return a.d<b.d;
	return a.t<b.t;
}
void update(int a,int i)
{
	if(a>=M1)
	{
		M2=M1;
		I2=I1;
		M1=a;
		I1=i;
	}
	else if(a>=M2)
	{
		M2=a;
		I2=i;
	}
}
int GetMaxTwo(int exp,int n)
{
	M1=-1,M2=-1,I1=-1,I2=-1;
	int t=0,a;
	for(int i=0;i<=n;i++)
	{
		if(i==exp)continue;
		t+=JOB[i].t;
		a=pos(t-JOB[i].d);
		update(a,i);
	}
	if(exp>=0)
	{
		t+=JOB[exp].t;
		a=pos(t-JOB[exp].d);
		update(a,-1);
	}
	return M1+M2;
}
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		JOB.clear();
		for(int i=0;i<N;i++)
		{
			int a,b;scanf("%d%d",&a,&b);
			JOB.push_back(Job(a,b)); 
		}
		if(N==1)
		{
			printf("%d\n",pos(JOB[0].t-JOB[0].d));
			continue;
		}
		sort(JOB.begin(),JOB.end(),cmpJOB);
		int ans=GetMaxTwo(-1,N-1);
		int I=max(I1,I2);
		for(int i=0;i<I;i++)
		{
			if(JOB[i].t<=JOB[I].t)continue;
			getmin(ans,GetMaxTwo(i,I));
		}
		printf("%d\n",ans);
	}
}
