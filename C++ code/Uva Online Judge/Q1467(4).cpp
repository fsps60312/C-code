#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstdarg>
#include<iostream>
#define max(a,b) (a>b?a:b)
#define pos(a) max(0,a)
using namespace std;
void getmin(int &a,int b) {if(b<a)a=b;}
int T,N,SUM[501],M1,M2,I1,I2;
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
void GetMaxTwo()
{
	M1=-1,M2=-1,I1=-1,I2=-1;
	for(int i=JOB.size()-1;i>=0;i--)
	{
		int a=pos(SUM[i+1]-JOB[i].d);
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
		SUM[0]=0;
		for(int i=0;i<N;i++)
		{
			SUM[i+1]=SUM[i]+JOB[i].t;
		}
		GetMaxTwo();
		int ans=M1+M2;
		for(int i=0;i<I1;i++)
		{
			if(JOB[i].t<=JOB[I1].t)continue;
			Job &j=JOB[i];
			getmin(ans,pos(M1-j.t)+pos(SUM[I1+1]-j.d));
		}
		printf("%d\n",ans);
	}
}
