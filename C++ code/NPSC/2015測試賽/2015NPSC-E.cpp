#include<cstdio>
#include<vector>
using namespace std;
typedef long long LL;
int T,R,C,N;
LL ROW0,COLUMN0,ROW1,COLUMN1;
struct Object
{
	LL s[4];
	char c;
	Object(){}
	Object(const LL s0,const LL s1,const LL s2,const LL s3,const char _c):s{s0,s1,s2,s3},c(_c)
	{
		for(int i=0;i<4;i++)
		{
			while((s[i]&ROW0)==0LL)s[i]<<=C;
			while((s[i]&COLUMN0)==0LL)s[i]<<=1;
		}
	}
	bool operator<(const Object &o){return c<o.c;}
};
vector<Object>O;
set<LL>VIS;
int I[5],R[5],C[5];
void Dfs(int dep,LL now)
{
	if(dep==N)return;
	if(VIS.find(now)!=VIS.end())
	{
		vector<int>ta;
		
		if(ta<BEST)BEST=ta;
		return;
	}
	for(int &i=I[dep]=0;i<4;i++)
	{
		LL s=O[dep].s[i];
		bool same=false;
		for(int j=0;j<i;j++)if(O[dep].s[j]==s){same=true;break;}
		if(same)continue;
		for(int &r=R[dep]=0;;r++)
		{
			LL s0=(s<<(r*C));
			for(int &c=C[dep]=0;;c++)
			{
				LL s1=(s<<c);
				if((now&s1)==0LL)Dfs(dep+1,now|s1);
				if((s1&COLUMN1)!=0LL)break;
			}
			if((s0&ROW1)!=0LL)break;
		}
	}
}
int main()
{
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
			if(i)scanf("%s",equal),assert(equal[0]=='='&&equal'1'=='\0');
			for(int j=0;j<4;j++)scanf("%s",tmp[j]);
			LL s0=0LL,s1=0LL,s2=0LL,s3=0LL;
			char c='\0';
			for(int j=0;j<16;j++)if(tmp[j/4][j%4]!='.')
			{
				assert(c=='\0'||c==tmp[j/4][j%4]);
				c=tmp[j/4][j%4];
				s0|=(1LL<<((j/4)  *C+(j%4)  ));
				s1|=(1LL<<((3-j%4)*C+(j/4)  ));
				s2|=(1LL<<((3-j/4)*C+(3-j%4)));
				s3|=(1LL<<((j%4)  *C+(3-j/4)));
			}
			assert(c!='\0');
			O.push_back(Object(o,c));
		}
		sort(O.begin(),O.end());
		if(Dfs(0,0LL))
		{
		}
		else
		{
		}
	}
	return 0;
}
