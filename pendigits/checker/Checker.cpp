#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

const int K = 10;
const int INF = 1e9;

vector <int> clusters[K];  //Предпологаемые кластеры clusters[i][j], i - номер кластера
vector <short int> answer;  //Наши данные, answer[n] это метка вектора под номером n

int table[K][K];  // Таблица со статистикой. table[i][d] количество изображений цифры d в кластере i

string s;  // Вспомогательная строка для операций считавания


void read_output()
{
	freopen("output.txt", "r", stdin);  //Файл в котором лежат список кластеров
	
	int index_clusters = 0;

	//Читаем из файла по строкам

	while (getline(cin, s))
	{
		for (int i = 0; i < s.length();)
		{
			int var = 0;

			while(s[i] < '0' or s[i] > '9')
			    i++;

			while('0' <= s[i] and s[i] <= '9')
			    var = (var << 3) + (var << 1) + (s[i++] - '0');

			//printf("считано: %d\n", var);

			
			//while(s[index] >= 48 && s[index] <= 59)
			//{
				//number.push_back(s[index]);
				//index++;
			//}
			clusters[index_clusters].push_back(var);
		}
		index_clusters++;
	}
}


void read_marks()
{
	short int d;
	ifstream in("answers.txt");
	while (in >> d)
	{
		answer.push_back(d);
	}
	in.close();
}


void count_digits_in_clusters()
{
	//Перебираем номера векторов которые находяться в кластерах
	
	for (int index_clusters = 0; index_clusters < K; index_clusters++)
	{
		//printf("Кластер %d\n", index_clusters);
		
		for (int number = 0; number < clusters[index_clusters].size(); number++)
		{
			//printf(" - число номер %d: %d\n", number, clusters[index_clusters][number]);

			table[index_clusters][answer[clusters[index_clusters][number]]]++;
		}
	}
}


void print_statistics()
{
	for (int index_clusters = 0; index_clusters < K; index_clusters++)
	{
		
		for (int digit = 0; digit < K; digit++)
		{

			printf("%4d ", table[index_clusters][digit]);

		}
		
		printf("\n");
		
	}
}


void count_accuracy()
{
	int all = 0, good = 0;
	for(int i = 0; i < K; i++)
	{
		for(int j = 0; j < K; j++)
			all += table[i][j];
		
		good += *max_element(table[i], table[i] + K);
	}

/*	for (int i = 0; i < K; i++)
	{
		int maxx = -1;
		
		for (int j = 0; j < K; j++)
		{
			all += table[j][i];
			maxx = max(maxx, table[j][i]);
		}
		
		good += maxx;
	}

	double accuracy = double(good) / all;
	//printf("Аккуратность1: %lf\n", accuracy);
	
	good = 0;

	for(int i = 0; i < K; i++)
        good += *max_element(table[i], table[i] + K);*/
	
	double accuracy = double(good) / all;
	accuracy *= 100;
	printf("Аккуратность(Миша): %0.2lf%c\n", accuracy, '%');
	
}

/*void f()
{
	vector <int> list(K, 0);
	vector <int> num(K, 0);
	int ans = 0;

	for (int i = 0; i < K; i++)
		list[i] = i;

	do {
		int stat = 0;

		for (int i = 0; i < K; i++)
			stat += table[i][list[i]];

		if (ans < stat)
		{
			for (int i = 0; i < K; i++)
				num[i] = table[i][list[i]];
			ans = stat;
		}

	} while( next_permutation(list.begin(), list.end()) ); // Полный перебор

	int all = 0;

	for (int i = 0; i < K; i++)
		for (int j = 0; j < K; j++)
			all += table[i][j];

	for (int i = 0; i < K; i++)
		printf("%d\n", num[i]);

	double accuracy = (double) ans / all;
	accuracy *= 100;
	printf("Аккуратность(Перебор): %0.2lf%c\n", accuracy, '%');
}*/

void count_accuracy_assignment_hungary()
{

	for (int i = 0; i < K; i++)
		for (int j = 0; j < K; j++)
			table[i][j] *= -1;
	
	vector <int> u(K + 1, 0), v(K + 1, 0), p(K + 1, 0), way(K + 1, 0);
	
	for (int i = 1; i <= K; i++) 
	{
		p[0] = i;
		int j0 = 0;
		vector <int> minv (K + 1, INF);
		vector <char> used (K + 1, false);
	
		do {
			used[j0] = true;
			int i0 = p[j0],  delta = INF,  j1;
	
			for (int j = 1; j <= K; j++)
				if (!used[j]) 
				{
					int cur = table[i0 - 1][j - 1] - u[i0] - v[j];
	
					if (cur < minv[j])
						minv[j] = cur,  way[j] = j0;
					if (minv[j] < delta)
						delta = minv[j],  j1 = j;
				}
	
			for (int j = 0; j <= K; j++)
				if (used[j])
					u[p[j]] += delta,  v[j] -= delta;
				else
					minv[j] -= delta;
	
			j0 = j1;
	
		} while (p[j0] != 0);

		do {
			int j1 = way[j0];
			p[j0] = p[j1];
			j0 = j1;
	
		} while (j0);
	}
	
	int good = 0, all = 0;
	
	for (int i = 1; i <= K; i++)
	{
		good += table[p[i] - 1][i - 1];
	
		for (int j = 0; j < K; j++)
			all += table[i - 1][j];
	}
	
	double accuracy = double(good) / all;
	accuracy *= 100;
	printf("Аккурстность(Венгерка): %0.2lf%c\n", accuracy, '%');

	for (int i = 0; i < K; i++)
		for (int j = 0; j < K; j++)
			table[i][j] *= -1;
}


int main()
{
	read_output();
	read_marks();
	
	puts("Считывание произошло успешно");

	//for(auto a : answer)
	    //printf(" + %d\n", a);

	count_digits_in_clusters();

	puts("Подсчёт цифр произошёл успешно");

	print_statistics();

	count_accuracy();
	//f();
	count_accuracy_assignment_hungary();
	
	
}
