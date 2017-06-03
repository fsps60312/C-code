#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
#include<queue>
#include<set>
using namespace std;
int M,PLAYER;
vector<int>CARD;
struct Pq
{
	vector<int>s;
	int score,step,card[2],player;
	bool operator<(const Pq p)const
	{
		if(step!=p.step)return step>p.step;
		if(score!=p.score)return score<p.score;
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
set<vector<int> >VIS;
int Solve(Pq &ini)
{
	priority_queue<Pq>pq;
	pq.push(ini);
	while(!pq.empty())
	{
		Pq u=pq.top();pq.pop();
		if(VIS.find(u.s)!=VIS.end())continue;
		VIS.insert(u);
		if(u.step==M*2)return u.score;
		Pq t;t.CopyFrom(u);
		t.s=u.s;
		for(int i=0;i<t.s.size();i++)
		{
			int &v=t.s[i];
			if(v/100<4)continue;
			int win,n=v+CARD[u.step];
			if(n/100<=7)win=0;
			else win=1;
			if(win==PLAYER)t.score+=n%100;
			else t.score-=n%100;
			v=CARD[u.step];
			pq.push(t);
			v=u.s[i];
			t.score=u.score;
		}
		int held=u.card[u.player];
		if(held)
		{
			for(int i=0;i<u.s.size();i++)
			{
				int &v=u.s[i];
				if(v/100>=4)continue;
				int win,n=v+CARD[u.step]+held;
				if(n/100<=7)win=0;
				else win=1;
				t.CopyFrom(u);
				t.card[u.player]=0;
				if(win==PLAYER)t.score+=n%100;
				else t.score-=n%100;
				t.s.clear();
				if(!i||i==u.s.size()-1)
				{
					
					pq.push(t);
				}
				///
			}
		}
	}
	assert(0);
}
int main()
{
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
			CARD.push_back((c=='B'?200:300)+v);
		}
		Pq ini;
		ini.step=8;//next card
		ini.score=0;//score
		ini.card[0]=ini.card[1]=0;
		ini.player=CARD[0]/100==2?0:1;
		for(int i=1;i<=3;i++)ini.s.push_back(CARD[i*2-1]+CARD[i*2]);
		int ans=Solve(ini);
		static int kase=1;
		printf("Case %d: ",kase++);
		if(!ans)puts("Axel and Birgit tie");
		else printf("%s %s %d\n",PLAYER?"Axel":"Birgit",ans<0?"loses":"wins",abs(ans));
	}
	return 0;
}
