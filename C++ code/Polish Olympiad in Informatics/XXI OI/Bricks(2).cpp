#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
int K,P,Q,N;
struct Brick
{
	int color,cnt;
	Brick(){}
	Brick(const int _color,const int _cnt):color(_color),cnt(_cnt){}
	bool operator<(const Brick &b)const{return cnt>b.cnt;}
};
int ANS[999998];
void Fill(const vector<Brick>&S,const vector<int>&order,const int exclude1,const int exclude2,const int exclude3)
{
	vector<int>s;
	for(int i=0;i<K;i++)if(i!=exclude1&&i!=exclude2&&i!=exclude3)
	{
		for(int j=0;j<S[i].cnt;j++)s.push_back(S[i].color);
	}
	assert(s.size()==order.size());
	for(int i=0;i<(int)s.size();i++)
	{
		ANS[order[i]]=s[i];
	}
}
bool Solve(const vector<Brick>&S)
{
	for(int i=0;i<N;i++)ANS[i]=0;
	if(N&1)
	{
		if(S[0].cnt>N/2+1)return false;
		else if(S[0].cnt==N/2+1)
		{
			if(S[0].color==P||S[0].color==Q)return false;
			for(int i=0;i<S[0].cnt;i++)ANS[i*2]=S[0].color;
			vector<int>order;
			for(int i=1;i<=N-2;i+=2)order.push_back(i);
			Fill(S,order,0,-1,-1);
			return true;
		}
		else if(S[0].cnt==N/2)
		{
			if(S[0].color==P)
			{
				for(int i=0;i<S[0].cnt;i++)ANS[1+i*2]=S[0].color;
				int a=1,b=1;
				while(a<K&&S[a].color==P)a++;
				if(a==K)return false;
				while(b<K&&(S[b].color==Q||(b==a&&S[a].cnt==1)))b++;
				if(b==K)return false;
				if(a==b)
				{
					assert(S[a].cnt>=2);
					for(int i=0;i<S[a].cnt-1;i++)ANS[i*2]=S[a].color;
					ANS[N-1]=S[a].color;
					vector<int>order;
					for(int i=(S[a].cnt-1)*2;i<=N-3;i+=2)order.push_back(i);
					Fill(S,order,0,a,-1);
					return true;
				}
				else
				{
					for(int i=0;i<S[a].cnt;i++)ANS[i*2]=S[a].color;
					for(int i=0;i<S[b].cnt;i++)ANS[N-1-i*2]=S[b].color;
					vector<int>order;
					for(int i=S[a].cnt*2;i<=N-1-S[b].cnt*2;i+=2)order.push_back(i);
					Fill(S,order,0,a,b);
					return true;
				}
			}
			else
			{
				for(int i=0;i<S[0].cnt;i++)ANS[i*2]=S[0].color;
				int a=1;
				while(a<K&&S[a].color==Q)a++;
				if(a==K)return false;
				vector<int>order;
				for(int i=N-2;i>=1;i-=2)order.push_back(i);
				for(int i=S[0].cnt*2;i<=N-1;i+=2)order.push_back(i);
				for(int i=0;i<S[a].cnt;i++)ANS[order.back()]=S[a].color,order.pop_back();
				Fill(S,order,0,a,-1);
				return true;
			}
		}
		else
		{
			int a=0,b=0;
			while(a<K&&S[a].color==P)a++;
			if(a==K)return false;
			while(b<K&&(S[b].color==Q||(b==a&&S[a].cnt==1)))b++;
			if(b==K)return false;
			if(a==b)
			{
				assert(S[a].cnt>=2);
				for(int i=0;i<S[a].cnt-1;i++)ANS[i*2]=S[a].color;
				ANS[N-1]=S[a].color;
				const int l=(S[a].cnt-1)*2,r=N-1-2;
				vector<int>order;
				for(int i=l;i<=r;i+=2)order.push_back(i);
				for(int i=1;i<=l-3;i+=2)order.push_back(i);
				for(int i=r+3;i<N;i+=2)order.push_back(i);
				for(int i=l-1;i<=r+1;i+=2)order.push_back(i);
				Fill(S,order,a,-1,-1);
				return true;
			}
			else
			{
				if(S[a].cnt+S[b].cnt<N/2+1)
				{
					for(int i=0;i<S[a].cnt;i++)ANS[i*2]=S[a].color;
					for(int i=0;i<S[b].cnt;i++)ANS[N-1-i*2]=S[b].color;
					const int l=S[a].cnt*2,r=N-1-S[b].cnt*2;
					vector<int>order;
					for(int i=l;i<=r;i+=2)order.push_back(i);
					for(int i=1;i<=l-3;i+=2)order.push_back(i);
					for(int i=r+3;i<N;i+=2)order.push_back(i);
					for(int i=l-1;i<=r+1;i+=2)order.push_back(i);
					Fill(S,order,a,b,-1);
					return true;
				}
				else
				{
					const int exceed=(S[a].cnt+S[b].cnt)-(N/2+1);
					for(int i=0;i<S[a].cnt;i++)ANS[i*2]=S[a].color;
					for(int i=0;i<S[b].cnt-exceed;i++)ANS[N-1-i*2]=S[b].color;
					for(int i=0;i<exceed;i++)ANS[1+i*2]=S[b].color;
					vector<int>order;
					for(int i=1+exceed*2;i<N;i+=2)order.push_back(i);
					Fill(S,order,a,b,-1);
					return true;
				}
			}
		}
	}
	else
	{
		if(S[0].cnt>N/2)return false;
		else if(S[0].cnt==N/2)
		{
			if(S[0].color==P)return false;
			assert(S[0].color!=P);
			int a=1;
			while(a<K&&S[a].color==Q)a++;
			if(a==K)return false;
			vector<int>ans;
			for(int i=0;i<S[0].cnt;i++)ans.push_back(S[0].color);
			for(int i=1;i<K;i++)if(i!=a)
			{
				for(int j=0;j<S[i].cnt;j++)ans.push_back(S[i].color);
			}
			for(int i=0;i<S[a].cnt;i++)ans.push_back(S[a].color);
			assert((int)ans.size()==N);
			for(int i=0;i<N/2;i++)ANS[i*2]=ans[i],ANS[i*2+1]=ans[N/2+i];
			return true;
		}
		else
		{
			int a=0,b=0;
			while(a<K&&S[a].color==P)a++;
			if(a==K)return false;
			while(b<K&&(S[b].color==Q||(b==a&&S[a].cnt==1)))b++;
			if(b==K)return false;
			vector<int>ans;
			if(a==b)
			{
				assert(S[a].cnt>=2);
				for(int i=0;i<S[a].cnt-1;i++)ans.push_back(S[a].color);
				for(int i=0;i<K;i++)if(i!=a)
				{
					for(int j=0;j<S[i].cnt;j++)ans.push_back(S[i].color);
				}
				ans.push_back(S[a].color);
			}
			else
			{
				for(int i=0;i<S[a].cnt;i++)ans.push_back(S[a].color);
				for(int i=0;i<K;i++)if(i!=a&&i!=b)
				{
					for(int j=0;j<S[i].cnt;j++)ans.push_back(S[i].color);
				}
				for(int i=0;i<S[b].cnt;i++)ans.push_back(S[b].color);
			}
			assert((int)ans.size()==N);
			for(int i=0;i<N/2;i++)ANS[i*2]=ans[i],ANS[i*2+1]=ans[N/2+i];
			return true;
		}
	}
}
vector<Brick>S;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&K,&P,&Q)==3)
	{
		S.clear();
		N=0;
		for(int i=1,v;i<=K;i++)
		{
			scanf("%d",&v);
			S.push_back(Brick(i,v));
			N+=v;
		}
		if(P==Q)
		{
			if(N==1&&S[0].color==P)
			{
				printf("%d\n",P);
				continue;
			}
			if(S[P-1].cnt==1)goto no_solution;
		}
		if(!--S[max(P,Q)-1].cnt)S.erase(S.begin()+(max(P,Q)-1)),--K;
		if(!--S[min(P,Q)-1].cnt)S.erase(S.begin()+(min(P,Q)-1)),--K;
		N-=2;
		sort(S.begin(),S.end());
		assert((int)S.size()==K);
		if(!Solve(S))
		{
			swap(P,Q);
			if(!Solve(S))
			{
				no_solution:;
				puts("0");
			}
			else
			{
				swap(P,Q);
				reverse(ANS,ANS+N);
				goto print_answer;
			}
		}
		else
		{
			print_answer:;
			printf("%d",P);
			for(int i=0;i<N;i++)printf(" %d",ANS[i]);
			printf(" %d\n",Q);
		}
	}
	return 0;
}
