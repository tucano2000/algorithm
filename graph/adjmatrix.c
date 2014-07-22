#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 5
#define M 10

typedef int datatype;

typedef struct
{
	datatype data[M];
	int front, rear;
} sequeue;

sequeue *CreateEmptySequeue()
{
	sequeue *sq;

	sq = (sequeue *)malloc(sizeof(sequeue));
	sq->front = sq->rear = 0;

	return sq;
}

int EmptySequeue(sequeue *sq)
{
	return sq->front == sq->rear;
}

int FullSequeue(sequeue *sq)
{
	return ((sq->rear+1) % M == sq->front);
}

void EnQueue(sequeue *sq, datatype x)
{
	sq->rear = (sq->rear + 1) % M;
	sq->data[sq->rear] = x;

	return;
}

datatype DeQueue(sequeue *sq)
{
	sq->front = (sq->front + 1) % M;
	
	return sq->data[sq->front];
}

int FirstAdj(int matrix[][N], int v)
{
	int i;

	for (i=0; i<N; i++)
	{
		if (matrix[v][i] == 1) return i;
	}

	return -1;
}

int NextAdj(int matrix[][N], int v, int u)
{
	int i;

	for (i=u+1; i<N; i++)
	{
		if (matrix[v][i] == 1) return i;
	}

	return -1;
}

void DFS(int matrix[][N], int v, int visited[])
{
	int u;

	printf("V%d ", v);
	visited[v] = 1;
	u = FirstAdj(matrix, v);
	while (u >= 0)
	{
		if ( !visited[u] ) DFS(matrix, u, visited);
		u = NextAdj(matrix, v, u);
	}

	return;
}

void BFS(int matrix[][N], int v, int visited[])
{
	int u;
	sequeue *sq;

	sq = CreateEmptySequeue();
	printf("V%d ", v);
	visited[v] = 1;
	EnQueue(sq, v);

	while ( ! EmptySequeue(sq) )
	{
		v = DeQueue(sq);
		u = FirstAdj(matrix, v);
		while (u >= 0)
		{
			if ( !visited[u] ) 
			{
				printf("V%d ", u);
				visited[u] = 1;
				EnQueue(sq, u);
			}
			u = NextAdj(matrix, v, u);
		}
	}

	return;
}

int main()
{
	int matrix[N][N] = {{0}};
	int i, j, visited[N] = {0};

	while ( 1 )
	{
		scanf("%d,%d", &i, &j);
		if (i == j) break;
		matrix[i][j] = matrix[j][i] = 1;
	}

	for (i=0; i<N; i++)
	{
		printf("V%d : ", i);
		for (j=0; j<N; j++)
		{
			if (matrix[i][j] == 1) printf("V%d ", j);
		}
		printf("\n");
	}

	printf("DFS : ");
	DFS(matrix, 0, visited);
	printf("\n");
	
	printf("BFS : ");
	bzero(visited, sizeof(visited));
	BFS(matrix, 0, visited);
	printf("\n");

	return 0;
}
