#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <windows.h>
#include <locale.h>


using namespace std;

int jokerHakki = 1, jokerHakki2 = 1, odul = 0;
string nick;

int odullendirme(int);
bool kontrolFonksiyonu(int[], int, int);
void elemanlariFarkliDizi(int[], int);
void yanlisCevaplariSilme(string[]);
bool ciftCevap(int, string, string);
bool diziyiYazdir(int[], int, int, string, int);
void kurallar();
void girisEkrani();
void listeyeSiralama(string, int);



void listeyeSiralama(string nick, int para) {

	ofstream liste("yarismacilar.txt", ios::out | ios::app);
	liste << nick << "\t" << para << endl;
	liste.close(); 

}

void yanlisCevaplariSilme(string soru[8]) {

	srand(time(0));
	int sayi1, sayi2, dizi[2];
	
	
	sayi1 = rand() % 4 + 2, sayi2 = rand() % 4 + 2;

	while (sayi1 == sayi2 || sayi1 == stoi(soru[7]) || sayi2 == stoi(soru[7]))
	{
		sayi1 = rand() % 4 + 2;
		sayi2 = rand() % 4 + 2;
	}

	soru[sayi1] = "";
	soru[sayi2] = "";

}

bool ciftCevap(int soruNumarasi, string gcevap, string nick) {
	string kcevap;
	int hak = 2;
	cout << soruNumarasi << ". soru için çift cevap jokerinizi kullandýnýz. Cevaplarýnýzý giriniz : \n";
	while (hak > 0)
	{
		cin >> kcevap;
		if (gcevap == kcevap)
		{
		
			cout << "Tebrikler doðru cevap ! " << odullendirme(soruNumarasi - 1) << "TL kazandýnýz ! \n";
			return 1;

		}
		else
		{
			hak--;
			if (hak==1)
			{
				cout << hak << " hakkýnýz kaldý \n";
			}
			else
			{
				if (soruNumarasi >= 2 && soruNumarasi < 8)
				{
					odul = 2000;
					listeyeSiralama(nick, odul);
					cout << "2000 tl baraj ödülünü kazandýnýz. Görüþmek üzere ! ";
					return 0;
				}
				else if (soruNumarasi >= 8)
				{
					odul = 50000;
					listeyeSiralama(nick, odul); 
					cout << "50000 tl baraj ödülünü kazandýnýz. Görüþmek üzere ! ";
					return 0;
				}
				else
				{
					odul = 0;
					listeyeSiralama(nick, odul); 
					cout << "Maalesef hiç ödül kazanamadýnýz. Görüþmek üzere ! ";
					return 0;
				}
				
			}
		}
	}

	return 0;
}

int odullendirme(int sayac) {

	int dizi[12] = { 1000,2000,3000,5000,7500,10000,30000,50000,100000,200000,400000,1000000 };

	return dizi[sayac];

}
bool kontrolFonksiyonu(int dizi[], int sayi, int boyut) {
	for (int i = 0; i < boyut; i++)
	{

		if (dizi[i] == sayi)
		{
			return 0;
		}
	}

	return 1;

}

void elemanlariFarkliDizi(int dizi[], int boyut) {

	srand(time(0));

	int sayi;

	for (int i = 0; i < boyut; i++)
	{
		sayi = rand() % 50 + 1;
		while (!kontrolFonksiyonu(dizi, sayi, i))
		{
			sayi = rand() % 50 + 1;
		}
		dizi[i] = sayi;
	}

}

bool diziyiYazdir(int dizi[], int bas, int son, string dosyaAdi, int sayac) {


	string str;
	string soru[8];
	string gcevap, kcevap;
	
	for (int i = bas + 1; i < son + 1; i++)
	{
		for (int j = bas; j < son; j++)
		{

			ifstream dosya(dosyaAdi, ios::in);
			for (int k = 0; k < dizi[i]; k++)
			{


				if (k != dizi[i] - 1)
				{
					getline(dosya, str);
				}
				else 
				{ 
					for (int l = 0; l < 8; l++)
					{ 
						getline(dosya, str, '#'); 
						soru[l] = str; 
					}
				}

			} 
			dosya.close();

		}

		gcevap = soru[6];
		cout << "\n" << i << ". soru = " << soru[1] << " \n " << "A-)" << soru[2] << "\t\t" << "B-)" << soru[3] << " \n " << "C-)" << soru[4] << "\t\t" << "D-)" << soru[5] << endl;
		cout << "Cevabýnýz Nedir? \n";

		clock_t baslangic1 = clock();
		cin >> kcevap;

		if (kcevap != "A" && kcevap != "B" && kcevap != "C" && kcevap != "D" && kcevap != "K" && kcevap != "L" && kcevap != "Q")
		{

			while (kcevap != "A" && kcevap != "B" && kcevap != "C" && kcevap != "D" && kcevap != "K" && kcevap != "L" && kcevap != "Q")
			{
				cout << "Lütfen geçerli bir cevap giriniz ! \n";
				cin >> kcevap;
			}
		}

		if (kcevap == "Q")
		{
			cout << odullendirme(sayac-1) << " lirayý alarak çekiliyorsunuz. Görüþmek üzere !";
			odul = odullendirme(sayac-1);

			listeyeSiralama(nick, odul); 
			
			return 0;
		}

		if (kcevap == "K")
		{
			if (jokerHakki > 0)
			{


				if (ciftCevap(sayac + 1, gcevap, nick))
				{
					sayac++;
					jokerHakki--;
					Sleep(2000);
					system("CLS");
					continue;
				}
				else
				{
					return 0;
				}
			}
			else
			{

				while (kcevap == "K")
				{
					cout << "Çift cevap joker hakkýnýz kalmadý ! \n Cevabýnýzý giriniz : \n";
					cin >> kcevap;
				}
			}

		}
		if (sayac >= 7)
		{


			if (kcevap == "L")
			{

				if (jokerHakki2 > 0)
				{
					jokerHakki2--;

					system("CLS");
					cout << i << ". soru için yarý yarýya joker hakkýný kullandýnýz. Cevabýnýzý giriniz : \n";
					yanlisCevaplariSilme(soru);
					cout << "\n" << i << ". soru = " << soru[1] << " \n " << "A-)" << soru[2] << "\t\t" << "B-)" << soru[3] << " \n " << "C-)" << soru[4] << "\t\t" << "D-)" << soru[5] << endl;
					cout << "Cevabýnýz Nedir? \n";
					cin >> kcevap;


					if (kcevap == "Q")
					{

						cout << odullendirme(sayac-1) << " lirayý alarak çekiliyorsunuz. Görüþmek üzere !"; 
						odul = odullendirme(sayac-1); 

						listeyeSiralama(nick, odul); 

						return 0;
					}

					if (kcevap == "K") 
					{
						while (kcevap == "K")
						{
							cout << "Þu anda bunu kullanamazsýnýz ! \n Lütfen geçerli bir cevap girin \n";
							cin >> kcevap;
						}

					}

				}
				else
				{

					while (kcevap == "L")
					{
						cout << "Yarý yarýya joker hakkýnýz kalmadý ! \n Cevabýnýzý giriniz : \n";
						cin >> kcevap;
					}
				}
				for (int i = bas; i < son; i++)
				{
					ifstream dosya(dosyaAdi, ios::in);

					for (int j = 0; j < dizi[i]; j++)
					{

						if (j != dizi[i] - 1)
						{
							getline(dosya, str);
						}
						else
						{
							for (int k = 0; k < 8; k++)
							{
								getline(dosya, str, '#');
								soru[k] = str;
							}
						}
					}
					dosya.close();
				}
			}
		}
		else
		{
			if (kcevap == "L")
			{

				while (kcevap == "L")
				{
					cout << "Yarý yarýya jokerini açmadýnýz. Lütfen geçerli bir cevap giriniz ! \n";
					cin >> kcevap;
				}
			}
		}

		clock_t baslangic2 = clock();
		double gecenSure = double(baslangic2 - baslangic1) / CLOCKS_PER_SEC;
		if (sayac < 7)
		{
			if (gecenSure > 30)
			{
				cout << "Maalesef 30 Saniyenin üzerinde cevap verdiniz.\n";

				cout << "0 tl ile oyuna veda ediyorsunuz. Gorusmek uzere !"; 
				odul = 0;

				listeyeSiralama(nick, odul); 

				return 0;
			}
		}
		else
		{
			if (gecenSure > 60)
			{
				cout << "Maalesef 60 Saniyenin üzerinde cevap verdiniz.\n";

				cout << "0 tl ile oyuna veda ediyorsunuz. Gorusmek uzere !"; 
				odul = 0; 

				listeyeSiralama(nick, odul); 

				return 0;
			}
		}




		if (gcevap == kcevap)
		{
			sayac++;
			if (sayac != 12)
			{
				 
				cout << "Tebrikler doðru cevap ! " << odullendirme(sayac - 1) << "TL kazandýnýz ! \n";
				cout << "Sonraki soru geliyor...\n";
			}
			else
			{
				listeyeSiralama(nick, 1000000); 

				for (int i = 0; i < 10; i++)
				{
				
					system("CLS");
					Sleep(1000);
					cout << string(36, '*') << endl;
					cout << "\tMÝLYONER OLDUNUZ !" << endl;
					cout << string(36, '*') << endl;
					Sleep(1000);

				}
			}
		}
		else
		{
			if (sayac >= 2 && sayac < 8)
			{
				odul = 2000;
				listeyeSiralama(nick, odul); 
				cout << "2000 tl baraj ödülünü kazandýnýz. Görüþmek üzere ! ";
				return 0;
			}
			else if (sayac >= 8)
			{
				odul = 50000;
				listeyeSiralama(nick, odul); 
				cout << "50000 tl baraj ödülünü kazandýnýz. Görüþmek üzere ! ";
				return 0;
			}
			else
			{
				odul = 0;
				listeyeSiralama(nick, odul); 
				cout << "Maalesef hiç ödül kazanamadýnýz. Görüþmek üzere ! ";
				return 0;
			}
		}
		Sleep(3000);
		system("CLS");



	}

	

	return 1;

}

void kurallar() {
	cout << "\t KURALLAR\n" << string(26, '-') << endl;
	cout << "-Oyun 12 sorudan oluþmaktadýr.\n-Ýlk 8 soruda 30, son 4 soruda 60 saniyeniz vardýr.\n-'A', 'B', 'C' ve 'D' olmak üzere 4 þýktan birini girmeniz gerekmektedir.\n";
	cout << "-Ýlk sorudan itibaren çift cevap joker hakkýnýz ve 8. sorudan itibaren yarý yarýya joker hakkýnýz kullanýma açýlacaktýr.\n";
	cout << "-Çift cevap joker hakkýnýzý kullanmak için 'K' tuþunu, yarý yarýya joker hakkýnýzý kullanmak için 'L' tuþunu giriniz.\n";
	cout << "-Her jokeri yalnýzca bir kez kullanabilirsiniz.\n";
	cout << "-2. soru ve 8. soru baraj sorularýdýr.\n-Eðer oyundan çekilip geldiðiniz yere kadarki ödülünüzle ayrýlmak isterseniz 'Q' tuþunu giriniz. \n";
}

void girisEkrani() {

	string cevap1;
	cout << "Kim Milyoner Olmak Ýster Oyununa Hoþ Geldiniz ! ";
	Sleep(2000);
	system("CLS");
	cout << "Baþlamadan önce sizi tanýyalým.\nÝsminiz nedir ? ";
	getline(cin, nick);
	system("CLS");
	cout << "Merhaba " << nick << ". Baþlamadan önce oyunun kurallarýný öðrenmelisin...\n";
	Sleep(2500);
	system("CLS");
	kurallar();
	cout << "\nOyuna baþlamaya hazýr mýsýn ? (evet/hayýr) \n";

	cin >> cevap1;

	if (cevap1 != "evet" && cevap1 != "hayýr")
	{
		while (cevap1 != "evet" && cevap1 != "hayýr")
		{
			system("CLS");
			cout << "Lütfen Geçerli Bir Cevap Giriniz ! \n";
			cin >> cevap1;
		}
		if (cevap1 == "evet") {
			system("CLS");
			cout << "Ýþte Ýlk Sorun Geliyor " << nick << ". Baþarýlar...\n";
			Sleep(2000);
			system("CLS");
		}
		else
		{
			system("CLS");
			cout << "Hazýr hissettiðiniz bir zamanda yine bekleriz...";
			exit(1);
		}

	}
	else if (cevap1 == "evet")
	{
		system("CLS");
		cout << "Ýþte ilk sorun geliyor " << nick << ". Baþarýlar...\n";
		Sleep(2000);
		system("CLS");
	}
	else
	{
		system("CLS");
		cout << "Hazýr hissettiðiniz bir zamanda yine bekleriz...";
		exit(1);
	}

}

int main() {

	setlocale(LC_ALL, "Turkish");

	int dizi[12];
	
	elemanlariFarkliDizi(dizi, 12);

	girisEkrani();

	if (!diziyiYazdir(dizi, 0, 4, "kolaySorular.txt", 0))
	{
		exit(1);
	}
	if (!diziyiYazdir(dizi, 4, 8, "ortaSorular.txt", 4))
	{
		exit(1);
	}
	if (!diziyiYazdir(dizi, 8, 12, "zorSorular.txt", 8))
	{
		exit(1);
	}

	
	

	return 0;
}