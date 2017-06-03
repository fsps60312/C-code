//#define SELF
#ifndef SELF
#include "lib1897.h"
#endif
#include<vector>
#include<algorithm>
#include<utility>
#include<cassert>
using namespace std;
int valid(int n, int *s)
{
	int dis=-1;
	vector<int>final;
	for(int i=0;i<n;i++)
	{
		if(s[i]<=n)
		{
			if(s[i]<1)return false;
			const int d=((i+1)-s[i]+n)%n;
			if(dis==-1)dis=d;
			else if(dis!=d)return 0;
		}
		else final.push_back(s[i]);
	}
	sort(final.begin(),final.end());
	for(int i=1;i<(int)final.size();i++)if(final[i-1]==final[i])return 0;
	return 1;
}
int replacement(int n, int *s,int *ans)
{
	assert(valid(n,s));
	vector<pair<int,int> >final;
	for(int i=0;i<n;i++)if(s[i]>n)final.push_back(make_pair(s[i],i));
	int dis=0;
	for(int i=0;i<n;i++)if(s[i]<=n){dis=(s[i]-(i+1)+n)%n;break;}
	for(int i=0;i<n;i++)s[i]=((i+1)+dis-1)%n+1;
	sort(final.begin(),final.end());
	int cur=n+1,j=-1;
	for(int i=0;i<(int)final.size();i++)
	{
		for(;cur<=final[i].first;cur++)
		{
			ans[++j]=s[final[i].second];
			s[final[i].second]=cur;
		}
	}
	vector<pair<int,int> >().swap(final);
	return ++j;
}
typedef long long LL;
const LL MOD=1e9+9;
LL Pow(LL a,LL p)
{
	LL ans=1LL;
	for(;p;p>>=1)
	{
		if(p&1LL)(ans*=a)%=MOD;
		(a*=a)%=MOD;
	}
	return ans;
}
int countReplacement(int n, int *s)
{
	if(!valid(n,s))return 0;
	vector<int>final;
	for(int i=0;i<n;i++)if(s[i]>n)final.push_back(s[i]);
	sort(final.begin(),final.end());
	int cur=n+1;
	LL ans=n;
	for(int i=0;i<n;i++)if(s[i]<=n){ans=1LL;break;}
	for(int i=0;i<(int)final.size();i++)
	{
		const int move=((final[i]-1)-cur)+1;
		cur=final[i]+1;
		(ans*=Pow(final.size()-i,move))%=MOD;
	}
	vector<int>().swap(final);
	return (int)ans;
}
#ifdef SELF
int main()
{
	printf("%d\n",valid(7,new int[7]{1,2,3,4,5,6,7}));
	printf("%d\n",valid(6,new int[6]{3,4,5,6,1,2}));
	printf("%d\n",valid(7,new int[7]{1,5,3,4,2,7,6}));
	printf("%d\n",valid(4,new int[4]{4,3,2,1}));
	printf("%d\n",valid(7,new int[7]{1,2,3,4,5,6,5}));
	printf("%d\n",valid(7,new int[7]{2,3,4,9,6,7,1}));
	printf("%d\n",valid(5,new int[5]{10,4,3,11,12}));
	
	int ans[7],n;
	n=replacement(3,new int[3]{3,1,4},ans);
	for(int i=0;i<n;i++)printf(" %d",ans[i]);puts("");
	n=replacement(5,new int[5]{5,1,2,3,4},ans);
	for(int i=0;i<n;i++)printf(" %d",ans[i]);puts("");
	n=replacement(7,new int[7]{2,3,4,9,6,7,1},ans);
	for(int i=0;i<n;i++)printf(" %d",ans[i]);puts("");
	
	printf("%d\n",countReplacement(4,new int[4]{1,2,7,6}));
	printf("%d\n",countReplacement(7,new int[7]{2,3,4,12,6,7,1}));
	printf("%d\n",countReplacement(4,new int[4]{4,7,4,7}));
	printf("%d\n",countReplacement(2,new int[2]{3,4}));
	return 0;
}
#endif
