#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
struct Query
{
	int x,z,h,id;
	Query(){}
	Query(const int _x,const int _z,const int _h,const int _id):x(_x),z(_z),h(_h),id(_id){}
};
bool operator<(const Query &a,const Query &b){return a.x<b.x;}
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int testcount;scanf("%d",&testcount);
	vector<Query>queries[21];
	static double answers[1000];
	for(int i=0;i<testcount;i++)answers[i]=0.0;
	for(int testId=0;testId<testcount;testId++)
	{
		int h,s;
		scanf("%d%d",&h,&s);
		for(int i=0;i<s;i++)
		{
			static char str[100];
			scanf("%s",str);
			int x,y,z;
			if(sscanf(str,"%dd%d%d",&x,&y,&z)!=3)z=0;
//			printf("(%d,%d,%d)\n",x,y,z);
			queries[y].push_back(Query(x,z,h,testId));
		}
	}
	for(int y=0;y<=20;y++)if(!queries[y].empty())
	{
//		printf("y=%d\n",y);
		assert(y==4||y==6||y==8||y==10||y==12||y==20);
		sort(queries[y].begin(),queries[y].end());
		auto q=queries[y].begin();
		static double dp[2][10001];
		for(int i=0;i<=10000;i++)dp[0][i]=0.0;
		dp[0][0]=1.0;
		for(int x=1,d=1;x<=10000;x++,d^=1)
		{
			for(int i=0;i<=10000;i++)dp[d][i]=0.0;
			{
				double v=0.0;
				for(int i=1;i<=10000;i++)
				{
					v+=dp[d^1][i-1]/y;
					if(i-y-1>=0)v-=dp[d^1][i-y-1]/y;
					dp[d][i]+=v;
				}
			}
			static double p[10002];
			for(int i=0;i<=10001;i++)p[i]=0;
			for(int j=10000;j>=0;j--)p[j]=p[j+1]+dp[d][j];
			for(;q!=queries[y].end()&&q->x==x;q++)
			{
				const int required=min(10001,max(0,(q->h)-(q->z)));
				if(p[required]>answers[q->id])answers[q->id]=p[required];
			}
		}
		assert(q==queries[y].end());
	}
	for(int i=0;i<testcount;i++)printf("Case #%d: %.6f\n",i+1,answers[i]);
	return 0;
}
