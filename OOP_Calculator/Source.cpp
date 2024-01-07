#define _CRT_SECURE_NO_WARNINGS
#include "EquationAlgorithm.h"
#include "StringsMakerHeader.h"
#include "CalculatorHeader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h> //am inclus aceasta biblioteca pentru a curata CMD
#include <vector>
using namespace std;

int main(int varc, char** sirInt)
{
	
	
	if (varc >= 2)
	{
		
		int ID = 1;
		string ecuatiaIntrodusa;
		StringsMaker st;
		Calculator c;

		Ecuatie ec(sirInt[1], ID);
		ec.noSpaces();
		ec.erori();
		if (ec.getEcuatia()[0] == 'E' || ec.getEcuatia()[0] == 'e')
		{
			cout << endl << ec.getEcuatia() << endl << endl;
		}
		else
		{
			st.setEcuatie(ec);
			st.separareCifre();
			st.separareSemne();
			cout << st;

			c.setStrings(st);
			c.paranteze();
			c.setEcuatie(ec);
			c.rezultateCalcule();
			cout << c;
			ID++;
		}
		cout << endl;

		system("pause");
		system("cls");
	}
	
	
		short int a = 3;
		Ecuatie* ect;
		Calculator* pc;
		CalculatorFile fc;
		StringsMaker st;
		Calculator c;
		string ecuatieInit;


		while (a != 0)
		{
			//system("cls");
			cout << "1. Introducere de la tastatura." << endl;
			cout << "2. Introducere din fisier text." << endl;
			cout << "3. Introducere ecuatie cu necunoscuta x:." << endl;
			cout << "4. Iesire din executie." << endl;
			//system("pause");

			cin >> a;
			system("cls");
			if (a == 1)
			{
				int ID = 1;
				string ecuatiaIntrodusa;


				while (ecuatiaIntrodusa != "exit")
				{
					Ecuatie ec(ID);
					ect = &ec;
					ect->citire(cin);
					ec.noSpaces();
					ec.erori();

					if (ec.getEcuatia()[0] == 'e')
					{
						ecuatiaIntrodusa = "exit";
					}
					else
					{
						if (ec.getEcuatia()[0] == 'E')
						{
							cout << endl << ec.getEcuatia() << endl << endl;
						}
						else
						{
							st.setEcuatie(ec);
							st.separareCifre();
							st.separareSemne();

							StringsChoose* sch;
							StringsSign ssgn;
							StringsNr srn;
							sch = &ssgn;
							sch->setStrMk(st);
							sch->afisare();
							sch = &srn;
							sch->setStrMk(st);
							sch->afisare();
							//cout << st;

							c.setStrings(st);
							c.paranteze();
							c.setEcuatie(ec);
							c.rezultateCalcule();
							cout << c;
							c.serializare(c.getRezultat());
							ID++;
						}
					}
				}
				if (ecuatiaIntrodusa.at(0) == 'E')
				{
					cout << endl << ecuatiaIntrodusa << endl << endl;
				}
				else
				{
					
					system("cls");
					cout << "1. Afisare rezultate pe ecran." << endl;
					cout << "2. Stocare rezultate in fisierul output.txt." << endl;
					short int b;
					cin >> b;
					if (b == 1)
					{
						pc = &c;
						pc->scriere(cout);
					}
					else
					{
						if (b == 2)
						{
							ofstream g("output.txt");
							pc = &fc;
							pc->scriere(g);
							cout << "Rezultatele se afla in fisierul output.txt" << endl;
						}
					}
				}

			}
			else
			{
				if (a == 2)
				{
					ofstream g("output.txt");
					int ID = 1;
					string ecuatiaIntrodusa;
					ifstream f("input.txt");

					while (ecuatiaIntrodusa != "exit")
					{
						Ecuatie ec(ID);
						EcuatieFile ef;
						ect = &ef;
						ect->citire(f);
						
						ec = ef;
						g << ec.getEcuatia() << endl;
						ec.noSpaces();
						ecuatieInit = ec.getEcuatia();
						ec.erori();
						if (ec.getEcuatia()[0] == 'E' || ec.getEcuatia()[0] == 'e')
						{
							cout << endl << ec.getEcuatia() << endl << endl;
							g << ecuatieInit << "= " << ec.getEcuatia() << endl << endl;
							ecuatiaIntrodusa = "exit";
						}
						else
						{
							st.setEcuatie(ec);
							st.separareCifre();
							st.separareSemne();
							//cout << st;

							c.setStrings(st);
							c.paranteze();
							c.setEcuatie(ec);
							c.rezultateCalcule();
							g << c;
							cout << c;
							c.serializare(c.getRezultat());
							ID++;
						}
					}
					if (ecuatiaIntrodusa.at(0) == 'E')
					{
						cout << endl << ecuatiaIntrodusa << endl << endl;
					}
					else
					{
						//system("cls");
						cout << "1. Afisare rezultate pe ecran." << endl;
						cout << "2. Stocare rezultate in fisierul output.txt." << endl;
						short int b;
						cin >> b;
						system("cls");
						if (b == 1)
						{
							pc = &c;
							pc->scriere(cout);
						}
						else
						{
							if (b == 2)
							{

								pc = &fc;
								//g << ecuatieInit << "= ";
								pc->scriere(g);
								cout << "Rezultatele se afla in fisierul output.txt" << endl;
							}
						}

					}
					f.close();
					g.close();
				}
				else
				{
					if (a == 3)
					{
						int ID = 1;
						string ecuatiaIntrodusa;


						while (ecuatiaIntrodusa != "exit")
						{
							Ecuatie ec(ID);
							ect = &ec;
							ect->citire(cin);
							ec.noSpaces();
							ec.erori();

							if (ec.getEcuatia()[0] == 'e')
							{
								ecuatiaIntrodusa = "exit";
							}
							else
							{
								if (ec.getEcuatia()[0] == 'E')
								{
									cout << endl << ec.getEcuatia() << endl << endl;
								}
								else
								{
									st.setEcuatie(ec);
									st.separareCifre();
									st.separareSemne();
									
									StringsChoose* sch;
									StringsSign ssgn;
									StringsNr srn;
									sch = &ssgn;
									sch->setStrMk(st);
									sch->afisare();
									sch = &srn;
									sch->setStrMk(st);
									sch->afisare();
									//cout << st;

									c.setStrings(st);
									c.paranteze();
									c.setEcuatie(ec);
									c.rezultateCalcule();
									cout << c;
									c.serializare(c.getRezultat());
									ID++;
								}
							}
						}
						if (ecuatiaIntrodusa.at(0) == 'E')
						{
							cout << endl << ecuatiaIntrodusa << endl << endl;
						}
						else
						{

							system("cls");
							cout << "1. Afisare rezultate pe ecran." << endl;
							cout << "2. Stocare rezultate in fisierul output.txt." << endl;
							short int b;
							cin >> b;
							if (b == 1)
							{
								pc = &c;
								pc->scriere(cout);
							}
							else
							{
								if (b == 2)
								{
									ofstream g("output.txt");
									pc = &fc;
									pc->scriere(g);
									cout << "Rezultatele se afla in fisierul output.txt" << endl;
								}
							}
						}
					}
					else
					{
						system("cls");
						cout << "Executarea s-a incheiat...." << endl;
						break;
					}
					
				}
			}
		}
	
	

}