#include<cstdio>
#include<cassert>
#include<queue>
using namespace std;
int N,M,R[100],W[2000];
int PARK[100];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)assert(scanf("%d",&R[i])==1),PARK[i]=0;
		for(int i=0;i<M;i++)assert(scanf("%d",&W[i])==1);
		queue<int>q;
		int ans=0;
		for(int i=0,e;i<2*M;i++)
		{
			assert(scanf("%d",&e)==1);
			if(e>0)
			{
				int found=-1;
				for(int i=0;i<N;i++)if(!PARK[i]){found=i;break;}
				if(found==-1)q.push(e);
				else PARK[found]=e,ans+=W[e-1]*R[found];
			}
			else
			{
				e=-e;
				int found=-1;
				for(int i=0;i<N;i++)if(PARK[i]==e){found=i;break;}
				assert(found!=-1);
				if(q.empty())PARK[found]=0;
				else ans+=W[(PARK[found]=q.front())-1]*R[found],q.pop();
			}
//			printf("now %d\n",ans);
		}
		assert(q.empty());
		printf("%d\n",ans);
		break;
	}
	return 0;
}
