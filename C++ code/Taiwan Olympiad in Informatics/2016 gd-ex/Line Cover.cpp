#include<bits/stdc++.h>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
int N;
vector<pair<int,int> >S;
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
			assert(x<=y);
			if(x>y)swap(x,y);
			S.push_back(make_pair(x,y));
		}
		sort(S.begin(),S.end());
		pair<int,int>now=S[0];
		int ans=0;
		for(int i=1;i<N;i++)
		{
			if(S[i].first<=now.second)getmax(now.second,S[i].second);
			else ans+=now.second-now.first,now=S[i];
		}
		ans+=now.second-now.first;
		printf("%d\n",ans);
	}
	return 0;
}
