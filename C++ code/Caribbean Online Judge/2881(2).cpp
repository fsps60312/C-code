#include<cstdio>
#include<cassert>
#include<utility>
using namespace std;
int N,TO[300001];
struct Stack
{
	int s[600000],sz;
	void clear(){sz=0;}
	void push_back(const int v){s[sz++]=v;}
	int size()const{return sz;}
	int back()const{return s[sz-1];}
	int operator[](const int i)const{return s[i];}
}ANS,STK;
struct DoubleStack
{
	Stack stk1,stk2;
	void clear(){stk1.clear(),stk2.clear();}
	void push_back(const int v1,const int v2){stk1.push_back(v1),stk2.push_back(v2);}
	int size()const{return stk1.size();}
	int first(const int i)const{return stk1[i];}
	int second(const int i)const{return stk2[i];}
}QUERY;
int To(const int a)
{
	int cur=a;
	STK.clear();
	while(TO[cur]!=cur)STK.push_back(cur),cur=TO[cur];
	for(int i=STK.size()-1;i>=0;i--)TO[STK[i]]=cur;
	return cur;
}
int main()
{
//	assert(0);
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=1;i<=N;i++)
		{
			scanf("%d",&TO[i]);
			if(!TO[i])TO[i]=i;
		}
		TO[0]=0;
		QUERY.clear();
		int querycount;scanf("%d",&querycount);
		for(int i=0,type,x;i<querycount;i++)
		{
			scanf("%d%d",&type,&x);
			if(type==1)QUERY.push_back(-1,x);
			else if(type==2)QUERY.push_back(x,TO[x]),TO[x]=x;
			else assert(0);
		}
		for(int i=1;i<=N;i++)if(TO[i]!=i)QUERY.push_back(i,TO[i]),TO[i]=i;
		ANS.clear();
		for(int i=QUERY.size()-1;i>=0;i--)
		{
			const int a=QUERY.first(i),b=QUERY.second(i);
			if(a==-1)
			{
				assert(i<querycount);
				ANS.push_back(To(b));
			}
			else
			{
				assert(a!=b&&TO[a]==a);
				if(To(b)==a)TO[a]=0;
				else TO[a]=b;
			}
		}
		for(int i=ANS.size()-1;i>=0;i--)
		{
			if(ANS[i]==0)puts("CIKLUS");
			else printf("%d\n",ANS[i]);
		}
//		break;
	}
	return 0;
}
