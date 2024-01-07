#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Calculator
{
private:
	static double rezultat;
	static int parantezePatrate;
	Ecuatie ecuatie2;
	StringsMaker eqStrings;
protected:
	static double* sirRezultate;
	static int countSirRezultate;

public:
	Calculator()
	{
		rezultat = 0;
	}

	void setStrings(StringsMaker sm)
	{
		eqStrings = sm;
	}

	static double getRezultat()
	{
		return rezultat;
	}

	static void setRezultat(double r)
	{
		rezultat = r;
	}

	Calculator(const Calculator& e)
	{
		rezultat = e.rezultat;
	}

	Calculator& operator=(Calculator& e)
	{
		rezultat = e.rezultat;
		return *this;
	}

	static void power(double& x, double putere)
	{
		x = pow(x, putere);
	}

	void nthRoot(double& A, double N)
	{
		A = pow(A, 1.0 / N);
	}

	void dezminusificare(double* cifreEq, char* semne, int countSemne, int countCifEq)
	{
		if (semne[0] == '-' && countCifEq == countSemne)
		{
			cifreEq[0] = cifreEq[0] - 2 * cifreEq[0];
			char* cop = new char[countSemne - 1];
			for (int i = 1; i < countSemne; i++)
			{
				cop[i] = semne[i];
			}
			delete[] semne;
			semne = new char[countSemne - 1];
			strcpy_s(semne, countSemne - 1, cop);
		}
	}

	//calculaeaza rezultatul unei ecuatii fara paranteze 
	double calculator(double* cifreEq, char* semne, int countSemne, int countCifEq)
	{
		double rezultat;
		//parcurge vectorul de semne

		for (int i = 0; i < countSemne; i++)
		{
			if (semne[i] == '^')
			{
				power(cifreEq[i], cifreEq[i + 1]);
				cifreEq[i + 1] = cifreEq[i];
				int j = 1;
				while (semne[i - j] == '^' || semne[i - j] == '#')
				{
					cifreEq[i - j] = cifreEq[i];
					j++;
				}
			}
			if (semne[i] == '#')
			{
				nthRoot(cifreEq[i], cifreEq[i + 1]);
				cifreEq[i + 1] = cifreEq[i];
				int j = 1;
				while (semne[i - j] == '^' || semne[i - j] == '#')
				{
					cifreEq[i - j] = cifreEq[i];
					j++;
				}
			}
		}

		for (int i = 0; i < countSemne; i++)
		{	//verifica ce semn are din vector

			if (semne[i] == '*')
			{
				cifreEq[i] = cifreEq[i] * cifreEq[i + 1]; //salveaza in operatorul stang rezultatul operatiei
				cifreEq[i + 1] = cifreEq[i]; //ambii operatori au rezultatul

				int j = 1;
				//verifica ce semne anterioare sunt *, /, ^ sau # si atribuie operatorilor acestora rezultatul de mai sus
				while (semne[i - j] == '*' || semne[i - j] == '/' || semne[i - j] == '^' || semne[i - j] == '#')
				{
					cifreEq[i - j] = cifreEq[i];
					j++;
				}

				j = 1;
				while (semne[i + j] == '^' || semne[i + j] == '#')
				{
					cifreEq[i + 1 + j] = cifreEq[i];
					j++;
				}
			}
			if (semne[i] == '/')
			{
				cifreEq[i] = cifreEq[i] / cifreEq[i + 1];
				cifreEq[i + 1] = cifreEq[i];

				int j = 1;
				while (semne[i - j] == '*' || semne[i - j] == '/' || semne[i - j] == '^' || semne[i - j] == '#')
				{
					cifreEq[i - j] = cifreEq[i];
					j++;
				}

				j = 1;
				while (semne[i + j] == '^' || semne[i + j] == '#')
				{
					cifreEq[i + 1 + j] = cifreEq[i];
					j++;
				}

			}
		}
		if (cifreEq != nullptr)
		{
			rezultat = cifreEq[0];
		}

		//in vectorul de semne se mai afla doar sem

		for (int i = 0; i < countSemne; i++) //aduna/scade numerele ramase, returneaza rezultatul
		{
			if (semne[i] == '+')
			{
				rezultat = rezultat + cifreEq[i + 1];
			}
			if (semne[i] == '-')
			{
				rezultat = rezultat - cifreEq[i + 1];
			}
		}

		if (cifreEq != nullptr)
		{
			return rezultat;
		}
	}

	void paranteze()
	{
		int ok = 2;
		while (ok != 0)
		{
			int locParS = -1;
			int locParD = -1;
			int distantaLoc;
			if (eqStrings.getParantezeRotunde() == 0)
			{
				for (int i = 0; i < eqStrings.getCountSemne(); i++)
				{
					if (eqStrings.getSemne()[i] == '[') eqStrings.setSemneChar('(', i);

					if (eqStrings.getSemne()[i] == ']') eqStrings.setSemneChar(')', i);

					parantezePatrate = 0;
				}
			}

			for (int i = 0; i < eqStrings.getCountSemne(); i++)
			{
				if (eqStrings.getSemne()[i] == '[') parantezePatrate++;
				if (eqStrings.getSemne()[i] == ']') parantezePatrate++;

				if (eqStrings.getSemne()[i] == '(')
				{
					locParS = i;
				}
				if (eqStrings.getSemne()[i] == ')')
				{
					locParD = i;
				}
				distantaLoc = locParD - locParS;
				if (locParS != -1 && locParD != -1)
				{
					double* auxCifre = new double[distantaLoc];
					int x = 0, z = 0;
					char* auxSemne = new char[distantaLoc];
					for (int j = locParS + 1; j < locParD; j++)
					{
						auxSemne[x] = eqStrings.getSemne()[j];
						x++;
					}

					locParS -= parantezePatrate;
					locParD -= parantezePatrate;

					for (int j = locParS; j < locParD; j++)
					{
						auxCifre[z] = eqStrings.getCifreEq()[j];
						z++;
					}

					double rezTemp;
					//dezminusificare(auxCifre, auxSemne, distantaLoc - 1, distantaLoc);
					rezTemp = calculator(auxCifre, auxSemne, distantaLoc - 1, distantaLoc);

					int copDL = distantaLoc - 1;
					while (copDL != 0)
					{
						for (int i = locParS; i < eqStrings.getcountCifEq() - 1; i++)
						{
							//cifreEq[i] = cifreEq[i + 1];
							eqStrings.setCifreEqIndex(i, i + 1);
						}
						//countCifEq--;
						eqStrings.setcountCifEq(eqStrings.getcountCifEq() - 1);
						copDL--;
					}
					//cifreEq[locParS] = rezTemp;
					eqStrings.setCifreEqInt(rezTemp, locParS);

					locParS += parantezePatrate;
					locParD += parantezePatrate;

					copDL = distantaLoc + 1;
					while (copDL != 0)
					{
						for (int i = locParS; i < eqStrings.getCountSemne(); i++)
						{
							//semne[i] = semne[i + 1];
							eqStrings.setSemneIndex(i, i + 1);
						}
						//countSemne--;
						eqStrings.setCountSemne(eqStrings.getCountSemne() - 1);
						copDL--;
					}
					if (parantezePatrate != 0)
					{
						i = locParS - parantezePatrate;
					}
					else
					{
						i = locParS;
					}

					locParD = -1;
					locParS = -1;
				}
			}

			eqStrings.setParantezeRotunde(0);
			ok--;
		}
		rezultat = calculator(eqStrings.getCifreEq(), eqStrings.getSemne(), eqStrings.getCountSemne(), eqStrings.getcountCifEq());
	}

	void setEcuatie(Ecuatie f)
	{
		ecuatie2 = f;
	}

	static void rezultateCalcule()
	{
		sirRezultate[countSirRezultate] = rezultat;
		countSirRezultate++;
	}

	double* getRezultateCalcule()
	{
		if (sirRezultate != nullptr && countSirRezultate != 0)
		{
			double* cop = new double[countSirRezultate];
			for (int i = 0; i < countSirRezultate; i++)
			{
				cop[i] = sirRezultate[i];
			}
			return cop;
		}
		else
		{
			return nullptr;
		}
	}

	int getCountSirRezultate()
	{
		return countSirRezultate;
	}

	virtual void scriere(ostream& o)
	{
		if (countSirRezultate == 0)
		{
			o << "Nu au fost introduse ecuatii, sau au fost introduse doar erori." << endl << endl;
			system("pause");
			system("cls");
		}
		else
		{
			system("cls");
			o << "Rezultatele ecuatiilor introduse anterior: ";
			for (int i = 0; i < countSirRezultate; i++)
			{
				o << sirRezultate[i] << " ";
			}
			o << endl;
			system("pause");
			system("cls");
		}
	}

	void serializare(long x)
	{
		cout << "Doriti sa salvati acest rezultat in fisierul binar? " << endl << "1. DA" << endl << "2. NU" << endl << endl;
		short int z;
		cin >> z;
		system("cls");

		if (z == 1)
		{
			ofstream f("rezultateTemp.bin", ios::binary);
			f.write((char*)&x, sizeof(x));

			f.close();
		}
		
	}

	

	friend ostream& operator<<(ostream& out, Calculator e);
	friend istream& operator>>(istream& in, Calculator& e);

	Calculator operator+(Calculator c)
	{
		Calculator aux;
		aux.rezultat = rezultat + c.rezultat;
		return aux;
	}

	Calculator operator-(Calculator c)
	{
		Calculator aux;
		aux.rezultat = rezultat + c.rezultat;
		return aux;
	}

	Calculator operator*(Calculator c)
	{
		Calculator aux;
		aux.rezultat = rezultat * c.rezultat;
		return aux;
	}


};

double Calculator::rezultat = 0;
int Calculator::parantezePatrate = 0;
double* Calculator::sirRezultate = new double[100];
int Calculator::countSirRezultate = 0;

ostream& operator<<(ostream& out, Calculator e)
{
	out.precision(7);
	out << "Rezultatul este: ";
	out << e.rezultat << endl << endl << endl;
	return out;
}

istream& operator>>(istream& in, Calculator& e)
{
	int c;
	cout << "Introduceti rezultatul: ";
	in >> c;
	e.rezultat = c;

	int z;
	cout << "Introduceti numarul de paranteze patrare: ";
	in >> z;
	e.parantezePatrate = z;

	return in;
}

class CalculatorFile : public Calculator
{
public:
	void scriere(ostream& o) override
	{
		system("cls");
		o << "Rezultatele ecuatiilor sunt: ";
		for (int i = 0; i < countSirRezultate; i++)
		{
			o << sirRezultate[i] << " ";
		}
		system("pause");
		system("cls");
	}
};

template<typename V, int x>
class Vector
{
private:
	V elemente[x];

public:
	int getDimensiune()
	{
		return x;
	}

	
};
