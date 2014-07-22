#include <stdio.h>
#include <stdlib.h>

#define N 5

typedef struct _node_
{
	int vertex;
	struct _node_ *next;
} linknode, *linklist;

void AddEdge(linknode s[], int i, int j)
{
	linklist h, p;

	h = s + i;
	while ((h->next != NULL) && (h->next->vertex < j)) h = h->next;
	p = (linklist)malloc(sizeof(linknode));
	p->vertex = j;
	p->next = h->next;
	h->next = p;

	return;
}

int FirstAdj(linknode s[], int v)
{
	return (s[v].next->vertex);
}

int NextAdj(linknode s[], int v, int u)
{
	linklist p;

	p = s[v].next;
	while (p->vertex != u) p = p->next;

	return (p->next == NULL ? -1 : p->next->vertex);
}


void Visit(linklist h)
{
	h = h->next;
	while (h != NULL)
	{
		printf("V%d ", h->vertex);
		h = h->next;
	}

	return;
}

int main()
{
	int i, j;
	linknode s[N] = {{0, NULL}};

	while ( 1 )
	{
		scanf("%d,%d", &i, &j);
		if (i == j) break;
		AddEdge(s, i, j);
		AddEdge(s, j, i);
	}

	for (i=0; i<N; i++)
	{
		printf("V%d : ", i);
		Visit(s + i);
		printf("\n");
	}

	return 0;
}
