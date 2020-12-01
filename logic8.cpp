#include <time.h>
#include <iostream>
#include <stack>
#include <queue>
#include <conio.h>
//работа сделана, есть баг с изолированной вершиной
using namespace std;
queue <int> Q;
int i, j, m, n, h;
int* vis;
int* v;
int** graph;
int* ex;
int* e;

void BFS() {
	for (int j = 0; j < m; j++) {
		printf("\nПоиск расстояний от вершины %d\n", j + 1);
		for (int i = 0; i < m; i++) {
			vis[i] = 1000;
			v[j] = 0;
			e[j] = 0;
		}

		int s = j;
		Q.push(s);
		int st = s;

		vis[s] = 0;

		while (!Q.empty())
		{
			s = Q.front();
			Q.pop();

			for (int r = 0; r < n; r++)
				if ((graph[s][r] > 0) && (vis[r] > vis[s] + graph[s][r]))
				{
					Q.push(r);
					vis[r] = vis[s] + graph[s][r];
				}
		}

		for (int i = 0; i < m; i++)
		{
			//проверка на концевую вершину
			if (vis[i] == h) {
				e[j]++;
			}
			//проверка на изолированную вершину
			if (vis[i] == 1000) {
				printf("- ");
				vis[i] = 0;
			}
			//вывод вершин
			else
				printf("%d ", vis[i]);
			v[j] += vis[i];

			if (vis[i] > ex[st])
			{
				ex[st] = vis[i];
			}
			
		}
	}
	int k = 0;
	int rad = 100000;
	int dia = 0;
	printf("\nЭксцентриситеты: \n");
	for (int i = 0; i < m; i++) {

		printf("%d ", ex[i]);
		if (ex[i] == 0)
			continue;
		if (ex[i] > dia)
			dia = ex[i];
		if ((ex[i] < rad) && (ex[i] != -1))
			rad = ex[i];
	}
	printf("\n\nРадиус - %d\nДиаметр - %d", rad, dia);
	printf("\nЦентральные вершины: \n");
	for (int i = 0; i < m; i++) {
		if (ex[i] == rad)
			printf("%d ", i + 1);
	}
	printf("\nПериферийные вершины: \n");
	for (int i = 0; i < m; i++) {
		if (ex[i] == dia)
			printf("%d ", i + 1);
	}
	printf("\nИзолированные вершины: \n");
	for (int i = 0; i < m; i++) {
		if (ex[i] == 0) {
			printf("%d ", i + 1);
			k++;
		}
	}
	printf("\nДоминирующие вершины: \n");
	if (k == 0) {
		for (int i = 0; i < m; i++) {
			if (v[i] == m - 1)
				printf("%d ", i + 1);
		}
	}
	
	printf("\nКонцевые вершины: \n");
	for (int i = 0; i < m; i++) {
		if (e[i] == h)
			printf("%d ", i + 1);
	}
}

void DFS_main()
{
	setlocale(LC_ALL, "Rus");
	printf("Размерность:  ");
	scanf_s("%d", &m);
	printf("Диапазон числе в графе: ");
	scanf_s("%d", &h);
	h++;
	n = m;
	graph = new int* [m];
	v = (int*)malloc(m * sizeof(int));
	ex = (int*)malloc(m * sizeof(int));
	e = (int*)malloc(m * sizeof(int));
	vis = (int*)malloc(m * sizeof(int));

	for (int i = 0; i < m; i++) {
		graph[i] = new int[m];
	}
	//генерация матрицы
	int start;
	printf("Матрица смежности: \n");
	srand(time(NULL));
	for (i = 0; i < m; ++i) {
		for (j = i; j < m; ++j) {
			graph[i][j] = graph[j][i] = rand() % h;
		}
		graph[i][i] = 0; //обнуление вершины
	}
	h--;
	//нумерование столбцов
	printf("  ");
	for (j = 0; j < m; j++)
	{
		printf("k%d ", j + 1);
	}

	printf("\n");

	//нумерование строк
	for (i = 0; i < m; ++i)
	{
		printf("v%d ", i + 1);
		for (j = 0; j < m; ++j)
			printf("%d  ", graph[i][j]);
		printf("\n\n");
	}
	//вывод списков смежности (работает только с невзвешенным графом)

	for (i = 0; i < m; i++)
	{
		printf("\n%d - ", i + 1);
		for (j = 0; j < m; j++) {
			if (graph[i][j] != 0) printf("%d ", j + 1); 
			
		}
	}

	printf("\n");
	BFS();
	_getch();
}

int Menu(void)
{
	system("CLS");
	int c = 0;
	setlocale(LC_ALL, "Rus");
	while (c < '0' || c > '1')
	{
		printf(
			"::=================================::\n"
			"|| 1 : Начать                      ||\n"
			"|| 0 : Выход                       ||\n"
			"::=================================::\n"
			"> ");
		c = _getch();
		system("cls");
	}
	return c;
}

void main(void)
{
	int Select;
	while ((Select = Menu()) != '0' && Select != 27)
		switch (Select)
		{
		case '1':
			DFS_main();
			break;
		}
}