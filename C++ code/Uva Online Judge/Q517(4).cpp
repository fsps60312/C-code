#include<cstdio>
const int INF=2147483647;
int N,T,A,C[8][4];
char S[17];
inline void getmin(int &a,const int &b){if(b<a)a=b;}
inline int Bit(const int &n,const int &i){return (n&(1<<i))>>i;}
inline void SetBit(int &n,const int &i,const int &v){n=((n&~(1<<i))|(v<<i));}
inline int Transform(const int &a)
{
	static int r,i,ans;ans=a;
	for(r=0;r<8;r++)for(i=0;i<N;i++)if(Bit(a,i)==C[r][0]&&Bit(a,(i+2)%N)==C[r][1]&&Bit(a,(i+3)%N)==C[r][2])SetBit(ans,(i+2)%N,C[r][3]);
	return ans;
}
int Solve()
{
	for(int i1=0,v1=A,i2=0,v2=A;;)
	{
//		printf("(%d,%d)(%d,%d)\n",i1,v1,i2,v2);
		if(i1==T)
		{
			int v=0;
			for(int i=0;i<N;i++)SetBit(v,i,Bit(v1,N-1-i));
			int ans=v;
			for(int i=1;i<N;i++)getmin(ans,v=(v>>1)+((v&1)<<(N-1)));
			return ans;
		}
		v1=Transform(v1);i1++;
		if(i2!=INF)
		{
			v2=Transform(v2);i2++;
			v2=Transform(v2);i2++;
			if(v1==v2)
			{
				i1+=(T-i1)/(i2-i1)*(i2-i1);
				i2=v2=INF;
			}
		}
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	while(scanf("%d",&N)==1)
	{
		scanf("%s",S);
		A=0;
		for(int i=0;i<N;i++)A|=(S[i]-'a')<<i;
		for(int i=0;i<8;i++)for(int j=0;j<4;j++)
		{
			static char c;
			do{scanf("%c",&c);}while(c!='a'&&c!='b');
			C[i][j]=c-'a';
		}
		scanf("%d",&T);
		int ans=Solve();
//		printf("%c",'a'+Bit(ans,N-1));
		for(int i=N-1;i>=0;i--)printf("%c",'a'+Bit(ans,i));
		puts("");
	}
	return 0;
}
