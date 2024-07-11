#include <iostream>
#include <vector>
#include<string.h>
#include<stdio.h>
#include<windows.h>
#include<unistd.h>
#define MAX 10000000
using namespace std;

class Node;
class Edge;
vector<Node*> nodes;
vector<Edge*> edges;
int totDistance;
class Node {
   public:
  Node(string id): id(id), previous(NULL), distanceFromStart(MAX),visited(false),pathexist(false) {
    nodes.push_back(this);
  }

   public:
  string id;
  Node* previous;
  int distanceFromStart;
  bool visited;
  bool pathexist;
};

class Edge {
   public:
  Edge(Node* node1, Node* node2, int distance)
    : node1(node1), node2(node2), distance(distance) {
    edges.push_back(this);
  }
  bool Connects(Node* node1, Node* node2) {
    return (
      (node1 == this->node1 &&
       node2 == this->node2) ||
      (node1 == this->node2 &&
       node2 == this->node1));
  }

   public:
  Node* node1;
  Node* node2;
  int distance;
};

// Find the node with the smallest distance,
// remove it, and return it.
Node* ExtractSmallest(vector<Node*>& nodes) {
  int size = nodes.size();
  if (size == 0) return NULL;
  int smallestPosition = 0;
  Node* smallest = nodes.at(0);
  for (int i = 1; i < size; ++i) {
    Node* current = nodes.at(i);
    if (current->distanceFromStart <
      smallest->distanceFromStart) {
      smallest = current;
      smallestPosition = i;
    }
  }
  nodes.erase(nodes.begin() + smallestPosition);
  return smallest;
}

bool Contains(vector<Node*>& nodes, Node* node) {
  const int size = nodes.size();
  for (int i = 0; i < size; ++i) {
    if (node == nodes.at(i)) {
      return true;
    }
  }
  return false;
}
// Return all nodes adjacent to 'node' which are still
// in the 'nodes' collection.
vector<Node*>* AdjacentRemainingNodes(Node* node) {
  vector<Node*>* adjacentNodes = new vector<Node*>();
  const int size = edges.size();
  for (int i = 0; i < size; ++i) {
    Edge* edge = edges.at(i);
    Node* adjacent = NULL;
    if (edge->node1 == node) {
      adjacent = edge->node2;
    } else if (edge->node2 == node) {
      adjacent = edge->node1;
    }
    if (adjacent && Contains(nodes, adjacent)) {
      adjacentNodes->push_back(adjacent);
    }
  }
  return adjacentNodes;
}

int Distance(Node* node1, Node* node2) {
  const int size = edges.size();
  for (int i = 0; i < size; ++i) {
    Edge* edge = edges.at(i);
    if (edge->Connects(node1, node2)) {
      return edge->distance;
    }
  }
  return -1; 
}

void Dijkstras() {
  while (nodes.size() > 0) {
    Node* smallest = ExtractSmallest(nodes);
    vector<Node*>* adjacentNodes =AdjacentRemainingNodes(smallest);

    const int size = adjacentNodes->size();
    for (int i = 0; i < size; ++i) {
      Node* adjacent = adjacentNodes->at(i);
      int distance = Distance(smallest, adjacent) +smallest->distanceFromStart;

      if (distance < adjacent->distanceFromStart) {
        adjacent->distanceFromStart = distance;
        adjacent->previous = smallest;
      }
    }
    delete adjacentNodes;
  }
}

void PrintShortestRouteTo(Node* destination) {
	vector<string> route;
  Node* previous = destination;
  cout << "Distance from source to destination: "
     << destination->distanceFromStart<<"km\n"<< endl;
	 totDistance=destination->distanceFromStart;
  while (previous) {
	  //cout<<previous->id<<" ";
    route.push_back(previous->id);
    previous = previous->previous;
  }
  cout<<"\n-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n";
  cout<<"shortest path from "<<route.at(route.size()-1)<<" to "<<route.at(0)<<"\n\n";
  for(auto i=route.crbegin();i!=route.crend()-1;i++)
	  cout<<*i<<"->";
  cout<<destination->id<< endl;
  cout<<"\n-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n";
}

Node *place[37];
Edge *border[76];
void createGraph()
{
FILE *fp;
	char district[30],d1[30],d2[30];
	int dist,val1,val2;
	fp=fopen("input.txt","r");
	
	for(int i=0;i<37;i++)
	{fscanf(fp,"%s",district);
	place[i]=new Node(district);
	//cout<<"place from node"<<place[i]->id<<"\n";
	}
	fclose(fp);
  fp=fopen("edge.txt","r");
  for(int i=0;i<75;i++)
	{fscanf(fp,"%s %s %d",d1,d2,&dist);
//cout<<d1<<" "<<d2<<" "<<dist<<"\n";
for(int j=0;j<37;j++){
if(place[j]->id==d1)
{val1=j;
//cout<<val1;
}
if(place[j]->id==d2)
{val2=j;
//cout<<val2;
}}
	border[i]=new Edge(place[val1],place[val2],dist);
	}
	fclose(fp);	
}
void DijkstrasTest(string source,string dest) {
	
	FILE *fp;
	char district[30],d1[30],d2[30];
	int dist,val1,val2;
	fp=fopen("input.txt","r");
	
	for(int i=0;i<37;i++)
	{fscanf(fp,"%s",district);
	place[i]=new Node(district);
	//cout<<"place from node"<<place[i]->id<<"\n";
	}
	fclose(fp);
  fp=fopen("edge.txt","r");
  for(int i=0;i<75;i++)
	{fscanf(fp,"%s %s %d",d1,d2,&dist);
//cout<<d1<<" "<<d2<<" "<<dist<<"\n";
for(int j=0;j<37;j++){
if(place[j]->id==d1)
{val1=j;
//cout<<val1;
}
if(place[j]->id==d2)
{val2=j;
//cout<<val2;
}}
	border[i]=new Edge(place[val1],place[val2],dist);
	}
	fclose(fp);
 for(int i=0;i<37;i++) 
 {
	 if(place[i]->id==source)
	 {
		place[i]->distanceFromStart = 0;
//cout<<place[i]->id;		
		break;
	 }
 }
   // set start node
  Dijkstras();
  for(int i=0;i<37;i++)
  {
	if(place[i]->id==dest)
	{//cout<<place[i]->id;
		PrintShortestRouteTo(place[i]);
		break;
	}		
  }
  
}

void disp()
{//cout<<"displaying image........\n";

cout<<"tamilnadhu district map\n";
cout<<"---------------------------------------------------------------------------------------------------------------------------\n";
for(auto i=nodes.begin();i!=nodes.end();i++)
	{cout<<"| "<<(*i)->id<<"-> ";
	vector<Node*>* adjacentNodes =AdjacentRemainingNodes(*i);
	for(auto i=adjacentNodes->begin();i!=adjacentNodes->end();i++)
	{
		cout<<(*i)->id<<" | ";
	}
	cout<<"\n";
cout<<"---------------------------------------------------------------------------------------------------------------------------\n";
	
	}
	

}
void nearDistrict()
{int val;
string name;
	cout<<"enter district: ";
	cin>>name;
	for(int i=0;i<37;i++)
	{
		if(place[i]->id==name)
			{val=i;
			break;}
	}
	//cout<<place[val]->id;
	vector<Node*>* adjacentNodes =AdjacentRemainingNodes(place[val]);
	cout<<"Nearby district of "<<name<<" are as follow\n";
	for(auto i=adjacentNodes->begin();i!=adjacentNodes->end();i++)
	{
		cout<<(*i)->id<<"\n";
	}
	cout<<"\n";
}
void computeTime()
{
	float time;
	float speed;
	int n;
	        cout<<"   _______   \n";
			cout<<"  /       \\  \n";
			cout<<" /         \\  \n";
			cout<<" -----------    \n";
			cout<<" | TN:3010 |    \n";
			cout<<" -----------    \n";
			cout<<"  |_|   |_|    \n";
	do{cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
	   cout<<"|1.Estimated time in bus       |\n";
	   cout<<"|2.Estimated time in car       |\n";
	   cout<<"|3.exit                        |\n";
	   cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
		cout<<"Enter your choice:";
        cin>>n;
        switch(n)
        {
			case 1:
			cout<<"Average bus speed is fixed with 45km/hr\n";
			speed=45.0;
            time=totDistance/speed;
            cout<<"approx estimated hour in bus: "<<time<<"\n";			
			break;
			case 2:
			cout<<"Average car speed is taken as 75km/hr\n";
			speed=75.0;
			time=totDistance/speed;
			cout<<"approx estimated hour in car: "<<time<<"\n";
			break;
		}		
	}while(n!=3);
	
}
int main() {
int n;
//import graph;
createGraph();
string src,des;
do{
	cout<<"                            -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
	cout<<"                            |                Path Finder               |\n";
	cout<<"                            -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
	cout<<"\n                           welcome to path finder.Here are your option\n\n";
	cout<<"                            -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
	cout<<"                            |1.Show Tamilnadhu District map            |\n";
	cout<<"                            |2.Finding Shortest path                   |\n";
	cout<<"                            |3.Estimated Hour to reach destination     |\n";
	cout<<"                            |4.Finding Neaby district                  |\n";
	cout<<"                            |5.exit                                    |\n";
	cout<<"                            -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
cout<<"\nEnter your choice:";
cin>>n;
switch(n)
{
case 1:
disp();
break;
case 2:
cout<<"\nEnter source place:";
cin>>src;
cout<<"\nEnter destination place:";
cin>>des;
cout<<"\n";
DijkstrasTest(src,des);
cout<<"\n";
break;
case 3:
computeTime();
break;
case 4:
createGraph();
nearDistrict();
break;
}
}while(n!=5);
  cout<<"-*-*-*-*-*-*Happy journey-*-*-*-*-*-*-\n";
  return 0;
}  