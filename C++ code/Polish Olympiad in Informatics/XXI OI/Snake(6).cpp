#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
using namespace std;
typedef long long LL;
const LL ALL=(1LL<<16)-1LL;
inline int Combine(const int a,const int b,const int c){return a|(b<<2)|(c<<4);}
inline int Digit(const int s,const int i){return (s>>(i<<1))&3;}
struct State
{
	int a,b,c,o;
	State(){}
	State(const int _a,const int _b,const int _c,const int _o):a(_a),b(_b),c(_c),o(_o){}
	inline LL GetCode()const{return ((LL)a<<48)|((LL)b<<32)|((LL)c<<16)|((LL)o);}
	inline bool operator<(const State &v)const
	{
		if(a!=v.a)return a<v.a;
		if(b!=v.b)return b<v.b;
		if(c!=v.c)return c<v.c;
		if(o!=v.o)return o<v.o;
		return false;
	}
	inline int EntranceExitCount()const
	{
		int ans=0;
		for(int i=0;i<3;i++)if(Digit(o,i))++ans;
		return ans;
	}
	inline bool IsValid(const int *s)const
	{
		if(s[0]&&a!=s[0])return false;
		if(s[1]&&b!=s[1])return false;
		if(s[2]&&c!=s[2])return false;
		return true;
	}
};
int N,S[1000][3];
void SolveNis1()
{
	bool valid=true;
	for(int i=0;i<3;i++)if(S[0][i]&&S[0][i]!=i+1){valid=false;break;}
	if(valid)
	{
		for(int i=0;i<3;i++)S[0][i]=i+1;
		return;
	}
	for(int i=0;i<3;i++)
	{
		if(S[0][i])assert(S[0][i]==3-i);
		else S[0][i]=3-i;
	}
	return;
}
bool Dfs(const int column,const State &s,const LL &pre);
bool VIS[4][3001];
bool InsertOneWayNxts(const int column,const int d,const int id,const int loc,const LL val)
{
	assert(loc==0||loc==2);
	assert(d==1||d==2);
	if(d==2)//out
	{
		if(VIS[0+loc][id])return false;
		VIS[0+loc][id]=true;
		for(int i=id+3;i+1<=N*3;i+=2)
		{
			if(loc==0){if(Dfs(column,State(  id,   i, i+1, Combine(            2,            1, i+1==N*3?0:2)),val))return true;}
			else      {if(Dfs(column,State( i+1,   i,  id, Combine( i+1==N*3?0:2,            1,            2)),val))return true;}
		}
		for(int i=id+4;i+1<=N*3;i+=2)
		{
			if(loc==0){if(Dfs(column,State(  id, i+1,   i, Combine(            2, i+1==N*3?0:2,            1)),val))return true;}
			else      {if(Dfs(column,State(   i, i+1,  id, Combine(            1, i+1==N*3?0:2,            2)),val))return true;}
		}
	}
	else//enter
	{
		if(VIS[1+loc][id])return false;
		VIS[1+loc][id]=true;
		for(int i=id-3;i-1>=1;i-=2)
		{
			if(loc==0){if(Dfs(column,State(  id,   i, i-1, Combine(            1,            2,   i-1==1?0:1)),val))return true;}
			else      {if(Dfs(column,State( i-1,   i,  id, Combine(   i-1==1?0:1,            2,            1)),val))return true;}
		}
		for(int i=id-4;i-1>=1;i-=2)
		{
			if(loc==0){if(Dfs(column,State(  id, i-1,   i, Combine(            1,   i-1==1?0:1,            2)),val))return true;}
			else      {if(Dfs(column,State(   i, i-1,  id, Combine(            2,   i-1==1?0:1,            1)),val))return true;}
		}
	}
	return false;
}
bool UpdateFromOneWay(const int column,const State &s,const int loc)
{
	const LL code=s.GetCode();
	const int d=Digit(s.o,loc);
	assert(d==1||d==2);
	const int id=(loc==0?s.a:s.c)+(d==2?1:-1);
	if(loc==0||loc==2)
	{
//		---  ->
//		/--  <>
//		\--  <>
		if(InsertOneWayNxts(column+1,d,id,loc,s.GetCode()))return true;//doesn't matter whether id is in range[1,N*3]
//		-\   X
//		 \-  ->
//		 *-  <-
		if(d==2)//out
		{
			if(N*3-(id+1)>=3&&(N*3-(id+1))%2==1)
			{
				if(loc==0){if(Dfs(column+1,State( id,id+1,N*3,Combine(0,2,1)),code))return true;}
				else      {if(Dfs(column+1,State(N*3,id+1, id,Combine(1,2,0)),code))return true;}
			}
		}
		else//enter
		{
			if((id-1)-1>=3&&((id-1)-1)%2==1)
			{
				if(loc==0){if(Dfs(column+1,State( id,id-1,  1,Combine(0,1,2)),code))return true;}
				else      {if(Dfs(column+1,State(  1,id-1, id,Combine(2,1,0)),code))return true;}
			}
		}
//		-\   X
//		 |   X
//		 \-  ->
		if(d==2)//out
		{
			if(id+2<=N*3)
			{
				if(loc==0){if(Dfs(column+1,State(  id,id+1,id+2,Combine(0,0,id+2==N*3?0:2)),code))return true;}
				else      {if(Dfs(column+1,State(id+2,id+1,  id,Combine(id+2==N*3?0:2,0,0)),code))return true;}
			}
		}
		else//enter
		{
			if(id-2>=1)
			{
				if(loc==0){if(Dfs(column+1,State(  id,id-1,id-2,Combine(0,0,id-2==1?0:1)),code))return true;}
				else      {if(Dfs(column+1,State(id-2,id-1,  id,Combine(id-2==1?0:1,0,0)),code))return true;}
			}
		}
	}
	else if(loc==1)
	{
//		 *-  <-
//		-\   X
//		 \-  ->
		if(d==2)//out
		{
			if(N*3-id>=5&&(N*3-id)%2==1)
			{
				{if(Dfs(column+1,State( N*3,id,id+1,Combine(1,0,2)),code))return true;}
				{if(Dfs(column+1,State(id+1,id, N*3,Combine(2,0,1)),code))return true;}
			}
		}
		else
		{
			if(id-1>=5&&(id-1)%2==1)
			{
				{if(Dfs(column+1,State(   1,id,id-1,Combine(2,0,1)),code))return true;}
				{if(Dfs(column+1,State(id-1,id,   1,Combine(1,0,2)),code))return true;}
			}
		}
	}
	else assert(0);
	return false;
}
bool UpdateFromTwoWay(const int column,const State &s,const int loc)
{
	const LL code=s.GetCode();
	if(loc==0||loc==2)
	{
		assert(Digit(s.o,2-loc)+Digit(s.o,1)==3);//must be 1 & 2
		const int d=Digit(s.o,1);
		assert(d==1||d==2);
		const int id1=s.b+(d==2?1:-1),id2=(loc==0?s.c:s.a)+(d==2?-1:1);
//		 /-  ->
//		-/   X
//		---  <-
		if(d==2)//out
		{
			if(id1+1<=N*3&&((s.b<(loc==0?s.c:s.a)&&id2-id1>=5&&(id2-id1)%2==1)||s.b>(loc==0?s.c:s.a)))
			{
				if(loc==0){if(Dfs(column+1,State(id1+1,id1,  id2,Combine(id1+1==N*3?0:2,0,    id2==1?0:1)),code))return true;}
				else      {if(Dfs(column+1,State(  id2,id1,id1+1,Combine(    id2==1?0:1,0,id1+1==N*3?0:2)),code))return true;}
			}
		}
		else//in
		{
			if(id1-1>=1&&((s.b>(loc==0?s.c:s.a)&&id1-id2>=5&&(id1-id2)%2==1)||s.b<(loc==0?s.c:s.a)))
			{
				if(loc==0){if(Dfs(column+1,State(id1-1,id1,  id2,Combine(id1-1==1?0:1, 0, id2==N*3?0:2)),code))return true;}
				else      {if(Dfs(column+1,State(  id2,id1,id1-1,Combine(id2==N*3?0:2, 0, id1-1==1?0:1)),code))return true;}
			}
		}
//		 *-  <>
//		---  -> id1
//		---  <- id2
		if(d==2)//out
		{
//			 *-  <-
//			---  -> id1
//			---  <- id2
			if(N*3-id1>=3&&(N*3-id1)%2==1&&(id1-id2>=3&&(id1-id2)%2==1))
			{
				if(loc==0){if(Dfs(column+1,State(N*3,id1,id2,Combine(1,2,id2==1?0:1)),code))return true;}
				else      {if(Dfs(column+1,State(id2,id1,N*3,Combine(id2==1?0:1,2,1)),code))return true;}
			}
//			 *-  ->
//			---  -> id1
//			---  <- id2
			if(id2-1>=4&&(id2-1)%2==0&&(id1-id2>=3&&(id1-id2)%2==1))
			{
				if(loc==0){if(Dfs(column+1,State(  1,id1,id2,Combine(2,id1==N*3?0:2,1)),code))return true;}
				else      {if(Dfs(column+1,State(id2,id1,  1,Combine(1,id1==N*3?0:2,2)),code))return true;}
			}
		}
		else//in
		{
//			 *-  ->
//			---  <- id1
//			---  -> id2
			if(id1-1>=3&&(id1-1)%2==1&&(id2-id1>=3&&(id2-id1)%2==1))
			{
				if(loc==0){if(Dfs(column+1,State(  1,id1,id2,Combine(2,1,id2==N*3?0:2)),code))return true;}
				else      {if(Dfs(column+1,State(id2,id1,  1,Combine(id2==N*3?0:2,1,2)),code))return true;}
			}
//			 *-  <-
//			---  <- id1
//			---  -> id2
			if(N*3-id2>=4&&(N*3-id2)%2==0&&(id2-id1>=3&&(id2-id1)%2==1))
			{
				if(loc==0){if(Dfs(column+1,State(N*3,id1,id2,Combine(1,id1==1?0:1,2)),code))return true;}
				else      {if(Dfs(column+1,State(id2,id1,N*3,Combine(2,id1==1?0:1,1)),code))return true;}
			}
		}
	}
	else if(loc==1)
	{
		assert(Digit(s.o,0)+Digit(s.o,2)==3);//must be 1 & 2
		const int d=Digit(s.o,0);
		assert(d==1||d==2);
		const int id1=s.a+(d==2?1:-1),id2=s.c+(d==2?-1:1);
//		-\   X
//		 \-  ->
//		---  <-
		if(d==2)//out
		{
//			if(s.a==17&&s.b==18&&s.c==25)puts("a");
			if(id2-id1==2){if(Dfs(column+1,State(id1,id1+1,id2,Combine(0,0,0)),code))return true;}
			else if(id2-id1>2)
			{
				{if(Dfs(column+1,State(id1,id1+1,id2,Combine(0,2,1)),code))return true;}
				{if(Dfs(column+1,State(id1,id2-1,id2,Combine(2,1,0)),code))return true;}
			}
			else
			{
				assert(id1>id2);
				if(id1+1<=N*3){if(Dfs(column+1,State(id1,id1+1,id2,Combine(0,id1+1==N*3?0:2,id2==1?0:1)),code))return true;}
				if(id2-1>=1)  {if(Dfs(column+1,State(id1,id2-1,id2,Combine(id1==N*3?0:2,id2-1==1?0:1,0)),code))return true;}
			}
		}
		else//in
		{
//			if(s.a==17&&s.b==18&&s.c==25)puts("b");
			if(id1-id2==2){if(Dfs(column+1,State(id1,id2+1,id2,Combine(0,0,0)),code))return true;}
			else if(id1-id2>2)
			{
				{if(Dfs(column+1,State(id1,id1-1,id2,Combine(0,1,2)),code))return true;}
				{if(Dfs(column+1,State(id1,id2+1,id2,Combine(1,2,0)),code))return true;}
			}
			else
			{
				assert(id2>id1);
				if(id1-1>=1)
				{
					{if(Dfs(column+1,State(id1,id1-1,id2,Combine(0,id1-1==1?0:1,id2==N*3?0:2)),code))return true;}
				}
				if(id2+1<=N*3)
				{
					{if(Dfs(column+1,State(id1,id2+1,id2,Combine(id1==1?0:1,id2+1==N*3?0:2,0)),code))return true;}
				}
			}
		}
//		---  ->
//		 *-  <>
//		---  <-
		if(d==2)//out
		{
			if(N*3-id1>=3&&(N*3-id1)%2==1&&id1-id2>=4&&(id1-id2)%2==0)
			{
				{if(Dfs(column+1,State(id1,N*3,id2,Combine(2,1,id2==1?0:1)),code))return true;}
			}
			if(id2-1>=3&&(id2-1)%2==1&&id1-id2>=4&&(id1-id2)%2==0)
			{
				{if(Dfs(column+1,State(id1,1,id2,Combine(id1==N*3?0:2,2,1)),code))return true;}
			}
		}
//		---  <-
//		 *-  <>
//		---  ->
		else
		{
			if(id1-1>=3&&(id1-1)%2==1&&id2-id1>=4&&(id2-id1)%2==0)
			{
				{if(Dfs(column+1,State(id1,1,id2,Combine(1,2,id2==N*3?0:2)),code))return true;}
			}
			if(N*3-id2>=3&&(N*3-id2)%2==1&&id2-id1>=4&&(id2-id1)%2==0)
			{
				{if(Dfs(column+1,State(id1,N*3,id2,Combine(id1==1?0:1,1,2)),code))return true;}
			}
		}
	}
	else assert(0);
	return false;
}
inline int GetDifferentOne(const int *s)
{
	for(int i=0;i<3;i++)assert(s[i]==-1||s[i]==1);
	if(s[0]!=s[1]&&s[0]!=s[2])return 0;
	if(s[1]!=s[0]&&s[1]!=s[2])return 1;
	if(s[2]!=s[0]&&s[2]!=s[1])return 2;
	assert(0);return -1;
}
bool UpdateFromThreeWay(const int column,const State &s)
{
	const LL code=s.GetCode();
	static int __dis[3];
	for(int i=0;i<3;i++)
	{
		const int v=Digit(s.o,i);
		__dis[i]=(v==2?1:(v==1?-1:0));
	}
	const int *dis=__dis;
	const int loc=GetDifferentOne(dis);
	const int d=Digit(s.o,loc);
	assert(d==1||d==2);
	const int id0=s.a+dis[0],id1=s.b+dis[1],id2=s.c+dis[2];
	if(id0+dis[0]==id1)
	{
		assert(id1+dis[1]==id0);
		{if(Dfs(column+1,State(id0,id1,id2,Combine(0,0,dis[2]==1?(id2==N*3?0:2):(id2==1?0:1))),code))return true;}
	}
	else if(id0+dis[0]*2==id2)
	{
//		assert(0&&"This is impossible!");
	}
	else if(id1+dis[1]==id2)
	{
		assert(id2+dis[2]==id1);
		{if(Dfs(column+1,State(id0,id1,id2,Combine(dis[0]==1?(id0==N*3?0:2):(id0==1?0:1),0,0)),code))return true;}
	}
	else
	{
		assert(id1+dis[1]!=id0&&id2+dis[2]*2!=id0&&id2+dis[2]!=id1);
		{if(Dfs(column+1,State(id0,id1,id2,Combine(dis[0]==1?(id0==N*3?0:2):(id0==1?0:1),dis[1]==1?(id1==N*3?0:2):(id1==1?0:1),dis[2]==1?(id2==N*3?0:2):(id2==1?0:1))),code))return true;}
	}
	return false;
}
map<LL,LL>DP[1000];
const State Decode(const LL v){return State((int)(v>>48),(int)((v>>32)&ALL),(int)((v>>16)&ALL),(int)(v&ALL));}
bool Dfs(const int column,const State &s,const LL &pre)
{
	const LL code=s.GetCode();
	if(DP[column].find(code)!=DP[column].end())return false;
	DP[column][code]=pre;
	if(!s.IsValid(S[column]))return false;
	if(column==N-1)
	{
		if(s.EntranceExitCount()==0)
		{
			LL cur=s.GetCode();
			for(int i=N-1;i>=0;cur=DP[i][cur],--i)
			{
				assert(Decode(cur).IsValid(S[i]));
				S[i][0]=Decode(cur).a;
				S[i][1]=Decode(cur).b;
				S[i][2]=Decode(cur).c;
			}
			assert(cur==NULL);
			return true;
		}
		else return false;
		assert(0);
	}
	vector<int>opens;
	for(int i=0;i<3;i++)if(Digit(s.o,i))opens.push_back(i);
	switch(opens.size())
	{
		case 0:break;
		case 1:if(UpdateFromOneWay(column,s,opens[0]))return true;break;
		case 2:if(UpdateFromTwoWay(column,s,(0+1+2)-(opens[0]+opens[1])))return true;break;
		case 3:if(UpdateFromThreeWay(column,s))return true;break;
		default:assert(0);break;
	}
	return false;
}
void InitializeDP()
{
	for(int i=0;i<4;i++)for(int j=1;j<=N*3;j++)VIS[i][j]=false;
	for(int i=0;i<N;i++)DP[i].clear();
}
void Solve()
{
	if(N==1){SolveNis1();return;}
	assert(2<=N&&N<=1000);
	InitializeDP();
//	/-
//	|
//	\-
	for(int i=1;i+2<=N*3;i++)
	{
		if(Dfs(0,State(i,i+1,i+2,Combine(i==1?0:1,0,i+2==N*3?0:2)),0LL))return;
		if(Dfs(0,State(i+2,i+1,i,Combine(i+2==N*3?0:2,0,i==1?0:1)),0LL))return;
	}
//	--
//	/-
//	\-
	if(InsertOneWayNxts(0,2,1,0,0LL))return;
	if(InsertOneWayNxts(0,2,1,2,0LL))return;
	if(InsertOneWayNxts(0,1,N*3,0,0LL))return;
	if(InsertOneWayNxts(0,1,N*3,2,0LL))return;
	assert(0);
//	int counter=0;
//	for(int column=0;column+1<N;++column)
//	{
////		printf("DP[%d].size()=%d,counter=%d\n",column,(int)DP[column].size(),counter+=(int)DP[column].size());
//		assert(!DP[column].empty());
//		for(map<LL,LL>::const_iterator it=DP[column].begin();it!=DP[column].end();++it)
//		{
//			const State &s=State(it->first);
////			printf("%d %d %d\n",s.a,s.b,s.c);
//			if(!s.IsValid(S[column]))continue;
////			Print(s,column);
//			vector<int>opens;
//			for(int i=0;i<3;i++)if(Digit(s.o,i))opens.push_back(i);
//			switch(opens.size())
//			{
//				case 0:break;
//				case 1:UpdateFromOneWay(column,s,opens[0]);break;
//				case 2:UpdateFromTwoWay(column,s,(0+1+2)-(opens[0]+opens[1]));break;
//				case 3:UpdateFromThreeWay(column,s);break;
//				default:assert(0);break;
//			}
//		}
//	}
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("waz36.in","r",stdin);
//	freopen("out.txt","w",stdout);
	scanf("%d",&N);
	for(int i=0;i<3;i++)for(int j=0;j<N;j++)scanf("%d",&S[j][i]);
	Solve();
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<N;j++)
		{
			if(j)putchar(' ');
			printf("%d",S[j][i]);
		}
		puts("");
	}
	return 0;
}
/*
9
  0  0  0  0  1  0  3  0  0
  0  0  0 15 14  0  0  0  0
  0  0  0  0 27  0  0  0  0

 21 20 17 16  1  2  3  6  7
 22 19 18 15 14 13  4  5  8
 23 24 25 26 27 12 11 10  9
*/
