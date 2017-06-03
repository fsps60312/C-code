#include<cstdio>
#include<vector>
#include<set>
using namespace std;
struct Deq
{
	vector<int>s;
	int l,r;
	void clear(){s.clear();l=0,r=-1;}
	void push_back(const int v){s.push_back(v);r++;}
	void push_back(const int a,const int b,const int c){push_back(a),push_back(b),push_back(c);}
	int pop_front(){return s[l++];}
	int pop_back(){int ans=s[r--];s.pop_back();return ans;}
	void pop(const int a,const int b){for(int i=0;i<a;i++)pop_front();for(int i=0;i<b;i++)pop_back();}
	int front(const int i)const{return s[l+i];}
	int back(const int i)const{return s[r-i];}
	int size()const{return r-l+1;}
	bool empty()const{return r<l;}
	int operator[](const int i)const{return s[l+i];}
};
struct State
{
	Deq p[7],seq;
	int step,now;
	bool operator<(const State &s)const
	{
		if(seq.size()!=s.seq.size())return seq.size()<s.seq.size();
		for(int i=0;i<seq.size();i++)if(seq[i]!=s.seq[i])return seq[i]<s.seq[i];
		for(int i=0;i<7;i++)
		{
			if(p[i].size()!=s.p[i].size())return p[i].size()<s.p[i].size();
			for(int j=0;j<p[i].size();j++)if(p[i][j]!=s.p[i][j])return p[i][j]<s.p[i][j];
		}
		return false;
	}
	void clear(){for(int i=0;i<7;i++)p[i].clear();seq.clear();step=7,now=0;}
	bool Match(const int v){return v==10||v==20||v==30;}
	int Process()
	{
		if(seq.empty())return -1;
		int cnt=7;
		while(p[now%7].empty()&&cnt--)now=(now+1)%7;
		if(cnt<0)return 1;
		Deq &deq=p[now%7];
		deq.push_back(seq.pop_front());
		step++,now++;
		bool changed=true;
		while(changed&&deq.size()>=3)
		{
			if(Match(deq.front(0)+deq.front(1)+deq.back(0)))seq.push_back(deq.front(0),deq.front(1),deq.back(0)),deq.pop(2,1);
			else if(Match(deq.front(0)+deq.back(1)+deq.back(0)))seq.push_back(deq.front(0),deq.back(1),deq.back(0)),deq.pop(1,2);
			else if(Match(deq.back(2)+deq.back(1)+deq.back(0)))seq.push_back(deq.back(2),deq.back(1),deq.back(0)),deq.pop(0,3);
			else changed=false;
		}
		return 0;
	}
//	void Print()
//	{
//		printf("step %d\n",step);
//		for(int i=0;i<7;i++)
//		{
//			printf("%d:",i);
//			for(int j=0;j<p[i].size();j++)printf(" %d",p[i][j]);puts("");
//		}
//		for(int i=0;i<seq.size();i++)printf("%d ",seq[i]);puts("");
//		puts("");
//	}
}A;
bool Input()
{
	int v;
	scanf("%d",&v);
	if(v==0)return false;
	A.clear();
	A.p[0].push_back(v);
	for(int i=1;i<7;i++)scanf("%d",&v),A.p[i].push_back(v);
	for(int i=7;i<52;i++)scanf("%d",&v),A.seq.push_back(v);
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	while(Input())
	{
		set<State>s;
		for(;;)
		{
//			A.Print();
			s.insert(A);
			int result=A.Process();
			if(result==-1){printf("Loss: ");break;}
			else if(result==1){printf("Win : ");break;}
			else if(s.find(A)!=s.end()){printf("Draw: ");break;}
		}
		printf("%d\n",A.step);
	}
	return 0;
}
