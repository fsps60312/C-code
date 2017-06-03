#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
//int Sks(const int n)
//{
//	int ans=0;
//	int d=0;
//	while((1<<(d+1))<=n)d++;
//	if(d==0)return 1;
//	ans+=(1<<d)-(d-1);
//	if(n&(1<<(d-1)))ans+=(1<<(d-1))-1;
//	else ans+=n&((1<<(d-1))-1);
////	printf("ans=%d\n",ans);
//	for(int i=d-2,v=0;i>=0;i--)
//	{
//		if((n&((1<<(i+2))-1))>=(1<<i))ans+=v+1;
//		else ans+=v;
//		v=(v<<1)+((n>>(i+1))&1);
//	}
//	return ans;
//}
int N,S[1000000],LOC[1000000];
int GetSum(){int ans=0;for(int i=0;i<N;i++)ans+=S[i];return ans;}
typedef long long LL;
int main()
{
//	freopen("jed10a.in","r",stdin);
//	freopen("out.txt","w",stdout);
	for(;scanf("%d",&N)==1;)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		const int sum=GetSum();
		if(sum==1){printf("1\n1\n");continue;}
		assert(sum>=2);
		vector<vector<int> >anses;
		LL adjust=0LL;
		if(true)
		{
			vector<int>s;
			s.push_back(1);
			s.push_back(sum-1);
			anses.push_back(s);
			adjust-=(sum-2);
			vector<int>().swap(s);
		}
		if(S[0]>=2)
		{
			if(sum>2)
			{
				vector<int>s;
				s.push_back(sum-2);
				anses.push_back(s);
				vector<int>().swap(s);
			}
		}
		else
		{
			assert(S[0]==1);
			if(2<N)
			{
				vector<int>s;
				for(int i=2;i<N;i++)s.push_back(S[i]);
				anses.push_back(s);
				vector<int>().swap(s);
			}
		}
//		puts("a");
		if(sum>3)
		{
			vector<int>a;
			if(S[0]==1)
			{
				for(int i=2;i<N;i++)a.push_back(S[i]);
			}
			else
			{
				assert(S[0]>1);
				a.push_back(S[0]-1);
				for(int i=1;i<N;i++)a.push_back(S[i]);
			}
			bool valid=(!a.empty());
			for(int i=0;i<2&&valid;i++)
			{
				if(!--a.back())a.pop_back();
				valid&=(!a.empty());
			}
			if(valid)
			{
				vector<int>loc;loc.resize(a.size());
				for(int i=(int)a.size()-1,cur=0;i>=0;i--)loc[i]=(cur+=a[i]);
				for(int i=0;i<(int)a.size();i+=2)
				{
					vector<int>s;
					s.push_back(a[i]);
					s.push_back(loc[i]-a[i]+1);
					anses.push_back(s);
					--adjust;
					adjust-=(a[i]-1);
				}
				vector<int>().swap(loc);
			}
			vector<int>().swap(a);
		}
		if(S[0]>=3)adjust+=S[0]-2;
		for(int i=2;i<N;i+=2)adjust+=S[i];
		if(S[0]>=2&&1<N)++adjust;
		for(int i=3;i<N;i+=2)++adjust;
//		assert(0);
//		puts("b");
		map<int,int>mans;
		for(int i=0;i<(int)anses.size();i++)
		{
			const vector<int>&s=anses[i];
			vector<int>loc;loc.resize(s.size());
			for(int cur=0,j=(int)s.size()-1;j>=0;j--)loc[j]=(cur+=s[j]);
			for(int j=0;j<(int)s.size();j+=2)
			{
				++mans[loc[j]];
				--mans[loc[j]-s[j]];
			}
			vector<int>().swap(anses[i]);
		}
		vector<vector<int> >().swap(anses);
//		puts("c");
		if(adjust>0LL)
		{
			for(int i=0;(1LL<<i)<=adjust;i++)if(adjust&(1LL<<i))++mans[i];
		}
		else
		{
			adjust*=-1LL;
			for(int i=0;(1LL<<i)<=adjust;i++)if(adjust&(1LL<<i))--mans[i];
		}
		for(map<int,int>::iterator it=mans.begin();it!=mans.end();)
		{
			if(abs(it->second)>=2)
			{
				mans[it->first+1]+=it->second/2;
				it->second%=2;
			}
			if(!it->second)mans.erase(it++);
			else ++it;
		}
//		puts("d");
		vector<pair<int,int> >pans;
		int loc=0;
		for(map<int,int>::iterator it=mans.begin();it!=mans.end();++it)
		{
//			printf("(%d,%d)\n",it->first,it->second);
			int val=1;
			if(it==mans.begin())val=0;
			else
			{
				--it;
				if(it->second==1)val=0;
				else assert(it->second==-1);
				++it;
			}
			pans.push_back(make_pair(val,(it->first-1)-loc+1));
			pans.push_back(make_pair(val^1,1));
			loc=it->first+1;
		}
		map<int,int>().swap(mans);
//		puts("e");
		while(!pans.empty()&&(pans.back().first==0||pans.back().second==0))pans.pop_back();
		assert(!pans.empty());
		vector<int>ans;
		for(int i=(int)pans.size()-1,d=1;;d^=1)
		{
			ans.push_back(0);
			for(;i>=0&&(pans[i].first==d||pans[i].second==0);i--)ans.back()+=pans[i].second;
			if(i==-1)break;
		}
		vector<pair<int,int> >().swap(pans);
		printf("%d\n",(int)ans.size());
		for(int i=0;i<(int)ans.size();i++)
		{
			if(i)putchar(' ');
			printf("%d",ans[i]);
		}
		puts("");
		vector<int>().swap(ans);
	}
	return 0;
}
/*
2
1 2
*/
