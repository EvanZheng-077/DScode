#include<iostream>
#define INF 100000 //表示正无穷
using namespace std;
const int DefaultVertices = 30;

class Graph
{
public:
	static const int maxWeight = INF;
	Graph(int size = DefaultVertices) {
		maxVertices=1000;
		numEdges=0;
		numVertices=0;
	};
	~Graph() {};
	bool GraphEmpty()const //检查为空
	{
		if (numEdges == 0)return true;
		else return false;
	}
	bool GraphFull()const //检查为满
	{
		if (numVertices == maxVertices || numEdges == maxVertices * (maxVertices - 1) / 2)
			return true;
		else
			return false;
	}
	int NumberOfVertices() { return numVertices; }			//返回当前顶点数
	int NumberOfEdges() { return numEdges; }				//返回当前边数
	virtual int getValue(int i) = 0;						//取顶点i的值，i不合理返回0
	virtual int getWeight(int v1, int v2) = 0;				//取边（v1，v2）的权值
	virtual int getFirstNeighbor(int v) = 0;				//取顶点v的第一个邻接顶点
	virtual int getNextNeighbor(int v, int w) = 0;			//取邻接顶点w的下一个邻接顶点
	virtual bool insertVertex(const int& vertex) = 0;		//插入一个顶点vertex
	virtual bool insertEdge(int v1, int v2, int cost) = 0;	//插入边（v1,v2）,权值cost
	virtual bool removeVertex(int v) = 0;					//删除顶点v和所有与之关联的边
	virtual bool removeEdge(int v1, int v2) = 0;			//删除边（v1,v2）
	virtual int getVertexPos(int vertex) = 0;

protected:
	int maxVertices;
	int numEdges;
	int numVertices;

}; 

class Graphmtx : public Graph
{

public:
	Graphmtx(int sz = DefaultVertices);							//构造
	~Graphmtx()													//析构
	{
		delete[]VerticesList;
		delete[]Edge;
	}
	int getValue(int i)											//取顶点i的值，若i不合理返回NULL
	{
		if (i >= 0 && i < numVertices) return VerticesList[i];
		else return NULL;
	}
	int getWeight(int v1, int v2)								//取边（v1,v2）的权值，不合理返回0
	{
		if (v1 != -1 && v2 != -1)
			return Edge[v1][v2];
		else
			return 0;
	}
	int getFirstNeighbor(int v); //重要
	int getNextNeighbor(int v, int w);//重要
	bool insertVertex(const int& vertex);
	bool insertEdge(int v1, int v2, int cost);
	bool removeVertex(int v);
	bool removeEdge(int v1, int v2);
	void inputGraph();
	void outputGraph();
	int getVertexPos(int vertex)									//给出顶点在图中的位置
	{
		for (int i = 0; i < numVertices; i++)
			if (VerticesList[i] == vertex)return i;
		return -1;												//找不到返回-1
	}
private:
	int* VerticesList;											//顶点表
	int** Edge;													//邻接矩阵

};

Graphmtx::Graphmtx(int sz)	//构造函数
{
	maxVertices = sz;
	numVertices = 0;
	numEdges = 0;
	int i, j;
	VerticesList = new int[maxVertices];
	Edge = new int * [maxVertices];
	for (i = 0; i < maxVertices; i++)
		Edge[i] = new int[maxVertices];
	for (i = 0; i < maxVertices; i++)
		for (j = 0; j < maxVertices; j++)
			Edge[i][j] = (i == j) ? 0 : maxWeight;//没有边则赋予infinity
}

int Graphmtx::getFirstNeighbor(int v)//返回v的第一个邻接顶点的位置，（v是顶点的标号，不是顶点值）
{
	if (v != -1)
	{
		for (int col = 0; col < maxVertices; col++)
			if (Edge[v][col] > 0 && Edge[v][col] < maxWeight)
				return col;
	}
	return -1;
}

int Graphmtx::getNextNeighbor(int v, int w)//返回v的邻接顶点w的下一个邻接顶点
{
	if (v != -1 && w != -1)
	{
		for (int col = w + 1; col < maxVertices; col++)
		{
			if (Edge[v][col] > 0 && Edge[v][col] < maxWeight)
				return col;
		}
	}
	return -1;
}

bool Graphmtx::insertVertex(const int& vertex) //插入一个顶点
{
	if (numVertices == maxVertices)return false; //顶点表已满，返回false
	VerticesList[numVertices++] = vertex;
	return true;
}

bool Graphmtx::insertEdge(int v1, int v2, int cost)//插入一条边
{
	if (v1 > -1 && v1 < numVertices && v2 > -1 && v2 < numVertices) //检查条件
	{
		if (Edge[v1][v2] == maxWeight)
		{
			Edge[v1][v2] = Edge[v2][v1] = cost;
			numEdges++;
			return true;
		}
		else
		{
			cout << "该边已存在，添加失败" << endl;
			return false;
		}
	}
	else return false;
}

bool Graphmtx::removeVertex(int v)						//删除一个顶点
{
	if (v<0 || v>numVertices)	return false;			//v不在图中，不删除
	if (numVertices == 1)	return false;				//只剩一个顶点，不删除
	int i, j;
	VerticesList[v] = VerticesList[numVertices - 1];	//顶点表中删除
	
	for (i = 0; i < numVertices; i++)					//边数调整
		if (Edge[i][v] > 0 && Edge[i][v] < maxWeight)
			numEdges--;
	
	for (i = 0; i < numVertices; i++)					//用最后一列填补第v列
		Edge[i][v] = Edge[i][numVertices - 1];
	numVertices--;										//顶点数调整
	
	for (j = 0; j < numVertices; j++)					//用最后一行填补第v行
		Edge[v][j] = Edge[numVertices][j];
	return true;
}

bool Graphmtx::removeEdge(int v1, int v2)		//删除边
{
	if (v1 > -1 && v1<numVertices && v2>-1 && v2 < numVertices && Edge[v1][v2]>0 && Edge[v1][v2] < maxWeight)
	{
		Edge[v1][v2] = Edge[v1][v2] = maxWeight;
		numEdges--;
		return true;
	}
	else return false;
};

void Graphmtx::inputGraph()
{
	//通过从输入流对象in输入n的顶点和e条五项边的信息建立邻接矩阵表示的图G。邻接矩阵初始化工作在构造函数完成
	int i, j, k, m, n;
	int e1, e2;
	int weight;
	cout << "请输入顶点数和边数(空格隔开):" << endl;
	cin >> n >> m;	//输入点数n的边数m
	cout << "请依次输入顶点值:" << endl;
	for (i = 0; i < n; i++)//输入顶点，建立顶点表
	{
		cin >> e1;
		this->insertVertex(e1);
		//G.insertVertex(e1);
	}
	cout << "请依次输入边，形如 v1 v2 weight （v1，v2为点的值）：" << endl;
	i = 0;
	while (i < m)
	{
		cin >> e1 >> e2 >> weight;
		j = this->getVertexPos(e1);//查顶点号
		k = this->getVertexPos(e2);
		if (j == -1 || k == -1)
		{
			cout << "边两端点信息有误，重新输入！" << endl;
		}
		else
		{
			if (this->insertEdge(j, k, weight))
				i++;
		}
	}

}

void Graphmtx::outputGraph()
{
	//输出图的所有顶点和边信息
	int i, j, n, m;
	int e1, e2;
	int weight;
	n = this->NumberOfVertices();	 //点数
	m = this->NumberOfEdges();		//边数
	cout << "顶点数和边数为：";
	cout << n << "," << m << endl;		//输出点数和边数
	cout << "各边依次为：" << endl;
	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			weight = this->getWeight(i, j);
			if (weight > 0 && weight < maxWeight)
			{
				e1 = this->getValue(i);
				e2 = this->getValue(j);
				cout << "(" << e1 << "," << e2 << "," << weight << ")" << endl;
			}
		}
	}
}

void test_Graphmtx()
{
	int ch1, ch2;
	int weight;
	Graphmtx g(30);
	g.inputGraph();		//构造图
	g.outputGraph();	//显示图

	cout << "顶点数和边数：" << g.NumberOfVertices() << " " << g.NumberOfEdges() << endl;
	cout << "查看第一个邻接顶点:";
	cin >> ch1;
	cout << g.getValue(g.getFirstNeighbor(g.getVertexPos(ch1))) << endl;
	cout << "查看后一个邻接顶点:";
	cin >> ch1 >> ch2;
	cout << g.getValue(g.getNextNeighbor(g.getVertexPos(ch1), g.getVertexPos(ch2))) << endl;

	cout << "插入顶点:";
	cin >> ch1;
	g.insertVertex(ch1);  //插入点
	cout << "插入边：" << endl;
	cin >> ch1 >> ch2 >> weight;
	g.insertEdge(g.getVertexPos(ch1), g.getVertexPos(ch2), weight);//插入边
	g.outputGraph();

	cout << "删除边(输入两个端点的值)：";
	cin >> ch1 >> ch2;
	g.removeEdge(g.getVertexPos(ch1), g.getVertexPos(ch2)); //删除边
	g.outputGraph();
	
	
	cout << "删除点：";
	cin >> ch1;
	g.removeVertex(g.getVertexPos(ch1));
	g.outputGraph();

}

int main()
{
	test_Graphmtx();
	system("pause");
	return 0;
}
