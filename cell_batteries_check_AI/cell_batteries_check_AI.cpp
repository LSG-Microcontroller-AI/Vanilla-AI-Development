using namespace std;

#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <stdint.h>
#include <sstream>


#include <random>   // Per generazione numeri casuali
#include <ctime>    // Per il seme random

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

double get_random_number_from_xavier();

void esegui();

void apprendi();

void back_propagate();

void read_weights_from_file();

void write_weights_on_file();

void read_samples_from_file_diagram_battery();

//void read_samples_from_file_scooter_battery();

float T(float A);

const uint8_t numberOf_X = 2 + 1;

const uint8_t numberOf_H = 2 + 1;

const uint8_t numberOf_Y = 1;

uint16_t const training_samples = 573;


float err_rete;

double _lower_bound_xavier;

double _upper_bound_xavier;

float W1[numberOf_X][numberOf_H];

float W2[numberOf_H][numberOf_Y];

float x[numberOf_X] = {};

float y[numberOf_Y] = {};

float h[numberOf_H] = {};

float d[numberOf_Y] = {};

float c_factor_training[training_samples]{};

float dischage_percentage_training[training_samples]{};

float battery_out_training[training_samples]{};

default_random_engine generator(time(0));

int main()
{
	init();

#ifdef __linux__

	//no sound on linux

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

double xavier_init(double n_x, double n_y) {
	return sqrt(6.0) / sqrt(n_x + n_y);
}

void lavora()
{
	x[0] = 14.82f / 1000.00f;//AMPS

	x[1] = 30.00f / 1000.00f;//WATTS

	esegui();

	cout << "\n amps : " << x[0] * 1000.00f;

	cout << "\n watts : " << x[1] * 1000.00f;

	cout << "\n batt1 : " << y[0] * 100.00f;
}

void init()
{
	double param = xavier_init(numberOf_X, numberOf_Y);

	_lower_bound_xavier = -param;

	_upper_bound_xavier = param;


	//Set Bias
	x[numberOf_X - 1] = 0.1f;

	h[numberOf_H - 1] = 0.1f;

	cout << "input elements:\n";

	for (int i = 0; i < (numberOf_X - 1); i++)
	{
		x[i] = 0.00f;

		cout << "x[" << i << "]" << "=" << x[i] << "\n";
	}
	cout << "x[" << (int)(numberOf_X - 1) << "]" << "=" << x[numberOf_X - 1] << "-BIAS" << "\n";

	cout << "hidden elements:\n";

	for (int i = 0; i < (numberOf_H - 1); i++)
	{
		h[i] = 0.00f;

		cout << "h[" << i << "]" << "=" << h[i] << "\n";
	}
	cout << "h[" << (int)(numberOf_H - 1) << "]" << "=" << h[numberOf_H - 1] << "-BIAS" << "\n";

	cout << "output elements:\n";

	for (int i = 0; i < numberOf_Y; i++)
	{
		y[i] = 0.00f;

		cout << "y[" << i << "]=" << y[i] << "\n";
	}

	for (int i = 0; i < numberOf_X; i++)
	{
		for (int k = 0; k < numberOf_H; k++)
		{
			W1[i][k] = get_random_number_from_xavier();

			cout << "W1[" << i << "]" << "[" << k << "]" << "=" << W1[i][k] << "\n";
		}
	}

	for (int k = 0; k < numberOf_H; k++)
	{
		for (int j = 0; j < numberOf_Y; j++)
		{
			W2[k][j] = get_random_number_from_xavier();

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
//    c_factor[index] = 0.030f;
//
//    dischage_percentage[index] = 0.0100f;
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
//    c_factor[index] = 0.030f;
//
//    dischage_percentage[index] = 0.0200f;
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
//    c_factor[index] = 0.030f;
//
//    dischage_percentage[index] = 0.0300f;
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
//    c_factor[index] = 0.025f;
//
//    dischage_percentage[index] = 0.0500f;
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

	for (int k = 0; k < (numberOf_H); k++)
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

	float err_amm = 0.001f;

	int epoca = 0;

	auto start = std::chrono::system_clock::now();

	do
	{
		err_epoca = 0.00f;

		for (unsigned long p = 0; p < training_samples; p++)
		{
			x[0] = c_factor_training[p];

			x[1] = dischage_percentage_training[p];

			d[0] = battery_out_training[p];

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
	getchar();
#elif _WIN32
	_getch();
#else

#endif
}

void back_propagate()
{
	float epsilon = 0.7f;

	float err_H[numberOf_H];

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

double get_random_number_from_xavier()
{
	uniform_real_distribution<double> distribution(_lower_bound_xavier, _upper_bound_xavier);

	double random_value = distribution(generator);

	return random_value;
}

float T(float A)
{
	return 1.00f / (1.00f + pow(M_E, -A));
}

void read_samples_from_file_diagram_battery()
{
	std::string filename = "total.csv";

	// Apertura del file
	std::ifstream file(filename);

	// Verifica se il file � stato aperto correttamente
	if (!file.is_open()) {

		std::cerr << "Errore nell'apertura del file " << filename << std::endl;
	}

	std::string line;

	int index = 0;

	// Leggi il file riga per riga
	while (std::getline(file, line)) {

		std::stringstream ss(line);

		std::string item;

		std::getline(ss, item, ';');

		c_factor_training[index] = std::stod(item);

		std::getline(ss, item, ';');

		dischage_percentage_training[index] = std::stod(item);

		std::getline(ss, item, ';');

		battery_out_training[index] = std::stod(item);

		// Esegui qualcosa con le variabili a, b, e c
		// Ad esempio, stampale a video
		std::cout << "c_factor_training: " << c_factor_training[index]
			<< "\tdischage_percentage_training: " << dischage_percentage_training[index]
			<< "\tbattery_out_training: " << battery_out_training[index] << std::endl;
		index++;

	}
	cout << "number of training sample = \t" << index;

	if (index != training_samples)
	{
		cout << "ALLERT!!!!!!! training sample different to index = \t" << index;
	}

	file.close();

}

//void read_samples_from_file_scooter_battery()
//{
//    uint16_t samples_index = 0;
//
//    string col = "";
//
//    float col2 = 0.00f;
//
//    ifstream in("BATT0.CSV");
//
//    getline(in, col, ';');
//
//    getline(in, col, ';');
//
//    getline(in, col, ';');
//
//    getline(in, col, ';');
//
//    uint8_t lines_index = 1;
//
//    while (in.good() && samples_index <= sample_file_line_numbers)
//    {
//        getline(in, col, ';');
//
//        getline(in, col, ';');
//
//        getline(in, col, ';');
//
//        col2 = stof(col);
//
//        switch (lines_index)
//        {
//        case 1:
//            b1_out[samples_index] = col2 / 100.00;
//
//            cout << "b1_out = " << col2  << "\r\n";
//
//            break;
//        case 2:
//            b2_out[samples_index] = col2 / 100.00;
//
//            cout << "b2_out = " << col2 << "\r\n";
//
//            break;
//        case 3:
//            b3_out[samples_index] = col2 / 100.00;
//
//            cout << "b3_out = " << col2 << "\r\n";
//
//            break;
//        case 4:
//            b4_out[samples_index] = col2 / 100.00;
//
//            cout << "b4_out = " << col2 << "\r\n";
//
//            break;
//        case 5:
//            b5_out[samples_index] = col2 / 100.00;
//
//            cout << "b5_out = " << col2 << "\r\n";
//
//            break;
//        case 6:
//            b6_out[samples_index] = col2 / 100.00;
//
//            cout << "b6_out = " << col2 << "\r\n";
//
//            break;
//        case 7:
//            dischage_percentage[samples_index] = col2 / 1000.00;
//
//            cout << "total_watts = " << col2 << "\r\n";
//
//            break;
//        case 8:
//            c_factor[samples_index] = col2 / 1000.00;
//
//            cout << "amp_in = " << col2 << "\r\n";
//
//            lines_index = 0;
//
//            cout << "-----------> samples_index = " << samples_index << "\r\n";
//
//            samples_index++;
//
//            break;
//        default:
//
//            break;
//        }
//
//        getline(in, col, ';');
//
//        lines_index++;
//
//        //Sleep(200);
//    }
//}

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

			for (int k = 0; k < numberOf_H; k++)
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
