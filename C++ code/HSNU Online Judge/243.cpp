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
map<int,vector<int> >IDX[4];
vector<Kunai>KUNAI[4];
int DNOW;
bool CmpXI(const int a,const int b){return KUNAI[DNOW][a].x<KUNAI[DNOW][b].x;}
bool CmpYI(const int a,const int b){return KUNAI[DNOW][a].y<KUNAI[DNOW][b].y;}
void Collide()
{
	
}
void LinearCollide()
{
	for(int d=0;d<4;d++)IDX[d].clear();
	for(int d=0;d<4;d++)for(int i=0;i<KUNAI[d].size();i++)IDX[d][d&1?KUNAI[d][i].x:KUNAI[d][i].y].push_back(i);
	for(auto it0=IDX[0].begin(),it2=IDX[1].begin();it0!=IDX[0].end();it0++)if((it2=IDX[2].find(it0->first))!=IDX[2].end())
	{
		vector<int>&idx0=it0->second,&idx2=it2->second;
		DNOW=0,sort(idx0.begin(),idx0.end(),CmpXI);
		DNOW=2,sort(idx2.begin(),idx2.end(),CmpXI);
		for(int l=0,r=0;l<idx0.size();l++)
		{
			while(r<idx2.size()&&KUNAI[0][idx0[l]].x>=KUNAI[2][idx2[r]].x)r++;
			if(r==idx2.size())break;
			Kunai &kl=KUNAI[0][idx0[l]],&kr=KUNAI[2][idx2[r]];
			getmin(kl.dist,(kr.x-kl.x)/2),getmin(kr.dist,(kr.x-kl.x)/2);
		}
	}
	for(auto it1=IDX[1].begin(),it3=IDX[3].begin();it1!=IDX[1].end();it1++)if((it3=IDX[3].find(it1->first))!=IDX[3].end())
	{
		vector<int>&idx1=it1->second,&idx3=it3->second;
		DNOW=1,sort(idx1.begin(),idx1.end(),CmpYI);
		DNOW=3,sort(idx3.begin(),idx3.end(),CmpYI);
		for(int u=0,d=0;u<idx1.size();u++)
		{
			while(d<idx3.size()&&KUNAI[1][idx1[u]].y>=KUNAI[3][idx3[d]].y)d++;
			if(d==idx3.size())break;
			Kunai &ku=KUNAI[1][idx1[u]],&kd=KUNAI[3][idx3[d]];
			getmin(ku.dist,(kd.y-ku.y)/2),getmin(kd.dist,(kd.y-ku.y)/2);
		}
	}
}
int W,H,N;
int main()
{
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
		TiltingCollide();
		
	}
	return 0;
}
