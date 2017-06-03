#include<cstdio>
#include<cassert>
#include<cmath>
#include<queue>
using namespace std;
int N;
double S[100];
struct Pq
{
	double p;
	int t;
	Pq(const double _p,const int _t):p(_p),t(_t){}
	double Guessed()const{return 1.0-pow(1.0-p,t);}
	bool operator<(const Pq &o)const{return Guessed()>o.Guessed();}
};
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%lf",&S[i]),S[i]*=0.01;
		priority_queue<Pq>pq;
		double now=1.0;
		for(int i=0;i<N;i++)
		{
			const Pq p=Pq(S[i],1);
			now*=p.Guessed();
			pq.push(p);
		}
		double ans=N*now;
		for(int i=N+1;i<1000000;i++)
		{
			Pq p=pq.top();pq.pop();
			const double pre=now;
			now/=p.Guessed();
			p.t++;
			now*=p.Guessed();
			pq.push(p);
			ans+=i*(now-pre);
		}
		printf("%.9f\n",ans);
	}
	return 0;
}
