#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
#include<queue>
#include<set>
using namespace std;
const int LEFT=1<<30,RIGHT=1<<29,PLAT=1<<28,RED=1<<27,SCORE=~(LEFT+RIGHT+PLAT+RED),COLOR=~(LEFT+RIGHT+PLAT);
int M,PLAYER;
vector<int>CARD;
struct Pq
{
	vector<int>s;
	int score,step,card[2],player;
	vector<Pq>ch;
	bool operator<(const Pq p)const
	{
		if(step!=p.step)return step>p.step;
		if(score!=p.score)
		{
			if(player==PLAYER)return score>p.score;
			else return score<p.score;
		} 
		return false;
	}
	void CopyFrom(Pq &u)
	{
		s.clear();
		score=u.score;
		step=u.step+1;
		card[0]=u.card[0];
		card[1]=u.card[1];
		player=u.player^1;
	}
};
set<Pq,cmp>VIS;
void Score(int &win,int &n,int a,int b,int c)
{
	int cnt=0;
	if(a&RED)cnt++;
	if(b&RED)cnt++;
	if(c&RED)cnt++;
	win=(cnt<=1?0:1);
	n=(a&SCORE)+(b&SCORE)+(c&SCORE);
}
void Cover(vector<int>&a,vector<int>&b,int loc,int replace)
{
	b.clear();
	for(int i=0;i<a.size();i++)
	{
		if(i==loc)
		{
			b.pop_back();
			b.push_back((replace&COLOR)|PLAT);
		}
		else b.push_back(a[i]);
	}
}
void Build(vector<int>&a,vector<int>&b,int loc,int l,int r)
{
	b.clear();
	for(int i=0;i<a.size();i++)
	{
		if(i==loc)
		{
			if(i)b.push_back((l&COLOR)|LEFT);
			if(i!=a.size()-1)b.push_back((r&COLOR)|RIGHT);
		}
		else b.push_back(a[i]);
	}
}
void show(Pq u)
{
	printf("%d: %s,%d",u.step,PLAYER?"Axel":"Birgit",u.score);
	for(int i=0;i<u.s.size();i++)
	{
		printf(" %d%c",u.s[i]&SCORE,(u.s[i]&RED)?'R':'B');
		int cnt=0;
		if(u.s[i]&PLAT){printf("P");cnt++;}
		if(u.s[i]&LEFT){printf("L");cnt++;}
		if(u.s[i]&RIGHT){printf("R");cnt++;}
		assert(cnt==1);
	}
	puts("");
}
void Solve(Pq &ini)
{
	priority_queue<*Pq>pq;
	pq.push(&ini);
//	VIS.insert(ini);
	while(!pq.empty())
	{
		Pq *u=pq.front();pq.pop();
		if(u.step==M*2)continue;
		Pq t;
		if(!u.card[u.player])
		{
			t.CopyFrom(u);
			t.s=u.s;
			t.card[u.player]=CARD[u.step];
			Push(pq,t,u);
		}
		for(int i=1;i<u.s.size();i++)
		{
			if((u.s[i-1]&RIGHT)&&(u.s[i]&LEFT))
			{
				static int win,n;
				Score(win,n,u.s[i-1],u.s[i],CARD[u.step]);
				t.CopyFrom(u);
				if(win==PLAYER)t.score+=n;
				else t.score-=n;
				Cover(u.s,t.s,i,CARD[u.step]);
				Push(pq,t);
				if(u.card[u.player])
				{
					Score(win,n,u.s[i-1],u.s[i],u.card[u.player]);
					t.CopyFrom(u);
					t.card[u.player]=CARD[u.step];
					if(win==PLAYER)t.score+=n;
					else t.score-=n;
					Cover(u.s,t.s,i,u.card[u.player]);
					Push(pq,t);
				}
			}
		}
		if(u.card[u.player])
		{
			for(int i=0;i<u.s.size();i++)
			{
				if(u.s[i]&PLAT)
				{
					static int win,n;
					Score(win,n,u.s[i],CARD[u.step],u.card[u.player]);
					t.CopyFrom(u);
					t.card[u.player]=0;
					if(win==PLAYER)t.score+=n;
					else t.score-=n;
					Build(u.s,t.s,i,CARD[u.step],u.card[u.player]);
					Push(pq,t);
					Build(u.s,t.s,i,u.card[u.player],CARD[u.step]);
					Push(pq,t);
				}
			}
		}
	}
	assert(0);
}
int main()
{
	freopen("in.txt","r",stdin);
	static char LINE[7];
	while(scanf("%s",LINE)==1)
	{
		if(LINE[0]=='E')break;
		assert(LINE[0]=='A'||LINE[0]=='B');
		PLAYER=LINE[0]=='B'?0:1;
		scanf("%d",&M);
		CARD.clear();
		VIS.clear();
		for(int i=0;i<M*2;i++)
		{
			static int v;
			static char c;
			scanf("%d%c",&v,&c);
			assert(c=='B'||c=='R');
			if(c=='R')v|=RED;
			CARD.push_back(v);
		}
		Pq ini;
		ini.step=8;//next card
		ini.score=0;//score
		ini.card[0]=ini.card[1]=0;
		ini.player=(CARD[0]&RED?1:0);
		for(int i=1;i<7;i++)ini.s.push_back((i&1)?CARD[i]|RIGHT:CARD[i]|LEFT);
		int ans=Solve(ini);
		static int kase=1;
		printf("Case %d: ",kase++);
		if(!ans)puts("Axel and Birgit tie");
		else printf("%s %s %d\n",PLAYER?"Axel":"Birgit",ans<0?"loses":"wins",abs(ans));
	}
	return 0;
}
