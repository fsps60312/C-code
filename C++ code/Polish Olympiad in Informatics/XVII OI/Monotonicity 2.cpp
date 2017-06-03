#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
const int INF=2147483647;
int N,K,A[500001],PRE[500001];
int EQ[500001];
struct Sign
{
	char type;
	int cnt;
	Sign(){}
	Sign(const char _t,const int _c):type(_t),cnt(_c){}
};
vector<Sign>S;
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		A[0]=-INF,EQ[0]=1;
		for(int i=1;i<=N;i++)scanf("%d",&A[i]),EQ[i]=1;
		for(int i=N-1;i>=0;i--)if(A[i]==A[i+1])EQ[i]+=EQ[i+1];
		if(true)
		{
			static char cs[1000001];
			cs[0]='<';
			for(int i=1;i<=K;i++)
			{
				static char tmp[2];scanf("%s",tmp);
				cs[i]=tmp[0];
			}
			for(int i=K+1;i<=N*2;i++)cs[i]=cs[(i-1)%K+1];
			S.clear();
			for(int i=0;i<=N*2;i++)
			{
				assert(cs[i]=='<'||cs[i]=='='||cs[i]=='>');
				if(S.empty()||S.back().type!=cs[i])S.push_back(Sign(cs[i],1));
				else S.back().cnt++;
			}
		}
		int ans=0;
		int last=INF;
		for(int i=0,j=0;i<=N;j++)
		{
			assert(j+1<(int)S.size());
			assert(S[j].type!='=');
			for(int len=0;;i++)
			{
				if(i>N){ans+=(len+1)-1;break;}
				if(S[j].type=='<')
				{
					if(j>0&&S[j-1].type=='=')
					{
						
					}
					else
					{
						if()
					}
				}
				else
				{
				}
				static int dp[500000];
				int l=0,r=len;
				while(l<r)
				{
					if(S[j].type=='<')
					{
						const int mid=(l+r)/2;
						if(A[i]>A[dp[mid]])l=mid+1;
						else r=mid;
					}
					else
					{
						const int mid=(l+r)/2;
						if(A[i]<A[dp[mid]])l=mid+1;
						else r=mid;
					}
				}
				PRE[i]=dp[r];
				dp[r]=i;
				if(r==len)len++;
				if(S[j+1].type=='=')
				{
					if(r+1==S[j].cnt+1&&EQ[i]>=S[j+1].cnt+1){j+=2,ans+=r,i+=EQ[i]-1;break;}
				}
				else
				{
					if(r+1>=S[j].cnt){ans+=r,i++;break;}
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
