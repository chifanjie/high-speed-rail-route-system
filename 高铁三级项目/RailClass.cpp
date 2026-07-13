#pragma once
#include "RailClass.h"
using namespace std;
void Rail::Add(string a, string b, int c){
	ID=a;
	Name=b;
	Degree=c;
}//更新Rail对象的值
void Rail::Prin(){
	cout<<ID<<" "<<Name<<" "<<Degree<<endl;
}
string Rail::GetID() {
	return ID;
}
string Rail::GetName() {
	return Name;
}
int Rail::GetDegree() {
	return Degree;
}
void Rail::Modify(int x,string y) {
	switch (x) {
	case 1: {
		ID = y;
		break;
	}
	case 2: {
		Name = y;
		break;
	}
	}
}
void Rail::AddDegree() {
	Degree++;
}
void Rail::InitDegree() {
	TempDegree = Degree;
}