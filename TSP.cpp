#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>

using namespace std;

#define N 5 //����ص����
#define INF 10e5 //�����߲�ͨ��·�����
#define min(a,b) ((a>b)?b:a) //���Сֵ����

static const int M = 1 << (N - 1); //�ص�֮���������

int g[N][N] = { {INF,500,350,700,INF},
				{500,INF,400,600,1000},
				{350,400,INF,250,INF},
				{700,600,250,INF,600},
				{INF,1000,INF,600,INF} };//�ص��������

int dp[N][M]; //�߹���·��

vector<int> path; //dp���鴦��������

void HZW() 
//����·������Ҫ����
{
	for (int i = 0; i < N;i++)
	{
		dp[i][0] = g[i][0];
	}//��ʼ��

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
//��ȡ���ݺ���
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
//����������
{
	cout << "��С·����";
	vector<int>::iterator  it = path.begin();
	for (it; it != path.end(); it = it + 1)
		cout << *it << "---";
	cout << 0;
}

int main()
{
	printf("��ʼ\n\n");
	HZW();
	cout << "��Сֵ��" << dp[0][M - 1] << endl;
	In();
	Out();
	printf("\n\n�ѽ���\n\n");
	return 0;
}