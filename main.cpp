#include<bits/stdc++.h>

using namespace std;

// a structure to represent a weighted edge and its capacity in graph 
struct  LINK{ 
	int endpoint1, endpoint2, cost, capacity;
}; 

struct  CONNECTION{
	int id ,src,dest,Bmin,Bavg,Bmax; float Bequiv;
}; 

 struct PATH{
	 int src, dest, cost; vector<int> P;
 };

// subfunction of dijkstra algo 
int minDistance(vector<int>dist,vector<bool>&sptSet,int V) 
{ 
	int min = INT_MAX, min_index; 

	for (int v = 0; v < V; v++) 
		if (sptSet[v] == false &&dist[v] <= min) 
			min = dist[v], min_index = v; 
	return min_index; 
} 
//function for getting path
void getPath(vector<int>&parent, int j, vector<int>&path,int count) 
{ 
	if (parent[j] == - 1|| count>parent.size()) 
		return; 
		count++;
	getPath(parent, parent[j],path,count); 
	path.push_back(j); 
} 

//////////////shortest path algorithm/////////////////////////////
void dijkstra(vector<vector<int>> &graph, int src,int V,vector<int>&parent ,vector<int>&dist ) 
{ 
	
	vector<bool>sptSet(V,false);  

	dist[src] = 0; 
	parent[src] = -1;
	for (int count = 0; count < V - 1; count++) 
	{ 
		int u = minDistance(dist, sptSet,V); 
		sptSet[u] = true; 
		for (int v = 0; v < V; v++) 
			{
				if (!sptSet[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v]) 
				{ 
				parent[v] = u; 
				dist[v] = dist[u] + graph[u][v]; 
				} 
			}
	} 
 
} 
////////////////////create routing table//////////////////////////////
void make_routing_table(vector<int> &path,vector<int> &path2,vector<int> &dist,vector<int> &dist2,int &dest,ofstream &out,string flag)
{

	    out<<dest<<"    ";
		for(auto i : path)
			out<<i<<"->";

		
			out<<" first shortest path";
			if(flag=="dist")out<<" using dist cost=";
			if(flag=="hop")out<<" using hop cost=";
			out<<dist[dest]<<"\n";

		if(dist2[dest]!=10000)
		{
			out<<dest<<"    ";
			for(auto i : path2)
			out<<i<<"->";
			 out<<" second shortest path";
			 	if(flag=="dist")out<<" using dist cost=";
			if(flag=="hop")out<<" using hop cost=";
			 out<<dist2[dest]<<"\n";
			out<<"\n";
		}else
		 out<<"no path found \n\n";
}
/////////////////find path////////////////////////////////////////////////

vector<int> find_path(PATH path[],int &cost,int src,int dest)
{
	for(int i=0;i<5000;i++)
	{
		if( path[i].src==src && path[i].dest==dest ){
			cost=path[i].cost;
		return path[i].P;
		}
	}
	return {};
}

vector<int> find_link_capacity(LINK link[],int E,int src,int dest)
{
	for(int i=0;i<E;i++)
	{
		if( link[i].endpoint1==src&&link[i].endpoint2==dest  || link[i].endpoint2==src&&link[i].endpoint1==dest)
		return {i,link[i].capacity};
	}
	return {};
}
////////////////Optimistic Approach to create link connection////////////////
int Optimistic_Approach(LINK link[],int E,float Beq, vector<int> path)
{
	int i,flag=0;
		for( i=0;i<path.size()-1;i++)
		{
			int a=path[i],b=path[i+1];
			vector<int> link_info=find_link_capacity(link,E,a,b);

			if (Beq >link_info[1]) { flag=1; break;}

			link[link_info[0]].capacity-= Beq;
		}
		if(flag){
				for(int j=i-1;j>=0;j--)
				{
					int a=path[i],b=path[i+1];
					vector<int> link_info=find_link_capacity(link,E,a,b);
					link[link_info[0]].capacity+= Beq;
				}
		}
if(flag) return 0;
return 1;
}
////////////////Pessimistic Approach to create link connection////////////////
int Pessimistic_Approach(LINK link[],int E,int &Bmaxi, vector<int>&path)
{
		int i,flag=0;
		for( i=0;i<path.size()-1;i++)
		{
			int a=path[i],b=path[i+1];
			vector<int> link_info=find_link_capacity(link,E,a,b);

			if (Bmaxi >link_info[1]) { flag=1; break;}

			link[link_info[0]].capacity-= Bmaxi;
		}
		if(flag){
				for(int j=i-1;j>=0;j--)
				{
					int a=path[i],b=path[i+1];
					vector<int> link_info=find_link_capacity(link,E,a,b);
					link[link_info[0]].capacity+= Bmaxi;
				}
		}
if(flag) return 0;  // flag value becomes 1 when connecton of link 
return 1;
}

int frwd_table[50][20][4];
int label_id=1000;
int ft[14]={0};
void make_forwd_table(vector<int>&path,vector<int>&label_list)
{
	//cout<<k<<" ";
	for(int i=0;i<path.size();i++)
	{
		if(i==0){
			 frwd_table[path[i]][ft[path[i]]][0]=-1; frwd_table[path[i]][ft[path[i]]][1]=-1;
			  frwd_table[path[i]][ft[path[i]]][2]=path[i+1]; frwd_table[path[i]][ft[path[i]]][3]=label_id++;
		}
		else if(i==path.size()-1){
			frwd_table[path[i]][ft[path[i]]][0]=path[i-1]; frwd_table[path[i]][ft[path[i]]][1]=label_id-1;
			 frwd_table[path[i]][ft[path[i]]][2]=-1; frwd_table[path[i]][ft[path[i]]++][3]=-1;
		}
		else{
			frwd_table[path[i]][ft[path[i]]][0]=path[i-1]; frwd_table[path[i]][ft[path[i]]][1]=label_id-1 ;
			 frwd_table[path[i]][ft[path[i]]][2]=path[i+1]; frwd_table[ path[i]] [ft[path[i]]][3]=label_id++;
		}

	ft[path[i]]++;
	label_list.push_back(label_id);
	}
}



////////////////////////////////////main function//////////////////////////////////////////

int main(int argc, char ** argv) 
{
	// ./-routing0 -top1 topologyfile2 -conn3 connectionsfile4 -rt5 routingtablefile6 -ft7 forwardingtablefile8 -path9 pathsfile10 -flag11 hopjdist12 -p13 0|1_14
string topology_file=argv[2]; cout<<"IN_file :topology_file -> "<<topology_file<<"\n";
string connection_file=argv[4]; cout<<"IN_file :connection_file -> "<<connection_file<<"\n";
string routingfile=argv[6];   cout<<"OUT_file :routingfile -> "<<routingfile<<"\n";
string forwarding_file=argv[8]; cout<<"OUT_file :forwarding_file -> "<<forwarding_file<<"\n";
string path_file=argv[10];   cout<<"OUT_file :forwarding_file -> "<<forwarding_file<<"\n";
string flag=argv[12];		 cout<<"flag -> "<<flag<<"\n"; if(flag=="dist" || flag == "hop"){}else {cout<<"please give flag argument dist or hop"; return 0;} 
int p=atoi(argv[14]);  cout<<"p-> "<<p<<"\n"; if(p==0 || p==1){}else {cout<<"please give p argument 1 or 0"; return 0;} 


ifstream in;
in.open(topology_file);
if(!in) {cout<<"topology file not oopen"; return 0;}
int E,V;
in>>V>>E;

 struct LINK  link[E];

 struct PATH first_path[5000];
 struct PATH second_path[5000];
 

    for(int i=0;i<E;i++)
        in>>link[i].endpoint1>>link[i].endpoint2>>link[i].cost>>link[i].capacity;
in.close();
//create graph of vector representation
vector<vector<int>> GRAPH(V,vector<int>(V,0));
if(flag=="dist")
{

for(int i=0;i<E;i++){
    GRAPH[ link[i].endpoint1] [link[i].endpoint2]  =  link[i].cost ;
    GRAPH[ link[i].endpoint2] [link[i].endpoint1]  =  link[i].cost ;
	}
}
if(flag=="hop")
{

for(int i=0;i<E;i++){
    GRAPH[ link[i].endpoint1] [link[i].endpoint2]  =  1;
    GRAPH[ link[i].endpoint2] [link[i].endpoint1]  =  1 ;
	}
}


ofstream out;
out.open(routingfile);
if(!out) {cout<<"routingfile not open "; return 0;}
int k=0;  // for path
for(int hop=0;hop<V;hop++)
{
//////////////////////////////////////////////////////first shortest path //////////////////////////////////////////////////////
int src=hop;
vector<int> parent(V);

vector<int>dist(V,INT_MAX);

dijkstra(GRAPH,src,V,parent,dist);
//////////////////////////////////////////////////////second shortest path //////////////////////////////////////////////////////
		for(int i=0;i<V;i++)
		{
			int dest=i;
			if(src==dest) continue;

			vector<int> path;
			path.push_back(src);
			getPath(parent,dest,path,0);

			first_path[k].src=src; first_path[k].dest=dest;first_path[k].cost=dist[dest]; first_path[k].P=path;
		
    		vector<vector<int>> GRAPH2=GRAPH;

    				for(int i=0;i<path.size()-1;i++)
        			{
         			GRAPH2[path[i]][path[i+1]]=0;
         			GRAPH2[path[i+1]][path[i]]=0;
         			}
    		 vector<int> parent2(V); 
   			 vector<int>dist2(V,10000);
    		 dijkstra(GRAPH2,src,V,parent2, dist2);
  
    		 vector<int> path2;
    		 path2.push_back(src);		
    		getPath(parent2,dest,path2,0);
			second_path[k].src=src; second_path[k].dest=dest;second_path[k].cost=dist2[dest]; second_path[k].P=path2;
			make_routing_table(path,path2,dist,dist2,dest,out,flag);
			k++;


		}
		
}
		
in.open(connection_file);
if(!in){ cout<<"connection_file not open"; return 0;}
int total_conn;
in>>total_conn;


 struct CONNECTION connection[total_conn];

    for(int i=0;i<total_conn;i++)
	{
		connection[i].id=i;
        in>>connection[i].src>>connection[i].dest>>connection[i].Bmin>>connection[i].Bavg>>connection[i].Bmax;
		 connection[i].Bequiv = min((1.0 * connection[i].Bmax ),( connection[i].Bavg + 0.25 * (connection[i].Bmax - connection[i].Bmin)));//calculating Bequiv
	}
in.close();

ofstream o;
o.open(path_file);
if(!o) {cout<<"path file not open"; return 0;}
int total_stablished_conn=0;
o<<"Connection Id | Source | Destination |           path        |         Label List      |  Path Cost using : ";
if(flag=="dist") o<<"dist\n"; if(flag=="hop") o<<"hop\n";
for(int i=0;i<total_conn;i++)
{
	
		if(p==0)
		{
			int x,y;
			int id=connection[i].id , src=connection[i].src , dest=connection[i].dest; float Beq=connection[i].Bequiv;
			int cost=0;
			vector<int>foundpath= find_path(first_path,cost,src,dest); 
			x= Optimistic_Approach(link,E,Beq,foundpath);
			
			if(x==1){  // if x==1 then connection build successfully then make file with conn. id
					
					vector<int>label_list;
					make_forwd_table(foundpath,label_list);
					o<<id<<"                "<<src<<"       "<<dest<<"             ";
					for(int i=0;i<foundpath.size()-1;i++) o<<foundpath[i]<<"->";
					o<<foundpath[foundpath.size()-1]<<"       [";

					for(int i=0;i<label_list.size()-1;i++)
						o<<label_list[i]<<", "; o<<"]  "<<cost<<" \n";

					total_stablished_conn++;
					}
	
			if(x==0){
			vector<int>foundpath= find_path(second_path,cost,src,dest);  // if connection fails in first shortest path then try for second shorest path
	     	y= Optimistic_Approach(link,E,Beq,foundpath);
			 if(y==1){  // if x==1 then connection build successfully then make file with conn. id
			 		vector<int>label_list;
					make_forwd_table(foundpath,label_list);
					o<<id<<"                "<<src<<"       "<<dest<<"             ";
					for(int i=0;i<foundpath.size()-1;i++) o<<foundpath[i]<<"->";
					o<<foundpath[foundpath.size()-1]<<"       [";

					for(int i=0;i<label_list.size()-1;i++)
						o<<label_list[i]<<", "; o<<"]  "<<cost<<" \n";

					total_stablished_conn++;
					}
					
			}
		}



		if(p==1)
		{
			int x,y;
			int id=connection[i].id ,src=connection[i].src, dest=connection[i].dest, Bmaxi=connection[i].Bmax;
			int cost=0;
			vector<int>foundpath= find_path(first_path,cost,src,dest);
			x= Pessimistic_Approach(link,E,Bmaxi,foundpath);
			if(x==1){  // if x==1 then connection build successfully then make file with conn. id
					vector<int>label_list;
					make_forwd_table(foundpath,label_list);
					o<<id<<"                "<<src<<"       "<<dest<<"             ";
					for(int i=0;i<foundpath.size()-1;i++) o<<foundpath[i]<<"->";
					o<<foundpath[foundpath.size()-1]<<"       [";

					for(int i=0;i<label_list.size()-1;i++)
						o<<label_list[i]<<", "; o<<"]  "<<cost<<" \n";

					total_stablished_conn++;
					}
	
	
			if(x==0){
			vector<int>foundpath= find_path(second_path,cost,src,dest);  // if connection fails in first shortest path then try for second shorest path
	     	y= Pessimistic_Approach(link,E,Bmaxi,foundpath);
			if(y==1){  // if x==1 then connection build successfully then make file with conn. id
					vector<int>label_list;
					make_forwd_table(foundpath,label_list);
					o<<id<<"                "<<src<<"       "<<dest<<"             ";
					for(int i=0;i<foundpath.size()-1;i++) o<<foundpath[i]<<"->";
					o<<foundpath[foundpath.size()-1]<<"       [";

					for(int i=0;i<label_list.size()-1;i++)
						o<<label_list[i]<<", "; o<<"]  "<<cost<<" \n";

					total_stablished_conn++;
					}

			}
			
		}
		
 }
o.close();

o.open(forwarding_file);
////////////////////////////////create forwarding table//////////////////////////////////////////////////////
for(int i=0;i<V;i++)
{
	o<<"forwarding table for router : "<<i<<"\n";
	o<<"Interface_in |Label in  |Interface out |    Label out\n";

	for(int j=0;j<20;j++)
	{
		if(frwd_table[i][j][1]==0) continue;
		for(int k=0;k<4;k++)
		o<<frwd_table[i][j][k]<<"              ";
		o<<"\n";
	}
	o<<"\n\n";
}
cout<<"total_stablished_conn = "<<total_stablished_conn;
    return 0;

}
