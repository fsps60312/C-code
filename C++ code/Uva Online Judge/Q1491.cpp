#include<cstdio>
void termin(){int a[9];for(int i=0;;i--)a[i]=9;}
int N,L[4];
char S[501];
int DP[256][256][4];
bool Same(int i1,int i2,int l)
{
	for(int i=0;i<l;i++)if(S[i1+i]!=S[i2+i])return false;
	return true;
}
int CanSplit(int l,int r,int dep)
{
	if(dep>=N)
	{
		printf("error %d %d %d\n",l,r,dep);
		termin();
	}
	int &ans=DP[l][r][dep];
	if(ans!=-1)return ans;
	if(r-l+1<=L[dep])return ans=true;
	if(dep==N-1)return ans=false;
	if(L[dep]==1)return ans=CanSplit(l,r,dep+1);
	if(L[dep]>=2)
	{
		if((r-l+1)&1==0)
		{
			int mid=(l+r)/2;
			int d=dep+1;
			if(Same(l,mid+1,mid-l+1)
			&&CanSplit(l,mid,dep+1)
			&&CanSplit(mid+1,r,dep+1))return ans=true;
		}
		if(dep+2<N)
		{
			for(int i=l;i<r;i++)
			{
				if(CanSplit(l,i,dep+2)&&CanSplit(i+1,r,dep+2))return ans=true;
			}
		}
	}
	if(L[dep]>=3)
	{
		if(!(r-l+1)%3)
		{
			int dis=(r-l+1)/3;
			if(Same(l,l+dis,dis)&&Same(l,l+dis*2,dis)
			&&CanSplit(l,l+dis-1,dep+1)
			&&CanSplit(l+dis,l+dis*2-1,dep+1)
			&&CanSplit(l+dis*2,r,dep+1))return ans=true;
		}
		int mid=(l+r)/2;
		int d=dep+1;
		if(!Same(l,mid+1,mid-l))d++;
		if(CanSplit(l,mid-1,d)&&CanSplit(mid+1,r,d))return ans=true;
	}
}
bool check1(int n)
{
	int t=0;
	for(int i=0;i<N;i++)
	{
		t+=L[i];
		if(t>=n)return true;
		t--;
	}
	return false;
}
bool check2(int n)
{
	int t=1;
	for(int i=0;i<N;i++)t+=L[i]-1;
	int cnt[26];
	for(int i=0;i<26;i++)cnt[i]=0;
	for(int i=0;i<n;i++)
	{
		int &c=cnt[S[i]-'a'];
		if(!c)
		{
			t--;
			if(t<0)return false;
		}
		c++;
	}
	return true;
}
bool solve()
{
	int n=-1;while(S[++n]);
	if(n>256)return false;
	if(check1(n))return true;
	if(!check2(n))return false;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			for(int k=0;k<N;k++)
				DP[i][j][k]=-1;
	return CanSplit(0,n-1,0);
}
int main()
{
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)
		{
			scanf("%d",&L[i]);
		}
		scanf("%s",S);
		printf(solve()?"Yes\n":"No\n");
	}
	return 0;
}
