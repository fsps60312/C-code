#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int T,S,M,L,R;
vector<int> ANS;
bool check(int v)
{
	for(int i=0;v<=R&&i<=S;i++)
	{
		if(i>=S&&v>=L)ANS.push_back(v);
		if(v%(S-1))return i>=S&&i>=L;
		v=v*S/(S-1)+M;
	}
}
int solve()
{
	int l=L,r=R;
	for(int i=0;i<S;i++)
	{
		l=(l-M)*(S-1)/S;
		r=(r-M)*(S-1)/S;
	}
//	printf("l=%d r=%d\n",l,r);
	if(l<0)l=0;
	if(!M&&!l)l=1;
	l=(l+S-1)/S*S;
	r=r/S*S;
	for(int i=l;i<=r;i+=S)
	{
		check(i);
//		printf(" %d",i);
	}//printf("check\n");
	sort(ANS.begin(),ANS.end());
	int ans=ANS.size();
	for(int i=1;i<ANS.size();i++)if(ANS[i-1]==ANS[i])ans--;
//	for(int i=0;i<j;i++)printf(" %d",ANS[i]);
	for(int i=0;i<ANS.size();i++)
	{
		if(i==0||ANS[i-1]!=ANS[i])printf(" %d",ANS[i]);
	}
	printf("pass\n");
	return ANS.size();
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	int kase=1;
	while(T--)
	{
		scanf("%d%d%d%d",&S,&M,&L,&R);
		ANS.clear();
		printf("Case %d: %d\n",kase++,solve());//break;
	}
}
