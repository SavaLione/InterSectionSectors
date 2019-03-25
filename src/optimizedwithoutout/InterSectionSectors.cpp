/*
	Оптимизированный код прогрыммы InterSectionSectors
	
	Во многих местах заменили std::cout и std::endl на printf
	Вместо листа теперь вектор
*/

/* Вывод данных */
#define DATA_OUTPUT 0

/* Вывод данных о возможности использования OpenMP */
#define PARALLEL 1

/*
	Таймер работы программы
	Работает только под GNU
	Препроцессорная директива
*/
#ifdef __GNUC__
#define TIME_TEST 1
#endif

#ifdef __MINGW32__
#define TIME_TEST 1
#endif

/*
	Если таймер работы программы включен, подключаем библиотеку
*/
#if TIME_TEST
#include <chrono>
#endif

/*
	Подключение библиотек и заголовочных файлов
		stdio.h			- Ввод вывод
		time.h			- Подключение библиотеки для работы с временем. Нужно для генерации зерна
		ReadFile.h		- Заголовочный файл с функцией чтения и обработки данных из файла
		Sector.h		- Заголовочный файл с структурами и функциями для работы программы
		rand_sse.h		- Заголовочный файл генератора случайных чисел на SSE
*/
#include <stdio.h>
#include <time.h>

#include "ReadFile.h"
#include "Sector.h"
#include "rand_sse.h"

using namespace std;

/*
	Точка входа в программу
	Возвращаем 0, если программа успешно выполнилась
*/
int main()
{

#if PARALLEL
	/*
		Выводим текст в консоль каждым потоком
		Нужно для проверки количества задействованных потоков
	*/
	printf("Cores: ");
	#pragma omp parallel
	{
		printf("[CORE] ");
	}
	printf("\n");

	/*
		Вывод данных о возможности использования OpenMP 
	*/
	#ifdef _OPENMP
		printf("Compiled by an OpenMP-compliant implementation.\n");
	#endif
#endif

#if TIME_TEST
	/*
		Таймер
		Создаём 2 переменные
			start	- текущее время
			end		- время работы программы
	*/
	std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
#endif

	/*
		Задаём зерно для генератора случайных чисел
	*/
	srand_sse(time(NULL));

    int count_set = 0;
    int count_intersection = 0;
	Point temp_point;
#if DATA_OUTPUT
	double radius = 0;
#endif

	vector<vector<Sector>> data;
	data = ReadDataFromFile((char*)"data.test");

	int i_size = 0;
	for(auto it = data.begin(); it != data.end(); ++it)
		++i_size;

	
	// #pragma omp parallel for
	for(int i = 0; i < i_size; ++i)
    {
#if DATA_OUTPUT
		printf("Number set == %i\n", count_set);
        PrintSetSectors(&data[i]);
#endif
        // temp_point = CheckIntersectionSetOfSectors(&(*it));
		temp_point = CheckIntersectionSetOfSectors(&data[i]);

        if (temp_point.x == 0 && temp_point.y == 0)
        {
#if DATA_OUTPUT
			printf("Intesection of Sectors Not Found!\n");
#endif
        }
        else
        {
#if DATA_OUTPUT
			radius = 0;
            Point center_circle = CreateCircleFromArea(&temp_point, &data[i], &radius);
			printf("Center Circle -- (%lf ; %lf ),    Radius = %lf\n", center_circle.x, center_circle.y, radius);
#endif
            count_intersection++;
        }
#if DATA_OUTPUT
        printf("\n\n");
#endif

		count_set++;
    }
    printf("\n\nCount of Intersection === %i", count_intersection);

#if TIME_TEST
	end = std::chrono::system_clock::now();
    int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds> (end-start).count();
	printf("\n\n\n\nTIME\t%i\n\n", elapsed_seconds);
#endif
	return 0;
}