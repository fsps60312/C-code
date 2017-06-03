#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
int N,K,A[500001],PRE[500001],PRE_SAME[500001];
vector<int>STK[1000001];
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
	A[0]=0;
	for(int i=1;i<=N;i++)scanf("%d",&A[i]);
	for(int i=0;i<=1000000;i++)STK[i].clear();
	for(int i=0;i<=N;i++)PRE[i]=PRE_SAME[i]=INF;
	for(int i=N;i>=0;i--)
	{
		vector<int>&s=STK[A[i]];
		if(!s.empty())PRE_SAME[s.back()]=i;
		s.push_back(i);
	}
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
int Search(const int *dp,const int len,const char type,const int i)
{
	STK[A[i]].pop_back();
	int l=0,r=len;
	while(l<r)
	{
		if(type=='<')
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
	return r;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		ReadInput();
		int ans=0;
//		for(int i=0;i<=N;i++)printf("%d ",A[i]);puts("");
		int last=0;
		for(int i=1,j=0;i<=N;)
		{
//			printf("(%c,%d)\n",S[j].type,S[j].cnt);
			assert(j+1<(int)S.size());
			assert(S[j].type!='=');
			static int dp[500000];
			dp[0]=i-1;
			if(S[j+1].type=='=')
			{
//				puts("enter: =");
				bool found=false;
				for(int len=1,back=N+1;;i++)
				{
					if(i>N){ans+=min((len+1)-1,S[j].cnt);break;}
					if(i==back)
					{
						ans+=S[j].cnt+S[j+1].cnt,j+=2;
						PRE[back-1]=-S[j+1].cnt;
						break;
					}
					const int result=Search(dp,len,S[j].type,i);
//					printf("i=%d,result=%d\n",i,result);
					if(result)PRE[i]=dp[result-1];
					else PRE[i]=PRE[dp[0]];
					dp[result]=i;
					if(result==len)
					{
						if(!found)last=i;
						len++;
					}
					if(result+1==S[j].cnt+1&&(int)STK[A[i]].size()>=S[j+1].cnt)
					{
						getmin(back,STK[A[i]][(int)STK[A[i]].size()-S[j+1].cnt]+1);
						found=true,last=back-1;
					}
				}
			}
			else
			{
//				puts("enter: ><");
				for(int len=1;;i++)
				{
					if(i>N){ans+=min((len+1)-1,S[j].cnt);break;}
					const int result=Search(dp,len,S[j].type,i);
//					printf("i=%d,result=%d\n",i,result);
					if(result)PRE[i]=dp[result-1];
					else PRE[i]=PRE[dp[0]];
					dp[result]=i;
					if(result==len)last=i,len++;
//					printf("result+1=%d,S[j].cnt+1=%d\n",result+1,S[j].cnt+1);
					if(result+1==S[j].cnt+1)
					{
						ans+=S[j].cnt,i++,j++;
//						printf("%d: %c\n",i,S[j-1].type);
//						printf("ans=%d\n",ans);
						break;
					}
				}
			}
		}
		printf("%d\n",ans);
		vector<int>s;
		for(;last!=INF;)
		{
			if(PRE[last]<0)
			{
				for(int i=0;i>PRE[last];i--)s.push_back(A[last]),last=PRE_SAME[last];
			}
			else s.push_back(A[last]),last=PRE[last];
		}
		reverse(s.begin(),s.end());
		vector<char>sign;
		for(int i=0,j=0,k=0;i<ans;i++)
		{
			if(S[j].cnt==k)j++,k=0;
			sign.push_back(S[j].type),k++;
		}
//		puts(&sign[0]);
		static int buf[500000];
		for(int i=1,j=-1;i<(int)s.size();i++)
		{
			bool fit=(j+1<(int)sign.size());
			if(fit)
			{
				switch(sign[j+1])
				{
					case'<':fit=(s[i-1]<s[i]);break;
					case'=':fit=(s[i-1]==s[i]);break;
					case'>':fit=(s[i-1]>s[i]);break;
					default:assert(0);break;
				}
			}
			if(fit)j++;
			buf[j]=s[i];
//			printf("j=%d,s[%d]=%d\n",j,i,s[i]);
		}
		for(int i=0;i<ans;i++)
		{
			if(i)putchar(' ');
			printf("%d",buf[i]);
		}
		puts("");
	}
	return 0;
}
