#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
int T,R,C,N;
LL ROW0,COLUMN0,ROW1,COLUMN1;
bool Cmp(const LL &a,const LL &b)
{
	for(int i=0;i<R*C;i++)
	{
		if((a&(1LL<<i))!=(b&(1LL<<i)))return (a&(1LL<<i))>(b&(1LL<<i));
	}
	return false;
}
struct Object
{
	vector<LL>s;
	char c;
	Object(){}
	Object(LL *tmp,const char _c):c(_c)
	{
		s.clear();
		for(int i=0;i<4;i++)
		{
			while((tmp[i]&ROW0)==0LL)tmp[i]>>=C;
			while((tmp[i]&COLUMN0)==0LL)tmp[i]>>=1;
			for(int r=0;;r++)
			{
				LL t0=(tmp[i]<<(r*C));
				for(int c=0;;c++)
				{
					LL t1=(t0<<c);
					s.push_back(t1);
					if((t1&COLUMN1)!=0LL)break;
				}
				if((t0&ROW1)!=0LL)break;
			}
		}
		sort(s.begin(),s.end(),Cmp);
		s.resize(unique(s.begin(),s.end())-s.begin());
	}
	bool operator<(const Object &o)const{return c<o.c;}
};
vector<Object>O;
int ITMP[5];
bool USED[5];
vector<int>REC;
LL Lowbit(const LL &v){return v&(-v);}
bool Dfs(const int dep,const LL now,const LL low)
{
	if(dep==N)return true;
	for(int o=0;o<N;o++)if(!USED[o])
	{
		USED[o]=true;
		REC.push_back(o);
		for(int &i=ITMP[dep]=0;i<O[o].s.size();i++)
		{
			LL s=O[o].s[i];
			if(Lowbit(s)<=low)continue;
			if((now&s)==0LL&&Dfs(dep+1,now|s,Lowbit(s)))return true;
		}
		USED[o]=false;
		REC.pop_back();
	}
	return false;
}
int main()
{
	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&R,&C,&N);
		ROW0=COLUMN0=ROW1=COLUMN1=0LL;
		for(int i=0;i<C;i++)ROW0|=(1LL<<i),ROW1|=(1LL<<(C*(R-1)+i));
		for(int i=0;i<R;i++)COLUMN0|=(1LL<<(i*C)),COLUMN1|=(1LL<<(i*C+(C-1)));
		O.clear();
		for(int i=0;i<N;i++)
		{
			static char tmp[4][5],equal[2];
			if(i)scanf("%s",equal),assert(equal[0]=='='&&equal[1]=='\0');
			for(int j=0;j<4;j++)scanf("%s",tmp[j]);
			LL s[4]={0LL,0LL,0LL,0LL};
			char c='\0';
			for(int j=0;j<16;j++)if(tmp[j/4][j%4]!='.')
			{
				assert(c=='\0'||c==tmp[j/4][j%4]);
				c=tmp[j/4][j%4];
				s[0]|=(1LL<<(  (j/4)*C+  (j%4)));
				s[1]|=(1LL<<((3-j%4)*C+  (j/4)));
				s[2]|=(1LL<<((3-j/4)*C+(3-j%4)));
				s[3]|=(1LL<<(  (j%4)*C+(3-j/4)));
			}
			assert(c!='\0');
			O.push_back(Object(s,c));
		}
		sort(O.begin(),O.end());
		for(int i=0;i<N;i++)USED[i]=false;
		REC.clear();
		assert(Dfs(0,0LL,0LL));
		char ans[R][C];
		for(int i=0;i<R*C;i++)ans[i/C][i%C]='.';
		assert(REC.size()==N);
		for(int i=0;i<N;i++)
		{
			const int o=REC[i];
			LL s=O[o].s[ITMP[i]];
			for(int j=0;j<R*C;j++)if(s&(1LL<<j))
			{
				assert(ans[j/C][j%C]=='.');
				ans[j/C][j%C]=O[o].c;
			}
		}
		for(int i=0;i<R;i++)
		{
			for(int j=0;j<C;j++)putchar(ans[i][j]);
			puts("");
		}
		if(T)puts("#");
	}
	return 0;
}
