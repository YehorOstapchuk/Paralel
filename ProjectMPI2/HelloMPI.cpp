#include <conio.h>
#include <time.h>
#include <mpi.h>
#include <iostream>
#include<fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
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
    int const tag1 = 13;
    int const tag2 = 17;
    int size, rank, res;
    int namelen;
    string path = "Text.txt";
    int wordHash, length;
    double startwtime = 0.0, endwtime;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(processor_name, &namelen);

    ifstream file;
    file.open(path);
    if (!file)
    {
        cout << "File is not open\n";
        return -1;
    }

    if (rank == 0)
    {
        cout << "Enter the word\n";
        string word;
        cin >> word;
        startwtime = MPI_Wtime();
        length = word.length();
        char* char_array = new char[length + 1];
        strcpy_s(char_array, length + 1, word.c_str());
        wordHash = hashF(char_array, length);
    }
    MPI_Bcast(&wordHash, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&length, 1, MPI_INT, 0, MPI_COMM_WORLD);
        file.seekg(0, ios_base::end);
        int fileLength = file.tellg();
        int end = fileLength - length;
        int found = 0;
        for (int i = rank; i <= end; i = i + size)
        {
            char* buffer = new char[length + 1];
            file.seekg(i);
            file.get(buffer, (length + 1));
            int bufferHash = hashF(buffer, length);
            delete[] buffer;
            if (bufferHash == wordHash) { cout << "The word is found on position " << i << "\n"; found++; }
        }
        
       MPI_Reduce(&found, &res, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

       if (rank == 0)
       {
           endwtime = MPI_Wtime();
           cout << "The word happens " << res << "\n";
           cout << "Wall clock time " << (endwtime - startwtime);
     }
        MPI_Finalize();
    return 0;
}