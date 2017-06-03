#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
#include<set>
#include<utility>
using namespace std;
typedef long long LL;
const LL BASE=103,MOD=2147483647;
LL PS[2000000],POW[2000000];
LL Hash(const int l,const int r){return ((PS[r]-PS[l-1]*POW[r-l+1])%MOD+MOD)%MOD;}
int N;
int L[1000000];
char S[2000000];
int Solve()
{
//	puts(S+1);
	for(int i=1;i<N;++i)
	{
		int l=0,r=min(i-1,N*2-1-i);
		while(l<r)
		{
			const int mid=(l+r+1)/2;
			if(Hash(i-mid,i+mid)==Hash(N*2-i-mid,N*2-i+mid))l=mid;
			else r=mid-1;
		}
		L[i]=r;
	}
	vector<pair<int,int> >sot;
	for(int i=1;i<N;i++)sot.push_back(make_pair(i-L[i],i));
	sort(sot.begin(),sot.end());
	vector<int>z;
	for(int i=0;i<N/2;i++)if(Hash(1,1+i*2)==Hash(N*2-1-i*2,N*2-1))z.push_back(1+i*2);
	set<int>s;
	int ans=-1;
	for(int i=0,j=0;i<(int)z.size();++i)
	{
		for(;j<(int)sot.size()&&sot[j].first<=z[i]+1;++j)
		{
			s.insert(sot[j].second);
		}
		while(!s.empty()&&*s.begin()<=z[i])s.erase(s.begin());
		const int mx=((N-1)+(z[i]+1))/2;
		set<int>::iterator it=s.upper_bound(mx);
		if(it!=s.begin())
		{
			--it;
			const int ta=(*it)+((*it)-z[i]-1)-1;
			if(ta>ans)ans=ta;
		}
		if(z[i]>ans)ans=z[i];
//		printf("z[%d]=%d\n",i,z[i]);
	}
	assert(ans&1);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	static char str[1000001];
	scanf("%d%s",&N,str);
	S[1]=str[0];
	for(int i=1;i<N;++i)S[i*2]='z'+1,S[i*2+1]=str[i];
	PS[0]=0,POW[0]=1;
	for(int i=1;i<N*2;++i)PS[i]=(PS[i-1]*BASE+(S[i]-'a'))%MOD,POW[i]=POW[i-1]*BASE%MOD;
	printf("%d\n",(Solve()+1)/2);
	return 0;
}
