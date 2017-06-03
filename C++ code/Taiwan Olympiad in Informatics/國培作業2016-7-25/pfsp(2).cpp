#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<ctime>
using namespace std;
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
template<class T>inline bool getmin(T&a,const T&b){return b<=a?(a=b,true):false;}
int W,M,S[20][100];
int T[20];
int COUNT=0;
int Cost(const vector<int>&order)
{
	++COUNT;
	if(COUNT==5000000)exit(0);
//	if(++count%1000000==0)printf("count=%d\n",count);
	for(int i=0;i<M;i++)T[i]=0;
	for(const int w:order)
	{
		T[0]+=S[0][w];
		for(int i=1;i<M;i++)
		{
			getmax(T[i],T[i-1]);
			T[i]+=S[i][w];
		}
	}
	return T[M-1];
}
unsigned int Rand()
{
	unsigned int seed=0x20160725;
	seed*=0xdefaced,seed+=0x95138;
	return seed+=seed>>20;
}
int best=2147483647;//Cost(s);
void Print(const vector<int>&s)
{
//	if(best==1582)
	if(best==1278)
	{
		printf("best=%d, count=%d, ",best,COUNT);
		for(int i=0;i<W;i++)
		{
			if(i)putchar(' ');
			printf("%d",s[i]+1);
		}
		puts("");
//		exit(0);
	}
}
#include<set>
int main()
{
	freopen("tai20_5_1.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	srand((unsigned int)time(NULL));
	scanf("%d%d%*s",&W,&M);
	for(int i=0;i<M;i++)for(int j=0;j<W;j++)scanf("%d",&S[i][j]);
	vector<int>s;
	for(int i=0;i<W;i++)s.push_back(i);
	set<vector<int> >vis;
	while(true)
	{
		random_shuffle(s.begin(),s.end());
//		const unsigned int i=Rand()%(unsigned int)(W-1);
		if(getmin(best,Cost(s)))Print(s);
		for(int changed=true;changed;)
		{
			changed=false;
			for(int i=0;i<W;i++)for(int j=i+1;j<W;j++)
			{
				swap(s[i],s[j]);
				if(vis.find(s)!=vis.end())swap(s[i],s[j]);
				else
				{
					vis.insert(s);
					if(getmin(best,Cost(s)))Print(s),changed=true;
					else swap(s[i],s[j]);
				}
			}
			for(int i=0;i<W;i++)for(int j=i+2;j<W;j++)
			{
				rotate(s.begin()+i,s.begin()+i+1,s.begin()+j+1);
				if(vis.find(s)!=vis.end())rotate(s.begin()+i,s.begin()+j,s.begin()+j+1);
				else
				{
					vis.insert(s);
					if(getmin(best,Cost(s)))Print(s),changed=true;
					else rotate(s.begin()+i,s.begin()+j,s.begin()+j+1);
				}
				rotate(s.begin()+i,s.begin()+j,s.begin()+j+1);
				if(vis.find(s)!=vis.end())rotate(s.begin()+i,s.begin()+i+1,s.begin()+j+1);
				else
				{
					vis.insert(s);
					if(getmin(best,Cost(s)))Print(s),changed=true;
					else rotate(s.begin()+i,s.begin()+i+1,s.begin()+j+1);
				}
			}
		}
	}
	return 0;
}
