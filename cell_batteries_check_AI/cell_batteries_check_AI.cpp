using namespace std;

#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <stdint.h>

#ifdef __linux__

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

void lavora();

int getRandomNumber();

void esegui();

void apprendi();

void back_propagate();

void read_weights_from_file();

void write_weights_on_file();

void read_data_from_CSV_file();

const uint8_t numberOf_X = 2 + 1;

const uint8_t numberOf_H = 5 + 1;

const uint8_t numberOf_Y = 6;

uint16_t const sample_numbers = 10;

float epsilon;

float err_rete;

float W1[numberOf_X][numberOf_H];

float W2[numberOf_H][numberOf_Y];

float x_input_level[50] = {};

float y_output_level[50] = {};

float h_hidden_level[50] = {};

float d_expected_output_values[50] = {};

float amp_in[sample_numbers]{};

float watts_hour[sample_numbers]{};

float b1_out[sample_numbers]{};

float b2_out[sample_numbers]{};

float b3_out[sample_numbers]{};

float b4_out[sample_numbers]{};

float b5_out[sample_numbers]{};

float b6_out[sample_numbers]{};

int battery_total_watts = 1440;

float T(float A);

int main()
{
    init();

#ifdef __linux__

#elif _WIN32
    Beep(3000, 200);
#else

#endif

    char response;

    cout << "\n Do you want load the weights file\n";

#ifdef __linux__
    response = std::cin.get();
    std::cin.ignore();
#elif _WIN32
    response = _getch();
#else

#endif

    if (response == 'y')
    {
        cout << "\n Weights loaded\n";

        read_weights_from_file();
    }
    else
    {
        cout << "\n Weights overwritten\n";
    }

    cout << "\n Do you want to start learning\n";

#ifdef __linux__
    response = std::cin.get();
    std::cin.ignore();
#elif _WIN32
    response = _getch();
#else
#endif

    if (response == 'y')
    {
        cout << "\n Start to learning......\n";

        apprendi();

    }

    lavora();
}

void lavora()
{
    x_input_level[0] = 14.82f / 1000.00f;//AMPS

    x_input_level[1] = 30.00f / 1000.00f;//WATTS

    esegui();

    cout << "\n amps : " << x_input_level[0] * 1000.00f;

    cout << "\n watts : " << x_input_level[1] * 1000.00f;

    cout << "\n batt1 : " << y_output_level[0] * 100.00f;

    cout << "\n batt2 : " << y_output_level[1] * 100.00f;

    cout << "\n batt3 : " << y_output_level[2] * 100.00f;

    cout << "\n batt4 : " << y_output_level[3] * 100.00f;

    cout << "\n batt5 : " << y_output_level[4] * 100.00f;

    cout << "\n batt6 : " << y_output_level[5] * 100.00f;
}

void init()
{
    //Set Bias
    x_input_level[numberOf_X - 1] = 1.00f;

    h_hidden_level[numberOf_H - 1] = 1.00f;

    cout << "input elements:\n";

    for (int i = 0; i < (numberOf_X - 1); i++)
    {
        x_input_level[i] = 0.00f;

        cout << "x[" << i << "]" << "=" << x_input_level[i] << "\n";
    }
    cout << "x[" << (int)(numberOf_X - 1) << "]" << "=" << x_input_level[numberOf_X - 1] << "-BIAS" << "\n";

    cout << "hidden elements:\n";

    for (int i = 0; i < (numberOf_H - 1); i++)
    {
        h_hidden_level[i] = 0.00f;

        cout << "h[" << i << "]" << "=" << h_hidden_level[i] << "\n";
    }
    cout << "h[" << (int)(numberOf_H - 1) << "]" << "=" << h_hidden_level[numberOf_H - 1] << "-BIAS" << "\n";

    cout << "output elements:\n";

    for (int i = 0; i < numberOf_Y; i++)
    {
        y_output_level[i] = 0.00f;

        cout << "y[" << i << "]=" << y_output_level[i] << "\n";
    }

    for (int i = 0; i < numberOf_X; i++)
    {
        for (int k = 0; k < numberOf_H - 1; k++)
        {
            W1[i][k] = (float)((getRandomNumber() - 50.00f) / 100.00f);

            cout << "W1[" << i << "]" << "[" << k << "]" << "=" << W1[i][k] << "\n";
        }
    }

    for (int k = 0; k < numberOf_H; k++)
    {
        for (int j = 0; j < numberOf_Y; j++)
        {
            W2[k][j] = (float)((getRandomNumber() - 50.00f) / 100.00f);

            cout << "W2[" << k << "]" << "[" << j << "]" << "=" << W2[k][j] << "\n";
        }
    }
}

//void genera_esempi_for_battManag()
//{
//    srand(time(NULL));
//
//    int index = 0;
//
//    amp_in[index] = 0.030f;
//
//    watts_hour[index] = 0.0100f;
//
//    b1_out[index] = 0.375f;
//
//    b2_out[index] = 0.379f;
//
//    b3_out[index] = 0.375f;
//
//    b4_out[index] = 0.379f;
//
//    b5_out[index] = 0.375f;
//
//    b6_out[index] = 0.379f;
//
//    index++;
//
//    amp_in[index] = 0.030f;
//
//    watts_hour[index] = 0.0200f;
//
//    b1_out[index] = 0.335f;
//
//    b2_out[index] = 0.339f;
//
//    b3_out[index] = 0.335f;
//
//    b4_out[index] = 0.339f;
//
//    b5_out[index] = 0.335f;
//
//    b6_out[index] = 0.339f;
//
//    index++;
//
//    amp_in[index] = 0.030f;
//
//    watts_hour[index] = 0.0300f;
//
//    b1_out[index] = 0.285f;
//
//    b2_out[index] = 0.289f;
//
//    b3_out[index] = 0.285f;
//
//    b4_out[index] = 0.289f;
//
//    b5_out[index] = 0.285f;
//
//    b6_out[index] = 0.289f;
//
//    index++;
//
//    amp_in[index] = 0.025f;
//
//    watts_hour[index] = 0.0500f;
//
//    b1_out[index] = 0.125f;
//
//    b2_out[index] = 0.129f;
//
//    b3_out[index] = 0.125f;
//
//    b4_out[index] = 0.129f;
//
//    b5_out[index] = 0.125f;
//
//    b6_out[index] = 0.129f;
//
//}

void esegui()
{
    float A;

    for (int k = 0; k < (numberOf_H - 1); k++)
    {
        A = 0.00f;

        for (int i = 0; i < numberOf_X; i++)
        {

            A = A + (W1[i][k] * x_input_level[i]);

        }

        h_hidden_level[k] = T(A);
    }

    for (int j = 0; j < numberOf_Y; j++)
    {
        A = 0.00f;

        for (int k = 0; k < numberOf_H; k++)
        {
            A = A + (W2[k][j] * h_hidden_level[k]);
        }

        y_output_level[j] = T(A);
    }
}

void apprendi()
{
    float err_epoca_first = 0;

    float err_epoca;

    float err_amm;

    int epoca = 0;

    err_amm = 0.001f;

    epsilon = 0.7f;

    //genera_esempi_for_battManag();

    read_data_from_CSV_file();

    auto start = std::chrono::system_clock::now();

    do
    {
        err_epoca = 0.00f;

        for (unsigned long p = 0; p < sample_numbers; p++)
        {
            x_input_level[0] = amp_in[p];

            x_input_level[1] = watts_hour[p];

            d_expected_output_values[0] = b1_out[p];

            d_expected_output_values[1] = b2_out[p];

            d_expected_output_values[2] = b3_out[p];

            d_expected_output_values[3] = b4_out[p];

            d_expected_output_values[4] = b5_out[p];

            d_expected_output_values[5] = b6_out[p];

            esegui();

            back_propagate();

            if (err_rete > err_epoca)
            {
                err_epoca = err_rete;
            }
            //			if ((err_epoca_first >= err_epoca) /*&& err_epoca_first != 0.00f*/)
            //			{
            //				cout << "\n problems \n\n";
            //				cout << "press a key..\n\n";
            //
            //#ifdef __linux__
            //				getchar();
            //#elif _WIN32
            //				_getch();
            //#else
            //
            //#endif
            //			}
            //			else
            //			{
            //				err_epoca_first = err_epoca;
            //			}
        }
        epoca = epoca + 1;

        cout << "\nVersion: Y \n\n";

        cout << "stop when err_epoca < " << err_amm << "\n\n";

        cout << "epoca:" << epoca << " errore_epoca= " << err_epoca << " errore_rete=" << err_rete << "\n";

        write_weights_on_file();

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
    response = std::cin.get();
    std::cin.ignore();
#elif _WIN32
    _getch();
#else

#endif
}

void back_propagate()
{
    float err_H[500];

    float delta;

    for (int k = 0; k < numberOf_H; k++)
    {
        err_H[k] = 0.00f;
    }
    err_rete = 0.00f;

    for (int j = 0; j < numberOf_Y; j++)
    {
        if (abs(d_expected_output_values[j] - y_output_level[j]) > err_rete)
        {
            err_rete = abs(d_expected_output_values[j] - y_output_level[j]);
        }
        delta = (d_expected_output_values[j] - y_output_level[j]) * y_output_level[j] * (1.00f - y_output_level[j]);

        for (int k = 0; k < numberOf_H; k++)
        {
            err_H[k] = err_H[k] + (delta * W2[k][j]);

            W2[k][j] = W2[k][j] + (epsilon * delta * h_hidden_level[k]);
        }
    }
    for (int k = 0; k < numberOf_H - 1; k++)
    {
        delta = err_H[k] * h_hidden_level[k] * (1.00f - h_hidden_level[k]);

        for (int i = 0; i < numberOf_X; i++)
        {
            W1[i][k] = W1[i][k] + (epsilon * delta * x_input_level[i]);
        }
    }
}

int getRandomNumber()
{
    return (rand() % (0 - 100 + 1) + 0);
    //return (rand() % 60 + 10) / 1000.00f;
    // return (rand() % (0 - 49 + 1) + 0);
}

//float getRandomNumberFloat1()
//{
//
//	//return (rand() % 1700 + 2500) / 10000.00f;
//	return (rand() % 1200 + 3000) / 10000.00f;
//}
//
//float getRandomNumberFloat2()
//{
//	//return (rand() % 1700 + 2500) / 10000.00f;
//	return (rand() % 4200 + 3000) / 10000.00f;
//}

float T(float A)
{
    return 1.00f / (1.00f + pow(M_E, -A));
}

void read_data_from_CSV_file()
{
    uint16_t samples_index = 0;

    string col = "";

    float col2 = 0.00f;

    ifstream file_in("BATT0.CSV");

    getline(file_in, col, ';');

    getline(file_in, col, ';');

    getline(file_in, col, ';');

    getline(file_in, col, ';');

    uint8_t lines_index = 1;

    while (file_in.good() && samples_index <= sample_numbers)
    {
        getline(file_in, col, ';');

        getline(file_in, col, ';');

        getline(file_in, col, ';');

        col2 = stof(col);

        switch (lines_index)
        {
        case 1:
            b1_out[samples_index] = col2 / 100.00;

            cout << "b1_out = " << col2 << "\r\n";

            break;
        case 2:
            b2_out[samples_index] = col2 / 100.00;

            cout << "b2_out = " << col2 << "\r\n";

            break;
        case 3:
            b3_out[samples_index] = col2 / 100.00;

            cout << "b3_out = " << col2 << "\r\n";

            break;
        case 4:
            b4_out[samples_index] = col2 / 100.00;

            cout << "b4_out = " << col2 << "\r\n";

            break;
        case 5:
            b5_out[samples_index] = col2 / 100.00;

            cout << "b5_out = " << col2 << "\r\n";

            break;
        case 6:
            b6_out[samples_index] = col2 / 100.00;

            cout << "b6_out = " << col2 << "\r\n";

            break;
        case 7:
            watts_hour[samples_index] = col2 / 1000.00;

            cout << "total_watts = " << col2 << "\r\n";

            break;
        case 8:
            amp_in[samples_index] = col2 / 1000.00;

            cout << "amp_in = " << col2 << "\r\n";

            lines_index = 0;

            cout << "-----------> samples_index = " << samples_index << "\r\n";

            samples_index++;

            break;
        default:

            break;
        }

        getline(file_in, col, ';');

        lines_index++;

        //Sleep(200);
    }
}

void read_weights_from_file()
{
    std::ifstream in("batManage1.bin", std::ios_base::binary);

    if (in.good())
    {
        for (int j = 0; j < numberOf_Y; j++)
        {
            for (int k = 0; k < numberOf_H; k++)
            {
                // cout << W2[k][j];
                in.read((char*)&W2[k][j], sizeof(float));
            }
        }

        for (int k = 0; k < numberOf_H - 1; k++)
        {
            for (int i = 0; i < numberOf_X; i++)
            {
                in.read((char*)&W1[i][k], sizeof(float));
            }
        }
    }
}

void write_weights_on_file()
{
    float f1 = 0.00f;
    try
    {
        cout << "\nWriting to file... \n\n";

        std::ofstream fw("batManage1.bin", std::ios_base::binary);

        if (fw.good())
        {
            for (int j = 0; j < numberOf_Y; j++)
            {
                for (int k = 0; k < numberOf_H; k++)
                {
                    fw.write((char*)&W2[k][j], sizeof(float));
                }
            }

            for (int k = 0; k < numberOf_H - 1; k++)
            {
                for (int i = 0; i < numberOf_X; i++)
                {
                    fw.write((char*)&W1[i][k], sizeof(float));
                }
            }

            fw.close();

            cout << "\nFile closed... \n\n";
        }
        else
            cout << "Problem with opening file";
    }
    catch (const char* msg)
    {
        cerr << msg << endl;
    }
}



