#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int valoareinvalida = -1;

class StringsMaker
{
private:
	char* semne;
	int countSemne;
	double* cifreEq;
	int countCifEq;
	static bool parantezeRotunde;
	Ecuatie ecuatie;
	

public:
	StringsMaker()
	{

		cifreEq = nullptr;
		string smn = "";
		semne = new char[2];
		strcpy_s(semne, 2, smn.c_str());

		countCifEq = 0;
		countSemne = 0;
	}
	StringsMaker(int countSemne)
	{

		string smn = "";
		semne = new char[2];
		strcpy_s(semne, 2, smn.c_str());

		cifreEq = nullptr;
		countCifEq = 0;
		this->countSemne = countSemne;
	}

	void setEcuatie(Ecuatie e)
	{
		ecuatie = e;
	}

	void setCifreEq(double* cifreEq, int countCifEq)
	{
		if (cifreEq != nullptr && countCifEq > 0)
		{
			this->countCifEq = countCifEq;
			if (this->cifreEq != nullptr)
			{
				delete[] this->cifreEq;
			}
			this->cifreEq = new double[countCifEq];

			for (int i = 0; i < countCifEq; i++)
			{
				this->cifreEq[i] = cifreEq[i];
			}
		}
		else
		{
			countCifEq = 0;
			cifreEq = nullptr;
		}
	}

	void setCifreEqIndex(int i, int j)
	{
		this->cifreEq[i] = this->cifreEq[j];
	}

	void setCifreEqInt(double a, int i)
	{
		if (a == 0)
			cifreEq[i] = 0;
		else
			cifreEq[i] = a;
	}


	double* getCifreEq()
	{
		if (cifreEq != nullptr && countCifEq != 0)
		{
			double* cop = new double[countCifEq];
			for (int i = 0; i < countCifEq; i++)
			{
				cop[i] = cifreEq[i];
			}
			return cop;
		}
		else
		{
			return nullptr;
		}
	}

	char* getSemne()
	{
		if (semne != nullptr)
		{
			char* cop = new char[strlen(semne) + 1];
			strcpy_s(cop, strlen(semne) + 1, semne);
			return cop;
		}

	}

	void setSemne(const char* semne)
	{
		if (semne != nullptr)
		{
			if (this->semne != nullptr)
			{
				delete[] semne;
			}
			this->semne = new char[strlen(semne) + 1];
			strcpy_s(this->semne, strlen(semne) + 1, semne);
		}
		else
		{
			this->semne = nullptr;
		}
	}

	void setSemneChar(char a, int i)
	{
		this->semne[i] = a;
	}

	void setSemneIndex(int i, int j)
	{
		this->semne[i] = this->semne[j];
	}

	int getCountSemne()
	{
		return countSemne;
	}

	void setCountSemne(int countSemne)
	{
		this->countSemne = countSemne;
	}

	int getcountCifEq()
	{
		return countCifEq;
	}

	void setcountCifEq(int countCifEq)
	{
		this->countCifEq = countCifEq;
	}

	bool getParantezeRotunde()
	{
		return parantezeRotunde;
	}

	void setParantezeRotunde(bool x)
	{
		parantezeRotunde = x;
	}

	StringsMaker(const StringsMaker& e)
	{
		countSemne = e.countSemne;
		countCifEq = e.countCifEq;
		if (e.countCifEq != 0 && e.cifreEq != nullptr)
		{
			countCifEq = e.countCifEq;
			cifreEq = new double[countCifEq];
			for (int i = 0; i < countCifEq; i++)
			{
				cifreEq[i] = e.cifreEq[i];
			}
		}
		else
		{
			cifreEq = nullptr;
			countCifEq = 0;
		}

		if (e.semne != nullptr)
		{
			semne = new char[strlen(e.semne) + 1];
			strcpy_s(semne, strlen(e.semne) + 1, e.semne);
		}
		else
		{
			semne = nullptr;
		}
	}

	~StringsMaker()
	{
		if (cifreEq != nullptr)
		{
			delete[] cifreEq;
			cifreEq = nullptr;
		}

		if (semne != nullptr)
		{
			delete[] semne;
			semne = nullptr;
		}
	}

	StringsMaker& operator=(StringsMaker& e)
	{
		if (cifreEq != nullptr)
		{
			delete[] cifreEq;
			cifreEq = nullptr;
		}

		if (semne != nullptr)
		{
			delete[] semne;
			semne = nullptr;
		}

		countSemne = e.countSemne;
		countCifEq = e.countCifEq;
		if (e.countCifEq != 0 && e.cifreEq != nullptr)
		{
			countCifEq = e.countCifEq;
			cifreEq = new double[countCifEq];
			for (int i = 0; i < countCifEq; i++)
			{
				cifreEq[i] = e.cifreEq[i];
			}
		}
		else
		{
			cifreEq = nullptr;
			countCifEq = 0;
		}

		if (e.semne != nullptr)
		{
			semne = new char[strlen(e.semne) + 1];
			strcpy_s(semne, strlen(e.semne) + 1, e.semne);
		}
		else
		{
			semne = nullptr;
		}

		return *this;
	}

	long deserializare()
	{
		int numarul;
		ifstream f("rezultateTemp.bin", ios::binary);
		f.read((char*)&numarul, sizeof(numarul));
		return numarul;

		f.close();
	}

	void separareCifre()
	{
		char* cop = new char[strlen(ecuatie.getEcuatia()) + 1];
		strcpy_s(cop, strlen(ecuatie.getEcuatia()) + 1, ecuatie.getEcuatia());
		char* context = NULL;
		char* pas;
		int contorCifre = 0;
		pas = strtok_s(cop, " +-*/[]()^#", &context);
		while (pas != NULL)
		{
			contorCifre++;
			pas = strtok_s(NULL, " +-*/[]()^#", &context);
		}
		countCifEq = contorCifre;
		cifreEq = new double[countCifEq];
		delete[] pas;

		delete[] cop;
		cop = new char[strlen(ecuatie.getEcuatia()) + 1];
		strcpy_s(cop, strlen(ecuatie.getEcuatia()) + 1, ecuatie.getEcuatia());
		pas = strtok(cop, " +-*/[]()^#");
		int i;
		i = 0;
		while (pas != NULL)
		{
			string aux;
			aux = pas;
			if (aux == "x")
			{
				cifreEq[i] = deserializare();
				i++;
			}
			else
			{
				cifreEq[i] = stod(aux);
				i++;
			}
			
			pas = strtok(NULL, " +-*/[]()^#"); 
		}

	}

	void separareSemne()
	{
		char* cop = new char[strlen(ecuatie.getEcuatia()) + 1];
		strcpy_s(cop, strlen(ecuatie.getEcuatia()) + 1, ecuatie.getEcuatia());

		char* pas;
		double contorCifre = 0;
		pas = strtok(cop, " 0123456789.x");
		while (pas != NULL)
		{
			contorCifre = contorCifre + strlen(pas);
			pas = strtok(NULL, " 0123456789.x");
		}

		if (semne != nullptr)
		{
			delete[] semne;
		}

		semne = new char[contorCifre + 1];
		countSemne = contorCifre;

		cop = new char[strlen(ecuatie.getEcuatia()) + 1];
		strcpy_s(cop, strlen(ecuatie.getEcuatia()) + 1, ecuatie.getEcuatia());
		pas = strtok(cop, " 0123456789.x");
		int i;
		int j = 0;
		while (pas != NULL)
		{
			for (i = 0; i < strlen(pas); i++)
			{
				if (pas[i] == '(') parantezeRotunde = 1;
				if (pas[i] != 'x')
				{
					semne[j] = pas[i];
					j++;
				}
				
			}
			pas = strtok(NULL, " 0123456789.x");
		}

	}

	int operator--()
	{
		countCifEq--;
		return countCifEq;
	}

	int operator--(int i)
	{
		int copie = countCifEq;
		countCifEq--;
		return copie;
	}

	int operator++()
	{
		countCifEq++;
		return countCifEq;
	}

	int operator++(int i)
	{
		int copie = countCifEq;
		countCifEq++;
		return copie;
	}

	char operator[](int i)
	{
		if (i >= 0 && i < countSemne)
			return semne[i];
		else
			return valoareinvalida;
	}

	friend ostream& operator<<(ostream& out, StringsMaker st);
	friend istream& operator>>(istream& in, StringsMaker& st);
};

bool StringsMaker::parantezeRotunde = 0;

ostream& operator<<(ostream& out, StringsMaker st)
{
	out << endl;

	out << "Semnele ecuatiei sunt: ";
	for (int i = 0; i < st.countSemne; i++)
	{
		out << st.semne[i] << " ";
	}
	cout << endl;

	out << "Cifrele ecuatiei sunt: ";
	for (int i = 0; i < st.countCifEq; i++)
	{
		out << st.cifreEq[i] << " ";
	}
	out << endl;
	return out;
}

istream& operator>>(istream& in, StringsMaker& st)
{
	int x;
	in >> x;
	st.countCifEq = x;
	int y;
	in >> y;
	st.countSemne = y;

	string str;
	cout << "Introduceti semnele: ";
	st.setSemne(str.c_str());

	double* v = new double[x];
	st.setCifreEq(v, x);

	return in;
}

class StringsChoose
{
public:
	virtual void afisare() = 0;
	//virtual void afisareNr(int a) = 0;
	virtual void setStrMk(StringsMaker e) = 0;
};

class StringsSign : public StringsChoose
{
private:
	StringsMaker str;

public:
	void setStrMk(StringsMaker e) override
	{
		str = e;
	}

	void afisare() override
	{
		cout << "Semnele ecuatiei sunt: ";
		for (int i = 0; i < str.getCountSemne(); i++)
		{
			cout << str.getSemne()[i] << " ";
		}
		cout << endl << endl;
	}
};


class StringsNr : public StringsChoose
{
private:
	StringsMaker str;
	double* cifreEqVT;
	int countCifEqVT;

public:
	void setStrMk(StringsMaker e) override
	{
		str = e;
	}

	void afisare() override
	{
		//setStrMk(str);
		countCifEqVT = str.getcountCifEq();
		cifreEqVT = new double[countCifEqVT];

		for (int i = 0; i < countCifEqVT; i++)
		{
			cifreEqVT[i] = str.getCifreEq()[i];
		}
		cout << "Numerele ecuatiei sunt: ";
		for (int i = 0; i < countCifEqVT; i++)
		{
			cout << cifreEqVT[i] << " ";
		}
		cout << endl << endl;
	}
};