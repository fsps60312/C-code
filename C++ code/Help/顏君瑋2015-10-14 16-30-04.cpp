#include<cstdio>
#include<set>
#include<vector>
#define print(x,...) fprintf(OUT,x,##__VA_ARGS__),printf(x,##__VA_ARGS__)
FILE *OUT=fopen("out.txt","w");
using namespace std;
set<int>S;
vector<int>CNT[5][5];
void Fill(int s,int *v){for(int i=0;i<4;i++)v[i]=s%10,s/=10;}
void Refresh(const int &guess)
{
	static int aa[4],bb[4];
	Fill(guess,aa);
	for(int i=0;i<=4;i++)for(int j=0;j<=4;j++)CNT[i][j].clear();
	for(int v:S)
	{
		Fill(v,bb);
		static bool b1[4],b2[4];
		for(int i=0;i<4;i++)b1[i]=b2[i]=false;
		int a=0,b=0;
		for(int i=0;i<4;i++)if(aa[i]==bb[i])a++,b1[i]=b2[i]=true;
		for(int i=0;i<4;i++)
		{
			if(b1[i])continue;
			for(int j=0;j<4;j++)
			{
				if(b2[j])continue;
				if(aa[i]==bb[j]){b++,b1[i]=b2[j]=true;break;}
			}
		}
		CNT[a][b].push_back(v);
	}
	int a=0,b=0;
	for(int i=0;i<=4;i++)
	{
		for(int j=0;j<=4;j++)
		{
//			if(j)printf(", ");
			if(CNT[i][j].size())print("%dA%dB:%d\n",i,j,CNT[i][j].size());
			if(CNT[i][j].size()>CNT[a][b].size())a=i,b=j;
		}
//		puts("");
	}
	print("One of maximum: %dA%dB (%d remains)\n",a,b,CNT[a][b].size());
	scanf("%d%d",&a,&b);
	S.clear();
	vector<int>&v=CNT[a][b];
	for(int i:v)S.insert(i);
	print("%d conditions remain\n",S.size());
	for(int v:S)fprintf(OUT," %04d",v);
}
int main()
{
	for(int i=0;i<=4;i++)for(int j=0;j<=4;j++)CNT[i][j].clear();
	for(int s=0;s<=9999;s++)
	{
		static int v[4];
		Fill(s,v);
		bool ok=true;
		for(int i=0;i<4&&ok;i++)for(int j=i+1;j<4&&ok;j++)if(v[i]==v[j])ok=false;
		if(!ok)continue;
		S.insert(s);
	}
	print("%d conditions remain\n",S.size());
	int guess;
	while(scanf("%d",&guess)==1)
	{
		Refresh(guess);
	}
	return 0;
}
