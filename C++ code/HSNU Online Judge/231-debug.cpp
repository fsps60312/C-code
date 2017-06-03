#include<stdio.h>
#include<string.h>
#include<vector>
#include<algorithm>
using namespace std;
#define N 20005
int p[N];
int _find(int k){
    if(p[k]==k) return k;
    return p[k]=_find(p[k]);
}
struct P{
    int x,y;
}in;
vector<P> A,B,C,D,E;
int main(){
	freopen("in.txt","r",stdin);
	freopen("new.txt","w",stdout);
    int n,m,k,t,x,y,i,j,add,now=0;
    while(scanf("%d%d%d",&n,&m,&k)==3)
    {
    	A.clear(),B.clear(),C.clear(),D.clear(),E.clear();
    	now=0;
	    for(i=0;i<m;i++){
	        scanf("%d%d%d",&in.x,&in.y,&x);
	        if(x) A.push_back(in);
	        else B.push_back(in);
	    }
	    add=n-1;
	    for(i=1;i<=n;i++)
	        p[i]=i;
	    for(i=0;i<A.size();i++){
	        x=_find(A[i].x);
	        y=_find(A[i].y);
	        if(p[x]!=p[y]){
	            p[x]=y;
	            add--;
	        }
	    }
	    for(i=0;i<B.size();i++){
	        x=_find(B[i].x);
	        y=_find(B[i].y);
	        if(p[x]!=p[y]){
	            p[x]=y;
	            add--;
	            C.push_back(B[i]);
	        }
	        else D.push_back(B[i]);
	    }
	    if(add){
	        puts("no solution");
	        continue;
	    }
	    add=n-1;
	    for(i=1;i<=n;i++)
	        p[i]=i;
	    for(i=0;i<C.size();i++){
	        x=_find(C[i].x);
	        y=_find(C[i].y);
	        if(p[x]!=p[y]){
	            p[x]=y;
	            add--;
	        }
	    }
	    now=C.size();
	    for(i=0;i<D.size() && now<k;i++){
	        x=_find(D[i].x);
	        y=_find(D[i].y);
	        if(p[x]!=p[y]){
	            p[x]=y;
	            add--;
	            now++;
	            C.push_back(D[i]);
	        }
	    }
	    for(i=0;i<A.size();i++){
	        x=_find(A[i].x);
	        y=_find(A[i].y);
	        if(p[x]!=p[y]){
	            p[x]=y;
	            add--;
	            E.push_back(A[i]);
	        }
	    }
	    //printf("%d\n",now);
	    if(add || now<k) puts("no solution");
	    else{
	    	printf("%d\n",C.size()+E.size());
//	        for(i=0;i<C.size();i++)
//	            printf("%d %d 0\n",C[i].x,C[i].y);
//	        for(i=0;i<E.size();i++)
//	            printf("%d %d 1\n",E[i].x,E[i].y);
	        //puts("yes");
	    }
	}
}
