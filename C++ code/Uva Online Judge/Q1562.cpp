#include<cstdio>
#include<map>
using namespace std;
int T,M,N,MAT[10][10];
char S[201];
map<int,int>IDX;
bool Upper(char &c){return c>='A'&&c<='Z';}
bool Lower(char &c){return c>='a'&&c<='z';}
bool Digit(char &c){return c>='0'&&c<='9';} 
void ClearRow(int r1){for(int i=0;i<=N;i++)MAT[r1][i]=0;}
int GetAtom(char *s)
{
	int t=*(s++);
	if(Lower(*s))t+=*s*1000;
	if(IDX.find(t)==IDX.end()){ClearRow(++M);IDX[t]=M;}
	return IDX[t];
}
int GetCnt(char *s)
{
	s++;if(Lower(*s))s++;
	if(!Digit(*s))return 1;
	return *s-'0';
}
void initMAT()
{
	IDX.clear();
	N=2;
	for(int i=0;S[i];i++)if(S[i]=='+')N++;
	M=-1;
	for(int i=0,left=1,j=0;S[i];i++)
	{
		if(S[i]=='+')j++;
		else if(S[i]=='=')j++,left=-1;
		else if(Upper(S[i]))MAT[GetAtom(S+i)][j]+=left*GetCnt(S+i);
	}
	M++;
	printf("M=%d\n",M);
}
void showMAT(char *msg)
{
	for(int i=0;i<M;i++)
	{
		for(map<int,int>::iterator it=IDX.begin();it!=IDX.end();it++)
		{
			if(it->second==i)
			{
				int v=it->first;
				if(v<1000)printf("%c",v);
				else printf("%c%c")
			}
		}
	}
}
int main()
{
	freopen("in.txt","r",stdin);
//	printf("%d %d %d %d %d",'A','a','0','+','=');
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",S);
		initMAT();
//		showMAT("initial");
		solve();
	}
	return 0;
}
