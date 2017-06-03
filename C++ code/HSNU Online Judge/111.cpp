#include<cstdio>
#include<set>
using namespace std;
typedef long long LL;
int T,N;
set<int>X,Y;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		X.clear(),Y.clear();
		LL ans=0LL;
		for(int i=0,x,y;i<N;i++)
		{
			scanf("%d%d",&x,&y);
			auto xit=X.find(x),yit=Y.find(y);
			if(xit!=X.end()&&yit!=Y.end())ans--;
			else
			{
				if(xit==X.end())
				{
					if(yit==Y.end())ans+=Y.size();
					else ans+=Y.size()-1;
				}
				if(yit==Y.end())
				{
					if(xit==X.end())ans+=X.size();
					else ans+=X.size()-1;
				}
				X.insert(x),Y.insert(y);
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
