using namespace std;

#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <stdint.h>
#include <sstream>

#include <random> // Per generazione numeri casuali
#include <ctime>  // Per il seme random

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

float T(float A);

float TLR(float A);

float err_epoca = 0.00f;

float err_rete = 0.00f;

float _err_amm = 0.011f; 

float epsilon = 0.2f; 

const uint8_t numberOf_X = 2 + 1;
 
const uint8_t numberOf_H = 5 + 1;

const uint8_t numberOf_Y = 1;

uint16_t const training_samples = 21;

double _lower_bound_xavier;

double _upper_bound_xavier;

float W1[numberOf_X - 1][numberOf_H - 1] = { 0 };

float W2[numberOf_H - 1][numberOf_Y] = { 0 };

float x[numberOf_X] = {0};

float y[numberOf_Y] = {0};

float h[numberOf_H] = {0};

float d[numberOf_Y] = {0};

float c_factor_training[training_samples]{};

float dischage_percentage_training[training_samples]{};

float battery_out_training[training_samples]{};

default_random_engine generator(time(0));

int main()
{
#ifdef __linux__

#elif _WIN32

	HWND consoleWindow = GetConsoleWindow();

	// Sposta e massimizza la finestra
	SetWindowPos(consoleWindow, nullptr, -1920, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	ShowWindow(consoleWindow, SW_MAXIMIZE);
	//std::cout << "La console è stata spostata e massimizzata!" << std::endl;

	//system("pause");

#else

#endif

	init();

	/*write_weights_on_file();

	return 0;*/

#ifdef __linux__

	// no sound on linux

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

	cout << "press a key..\n\n";
}

double xavier_init(double n_x, double n_y)
{
	return sqrt(6.0) / sqrt(n_x + n_y);
}

void lavora()
{
	x[0] = 0.20f / 10.00f; 

	x[1] = 30.00f / 100.00f; 

	esegui();

	cout << "\n batt1 : " << y[0] * 10.00f;

	x[0] = 1.00f / 10.00f; // AMPS 

	x[1] = 2.00f / 100.00f; // WATTS

	esegui();

	cout << "\n batt1 : " << y[0] * 10.00f;

	x[0] = 5.00f / 10.00f; // AMPS 

	x[1] = 100.00f / 100.00f; // WATTS

	esegui();

	cout << "\n batt1 : " << y[0] * 10.00f;
}

void apprendi()
{
	int epoca = 0;

	int cout_counter = 0;

	auto start = std::chrono::system_clock::now();

	read_samples_from_file_diagram_battery();

	do
	{
		err_epoca = 0.00f;

		for (unsigned long p = 0; p < training_samples; p++)
		{
			x[0] = c_factor_training[p] / 10.00f;

			x[1] = dischage_percentage_training[p] / 100.00f;

			d[0] = battery_out_training[p] / 10.00f;

			esegui();

			back_propagate();

			if (err_rete > err_epoca)
			{
				//cout << "ciclo: " << p << "  errore_rete= " << err_rete << "\n";
				err_epoca = err_rete;
			}
		}
		epoca++;
		cout_counter++;

		//cout << "stop when err_epoca < " << _err_amm << "\n\n";
		if (cout_counter == 1) {
			cout << "\nepoca: " << epoca << " errore_epoca= " << err_epoca << " errore_rete=" << err_rete << "\n";
			cout_counter = 0;
		}

		write_weights_on_file();

	} while (err_epoca > _err_amm);

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

	

#ifdef __linux__
	getchar();
#elif _WIN32
	_getch();
#else

#endif
}

void init()
{
	double param = xavier_init(numberOf_X - 1, numberOf_Y);

	cout << "xavier glorot param : " << param << "\n\n";

	_lower_bound_xavier = -param;

	_upper_bound_xavier = param;

	// Set Bias
	x[numberOf_X - 1] = 0.20f;

	h[numberOf_H - 1] = 0.20f;

	cout << "input elements initialization:\n\n";

	for (int i = 0; i < (numberOf_X - 1); i++)
	{
		x[i] = 0.00f;

		cout << "x[" << i << "]" << "=" << x[i] << "\n";
	}

	cout << "x[" << (int)(numberOf_X - 1) << "]" << "=" << x[numberOf_X - 1] << "-BIAS" << "\n";

	cout << "hidden elements initialization:\n\n";

	for (int i = 0; i < (numberOf_H - 1); i++)
	{
		h[i] = 0.00f;

		cout << "h[" << i << "]" << "=" << h[i] << "\n";
	}

	cout << "h[" << (int)(numberOf_H - 1) << "]" << "=" << h[numberOf_H - 1] << "-BIAS" << "\n";

	cout << "output elements initialization:\n\n";

	for (int i = 0; i < numberOf_Y; i++)
	{
		y[i] = 0.00f;

		cout << "y[" << i << "]=" << y[i] << "\n";
	}

	cout << "W1 elements initialization:\n\n";

	for (int i = 0; i < numberOf_X - 1; i++)
	{
		for (int k = 0; k < numberOf_H - 1; k++)
		{
			W1[i][k] = get_random_number_from_xavier();

			cout << "W1[" << i << "]" << "[" << k << "]" << "=" << W1[i][k] << "\n";
		}
	}

	for (int k = 0; k < numberOf_H - 1; k++)
	{
		for (int j = 0; j < numberOf_Y; j++)
		{
			W2[k][j] = get_random_number_from_xavier();

			cout << "W2[" << k << "]" << "[" << j << "]" << "=" << W2[k][j] << "\n";
		}
	}
}

void esegui()
{
	float A;

	for (int k = 0; k < (numberOf_H - 1); k++)
	{
		A = 0.00f;

		for (int i = 0; i < numberOf_X - 1; i++)
		{
			A = A + (W1[i][k] * x[i]);
		}

		//insert X bias 
		A = A + x[numberOf_X - 1];

		h[k] = T(A);
	}

	for (int j = 0; j < numberOf_Y; j++)
	{
		A = 0.00f;

		for (int k = 0; k < numberOf_H - 1; k++)
		{
			A = A + (W2[k][j] * h[k]);
		}

		//insert H bias 
		A = A + h[numberOf_H - 1];

		y[j] = T(A);
	}
}

void back_propagate()
{
	float err_H[numberOf_H - 1];

	float delta = 0.00f;

	err_rete = 0.00f;

	for (int k = 0; k < numberOf_H - 1; k++)
	{
		err_H[k] = 0.00f;
	}

	for (int j = 0; j < numberOf_Y; j++)
	{
		if (abs(d[j] - y[j]) > err_rete)
		{
			err_rete = abs(d[j] - y[j]);
		}

		delta = (d[j] - y[j]) * y[j] * (1.00f - y[j]);

		for (int k = 0; k < numberOf_H - 1; k++)
		{
			err_H[k] = err_H[k] + (delta * W2[k][j]);

			W2[k][j] = W2[k][j] + (epsilon * delta * h[k]);
		}

		// Aggiornamento del bias del livello di uscita
		h[numberOf_H - 1] += epsilon * delta;
	}
	for (int k = 0; k < numberOf_H - 1; k++)
	{
		delta = err_H[k] * h[k] * (1.00f - h[k]);

		for (int i = 0; i < numberOf_X - 1; i++)
		{
			W1[i][k] = W1[i][k] + (epsilon * delta * x[i]);
		}

		x[numberOf_X - 1] += epsilon * delta;
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
	std::string filename = "parziale2.csv";

	// Apertura del file
	std::ifstream file(filename);

	// Verifica se il file � stato aperto correttamente
	if (!file.is_open())
	{

		std::cerr << "Errore nell'apertura del file " << filename << std::endl;
	}

	std::string line;

	int index = 0;

	// Leggi il file riga per riga
	while (std::getline(file, line))
	{
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
	cout << "number of training sample = \t" << index << "\n\n";

	system("pause");

	if (index != training_samples)
	{
		cout << "\n\nALLERT!!!!!!! training sample different to index = \t" << index << "\n";
		system("pause"); 
	}

	file.close();
}

void read_weights_from_file()
{
	std::ifstream in("batManage1.bin", std::ios_base::binary);

	if (in.good())
	{
		for (int i = 0; i < numberOf_X - 1; i++)
		{
			for (int k = 0; k < numberOf_H - 1; k++)
			{
				in.read((char*)&W1[i][k], sizeof(float));
			}
		}

		for (int j = 0; j < numberOf_Y; j++)
		{
			for (int k = 0; k < numberOf_H - 1; k++)
			{
				in.read((char*)&W2[k][j], sizeof(float));
			}
		}

		in.read((char*)&x[numberOf_X - 1], sizeof(float));

		in.read((char*)&h[numberOf_H - 1], sizeof(float));
	}
}

void write_weights_on_file()
{
	try
	{
		//cout << "\nWriting to file... \n\n";

		std::ofstream fw("batManage1.bin", std::ios_base::binary);

		if (fw.good())
		{
			for (int i = 0; i < numberOf_X - 1; i++)
			{
				for (int k = 0; k < numberOf_H - 1; k++)
				{
					fw.write((char *)&W1[i][k], sizeof(float));
				}
			}

			for (int j = 0; j < numberOf_Y; j++)
			{
				for (int k = 0; k < numberOf_H - 1; k++)
				{
					fw.write((char*)&W2[k][j], sizeof(float));
				}
			}

			fw.write((char*)&x[numberOf_X - 1], sizeof(float));

			fw.write((char*)&h[numberOf_H - 1], sizeof(float));

			

			fw.close();

			//cout << "\nFile closed... \n\n";
		}
		else
			cout << "Problem with opening file";
	}
	catch (const char *msg)
	{
		cerr << msg << endl;
	}
}

float TLR(float x)
{
	return x > 0 ? x : 0.01f * x; // Leaky ReLU
}