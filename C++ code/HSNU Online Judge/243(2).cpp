#include<cstdio>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
static int D[4][2]={{1,0},{0,-1},{-1,0},{0,1}};
struct Kunai
{
	int x,y,dist;
	Kunai(){}
	Kunai(const int _x,const int _y):x(_x),y(_y),dist(INF){}
};
struct Info
{
	int v;
	Kunai *k;
	Info(){}
	Info(Kunai *_k,const int _v):k(_k),v(_v){}
	bool operator<(const Info &i)const{return v<i.v;}
};
map<int,vector<Info> >INFO[4];
vector<Kunai>KUNAI[4];
void DealWith(vector<Info>&va,vector<Info>&vb)
{
	sort(va.begin(),va.end()),sort(vb.begin(),vb.end());
	for(int l=0,r=0;l<va.size();l++)
	{
		while(r<vb.size()&&va[l].v>=vb[r].v)r++;
		getmin(va[l].k->dist,vb[r].v-va[l].v);
		getmin(vb[r].k->dist,vb[r].v-va[l].v);
	}
}
void DealWith(map<int,vector<Info> >&ma,map<int,vector<Info> >&mb){for(auto ita=ma.begin(),itb=mb.begin();ita!=ma.end();ita++)if((itb=mb.find(ita->first))!=mb.end())DealWith(ita->second,itb->second);}
void UpRightCollide()
{
	for(int d=0;d<4;d++)INFO[d].clear();
	for(int d=0;d<4;d++)for(int i=0;i<KUNAI[d].size();i++)
	{
		Kunai &k=KUNAI[d][i];
		INFO[d][k.x+k.y].push_back(Info(&k,k.x));
	}
	DealWith(INFO[0],INFO[1]);
	DealWith(INFO[3],INFO[2]);
}
void LeftDownCollide()
{
	for(int d=0;d<4;d++)INFO[d].clear();
	for(int d=0;d<4;d++)for(int i=0;i<KUNAI[d].size();i++)
	{
		Kunai &k=KUNAI[d][i];
		INFO[d][k.x-k.y].push_back(Info(&k,k.x));
	}
	DealWith(INFO[0],INFO[1]);
	DealWith(INFO[3],INFO[2]);
}
void LinearCollide()
{
	for(int d=0;d<4;d++)INFO[d].clear();
	for(int d=0;d<4;d++)for(int i=0;i<KUNAI[d].size();i++)
	{
		int same=KUNAI[d][i].y,diff=KUNAI[d][i].x;
		if(d&1)swap(same,diff);
		INFO[d][same].push_back(Info(&KUNAI[d][i],diff));
	}
	DealWith(INFO[0],INFO[2]);
	DealWith(INFO[1],INFO[3]);
}
int W,H,N;
bool VIS[1001][1001];
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&W,&H,&N)==3)
	{
		for(int d=0;d<4;d++)KUNAI[d].clear();
		for(int i=0,d;i<N;i++)
		{
			static Kunai k;
			scanf("%d%d%d",&k.x,&k.y,&d);
			switch(d)
			{
				case 0:k.dist=W-k.x;break;
				case 1:k.dist=k.y-1;break;
				case 2:k.dist=k.x-1;break;
				case 4:k.dist=H-k.y;break;
			}
			KUNAI[d].push_back(k);
		}
		LinearCollide();
		UpRightCollide();
		LeftDownCollide();
		for(int i=1;i<=W;i++)for(int j=1;j<=H;j++)VIS[i][j]=false;
		int cnt=0;
		for(int d=0;d<4;d++)for(int i=0;i<KUNAI[d].size();i++)
		{
			const Kunai &k=KUNAI[d][i];
			for(int j=0;j<=k.dist;j++)
			{
				int x=k.x+D[d][0]*j,y=k.y+D[d][1]*j;
				if(!VIS[x][y])VIS[x][y]=true,cnt++;
			}
		}
		for(int i=1;i<=H;i++)
		{
			for(int j=1;j<=W;j++)printf("%d",VIS[j][i]);
			puts("");
		}
		printf("%d\n",cnt);
	}
	return 0;
}
