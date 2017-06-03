#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int T,S,M,L,R;
int ANS;
void check(int v)
{
	for(int i=0;i<S;i++)
	{
		if(v%(S-1))return;
		v=v*S/(S-1)+M;
	}
	ANS++;
}
int solve()
{
	int l=L,r=R;
	for(int i=0;i<S;i++)
	{
		if(l>=M&&(l-M)%S)l=((l-M)/S+1)*S+M;
		if(l>=M)l=(l-M)*(S-1)/S;
		else l=0;
		if(r>=M)r=(r-M)*(S-1)/S;
		else r=0;
	}
	if(l%S)l+=S;
	l=l/S*S;
	if(!l)l+=S;
	ANS=0;
	if(!M&&!l)
	{
		if(!L)ANS++;
		l=1;
	}
//	printf("%d %d\n",l,r);
	for(int i=l;i<=r;i+=S)check(i);
	return ANS;
}
int main()
{
//	freopen("inn.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	scanf("%d",&T);
	int kase=1;
	while(T--)
	{
		scanf("%d%d%d%d",&S,&M,&L,&R);
		printf("Case %d: %d\n",kase++,solve());//break;
	}
}
