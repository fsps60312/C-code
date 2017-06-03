#include<cstdio>
#include<cstdlib>
#include<set>
using namespace std;
multiset<int> S;
int n;
int main()
{
	while(scanf("%d",&n)==1&&n)
	{
		S.clear();
		int ans=0;
		for(int i=0,j,k;i<n;i++)
		{
			scanf("%d",&k);
			while(k--)
			{
				scanf("%d",&j);
				S.insert(j);
			}
			multiset<int>::iterator a,b;
			a=S.begin(),b=S.end();
			b--;
			//printf("%d %d\n",*b,*a);
			ans+=(*b)-(*a);
			S.erase(b),S.erase(S.begin());
		}
		printf("%d\n",ans);
	}
	return 0;
}
