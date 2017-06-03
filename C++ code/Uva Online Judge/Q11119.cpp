#include<cstdio>
#include<cassert>
#include<map>
#include<vector>
#include<queue>
using namespace std;
int Encode(const char *s){assert(s[0]>='A'&&s[0]<='Z'&&s[1]>='a'&&s[1]<='z');return (s[0]-'A')*26+(s[1]-'a');}
char *Decode(const int code){static char ans[3];ans[0]='A'+code/26,ans[1]='a'+code%26,ans[2]='\0';return ans;}
struct Atoms
{
	int SZ;
	map<int,int>IDX;
	vector<int>RIDX;
	bool ScanfElement()
	{
		assert(scanf("%d",&SZ)==1);
		if(SZ==0)return false;
		IDX.clear(),RIDX.clear();
		static char tmp[3];
		for(int i=0;i<SZ;i++)
		{
			assert(scanf("%s",tmp)==1);
			const int code=Encode(tmp);
			assert(IDX.find(code)==IDX.end());
			IDX[code]=i;
			RIDX.push_back(code);
		}
		return true;
	}
	vector<vector<int> >ATTRACT;
	void ScanfAttract(const int type_cnt)
	{
		ATTRACT.clear();
		for(int i=0;i<SZ;i++)
		{
			vector<int>s,ans;
			ans.resize(type_cnt,-1);
			for(int j=0,v;j<type_cnt;j++)
			{
				assert(scanf("%d",&v)==1&&ans[type_cnt-v]==-1);
				ans[type_cnt-v]=j;
			}
			ATTRACT.push_back(ans);
		}
	}
	int GetIdx(const int code)const
	{
		const auto it=IDX.find(code);
		assert(it!=IDX.end());
		return it->second;
	}
}CAT,ANI;
struct StableMarriageSolver
{
	vector<vector<int> >LA,LB,PA,PB;
	vector<int>MA,MB,CUR;
	int N;
	void Solve()
	{
//		printf("N=%d\n",N);
		assert((int)LA.size()==N&&(int)LB.size()==N);
		for(const auto &v:LA)assert((int)v.size()==N);
		for(const auto &v:LB)assert((int)v.size()==N);
		PA.resize(N),PB.resize(N);
		for(int i=0;i<N;i++)
		{
			PA[i].resize(N,-1),PB[i].resize(N,-1);
			for(int j=0;j<N;j++)PA[i][LA[i][j]]=j,PB[i][LB[i][j]]=j;
			for(int j=0;j<N;j++)assert(PA[i][j]!=-1&&PB[i][j]!=-1);
		}
		MA.clear(),MB.clear(),CUR.clear();
		MA.resize(N,-1),MB.resize(N,-1),CUR.resize(N,0);
		queue<int>q;
		for(int i=0;i<N;i++)q.push(i);
		while(!q.empty())
		{
			const int u=q.front();q.pop();
//			printf("u=%d\n",u);
			assert(MA[u]==-1);
			for(;;)
			{
				assert(CUR[u]<N);
				const int nxt=LA[u][CUR[u]++];
				if(MB[nxt]==-1){MB[nxt]=u,MA[u]=nxt;break;}
				else if(PB[nxt][u]<PB[nxt][MB[nxt]])
				{
					MA[MB[nxt]]=-1;
					q.push(MB[nxt]);
					MB[nxt]=u,MA[u]=nxt;
					break;
				}
			}
		}
	}
}SOLVER;
int main()
{
//	freopen("in.txt","r",stdin);
	while(CAT.ScanfElement())
	{
		assert(ANI.ScanfElement());
		CAT.ScanfAttract(ANI.SZ),ANI.ScanfAttract(CAT.SZ);
		static int kase=0;kase++;
		for(int mixcount=1;;mixcount++)
		{
			assert(scanf("%d",&SOLVER.N)==1);
			const int n=SOLVER.N;
			if(n==0)break;
			vector<int>sa,sb;
			for(int i=0;i<n;i++)
			{
				static char tmp[5];assert(scanf("%s",tmp)==1);
				sa.push_back(CAT.GetIdx(Encode(&tmp[0])));
				sb.push_back(ANI.GetIdx(Encode(&tmp[2])));
			}
			do
			{
				multimap<int,int>idxa,idxb;
				for(int i=0;i<n;i++)idxa.insert(make_pair(sa[i],i)),idxb.insert(make_pair(sb[i],i));
				auto &la=SOLVER.LA,&lb=SOLVER.LB;
				la.resize(n),lb.resize(n);
				for(int i=0;i<n;i++)
				{
					auto tidxa=idxa,tidxb=idxb;
					la[i].clear(),lb[i].clear();
					for(const int e:CAT.ATTRACT[sa[i]])
					{
						auto it=tidxb.begin();
						while((it=tidxb.find(e))!=tidxb.end())la[i].push_back(it->second),tidxb.erase(it);
					}
					for(const int e:ANI.ATTRACT[sb[i]])
					{
						auto it=tidxa.begin();
						while((it=tidxa.find(e))!=tidxa.end())lb[i].push_back(it->second),tidxa.erase(it);
					}
				}
			}while(0);
			SOLVER.Solve();
//			for(int i=0;i<CAT.SZ;i++)printf(" %s",Decode(CAT.RIDX[i]));puts("");
//			for(int i=0;i<ANI.SZ;i++)printf(" %s",Decode(ANI.RIDX[i]));puts("");
			printf("Scenario %d, Mixture %d:\n",kase,mixcount);
			for(int i=0;i<n;i++)
			{
				if(i)putchar(' ');
				assert(SOLVER.MB[SOLVER.MA[i]]==i);
				printf("%s",Decode(CAT.RIDX[sa[i]]));
				printf("%s",Decode(ANI.RIDX[sb[SOLVER.MA[i]]]));
			}
			puts("");
			puts("");
		}
	}
	return 0;
}
