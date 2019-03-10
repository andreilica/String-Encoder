#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 69 // Dimensiunea string-ului citit
#define ASCII_M 32 // Codul ASCII minim al caracterului ce poate fi citit de program
#define CHARSET_LENGTH 95 // Diferenta dintre 132 si 32 (cod ASCII) 	

/** Structura folosita pentru rearanjarea mesajului **/

struct piece{
	char *sstring;
	double cp;
};


/** Functie care verifica daca string-ul introdus reprezinta un caracter **/

int check_caracter(char *s)
{
	int length = strlen(s);
	if(length == 1 && isdigit(s[0]) == 0)
		return 1;
	else
		return 0;
}

/** Functie care verifica daca string-ul introdus reprezinta un numar **/

int check_number(char *s)
{
	int i;
	for(i = 1; i < strlen(s); i++)
		if (isdigit(s[i]) == 0)
			return 0;
	if (s[0] != '-' && isdigit(s[0]) == 0)
		return 0;
	if (s[0] == '-' && strlen(s) == 1)
		return 0;
	return 1;

}

/** Functie care inverseaza un string primit ca parametru **/ 

char *str_reverse(char *s)
{
	int i = strlen(s) - 1, j = 0;
	char ch;
	while (i > j)
	{
		ch = s[i];
		s[i] = s[j];
		s[j] = ch;
		i--;
		j++;
	}
	return s;
}

/** Functie care calculeaza cel mai mare divizor al numarului de caractere ale string-ului citit **/

int divisor(char *s)
{
	int i, length = strlen(s);
	int divisor;
	for (i = 1; i < length; i++)
		if (length % i == 0)
			divisor = i;
	return divisor;
}

/** Functie care elimina primele n caractere din string-ul primit ca parametru **/

void cut(char *s, int n)
{
	int length = strlen(s);
	if (n > length)
		return;
	memmove(s, s+n, length - n + 1);
} 

/** Functie de codificare a cuvintelor **/

void word_edit(char *s)
{	
	int divisor_i = divisor(s), i, flag = 0;
		for (i = 0; i < strlen(s);i++)
			if (isdigit(s[i]) != 0)
			{
				flag = 1;
				break;
			}

		if (flag)
			str_reverse(s+divisor_i);
		strncat(s,s,divisor(s));
		cut(s,divisor_i);
}

/** Functie de codificare a numerelor **/

void number_edit(char *s)
{
	int i;
	char aux[50];
	if (s[0] != '-')
	{
		strcpy(aux,s);
		for (i = 0; i < strlen(s); i++)
		{
			strncat(s,s,1);
			cut(s,1);
			if (strcmp(s,aux) > 0)
				strcpy(aux,s);
		}
	}
	else
	{
		cut(s,1);
		strcpy(aux, s);
		for (i = 0; i < strlen(s); i++)
		{
			strncat(s,s,1);
			cut(s,1);
			if (strcmp(s,aux) < 0)
				strcpy(aux,s);
		}
	}
	strcpy(s,aux);

}

/** Functie care returneaza caracterul cu cele mai putine aparitii din mesajul final **/

char find_minchar(char *mesaj)
{
	int length = strlen(mesaj);
	int i, min = length + 1, min_p = 0;
	int *frecv;
	frecv = (int*) calloc(CHARSET_LENGTH, sizeof(int));
	for( i = 0; i < length; i++)
		frecv[mesaj[i] - ASCII_M]++;
	for( i = 0; i < CHARSET_LENGTH; i++)
		if (frecv[i] >= 1)
		{
			if ((min > frecv[i]) || ((min == frecv[i]) && (strchr(mesaj, min_p + ASCII_M) > strchr(mesaj, i + ASCII_M))))
			{
				min = frecv[i];
				min_p = i;
			}
		}
	free(frecv);
		return (min_p + ASCII_M);
}

/** Functie care returneaza caracterul cu cele mai multe aparitii din mesajul final **/

char find_maxchar(char *mesaj)
{
	int length = strlen(mesaj);
	int i, max = 0, max_p = 0;
	int *frecv;
	frecv = (int*) calloc(CHARSET_LENGTH, sizeof(int));
	for (i = 0; i < length; i++)
		frecv[mesaj[i] - ASCII_M]++;
	for (i = 0; i < CHARSET_LENGTH; i++)
			if ((max < frecv[i]) || ((max == frecv[i]) && (strchr(mesaj, max_p + ASCII_M) > strchr(mesaj, i + ASCII_M))))
			{
				max = frecv[i];
				max_p = i;
			}
	free(frecv);
		return (max_p + ASCII_M);
}

/** Functie de codificare a caracterelor **/

void char_edit(char *mesaj, char *s)
{
	s[1] = s[0];
	s[0] = find_maxchar(mesaj);
	s[2] = find_minchar(mesaj);
	s[3] = '\0';
}

/** Functie care calculeaza complexiatatea fiecarui string din structura **/

double complexity(char *s)
{
	int i;
	double sum = 0;
	unsigned int length = strlen(s);
	double cp;
	if (length == 0)
		return 0;
	for (i = 0; i < length; i++)
		sum = sum + s[i];
	cp = sum / length;
	return cp;
}

/** Functie care sorteaza descrescator string-urile din structura **/

void struct_sort(struct piece* pieces, int n)
{
	int flag = 1, i;
	struct piece aux;
	while (flag)
	{
		flag = 0;
		for (i = 0; i < n - 1; i++)
		{
			if (pieces[i].cp < pieces[i + 1].cp)
			{
				aux = pieces[i];
				pieces[i] = pieces[i + 1];
				pieces[i + 1] = aux;
				flag = 1;
			}
			else
				if (pieces[i].cp == pieces[i + 1].cp && strcmp(pieces[i].sstring, pieces[i + 1].sstring) > 0)
				{
					aux = pieces[i];
					pieces[i] = pieces[i + 1];
					pieces[i + 1] = aux;
					flag = 1;
				}
		}
	}
}

/** Functie care rearanjeaza string-urile din structura dupa algoritmul dorit **/

char* rearrangement(struct piece* pieces, int n)
{

	unsigned int length = 0;
	int i = n - 1, j = 0;

	for (i = 0; i < n; i++)
	{
		length = length + strlen(pieces[i].sstring);
	}

	char *s = (char*) calloc(length + 1, sizeof(char));
	
	i = n - 1;
	while (i > j)
	{
		strcat(s, pieces[j].sstring);
		strcat(s, pieces[i].sstring);
		i--;
		j++;
	}

	if (i == j)
	{
		strcat(s, pieces[i].sstring);
	}

	return s;
}


int main()
{
	int n = 0;
	int words = 0, chars = 0, numbers = 0;
	char mesaj[5000] = "";
	char string[SIZE];
	char string_n[SIZE];
	struct piece* pieces;
	fgets(string, SIZE, stdin);
	string[strlen(string) - 1] = '\0';
	if (strcmp(string, "END") != 0)
	{
		do
		{
			fgets(string_n, SIZE, stdin);
			string_n[strlen(string_n) - 1] = '\0';
			if (strcmp(string_n, "END") != 0 && strcmp(string_n, "") != 0) 
			{
				/** Verificare natura string **/ 

				if (check_caracter(string))
				{
						chars++;
						if (strcmp(mesaj, "") == 0)
						{
							strcat(mesaj,string);
						}
						else
						{
							char_edit(mesaj,string);
							strcat(mesaj, string);
						}
				}
				else
					if (check_number(string))
					{
						numbers++;
						number_edit(string);
						strcat(mesaj,string);
					}	
					else
					{
							
							words++;
							word_edit(string);
							strcat(mesaj,string);
					}
			}
			else
				n = atoi(string); 
			strcpy(string, string_n);
		}while (strcmp(string, "END") != 0);
	}
	printf("%d %d %d\n", words, chars, numbers); // Numarul de cuvinte, caractere si numere din string-urile citite
	printf("%s\n", mesaj); // Mesajul codificat inainte de rearanjare

	/** Rearanjare **/

	if (n == 0)
		return 0;

	int length = strlen(mesaj);
	int length_p = length / n;
	int i;
	char* mesaj_rearanjat;

	pieces = (struct piece*) calloc(n, sizeof(struct piece));  // Alocare dinamica a structurii
	int max_length = length - length_p * (n - 1) + 1;

	for (i = 0; i < n; i++)
		pieces[i].sstring = (char *) malloc(max_length * sizeof(char)); // Alocare dinamica a fiecarui string din structura

	for (i = 1; i < n; i++)
	{
		strncpy(pieces[i-1].sstring, mesaj + length_p * (i - 1), length_p);
		pieces[i - 1].sstring[length_p] = '\0';
	}

	strcpy(pieces[n - 1].sstring, mesaj + length_p * (n - 1));
	pieces[n - 1].sstring[max_length - 1] = '\0';

	for (i = 0; i < n; i++)
		pieces[i].cp = complexity(pieces[i].sstring);

	struct_sort(pieces, n); // Sortarea structurii create

	mesaj_rearanjat = rearrangement(pieces, n); // Crearea mesajului rearanjat
	printf("%s\n", mesaj_rearanjat);

	/** Eliberare de memorie alocata dinamic **/

	for (i = 0; i < n; i++)
		free(pieces[i].sstring);

	free(pieces);
	free(mesaj_rearanjat);

		return 0;
}