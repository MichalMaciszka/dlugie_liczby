#include <iostream>

using namespace std;

char* wczytaj() {
	char wejscie = ' ';
	char* liczba = NULL;
	int rozmiar = 0;
	while (wejscie != '\n') {
		scanf("%c", &wejscie);
		liczba = (char*)realloc(liczba, (rozmiar + 1) * sizeof(char));
		liczba[rozmiar] = wejscie;
		rozmiar++;
	}
	liczba[rozmiar - 1] = '\0';
	return liczba;
}

void wypisz(int n, char** liczba) {
	for (int i = 0; i < n; i++) {
		printf("%s", liczba[i]);
		printf("\n");
	}
}

int dlugosc_wyrazu(char wyraz[]) {
	int i = 0;
	while (wyraz[i] != '\0') i++;
	return i;
}

bool porownaj_wyrazy(char wyraz1[], char wyraz2[]) {
	int dl1 = dlugosc_wyrazu(wyraz1);
	int dl2 = dlugosc_wyrazu(wyraz2);
	if (dl1 != dl2) return false;
	else {
		for (int i = 0; i < dl1; i++)
		{
			if (wyraz1[i] != wyraz2[i]) return false;
		}
	}
	return true;
}

bool czy_zawiera(char znak, char wyraz[]) {
	for (int i = 0; i < dlugosc_wyrazu(wyraz); i++) {
		if (wyraz[i] == znak) return true;
	}
	return false;
}

void szukaj_min(char** min, char* liczba) {
	if ((*min)[0] != '-' && liczba[0] != '-') {
		char* x = *min;
		if (dlugosc_wyrazu(*min) < dlugosc_wyrazu(liczba));
		else if (dlugosc_wyrazu(*min) > dlugosc_wyrazu(liczba)) (*min) = liczba;
		else for (int i = 0; i < dlugosc_wyrazu(x); i++) {
			if (x[i] < liczba[i]) return;
			else if (x[i] > liczba[i]) {
				(*min) = liczba;
				break;
			}
		}
	}
	else if ((*min)[0] != '-' && liczba[0] == '-') (*min) = liczba;
	else if ((*min)[0] == '-' && liczba[0] == '-') {
		if (dlugosc_wyrazu((*min)) > dlugosc_wyrazu(liczba));
		else if (dlugosc_wyrazu(liczba) > dlugosc_wyrazu((*min))) (*min) = liczba;
		else for (int i = 0; i < dlugosc_wyrazu(*min); i++) {
			if ((*min)[i] > liczba[i]) break;
			else if (liczba[i] > (*min)[i]) {
				(*min) = liczba;
				break;
			}
		}
	}
}

void szukaj_max(char** max, char* liczba) {
	if (*max[0] != '-' && liczba[0] != '-') {
		if (dlugosc_wyrazu(*max) > dlugosc_wyrazu(liczba)) return;
		else if (dlugosc_wyrazu(liczba) > dlugosc_wyrazu(*max)) (*max) = liczba;
		else for (int i = 0; i < dlugosc_wyrazu(*max) - 1; i++) {
			if ((*max)[i] > liczba[i]) break;
			else if (liczba[i] > (*max)[i]) {
				(*max) = liczba;
				break;
			}
		}
	}
	else if (*max[0] == '-' && liczba[0] != '-') *max = liczba;
	else if (*max[0] == '-' && liczba[0] == '-') {
		if (dlugosc_wyrazu(*max) < dlugosc_wyrazu(liczba));
		else if (dlugosc_wyrazu(liczba) < dlugosc_wyrazu(*max)) *max = liczba;
		else for (int i = 1; i < dlugosc_wyrazu(*max); i++) {
			if ((*max)[i] < liczba[i]) break;
			else if (liczba[i] < (*max)[i]) {
				(*max) = liczba;
				break;
			}
		}
	}
}

int ktora_wieksza(char* liczba1, char* liczba2) {
	int d1 = dlugosc_wyrazu(liczba1);
	int d2 = dlugosc_wyrazu(liczba2);
	if (d1 > d2) return 1;
	else if (d2 > d1) return -1;
	else {
		for (int i = 0; i < d1; i++) {
			if (liczba1[i] > liczba2[i]) return 1;
			else if (liczba2[i] > liczba1[i]) return -1;
		}
	}
	return 1;
}

char* zwroc_najmniejsza(char** liczby, int n) {
	char* min = liczby[0];
	char** min_w = &min;
	for (int i = 1; i < n; i++) {
		szukaj_min(min_w, liczby[i]);
	}
	return (*min_w);
}

char* zwroc_najwieksza(char** liczby, int n) {
	char* max = liczby[0];
	char** max_w = &max;
	for (int i = 1; i < n; i++) {
		szukaj_max(max_w, liczby[i]);
	}
	return *max_w;
}

char* rozszerz(char* napis, int rozmiar, int nowy_rozmiar) {
	char* nowy_napis = (char*)malloc((nowy_rozmiar+1) * sizeof(char));
	nowy_napis[nowy_rozmiar] = '\0';
	while (rozmiar > 0) {
		nowy_napis[nowy_rozmiar - 1] = napis[rozmiar - 1];
		rozmiar--;
		nowy_rozmiar--;
	}
	while (nowy_rozmiar > 0) {
		nowy_napis[nowy_rozmiar - 1] = '0';
		nowy_rozmiar--;
	}
	return nowy_napis;
}

char* dopisz_minus(char* napis, int rozmiar) {
	int nowy_rozmiar = rozmiar + 1;
	char* nowy_napis = (char*)malloc((nowy_rozmiar+1) * sizeof(char));
	nowy_napis[nowy_rozmiar] = '\0';
	while (rozmiar > 0) {
		nowy_napis[nowy_rozmiar - 1] = napis[rozmiar - 1];
		rozmiar--;
		nowy_rozmiar--;
	}
	while (nowy_rozmiar > 0) {
		nowy_napis[nowy_rozmiar - 1] = '-';
		nowy_rozmiar--;
	}
	return nowy_napis;
}


char* pomin_zera(char* napis, int dlugosc) {
	int ile_zer = 0;
	while (napis[ile_zer] == '0') ile_zer++;
	for (int i = 0; i < dlugosc - ile_zer; i++) {
		napis[i] = napis[i + ile_zer];
	}
	napis[dlugosc - ile_zer] = '\0';
	return napis;
}

char* kopiuj(char* wyraz) {
	int d = dlugosc_wyrazu(wyraz);
	char* wynik = new char[d + 1];
	for (int i = 0; i < d; i++) {
		wynik[i] = wyraz[i];
	}
	wynik[d] = '\0';
	return wynik;
}

char* dodawanie(char liczba1[], char liczba2[]) {
	int d1 = dlugosc_wyrazu(liczba1);
	int d2 = dlugosc_wyrazu(liczba2);
	char* wynik;
	if (d1 > d2) {
		liczba2 = rozszerz(liczba2, d2, d1);
		wynik = new char[d1 + 2];
		for (int i = 0; i <= d1; i++) wynik[i] = '0';
		wynik[d1 + 1] = '\0';
		for (int i = d1; i > 0; i--) {
			if ((liczba1[i - 1] + liczba2[i - 1] + wynik[i] - 144) < 10) wynik[i] += liczba1[i - 1] + liczba2[i - 1] - 96;
			else if (((liczba1[i - 1] + liczba2[i - 1] + wynik[i] - 144)) == 10) {
				wynik[i] = '0';
				wynik[i - 1] = '1'; /*+= (liczba1[i - 1] + liczba2[i - 1] - 96) / 10;*/
			}
			else {
				wynik[i] += (liczba1[i - 1] + liczba2[i - 1] - 96) % 10;
				wynik[i - 1] += (liczba1[i - 1] + liczba2[i - 1] - 96) / 10;
			}
		}
	}
	else if (d2 > d1) {
		liczba1 = rozszerz(liczba1, d1, d2);
		wynik = new char[d2 + 2];
		for (int i = 0; i <= d2; i++) wynik[i] = '0';
		wynik[d2 + 1] = '\0';
		for (int i = d2; i > 0; i--) {
			if ((liczba1[i - 1] + liczba2[i - 1] + wynik[i] - 144) < 10) wynik[i] += liczba1[i - 1] + liczba2[i - 1] - 96;
			else if (((liczba1[i - 1] + liczba2[i - 1] + wynik[i] - 144)) == 10) {
				wynik[i] = '0';
				wynik[i - 1] = '1'; /*+= (liczba1[i - 1] + liczba2[i - 1] - 96) / 10;*/
			}
			else {
				wynik[i] += (liczba1[i - 1] + liczba2[i - 1] - 96) % 10;
				wynik[i - 1] += (liczba1[i - 1] + liczba2[i - 1] - 96) / 10;
			}
		}
	}
	else {
		wynik = new char[d2 + 2];
		for (int i = 0; i <= d2; i++) wynik[i] = '0';
		wynik[d2 + 1] = '\0';
		for (int i = d1; i > 0; i--) {
			if ((liczba1[i - 1] + liczba2[i - 1] + wynik[i] - 144) < 10) wynik[i] += liczba1[i - 1] + liczba2[i - 1] - 96;
			else if (((liczba1[i - 1] + liczba2[i - 1] + wynik[i] - 144)) == 10) {
				wynik[i] = '0';
				wynik[i - 1] = '1'; /*+= (liczba1[i - 1] + liczba2[i - 1] - 96) / 10;*/
			}
			else {
				wynik[i] += (liczba1[i - 1] + liczba2[i - 1] - 96) % 10;
				wynik[i - 1] += (liczba1[i - 1] + liczba2[i - 1] - 96) / 10;
			}
		}
	}

	if (wynik[0] == '0') pomin_zera(wynik, dlugosc_wyrazu(wynik));
	return wynik;
}

char* odejmowanie(char liczba1[], char liczba2[]) {
	char* x = kopiuj(liczba1);
	char* y = kopiuj(liczba2);
	int d1 = dlugosc_wyrazu(x);
	int d2 = dlugosc_wyrazu(y);
	int a = ktora_wieksza(x, y);
	char* wynik;
	//bool czy_dodac = false;
	if (d1 > d2) {
		y = rozszerz(y, d2, d1);
		wynik = new char[d1 + 2];
		for (int i = 0; i < d1; i++) wynik[i] = '0';
		wynik[d1] = '\0';
	}
	else if (d2 > d1) {
		x = rozszerz(x, d1, d2);
		wynik = new char[d2 + 2];
		for (int i = 0; i < d2; i++) wynik[i] = '0';
		wynik[d2] = '\0';
	}
	else {
		wynik = new char[d2 + 2];
		for (int i = 0; i < d2; i++) wynik[i] = '0';
		wynik[d2] = '\0';
	}
	if (a == 1) {
		for (int i = dlugosc_wyrazu(wynik) - 1; i >= 0; i--) {
			if (x[i] >= y[i]) {
				wynik[i] = x[i] - y[i] + 48;
				//if (czy_dodac) x[i]++;
				//czy_dodac = false;
			}
			else {
				x[i] += 10;
				x[i - 1] --;
				wynik[i] = x[i] - y[i] + 48;
				x[i] -= 10;
				//if (czy_dodac) x[i]++;
				//czy_dodac = true;
			}

		}
	}
	else if (a == -1) {
		wynik = odejmowanie(y, x);
		wynik = dopisz_minus(wynik, dlugosc_wyrazu(wynik));
	}
	wynik = pomin_zera(wynik, dlugosc_wyrazu(wynik));
	x = liczba1;
	y = liczba2;
	if (porownaj_wyrazy(liczba1, liczba2)) {
		wynik[0] = '0';
		wynik[1] = '\0';
	}
	return wynik;
}

int main()
{
	int n;
	cin >> n;
	getchar();
	char** liczba_w;
	liczba_w = new char* [n];
	for (int i = 0; i < n; i++) {
		liczba_w[i] = wczytaj();
	}
	char min[] = "min";
	char max[] = "max";
	char pokaz[] = "?";
	for (;;) {
		char* akcja = wczytaj();
		char* efekt;
		if (porownaj_wyrazy(akcja, pokaz)) wypisz(n, liczba_w);
		else if (porownaj_wyrazy(akcja, min)) {
			efekt = zwroc_najmniejsza(liczba_w, n);
			printf("%s", efekt);
			printf("\n");
			//free(efekt);
		}
		else if (porownaj_wyrazy(akcja, max)) {
			efekt = zwroc_najwieksza(liczba_w, n);
			printf("%s", efekt);
			printf("\n");
			//free(efekt);
		}
		else if (czy_zawiera('+', akcja)) {
			char* indeks1; char* indeks2; char* indeks3;
			int dl1 = 0, dl2 = 0, dl3 = 0;
			while (akcja[dl1] != ' ') dl1++;
			while (akcja[dl1 + 3 + dl2] != ' ') dl2++;
			while (akcja[dl1 + dl2 + 6 + dl3] != '\0') dl3++;
			indeks1 = new char[dl1];
			indeks2 = new char[dl2];
			indeks3 = new char[dl3];
			for (int i = 0; i < dl1; i++) indeks1[i] = akcja[i];
			for (int i = 0; i < dl2; i++) indeks2[i] = akcja[dl1 + 3 + i];
			for (int i = 0; i < dl3; i++) indeks3[i] = akcja[dl1 + dl2 + i + 6];
			if (liczba_w[atoi(indeks2)][0] != '-' && liczba_w[atoi(indeks3)][0] != '-') {
				liczba_w[(atoi(indeks1))] = dodawanie(liczba_w[atoi(indeks2)], liczba_w[atoi(indeks3)]);
			}
			else if (liczba_w[atoi(indeks2)][0] == '-' && liczba_w[atoi(indeks3)][0] != '-') {
				liczba_w[(atoi(indeks1))] = odejmowanie(liczba_w[atoi(indeks3)], &liczba_w[atoi(indeks2)][1]);
			}

			else if (liczba_w[atoi(indeks2)][0] != '-' && liczba_w[atoi(indeks3)][0] == '-') {
				liczba_w[(atoi(indeks1))] = odejmowanie(liczba_w[atoi(indeks2)], &liczba_w[atoi(indeks3)][1]);
			}
			else if (liczba_w[atoi(indeks2)][0] == '-' && liczba_w[atoi(indeks3)][0] == '-') {
				liczba_w[(atoi(indeks1))] = dodawanie(&liczba_w[atoi(indeks2)][1], &liczba_w[atoi(indeks3)][1]);
				liczba_w[(atoi(indeks1))] = dopisz_minus(liczba_w[(atoi(indeks1))], dlugosc_wyrazu(liczba_w[(atoi(indeks1))]));
			}
		}
		else if (czy_zawiera('-', akcja)) {
			char* indeks1 = NULL; char* indeks2 = NULL; char* indeks3 = NULL;
			int dl1 = 0, dl2 = 0, dl3 = 0;
			while (akcja[dl1] != ' ') dl1++;
			while (akcja[dl1 + 3 + dl2] != ' ') dl2++;
			while (akcja[dl1 + dl2 + 6 + dl3] != '\0') dl3++;
			indeks1 = new char[dl1];
			indeks2 = new char[dl2];
			indeks3 = new char[dl3];
			for (int i = 0; i < dl1; i++) indeks1[i] = akcja[i];
			for (int i = 0; i < dl2; i++) indeks2[i] = akcja[dl1 + 3 + i];
			for (int i = 0; i < dl3; i++) indeks3[i] = akcja[dl1 + dl2 + i + 6];
			if (liczba_w[atoi(indeks2)][0] != '-' && liczba_w[atoi(indeks3)][0] != '-') liczba_w[(atoi(indeks1))] = odejmowanie(liczba_w[atoi(indeks2)], liczba_w[atoi(indeks3)]);
			else if (liczba_w[atoi(indeks2)][0] != '-' && liczba_w[atoi(indeks3)][0] == '-') {
				liczba_w[atoi(indeks1)] = dodawanie(liczba_w[atoi(indeks2)], &liczba_w[atoi(indeks3)][1]);
			}
			else if (liczba_w[atoi(indeks2)][0] == '-' && liczba_w[atoi(indeks3)][0] != '-') {
				liczba_w[atoi(indeks1)] = dodawanie(liczba_w[atoi(indeks3)], &liczba_w[atoi(indeks2)][1]);
				liczba_w[atoi(indeks1)] = dopisz_minus(liczba_w[atoi(indeks1)], dlugosc_wyrazu(liczba_w[atoi(indeks1)]));
			}
			else if (liczba_w[atoi(indeks2)][0] == '-' && liczba_w[atoi(indeks3)][0] == '-') {
				liczba_w[atoi(indeks1)] = odejmowanie(&liczba_w[atoi(indeks3)][1], &liczba_w[atoi(indeks2)][1]);
			}
		}
		else break;
	}
	return 0;
}