#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
struct Strip
{
	int C,X,Y,W,H;
}S[1200];
int W,H,N;
vector<int>X,Y;
map<int,vector<pair<int,pair<int,int> > > >TAG[2000];//time, end, color
int Id(const vector<int>&s,const int v)
{
	const int ans=lower_bound(s.begin(),s.end(),v)-s.begin();
	assert(s[ans]==v);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d%d",&W,&H,&N);
		X.clear(),Y.clear();
		X.push_back(0),X.push_back(W),Y.push_back(0),Y.push_back(H);
		for(int i=0;i<N;i++)
		{
			scanf("%d%d%d%d%d",&S[i].C,&S[i].X,&S[i].Y,&S[i].W,&S[i].H);
			X.push_back(S[i].X),X.push_back(S[i].X+S[i].W);
			Y.push_back(S[i].Y),Y.push_back(S[i].Y+S[i].H);
		}
		sort(X.begin(),X.end()),sort(Y.begin(),Y.end());
		X.resize(unique(X.begin(),X.end())-X.begin());
		Y.resize(unique(Y.begin(),Y.end())-Y.begin());
		for(int i=0;i<N;i++)
		{
			S[i].W=Id(X,S[i].X+S[i].W);
			S[i].X=Id(X,S[i].X);
			S[i].H=Id(Y,S[i].Y+S[i].H);
			S[i].Y=Id(Y,S[i].Y);
		}
		for(int i=0;i+1<(int)Y.size();i++)TAG[i].clear();
		for(int i=0;i<N;i++)
		{
			for(int y=S[i].Y;y<S[i].H;y++)
			{
				TAG[y][S[i].X].push_back(make_pair(i,make_pair(S[i].W,S[i].C)));
//				printf("color=%d,y=%d,x=(%d,%d)\n",S[i].C,Y[y],X[S[i].X],X[S[i].W]);
			}
		}
		static long long ans[11];
		for(int i=0;i<=10;i++)ans[i]=0LL;
		for(int y=0;y+1<(int)Y.size();y++)
		{
			const long long cnt=Y[y+1]-Y[y];
			map<int,pair<int,int> >s;//time,length,color
			auto it=TAG[y].begin();
			for(int x=0;x+1<(int)X.size();x++)
			{
				while(!s.empty()&&s.rbegin()->second.first<=x)s.erase(prev(s.end()));
				assert(it==TAG[y].end()||it->first>=x);
				if(it!=TAG[y].end()&&it->first==x)
				{
					for(const auto &p:it->second)
					{
						assert(s.find(p.first)==s.end());
						auto iu=s.upper_bound(p.first);//check whether later strip cover this
//						printf("t=%d,x=%d,color=%d\n",p.first,X[p.second.first],p.second.second);
						if(iu!=s.end()&&iu->second.first>=p.second.first)continue;
						else
						{
							iu=s.upper_bound(p.first);
							if(iu!=s.begin())
							{
								iu--;//check which strip covered by this
								for(;p.second.first>=iu->second.first;)
								{
									if(iu==s.begin()){s.erase(iu);break;}
									else s.erase(iu--);
								}
							}
							s[p.first]=p.second;
						}
//						puts("pass");
					}
					it++;
				}
				assert(s.empty()||s.rbegin()->second.first>x);
				const int color=(s.empty()?0:prev(s.end())->second.second);
				ans[color]+=cnt*(X[x+1]-X[x]);
//				printf("color=%d,y=(%d,%d),x=(%d,%d)\n",color,Y[y],Y[y+1],X[x],X[x+1]);
//				printf("y=%d,x=%d,color=%d, %d\n",Y[y],x,color,s.empty()?-1:prev(s.end())->second.first);
//				for(const auto &p:s)printf("(%d,(%d,%d))",p.first,X[p.second.first],p.second.second);puts("");
			}
			assert(it==TAG[y].end());
		}
		static int kase=0;
		printf("Case %d:\n",++kase);
		for(int i=0;i<=10;i++)if(ans[i])
		{
			printf("%d %lld\n",i,ans[i]);
		}
	}
	return 0;
}
