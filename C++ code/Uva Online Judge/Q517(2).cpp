#include<cstdio>
const int INF=2147483647;
int N,T,A,C[8][4];
char S[17];
inline void getmin(int &a,const int &b){if(b<a)a=b;}
inline int Bit(const int &n,const int &i){return (n&(1<<i))>>i;}
inline void SetBit(int &n,const int &i,const int &v){n=((n&~(1<<i))|(v<<i));}
int Transform(const int &a,const int &r)
{
	int ans=a;
	for(int i=0;i<N;i++)if(Bit(a,i)==C[r&7][0]&&Bit(a,(i+2)%N)==C[r&7][1]&&Bit(a,(i+3)%N)==C[r&7][2])SetBit(ans,(i+2)%N,C[r&7][3]);
	return ans;
}
int Solve()
{
	for(int i1=0,v1=A,i2=0,v2=A;;)
	{
//		printf("(%d,%d)(%d,%d)\n",i1,v1,i2,v2);
		v1=Transform(v1,i1++);
		if(i2!=INF)
		{
			v2=Transform(v2,i2++);
			v2=Transform(v2,i2++);
			if(v1==v2&&(i1&7)==(i2&7))
			{
				i1+=(T-i1)/(i2-i1)*(i2-i1);
				i2=v2=INF;
			}
		}
		if(i1==T)
		{
			int v=0;
			for(int i=0;i<N;i++)SetBit(v,i,Bit(v1,N-1-i));
			int ans=v;
			for(int i=1;i<N;i++)getmin(ans,v=(v>>1)+((v&1)<<(N-1)));
			return ans;
		}
	}
}
int main()
{
	while(scanf("%d",&N)==1)
	{
		scanf("%s",S);
		A=0;
		for(int i=0;i<N;i++)A=A*2+(S[i]-'a');
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
