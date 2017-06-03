#include<stdio.h>
inline void assert(bool valid){if(valid)return;int a=0,b=0;a/=b;}
int N,TO[300001];
struct Stack
{
	int s[600000],sz;
	inline void clear(){sz=0;}
	inline void push_back(const int v){assert(sz<600000);s[sz++]=v;}
	inline int size()const{return sz;}
	inline int operator[](const int i)const{return s[i];}
}ANS,STK;
struct DoubleStack
{
	Stack stk1,stk2;
	inline void clear(){stk1.clear(),stk2.clear();}
	inline void push_back(const int v1,const int v2){stk1.push_back(v1),stk2.push_back(v2);}
	inline int size()const{return stk1.size();}
	inline int first(const int i)const{return stk1[i];}
	inline int second(const int i)const{return stk2[i];}
}QUERY;
inline int To(const int a)
{
	int cur=a;
	STK.clear();
	while(TO[cur]!=cur)STK.push_back(cur),cur=TO[cur];
	for(int i=STK.size()-1;i>=0;i--)TO[STK[i]]=cur;
	return cur;
}
inline void GetInt(int &v)
{
	const static int ZERO='0',NINE='9';
	static int c;c=getchar();
	while(c<ZERO||c>NINE)c=getchar(),assert(c!=EOF);
	v=0;
	while(ZERO<=c&&c<=NINE)v=v*10+(c-ZERO),c=getchar();
}
int main()
{
//	assert(0);
//	freopen("in.txt","r",stdin);
//	freopen("kuglice\\kuglice.in.10","r",stdin);
//	freopen("out.txt","w",stdout);
//	for(;;)
//	{
		GetInt(N);
		assert(N<=300000);
		for(int i=1;i<=N;i++)
		{
			GetInt(TO[i]);
			if(!TO[i])TO[i]=i;
			else assert(1<=TO[i]&&TO[i]<=N);
		}
		TO[0]=0;
		QUERY.clear();
		int querycount;GetInt(querycount);
		for(int i=0,type,x;i<querycount;i++)
		{
			GetInt(type),GetInt(x);
			assert(1<=x&&x<=N);
			if(type==1)QUERY.push_back(-1,x);
			else if(type==2)assert(TO[x]!=x),QUERY.push_back(x,TO[x]),TO[x]=x;
			else assert(0);
		}
		for(int i=1;i<=N;i++)if(TO[i]!=i)QUERY.push_back(i,TO[i]),TO[i]=i;
		assert(QUERY.size()<=600000);
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
//	}
	return 0;
}
