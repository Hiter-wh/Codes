#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void percolate_down(vector<int> &binaryheap, vector<double> &price)
{
    int k=binaryheap.size()-1;
    int temp;
    binaryheap[0]=binaryheap[k];
    binaryheap.pop_back();
    if(binaryheap.size()==0)
    {
        return;
    }
    k=0;
    while(binaryheap.size()-1 >= 2*k+1)
    {
        if(2*k+1==binaryheap.size())//只存在左节点
        {
            if(price[binaryheap[k]]>price[binaryheap[2*k+1]])
            {
                temp=binaryheap[2*k+1];
                binaryheap[2*k+1]=binaryheap[k];
                binaryheap[k]=temp;
                k=2*k+1;
            }
        }
        else//左右子节点都存在
        {
            if(price[binaryheap[k]]>price[binaryheap[2*k+1]])
            {
                if(price[binaryheap[k]]>=price[binaryheap[2*k+2]])
                {
                    if(price[binaryheap[2*k+1]]<=price[binaryheap[2*k+2]])
                    {
                        temp=binaryheap[2*k+1];
                        binaryheap[2*k+1]=binaryheap[k];
                        binaryheap[k]=temp;
                        k=2*k+1;
                    }
                    else
                    {
                        temp=binaryheap[2*k+2];
                        binaryheap[2*k+2]=binaryheap[k];
                        binaryheap[k]=temp;
                        k=2*k+2;
                    }
                }
                else
                {
                    temp=binaryheap[2*k+1];
                    binaryheap[2*k+1]=binaryheap[k];
                    binaryheap[k]=temp;
                    k=2*k+1;
                }
            }
            else
            {
                if(price[binaryheap[k]]>price[binaryheap[2*k+2]])
                {
                    temp=binaryheap[2*k+2];
                    binaryheap[2*k+2]=binaryheap[k];
                    binaryheap[k]=temp;
                    k=2*k+2;
                }
                else
                {
                    break;
                }
            }
        }
    }
}

void percolate_up(vector<int> &binaryheap, vector<double> &price,int k)
{
    int temp;
    while (k>0)
    {
        if(price[binaryheap[k]]>price[binaryheap[(k-1)/2]])//不用换了
        {
            break;
        }
        else//要换
        {
            temp=binaryheap[(k-1)/2];
            binaryheap[(k-1)/2]=binaryheap[k];
            binaryheap[k]=temp;
            k=(k-1)/2;
        }
    }
}

void updatedistance(vector<vector <vector <int> > > &AL, vector<int> &binaryheap, vector<double> &price, vector<int> &vistiedset, vector<int> &MST)
{
    vector<int> ::iterator it;//查找在binaryheap中的迭代器
    int u=binaryheap[0];
    MST[u]=1;
    percolate_down(binaryheap,price);
    for(int i=0;i<AL[u].size();i++)
    {
        if(MST[AL[u][i][0]]==-1)//不在最小生成树里
        {
            it=find(binaryheap.begin(),binaryheap.end(),AL[u][i][0]);
            if(it==binaryheap.end())//不在堆里
            {
                binaryheap.push_back(AL[u][i][0]);
                vistiedset[AL[u][i][0]]=1;
                price[AL[u][i][0]]=price[u]/(1-AL[u][i][1]/100.0);
                percolate_up(binaryheap,price,binaryheap.size()-1);
            }
            else//在堆里
            {
                if(price[u]/(1-AL[u][i][1]/100.0)<price[AL[u][i][0]])
                {
                    price[AL[u][i][0]]=price[u]/(1-AL[u][i][1]/100.0);
                    int kk=distance(it,binaryheap.begin());
                    percolate_up(binaryheap,price,distance(it,binaryheap.begin()));
                }
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    // freopen("input.txt", "r", stdin);
    int n,m,a,b,c,s,e,u;
    vector <int> v(2);
    cin>>n>>m;//INput
    vector<vector <vector <int> > > AL(n);//3D Adjacent table
    for(int i=0;i<m;i++)
    {//Input edges
        cin>>a>>b>>c;
        v[0]=b-1;
        v[1]=c;
        AL[a-1].push_back(v);
        v[0]=a-1;
        AL[b-1].push_back(v);
    }
    cin>>s>>e;
    s=s-1;
    e=e-1;
    vector<double> price(n,3);
    price[e]=1;
    vector<int> vistiedset(n,-1);//set of ids that have been visited
    vector<int> MST(n,-1);//set of nodes that have been placed int MST
    vector<int> binaryheap;//Binary heap
    binaryheap.push_back(e);
    vistiedset[e]=1;
    while(MST[s]==-1)
    {
        updatedistance(AL,binaryheap,price,vistiedset,MST);
    }
    printf("%.8f\n",price[s]*100);
    return 0;
}