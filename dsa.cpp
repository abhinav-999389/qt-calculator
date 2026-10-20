#include<iostream>
#include<vector>
#include<queue>
#include<limits>
using namespace std;
struct edge{
    int targetnode;
    double distance;
    double riskfactor;
    double fuelcost;
    double geteffectivecost()const{
        return distance*(1.0+riskfactor)+fuelcost;
    }
};
struct pqelement{
    int node;
    double totalcost;
    bool operator>(const pqelement& other) const{
        return totalcost>other.totalcost;
    }

};

class graph{
    private:
    int numnodes;
    vector<vector<edge>>adjlist;
    public:
    graph(int n){
        numnodes=n;
        adjlist.resize(n);

    }
    void addpathway(int source,int target,double dis,double risk,double fuel){
        edge forwardedge={target,dis,risk,fuel};
        adjlist[source].push_back(forwardedge);
        edge backwardedge={source,dis,risk,fuel};
        adjlist[source].push_back(backwardedge);
    }

    const vector<vector<edge>>& getadjlist()const{
        return adjlist;
    }
    int getNumnodes()const{
        return numnodes;
    }
};

void runDijkstra(const graph& g,int starNode){
    int n=g.getNumnodes();
    vector<double>mincost(n,numeric_limits<double>::infinity());
    vector<int>parent(n,-1);

    priority_queue<pqelement,vector<pqelement>,greater<pqelement>>pq;
    mincost[starNode]=0.0;
    pq.push({starNode,0.0});
    while(!pq.empty()){
        pqelement current=pq.top();
        pq.pop();
        int u=current.node;
        double currentcost=current.totalcost;

        if(currentcost>mincost[u]){
            continue;
        }
        for(const edge& neighbor : g.getadjlist()[u]){
            int v=neighbor.targetnode;
            double newcost=currentcost+neighbor.geteffectivecost();
            if(newcost<mincost[v]){
                mincost[v]=newcost;
                parent[v]=u;
                pq.push({v,newcost});
            }
        }
    }
    int targetsector=4;
    if(mincost[targetsector]==numeric_limits<double>::infinity()){
        cout<<"target is unreachable.\n";

    }else{
        cout<<"total cost to target:"<<mincost[targetsector]<<"\n";
        vector<int>path;
        for(int curr=targetsector;curr!=-1;curr=parent[curr]){
            path.push_back(curr);

        }
        cout<<"recommend safe path :";
        for(int i=path.size()-1;i>=0;--i){
            cout<<path[i]<<(i==0?"":"->");
        }
        cout<<"\n";
    }
}

int main(){
    graph g(5);
    g.addpathway(0,1,10.0,0.1,2.0);
    g.addpathway(0,2,5.0,1.5,1.0);
    g.addpathway(1,3,8.0,0.2,1.5);
    g.addpathway(2,3,2.0,1.0,0.5);
    g.addpathway(3,4,7.0,0.0,1.0);
    runDijkstra(g,0);
    return 0;


}
