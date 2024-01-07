#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Ecuatie
{
protected:
	char* ecuatia;
	const int id;

public:
	Ecuatie() : id(1)
	{
		string eqa = " ";
		ecuatia = new char[2];
		strcpy_s(ecuatia, 2, eqa.c_str());
	}

	Ecuatie(const char* ecuatia, int i) : id(i)
	{
		if (ecuatia != nullptr || strcmp(ecuatia, "") == 0)
		{
			this->ecuatia = new char[strlen(ecuatia) + 1];
			strcpy_s(this->ecuatia, strlen(ecuatia) + 1, ecuatia);
		}
	}

	Ecuatie(int i) : id(i)
	{}

	Ecuatie(const Ecuatie& e) : id(e.id)
	{
		if (e.ecuatia != nullptr)
		{
			ecuatia = new char[strlen(e.ecuatia) + 1];
			strcpy_s(ecuatia, strlen(e.ecuatia) + 1, e.ecuatia);
		}
		else
		{
			ecuatia = nullptr;
		}
	}
	

	~Ecuatie()
	{
		if (ecuatia != nullptr)
		{
			delete[] ecuatia;
			ecuatia = nullptr;
		}
	}

	Ecuatie& operator=(Ecuatie& e)
	{
		if (ecuatia != nullptr)
		{
			delete[] ecuatia;
			ecuatia = nullptr;
		}

		if (e.ecuatia != nullptr)
		{
			ecuatia = new char[strlen(e.ecuatia) + 1];
			strcpy_s(ecuatia, strlen(e.ecuatia) + 1, e.ecuatia);
		}
		else
		{
			ecuatia = nullptr;
		}

		return *this;
	}

	virtual void citire(istream& f)
	{
		string ecuatiaIntrodusa;
		
		
		cout << "Introduceti ecuatia " << id << " sau (exit): ";
		f >> ws;
		getline(cin, ecuatiaIntrodusa);
		if (ecuatia != nullptr)
		{
			delete[] ecuatia;
		}
		ecuatia = new char[ecuatiaIntrodusa.length() + 1];
		strcpy_s(ecuatia, ecuatiaIntrodusa.length() + 1, ecuatiaIntrodusa.c_str());
		
	}

	void setEcuatia(const char* ecuatia)
	{
		if (ecuatia != nullptr)
		{
			if (this->ecuatia != nullptr)
			{
				delete[] this->ecuatia;
			}
			this->ecuatia = new char[strlen(ecuatia) + 1];
			strcpy_s(this->ecuatia, strlen(ecuatia) + 1, ecuatia);
		}
	}

	char* getEcuatia()
	{
		if (ecuatia != nullptr)
		{
			char* cop = new char[strlen(ecuatia) + 1];
			strcpy_s(cop, strlen(ecuatia) + 1, ecuatia);
			return cop;
		}

	}

	int getId()
	{
		if (id != 0)
		{
			return id;
		}
	}


	void noSpaces()
	{
		int whiteSpaces = 0;
		int cop;
		for (int i = 0; i < strlen(ecuatia); i++)
		{
			if (ecuatia[i] == ' ')
			{
				whiteSpaces++;
			}
		}
		cop = whiteSpaces;

		while (whiteSpaces != 0)
		{
			for (int i = 0; i < strlen(ecuatia); i++)
			{
				if (ecuatia[i] == ' ')
				{
					for (int j = i; j < strlen(ecuatia) - 1; j++)
					{
						ecuatia[j] = ecuatia[j + 1];
					}
				}
			}
			whiteSpaces--;
		}
		ecuatia[strlen(ecuatia) - cop] = NULL;
	}

	void erori()
	{
		int parPS = 0;
		int parPD = 0;
		int parRS = 0;
		int parRD = 0;
		int poz1 = 0;
		int poz2 = 0;

		for (int i = 0; i < strlen(ecuatia); i++)
		{
			if (ecuatia[i] == '(') { parRS++; poz1 = i; }
			if (ecuatia[i] == ')') parRD++;
			if (ecuatia[i] == '[') { parPS++; poz2 = i; }
			if (ecuatia[i] == ']') parPD++;

	
			if (strcmp("exit", ecuatia) == 0)
			{
				delete[] ecuatia;
				ecuatia = new char[strlen("exit") + 1];
				strcpy(ecuatia, "exit");
				break;
			}

			if (strchr("ABCDEFGHIJKLMNOPQRSTUBWXYZabcdefghijklmnopqrstuvwyz,{}=!@$%&`~';:", ecuatia[i]) != 0)
			{
				delete[] ecuatia;
				ecuatia = new char[strlen("Eroare - Nu-i ecuatie d-aia. Fara litere p-aicea. (Sau alte semne dubioase).") + 1];
				strcpy(ecuatia, "Eroare - Nu-i ecuatie d-aia. Fara litere p-aicea. (Sau alte semne dubioase).");
				break;
			}

			if (ecuatia[0] == '+' || ecuatia[0] == '*' || ecuatia[0] == '/' || ecuatia[0] == '^' || ecuatia[0] == '#')
			{
				delete[] ecuatia;
				ecuatia = new char[strlen("Eroare - Semn incorect la inceput de ecuatie.") + 1];
				strcpy(ecuatia, "Eroare - Semn incorect la inceput de ecuatie.");
				break;
			}

			if (ecuatia[strlen(ecuatia) - 1] == '+' || ecuatia[strlen(ecuatia) - 1] == '-' || ecuatia[strlen(ecuatia) - 1] == '*' ||
				ecuatia[strlen(ecuatia) - 1] == '/' || ecuatia[strlen(ecuatia) - 1] == '^' || ecuatia[strlen(ecuatia) - 1] == '#')
			{
				delete[] ecuatia;
				ecuatia = new char[strlen("Eroare - Semn incorect la final de operatie.") + 1];
				strcpy(ecuatia, "Eroare - Semn incorect la final de operatie.");
				break;
			}

			if ((strchr("/*+-#^", ecuatia[i])) != 0 && (strchr("/*+-#^", ecuatia[i + 1]) != 0))
			{
				delete[] ecuatia;
				ecuatia = new char[strlen("Eroare - Semne de calcul puse consecutiv.") + 1];

				strcpy(ecuatia, "Eroare - Semne de calcul puse consecutiv.");
				break;
			}

			if (ecuatia[i] == '/' && ecuatia[i + 1] == '0')
			{
				delete[] ecuatia;
				ecuatia = new char[strlen("Eroare - Impartire la 0.") + 1];

				strcpy(ecuatia, "Eroare - Impartire la 0.");
				break;
			}

		}

		

		char* cop = new char[strlen(ecuatia + 1)];
		strcpy_s(cop, strlen(ecuatia) + 1, ecuatia);
		char* pas = strtok(cop, " +-*/[]()^#");
		int j;
		j = 0;
		//int contorPuncte = 0;
		int contorPuncteOut = 0;
		while (pas != NULL)
		{
			string aux;
			aux = pas;
			int contorPuncte = 0;
			for (int j = 0; j < aux.length(); j++)
			{
				if (pas[j] == '.')
					contorPuncte++;
			}

			if (contorPuncte > 1)
			{
				contorPuncteOut = contorPuncte;
				break;
			}
			pas = strtok(NULL, " +-*/[]()^#");
		}

		if (contorPuncteOut > 1)
		{
			delete[] ecuatia;
			ecuatia = new char[strlen("Eroare - Doua sau mai multe puncte puse in loc de unul la zecimale.") + 1];
			strcpy(ecuatia, "Eroare - Doua sau mai multe puncte puse in loc de unul la zecimale.");
		}
		else
		{
			if ((parPS != parPD) || (parRS != parRD))
			{
				delete[] ecuatia;
				ecuatia = new char[strlen("Eroare - Nu au fost puse paranteze deschise egale cu cele inchise. / Ai pus 2 paranteze rodunte deschise consecutive.") + 1];

				strcpy(ecuatia, "Eroare - Nu au fost puse paranteze deschise egale cu cele inchise. / Ai pus 2 paranteze rotunte deschise consecutive.");
			}
		}

		if (poz1 < poz2)
		{
			delete[] ecuatia;
			ecuatia = new char[strlen("Eroare - Paranteze rotunde puse inaintea celor patrate.") + 1];
			strcpy(ecuatia, "Eroare - Paranteze rotunde puse inaintea celor patrate.");
		}

		if (strlen(ecuatia) == 0)
		{
			delete[] ecuatia;
			ecuatia = new char[strlen("Eroare - Nu s-a introdus nici o ecuatie.") + 1];
			strcpy(ecuatia, "Eroare - Nu s-a introdus nici o ecuatie.");
		}

		
	}

	friend ostream& operator<<(ostream& out, Ecuatie e);
	friend istream& operator>>(istream& in, Ecuatie& e);
};

ostream& operator<<(ostream& out, Ecuatie e)
{
	out << "Ecuatia: " << e.ecuatia << endl;
	return out;
}

istream& operator>>(istream& in, Ecuatie& e)
{
	cout << "Introduceti ecuatia: ";
	string eq;
	in >> eq;
	e.setEcuatia(eq.c_str());

	return in;
}

class EcuatieFile : public Ecuatie
{
public:

	void citire(istream& f) override
	{
		string ecuatia2;
		f >> ws;
		getline(f, ecuatia2);
		cout << "Ecuatia: " << ecuatia2 << endl;
		ecuatia = new char[strlen(ecuatia2.c_str()) + 1];
		strcpy_s(ecuatia, strlen(ecuatia2.c_str()) + 1, ecuatia2.c_str());
	}
};

