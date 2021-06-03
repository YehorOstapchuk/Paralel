// RabinKarp.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int hashF(char word[], int n)
{
    int modulo = pow(2, 31);
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
      //  cout << word[n - i - 1] << "\n";
        sum += ((int)abs((((int)word[n - i - 1]) * pow(10, i)))) % modulo;
    }
    return sum;
}

int main()
{
    ifstream file; // создаем объект класса ifstream
    string path;
    double starttime, endtime;
    cout << "Enter the txt path\n";
    cin >> path;
    file.open(path); // открываем файл
    if (!file)
    {
        cout << "File is not open\n";
        return -1;
    }
    else
    {
        cout << "Enter the word\n";
        string word;
        cin >> word;
        starttime = clock();
        int length = word.length();
        file.seekg(0, ios_base::end);
        int fileLength = file.tellg();
        int end = fileLength - length;
        char* char_array = new char[length + 1];
        strcpy_s(char_array, length+1, word.c_str());
        int wordHash = hashF(char_array, length);
        bool flagFound = false;
        int found = 0;
        for (int i = 0; i <= end; i++)
        {
            char* buffer = new char[length + 1];
            file.seekg(i);
            file.get(buffer, (length + 1));
            int bufferHash = hashF(buffer, length);
            delete[] buffer;
            if (bufferHash == wordHash) { cout << "The word is found on position " << i << "\n"; flagFound = true; found++; }
        }
       if(!flagFound) cout << "The word isn't found";
       endtime = clock();
       cout << "Word happens " << found << "\n";
       cout << "Time: " << (endtime - starttime)/CLOCKS_PER_SEC;
        return 1;
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
