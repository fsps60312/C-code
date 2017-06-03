#include<cstdio>
#include<cassert>
#include<algorithm>
#include<map>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
struct Bit
{
	int s[1001],n;
	void clear(const int _n){n=_n;for(int i=1;i<=n;i++)s[i]=0;}
	void Add(int i,const int v){while(i<=n)s[i]+=v,i+=(i&(-i));}
	int Query(int i){int ans=0;while(i)ans+=s[i],i-=(i&(-i));return ans;}
}BIT;
int N,UP[1000][1000],DOWN[1000][1000],LEFT[1000][1000],RIGHT[1000][1000];
char GRID[1000][1000];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)
	{
		char &c=GRID[i][j];
		do{c=getchar();}while(c!='0'&&c!='1');
	}
	for(int i=N-1;i>=0;i--)for(int j=N-1;j>=0;j--)
	{
		if(GRID[i][j]=='0')DOWN[i][j]=RIGHT[i][j]=0;
		else DOWN[i][j]=(i==N-1?1:DOWN[i+1][j]+1),RIGHT[i][j]=(j==N-1?1:RIGHT[i][j+1]+1);
	}
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)
	{
		if(GRID[i][j]=='0')UP[i][j]=LEFT[i][j]=0;
		else UP[i][j]=(i==0?1:UP[i-1][j]+1),LEFT[i][j]=(j==0?1:LEFT[i][j-1]+1);
	}
	int ans=0;
	for(int r=N-1,c=0;c<N;)
	{
		BIT.clear(N);
		multimap<int,int>pq;
		for(int i=0;r+i<N&&c+i<N;i++)
		{
			while(!pq.empty()&&pq.begin()->first<=i)BIT.Add(pq.begin()->second,-1),pq.erase(pq.begin());
			const int len1=min(DOWN[r+i][c+i],RIGHT[r+i][c+i]),len2=min(UP[r+i][c+i],LEFT[r+i][c+i]);
			if(len1)pq.insert(make_pair(i+len1,len1)),BIT.Add(len1,1);
			if(len2)ans+=BIT.Query(len2);
		}
		if(r)r--;
		else c++;
	}
	for(int r=N-1,c=0;r>=0;)
	{
		BIT.clear(N);
		multimap<int,int>pq;
		for(int i=0;r-i>=0&&c-i>=0;i++)
		{
			while(!pq.empty()&&pq.begin()->first<=i)BIT.Add(pq.begin()->second,-1),pq.erase(pq.begin());
			const int len1=min(UP[r-i][c-i],LEFT[r-i][c-i]),len2=min(DOWN[r-i][c-i],RIGHT[r-i][c-i]);
			if(len1)pq.insert(make_pair(i+len1,len1)),BIT.Add(len1,1);
			if(len2)ans+=BIT.Query(len2-1);
		}
		if(c+1<N)c++;
		else r--;
	}
	printf("%d\n",ans);
	return 0;
}
