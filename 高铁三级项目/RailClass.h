#pragma once
#include<iostream>
#include<string>
using namespace std;
class Rail {
private:
	string ID;
	string Name;
	int Degree;
public:
	int TempDegree; 
	int num;
	void Add(string a, string b, int c);
	void Prin();
	string GetID();
	string GetName();
	int GetDegree();
	void Modify(int x, string y);
	void AddDegree();
	void InitDegree();
};
struct Cmp {
	int end;
	int next;
	int value;
};//用于存储边的结构体
struct Cmp1 {
	int start;
	int end;
};
class Graph {
public:
	virtual ~Graph() {}
	virtual int NumberOfVertices() const = 0;
	virtual int NumberOfEdges() const = 0;
	virtual bool ExistsEdge(int, int) const = 0;
	virtual void InsertEdge() const = 0;
	virtual void EraseEdge() const = 0;
	virtual int Degree(int) const = 0;
	virtual bool Weighted() const = 0;
	virtual bool Directed() const = 0;
};
