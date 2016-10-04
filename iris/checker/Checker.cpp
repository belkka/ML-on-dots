#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

const int K = 3;

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
		for(auto t : table[i])
			all += t;
		
		good += *max_element(table[i], table[i] + K);
	}

	double accuracy = double(good) / all;
	printf("Аккуратность: %lf\n", accuracy);
	
}


int main()
{
	read_output();
	read_marks();
	
	//puts("Считывание произошло успешно");


	count_digits_in_clusters();

	//puts("Подсчёт цифр произошёл успешно");

	print_statistics();

	count_accuracy();

	
}
