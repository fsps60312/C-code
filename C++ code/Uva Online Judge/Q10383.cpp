#include<bits/stdc++.h>
using namespace std;
int T;
char LINE[4][5];
struct Point
{
	int x,y;
	Point(){}
	Point(const int &x,const int &y):x(x),y(y){}
	bool operator<(const Point &p)const{return x!=p.x?x<p.x:y<p.y;}
	bool operator!=(const Point &p)const{return x!=p.x||y!=p.y;}
	bool operator==(const Point &p)const{return x==p.x&&y==p.y;}
};
const Point DEAD=Point(-1,-1);
struct State
{
	Point K0,R0,K1,Q1;
	int player;
	State(){}
	State(const Point &k0,const Point &r0,const Point &k1,const Point &q1):K0(k0),R0(r0),K1(k1),Q1(q1){}
	Point &Val(const int &idx)const
	{
		switch(idx)
		{
			case 0:return K0;
			case 1:return R0;
			case 2:return K1;
			case 3:return Q1;
			default:assert(0);
		}
	}
	bool operator<(const State &s)const
	{
		if(K0!=s.K0)return K0<s.K0;
		if(R0!=s.R0)return R0<s.R0;
		if(K1!=s.K1)return K1<s.K1;
		if(Q1!=s.Q1)return Q1<s.Q1;
		return player<s.player;
	}
};
map<State,int>IDX;
vector<State>STATE;
vector<bool>INQ;
map<int,Point>SCORE;
map<int,vector<string> >MOVE;
queue<int>Q;
string CODE[4]={"K0","R0","K1","Q1"};
int D[8][2]={{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1}};
int GetIDX(const State &s)
{
	if(IDX.find(s)==IDX.end())
	{
		static int sz;sz=IDX.size();
		STATE.push_back(s);
		return IDX[s]=sz;
	}
	return IDX[s];
}
int GetIDX(const State &s,bool &exist)
{
	if(IDX.find(s)==IDX.end())
	{
		static int sz;sz=IDX.size();
		STATE.push_back(s);
		INQ.push_back(false);
		exist=false;
		return IDX[s]=sz;
	}
	exist=true;
	return IDX[s];
}
string ToString(string s,Point p)
{
	static char line[3];
	line[0]='a'+p.x,line[1]='0'+p.y,line[2]='\0';
	return s+line;
}
void UpdateShort(const State &s,const State &u,const Point &score,const string code,const Point &moveto)
{
	static bool exist;
	int j=GetIDX(u,exist);
	if(!exist)
	{
		SCORE[j]=Point(score.x,score.y+1);
		MVOE[j].push_back(ToString(code,moveto));
		Q.push(u);
		INQ[j]=true;
	}
	else
	{
		Point &os=SCORE[j];
		assert(os.y<=score.y+1);
		if(os.y==score.y+1)MOVE[j].push_back(ToString(code,moveto));
	}
}
void UpdateShort(const State &s,const State &u,const Point &score,const int &move,const int &watch)
{
	if(u.Val(move)!=u.Val(watch))UpdateShort(s,u,score,CODE[move],s.Val(move));
	if(u.Val(watch)==DEAD)
	{
		u.Val(watch)=s.Val(move);
		UpdateShort(s,u,score,CODE[move],s.Val(move));
		u.Val(watch)=DEAD;
	}
}
void UpdateLong(const State &s,const State &u,const Point &score,const string code,const Point &moveto)
{
	static bool exist;
	int j=GetIDX(u,exist);
	if(!exist)
	{
		SCORE[j]=Point(score.x,score.y+1);
		MVOE[j].push_back(ToString(code,moveto));
		Q.push(u);
		INQ[j]=true;
	}
	else
	{
		Point &os=SCORE[j];
		assert(os.y<=score.y+1);
		if(os.y<score.y+1)
		{
			MOVE[j].clear();
			os.y=score.y+1;
			if(!INQ[j])
			{
				Q.push(u);
				INQ[j]=true;
			}
		}
		if(os.y==score.y+1)MOVE[j].push_back(ToString(code,moveto));
	}
}
void UpdateLong(const State &s,const State &u,const Point &score,const int &move,const int &watch)
{
	if(u.Val(move)!=u.Val(watch))UpdateLong(s,u,score,CODE[move],s.Val(move));
	if(u.Val(watch)==DEAD)
	{
		u.Val(watch)=s.Val(move);
		UpdateLong(s,u,score,CODE[move],s.Val(move));
		u.Val(watch)=DEAD;
	}
}
bool Legal(const Point &p){return p.x>=0&&p.x<8&&p.y>=0&&p.y<8;}
void Build()
{
	while(!Q.empty())
	{
		int idx=Q.front();Q.pop();
		INQ[idx]=false;
		State &s=STATE[idx],u=s;
		Point &score=SCORE[idx];
		u.player^=1;
		if(u.player==score.x)
		{//get shortest path
			if(u.playr==0)
			{//move K0 or R0
				if(u.R0!=DEAD)
				{
					for(int i=0;i<8;i++)
					{
						if(i!=s.R0.x)
						{
							u.R0=Point(i,s.R0.y);
							UpdateShort(s,u,score,1,3);//1==R0,3==Q1
						}
						if(i!=s.R0.y)
						{
							u.R0=Point(s.R0.x,i);
							UpdateShort(s,u,score,1,3);//1==R0,3==Q1
						}
					}
					u.R0=s.R0;
				}
				for(int i=0;i<8;i++)
				{
					u.K0=Point(s.K0.x+D[i][0],s.K0.y+D[i][1]);
					if(Legal(u.K0))UpdateShort(s,u,score,0,3);//0==K0,3==Q1
				}
				u.K0=s.K0;
			}
			else
			{//move K1 or Q1
				if(u.Q1!=DEAD)
				{
					const Point &Q1=s.Q1;
					for(int d=0;d<8;d++)
					{
						for(int i=1;i<=7;i++)
						{
							u.Q1=Point(Q1.x+i*D[d][0],Q1.y+i*D[d][1]);
							if(Legal(u.Q1))UpdateShort(s,u,score,3,1);//3==Q1,1==R0
						}
					}
					u.Q1=s.Q1;
				}
				for(int i=0;i<8;i++)
				{
					u.K1=Point(s.K1.x+D[i][0],s.K1.y+D[i][1]);
					if(Legal(u.K1))UpdateShort(s,u,score,2,1);//2==K1,1==R0
				}
				u.K1=s.K1;
			}
		}
		else
		{//get longest path
			if(u.playr==0)
			{//move K0 or R0
				if(u.R0!=DEAD)
				{
					for(int i=0;i<8;i++)
					{
						if(i!=s.R0.x)
						{
							u.R0=Point(i,s.R0.y);
							UpdateLong(s,u,score,1,3);//1==R0,3==Q1
						}
						if(i!=s.R0.y)
						{
							u.R0=Point(s.R0.x,i);
							UpdateLong(s,u,score,1,3);//1==R0,3==Q1
						}
					}
					u.R0=s.R0;
				}
				for(int i=0;i<8;i++)
				{
					u.K0=Point(s.K0.x+D[i][0],s.K0.y+D[i][1]);
					if(Legal(u.K0))UpdateLong(s,u,score,0,3);//0==K0,3==Q1
				}
				u.K0=s.K0;
			}
			else
			{//move K1 or Q1
				if(u.Q1!=DEAD)
				{
					const Point &Q1=s.Q1;
					for(int d=0;d<8;d++)
					{
						for(int i=1;i<=7;i++)
						{
							u.Q1=Point(Q1.x+i*D[d][0],Q1.y+i*D[d][1]);
							if(Legal(u.Q1))UpdateLong(s,u,score,3,1);//3==Q1,1==R0
						}
					}
					u.Q1=s.Q1;
				}
				for(int i=0;i<8;i++)
				{
					u.K1=Point(s.K1.x+D[i][0],s.K1.y+D[i][1]);
					if(Legal(u.K1))UpdateLong(s,u,score,2,1);//2==K1,1==R0
				}
				u.K1=s.K1;
			}
		}
	}
}
int main()
{
	static State s;
	int &player=s.player;
	Point &K0=s.K0,&R0=s.R0,&K1=s.K1,&Q1=s.Q1;
	K1=Q1=DEAD;
	player=1;
	for(int &x=K0.x=0,i;x<8;x++)for(int &y=K0.y=0;y<8;y++)
	{
		R0=DEAD;
		SCORE[i=GetIDX(s)]=Point(0,0);
		Q.push(i);
		INQ[i]=true;
		for(int &a=R0.x=0;a<8;a++)for(int &b=R0.y=0;b<8;b++)
		{
			SCORE[i=GetIDX(s)]=Point(0,0);
			Q.push(i);
			INQ[i]=true;
		}
	}
	K0=R0=DEAD;
	player=0;
	for(int &x=K1.x=0,i;x<8;x++)for(int &y=K1.y=0;y<8;y++)
	{
		Q1=DEAD;
		SCORE[i=GetIDX(s)]=Point(1,0);
		Q.push(i);
		INQ[i]=true;
		for(int &a=Q1.x=0;a<8;a++)for(int &b=Q1.y=0;b<8;b++)
		{
			SCORE[i=GetIDX(s)]=Point(1,0);
			Q.push(i);
			INQ[i]=true;
		}
	}
	Build();
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			char which0='\0';
			for(int i=0;i<4;i++)
			{
				scanf("%s",LINE[i]);
				if(LINE[i][1]=='R')which0=LINE[0];
			}
			assert(which0!='\0');
			for(int i=0;i<4;i++)
			{
				char *l=LINE[i];
				Point p=Point(l[2]-'a',l[3]-'0');
				switch(l[1])
				{
					case'R':s.R0=p;break;
					case'Q':s.Q1=p;break;
					default:
						if(l[0]==which0)s.K0=p;
						else s.K1=p;
						break;
				}
			}
			scanf("%s",LINE[0]);
			s.player=LINE[0][0]==which0?0:1;
			Point &score=
		}
	}
	return 0;
}

