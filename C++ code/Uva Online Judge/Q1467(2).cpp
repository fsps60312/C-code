#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstdarg>
#include<iostream>
#define max(a,b) (a>b?a:b)
#define pos(a) max(0,a)
#define posmax(a,b) max(pos(a),pos(b))
#define possum(a,b) (pos(a)+pos(b))
#define abs(a) (a>0?a:-a)
using namespace std;
int T,N,SUM[501],M1,M2,I1,I2,CHANGE;
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
	for(int i=0;i<JOB.size();i++)
	{
		printf("\t%d\t%d\t%d\n",SUM[i+1],JOB[i].t,JOB[i].d);
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
void swapiim1(int i)
{
	CHANGE++;
	Job j=JOB[i-1];
	JOB[i-1]=JOB[i];
	JOB[i]=j;
	SUM[i]=SUM[i-1]+JOB[i-1].t;
}
void checkI1()
{
	if(I1==0)return;
	Job &j1=JOB[I1-1],&j2=JOB[I1];
	if(I1-1==I2)
	{
		int a=possum(SUM[I1]-j1.d,SUM[I1+1]-j2.d);
		int b=possum(SUM[I1-1]+j2.t-j2.d,SUM[I1+1]-j1.d);
		if(b<a)
		{
			swapiim1(I1);
//			printf("swap%d\n",CHANGE);
			I1--,I2++;
		}
	}
	else
	{
		int a=posmax(SUM[I1]-j1.d,SUM[I1+1]-j2.d);
		int b=posmax(SUM[I1-1]+j2.t-j2.d,SUM[I1+1]-j1.d);
		if(b<a)
		{
			swapiim1(I1);
			I1--;
		}
	}
}
void checkI2()
{
	if(I2==0)return;
	Job &j1=JOB[I2-1],&j2=JOB[I2];
	if(I2-1==I1)
	{
		int a=possum(SUM[I2]-j1.d,SUM[I2+1]-j2.d);
		int b=possum(SUM[I2-1]+j2.t-j2.d,SUM[I2+1]-j1.d);
		if(b<a)
		{
			swapiim1(I2);
//			printf("swap%d\n",CHANGE);
			I2--,I1++;
		}
	}
	else
	{
		int a=posmax(SUM[I2]-j1.d,SUM[I2+1]-j2.d);
		int b=posmax(SUM[I2-1]+j2.t-j2.d,SUM[I2+1]-j1.d);
		if(b<a)
		{
			swapiim1(I2);
			I2--;
		}
	}
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
		int cnt=0;
		CHANGE=-1;
		while(CHANGE)
		{
			CHANGE=0;
			printf("cnt=%d\n",cnt);
			GetMaxTwo();
			if(JOB[I1].t<JOB[I2].t)
			{
				int i=I1;
				I1=I2;
				I2=i;
			}
			printf("I1=%d,I2=%d\n",I1,I2);
			checkI1();
			checkI2();
//			printf("CHANGE%d\n",CHANGE);
		}
		printf("%d\n",M1+M2);
	}
}
