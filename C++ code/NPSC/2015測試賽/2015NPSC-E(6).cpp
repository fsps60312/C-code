#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
//FC "C:\Users\user\Desktop\C++ Code\Other\NPSC\out.txt" "C:\Users\user\Desktop\C++ Code\Other\NPSC\pa.out" /n
using namespace std;
typedef long long LL;
int T,R,C,N;
LL ROW1,COLUMN1,ALL;
bool Cmp(const LL &a,const LL &b)
{
	for(int i=0;i<R*C;i++)
	{
		if((a&(1LL<<i))!=(b&(1LL<<i)))return (a&(1LL<<i))>(b&(1LL<<i));
	}
	return false;
}
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
struct Object
{
	vector<LL>s;
	char c;
	Object(){}
	Object(LL *tmp,const char _c):c(_c)
	{
		const LL row0=(1LL<<4)-1LL;
		const LL column0=(1LL<<0)+(1LL<<4)+(1LL<<8)+(1LL<<12);
		s.clear();
		for(int i=0;i<4;i++)
		{
			while((tmp[i]&row0)==0LL)tmp[i]>>=4;
			while((tmp[i]&column0)==0LL)tmp[i]>>=1;
			LL ttt=0LL;
			for(int j=0;j<16;j++)if((tmp[i]&(1LL<<j))!=0LL)ttt|=(1LL<<(j/4*C+j%4));
			tmp[i]=ttt;
			for(int r=0;;r++)
			{
				LL t0=(tmp[i]<<(r*C));
				for(int c=0;;c++)
				{
					LL t1=(t0<<c);
					if((ALL&t1)==t1)s.push_back(t1);
					if((t1&COLUMN1)!=0LL)break;
				}
				if((t0&ROW1)!=0LL)break;
			}
		}
		sort(s.begin(),s.end(),Cmp);
		s.resize(unique(s.begin(),s.end())-s.begin());
//		for(int i=0;i<s.size();i++)
//		{
//			printf("i=%d\n",i);
//			Print(s[i]);
//		}puts("");
	}
	bool operator<(const Object &o)const{return c<o.c;}
};
vector<Object>O;
int ITMP[5];
bool USED[5];
LL Lowbit(const LL &v){return v&(-v);}
char ANS[6][6],TMP[6][6];
bool Better()
{
	for(int i=0;i<R;i++)
	{
		for(int j=0;j<C;j++)if(TMP[i][j]!=ANS[i][j])return TMP[i][j]<ANS[i][j];
	}
	return false;
}
bool FOUND;
void Dfs(const int dep,const LL now,const LL low)
{
//	Print(now);
	if(dep==N)
	{
//		puts("pass");
		if(Better())
		{
			for(int i=0;i<R;i++)for(int j=0;j<C;j++)ANS[i][j]=TMP[i][j];
			FOUND=true;
		}
		return;
	}
	for(int o=0;o<N;o++)if(!USED[o])
	{
//		for(int i=0;i<dep;i++)printf(" ");printf("%d%c\n",dep,O[o].c);
		USED[o]=true;
		bool equal=true;
		bool possible=true;
		for(int &i=ITMP[dep]=0,j=-1;i<O[o].s.size();i++)
		{
			LL s=O[o].s[i];
			if(equal)while((1LL<<j)<Lowbit(s))
			{
				if(ANS[j/C][j%C]>TMP[j/C][j%C]){equal=false;break;}
				if(ANS[j/C][j%C]<TMP[j/C][j%C]){equal=false;possible=false;break;}
				j++;
			}
			if(!possible)break;
			while((1LL<<j)<Lowbit(s))j++;
			assert((1LL<<j)==Lowbit(s));
			if(Lowbit(s)<=low)continue;
//			if(O[o].c=='B'&&Lowbit(s)==1LL)printf("YA");
			if((now&s)==0LL&&O[o].c<=ANS[j/C][j%C])
			{
				for(int k=0;k<R*C;k++)if(s&(1LL<<k))
				{
					assert(TMP[k/C][k%C]=='Z');
					TMP[k/C][k%C]=O[o].c;
				}
				Dfs(dep+1,now|s,Lowbit(s));
				for(int k=0;k<R*C;k++)if(s&(1LL<<k))
				{
					assert(TMP[k/C][k%C]==O[o].c);
					TMP[k/C][k%C]='Z';
				}
			}
		}
		USED[o]=false;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("pa.in","r",stdin);
	freopen("out.txt","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&R,&C,&N);
		ALL=(1LL<<(R*C))-1LL;
		ROW1=COLUMN1=0LL;
		for(int i=0;i<C;i++)ROW1|=(1LL<<(C*(R-1)+i));
		for(int i=0;i<R;i++)COLUMN1|=(1LL<<(i*C+(C-1)));
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
				s[0]|=(1LL<<(  (j/4)*4+  (j%4)));
				s[1]|=(1LL<<((3-j%4)*4+  (j/4)));
				s[2]|=(1LL<<((3-j/4)*4+(3-j%4)));
				s[3]|=(1LL<<(  (j%4)*4+(3-j/4)));
			}
			assert(c>='A'&&c<='Y');
			O.push_back(Object(s,c));
		}
		sort(O.begin(),O.end());
		for(int i=0;i<N;i++)USED[i]=false;
		for(int i=0;i<R*C;i++)ANS[i/C][i%C]=TMP[i/C][i%C]='Z';
		FOUND=false;
		Dfs(0,0LL,0LL);
		assert(FOUND);
		for(int i=0;i<R;i++)
		{
			for(int j=0;j<C;j++)putchar(ANS[i][j]=='Z'?'.':ANS[i][j]);
			puts("");
		}
		if(T)puts("#");
	}
	return 0;
}
