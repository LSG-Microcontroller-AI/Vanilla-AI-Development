// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

using namespace std;

#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <stdlib.h>
#ifdef __linux__
// linux code goes here
#elif _WIN32
#include <conio.h>
#include <windows.h>
#else

#endif

#include <chrono>
#include <ctime>
#include <string>
#include <fstream>

void init();

void genera_esempi();

int getRandomNumber();

void esegui();

void apprendi();

void back_propagate();

void readData();

void writeDataOnFile();

float getRandomNumberFloat();

void lavora();

unsigned long const sample_numbers = 10000000;

const uint8_t numberOf_X = 2 + 1;
const uint8_t numberOf_H = 10 + 1;
const uint8_t numberOf_Y = 1;

float epsilon;

float err_rete;

float W1[numberOf_X][numberOf_H];
float W2[numberOf_H][numberOf_Y];

float x[50] = {};
float y[50] = {};
float h[50] = {};
float d[50] = {};

float operando1[sample_numbers]{};
float operando2[sample_numbers]{};
float risultato[sample_numbers]{};

float T(float A);

int main()
{
    /* float a = 0.00f;
     srand(time(NULL));
     a = getRandomNumberFloat();
     cout << a << "\n";
     return 0;*/

    init();

#ifdef __linux__

#elif _WIN32
    Beep(3000, 200);
#else
#endif
    char response;
#ifdef __linux__
    cout << "\nAre you sure you want clear the weights file\n";
    response = getchar();
#elif _WIN32
    cout << "\nDo you want load the weights file\n";
    response = _getch();
#else
#endif
    if (response == 'y')
    {
        cout << "\nFile loaded\n";
        readData();
    }
    else
    {
        cout << "\nFile deleted\n";
    }
    cout << "\nDo you want to start learning\n";
    response = _getch();

    if (response == 'y')
    {
        cout << "\nstart to learning......\n";

        apprendi();
       
    }

    lavora();


}

void lavora()
{
    for (int i = 0; i < 100; i++)
    {
        x[0] = (getRandomNumber() / 1000.00f);
        x[1] = (getRandomNumber() / 1000.00f);
        esegui();
        char label = ' ';
        float realResult = x[0] + x[1];
        if ((realResult - y[0]) > ((realResult / 100.00f) * 1.00f))
        {
            label = '*';
        }
        cout << x[0] * 1000 << " + " << x[1] * 1000 << " = " << y[0] * 1000 << label << "\n";
    }
}

void init()
{
    x[numberOf_X - 1] = 1.00f;
    h[numberOf_H - 1] = 1.00f;

    std::cout << "input elements:\n";
    for (int i = 0; i < (numberOf_X - 1); i++)
    {
        x[i] = 0.00f;
        cout << "x[";
        cout << i;
        cout << "]";
        cout << "=";
        cout << x[i];
        cout << "\n";
    }
    std::cout << "x[";
    cout << (int)(numberOf_X - 1);
    cout << "]";
    cout << "=";
    cout << x[numberOf_X - 1];
    cout << " - BIAS";
    cout << "\n";

    std::cout << "hidden elements:\n";
    for (int i = 0; i < (numberOf_H - 1); i++)
    {
        h[i] = 0.00f;
        cout << "h[";
        cout << i;
        cout << "]";
        cout << "=";
        cout << h[i];
        cout << "\n";
    }
    cout << "h[";
    cout << (int)(numberOf_H - 1);
    cout << "]";
    cout << "=";
    cout << h[numberOf_H - 1];
    cout << " - BIAS";
    cout << "\n";
    cout << "output elements:\n";

    for (int i = 0; i < numberOf_Y; i++)
    {
        y[i] = 0.00f;
        cout << "y[";
        cout << i;
        cout << "]";
        cout << "=";
        cout << y[i];
        cout << "\n";
    }

    for (int i = 0; i < numberOf_X; i++)
    {
        for (int k = 0; k < numberOf_H - 1; k++)
        {
            W1[i][k] = (float)((getRandomNumber() - 50.00f) / 100.00f);
            cout << "W1[" << i << "]"
                 << "[" << k << "]"
                 << " = " << W1[i][k] << "\n";
        }
    }

    for (int k = 0; k < numberOf_H; k++)
    {
        for (int j = 0; j < numberOf_Y; j++)
        {
            W2[k][j] = (float)((getRandomNumber() - 50.00f) / 100.00f);
            cout << "W2[" << k << "]"
                 << "[" << j << "]"
                 << " = " << W2[k][j] << "\n";
        }
    }
}

void genera_esempi()
{
    for (unsigned long i = 0; i < sample_numbers; i++)
    {
        operando1[i] = getRandomNumber() / 1000.00f;
        operando2[i] = getRandomNumber() / 1000.00f;
        risultato[i] = operando1[i] + operando2[i];
        //cout << operando1[i] << " + " << operando2[i] << " = " << risultato[i] << "\n";
    }
}

void esegui()
{
    float A;

    for (int k = 0; k < (numberOf_H - 1); k++)
    {
        A = 0.00f;
        for (int i = 0; i < numberOf_X; i++)
        {
            A = A + (W1[i][k] * x[i]);
        }
        h[k] = T(A);
    }

    for (int j = 0; j < numberOf_Y; j++)
    {
        A = 0.00f;
        for (int k = 0; k < numberOf_H; k++)
        {
            A = A + (W2[k][j] * h[k]);
        }
        y[j] = T(A);
    }
}

void apprendi()
{
    float err_epoca;

    float err_amm;

    int epoca = 0;

    err_amm = 0.0050f;

    epsilon = 0.7f;

    genera_esempi();

    auto start = std::chrono::system_clock::now();
    
    do
    {
        err_epoca = 0.00f;

        for (unsigned long p = 0; p < sample_numbers; p++)
        {
            x[0] = operando1[p];
            x[1] = operando2[p];
            d[0] = risultato[p];
            esegui();
            back_propagate();
            if (err_rete > err_epoca)
            {
                err_epoca = err_rete;
            }
        }
        epoca = epoca + 1;

        cout << "\nVersion: Y \n\n";

        cout << "stop when err_epoca < " << err_amm << "\n\n";

        cout << "epoca:" << epoca << " errore_epoca= " << err_epoca << " errore_rete=" << err_rete << "\n";

        writeDataOnFile();

    } while (err_epoca > err_amm);

    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;

    double sample_time = elapsed_seconds.count();

    cout << "learning time : " << (int)(sample_time / 60) << " minutes.\n";

#ifdef __linux__
    // linux code goes here
#elif _WIN32
    Beep(3000, 200);
    Beep(3000, 200);
    Beep(3000, 200);
    Beep(3000, 200);
    Beep(3000, 200);
#else
#endif

    cout << "press a key..\n\n";

#ifdef __linux__
    getchar();
#elif _WIN32
    _getch();
#else

#endif
}

void back_propagate()
{
    float err_H[50];

    float delta;

    for (int k = 0; k < numberOf_H; k++)
    {
        err_H[k] = 0.00f;
    }
    err_rete = 0.00f;
    for (int j = 0; j < numberOf_Y; j++)
    {
        if (abs(d[j] - y[j]) > err_rete)
        {
            err_rete = abs(d[j] - y[j]);
        }
        delta = (d[j] - y[j]) * y[j] * (1.00f - y[j]);
        for (int k = 0; k < numberOf_H; k++)
        {
            err_H[k] = err_H[k] + (delta * W2[k][j]);
            W2[k][j] = W2[k][j] + (epsilon * delta * h[k]);
        }
    }
    for (int k = 0; k < numberOf_H - 1; k++)
    {
        delta = err_H[k] * h[k] * (1.00f - h[k]);
        for (int i = 0; i < numberOf_X; i++)
        {
            W1[i][k] = W1[i][k] + (epsilon * delta * x[i]);
        }
    }
}

int getRandomNumber()
{
   // return (rand() % (10 - 100 + 1) + 0);
    return rand() % 60 + 10;
    // return (rand() % (0 - 49 + 1) + 0);
}

float getRandomNumberFloat()
{
    return (rand() % 1200 + 3000) / 1000.00f;
}

float T(float A)
{
    return 1.00f / (1.00f + pow(M_E, -A));
}

void readData()
{
    std::ifstream in("test3.bin", std::ios_base::binary);
    if (in.good())
    {
        for (int j = 0; j < numberOf_Y; j++)
        {
            for (int k = 0; k < numberOf_H; k++)
            {
                // cout << W2[k][j];
                in.read((char *)&W2[k][j], sizeof(float));
            }
        }

        for (int k = 0; k < numberOf_H - 1; k++)
        {
            for (int i = 0; i < numberOf_X; i++)
            {
                in.read((char *)&W1[i][k], sizeof(float));
            }
        }
    }
}

void writeDataOnFile()
{
    float f1 = 0.00f;
    try
    {
        cout << "\nWriting to file... \n\n";

        std::ofstream fw("test3.bin", std::ios_base::binary);

        if (fw.good())
        {
            for (int j = 0; j < numberOf_Y; j++)
            {
                for (int k = 0; k < numberOf_H; k++)
                {
                    fw.write((char *)&W2[k][j], sizeof(float));
                }
            }

            for (int k = 0; k < numberOf_H - 1; k++)
            {
                for (int i = 0; i < numberOf_X; i++)
                {
                    fw.write((char *)&W1[i][k], sizeof(float));
                }
            }

            fw.close();

            cout << "\nFile closed... \n\n";
        }
        else
            cout << "Problem with opening file";
    }
    catch (const char *msg)
    {
        cerr << msg << endl;
    }
}
