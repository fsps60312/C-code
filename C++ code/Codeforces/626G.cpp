#include<cstdio>
#include<cassert>
#include<set>
using namespace std;
const double INF=1e100;
int N,T,P[200000],L[200000],S[200000];
struct AddChange
{
	int id;
	double dif;
	AddChange(const int i):id(i)
	{
		if(S[i]==L[i])dif=-INF;
		else dif=P[i]*((double)(S[i]+1)/(S[i]+1+L[i])-(double)S[i]/(S[i]+L[i]));
	}
	bool operator<(const AddChange &c)const{return dif!=c.dif?dif>c.dif:id<c.id;}
};
struct RevChange
{
	int id;
	double dif;
	RevChange(const int i):id(i)
	{
		if(S[i]==0)dif=-INF;
		else dif=P[i]*((double)(S[i]-1)/(S[i]-1+L[i])-(double)S[i]/(S[i]+L[i]));
	}
	bool operator<(const RevChange &c)const{return dif!=c.dif?dif>c.dif:id<c.id;}
};
set<AddChange>AC;
set<RevChange>RC;
double ANS;
double ExpEarn(const int id){return P[id]*(double)S[id]/(S[id]+L[id]);}
void ModifyS(const int id,const int val)
{
	AC.erase(AddChange(id)),RC.erase(RevChange(id)),ANS-=ExpEarn(id);
	S[id]+=val,T-=val;
	AC.insert(AddChange(id)),RC.insert(RevChange(id)),ANS+=ExpEarn(id);
}
void ModifyL(const int id,const int val)
{
	AC.erase(AddChange(id)),RC.erase(RevChange(id)),ANS-=ExpEarn(id);
	L[id]+=val;
	AC.insert(AddChange(id)),RC.insert(RevChange(id)),ANS+=ExpEarn(id);
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int querycount;scanf("%d%d%d",&N,&T,&querycount)==3;)
	{
		for(int i=0;i<N;i++)scanf("%d",&P[i]);
		for(int i=0;i<N;i++)scanf("%d",&L[i]);
		for(int i=0;i<N;i++)S[i]=0;
		AC.clear(),RC.clear();
		for(int i=0;i<N;i++)AC.insert(AddChange(i)),RC.insert(RevChange(i));
		ANS=0.0;
		while(T>0&&AC.begin()->dif>0.0)ModifyS(AC.begin()->id,1);
		for(int t,r;querycount--;)
		{
			scanf("%d%d",&t,&r),r--;
			if(t==1)ModifyL(r,1);
			else if(t==2)
			{
				if(S[r]>L[r]-1)ModifyS(r,-1);
				ModifyL(r,-1);
			}
			else assert(0);
			for(bool changed=true;changed;)
			{
				changed=false;
				if(T>0&&AC.begin()->dif>0.0)ModifyS(AC.begin()->id,1),changed=true;
				if(AC.begin()->dif+RC.begin()->dif>0.0)
				{
					const int a=RC.begin()->id,b=AC.begin()->id;
					ModifyS(a,-1),ModifyS(b,1);
					changed=true;
				}
			}
			printf("%.9f\n",ANS);
		}
	}
	return 0;
}
