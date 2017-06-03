#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstdarg>
#include<iostream>
#define max(a,b) (a>b?a:b)
#define pos(a) max(0,a)
#define posmax(a,b) max(pos(a),pos(b))
#define possum(a,b) (pos(a)+pos(b))
using namespace std;
int T,N,SUM[501];
struct Job
{
	int t,d;
	Job(int a,int b):t(a),d(b){}
};
vector<Job> JOB;
bool cmpJOB(Job a,Job b)
{
	if(a.d!=b.d)return a.d<b.d;
	return a.t>b.t;
}
int main()
{
	freopen("in.txt","r",stdin);
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
		sort(JOB.begin(),JOB.end(),cmpJOB);
		SUM[0]=0;
		for(int i=0;i<N;i++)
		{
			SUM[i+1]=SUM[i]+JOB[i].t;
		}
		int change=-1;
		while(change)
		{
			change=0;
			for(int i=1;i<JOB.size();i++)
			{
				Job &j1=JOB[i-1],&j2=JOB[i];
				int a=possum(SUM[i]-j1.d,SUM[i+1]-j2.d);
				int b=possum(SUM[i-1]+j2.t-j2.d,SUM[i+1]-j1.d);
				if(b<a||(b==a&&j1.t>j2.t))
				{
					change++;
					Job j=j1;
					j1=j2;
					j2=j;
					SUM[i]=SUM[i-1]+j1.t;
				}
			}
		}
		int m1=0,m2=0;
		for(int i=0;i<JOB.size();i++)
		{
			printf("\t%d\t%d\t%d\n",SUM[i+1],JOB[i].t,JOB[i].d);
			int a=pos(SUM[i+1]-JOB[i].d);
			if(a>=m1)
			{
				m2=m1;
				m1=a;
			}
			else if(a>=m2)
			{
				m2=a;
			}
		}
		printf("%d\n",m1+m2);
	}
}
