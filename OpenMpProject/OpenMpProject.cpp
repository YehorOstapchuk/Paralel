#include <conio.h>
#include <time.h>
#include <iostream>
#include<fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
using namespace std;

int hashF(char word[], int n)
{
    int modulo = pow(2, 31);
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += ((int)abs((((int)word[n - i - 1]) * pow(10, i)))) % modulo;
    }
    return sum;
}

int main(int argc, char* argv[])
{
    const int N = 4;
    int size, res;
    string path = "Text.txt";
    int wordHash, length;
    double startwtime = 0.0, endwtime;


    ifstream file;
    file.open(path);
    if (!file)
    {
        cout << "File is not open\n";
        return -1;
    }


        cout << "Enter the word\n";
        string word;
        cin >> word;
        startwtime = omp_get_wtime();
        length = word.length();
        char* char_array = new char[length + 1];
        strcpy_s(char_array, length + 1, word.c_str());
        wordHash = hashF(char_array, length);


    file.seekg(0, ios_base::end);
    omp_set_num_threads(N);
    int fileLength = file.tellg();
    int end = fileLength - length;
    int found = 0;
    #pragma omp parallel
    {
        ifstream tempFile;
        tempFile.open(path);
        tempFile.seekg(0, ios_base::end);
        for (int i = omp_get_thread_num(); i <= end; i+=N)
        {
            char* buffer = new char[length + 1]; 
            tempFile.seekg(i);
            tempFile.get(buffer, (length + 1));
            int bufferHash = hashF(buffer, length);
            delete[] buffer;
            if (bufferHash == wordHash) { cout << omp_get_thread_num() << "The word is found on position " << i << "\n"; 
            #pragma omp critical
            {
                found += 1;
            }
          }
        }
    }
    

    endwtime = omp_get_wtime();

    cout << "The word happens " << found << "\n";
    cout << "Wall clock time " << (endwtime - startwtime);
    return 0;
}