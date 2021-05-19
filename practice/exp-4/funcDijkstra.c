#include <stdbool.h>
#include <stdio.h>

#define MAX_NUM 0xffff

void dijkstra(int *graphM, int source, int *dist, int *prev, int scale);
void outputx(int *graphM, int dest, int *prev);
bool isFull(bool *set, int scale);

// int main(void)
// {
// 	int scale = 10;
// 	int source = 3;
// 	int nodesw[] = {
// 		0,		MAX_NUM,MAX_NUM,4,		1,		MAX_NUM,MAX_NUM,10,		MAX_NUM,MAX_NUM,
// 		MAX_NUM,0,		2,		MAX_NUM,MAX_NUM,1,		MAX_NUM,MAX_NUM,MAX_NUM,MAX_NUM,
// 		MAX_NUM,2,		0,		MAX_NUM,MAX_NUM,3,		MAX_NUM,MAX_NUM,MAX_NUM,MAX_NUM,
// 		4,		MAX_NUM,MAX_NUM,0,		MAX_NUM,MAX_NUM,MAX_NUM,1,		MAX_NUM,MAX_NUM,
// 		1,		MAX_NUM,MAX_NUM,MAX_NUM,0,		3,		MAX_NUM,5,		MAX_NUM,MAX_NUM,
// 		MAX_NUM,1,		3,		MAX_NUM,3,		0,		7,		MAX_NUM,1,		MAX_NUM,
// 		MAX_NUM,MAX_NUM,MAX_NUM,MAX_NUM,MAX_NUM,MAX_NUM,0,		MAX_NUM,MAX_NUM,1,
// 		10,		MAX_NUM,MAX_NUM,1,		5,		MAX_NUM,MAX_NUM,0,		9,		MAX_NUM,
// 		MAX_NUM,MAX_NUM,MAX_NUM,MAX_NUM,MAX_NUM,1,		MAX_NUM,MAX_NUM,0,		2,
// 		MAX_NUM,MAX_NUM,MAX_NUM,MAX_NUM,MAX_NUM,MAX_NUM,1,		MAX_NUM,MAX_NUM,0
// 	};
// 	int dist[scale], prev[scale];
// 	dijkstra(nodesw, source, dist, prev, scale);
// 	for (int i = 0; i < 10; i++)
// 	{
// 		printf("l(%d, %d) == %2d: ", source, i, dist[i]);
// 		outputx(nodesw, i, prev);
// 		putchar('\n');
// 	}
	
// 	return 0;
// }

int main(void)
{
	int scale, source,  numEdge, v1, v2, v3;
	printf("source = ");
	scanf("%d", &source);

	FILE *file = fopen("graphExp.txt", "r");
	fscanf(file, "%d", &scale);

	int map[scale * scale];
	for (int i = 0; i < scale * scale; i++)
	{
		map[i] =  MAX_NUM;
	}

	fscanf(file, "%d", &numEdge);

	for (int i = 0; i < numEdge; i++)
	{
		fscanf(file, "%d %d %d", &v1, &v2, &v3);
		map[v1 * scale + v2] = v3;
	}

	// for (int i = 0; i < scale; i++)
	// {
	// 	for (int j = 0; j < scale; j++)
	// 	{
	// 		printf("%d\t\t", map[i * scale + j]);
	// 	}
	// 	putchar('\n');
	// }

	int dist[scale], prev[scale];
	dijkstra(map, source, dist, prev, scale);
	for (int i = 0; i < scale; i++)
	{
		if (prev[i] != -1)
		{
			printf("l(%d, %d) == %4d: ", source, i, dist[i]);
			outputx(map, i, prev);
		}
		else printf("l(%d, %d) == Inf", source, i);
		putchar('\n');
	}

	return 0;
}

bool isFull(bool *set, int scale)
{
	for (int i = 0; i < scale; i++)
	{
		if (set[i] == false)
		{
			return false;
		}
	}
	return true;
}

void outputx(int *graphM, int dest, int *prev)
{
	if (prev[dest] != -2)
	{
		outputx(graphM, prev[dest], prev);
		printf("->");
	}
	printf("%d", dest);
	return;
}

void dijkstra(int *graphM, int source, int *dist, int *prev, int scale)
{
	int u, v, alt;
	bool visited[scale];

	for (int i = 0; i < scale; i++)
	{
		dist[i] = MAX_NUM;
		prev[i] = -1;
		visited[i] = false;
	}
	dist[source] = 0;
	prev[source] = -2;

	while (!isFull(visited, scale))
	{
		for (v = 0;; v++)
		{
			if (!visited[v])
			{
				u = v;
				break;
			}
		}
		for (; v < scale; v++)
		{
			if (visited[v])
			{
				continue;
			}
			else if (dist[v] < dist[u])
			{
				u = v;
			}
		}
		visited[u] = true;
		for (v = 0; v < scale; v++)
		{
			if (!visited[v])
			{
				alt = dist[u] + graphM[u * scale + v];
				if (alt < dist[v])
				{
					dist[v] = alt;
					prev[v] = u;
				}
			}
			
		}
	}
	return;
}
