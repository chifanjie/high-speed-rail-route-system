#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<Windows.h>
#include"Func.h"
#include"RailClass.h"
using namespace std;
int main()
{
	Scan();
	while(true) {
		UnionSet();
		system("cls");
		Prin();
		int num;
		cin >> num;
		switch (num) {
		    case 1: {
			    BusPrin();
			    int y;
			    cin >> y;
			    switch (y) {
			        case 1: {
				        PrinRail() ;
						break;
			        }
			        case 2: {
						BusAdd();
						break;
			        }
					case 3: {
						BusErase();
						break;
					}
					case 4: {
						BusModify();
						break;
					}
					default: {
						cout << "请选择正确的数字" << endl;
						system("pause");
						break;
					}
			    }
			    break;
		    }
			
			case 2: {
				for (unsigned int i = 1; i <= number; i++) {
					cout << i << "." << rail[i - 1].GetName() << endl;
				}
				int start,end;
				cout << "请输入起点:"; cin >> start;
				cout << "请输入终点:"; cin >> end;
				if (start <= 0 || start > number) {
					cout << "不存在该起点" << endl;
					system("pause");
				}
				else {
					if (end <= 0 || end > number) {
						cout << "不存在该终点" << endl;
						system("pause");
					}
					else {
							AddEdge(start, end);
							AddEdge(end, start);
							AddTEdge(start, end);
							cout << "添加成功" << endl;
							system("pause");
					}
				}
				break;
			}
			case 3: {
				for (unsigned int i = 1; i <= number; i++) {
					cout << i << "." << rail[i - 1].GetName() << endl;
				}
				int x, y;
				cout << "请输入结点1:"; cin >> x;
				cout << "请输入结点2:"; cin >> y;
				if (x <= 0 || x > number||y<=0||y>number) {
					cout << "结点不合法" << endl;
					system("pause");
				}
				else {
					if (pa[x] == pa[y]) {
						cout << "两个结点连通" << endl;
						system("pause");
					}
					else {
						cout << "两个结点不连通" << endl;
						system("pause");
					}
				}

				break;
			}
			case 4: {
				for (unsigned int i = 1; i <= number; i++) {
					cout << i << "." << rail[i - 1].GetName() << endl;
				}
				string x;
				cout << "请输入要查看的高铁站编号:"; cin >> x;
				bool flag = false;
				int num;
				for (int i = 0; i < rail.size(); i++) {
					if (rail[i].GetID() == x) {
						flag = true;
						num = rail[i].num;
					}
				}
				if (flag == false) {
					cout << "不存在当前商家编号" << endl;
					system("pause");
				}
				else {
					for (unsigned int i = 1; i <= number; i++) {
						if(Find(num) == Find(i))
					    cout << rail[i - 1].GetID() << "." << rail[i - 1].GetName() << endl;
				    }
					system("pause");
				}
				break;
			}
			case 5 :{
				FindCircle();
				break;
			}
			
			case 6: {
				DeleEdge();
				break;
			}
			case 7: {
				Make();
				break;
			}
			case 8: {
				PrinText();
				cout<<"保存信息成功"<<endl;
				system("pause");
				break;
			}
			case 9: {
				for (int i = 1; i <= rail.size(); i++) {
					cout << i << "." << rail[i - 1].GetName() << endl;
				}
				for (int i = rail.size() + 1; i <= number; i++) {
					cout << i << "." << rail[i - rail.size() - 1].GetName() << endl;
				}
				int start, end;
				cout << "请输入起始位置："; cin >> start;
				cout << "请输入终止位置："; cin >> end;
				Dijkstra(start);
				FindMinPath(start, end);
				break;
			}
			case 0: {
				PrinText();
				system("cls");
				cout<<"*===================================================================================* \n" << endl;
			    cout << "\n\n\t\t\t\t* 您已退出系统，欢迎下次使用 * \n\n\n" << endl;
			    cout<<"*===================================================================================* \n" << endl;
                system("pause");
	            return 0;
			}
			default: {
				cout << "该选项无效，请重新输入" << endl;
				system("pause");
				break;
			}
		}

		}

	system("pause");
	return 0;
}