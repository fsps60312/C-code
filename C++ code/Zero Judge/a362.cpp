#include<cstdio>
#include<algorithm>
using namespace std;
int N;
struct Statue
{
	int h,w,i,pri;
	bool operator<(const Statue &s)const
	{
		if(h!=s.h)return h<s.h;
		if(w!=s.w)return w<s.w;
		return i<s.i;
	}
}STATUE[10000];
bool Cmpi(const Statue &a,const Statue &b){return a.i<b.i;}
//struct Bit
//{
//	int s[10001];
//	void clear(){for(int i=1;i<=N;i++)s[i]=0;}
//	int lowbit(const int i){return i&(-i);}
//	void Add(int i){while(i<=N)s[i]++,i+=lowbit(i);}
//	int Query(int i){while(i)ans+=s[i],i-=lowbit(i);}
//}
int main()
{
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		Statue &s=STATUE[i];
		scanf("%d%d",&s.h,&s.w);
		s.i=i;
	}
	sort(STATUE,STATUE+N);
	for(int i=0;i<N;i++)STATUE[i].pri=i;
	sort(STATUE,STATUE+N,Cmpi);
	int ans=0;
	for(int i=0;i<N;i++)
	{
		ans+=abs(STATUE[i].pri-i);
	}
	printf("%d\n",ans);
	return 0;
}
