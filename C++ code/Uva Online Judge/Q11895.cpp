#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long LL;
LL Gcd(const LL &a,const LL &b){return b==0LL?a:Gcd(b,a%b);}
struct Bag
{
	LL up,down,cnt;
	Bag(){}
	Bag(const LL &_up,const LL &_down,const LL &_cnt):up(_up),down(_down),cnt(_cnt){}
	bool operator<(const Bag &a)const{return (double)up*a.down*a.cnt<(double)a.up*down*cnt;}
};
int N,K;
int main()
{
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&K);
		priority_queue<Bag>pq;
		for(int i=0;i<N;i++)
		{
			static Bag b;
			scanf("%lld%lld",&b.cnt,&b.up);
			b.down=1LL;
			pq.push(b);
		}
		for(int i=1;i<K;i++)
		{
			const Bag b=pq.top();pq.pop();
//			printf("%lld/%lld %lld\n",b.up,b.down,b.cnt);
			//b.f-=b.f/b.cnt
			//(b.up*b.cnt)/(b.down*b.cnt)-b.up/(b.down*b.cnt)
			const LL up=b.up*(b.cnt-1LL),down=b.down*b.cnt,g=Gcd(up,down);
			pq.push(Bag(up/g,down/g,b.cnt));
		}
		const Bag b=pq.top();
		const LL up=b.up,down=b.down*b.cnt,g=Gcd(up,down);
		printf("%lld/%lld\n",up/g,down/g);
	}
	return 0;
}
