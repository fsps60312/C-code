#include<cstdio>
#include<vector>
using namespace std;
char INPUT[1000000],S[201];
int N,K,MAT[200],VIS[200];
vector<vector<int> > V;
bool Digit(char &c){return c>='0'&&c<='9';}
void getMAT()
{
	gets(INPUT);
	int i=0,m=0;
	while(INPUT[i]==' ')i++;
	for(MAT[m]=0;INPUT[i];i++)
	{
		char &c=INPUT[i];
		if(c==' ')
		{
			if(Digit(INPUT[i-1]))MAT[++m]=0;
			continue;
		}
		MAT[m]=MAT[m]*10+(c-'0');
	}
//	for(int i=0;i<N;i++)printf(" %d",MAT[i]);puts("");
}
bool getK()
{
	gets(INPUT);
	int i=0;
	while(INPUT[i]==' ')i++;
	K=0;
	while(Digit(INPUT[i]))K=K*10+(INPUT[i++]-'0');
	if(!K)return false;
	i++;
	int j=0;
	for(;j<N&&INPUT[i+j];j++)S[j]=INPUT[i+j];
	while(j<N)S[j++]=' ';
	S[N]=0;
//	printf("K=%d\nS='%s'\n",K,S);
	return true;
}
void GetV(int i,vector<int> &v)
{
	for(int u=MAT[i];;u=MAT[u])
	{
		v.push_back(u);
		VIS[u]=1;
		if(u==i)return;
	}
}
int main()
{
//	printf("%d %d %d\n",'0','A','a');
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	while(gets(INPUT))
	{
		sscanf(INPUT,"%d",&N);
		if(!N)break;
		getMAT();
		for(int i=0;i<N;i++)MAT[i]--,VIS[i]=0;
		V.clear();
		for(int i=0;i<N;i++)
		{
			if(VIS[i])continue;
			vector<int> v;
			GetV(i,v);
			V.push_back(v);
		}
		while(getK())
		{
			for(int i=0;i<V.size();i++)
			{
				vector<int> &v=V[i];
//				for(int j=0;j<v.size();j++)printf(" %d",v[j]);puts("");
//				printf("%d %d %d\n",K,v.size(),K%v.size());
				for(int j=0,k=K%v.size();j<v.size();j++,k++,k%=v.size())
				{
//					printf("%d->%d(%d,%d)\n",v[j],v[(j+k)%v.size()],j,k);
					INPUT[v[k]]=S[v[j]];
				}
			}
			INPUT[N]=0;
			printf("%s\n",INPUT);
		}
		puts("");
	}
	return 0;
}
