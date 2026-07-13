#include "Func.h"
vector<Rail> rail;
Cmp Edge[10005];
int Head[10005];
int pa[10005];//并查集中记录祖先的数组
int number;//结点的个数
int EdgeNum;//边的数量的二倍
int TEdgeNum;//边的数量
Cmp1 TEdge[10005];
int dis[10005];//记录到起始位置的距离
bool v[10005];//在Dijkstra算法中对结点进行标识，只允许访问一次
int path[10005];//在Dijkstra算法中记录最短路径
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > PriQueue;//升序队列，小顶堆，先弹小的元素出来
stack<int> PathStack;
void Prin() {

	cout<<"\n************************************************************************************************************\n" << endl;
	cout << "\n\t\t\t* 高铁路线规划系统 *\n\n\n" << endl;
	cout << "     1.管理高铁站信息               2.添加高铁路径     \n" << endl << endl;
	cout << "     3.判断城市可达性               4.查看地铁可达范围     \n" << endl << endl;
	cout << "     5.判断是否存在环路             6.删除高铁路线     \n" << endl << endl;
	cout << "     7.继承Graph的ArrayGraph类      8.保存信息     \n" << endl << endl;
	cout << "     9.两高铁站间中转最少            0.退出系统\n" << endl << endl;
	cout<<"\n************************************************************************************************************\n" << endl;
	cout << "请选择你要进行的操作： " << endl;
		
}//打印输出程序运行后的主界面
void Scan() {
	ifstream in("rail.txt", ios::in);
	while (in.peek() != -1) {
		Rail temp;
		string a, b;
		in >>a >> b ;
		temp.Add(a, b,  0);
		rail.push_back(temp);
	}//读取高铁信息
	in.close();
	number = 0;
	for (int i = 0; i < rail.size(); i++) {
		rail[i].num = ++number;
	}
	EdgeNum = 0;
	TEdgeNum = 0;
	ifstream innn("Edge.txt", ios::in);
	while (innn.peek()!=-1) {
		int u, v;
		innn >> u >> v ;
		AddEdge(u, v);
		AddEdge(v, u);
		AddTEdge(u, v);
	}
	innn.close();
}//读入数据
void BusPrin() {
	system("cls");
	cout << "高铁站管理界面:" << endl;
	cout << "1.查看高铁站信息" << endl;
	cout << "2.添加高铁站信息" << endl;
	cout << "3.删除高铁站信息" << endl;
	cout << "4.更改高铁站信息" << endl;
	cout << "请输入您需求的功能：" << endl;
}
void PrinRail() {
	cout << "ID NAME 连通数" << endl;
	for (int i = 0; i < rail.size(); i++) {
		rail[i].Prin();
	}
	system("pause");
}
void BusAdd() {//添加高铁函数
	string a, b;
	cout << "请输入高铁站编号:"; cin >> a;
	cout << "请输入高铁站名称:"; cin >> b;
	bool flag = true;//用于标识是否有当前高铁编号
	for (int i = 0; i < rail.size(); i++) {
		if (rail[i].GetID() == a) {
			flag = false;
			break;
		}
	}
	if (flag == false) {
		cout << "已存在该高铁站编号，添加失败" << endl;
		system("pause");
	}
	else {
		for (int i = 1; i <= TEdgeNum; i++) {
			if (TEdge[i].start > rail.size()) {
				TEdge[i].start++;
			}
			if (TEdge[i].end > rail.size()) {
				TEdge[i].end++;
			}
		}//用于更新已经存在边的结点
		Rail temp;
		temp.Add(a, b, 0);
		rail.push_back(temp);
		number = 0;
		for (int i = 0; i < rail.size(); i++) {
			rail[i].num = ++number;
		}
		int EdgeNum = 0;
		memset(Head, 0, sizeof(Head));
		memset(Edge, 0, sizeof(Edge));
		for (int i = 1; i <= TEdgeNum; i++) {
			AddEdge(TEdge[i].start, TEdge[i].end);
			AddEdge(TEdge[i].end, TEdge[i].start);
		}
		cout << "添加成功" << endl;
		system("pause");
	}
}
void BusErase() {
	for (int i = 1; i <= rail.size(); i++) {
		cout << i << "." << rail[i - 1].GetName() << endl;
	}
	int a;
	bool flag = true;
	cout << "请输入要删除的序号" << endl; cin >> a;
	for (vector<Rail>::iterator it=rail.begin(); it != rail.end(); it++) {
		if ((*it).num == a) {
			for (int i = 1; i <= TEdgeNum; i++) {
				if (TEdge[i].start == a || TEdge[i].end == a) {
					for (int j = i; j < TEdgeNum; j++) {
						TEdge[i].start = TEdge[i + 1].start;
						TEdge[i].end = TEdge[i + 1].end;
					}
					TEdgeNum--;
					i--;
				}
				else {
					if (TEdge[i].start > a) {
						TEdge[i].start--;
					}
					if (TEdge[i].end > a) {
						TEdge[i].end--;
					}
				}
			}
			rail.erase(it);
			flag = false;
			break;
		}
	}
	if (flag == true) {
		cout << "不存在当前高铁站编号" << endl;
		system("pause");
	}
	else {
		number = 0;
		for (int i = 0; i < rail.size(); i++) {
			rail[i].num = ++number;
		}
		int EdgeNum = 0;
		memset(Head, 0, sizeof(Head));
		memset(Edge, 0, sizeof(Edge));
		for (int i = 1; i <= TEdgeNum; i++) {
			AddEdge(TEdge[i].start, TEdge[i].end);
			AddEdge(TEdge[i].end, TEdge[i].start);
		}
		cout << "删除成功" << endl;
		system("pause");
	}
}
void BusModify() {
	string a;
	cout << "请输入您要修改的高铁站编号："; cin >> a;
	bool flag = false;
	int index = -1;
	for (int i = 0; i < rail.size(); i++) {
		if (rail[i].GetID() == a) {
			flag = true;
			index = i;
			break;
		}
	}
	if (flag == false) {
		cout << "不存在此编号的高铁站,修改失败" << endl;
		system("pause");
	}
	else {
		cout << "请选择您要修改的属性:" << endl;
		cout << "1.ID" << endl;
		cout << "2.名称Name" << endl;
		int aa; string b;
		cin >> aa;
		cout << "请输入修改后的值" << endl;
		cin >> b;
		switch (aa) {
		     case 1: {
				 bool flag = true;
				 for (int i = 0; i < rail.size(); i++) {
					 if (rail[i].GetID() == b) {
						 flag = false;
						 break;
					 }
				 }
				 if (flag == false) {
					 cout << "修改失败，当前编号已存在" << endl;
					 system("pause");
				 }
				 else {
					 rail[index].Modify(1, b);
					 cout << "修改成功" << endl;
					 system("pause");
				 }
				 break;
			 }
			 case 2: {
				 rail[index].Modify(2, b);
				 cout << "修改成功" << endl;
				 system("pause");
				 break;
			 }
			 default: {
				 cout << "不存在当前功能" << endl;
				 system("pause");
				 break;
			 }
		}
	}
}
void PrinText() {//将数据输出到txt文件中
	ofstream out("rail.txt", ios::out);
	for (int i = 0; i < rail.size(); i++) {
		out <<rail[i].GetID() << " " << rail[i].GetName();
		if (i != rail.size() - 1) {
			out << endl;
		}
	}
	out.close();
	ofstream ou("Edge.txt", ios::out);
	for (int i = 1; i <=TEdgeNum; i++) {
		ou << TEdge[i].start << " " << TEdge[i].end;
		if (i != TEdgeNum) ou << endl;
	}
	ou.close();
}
void AddEdge(int start, int end) {//添加有向边的函数
	if (Find(start) != Find(end)) {
		Union(start, end);
	}//如果两个结点不在同一集合内，便将两个结点合并
	Edge[++EdgeNum].end = end;
	Edge[EdgeNum].next = Head[start];
	Head[start] = EdgeNum;//Head数组指向存储该边的下表
}
void AddTEdge(int start, int end) {//添加无向边的函数
	if (start > 0 && start <= number) {
		rail[start - 1].AddDegree();//将高铁结点的度+1
	}
	if (end > 0 && end <= number) {
		rail[end - 1].AddDegree();
	}
	TEdge[++TEdgeNum].start = start;
	TEdge[TEdgeNum].end = end;
}
int Find(int x) {//并查集查找祖先函数
	if (pa[x] == x) return x;
	else return pa[x] = Find(pa[x]);//采用路径压缩的方法，降低程序的时间复杂度
}
void Union(int x, int y) {//并查集合并函数
	pa[Find(y)] = Find(x);
	return;
}
void UnionSet() {//初始化并查集函数
	for (int i = 1; i <= number; i++) {
		pa[i] = i;//将每个结点的父亲结点都初始化为自己
	}
	for (int i = 1; i <= number; i++) {
		for (int j = Head[i]; j != 0; j=Edge[j].next) {
			if (Find(i) != Find(Edge[j].end)) {
				Union(i, Edge[j].end);//根据边来合并不同的结点
			}
		}
	}
}
void FindCircle() {//寻找环路的函数
	bool use[10005];//标记每一个结点，只允许访问一个结点一次
	memset(use, true, sizeof(use));//初始化use数组
	queue<int> x;//将度小于等于1的结点压入队列中
	int temp = 0;
	for (int i = 1; i <= number; i++) {
		rail[i - 1].InitDegree();//通过操作一个临时度来进行判断
	}
	for (int i = 1; i <= number; i++) {
		if (rail[i - 1].TempDegree <= 1) {
			x.push(i);
			use[i] = false;//将i结点置为已经访问过
			temp++;//用于统计已经访问过的结点
		}
	}
	while (x.size()) {
		if (temp == number) break;
		int u = x.front();
		x.pop();
		for (int i = Head[u]; i; i = Edge[i].next) {
			if (use[Edge[i].end] == true) {
				if (u > 0 && u <= number) {
					rail[u - 1].TempDegree -= 1;
				}
				if (Edge[i].end > 0 && Edge[i].end <= number) {
					rail[Edge[i].end - 1].TempDegree -= 1;
				}
			}
		}
		for (int i = 1; i <=number; i++) {
			if (use[i]==true && rail[i - 1].TempDegree <= 1) {
				x.push(i);
				use[i] = false;
				temp++;
			}
		}
	}
	if (temp == number) {//如果访问的结点数等于总结点数，则证明图中不含有环路
		cout << "该路径不存在环路" << endl;
		system("pause");
	}
	else {
		cout << "该路径存在环路" << endl;
		system("pause");
	}
}
void DeleEdge() {
	for (int i = 1; i <= number; i++) {
		cout << i << "." << rail[i - 1].GetName() << endl;
	}
	int start, end;
	cout << "请输入要删除边的起始结点:"; cin >> start;
	cout << "请输入要删除边的终止结点:"; cin >> end;
	bool flag = false;
	if (start <= 0 || start > number) {
		cout << "不存在这样的起始结点" << endl;
		system("pause");
	}
	else {
		if (end <= 0 || end > number) {
			cout << "不存在这样的终止结点" << endl;
			system("pause");
		}
		else {
			for (int i = 1; i <= TEdgeNum; i++) {
				if ((TEdge[i].start == start && TEdge[i].end == end) || (TEdge[i].end == start && TEdge[i].start == end)) {
					flag = true;
					for (int j = i; j < TEdgeNum; j++) {
						TEdge[i].start = TEdge[i + 1].start;
						TEdge[i].end = TEdge[i + 1].end;
					}
					TEdgeNum--;
					break;
				}
			}
			if (flag == false) {
				cout << "该两个结点之间不存在路径" << endl;
				system("pause");
			}
			else {
				int EdgeNum = 0;
				memset(Head, 0, sizeof(Head));
				memset(Edge, 0, sizeof(Edge));
				for (int i = 1; i <= TEdgeNum; i++) {
					AddEdge(TEdge[i].start, TEdge[i].end);
					AddEdge(TEdge[i].end, TEdge[i].start);
				}
				cout << "删除成功" << endl;
				system("pause");
			}
		}
	}
}
int ArrayGraph::NumberOfVertices() const {
	return number;
}
int ArrayGraph::NumberOfEdges()const {
	return TEdgeNum;
}
bool ArrayGraph::ExistsEdge(int start, int end)const {
	if (Find(start) == Find(end)) {
		return true;
	}
	else {
		return false;
	}
}
void ArrayGraph::InsertEdge()const {
	for (int i = 1; i <= number; i++) {
		cout << i << "." << rail[i - 1].GetName() << endl;
	}
	int start, end;
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
}
void ArrayGraph::EraseEdge()const {
	 DeleEdge();
}
int ArrayGraph::Degree(int n)const {
	if (n > 0 && n <= rail.size()) {
		return rail[n - 1].GetDegree();
	}
	else {
		return rail[n - 1 - rail.size()].GetDegree();
	}
}
bool ArrayGraph::Weighted()const {
	return true;
}
bool ArrayGraph::Directed()const {
	return false;
}
void Make() {
	system("cls");
	cout << "请选择您需要的功能" << endl;
	int choice;
	ArrayGraph v;
	cout << "1.输出结点数" << endl;
	cout << "2.输出边数" << endl;
	cout << "3.判断是否存在边使得两个结点连通" << endl;
	cout << "4.插入一条新边" << endl;
	cout << "5.删除一条边" << endl;
	cout << "6.是否为加权图" << endl;
	cout << "7.是否为有向图" << endl;
	cin >> choice;
	switch (choice) {
	case 1: {
		cout << v.NumberOfVertices() << endl;
		system("pause");
		break;
	}
	case 2: {
		cout << v.NumberOfEdges() << endl;
		system("pause");
		break;
	}
	case 3: {
		for (int i = 1; i <= number; i++) {
			  cout << i << "." << rail[i - 1].GetName() << endl;
		}
		int start, end;
		cout << "请输入第一个结点";
		cin >> start;
		cout << "请输入第二个结点";
		cin >> end;
		if(pa[start] == 0||pa[end]==0)
		{
			cout << "当前没有结点" << endl;
			system("pause");
			break;
		}
		else {
			if (v.ExistsEdge(start, end))
				cout << "存在一条边使得" << start << "与" << end << "两个结点连通" << endl;
			else
			{
				cout << "不存在一条边使得" << start << "与" << end << "两个结点连通" << endl;
			}
		}
		system("pause");
		break;
	}
	case 4: {
		v.InsertEdge();
		break;
	}
	case 5: {
		v.EraseEdge();
		break;
	}
	case 6: {
		if (!v.Weighted())
			cout << "该图为有权图" << endl;
		else
		{
			cout << "该图为无权图" << endl;
		}
		system("pause");
		break;
	}
	case 7: {
		if (v.Directed())
			cout << "该图为有向图" << endl;
		else
		{
			cout << "该图为无向图" << endl;
		}
		system("pause");
		break;
	}
	}
}
void set() {
	for(int i=1;i<=EdgeNum;i++){
		Edge[i].value=1;
	}
}
void Dijkstra(int x) {
	set();
	for (int i = 1; i <= number; i++) {
		dis[i] = 99999999;//将dis数组置为一个极大值，标记为无法抵达
	}
	memset(v, 0, sizeof(v));//memset函数初始化v和path数组
	memset(path, 0, sizeof(path));
	dis[x] = 0;//起点的dis数组置为0
	PriQueue.push(make_pair(0, x));//将起点的距离和结点压入优先队列中，根据dis数组的值排序
	while (PriQueue.size()) {//当优先队列为空时退出循环
		int u = PriQueue.top().second;
		PriQueue.pop();
		if (v[u] == 1) continue;//如果访问过这个结点便退出这层循环
		v[u] = 1;
		for (int i = Head[u]; i; i = Edge[i].next) {//依次遍历该结点的每一条边
			if (dis[Edge[i].end] > dis[u] + Edge[i].value) {
				dis[Edge[i].end] = dis[u] + Edge[i].value;
				path[Edge[i].end] = u;//记录到达目标结点最佳路径的前一结点
				PriQueue.push(make_pair(dis[Edge[i].end], Edge[i].end));//将该边的终点和路径压入优先队列
			}
		}
	}
}
void FindMinPath(int start, int end) {//寻找最小中转数路径函数
	if (start > number || start <= 0) {//对起始结点的范围进行判断
		cout << "不存在该起始位置" << endl;
		system("pause");
	}
	else {
		if (end > number || end <= 0) {//对终止节点的范围进行判断
			cout << "不存在该终止位置" << endl;
			system("pause");
		}
		else {
			if (Find(start) != Find(end)) {
				cout << "不存在一条路径使其连通" << endl;
				system("pause");
			}
			else {
				cout << "存在一条路径使其联通，最少中转路径为:" << endl;
				int index = end;
				while (path[index] != 0) {
					PathStack.push(path[index]);
					index = path[index];
				}//根据path数组输出路径
				
				int temp = PathStack.top();
				PathStack.pop();
				if (temp > 0 && temp <= number) {
					cout << temp << "." << rail[temp - 1].GetName() << "->";
				}
				while (PathStack.size() != 0) {
					temp = PathStack.top();
					PathStack.pop();
					if (temp > 0 && temp <= number) {
						cout << temp << "." << rail[temp - 1].GetName() << "->";
					}

				}
				if (end <= number) {
					cout << end << "." << rail[end - 1].GetName();
				}
				cout << endl << "最少中转高铁站数目为：" << dis[end]-1 << endl;
				system("pause");
			}
		}
	}
}
