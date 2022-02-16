#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;
const int mm=51010;
const int oo=1e9;
const int m=50004;
class node
{
  public:int v,c,to;
}e[23*mm];
int q[mm];
int dis[mm],vis[mm],n,l,r,pre[mm],pos;
void add(int u,int v,int c)
{
  e[pos].v=v;e[pos].c=c;e[pos].to=pre[u];pre[u]=pos++;
}
void spfa()
{memset(vis,0,sizeof(vis));
  for(int i=l;i<=r;i++)
    dis[i]=oo;
  dis[l]=0;
  int s=0,t=1;
  q[s]=l; vis[l]=1;int z;
  while(s!=t)
  {
    z=q[s];s=(s+1)%m;vis[z]=0;
    int v,c;
    for(int p=pre[z];p!=-1;p=e[p].to)
    {
      v=e[p].v;c=e[p].c;
      if(dis[v]>dis[z]+c)
      {
        dis[v]=dis[z]+c;
        if(!vis[v])
        {
          vis[v]=1;q[t]=v;t=(t+1)%m;
        }
      }
    }
  }
}
int main()
{
  while(cin>>n)
  {pos=0;
    memset(pre,-1,sizeof(pre));
    int a,b,c;l=oo;r=-oo;
  memset(e,0,sizeof(e));
    for(int i=0;i<n;i++)
    {
      cin>>a>>b>>c;
      add(a-1,b,-c);
      if(a<l)l=a;if(b>r)r=b;
    }
    --l;
   ///s[b]-s[a]<=c (a-1,b) has at least c
    for(int i=l;i<r;i++)
    {add(i+1,i,1);add(i,i+1,0);
    }
   ///l^=r;r^=l;l^=r;
    spfa();
    cout<<dis[l]-dis[r]<<"\n";
  }
}