#include<cstdio>
#include<cassert>
using namespace std;
//void assert(bool valid){if(valid)return;for(int a=0,b=0;;)a/=b;}
struct Djset
{
	int s[150000];
	void clear(const int n){for(int i=0;i<n;i++)s[i]=i;}
	int find(const int a){return s[a]==a?a:(s[a]=find(s[a]));}
	bool merge(int a,int b){if((a=find(a))==(b=find(b)))return false;s[a]=b;return true;}
	int operator[](const int i){return find(i);}
}DJ;
int N,K;
int main()
{
	while(scanf("%d%d",&N,&K)==2)
	{
		DJ.clear(N*3);
		int ans=0;
		for(int i=0,d,a,b;i<K;i++)
		{
			scanf("%d%d%d",&d,&a,&b),a--,b--;
			assert(a>=0&&b>=0);
			if(a>=N||b>=N)ans++;
			else if(d==1)
			{
				if(DJ[a]==DJ[N+b]||DJ[a]==DJ[N+N+b])ans++;
				else for(int j=0;j<3;j++)DJ.merge(N*j+a,N*j+b);
			}
			else if(d==2)
			{
				if(DJ[a]==DJ[b]||DJ[a]==DJ[N+N+b])ans++;
				else for(int j=0;j<3;j++)DJ.merge(N*j+a,N*((j+1)%3)+b);
			}
			else assert(0);
		}
		printf("%d\n",ans);
		break;
	}
	return 0;
}
