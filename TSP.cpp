#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>

using namespace std;

#define N 5 //定义地点个数
#define INF 10e5 //定义走不通的路（无穷）
#define min(a,b) ((a>b)?b:a) //求较小值函数

static const int M = 1 << (N - 1); //地点之间距离输入

int g[N][N] = { {INF,500,350,700,INF},
				{500,INF,400,600,1000},
				{350,400,INF,250,INF},
				{700,600,250,INF,600},
				{INF,1000,INF,600,INF} };//地点距离输入

int dp[N][M]; //走过的路径

vector<int> path; //dp数组处理主函数

void HZW() 
//计算路径的主要函数
{
	for (int i = 0; i < N;i++)
	{
		dp[i][0] = g[i][0];
	}//初始化

	for (int j = 1; j < M; j++) 
	{
		for (int i = 0; i < N; i++)
		{
			dp[i][j] = INF;
			if (((j >> (i - 1)) & 1) == 1)
			{
				continue;
			}
			for (int k = 1; k < N; k = k + 1)
			{
				if (((j >> (k - 1)) & 1) == 0)
				{
					continue;
				}
				if (dp[i][j] > g[i][k] + dp[k][j ^ (1 << (k - 1))])
				{
					dp[i][j] = g[i][k] + dp[k][j ^ (1 << (k - 1))];
				}
			}
		}
	}
}

bool isVisited(bool visited[])
{
	for (int i = 1; i < N; i = i + 1)
	{
		if (visited[i] == false)
			return false;
	}
	return true;
}

void In()
//获取数据函数
{
	bool visited[N] = { false };
	int pioneer = 0, min = INF, S = M - 1, temp;
	path.push_back(0);
	
	while (!isVisited(visited))
	{
		for (int i = 1; i < N; i = i + 1)
		{
			if (visited[i] == false && (S & (1 << (i - 1))) != 0)
			{
				if (min > g[i][pioneer] + dp[i][(S ^ (1 << (i - 1)))])
				{
					min = g[i][pioneer] + dp[i][(S ^ (1 << (i - 1)))];
					temp = i;
				}
			}
		}
		pioneer = temp;
		path.push_back(pioneer);
		visited[pioneer] = true;
		S = S ^ (1 << (pioneer - 1));
		min = INF;
	}
}

void Out()
//结果输出函数
{
	cout << "最小路径：";
	vector<int>::iterator  it = path.begin();
	for (it; it != path.end(); it = it + 1)
		cout << *it << "---";
	cout << 0;
}

int main()
{
	printf("开始\n\n");
	HZW();
	cout << "最小值：" << dp[0][M - 1] << endl;
	In();
	Out();
	printf("\n\n已结束\n\n");
	return 0;
}