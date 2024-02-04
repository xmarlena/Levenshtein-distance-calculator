//sekcja dokumentacji

/*
*
Algorytm okreslaj¹cy stopien podobienstwa tekstu za pomoca odleglosci Levenshtaine'a
Projekt zrealizowany na rzecz przedmiotu Programowanie Komputerów.

Autorzy: Dawid Serek, Marlena Sadowska
Wydzial: Zarzadzania
Kierunek: Informatyka i Ekonometria
Ostatnia data edycji: 27/05/2023

*/


//sekcja preprocesora
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void test_levenshtein();


//funkcja main
int main() {
	test_levenshtein();
	return 0;
}


// czesc wykonana przez Dawida
float levenshtein(char* text1, char* text2, int** t, int n, int m) {
	//przygotowanie macierzy
	for (int i = 0; i < n; i++)
		t[i][0] = i;
	for (int i = 0; i < m; i++)
		t[0][i] = i;

	//wyliczanie dla danych prefiksow dlugosci Levenshteina za pomoca programowania dynamicznego
	int i1, j1;
	for (int i = 1; i < n; i++)
	{
		i1 = i - 1;
		for (int j = 1; j < m; j++)
		{
			j1 = j - 1;
			t[i][j] = min(t[i - 1][j] + 1, min(t[i][j - 1] + 1, t[i - 1][j - 1] + (int)(text1[i - 1] != text2[j - 1])));
		}
	}

	//podobienstwo zwrocone jako iloraz dlugosci Levenshteina dla danej pary oraz minimalnej dlugosci ze slow
	n--;
	m--;
	float numerator = (float)max(n, m) - (float)t[n][m];
	float similarity = numerator / (float)max(n, m) * 100.0f;

	return similarity;
}


// czesc wykonana przez Marlene
void test_levenshtein() {
	//wczytanie danych
	char text1[5000], text2[5000];
	printf("Maksymalna dlugosc tekstow to 5000 znakow.\n\n");

	printf("Podaj pierwszy tekst:\n");
	gets_s(text1, (unsigned int)sizeof(text1));
	printf("Podaj drugi tekst:\n");
	gets_s(text2, (unsigned int)sizeof(text2));

	//sprawdzanie dlugosci tekstow
	int n = (int)strlen(text1) + 1;
	int m = (int)strlen(text2) + 1;

	if (n == 1 || m == 1) {
		printf("Blad wprowadzania danych.");
		return;
	}

	// alokowanie pamieci dla macierzy
	int** t = malloc(n * sizeof(*t));
	if (t == NULL) return;
	for (int i = 0; i < n; i++) {
		t[i] = malloc(m * sizeof(*t));
		if (t[i] == NULL) {
			for (int j = 0; j < i; j++) free(t[i]);
			free(t);
			return;
		}
	}

	float similarity = levenshtein(text1, text2, t, n, m);
	printf("Stopien podobienstwa: %f%c", similarity, '%');

	// zwalnianie pamieci
	for (int i = 0; i < n; i++) free(t[i]);
	free(t);
}


