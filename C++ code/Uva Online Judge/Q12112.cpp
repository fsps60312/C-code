#include<cstdio>
#include<string>
#include<set>
#include<map>
#include<vector>
#include<queue>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL HASH1=1000000007LL,HASH2=2147483647LL;
int N,M,X,Y;
char LINE[11];
struct State
{
	char s[10][10];
	int x,y,len;
	State():x(-1),y(-1){}
	bool operator<(const State &s)const
	{
		if(len!=s.len)return len>s.len;
		return abs(x-X)+abs(y-Y)>abs(s.x-X)+abs(s.y-Y);
	}
	LL GetCode()
	{
		LL ans=0LL;
		for(int i=0;i<N;i++)for(int j=0;j<M;j++)ans*=HASH1,ans+=s[i][j],ans%=HASH2;
		return ans;
	}
};
map<LL,State>STATE;
map<LL,string>MOVE;
void show(State &u)
{
	printf(" path:%s\n",MOVE[u.GetCode()].c_str());
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<M;j++)printf("%c",u.s[i][j]);
		puts("");
	}puts("");
}
void Push(priority_queue<State>&pq,State &u,string path)
{
	u.len=path.size();
	LL code=u.GetCode();
	if(STATE.find(code)!=STATE.end())return;
	STATE[code]=u;
	MOVE[code]=path;
	pq.push(u);
}
int Dropable(State &u,int r,int c)
{
	switch(u.s[r][c])
	{
		case'@':
		case'O':return 1;
		case'[':
		{
			int ans=1;
			for(;u.s[r][c+ans]=='=';ans++);
			return u.s[r][c+ans]==']'?++ans:0;
		}
		default:return 0;
	}
}
void Fall(State &u)
{
//	puts("falling");show(u);
	for(int r=N-2;r>0;r--)
	{
		for(int c=0;c<M;)
		{
			static int cnt;
			if(cnt=Dropable(u,r,c))
			{
				bool drop=true;
				for(int i=0;i<cnt;i++)if(u.s[r+1][c+i]!='.'){drop=false;break;}
				if(drop)
				{
					if(u.s[r][c]=='@')u.y++;
					for(int i=0;i<cnt;i++)
					{
						u.s[r+1][c+i]=u.s[r][c+i];
						u.s[r][c+i]='.';
					}
					r++;
					continue;
				}
			}
			c++;
		}
	}
//	puts("falled");show(u);
}
bool StickIceLeft(char &c)
{
	switch(c)
	{
		case'.':return false;
		case'X':return true;
		case'O':c='[';return true;
		case']':c='=';return true;
		default:assert(0);
	}
}
bool StickIceRight(char &c)
{
	switch(c)
	{
		case'.':return false;
		case'X':return true;
		case'O':c=']';return true;
		case'[':c='=';return true;
		default:assert(0);
	}
}
void DestroyIceLeft(char &c)
{
	switch(c)
	{
		case'[':c='O';break;
		case'=':c=']';break;
	}
}
void DestroyIceRight(char &c)
{
	switch(c)
	{
		case']':c='O';break;
		case'=':c='[';break;
	}
}
bool MagicWind(char &lc,char &c,char &rc)
{
	switch(c)
	{
		case'X':return false;
		case'.':
		{
			bool l=StickIceLeft(lc);
			bool r=StickIceRight(rc);
			if(l&&r)c='=';
			else if(!l&&!r)c='O';
			else c=l?']':'[';
			return true;
		}
		default:
		{
			DestroyIceLeft(lc);
			DestroyIceRight(rc);
			c='.';
			return true;
		}
	}
}
bool MagicWindLeft(State &nxt)
{
	int &x=nxt.x,&y=nxt.y;
	if(MagicWind(nxt.s[y+1][x-2],nxt.s[y+1][x-1],nxt.s[y+1][x]))
	{
		Fall(nxt);
		return true;
	}
	else return false;
}
bool MagicWindRight(State &nxt)
{
	int &x=nxt.x,&y=nxt.y;
	if(MagicWind(nxt.s[y+1][x],nxt.s[y+1][x+1],nxt.s[y+1][x+2]))
	{
		Fall(nxt);
		return true;
	}
	else return false;
}
bool Go(State &nxt,int d)
{
	int &x=nxt.x,&y=nxt.y;
	if(nxt.s[y][x+d]=='.')
	{
//		puts("a");show(nxt);
		swap(nxt.s[y][x],nxt.s[y][x+d]);
		nxt.x+=d;
//		puts("b");show(nxt);
		Fall(nxt);
//		puts("c");show(nxt);
		return true;
	}
	if(nxt.s[y][x+d]=='O'&&nxt.s[y][x+d+d]=='.')
	{
		for(int i=x+d;nxt.s[y+1][i]!='.'&&nxt.s[y][i+d]=='.';i+=d)
			swap(nxt.s[y][i],nxt.s[y][i+d]);
		Fall(nxt);
		return true;
	}
	if(nxt.s[y-1][x]=='.'&&nxt.s[y-1][x+d]=='.')
	{
		swap(nxt.s[y][x],nxt.s[y-1][x+d]);
		nxt.x+=d,nxt.y--;
		Fall(nxt);
		return true;
	}
	return false;
}
string Solve(State &ini)
{
	priority_queue<State>pq;
	Push(pq,ini,"");
//	printf("pq.size()=%d\n",pq.size());
	while(!pq.empty())
	{
		State u=pq.top();pq.pop();
		string &move=MOVE[u.GetCode()];
//		show(u);
		if(u.x==X&&u.y==Y)return move;
		State nxt;
		if(MagicWindLeft(nxt=u))Push(pq,nxt,move+"<");
		if(MagicWindRight(nxt=u))Push(pq,nxt,move+">");
		if(Go(nxt=u,-1))Push(pq,nxt,move+"L");
		if(Go(nxt=u,1))Push(pq,nxt,move+"R");
	}
	assert(0);
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	while(scanf("%d",&N)==1)
	{
		if(!N)break;
		scanf("%d",&M);
		STATE.clear(),MOVE.clear();
		State s=State();
		Y=-1;
		for(int i=0;i<N;i++)
		{
			scanf("%s",LINE);
			for(int j=0;j<M;j++)
			{
				if(LINE[j]=='@')s.y=i,s.x=j;
				else if(LINE[j]=='#')Y=i,X=j,LINE[j]='.';
				s.s[i][j]=LINE[j];
			}
		}
		assert(s.y!=-1&&Y!=-1);
		string ans=Solve(s);
		static int kase=1;
		printf("Case %d: ",kase++);
		printf("%s\n",ans.c_str());
	}
	return 0;
}
