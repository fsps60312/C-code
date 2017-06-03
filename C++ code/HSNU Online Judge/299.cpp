#include<cstdio>
#include<map>
#include<vector>
#include<cassert>
using namespace std;
struct Bit
{
	vector<int>s;
	int n;
	Bit(){}
	Bit(const int _n):n(_n){s.clear(),s.resize(n+1,0);}
	void Add(int i,const int v)
	{
		i=(i%n+n)%n+1;
		while(i<=n)s[i]+=v,i+=(i&(-i));
	}
	int Query(int i)
	{
		assert(0<=i&&i<n);i++;
		int ans=0;
		while(i)ans+=s[i],i-=(i&(-i));
		return ans;
	}
	int QueryAns(int dis)
	{
		assert(dis>=0),dis%=n;
		if(dis<n/2)return Query(n-1-dis)-Query(n/2-dis-1);
		else return Query(n-1-dis)+(Query(n-1)-Query(n+n/2-dis-1));
	}
}BIT[16];
int N,ADD;
map<int,int>S;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	ADD=0,S.clear();
	for(int i=0;i<=15;i++)BIT[i]=Bit(1<<(i+1));
	for(int i=0,val;i<N;i++)
	{
		static char tmp[7];
		scanf("%s%d",tmp,&val);
//		printf("%s %d\n",tmp,val);
		switch(tmp[0])
		{
			case'A':ADD+=val;break;
			case'D':
			{
				const auto it=S.find(val-ADD);
				if(it==S.end())break;
				for(int i=0;i<=15;i++)BIT[i].Add(val-ADD,-(it->second));
				S.erase(it);
			}break;
			case'I':
			{
				for(int i=0;i<=15;i++)BIT[i].Add(val-ADD,1);
				S[val-ADD]++;
			}break;
			case'Q':printf("%d\n",BIT[val].QueryAns(ADD));break;
			default:assert(0);break;
		}
	}
	return 0;
}
