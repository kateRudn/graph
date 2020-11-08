#include "pch.h"
#include <iostream>
#include <queue> 
#include <stack> 
#include <vector>
using namespace std;
class Graph
{
public:
	int num_vertex;
	int orgraph;
	int num_edge;
	int** adj_matrix = 0;
	int** inc_matrix;
	int** adj_list;
	int** degree;
	int** ex;
	int rad;
	int diam;
	int gr_flag = 1;
	vector<int>ver;

	int degree_vertex(int vertex);
	int ex_vertex(int vertex);

	void print(int row_column[], int** matrix);
	void print_list();
	void print_degree();
	void print_pendant_vertex();
	void print_isolated_vertex();
	void print_stok_istok();

	void create_adj_matrix(int num);
	void create_adj_list(int num);

	void delete_adj_matrix(int num);
	void delete_adj_list(int num);

	void create_inc_matrix(int num_v, int num_r);
	void delete_inc_matrix(int num);

	void create_dop();

	void create_degree(int vertex);
	void delete_degree();

	void create_ex();
	void delete_ex();

	void delete_1();
	void delete_2();

	void create_write_1();
	void create_write_2();

	void create_union_matrix(Graph gr_2);
	void create_soed_matrix(Graph gr_2);
	void my_delete();
	void create_mult_matrix(Graph gr_2);

	void Dejkstra(int vertex_1,int vertex_2);
	void Floid(int vertex_1, int vertex_2);
	void for_Floid(int** P, int v1, int v2);
	int sezrch(int** matrix, int vertex);
	void BFS(int vertex);
	void DFS(int vertex);
	void build_min_ostov(int vertex);

	int search_location(int vertex, int** matrix);
	int search_edge(int vertex_1, int vertex_2);

	void create_matrix_from_file(char file_name[], int** matrix, bool list);

	void write_adj_list(int vertex);
	void write_adj_matrix();
	void write_inc_matrix();
	void write_adj_list_from();
	int num_of_rib();
	void write_degree(int vertex);
	void power_sequence();
	int write_dist(int vertex, int dst_vertex, int param);
	void write_ex();
	void rad_diam();

	void add_vertex(int vertex);
	void add_edge(int vertex_1, int vertex_2);
	void delete_vertex(int vertex);
	void delete_edge(int edge);
	void dublicat_vertex(int vertex);
	void mn_vertex(int vertex);
	void identification_vertex(int vertex_1, int vertex_2);
	void rib_undercutting(int edge);
};
void Graph::for_Floid(int **P,int v1, int v2)
{
	if (v1 == P[v1][v2]) { return; }
	//cout << v1 << " " << P[v1][v2] << " " << v2 << endl;
	ver.push_back(P[v1][v2]);
	for_Floid(P, v1, P[v1][v2]);
	for_Floid(P, P[v1][v2], v2);
}
void Graph::Floid(int vertex_1, int vertex_2)
{
	int** D = new int* [num_vertex + 1];
	int** P = new int* [num_vertex + 1];
	for (int i = 0; i < num_vertex + 1; i++)
	{
		D[i] = new int[num_vertex + 1];
		P[i] = new int[num_vertex + 1];
	}
	for (int i = 0; i < num_vertex + 1; i++)
	{
		memcpy(D[i], adj_matrix[i], sizeof(int) * (num_vertex + 1));
		P[0][i] = i;
		P[i][0] = i;
	}
	for (int i = 1; i < num_vertex + 1; i++)
	{
		for (int j = 1; j < num_vertex + 1; j++)
		{
			P[i][j] = 0;
			if (D[i][j] != 1000&& D[i][j]!=0)
			{
				P[i][j] = i;
			}
		}
	}
	for (int k = 1; k < num_vertex + 1; k++)
	{
		for (int i = 1; i < num_vertex + 1; i++)
		{
			for (int j = 1; j < num_vertex + 1; j++)
			{
				if ((D[i][j] > D[i][k] + D[k][j])&&D[i][k]!=1000&& D[k][j] != 1000)
				{
					D[i][j] = D[i][k] + D[k][j];
					P[i][j] = k;
				}
			}
		}
	}
	cout << "Матрица длин путей между вершинами:" << endl;
	for (int i = 0; i < num_vertex + 1; i++)
	{
		for (int j = 0; j < num_vertex + 1; j++)
		{
			printf("%5d ", D[i][j]);
		}
		printf("\n");
	}
	cout << "Матрица путей:" << endl;
	for (int i = 0; i < num_vertex + 1; i++)
	{
		for (int j = 0; j < num_vertex + 1; j++)
		{
			printf("%5d ", P[i][j]);
		}
		printf("\n");
	}
	for_Floid(P, vertex_1, vertex_2);
	cout << "Путь из вершины "<<vertex_1<<" в вершину "<<vertex_2<<":" << endl;
	cout << vertex_1<<"->";
	for (int i = ver.size()-1; i>=0; i--)
	{
			cout << ver[i] <<"->";
	}
	cout << vertex_2 << endl;
	cout << "Стоимость пути: "<<D[vertex_1][vertex_2]<< endl;
	for (int i = 0; i < num_vertex+1; i++)
	{
		delete[]D[i];
		delete[]P[i];

	}
	delete[]D;
	delete[]P;
}
void Graph::Dejkstra(int vertex_1, int vertex_2)
{
	int* distance = new int[num_vertex + 1];
	bool* visited = new bool[num_vertex + 1];
	int* p = new int[num_vertex + 1];
	int flag = 1;
	int i, u;
	for (i = 0; i < num_vertex+1; i++)
	{
		distance[i] = INT_MAX;
		visited[i] = false;
		p[i] = 0;
	}
	distance[vertex_1] = 0;
	p[vertex_1] = vertex_1;
	while(flag)
	{
		int min = INT_MAX;
		for (i = 1; i < num_vertex+1; i++)
			if (!visited[i] && distance[i] <= min)
			{
				min = distance[i]; 
				u = i;
			}
		visited[u] = true;
		for (i = 1; i < num_vertex+1; i++)
			if (!visited[i] && adj_matrix[u][i] != INT_MAX && distance[u] != INT_MAX &&
				distance[u] + adj_matrix[u][i] < distance[i])
			{
				distance[i] = distance[u] + adj_matrix[u][i];
				p[i] = u;
			}
		int count = 0;
		for (i = 1; i < num_vertex+1; i++)
		{
			if (visited[i] == true) count++;
			if (count == num_vertex) { flag = 0; }
		}
	}
	cout<<"Стоимость пути из начальной вершины до остальных:\t\n";
	for (i = 1; i < num_vertex+1; i++) if (distance[i] != INT_MAX)
		cout<<vertex_1<<"->"<<i <<": "<<distance[i]<<endl;
	else cout<<vertex_1<<"->"<<i <<": "<<"маршрут не существует"<<endl;
	
	cout << "Путь из вершины " << vertex_1 << " в вершину " << vertex_2 << ":" << endl;
	i = vertex_2;
	cout << vertex_2;
	while (p[i] != i)
	{
		cout<<"->";
		cout << p[i];
		i = p[i];
	}
	cout << endl;
	cout << "Стоимость пути: " << distance[vertex_2] << endl;
	delete[]visited;
	delete[]distance;
	delete[]p;
}
void Graph::DFS(int vertex)
{
	int  h = 1, flag = 1;
	int** used = new int* [2];
	int* ver = new int[num_vertex + 1];
	for (int i = 0; i < 2; i++)
	{
		used[i] = new int[num_vertex];
	}
	for (int i = 0; i < num_vertex; i++)
	{
		used[0][i] = adj_matrix[0][i + 1];
		used[1][i] = 0;
	}
	
	stack<int> S;
loop:
	used[1][sezrch(used, vertex)] = 1;
	S.push(vertex);
	ver[h] = vertex;
	h++;
	while (!S.empty())
	{
		int u = S.top();
		S.pop();
		int j = 1;
		int s = search_location(u, adj_list);
		while (adj_list[s][j] != 0) { j++; }
		{
			for (int i = 1; i < j; i++)
			{
				int v = adj_list[s][i];
				if (!used[1][sezrch(used, v)])
				{
					used[1][sezrch(used, v)] = 1;
					S.push(v);
					ver[h] = v; h++;
				}
			}
		}
	}

	for (int i = 0; i < num_vertex; i++)
	{
		if (used[1][i]==0)
		{
			vertex=used[0][i];
			goto loop;
		}
	}
	for (int i = 0; i < 2; i++)
	{
		delete[]used[i];
	}
	delete[]used;
	for (int i = 1; i < num_vertex+1; i++) { cout << ver[i]<<" "; }
	cout << endl;
	delete[]ver;
}
int Graph::sezrch(int **matrix,int vertex)
{
	for (int i = 0; i < num_vertex; i++)
	{
		if (matrix[0][i]==vertex)
		{
			return i;
		}
	}
}
void Graph::BFS(int vertex)
{
	int ** used = new int* [2];
	for (int i = 0; i < 2; i++)
	{
		used[i] = new int[num_vertex];
	}
	for (int i = 0; i < num_vertex; i++)
	{
		used[0][i] = adj_matrix[0][i + 1];
		used[1][i] = 0;
	}
	used[1][sezrch(used, vertex)] = 1;
	queue<int> q;
	q.push(vertex);
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		int j = 1;
		int s = search_location(u, adj_list);
		while (adj_list[s][j] != 0) { j++; }
		for (int i = 1; i < j; i++)
		{
			int v = adj_list[s][i];
			if (!used[1][sezrch(used, v)])
			{
				cout << "{" << u  << " " << v  << "}" << endl;
				used[1][sezrch(used, v)] = 1;
				q.push(v);
			}
		}

	}
	for (int i = 0; i < 2; i++)
	{
		delete[]used[i];
	}
	delete[]used;
}
void Graph::build_min_ostov(int vertex)
{
	int flag = 1;
	int weight = 0;
	int* used = new int[num_vertex + 1];
	int** edge = new int* [2];
	for (int i = 0; i < 2; i++)
	{
		edge[i] = new int[num_vertex+1];
	}
	for (int i = 0; i < num_vertex+1; i++)
	{
		edge[0][i] = -1;
		edge[1][i] = INT_MAX;
		used[i] = 0;
	}
	edge[1][vertex] = 0;
	cout << "Ребра остова:" << endl;
	while (flag)
	{
		int v = -1;
		for (int i = 1; i < num_vertex + 1; i++)
		{
			if (!used[i] && (v == -1 || edge[1][i] < edge[1][v]))
				v = i;
		}
		used[v] = true;
		for (int i = 1; i < num_vertex + 1; i++)
			if (adj_matrix[v][i] < edge[1][i])
			{
				edge[1][i] = adj_matrix[v][i];
				edge[0][i] = v;
			}
		if (edge[0][v] != -1)
		{
			cout << v << "-" << edge[0][v]<<" вес: "<< edge[1][v]<< endl;
			weight += edge[1][v];
		}
		int count = 0;
		for (int i = 1; i < num_vertex + 1; i++)
		{
			if (used[i] == 1)
			{
				count++;
			}
		}
		if (count == num_vertex) { flag = 0; }
	}
	cout << "Вес минимального остова: " << weight << endl;
	for (int i = 0; i < 2; i++)
	{
		delete[]edge[i];
	}
	delete[]edge;
	delete[]used;
}
void Graph::create_soed_matrix(Graph gr_2)
{
	int* tmp = new int[num_vertex + 1];
	memcpy(tmp, adj_matrix[0], sizeof(int) * (num_vertex + 1));
	int* tmp_2 = new int[gr_2.num_vertex + 1];
	memcpy(tmp_2, gr_2.adj_matrix[0], sizeof(int) * (gr_2.num_vertex + 1));
	int num = num_vertex;
	int num_2 = gr_2.num_vertex;
	create_union_matrix(gr_2);
	delete_2();
	for (int i = 1; i < num + 1; i++)
	{
		for (int j = 1; j < num_2 + 1; j++)
		{
			add_edge(tmp[i], tmp_2[j]);
		}
	}
	create_write_2();
	delete[]tmp;
	delete[]tmp_2;
}
void Graph::create_union_matrix(Graph gr_2)
{
	delete_1();
	int num = num_vertex;
	int num_2 = gr_2.num_vertex;
	int* tmp = new int[num_vertex + 1];
	memcpy(tmp, adj_matrix[0], sizeof(int) * (num_vertex + 1));
	for (int i = 1; i < num_2 + 1; i++)//second
	{
		int count = 0;
		for (int j = 0; j < num + 1; j++)
		{
			if (tmp[j] != gr_2.adj_matrix[i][0])
			{
				count++;
			}
		}
		if (count == num + 1)
		{
			add_vertex(gr_2.adj_matrix[i][0]);
		}
	}

	for (int i = 1; i < gr_2.num_vertex + 1; i++)
	{
		for (int j = 1; j < gr_2.num_vertex + 1; j++)
		{
			if (gr_2.adj_matrix[i][j] == 1)
			{
				int s1 = search_location(gr_2.adj_matrix[i][0], adj_matrix);
				int s2 = search_location(gr_2.adj_matrix[j][0], adj_matrix);
				adj_matrix[s1][s2] = 1;
				adj_matrix[s2][s1] = 1;
			}
			else if (gr_2.adj_matrix[i][j] == 2)
			{
				int s1 = search_location(gr_2.adj_matrix[i][0], adj_matrix);
				int s2 = search_location(gr_2.adj_matrix[j][0], adj_matrix);
				adj_matrix[s1][s2] = 2;
				adj_matrix[s2][s1] = 2;
			}
		}
	}
	create_write_1();
	delete[]tmp;

}
void Graph::identification_vertex(int vertex_1, int vertex_2)
{
	int v1 = search_location(vertex_1, adj_matrix);
	int v2 = search_location(vertex_2, adj_matrix);
	for (int i = 1; i < num_vertex + 1; i++)
	{
		if (adj_matrix[i][v1] == 1 && adj_matrix[i][0] != vertex_2)
		{
			adj_matrix[i][v2] = 1;
			adj_matrix[v2][i] = 1;
		}
		else if (adj_matrix[i][v1] == 2 && adj_matrix[i][0] != vertex_1 && adj_matrix[i][0] != vertex_2)
		{
			adj_matrix[i][v2] = 2;
			adj_matrix[v2][i] = 2;
		}
		else if (adj_matrix[i][v1] == 1 && adj_matrix[i][0] == vertex_2)
		{
			adj_matrix[i][v2] = 2;
		}
		else if (adj_matrix[i][v1] == 2 && adj_matrix[i][0] == vertex_1)
		{
			adj_matrix[i][v2] = 2;
		}
	}
	delete_vertex(vertex_1);
}
void Graph::rib_undercutting(int edge)
{
	int cur_ed;
	int v1, v2;
	int flag = 0;
	for (int i = 1; i < num_vertex + 1; i++)
	{
		if (inc_matrix[0][i] == edge) { cur_ed = i; }
	}
	for (int i = 1; i < num_vertex + 1; i++)
	{
		if (inc_matrix[i][cur_ed] == 1 && flag == 0) { v1 = inc_matrix[i][0]; flag = 1; }
		else if (inc_matrix[i][cur_ed] == 1 && flag == 1) { v2 = inc_matrix[i][0]; flag = 1; }
		else if (inc_matrix[i][cur_ed] == -1) { v2 = inc_matrix[i][0]; }
		else if (inc_matrix[i][cur_ed] == 2) { v1 = inc_matrix[i][0]; v2 = inc_matrix[i][0]; }
	}
	delete_edge(edge);
	int new_vertex = inc_matrix[num_vertex][0] + 1;
	int** tmp = new int* [num_vertex + 1];
	for (int i = 0; i < num_vertex + 1; i++)
	{
		tmp[i] = new int[num_edge + 1];
	}
	for (int i = 0; i < num_vertex + 1; i++)
	{
		memcpy(tmp[i], inc_matrix[i], sizeof(int) * (num_edge + 1));
	}
	delete_inc_matrix(num_vertex + 1);
	num_vertex++;
	create_inc_matrix(num_vertex + 1, num_edge + 1);
	for (int i = 0; i < num_vertex; i++)
	{
		memcpy(inc_matrix[i], tmp[i], sizeof(int) * (num_edge + 1));
	}
	add_edge(v1, new_vertex);
	add_edge(new_vertex, v2);
}
void Graph::mn_vertex(int vertex)
{
	dublicat_vertex(vertex);
	adj_matrix[num_vertex][search_location(vertex, adj_matrix)] = 1;
	adj_matrix[search_location(vertex, adj_matrix)][num_vertex] = 1;
}
void Graph::dublicat_vertex(int vertex)
{
	int v = search_location(vertex, adj_matrix);
	add_vertex(adj_matrix[0][num_vertex] + 1);
	for (int i = 1; i < num_vertex + 1; i++)
	{
		adj_matrix[num_vertex][i] = adj_matrix[v][i];
		adj_matrix[i][num_vertex] = adj_matrix[i][v];
	}
}
void Graph::add_edge(int vertex_1, int vertex_2)
{
	int** tmp = new int* [num_vertex + 1];
	for (int i = 0; i < num_vertex + 1; i++)
	{
		tmp[i] = new int[num_edge + 1];
	}
	for (int i = 0; i < num_vertex + 1; i++)
	{
		memcpy(tmp[i], inc_matrix[i], sizeof(int) * (num_edge + 1));
	}
	delete_inc_matrix(num_vertex + 1);
	num_edge++;
	create_inc_matrix(num_vertex + 1, num_edge + 1);
	for (int i = 0; i < num_vertex + 1; i++)
	{
		memcpy(inc_matrix[i], tmp[i], sizeof(int) * (num_edge));
	}
	inc_matrix[0][num_edge] = inc_matrix[0][num_edge - 1] + 1;
	int search_1 = search_location(vertex_1, inc_matrix);
	int search_2 = search_location(vertex_2, inc_matrix);
	if (orgraph == 1 && search_1 != search_2)
	{
		inc_matrix[search_1][num_edge] = 1;
		inc_matrix[search_2][num_edge] = 1;
	}
	else if (orgraph == 1 && search_1 == search_2)
	{
		inc_matrix[search_1][num_edge] = 2;
	}
	else if (orgraph == 2 && search_1 != search_2)
	{
		inc_matrix[search_1][num_edge] = 1;
		inc_matrix[search_2][num_edge] = -1;
	}
	else if (orgraph == 2 && search_1 == search_2)
	{
		inc_matrix[search_1][num_edge] = 2;
	}
	delete[]tmp;
}
void Graph::delete_edge(int edge)
{
	int** tmp = new int* [num_vertex + 1];
	for (int i = 0; i < num_vertex + 1; i++)
	{
		tmp[i] = new int[num_edge];
	}
	int j = 0, t = 0;
	for (int i = 0; i < num_vertex + 1; i++)
	{
		for (int k = 0; k < num_edge + 1; k++)
		{
			if (inc_matrix[0][k] != edge)
			{
				tmp[j][t] = inc_matrix[i][k];
				t++;
				if (t == num_edge) { t = 0; j++; }
			}
		}
	}
	delete_inc_matrix(num_vertex + 1);
	num_edge--;
	create_inc_matrix(num_vertex + 1, num_edge + 1);
	for (int i = 1; i < num_vertex + 1; i++)
	{
		memcpy(inc_matrix[i], tmp[i], sizeof(int) * (num_edge + 1));
	}
	delete[]tmp;
}
void Graph::delete_vertex(int vertex)
{
	int** tmp = new int* [num_vertex];
	for (int i = 0; i < num_vertex; i++)
	{
		tmp[i] = new int[num_vertex];
	}
	int j = 0, t = 0;
	for (int i = 0; i < num_vertex + 1; i++)
	{
		for (int k = 0; k < num_vertex + 1; k++)
		{
			if (adj_matrix[0][k] != vertex && adj_matrix[i][0] != vertex)
			{
				tmp[j][t] = adj_matrix[i][k];
				t++;
				if (t == num_vertex) { t = 0; j++; }
			}
		}
	}
	delete_adj_matrix(num_vertex + 1);
	num_vertex--;
	create_adj_matrix(num_vertex + 1);
	for (int i = 0; i < num_vertex + 1; i++)
	{
		memcpy(adj_matrix[i], tmp[i], sizeof(int) * (num_vertex + 1));
	}
	delete[]tmp;
}
void Graph::add_vertex(int vertex)
{
	int** tmp = new int* [num_vertex + 1];
	for (int i = 0; i < num_vertex + 1; i++)
	{
		tmp[i] = new int[num_vertex + 1];
	}
	for (int i = 0; i < num_vertex + 1; i++)
	{
		memcpy(tmp[i], adj_matrix[i], sizeof(int) * (num_vertex + 1));
	}
	delete_adj_matrix(num_vertex + 1);
	num_vertex++;
	create_adj_matrix(num_vertex + 1);
	for (int i = 0; i < num_vertex; i++)
	{
		memcpy(adj_matrix[i], tmp[i], sizeof(int) * (num_vertex));
	}
	adj_matrix[num_vertex][0] = vertex;
	adj_matrix[0][num_vertex] = vertex;
	delete[]tmp;
}
void Graph::rad_diam()
{
	int** tmp = new int* [2];
	for (int i = 0; i < 2; i++)
	{
		tmp[i] = new int[num_vertex];
	}
	for (int i = 0; i < num_vertex; i++)
	{
		tmp[0][i] = ex[0][i];
		tmp[1][i] = ex[1][i];
	}
	for (int i = 0; i <= num_vertex - 2; i++)
	{
		for (int j = num_vertex - 2; j >= i; j--)
		{
			if (tmp[1][j] > tmp[1][j + 1])
			{
				swap(tmp[1][j], tmp[1][j + 1]);
				swap(tmp[0][j], tmp[0][j + 1]);
			}
		}
	}
	cout << "Радиус: " << tmp[1][0] << endl;
	cout << "Центральные вершины: ";
	for (int i = 0; i < num_vertex; i++)
	{
		if (tmp[1][i] == tmp[1][0])
		{
			cout << tmp[0][i] << " ";
		}
	}
	cout << endl;
	cout << "Диаметр: " << tmp[1][num_vertex - 1] << endl;
	cout << "Перефирийные вершины: ";
	for (int i = 0; i < num_vertex; i++)
	{
		if (tmp[1][i] == tmp[1][num_vertex - 1])
		{
			cout << tmp[0][i] << " ";
		}
	}
	cout << endl;
	for (int i = 0; i < 2; i++)
	{
		delete[]tmp[i];
	}
	delete[]tmp;
}
void Graph::write_adj_list_from()
{
	for (int i = 0; i < num_vertex + 1; i++)
	{
		for (int j = 1; j < num_vertex + 1; j++)
		{
			if (adj_list[i][j] != 0)
			{
				if (adj_list[i][j] == adj_list[i][0]) { adj_matrix[adj_list[i][0]][adj_list[i][0]] = 2; }
				else { adj_matrix[adj_list[i][0]][adj_list[i][j]] = 1; }
			}
		}
	}
}
void Graph::write_adj_matrix()
{
	for (int i = 1; i < num_vertex + 1; i++)
	{
		adj_matrix[i][0] = inc_matrix[i][0];
		adj_matrix[0][i] = inc_matrix[i][0];
	}
	for (int i = 1; i < num_vertex + 1; i++)
	{
		for (int j = 1; j < num_edge + 1; j++)
		{
			if (inc_matrix[i][j] == 1 && orgraph == 1)
			{
				for (int y = i + 1; y < num_vertex + 1; y++)
				{
					if (inc_matrix[y][j] == 1)
					{
						int search_1 = search_location(inc_matrix[i][0], adj_matrix);
						int search_2 = search_location(inc_matrix[y][0], adj_matrix);
						adj_matrix[search_1][search_2] = 1;
						adj_matrix[search_2][search_1] = 1;
					}
				}

			}
			else if (inc_matrix[i][j] == 2 && orgraph == 1)
			{
				int flag = 1;
				for (int y = i + 1; y < num_vertex + 1; y++)
				{
					if (inc_matrix[y][j] == 2)
					{
						flag = 0;
						int search_1 = search_location(inc_matrix[i][0], adj_matrix);
						int search_2 = search_location(inc_matrix[y][0], adj_matrix);
						adj_matrix[search_1][search_2] = 2;
						adj_matrix[search_2][search_1] = 2;
					}
				}
				if (flag) {
					int search_1 = search_location(inc_matrix[i][0], adj_matrix);
					adj_matrix[search_1][search_1] = 2;
				}
			}
			else if (inc_matrix[i][j] == 1 && orgraph == 2)
			{
				for (int y = i + 1; y < num_vertex + 1; y++)
				{
					if (inc_matrix[y][j] == -1)
					{
						int search_1 = search_location(inc_matrix[i][0], adj_matrix);
						int search_2 = search_location(inc_matrix[y][0], adj_matrix);
						adj_matrix[search_1][search_2] = 1;
						//adj_matrix[y][i] = -1;
					}
				}
			}
			else if (inc_matrix[i][j] == -1 && orgraph == 2)
			{
				for (int y = i + 1; y < num_vertex + 1; y++)
				{
					if (inc_matrix[y][j] == 1)
					{
						//adj_matrix[i][y] = -1;
						int search_1 = search_location(inc_matrix[i][0], adj_matrix);
						int search_2 = search_location(inc_matrix[y][0], adj_matrix);
						adj_matrix[search_2][search_1] = 1;
					}
				}
			}
			else if (inc_matrix[i][j] == 2 && orgraph == 2)
			{
				int search_1 = search_location(inc_matrix[i][0], adj_matrix);
				adj_matrix[search_1][search_1] = 2;
			}
		}
	}

	int check;
	for (int i = 1; i < num_edge + 1; i++)
	{
		int v1, v2;
		check = 0;
		int flag = 0;
		for (int k = i + 1; k < num_edge + 1; k++)
		{
			for (int j = 1; j < num_vertex + 1; j++)
			{
				if (inc_matrix[j][i] == inc_matrix[j][k])
				{
					check++;
					if (inc_matrix[j][i] == 1 && orgraph == 1)
					{
						if (flag) { v2 = inc_matrix[j][0]; }
						else
						{
							flag = 1; v1 = inc_matrix[j][0];
						}
					}
					else if (inc_matrix[j][i] == 1 && orgraph == 2)
					{
						v1 = inc_matrix[j][0];
					}
					else if (inc_matrix[j][i] == -1 && orgraph == 2)
					{
						v2 = inc_matrix[j][0];
					}
				}
			}
			if (check == num_vertex)
			{
				int search_1 = search_location(v1, adj_matrix);
				int search_2 = search_location(v2, adj_matrix);
				adj_matrix[search_1][search_2] = 2;
				adj_matrix[search_2][search_1] = 2;
			}
			check = 0;
		}
	}


}
void Graph::write_ex()
{
	for (int i = 0; i < num_vertex; i++)
	{
		ex[0][i] = adj_matrix[i + 1][0];
		ex[1][i] = write_dist(i, 0, 2);
	}
}
int Graph::write_dist(int vertex, int dst_vertex, int param)//из вершины до остальных
{
	int res;
	int* p = new int[num_vertex];
	int* used = new int[num_vertex];
	int* dist = new int[num_vertex];
	for (int i = 0; i < num_vertex; i++)used[i] = 0;
	for (int i = 0; i < num_vertex; i++)dist[i] = -1;
	used[vertex] = 1;
	p[vertex] = vertex;
	dist[vertex] = 0;
	queue<int> q;
	q.push(vertex);
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		int j = 0;
		int s = search_location(u + 1, adj_list);
		while (adj_list[s][j] != 0) { j++; }
		for (int i = 1; i < j; i++)
		{
			int v = adj_list[s][i] - 1;
			if (!used[v])
			{
				used[v] = 1;
				dist[v] = dist[u] + 1;
				p[v] = u;
				q.push(v);
			}
		}
	}
	for (int i = 0; i < num_vertex; i++)
	{
		if (dist[i] < 0)
		{
			dist[i] = INT_MAX;
		}
	}
	if (param == 1)
	{
		res = dist[dst_vertex];
	}
	else if (param == 2)
	{
		res = dist[0];
		for (int i = 0; i < num_vertex; i++)
		{
			if (dist[i] > res) { res = dist[i]; }
		}
	}
	delete[]used;
	delete[]dist;
	delete[]p;
	return res;
}
int Graph::search_edge(int vertex_1, int vertex_2)
{
	int edge = -1;
	int v1 = search_location(vertex_1, inc_matrix);
	int v2 = search_location(vertex_2, inc_matrix);
	for (int j = 1; j < num_edge + 1; j++)
	{
		if (inc_matrix[v1][j] == 1 && inc_matrix[v2][j] == 1 && orgraph == 1)
		{
			return inc_matrix[0][j];
		}
		else if (inc_matrix[v2][j] == 2 && (orgraph == 1 || orgraph == 2))
		{
			return inc_matrix[0][j];
		}
		else if (inc_matrix[v1][j] == 1 && inc_matrix[v2][j] == -1 && orgraph == 2)
		{
			return inc_matrix[0][j];
		}
	}

	return -1;
}
int Graph::search_location(int vertex, int** matrix)
{
	for (int i = 0; i < num_vertex + 1; i++)
	{
		if (matrix[i][0] == vertex)
		{
			return i;
		}
	}
	return -1;
}
void Graph::write_inc_matrix()
{
	for (int i = 1; i < num_vertex + 1; i++)
	{
		inc_matrix[i][0] = adj_matrix[i][0];
	}
	int count = 1;
	for (int i = 1; i < num_vertex + 1; i++)
	{
		for (int j = 1; j < num_vertex + 1; j++)
		{
			if (j >= i && orgraph == 1)
			{
				if (adj_matrix[i][j] == 1)
				{
					int search_1 = search_location(adj_matrix[i][0], inc_matrix);
					inc_matrix[search_1][count] = 1;
					int search_2 = search_location(adj_matrix[0][j], inc_matrix);
					inc_matrix[search_2][count] = 1;
					count++;
				}
				else if (adj_matrix[i][j] == 2 && i != j)
				{
					int search_1 = search_location(adj_matrix[i][0], inc_matrix);
					inc_matrix[search_1][count] = 1;
					int search_2 = search_location(adj_matrix[0][j], inc_matrix);
					inc_matrix[search_2][count] = 1;
					count++;
					search_1 = search_location(adj_matrix[i][0], inc_matrix);
					inc_matrix[search_1][count] = 1;
					search_2 = search_location(adj_matrix[0][j], inc_matrix);
					inc_matrix[search_2][count] = 1;
					count++;
				}
				else if (adj_matrix[i][j] == 2 && i == j)
				{
					int search_1 = search_location(adj_matrix[i][0], inc_matrix);
					inc_matrix[search_1][count] = 2;
					count++;
				}
			}
			else if (/*j >= i &&*/ orgraph == 2)
			{
				if (adj_matrix[i][j] == 1 && i != j)
				{
					int search_1 = search_location(adj_matrix[i][0], inc_matrix);
					inc_matrix[search_1][count] = 1;
					int search_2 = search_location(adj_matrix[0][j], inc_matrix);
					inc_matrix[search_2][count] = -1;
					count++;
				}
				if (adj_matrix[i][j] == 1 && i == j)
				{
					int search_1 = search_location(adj_matrix[i][0], inc_matrix);
					inc_matrix[search_1][count] = 2;
					count++;
				}
				/*else if (adj_matrix[i][j] == -1)
				{
					inc_matrix[i][count] = -1;
					inc_matrix[j][count] = 1;
					count++;
				}*/
				else if (adj_matrix[i][j] == 2 && i != j)
				{
					int search_1 = search_location(adj_matrix[i][0], inc_matrix);
					inc_matrix[search_1][count] = 1;
					int search_2 = search_location(adj_matrix[0][j], inc_matrix);
					inc_matrix[search_2][count] = -1;
					count++;
					search_1 = search_location(adj_matrix[i][0], inc_matrix);
					inc_matrix[search_1][count] = 1;
					search_2 = search_location(adj_matrix[0][j], inc_matrix);
					inc_matrix[search_2][count] = -1;
					count++;
				}
				else if (adj_matrix[i][j] == 2 && i == j)
				{
					int search_1 = search_location(adj_matrix[i][0], inc_matrix);
					inc_matrix[search_1][count] = 2;
					count++;
				}

			}
		}
	}
}
int Graph::degree_vertex(int vertex)
{
	for (int i = 0; i < num_vertex; i++)
	{
		if (degree[0][i] == vertex)
		{
			return degree[1][i];
		}
	}
}
int Graph::ex_vertex(int vertex)
{
	for (int i = 0; i < num_vertex; i++)
	{
		if (ex[0][i] == vertex)
		{
			return ex[1][i];
		}
	}
}
void Graph::power_sequence()
{
	int** degree_seq = new int* [3];
	for (int i = 0; i < 3; i++)
	{
		degree_seq[i] = new int[num_vertex];
	}
	for (int i = 0; i < num_vertex; i++)
	{
		degree_seq[0][i] = degree[0][i];
		degree_seq[1][i] = degree[1][i];
		degree_seq[2][i] = degree[2][i];
	}
	for (int i = 0; i <= num_vertex - 2; i++)
	{
		for (int j = num_vertex - 2; j >= i; j--)
		{
			if (degree_seq[1][j] > degree_seq[1][j + 1])
			{
				swap(degree_seq[1][j], degree_seq[1][j + 1]);
				swap(degree_seq[0][j], degree_seq[0][j + 1]);
				swap(degree_seq[2][j], degree_seq[2][j + 1]);
			}
		}
	}
	int u;
	if (orgraph == 1) { u = 2; }
	else { u = 3; }
	cout << "Степенная последовательность:" << endl;
	for (int i = 0; i < u; i++)
	{
		for (int j = 0; j < num_vertex; j++)
		{
			printf("%2d ", degree_seq[u][j]);
		}
		printf("\n");
	}
	delete[]degree_seq;
}
void Graph::write_degree(int vertex)
{
	for (int i = 0; i < vertex; i++)
	{
		degree[0][i] = adj_matrix[0][i + 1];
		degree[1][i] = 0;
		degree[2][i] = 0;
	}
	for (int i = 1; i < vertex + 1; i++)
	{
		for (int j = 1; j < vertex + 1; j++)
		{
			if (orgraph == 2&& adj_matrix[i][j]!=0)
			{
				degree[1][i - 1] += 1;
				degree[2][j - 1] -= 1;
			}
			else
			{
				degree[1][i - 1] += adj_matrix[i][j];
			}
		}
	}
}
void Graph::create_ex()
{
	ex = new int* [2];
	for (int i = 0; i < 2; i++)
	{
		ex[i] = new int[num_vertex];
	}
	for (int i = 0; i < num_vertex; i++)
	{
		ex[0][i] = adj_matrix[0][i + 1];
	}
}
void Graph::delete_ex()
{
	for (int i = 0; i < 2; i++)
	{
		delete[]ex[i];
	}
	delete[]ex;
}
void Graph::create_dop()
{
	for (int i = 1; i < num_vertex + 1; i++)
	{
		for (int j = 1; j < num_vertex + 1; j++)
		{
			if (adj_matrix[i][j] == 0 && i != j)
			{
				adj_matrix[i][j] = 1;
			}
			else if (adj_matrix[i][j] == 1 || adj_matrix[i][j] == 2 || i == j)
			{
				adj_matrix[i][j] = 0;
			}
		}
	}
	delete_1();
	create_write_1();
}
void Graph::create_degree(int vertex)
{
	degree = new int* [3];
	for (int i = 0; i < 3; i++)
	{
		degree[i] = new int[vertex];
	}
	for (int i = 0; i < vertex; i++)
	{
		degree[0][i] = i + 1;
	}
}
void Graph::delete_degree()
{
	for (int i = 0; i < 3; i++)
	{
		delete[]degree[i];
	}
	delete[]degree;
}
int Graph::num_of_rib()
{
	int sum = 0;
	for (int i = 1; i < num_vertex + 1; i++)
	{
		for (int j = 1; j < num_vertex + 1; j++)
		{
			if (orgraph == 2 && adj_matrix[i][j] == 2)
			{
				sum++;
			}
			else
			{
				sum += adj_matrix[i][j];
			}
		}
	}
	if (sum % 2 == 0 && orgraph == 1) { num_edge = sum / 2; return sum / 2; }
	else if (orgraph == 2) { return sum; }
	else { return -1; }
}
void Graph::write_adj_list(int vertex)
{
	for (int i = 1; i < num_vertex + 1; i++)
	{
		adj_list[i - 1][0] = adj_matrix[i][0];
	}
	int count = 1;
	for (int i = 1; i < vertex; i++)
	{
		for (int j = 1; j < vertex; j++)
		{
			if (adj_matrix[i][j] != 0)
			{
				int search = search_location(adj_matrix[i][0], adj_list);
				adj_list[search][count] = adj_matrix[0][j];
				count++;
			}
		}
		count = 1;
	}
}
void Graph::print(int row_column[], int** matrix)
{
	FILE* r = fopen("graph.txt", "w");

	for (int i = 0; i < row_column[0]; i++)
	{
		for (int j = 0; j < row_column[1]; j++)
		{
			printf("%3d ", matrix[i][j]);
			fprintf(r, "%d ", matrix[i][j]);
		}
		printf("\n");
		fprintf(r, "\n");
	}
	fclose(r);
}
void Graph::print_list()
{
	for (int i = 0; i < num_vertex; i++)
	{
		int j = 0;
		cout << "{";
		while (adj_list[i][j] != 0)
		{
			cout << adj_list[i][j];
			if (adj_list[i][j + 1] != 0)
			{
				cout << " ";
			}
			j++;
		}
		cout << "}";
	}
	cout << endl;

}
void Graph::create_adj_matrix(int num)
{
	adj_matrix = new int* [num];
	for (int i = 0; i < num; i++)
	{
		adj_matrix[i] = new int[num];
	}
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			if (j != 0)
			{
				adj_matrix[0][j] = j;
			}
			adj_matrix[i][j] = 0;
		}
	}
	for (int i = 1; i < num; i++)adj_matrix[i][0] = i;
	/*for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			cout<<adj_matrix[i][j]<< " ";
		}
		cout << endl;
	}*/

}
void Graph::create_adj_list(int num)
{
	adj_list = new int* [num];
	for (int i = 0; i < num; i++)
	{
		adj_list[i] = new int[num];
	}
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			adj_list[i][j] = 0;
		}
	}
	for (int i = 0; i < num; i++)adj_list[i][0] = i + 1;
}
void Graph::create_inc_matrix(int num_v, int num_r)
{
	inc_matrix = new int* [num_v];
	for (int i = 0; i < num_v; i++)
	{
		inc_matrix[i] = new int[num_r];
	}
	for (int i = 0; i < num_v; i++)
	{
		for (int j = 0; j < num_r; j++)
		{
			inc_matrix[i][j] = 0;
			if (j != 0)
			{
				inc_matrix[0][j] = j;
			}
		}
	}
	for (int i = 1; i < num_v; i++)inc_matrix[i][0] = i;
}
void Graph::delete_adj_matrix(int num)
{
	for (int i = 0; i < num; i++)
	{
		delete[]adj_matrix[i];
	}
	delete[]adj_matrix;
}
void Graph::delete_adj_list(int num)
{
	for (int i = 0; i < num; i++)
	{
		delete[]adj_list[i];
	}
	delete[]adj_list;
}
void Graph::delete_inc_matrix(int num)
{
	for (int i = 0; i < num; i++)
	{
		delete[]inc_matrix[i];
	}
	delete[]inc_matrix;
}
void Graph::my_delete()
{
	delete_degree();
	delete_adj_matrix(num_vertex + 1);
	delete_adj_list(num_vertex + 1);
	delete_inc_matrix(num_vertex + 1);
	delete_ex();
}
void Graph::create_mult_matrix(Graph gr_2)
{
	int N1 = num_vertex;
	int N2 = gr_2.num_vertex;
	cout << N1 << N2 << endl;
	int news = N1 * N2;
	int** c = new int* [news];    // массив указателей
	for (int i = 0; i < news; i++) {
		c[i] = new int[news];     // инициализация указателей
	}
	for (int i = 0; i < news; i++) {
		for (int j = 0; j < news; j++) {
			c[i][j] = 0;
		}
	}
	for (int h = 0; h < N2; h++)
	{
		for (int k = 0; k < N2; k++)
		{
			for (int i = 0; i < N1; i++)
			{
				for (int j = 0; j < N1; j++)
				{
					if (i == j && gr_2.adj_matrix[h + 1][k + 1] == 1)
					{
						c[i + h * N1][k * N1 + j] = 1;
					}
				}
			}
		}
	}
	//N2 штук g1
	for (int k = 0; k < N2; k++)
	{
		for (int i = 1; i < N1 + 1; i++)
		{
			for (int j = 1; j < N1 + 1; j++)
			{
				c[k * N1 + i - 1][k * N1 + j - 1] = adj_matrix[i][j];
			}
		}
	}
	delete_1();
	delete_adj_matrix(num_vertex + 1);
	create_adj_matrix(news + 1);
	num_vertex = news;
	for (int i = 1; i < num_vertex + 1; i++)
	{
		for (int j = 1; j < num_vertex + 1; j++)
		{
			adj_matrix[i][j] = c[i - 1][j - 1];
		}
	}
	create_write_1();
	for (int i = 0; i < news; i++) {
		delete[]c[i];
	}
	delete[]c;
	int row_cl[2];
	row_cl[0] = num_vertex + 1;
	row_cl[1] = num_vertex + 1;
	print(row_cl, adj_matrix);
}
void Graph::delete_1()
{
	delete_degree();
	delete_adj_list(num_vertex + 1);
	delete_inc_matrix(num_vertex + 1);
	delete_ex();
}
void Graph::create_write_1()
{
	create_degree(num_vertex);
	create_adj_list(num_vertex + 1);
	if (num_of_rib() > 0)
	{
		num_edge = num_of_rib();
		create_inc_matrix(num_vertex + 1, num_edge + 1);
	}
	else { cout << "Ошибка: такого графа не может быть." << endl; return; }
	create_ex();
	/////////////////////
	write_adj_list(num_vertex + 1);
	write_inc_matrix();
	write_degree(num_vertex);
}
void Graph::delete_2()
{
	delete_degree();
	delete_adj_list(num_vertex + 1);
	delete_adj_matrix(num_vertex + 1);
	delete_ex();
}
void Graph::create_write_2()
{
	create_degree(num_vertex);
	create_adj_list(num_vertex + 1);
	create_adj_matrix(num_vertex + 1);
	create_ex();
	/////////////////////
	write_adj_matrix();
	write_adj_list(num_vertex + 1);
	write_degree(num_vertex);
}
void Graph::create_matrix_from_file(char file_name[], int** matrix, bool list)
{
	FILE* x;
	int a = 1, b = 1;
	char c;
	x = fopen(file_name, "r");
	if (x == NULL)
	{
		cout << "Ошибка: файл не найден." << endl;
	}
	else
	{
		cout << "Файл открыт для чтения." << endl;
	}
	if (list)
	{
		while (1)
		{
			if (feof(x) != 0) { break; }
			c = fgetc(x);
			if (feof(x) != 0) { break; }
			if (c == '{')
			{
				fscanf(x, "%d", &a);
				while (c != '}')
				{
					c = fgetc(x);
					if (c == ' ')
					{
						fscanf(x, "%d", &matrix[a - 1][b]);
						b++;
					}
				}
				b = 1;
			}
		}
	}
	else
	{
		while (1)
		{
			if (feof(x) != 0) { break; }
			fscanf(x, "%d", &matrix[a][b]);
			b++;
			c = fgetc(x);
			if (feof(x) != 0) { break; }
			if (c == '\n')
			{
				a++; b = 1;
			}
		}
	}
	fclose(x);
}
void Graph::print_degree()
{
	for (int i = 0; i < orgraph + 1; i++)
	{
		for (int j = 0; j < num_vertex; j++)
		{
			printf("%2d ", degree[i][j]);
		}
		cout << endl;
	}
}
void Graph::print_pendant_vertex()
{
	int flag = 1;
	cout << "Висячие вершины:" << endl;
	for (int i = 0; i < num_vertex; i++)
	{
		if ((degree[1][i] == 1 && orgraph == 1) || (degree[2][i] == -1 && degree[1][i] == 0 && orgraph == 2))
		{
			flag = 0;
			cout << (degree[0][i]) << " ";
		}
	}
	if (flag) { cout << "Нет"; }
	cout << endl;
}
void Graph::print_isolated_vertex()
{
	int flag = 1;
	cout << "Изолированные вершины:" << endl;
	for (int i = 0; i < num_vertex; i++)
	{
		if ((degree[1][i] == 0 && orgraph == 1) || (degree[1][i] == 0 && degree[2][i] == 0 && orgraph == 2))
		{
			flag = 0;
			cout << (degree[0][i]) << " ";
		}

	}
	if (flag) { cout << "Нет"; }
	cout << endl;
}
void Graph::print_stok_istok()
{
	int flag_1 = 1, flag_2 = 1;
	cout << "Сток: " << endl;
	for (int i = 0; i < num_vertex; i++)
	{
		if (degree[1][i] == 0 && degree[2][i] != 0)
		{
			flag_1 = 0;
			cout << degree[0][i] << " ";
		}
	}
	if (flag_1) { cout << "Нет"; }
	cout << endl;
	cout << "Исток: " << endl;
	for (int i = 0; i < num_vertex; i++)
	{
		if (degree[2][i] == 0 && degree[1][i] != 0)
		{
			flag_2 = 0;
			cout << degree[0][i] << " ";
		}
	}
	if (flag_2) { cout << "Нет"; }
	cout << endl;
}
int read_file(int row_column[], char file_name[], bool list)
{
	FILE* x;
	int i = 0;
	x = fopen(file_name, "r");
	if (x == NULL)
	{
		cout << "Ошибка: файл не найден." << endl;
	}
	else
	{
		cout << "Файл открыт для чтения." << endl;
	}
	if (list)
	{
		while (!feof(x))
		{
			char h = fgetc(x);
			if (feof(x) != 0) { break; }
			if (h == '}')
			{
				i++;
			}
		}
		row_column[0] = i;
		row_column[1] = i;
	}
	else
	{
		while (!feof(x))
		{
			char h = fgetc(x);
			if (feof(x) != 0) { break; }
			if (h == ' ' || h == '\n')
			{
				i++;
			}
			if (h == '\n')
			{
				row_column[0]++;
				row_column[1] = i;
				i = 0;
			}
		}
	}
	fclose(x);
	return *row_column;
}
int main()
{
	setlocale(LC_ALL, "Russian");
	Graph my_graph[6];
	while (1)
	{
		int choice, view=1, ch;
		char option[] = "Выберете операцию:\n1 - Информация о графе\n2 - Степень вершины\n3 - Матрица смежности\n4 - Матрица инцидентности\n5 - Список смежности\n6 - Расстояние между вершинами\n7 - Эксцентриситет вершины\n8 - Радиус/диаметр, центр/перефирия\n9 - Добавление вершины\n10 - Удаление вершины\n11 - Добавление ребра\n12 - Удаление ребра\n13 - Дублирование вершины\n14 - Размножение вершины\n15 - Подразбиение ребра\n16 - Отождествление вершины\n17 - Стягивание графа\n18 - Дополнение графа\n19 - Объединение графов\n20 - Соединение графов\n21 - Произведение графов\n22 - Обход графа в ширину\n23 - Обход графа в глубину\n24 - Построение остова минимального веса методом Прима\n25 - Построение пути минимального веса алгоритмом Дейкстры\n26 - Построение пути минимального веса алгоритмом Флойда\n";
		cout << "Выберете граф/орграф:\n1 - граф G1\n2 - граф G2\n3 - орграф G3\n4 - граф G4\n5 - граф G5 (2)\n6 - граф G6 (с весами ребер)"<< endl;
		cin >> choice;
		if (choice == 0)break;
		if (my_graph[choice - 1].gr_flag&&choice!=6)
		{
			cout << "Выберите представление графа:\n1 - Матрица смежности\n2 - Матрица инцидентности\n3 - Список смежности" << endl;
			cin >> view;
		}
	    if (my_graph[choice - 1].gr_flag == 1&&view==1||choice==6)
		{
			int row_column[2] = { 1,0 };
			if(choice==1){ read_file(row_column, (char*)"graph1.txt", 0); my_graph[choice - 1].orgraph = 1;}
			else if(choice==2){ read_file(row_column, (char*)"graph4.txt", 0); my_graph[choice - 1].orgraph = 1;}
			else if(choice==3){ read_file(row_column, (char*)"graph7.txt", 0); my_graph[choice - 1].orgraph = 2;}
			else if (choice == 4) { read_file(row_column, (char*)"graph1.txt", 0); my_graph[choice - 1].orgraph = 1; }
			else if (choice == 5) { read_file(row_column, (char*)"graph4.txt", 0); my_graph[choice - 1].orgraph = 1; }
			else if (choice == 6) { read_file(row_column, (char*)"graph10.txt", 0); my_graph[choice - 1].orgraph = 1; }
			my_graph[choice - 1].num_vertex = row_column[0];
			my_graph[choice - 1].create_adj_matrix(my_graph[choice - 1].num_vertex + 1);
			if (choice == 1) { my_graph[choice - 1].create_matrix_from_file((char*)"graph1.txt", my_graph[choice - 1].adj_matrix, 0);  }
			else if (choice == 2) { my_graph[choice - 1].create_matrix_from_file((char*)"graph4.txt", my_graph[choice - 1].adj_matrix, 0); }
			else if (choice == 3) { my_graph[choice - 1].create_matrix_from_file((char*)"graph7.txt", my_graph[choice - 1].adj_matrix, 0); }
			else if (choice == 4) { my_graph[choice - 1].create_matrix_from_file((char*)"graph1.txt", my_graph[choice - 1].adj_matrix, 0); }
			else if (choice == 5) { my_graph[choice - 1].create_matrix_from_file((char*)"graph4.txt", my_graph[choice - 1].adj_matrix, 0); }
			else if (choice == 6) { my_graph[choice - 1].create_matrix_from_file((char*)"graph10.txt", my_graph[choice - 1].adj_matrix, 0); }
			row_column[0]++; row_column[1]++;
			cout << "Матрица смежности:" << endl;
			my_graph[choice - 1].print(row_column, my_graph[choice - 1].adj_matrix);
			if (choice!=6) my_graph[choice - 1].create_write_1();
			my_graph[choice - 1].gr_flag = 0;
		}
		else if (my_graph[choice - 1].gr_flag == 1&&view==2)
		{
			int row_column[2] = { 1,0 };
			if (choice == 1) { read_file(row_column, (char*)"graph2.txt", 0); my_graph[choice - 1].orgraph = 1; }
			else if (choice == 2) { read_file(row_column, (char*)"graph5.txt", 0); my_graph[choice - 1].orgraph = 1; }
			else if (choice == 3) { read_file(row_column, (char*)"graph8.txt", 0); my_graph[choice - 1].orgraph = 2; }
			else if (choice == 4) { read_file(row_column, (char*)"graph2.txt", 0); my_graph[choice - 1].orgraph = 1; }
			else if (choice == 5) { read_file(row_column, (char*)"graph5.txt", 0); my_graph[choice - 1].orgraph = 1; }
			my_graph[choice - 1].num_vertex = row_column[0];
			my_graph[choice - 1].num_edge = row_column[1];
			my_graph[choice - 1].create_inc_matrix(my_graph[choice - 1].num_vertex + 1, my_graph[choice - 1].num_edge + 1);
			if (choice == 1) { my_graph[choice - 1].create_matrix_from_file((char*)"graph2.txt", my_graph[choice - 1].inc_matrix, 0); }
			else if (choice == 2) { my_graph[choice - 1].create_matrix_from_file((char*)"graph5.txt", my_graph[choice - 1].inc_matrix, 0); }
			else if (choice == 3) { my_graph[choice - 1].create_matrix_from_file((char*)"graph8.txt", my_graph[choice - 1].inc_matrix, 0); }
			else if (choice == 4) { my_graph[choice - 1].create_matrix_from_file((char*)"graph2.txt", my_graph[choice - 1].inc_matrix, 0); }
			else if (choice == 5) { my_graph[choice - 1].create_matrix_from_file((char*)"graph5.txt", my_graph[choice - 1].inc_matrix, 0); }
			cout << "Матрица инцидентности:" << endl;
			row_column[0]++; row_column[1]++;
			my_graph[choice - 1].print(row_column, my_graph[choice - 1].inc_matrix);
			my_graph[choice - 1].create_write_2();
			my_graph[choice - 1].gr_flag = 0;
		}
		else if (my_graph[choice - 1].gr_flag == 1&&view==3)
		{
			int row_column[2] = { 1,0 };
			if (choice == 1) { read_file(row_column, (char*)"graph3.txt", 1); my_graph[choice - 1].orgraph = 1; }
			else if (choice == 2) { read_file(row_column, (char*)"graph6.txt", 1); my_graph[choice - 1].orgraph = 1; }
			else if (choice == 3) { read_file(row_column, (char*)"graph9.txt", 1); my_graph[choice - 1].orgraph = 2; }
			else if (choice == 4) { read_file(row_column, (char*)"graph3.txt", 1); my_graph[choice - 1].orgraph = 1; }
			else if (choice == 5) { read_file(row_column, (char*)"graph6.txt", 1); my_graph[choice - 1].orgraph = 1; }
			my_graph[choice - 1].num_vertex = row_column[0];
			my_graph[choice - 1].create_adj_list(my_graph[choice - 1].num_vertex + 1);
			if (choice == 1) { my_graph[choice - 1].create_matrix_from_file((char*)"graph3.txt", my_graph[choice - 1].adj_list, 1); }
			else if (choice == 2) { my_graph[choice - 1].create_matrix_from_file((char*)"graph6.txt", my_graph[choice - 1].adj_list, 1); }
			else if (choice == 3) { my_graph[choice - 1].create_matrix_from_file((char*)"graph9.txt", my_graph[choice - 1].adj_list, 1); }
			else if (choice == 4) { my_graph[choice - 1].create_matrix_from_file((char*)"graph3.txt", my_graph[choice - 1].adj_list, 1); }
			else if (choice == 5) { my_graph[choice - 1].create_matrix_from_file((char*)"graph6.txt", my_graph[choice - 1].adj_list, 1); }
			cout << "Список смежности:" << endl;
			my_graph[choice - 1].print_list();
			my_graph[choice - 1].create_adj_matrix(my_graph[choice - 1].num_vertex + 1);
			my_graph[choice - 1].create_degree(my_graph[choice - 1].num_vertex);
			my_graph[choice - 1].create_ex();
			my_graph[choice - 1].write_adj_list_from();
			my_graph[choice - 1].num_edge = my_graph[choice - 1].num_of_rib();
			my_graph[choice - 1].create_inc_matrix(my_graph[choice - 1].num_vertex + 1, my_graph[choice - 1].num_edge + 1);
			my_graph[choice - 1].write_inc_matrix();
			my_graph[choice - 1].write_degree(my_graph[choice - 1].num_vertex);
			my_graph[choice - 1].gr_flag = 0;
		}
		while (1)
		{
			cout << option << endl;
			cin >> ch;
			if (ch == 0) break;
			else if (ch == 1)
			{
				cout << "Количество вершин: " << my_graph[choice - 1].num_vertex << endl;
				cout << "Количество ребер: " << my_graph[choice - 1].num_edge << endl;
				cout << "Степени вершин:" << endl;
				my_graph[choice - 1].print_degree();
				my_graph[choice - 1].power_sequence();
				my_graph[choice - 1].print_isolated_vertex();
				my_graph[choice - 1].print_pendant_vertex();

				if (my_graph[choice - 1].orgraph == 2)
				{
					my_graph[choice - 1].print_stok_istok();
				}
			}
			else if (ch == 2)
			{
			next:
				int vertex;
				cout << "Введите номер вершины:" << endl;
				cin >> vertex;
				if (my_graph[choice - 1].search_location(vertex, my_graph[choice - 1].adj_matrix) <= 0)
				{
					goto next;
				}
				cout << my_graph[choice - 1].degree_vertex(vertex) << endl;
			}
			else if (ch == 3)
			{
				int row_column[2];
				row_column[0] = my_graph[choice - 1].num_vertex + 1; row_column[1] = my_graph[choice - 1].num_vertex + 1;
				cout << "Матрица смежности:" << endl;
				my_graph[choice - 1].print(row_column, my_graph[choice - 1].adj_matrix);
			}
			else if (ch == 4)
			{
				cout << "Матрица инцидентности:" << endl;
				int row_column[2]; row_column[0] = my_graph[choice - 1].num_vertex + 1; row_column[1] = my_graph[choice - 1].num_edge + 1;
				my_graph[choice - 1].print(row_column, my_graph[choice - 1].inc_matrix);
			}
			else if (ch == 5)
			{
				cout << "Список смежности:" << endl;
				my_graph[choice - 1].print_list();
			}

			else if (ch == 6)
			{
			p1:
				int v1;
				cout << "Введите номер первой вершины:" << endl;
				cin >> v1;
				if (my_graph[choice - 1].search_location(v1, my_graph[choice - 1].adj_matrix) <= 0) { goto p1; }
			p2:
				int v2;
				cout << "Введите номер второй вершины:" << endl;
				cin >> v2;
				if (my_graph[choice - 1].search_location(v2, my_graph[choice - 1].adj_matrix) <= 0) { goto p2; }
				cout << "Расстояние: " << my_graph[choice - 1].write_dist(v1 - 1, v2 - 1, 1) << endl;
			}
			else if (ch == 7)
			{
			p:
				int v;
				cout << "Введите номер вершины:" << endl;
				cin >> v;
				if (my_graph[choice - 1].search_location(v, my_graph[choice - 1].adj_matrix) <= 0) { goto p; }
				my_graph[choice - 1].write_ex();
				cout << "Эксцетриситет вершины: " << my_graph[choice - 1].ex_vertex(v) << endl;
			}
			else if (ch == 8)
			{
				my_graph[choice - 1].write_ex();
				my_graph[choice - 1].rad_diam();
			}
			else if (ch == 9)
			{
			vert_0:
				int v;
				cout << "Введите номер вершины:" << endl;
				cin >> v;
				if (my_graph[choice - 1].search_location(v, my_graph[choice - 1].adj_matrix) >= 0) { goto vert_0; }
				my_graph[choice - 1].delete_1();
				/////////////////////////////////
				my_graph[choice - 1].add_vertex(v);
				int row_cl[2]; row_cl[0] = my_graph[choice - 1].num_vertex + 1; row_cl[1] = my_graph[choice - 1].num_vertex + 1;
				cout << "Матрица смежности:" << endl;
				my_graph[choice - 1].print(row_cl, my_graph[choice - 1].adj_matrix);
				/////////////////////////////////
				my_graph[choice - 1].create_write_1();
			}
			else if (ch == 10)
			{
			vert_1:
				int v;
				cout << "Введите номер вершины:" << endl;
				cin >> v;
				if (my_graph[choice - 1].search_location(v, my_graph[choice - 1].adj_matrix) <= 0) { goto vert_1; }
				my_graph[choice - 1].delete_1();
				/////////////////
				my_graph[choice - 1].delete_vertex(v);
				int row_cl[2]; row_cl[0] = my_graph[choice - 1].num_vertex; row_cl[1] = my_graph[choice - 1].num_vertex;
				row_cl[0]++; row_cl[1]++;
				cout << "Матрица смежности:" << endl;
				my_graph[choice - 1].print(row_cl, my_graph[choice - 1].adj_matrix);
				///////////////////////
				my_graph[choice - 1].create_write_1();
			}
			else if (ch == 11)
			{
			vert_2:
				int v1, v2;
				cout << "Введите номер первой вершины:" << endl;
				cin >> v1;
				if (my_graph[choice - 1].search_location(v1, my_graph[choice - 1].adj_matrix) <= 0) { goto vert_2; }
			vert_3:
				cout << "Введите номер второй вершины:" << endl;
				cin >> v2;
				if (my_graph[choice - 1].search_location(v2, my_graph[choice - 1].adj_matrix) <= 0) { goto vert_3; }
				/////////////////
				my_graph[choice - 1].delete_2();
				/////////////////
				my_graph[choice - 1].add_edge(v1, v2);
				int row_cl[2]; row_cl[0] = my_graph[choice - 1].num_vertex; row_cl[1] = my_graph[choice - 1].num_edge;
				row_cl[0]++; row_cl[1]++;
				cout << "Матрица инцидентности:" << endl;
				my_graph[choice - 1].print(row_cl, my_graph[choice - 1].inc_matrix);
				///////////////////////
				my_graph[choice - 1].create_write_2();
			}
			else if (ch == 12)
			{
			vert_4:
				int v1, v2;
				cout << "Введите номер первой вершины:" << endl;
				cin >> v1;
				if (my_graph[choice - 1].search_location(v1, my_graph[choice - 1].adj_matrix) <= 0) { goto vert_4; }
			vert_5:
				cout << "Введите номер второй вершины:" << endl;
				cin >> v2;
				if (my_graph[choice - 1].search_location(v2, my_graph[choice - 1].adj_matrix) <= 0) { goto vert_5; }
				if (my_graph[choice - 1].search_edge(v1, v2) <= 0)
				{
					cout << "Такого ребра не существует." << endl;
					goto vert_4;
				}
				/////////////////////
				my_graph[choice - 1].delete_2();
				////////////////////
				my_graph[choice - 1].delete_edge(my_graph[choice - 1].search_edge(v1, v2));
				int row_cl[2]; row_cl[0] = my_graph[choice - 1].num_vertex; row_cl[1] = my_graph[choice - 1].num_edge;
				row_cl[0]++; row_cl[1]++;
				cout << "Матрица инцидентности:" << endl;
				my_graph[choice - 1].print(row_cl, my_graph[choice - 1].inc_matrix);
				///////////////////////
				my_graph[choice - 1].create_write_2();
			}
			else if (ch == 13)
			{
			vert_6:
				int v;
				cout << "Введите номер вершины:" << endl;
				cin >> v;
				if (my_graph[choice - 1].search_location(v, my_graph[choice - 1].adj_matrix) <= 0) { goto vert_6; }
				my_graph[choice - 1].delete_1();
				/////////////////
				my_graph[choice - 1].dublicat_vertex(v);
				int row_cl[2]; row_cl[0] = my_graph[choice - 1].num_vertex; row_cl[1] = my_graph[choice - 1].num_vertex;
				row_cl[0]++; row_cl[1]++;
				cout << "Матрица смежности:" << endl;
				my_graph[choice - 1].print(row_cl, my_graph[choice - 1].adj_matrix);
				///////////////////////
				my_graph[choice - 1].create_write_1();

			}
			else if (ch == 14)
			{
			vert_7:
				int v;
				cout << "Введите номер вершины:" << endl;
				cin >> v;
				if (my_graph[choice - 1].search_location(v, my_graph[choice - 1].adj_matrix) <= 0) { goto vert_7; }
				/////////////////
				my_graph[choice - 1].delete_1();
				/////////////////
				my_graph[choice - 1].mn_vertex(v);
				int row_cl[2]; row_cl[0] = my_graph[choice - 1].num_vertex; row_cl[1] = my_graph[choice - 1].num_vertex;
				row_cl[0]++; row_cl[1]++;
				cout << "Матрица смежности:" << endl;
				my_graph[choice - 1].print(row_cl, my_graph[choice - 1].adj_matrix);
				///////////////////////
				my_graph[choice - 1].create_write_1();
			}
			else if (ch == 15)
			{
			vert_8:
				int v1, v2;
				cout << "Введите номер первой вершины:" << endl;
				cin >> v1;
				if (my_graph[choice - 1].search_location(v1, my_graph[choice - 1].adj_matrix) <= 0) { goto vert_8; }
			vert_9:
				cout << "Введите номер второй вершины:" << endl;
				cin >> v2;
				if (my_graph[choice - 1].search_location(v2, my_graph[choice - 1].adj_matrix) <= 0) { goto vert_9; }
				if (my_graph[choice - 1].search_edge(v1, v2) <= 0)
				{
					cout << "Такого ребра не существует." << endl;
					goto vert_8;
				}
				/////////////////////
				my_graph[choice - 1].delete_2();
				////////////////////
				my_graph[choice - 1].rib_undercutting(my_graph[choice - 1].search_edge(v1, v2));
				int row_cl[2]; row_cl[0] = my_graph[choice - 1].num_vertex; row_cl[1] = my_graph[choice - 1].num_edge;
				row_cl[0]++; row_cl[1]++;
				cout << "Матрица инцидентности:" << endl;
				my_graph[choice - 1].print(row_cl, my_graph[choice - 1].inc_matrix);
				///////////////////////
				my_graph[choice - 1].create_write_2();
			}
			else if (ch == 16)
			{
			vert_10:
				int v1, v2;
				cout << "Введите номер первой вершины:" << endl;
				cin >> v1;
				if (my_graph[choice - 1].search_location(v1, my_graph[choice - 1].adj_matrix) <= 0) { goto vert_10; }
			vert_11:
				cout << "Введите номер второй вершины:" << endl;
				cin >> v2;
				if (my_graph[choice - 1].search_location(v2, my_graph[choice - 1].adj_matrix) <= 0) { goto vert_11; }
				/////////////////
				my_graph[choice - 1].delete_1();
				///////////////////
				my_graph[choice - 1].identification_vertex(v1, v2);
				int row_cl[2]; row_cl[0] = my_graph[choice - 1].num_vertex; row_cl[1] = my_graph[choice - 1].num_vertex;
				row_cl[0]++; row_cl[1]++;
				cout << "Матрица смежности:" << endl;
				my_graph[choice - 1].print(row_cl, my_graph[choice - 1].adj_matrix);
				///////////////////////
				my_graph[choice - 1].create_write_1();
			}
			else if (ch == 17)
			{
			again:
				int num_v;
				int* arr;
				cout << "Введите количество вершин:" << endl;
				cin >> num_v;
				if (num_v >= my_graph[choice - 1].num_vertex) { goto again; }
				arr = new int[num_v];
				cout << "Введите номера вершин:" << endl;
				for (int i = 0; i < num_v; i++)
				{
					cin >> arr[i];
				}
				//////////////////
				my_graph[choice - 1].delete_1();
				///////////////////
				for (int i = 0; i < num_v - 1; i++)
				{
					my_graph[choice - 1].identification_vertex(arr[i], arr[i + 1]);
				}
				int row_cl[2]; row_cl[0] = my_graph[choice - 1].num_vertex; row_cl[1] = my_graph[choice - 1].num_vertex;
				row_cl[0]++; row_cl[1]++;
				cout << "Матрица смежности:" << endl;
				my_graph[choice - 1].print(row_cl, my_graph[choice - 1].adj_matrix);
				///////////////////////
				my_graph[choice - 1].create_write_1();

			}
			else if (ch == 18)
			{
				my_graph[choice - 1].create_dop();
				int row_cl[2]; row_cl[0] = my_graph[choice - 1].num_vertex + 1; row_cl[1] = my_graph[choice - 1].num_vertex + 1;
				cout << "Дополнение:" << endl;
				my_graph[choice - 1].print(row_cl, my_graph[choice - 1].adj_matrix);
			}
			else if (ch == 19)
			{
			ag:
				int num_gr;
				cout << "Введите номер графа:" << endl;
				cin >> num_gr;
				if (my_graph[num_gr - 1].gr_flag) {
					cout << "Ошибка: такого графа не существует." << endl; goto ag;
				}
				my_graph[choice - 1].create_union_matrix(my_graph[num_gr - 1]);
				int row_cl[2];
				row_cl[0] = my_graph[choice - 1].num_vertex + 1; row_cl[1] = my_graph[choice - 1].num_vertex + 1;
				cout << "Матрица смежности:" << endl;
				my_graph[choice - 1].print(row_cl, my_graph[choice - 1].adj_matrix);
			}
			else if (ch == 20)
			{
			agr:
				int num_gr;
				cout << "Введите номер графа:" << endl;
				cin >> num_gr;
				if (my_graph[num_gr - 1].gr_flag) {
					cout << "Ошибка: такого графа не существует." << endl; goto agr;
				}
				my_graph[choice - 1].create_soed_matrix(my_graph[num_gr - 1]);
				int row_cl[2];
				row_cl[0] = my_graph[choice - 1].num_vertex + 1; row_cl[1] = my_graph[choice - 1].num_vertex + 1;
				cout << "Матрица смежности:" << endl;
				my_graph[choice - 1].print(row_cl, my_graph[choice - 1].adj_matrix);
			}
			else if (ch == 21)
			{
			agr_1:
				int num_gr;
				cout << "Введите номер графа:" << endl;
				cin >> num_gr;
				if (my_graph[num_gr - 1].gr_flag) {
					cout << "Ошибка: такого графа не существует." << endl; goto agr_1;
				}
				my_graph[choice - 1].create_mult_matrix(my_graph[num_gr - 1]);

			}
			else if (ch == 22)
			{
			     int vertex;
			     cout << "Введите номер начальной вершины: " << endl;
			     cin >> vertex;
				 my_graph[choice - 1].BFS(vertex);
            }
			else if (ch == 23)
			{
			     int vertex;
			     cout << "Введите номер начальной вершины: " << endl;
				 cin >> vertex;
			     my_graph[choice - 1].DFS(vertex);
			}
			else if (ch == 24)
			{
			for (int i = 1; i < my_graph[choice-1].num_vertex + 1; i++)
			{
				for (int j = 1; j < my_graph[choice - 1].num_vertex + 1; j++)
				{
					if (my_graph[choice - 1].adj_matrix[i][j] == 0)
					{
						my_graph[choice - 1].adj_matrix[i][j] = INT_MAX;

					}
				}
			}
			     int vertex;
			     cout << "Введите номер начальной вершины: " << endl;
			     cin >> vertex;
			     my_graph[choice - 1].build_min_ostov(vertex);
            }
			else if (ch == 25)
			{
			for (int i = 1; i < my_graph[choice - 1].num_vertex + 1; i++)
			{
				for (int j = 1; j < my_graph[choice - 1].num_vertex + 1; j++)
				{
					if (my_graph[choice - 1].adj_matrix[i][j] == -1)
					{
						my_graph[choice - 1].adj_matrix[i][j] = INT_MAX;

					}
				}
			}
			int vertex1, vertex2;
			cout << "Введите номер начальной вершины: " << endl;
			cin >> vertex1;
			cout << "Введите номер конечной вершины: " << endl;
			cin >> vertex2;
			my_graph[choice - 1].Dejkstra(vertex1, vertex2);
            }
			else if (ch == 26)
			{
			for (int i = 1; i < my_graph[choice - 1].num_vertex + 1; i++)
			{
				for (int j = 1; j < my_graph[choice - 1].num_vertex + 1; j++)
				{
					if (my_graph[choice - 1].adj_matrix[i][j] == -3)
					{
						my_graph[choice - 1].adj_matrix[i][j] = 1000;

					}
				}
			}
			int vertex1, vertex2;
			cout << "Введите номер начальной вершины: " << endl;
			cin >> vertex1;
			cout << "Введите номер конечной вершины: " << endl;
			cin >> vertex2;
			my_graph[choice - 1].Floid(vertex1, vertex2);
 }

		}
	}
	for (int i = 0; i < 6; i++)
	{
		if (!my_graph[i].gr_flag&&i!=5)
		{
			my_graph[i].my_delete();
		}
		else if (!my_graph[i].gr_flag && i == 5)
		{
			my_graph[i].delete_adj_matrix(my_graph[i].num_vertex + 1);
		}

	}
}


