#include<bits/stdc++.h>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
int N;
map<int,int>S;
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		S.clear();
		for(int i=0,x,y;i<N;i++)
		{
			scanf("%d%d",&x,&y);
			getmax(S[x],y),getmax(S[y],x);
		}
		int ans=0;
		for(const auto &p:S)ans+=p.second;
		printf("%d\n",ans);
	}
	return 0;
}
