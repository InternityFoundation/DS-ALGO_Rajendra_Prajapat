#include <iostream>
#include <sstream>
#include<fstream>
#include<limits.h>
#include "Graph.h"
using namespace std;



void Menu(){
	cout<<"\n\t\t\t\t     __________________________________________________________\n";
	cout<<"\n\t\t\t\t\t F L I G H T    M A N A G E M E N T    S Y S T E M\n";
	cout<<"\t\t\t\t     __________________________________________________________\n\n";
	cout<<"\n\n\t\t1. Find shortest Time path between two Airports\t\t\t\t10. Print current connectivity Graph \n\n\t\t2. Find Shortest Cost path between two Airports";
	cout<<"\t\t\t\t11. Show node number-name mapping\n\n\t\t3. Display the Shortest Times between each Airport Stations\t\t12. Name Nodes\n\n\t\t4. Display the Shortest Costs between each Airport Stations";
	cout<<"\t\t13. Load from file\n\n\t\t5. Add a new route from Airport A to Airport B\t\t\t\t14. Save To a File\n\n\t\t6. Add a new Airport station\t\t\t\t\t\t.";
	cout<<"\n\n\t\t7. Update an route's cost/time from Airport A to Airport B\t\t.";
	cout<<"\n\n\t\t8. Delete an route from Airport A to Airport B\t\t\t\t.\n\n\t\t9. Crash an Airport station\t\t\t\t\t\t15. Exit";
	//cout<<"\n\n\t\t10. Print current connectivity Graph\n\n\t\t11. Show node number-name mapping\n\n\t\t12. Name Nodes\n\n\t\t13. Load from file";
	cout<<"\n\n\n\n\t\t\t\t\tSelect Option\t==>\t";
}

int main()
{
	int option;
	Graph g;
	g.seed();
	do{
		system("MODE CON COLS=150 LINES=40");
		system("cls");
		Menu();
		cin>>option;
		if(option!=15)
			system("MODE CON COLS=90 LINES=40");
		switch(option){			
			case 1:{
				system("cls");
				cout<<"\n\t\t Shortest Time Path between Two Airports";
				cout<<"\n\n\tEnter Source Airport and Destination Airport\n\t";
				int src,dest;
				cin>>src>>dest;
				g.shortest_path(src,dest,1);
				cout<<"\n\tPress Enter to continue...";
				fflush(stdin);
				getchar();	
				break;
			}
			case 2:{
				system("cls");
				cout<<"\n\t\t Shortest Cost Path between Two Airports";
				cout<<"\n\n\tEnter Source Airport and Destination Airport\n\t=>\t";
				int src,dest;
				cin>>src>>dest;
				g.shortest_path(src,dest,0);
				cout<<"\n\tPress Enter to continue...";
				fflush(stdin);
				getchar();	
				break;								
			}
			case 3:{
				system("cls");
				cout<<"\n\t\t Shortest Time Path between all Airports\n\n";
				g.all_shortest_time_paths();
				cout<<"\n\tPress Enter to continue...";
				fflush(stdin);
				getchar();	
				break;				
			}
			case 4:{
				system("cls");
				cout<<"\n\t\t Shortest Cost Path between all Airports\n\n";
				g.all_shortest_time_paths(0);
				cout<<"\n\tPress Enter to continue...";
				fflush(stdin);
				getchar();					
				break;
			}
			case 5:{
				system("cls");
				cout<<"\n\t\t Add a new route between two Airport Stations\n\n";
				cout<<"\n\t\tEnter the the source Airport station and destination Airport station between which new route is to be added\n\t=>";
				int src,dest;
				cin>>src>>dest;
				cout<<"\n\t\tAdd the cost and time required for flying through the new route\n\t=>\t";
				int time,cost;
				cin>>cost>>time;				
				g.addEdge(src,dest,cost,time);
				cout<<"\n\tNew Route has been added successfully !";
				cout<<"\n\tPress Enter to continue...";
				fflush(stdin);
				getchar();					
				break;
			}
			case 6:{
				system("cls");
				cout<<"\n\t\t Add a new Airport Station\n\n";				
				g.addNode();
				cout<<"\n\tNew Airport station has been added successfully ! The new station has been numbered - Airport station #"<<g.graph.size()-1;
				cout<<"\n\tPress Enter to continue...";
				fflush(stdin);
				getchar();					
				break;
			}
			case 7:{
				system("cls");
				cout<<"\n\t\t Update an new route between two Airport Stations\n\n";
				cout<<"\n\t\tEnter the the source Airport station and destination Airport station between which route is to be updated\n\t=>\t";
				int src,dest;
				cin>>src>>dest;
				cout<<"\n\t\tSpecify the updated cost and time required for flying through this route\n\t=>\t";
				int time,cost;
				cin>>cost>>time;				
				g.addEdge(src,dest,cost,time);
				cout<<"\n\tThe Route has been updated successfully !";
				cout<<"\n\tPress Enter to continue...";
				fflush(stdin);
				getchar();					
				break;
			}
			case 8:{
				system("cls");
				cout<<"\n\t\t Delete a route between two Airport Stations\n\n";
				cout<<"\n\t\tEnter the source Airport station and destination Airport station between which the route is to be deleted\n\t=>\t";
				int src,dest;
				cin>>src>>dest;				
				g.deleteEdge(src,dest);
				cout<<"\n\tSpecified Route has been deleted successfully !";
				cout<<"\n\tPress Enter to continue...";
				fflush(stdin);
				getchar();						
				break;
			}
			case 9:{
				system("cls");
				cout<<"\n\t\t Delete an Airport Station\n\n";
				cout<<"\n\t\tEnter the Airport station which is to be deleted\n\t=>\t";
				int Airport_num;
				cin>>Airport_num;				
				g.deleteNode(Airport_num);
				cout<<"\n\tSpecified Airport station has been deleted successfully !";
				cout<<"\n\tPress Enter to continue...";
				fflush(stdin);
				getchar();				
				break;
			}
			case 10:{
				system("MODE CON COLS=120 LINES=45");
				system("cls");				
				cout<<"\n\t\t Airport Connectivity Graph\n\n";				
				cout<<"\n  Cost-Edge Graph- \n";
				g.printGraph(0);
				cout<<"\n\n\n Time-Edge Graph - \n";
				g.printGraph();							
				cout<<"\n\n\tPress Enter to continue...";
				fflush(stdin);
				getchar();					
				break;
			}
			case 11:{
				system("cls");
				cout<<"\n\t\t\tAirports Number-Name Mappings\n\t\t    ______________________________________\n\n\n";				
				g.node_name_mapping();
				cout<<"\n\tPress Enter to continue...";
				fflush(stdin);
				getchar();					
				break;
			}		
			case 12:{
				system("cls");
				cout<<"\n\t\t\t Airports Numbers Naming\n\t\t    ___________________________________\n\n\n";				
				cout<<"\tEnter the Airport number which is to be named\n\n\t=>\t";
				int node_num;
				cin>>node_num;
				cout<<"\n\tEnter a name for the Airport node\n\n\t=>\t";
				string name;
				cin>>name;
				g.name_nodes(name,node_num);
				cout<<"\n\tPress Enter to continue...";
				fflush(stdin);
				getchar();
				break;
			}		
			case 13:{
				system("cls");
				cout<<"\n\t\t\tAirport Data Loading from File\n\t\t    ______________________________________\n\n\n";	
				cout<<"\tEnter the file name which you want to load the data\n\n\t=>\t";
				string file_name,sz;
				cin>>file_name;
				ifstream fin(file_name.c_str());
				getline(fin,sz);
				stringstream ss(sz);				
				int n,numbers;
				ss>>n;
				Graph load_graph(n);
				for(int i=0;i<n;i++){
					for(int j=0;j<n;j++){
						fin>>numbers;
						load_graph.graph[i][j].time = numbers;
						//cout<<numbers<<" ";//<<i<<","<<j<<" ), ";
					}
					//cout<<endl;
				}
				getline(fin,sz);
				cout<<"\n\n";
				for(int i=0;i<n;i++){
					for(int j=0;j<n;j++){
						fin>>numbers;
						load_graph.graph[i][j].cost = numbers;
						//cout<<numbers<<" ";
					}
					//cout<<endl;
				}
				
				g=load_graph;
				cout<<"\n\tPress Enter to continue...";
				fflush(stdin);
				getchar();				
				break;
			}	
			case 14:{
				system("cls");
				cout<<"\n\t\t\tSaving Airport Data to a File\n\t\t    _____________________________________\n\n\n";	
				cout<<"\tEnter the file name where you want to save the data\n\n\t=>\t";				
				string file_name;
				cin>>file_name;
				int n = g.graph.size();
				ofstream fout(file_name.c_str());
				fout<<n<<"\n";
				for(int i=0;i<n;i++){
					for(int j=0;j<n;j++){
						fout<<g.graph[i][j].time<<" ";
					}
					fout<<"\n";
				}
				fout<<"\n";
				for(int i=0;i<n;i++){
					for(int j=0;j<n;j++){
						fout<<g.graph[i][j].cost<<" ";
					}
					fout<<"\n";
				}
				fout.close();	
				cout<<"\n\tFile has been saved to "<<file_name<<" successfully !\n";
				cout<<"\n\tPress Enter to continue...";
				fflush(stdin);
				getchar();								
				break;
			}			
			case 15:{
				int n = g.graph.size();
				ofstream fout("graph.txt");
				fout<<n<<"\n";
				for(int i=0;i<n;i++){
					for(int j=0;j<n;j++){
						fout<<g.graph[i][j].time<<" ";
					}
					fout<<"\n";
				}
				fout<<"\n";
				for(int i=0;i<n;i++){
					for(int j=0;j<n;j++){
						fout<<g.graph[i][j].cost<<" ";
					}
					fout<<"\n";
				}
				fout.close();
				cout<<"\n\t\t\t...Goodbye :)";				
				break;
			}
		}
		
	}while(option!=15);

}
