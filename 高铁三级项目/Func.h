#pragma once
#include<iostream>
#include<vector>
#include<cstring>
#include<fstream>
#include<queue>
#include<stack>
#include "RailClass.h"
using namespace std;

extern vector<Rail> rail;
extern Cmp Edge[10005];
extern int TEdgeNum;
extern Cmp1 TEdge[10005];
extern int Head[10005];
extern int number;
extern int pa[10005];
extern int EdgeNum;
extern priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > PriQueue;
extern stack<int> PathStack;
extern int dis[10005];
extern bool v[10005];
extern int path[10005];

void Prin();
void BusPrin();
void PrinRail();
void PrinBusiness();
void Scan();
void BusAdd();
void BusErase();
void BusModify();
void PrinText();
void AddEdge(int start, int end);
void AddTEdge(int start, int end);
void UnionSet();
int Find(int x);
void Union(int x,int y);
void FindCircle();
void DeleEdge();
void Dijkstra(int x);
void FindMinPath(int start, int end);
class ArrayGraph:public Graph {
public:
	virtual ~ArrayGraph() {}
	virtual	int NumberOfVertices()const;
	virtual	int NumberOfEdges()const;
	virtual	bool ExistsEdge(int start, int end)const;
	virtual	void InsertEdge()const;
	virtual	void EraseEdge()const;
	virtual	int Degree(int n)const;
	virtual	bool Weighted()const;
	virtual	bool Directed()const;
};
void Make();