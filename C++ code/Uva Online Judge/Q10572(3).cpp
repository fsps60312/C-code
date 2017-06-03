#include<cstdio>
#include<map>
#include<cassert>
using namespace std;
int T,N,M,GRID[8][8],A[8][8],B[8][8];
struct State
{
	int v[8],ul;
	bool operator<(const State &s)const
	{
		if(ul!=s.ul)return ul<s.ul;
		for(int i=0;i<N;i++)if(v[i]!=s.v[i])return v[i]<s.v[i];
		return false;
	}
	inline bool SameAs(int a,int b,int c,int &v){return a==v&&b==v&&c==v;}
	int TryMove(int row,int col,int c,State &t)
	{
		if(row&&col&&SameAs(v[col-1]&1,v[col]&1,ul&1,c))return 0;
		if(c!=(v[col]&1))
		{
			if(row==M-1)
			{
				bool life=false,legal=true;
				for(int i=col+1;i<N;i++)
				{
					if(v[i]==v[col]){life=true;break;}
					else if((v[i]&1)==(v[col]&1))legal=false;
				}
				if(!life)
				{
					if(!legal)return 0;
					if(c&&A[row][col])return 0;
					if(!c&&B[row][col])return 0;
//					c+=20;
//					for(int i=max(col-1,0);i<N;i++)
//					{
//						if((c&1)==(v[i]&1)&&v[i]<c)c=v[i];
//					}
//					for(int i=0;i<col;i++)if(v[i]<c)return 0;
					return -1;
				}
			}
			else
			{
				bool life=false,legal=true;
				for(int i=0;i<N;i++)
				{
					if(v[i]==v[col]){life=true;break;}
					else if((v[col]&1)==(v[i]&1))legal=false;
				}
				if(!life)
				{
					if(!legal)return 0;
					if(c&&A[row][col])return 0;
					if(!c&&B[row][col])return 0;
					return -1;
				}
			}
		}
		map<int,int>idx;
		int cnt[2]={0,0};
		if(c==(v[col-1]&1)&&c==(v[col]&1))c=v[col],idx[c]=idx[v[col-1]]=cnt[c&1]++;
		else if(c==(v[col-1]&1))c=v[col-1];
		else if(c==(v[col]&1))c=v[col];
		else c+=20;
		for(int i=0;i<N;i++)t.v[i]=v[i];
		t.ul=t.v[col];t.v[col]=c;
		for(int i=0;i<N;i++)if(idx.find(t.v[i])==idx.end())idx[t.v[i]]=cnt[t.v[i]&1]++;
		if(idx.find(t.ul)==idx.end())idx[t.ul]=cnt[t.ul&1]++;
		for(int i=0;i<N;i++)t.v[i]=(idx[t.v[i]]<<1)+(t.v[i]&1);
		t.ul=(idx[t.ul]<<1)+(t.ul&1);
		return 1;
	}
};
map<State,int>DP[8][8];
#include<set>
int Solve(int r,int c,State &s)
{
	if(c==N)c=0,r++;
	if(r==M)
	{
		for(int i=0;i<N;i++)if(s.v[i]>>1)return 0;
		return 1;
	}
	if(DP[r][c].find(s)!=DP[r][c].end())return DP[r][c][s];
	int dp=0,tmp;
	State t;
	if(GRID[r][c]!=1&&(tmp=s.TryMove(r,c,0,t)))
	{
		if(tmp==-1)dp++;
		else dp+=Solve(r,c+1,t);
	}
	if(GRID[r][c]!=0&&(tmp=s.TryMove(r,c,1,t)))
	{
		if(tmp==-1)dp++;
		else dp+=Solve(r,c+1,t);
	}
	return DP[r][c][s]=dp;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&T)==1)while(T--)
	{
		scanf("%d%d",&M,&N);
		for(int i=0;i<M;i++)
		{
			for(int j=0;j<N;j++)
			{
				static char v;
				do
				{
					scanf("%c",&v);
				}while(v!='o'&&v!='#'&&v!='.');
				int &g=GRID[i][j];
				switch(v)
				{
					case'.':g=-1;break;
					case'o':g=0;break;
					case'#':g=1;break;
					default:assert(0);
				}
				DP[i][j].clear();
			}
		}
		for(int i=M-1,a=0,b=0;i>=0;i--)
		{
			for(int j=N-1;j>=0;j--)
			{
				int &g=GRID[i][j];
				if(g==0)a++;
				else if(g==1)b++;
				A[i][j]=a,B[i][j]=b;
			}
		}
		State s;
		int ans=0;
		for(int i=0;i<(1<<N);i++)
		{
			for(int j=0;j<N;j++)s.v[j]=(i&(1<<j))?1:0;
			int a=0,b=0;
			s.ul=0;
			s.v[0]=((s.v[0]?b++:a++)<<1)+s.v[0];
			for(int j=1;j<N;j++)s.v[j]=(s.v[j]==(s.v[j-1]&1)?s.v[j-1]:((s.v[j]?b++:a++)<<1)+s.v[j]);
//			printf("i=%d:",i);for(int j=0;j<N;j++)printf("%d",s.v[j]);puts("");
			ans+=Solve(1,0,s);
		}
		printf("%d\n",ans);
//return 0;
	}
	return 0;
}
