#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
int T,R,C,N;
LL ROW0,COLUMN0,ROW1,COLUMN1;
void Print(const LL s)
{
	for(int i=0;i<R;i++)
	{
		for(int j=0;j<C;j++)
		{
			if(s&(1LL<<(i*C+j)))putchar('1');
			else putchar('0');
		}
		putchar('\n');
	}
}
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
	LL s[4];
	char c;
	Object(){}
	Object(const LL s0,const LL s1,const LL s2,const LL s3,const char _c):s{s0,s1,s2,s3},c(_c)
	{
		for(int i=0;i<4;i++)
		{
//			Print(s[i]);
			while((s[i]&ROW0)==0LL)s[i]>>=C;
			while((s[i]&COLUMN0)==0LL)s[i]>>=1;
		}
		sort(s,s+4,Cmp);
	}
	bool operator<(const Object &o){return c<o.c;}
};
vector<Object>O;
int ITMP[5],RTMP[5],CTMP[5];
bool USED[5];
vector<int>REC;
LL Lowbit(const LL &v){return v&(-v);}
bool Dfs(const int dep,const LL now,const LL low)
{
//	printf("dep=%d,low=%lld\n",dep,low);
//	Print(now);
	if(dep==N)return true;
	for(int o=0;o<N;o++)if(!USED[o])
	{
		USED[o]=true;
		REC.push_back(o);
		for(int &i=ITMP[dep]=0;i<4;i++)
		{
			LL s=O[o].s[i];
			bool same=false;
			for(int j=0;j<i;j++)if(O[o].s[j]==s){same=true;break;}
			if(same)continue;
			for(int &r=RTMP[dep]=0;;r++)
			{
				LL s0=(s<<(r*C));
				for(int &c=CTMP[dep]=0;;c++)
				{
					LL s1=(s0<<c);
					if(Lowbit(s1)<=low)continue;
					if((now&s1)==0LL&&Dfs(dep+1,now|s1,Lowbit(s1)))return true;
					if((s1&COLUMN1)!=0LL)break;
				}
				if((s0&ROW1)!=0LL)break;
			}
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
//		puts("ROW0"),Print(ROW0);
//		puts("ROW1"),Print(ROW1);
//		puts("COLUMN0"),Print(COLUMN0);
//		puts("COLUMN1"),Print(COLUMN1);
		O.clear();
		for(int i=0;i<N;i++)
		{
			static char tmp[4][5],equal[2];
			if(i)scanf("%s",equal),assert(equal[0]=='='&&equal[1]=='\0');
			for(int j=0;j<4;j++)scanf("%s",tmp[j]);
//			for(int j=0;j<4;j++)puts(tmp[j]);puts("");
			LL s0=0LL,s1=0LL,s2=0LL,s3=0LL;
			char c='\0';
			for(int j=0;j<16;j++)if(tmp[j/4][j%4]!='.')
			{
				assert(c=='\0'||c==tmp[j/4][j%4]);
				c=tmp[j/4][j%4];
				s0|=(1LL<<(  (j/4)*C+  (j%4)));
				s1|=(1LL<<((3-j%4)*C+  (j/4)));
				s2|=(1LL<<((3-j/4)*C+(3-j%4)));
				s3|=(1LL<<(  (j%4)*C+(3-j/4)));
			}
			assert(c!='\0');
			O.push_back(Object(s0,s1,s2,s3,c));
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
			LL s=(O[o].s[ITMP[i]]<<(RTMP[i]*C+CTMP[i]));
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
