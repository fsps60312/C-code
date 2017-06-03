#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
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
void ReadInput()
{
	A[0]=0,EQ[0]=1;
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
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		ReadInput();
		int ans=0;
		for(int i=0;i<=N;i++)printf("%d ",A[i]);puts("");
		for(int i=1,j=0;i<=N;)
		{
			printf("(%c,%d)\n",S[j].type,S[j].cnt);
			assert(j+1<(int)S.size());
			assert(S[j].type!='=');
			static int dp[500000];
			dp[0]=i-1;
			for(int len=1;;i++)
			{
				if(i>N){ans+=min((len+1)-1,S[j].cnt),printf("end %c\n",S[j].type);break;}
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
				printf("i=%d,r=%d\n",i,r);
				PRE[i]=dp[r];
				dp[r]=i;
				if(r==len)len++;
				if(S[j+1].type=='=')
				{
					if(r+1==S[j].cnt+1&&EQ[i]>=S[j+1].cnt+1)
					{
						printf("%d~",i);
						ans+=S[j].cnt+S[j+1].cnt,i+=EQ[i],j+=2;
						printf("%d: %c %c\n",i,S[j-2].type,'=');
						printf("ans=%d\n",ans);
						break;
					}
				}
				else
				{
					printf("r+1=%d,S[j].cnt+1=%d\n",r+1,S[j].cnt+1);
					if(r+1==S[j].cnt+1)
					{
						ans+=S[j].cnt,i++,j++;
						printf("%d: %c\n",i,S[j-1].type);
						printf("ans=%d\n",ans);
						break;
					}
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
