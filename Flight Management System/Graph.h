#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<algorithm>
using namespace std;
// Edge will store two weights - time and cost
typedef struct Edge{
	int time,cost;
	Edge(int time,int cost):time(time),cost(cost){}	
}Edge;

// Graph is represented using adjacency matrix 
class Graph{
	public:
	vector<vector<Edge> > graph;
	// default initialization to 10 nodes - all disconnected (0 won't be considered, nodes are numbered 1 to graph.size()-1)
	vector<string> names;
	Graph():graph(11,vector<Edge>(11,Edge(INT_MAX,INT_MAX))),names(11,"un-named"){}
	Graph(int n):graph(n,vector<Edge>(n,Edge(INT_MAX,INT_MAX))),names(n,"un-named"){}
	
	void name_nodes(string name,int node_num){
		if(node_num<=0||node_num>=names.size()){
			cout<<"\n\tThe given Airport station number doesn't exist ! Please check and enter a valid Airport station number";
			return;
		}
		names[node_num] = name;
		cout<<"\n\tName assigned to the give Airport successfully !\n";
	}
	
	void node_name_mapping(){
		cout<<"\n\t# Node\t\tNames\n\n\t   ";
		for(int i = 1;i<names.size();i++){
			cout<<i<<"\t:\t"<<names[i]<<"\n\n\t   ";
		}
	}
	// adds edge between two nodes with specified time and cost as the weight, defaulted to 5
	void addEdge(int src,int dest,int edgecost=5,int edgetime=5){
		if(src==dest)return;
		Edge e(edgetime,edgecost);
		graph[src][dest] = e;
	}
	
	// will initialise the graph with few default connections for nodes
	void seed(){
		/*// Test seed - 1
		this->addEdge(2,3,5);
		this->addEdge(2,9,6);
		this->addEdge(2,3,5);
		this->addEdge(1,4,10);
		this->addEdge(1,2,13);
		this->addEdge(4,5,4);
		this->addEdge(4,6,16);
		this->addEdge(3,11,16);
		this->addEdge(4,5,4);
		this->addEdge(12,11,3);
		this->addEdge(12,10,16);
		this->addEdge(9,10,22);
		this->addEdge(9,8,9);
		this->addEdge(3,7,6);
		this->addEdge(7,8,2);
		this->addEdge(8,12,10);
		*/
		// Test seed - 2
		this->addEdge(1,2,2);
		this->addEdge(2,3,7);
		this->addEdge(1,4,5);
		this->addEdge(1,8,15);
		this->addEdge(1,5,9);
		this->addEdge(4,5,4);
		this->addEdge(2,5,11);
		this->addEdge(3,5,17);
		this->addEdge(2,3,7);
		this->addEdge(5,2,11);
		this->addEdge(5,7,8);
		this->addEdge(7,8,6);
		this->addEdge(8,7,6);
		this->addEdge(8,9,10);
		this->addEdge(2,3,7);
		this->addEdge(3,2,16);
		this->addEdge(2,3,7);
		this->addEdge(8,3,22);
		this->addEdge(3,8,22);
		this->addEdge(5,6,12);
		this->addEdge(6,7,8);
		this->addEdge(7,6,8);
		this->addEdge(9,10,9);
		this->addEdge(8,10,8);
		this->addEdge(10,8,8);
	}
	
	// deletes the edge between source and destination nodes
	void deleteEdge(int src,int dest){
		if(src<=0||dest<=0||src>=graph.size()||dest>=graph.size()){
			cout<<"\n\t The specified route doesn't exist ! Please check and enter a valid source and destination Airports";
			return;
		}
		graph[src][dest].time = INT_MAX;
		graph[src][dest].cost= INT_MAX;
	}
	
	// adds a new row and a new column to adjacency matrix, thereby adding a new node
	void addNode(){
		for(int i=0;i<graph.size();i++){
			Edge new_edge(INT_MAX,INT_MAX);
			graph[i].push_back(new_edge);			
		}
		vector<Edge>new_node(graph.size()+1,Edge(INT_MAX,INT_MAX));
		graph.push_back(new_node);
	}
	
	// clears all the incoming and outgoing edges from the node to be deleted, thereby deleting the node
	void deleteNode(int node_num){
		if(node_num<=0||node_num>=graph.size()){
			cout<<"\n\tThe given Airport station doesn't exist ! Please check and enter a valid Airport station number";
			return;
		}
		for(int i=0;i<graph.size();i++){
			graph[i][node_num] = Edge(INT_MAX,INT_MAX);
		}	
		for(int i=0;i<graph[node_num].size();i++){
			graph[node_num][i] = Edge(INT_MAX,INT_MAX);
		}
	}
	
	
	void printGraph(int param=1){
		cout<<"   _____________________________________________________________________________________________________";
		cout<<"\n  |\t\t|\t\t\t\t\t\t\t\t\t\t\t|";
		cout<<"\n  | Node_num\t|\t";
		for(int i=1;i<graph.size();i++)cout<<i<<"\t";
		cout<<"|\n  |_____________|_______________________________________________________________________________________|";
		cout<<"\n  |\t\t|\t\t\t\t\t\t\t\t\t\t\t|\n";		
		for(int i=1;i<graph.size();i++){
			cout<<"  |\t"<<i<<"\t|\t";
			for(int j=1;j<graph[i].size();j++){
				if((param?graph[i][j].time:graph[i][j].cost)==INT_MAX){
					cout<<"NA\t";
				}
				else{
					cout<<(param?graph[i][j].time:graph[i][j].cost)<<"\t";				
				}
			}
			cout<<"|\n";
		}
		cout<<"  |_____________|_______________________________________________________________________________________|";
	}
	
	bool check_path(int src,int dest){
		if(src==dest)
			return true;
		int n = graph.size();
		if(src>=n||dest>=n)
			return false;
		vector<bool>visited(n,false);
		queue<int>q;
		q.push(src);
		visited[src] = true;
		while(!q.empty()){
			int node = q.front();
			q.pop();
			for(int i=1;i<n;i++){
				if(graph[node][i].time == INT_MAX)continue;
				if(i == dest)
					return true;
				if(!visited[i]){
					visited[i]=true;
					q.push(i);
				}									
			}
		}
		return false;
	}
	
	// Weights of an edge from node i to j -
	//     time - graph[i][j].time
	//     cost - graph[i][j].cost
	void shortest_path(int src,int dest,int parm = 1){   //parm = 1 for minimum time , parm = 0 for minimum cost
		// dijkstra's with time as weight
		// takes source and target nodes and return min time/cost needed to go from source to dest		
		
		if(!check_path(src,dest)){
			cout<<"The path doesn't exist between the given nodes :'(";
			return;
		}
		const int INF = INT_MAX;
		vector<int> distance, p; //to store optimal distance and  path 

		int n = graph.size();
		distance.assign(n, INF);
		p.assign(n, -1);
		vector<bool> visisted(n, false);

		distance[src] = 0;
		for (int i = 0; i < n; i++) 
		{
	
			int v = -1;
			for (int j = 0; j < n; j++) 
			{
				if (!visisted[j] && (v == -1 || distance[j] < distance[v]))
					v = j;
			}

			if (distance[v] == INF)
				break;

			visisted[v] = true;
			for (int e = 0;e < n;e++) 
			{
				if(graph[v][e].time != INF and graph[v][e].cost != INF)
				{
					int to = e;
					int len = parm?graph[v][e].time:graph[v][e].cost;

					if (distance[v] + len < distance[to]) {
						distance[to] = distance[v] + len;
						p[to] = v;
					}
				}
			}

			//get the path
			if(dest == v)
			{
				vector<int> path;
				for (int j = dest; j != src; j = p[j])
					path.push_back(j);
				path.push_back(src);
				reverse(path.begin(), path.end());
				cout<<"\n\tMinimum "<<(parm?"Time":"Cost")<<" = : "<<distance[dest]<<endl;
				cout<<"\n\tOptimal Path to acheive Minimum "<<(parm?"Time":"Cost")<<" is : \n\t";
				for(int j=0;j<path.size()-1;j++)
				{
					cout<<path[j]<<" -> ";
				}	
				cout<<dest<<endl;
				int other_cost=0;
				for(int j=0;j<path.size()-1;j++){
					other_cost+=(parm?graph[path[j]][path[j+1]].cost:graph[path[j]][path[j+1]].time);
				}
				cout<<"\n\tThe corresponding "<<(parm?"Cost":"Time")<<" associated with this route is "<<other_cost<<endl;				
				return; 
			}
		}
	}
		
	void all_shortest_time_paths(int param = 1){
		// Floyd-warshall algorithm with time as weight
		// - print a 2-d matrix where matrix[i][j] denotes least time path from node i to j
		int n = graph.size();
		vector<vector<int> >res(n,vector<int>(n,0));		
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(i==j)	
					res[i][j] = 0;
				else
					res[i][j] = param?graph[i][j].time:graph[i][j].cost;
			}
		}	
		for(int k=0;k<n;k++){
			for(int i=0;i<n;i++){
				for(int j=0;j<n;j++){
					if(res[i][k]!=INT_MAX&&res[k][j]!=INT_MAX&&res[i][k]+res[k][j]<res[i][j])
						res[i][j] = res[i][k]+res[k][j];
				}
			}
		}
		cout<<"  \t";
		for(int i=1;i<res.size();i++)cout<<i<<"\t";
		cout<<endl;
		for(int i=1;i<res.size();i++){
			cout<<i<<" :\t";
			for(int j=1;j<res[i].size();j++){
				if(res[i][j]==INT_MAX)
					cout<<"NA\t";
				else
					cout<<res[i][j]<<"\t";				
			}
			cout<<endl<<endl;
		}	
		
		
	}

	
};
