// MD5:RaCoUtVyWzpwQHPewO7tOQ==// Verifikator 4.07// Program:vjezba6// Pocetno vrijeme: 17:30 (internetsko) Završno vrijeme: 19:00 Preostalo: 7 +// Opis zadatka:unos u indeksiranu datoteku,pretrazivanje u indeksnoj datoteci prema primarnom kljucu, ispis sadrzaja maticne datoteke u redoslijedu primarnog kljuca, statistika...// Autor:Luka Pavlak// Pocetno vrijeme:11/23/2020 5:30:52 PM// Završno vrijeme:11/23/2020 6:52:58 PM// Identifikatori:dat,ind,main,izbor,brojzapisa,primarnikljuc,t_predmet,rednibroj,sifrapredmeta,naziv[50],sifrasmjera,brojprijaba,vrijemeunosa,kreiraj,cout<<"Broj,brojprijava,unos,predmet,brojaczapisa,*,dat.close,indeks.kljuc,ind.write,ispis,cout<<"Redni,statistika,brojac,avgkljuceva,zbrojkljuceva,if,pretrazivanje,pronaden// IP:fe80::9e:9f8f:5634:2d01%3 ( 5550 )// #:#include <iostream>[B],#include <fstream>[B],#include <cstring>[B],#include <time.h>[B],#include<iostream>,#include<iomanip>,#include<fstream>,#include"biblioteka_vrijeme_i_binarno_pretrazivanje.cc",// Uspješnih/neuspješnih prevodenja:47/11#include<iostream>
#include<iomanip>
#include<fstream>
#include"biblioteka_vrijeme_i_binarno_pretrazivanje.cc"

using namespace std;
fstream dat,ind;

struct t_predmet{
	int rednibroj;
	int sifrapredmeta;
	char naziv[50];
	int sifrasmjera;
	int brojprijava;

	
};

void unos(){
	t_predmet predmet;
	tindeks indeks;
	int brojaczapisa;
	ind.open("grupa04.ind", ios::in|ios::binary);
	while(1){
		ind.read((char*)&indeks,sizeof(tindeks));
		if(ind.eof()||indeks.kljuc==0) break;
		cout<<"Kljuc:"<<indeks.kljuc<<";adresa:"<<indeks.adresa<<endl;
		
		}
		dat.open("grupa03.dat", ios::in | ios::binary);
		if(!dat){
			brojaczapisa=0;
			dat.open("grupa03.dat",ios::out|ios::binary);
			ind.open("grupa04.ind",ios::out | ios::binary);
		}else{
			dat.seekg(0,ios::end);
			brojaczapisa=dat.tellg()/sizeof(t_predmet);
			dat.close();
			dat.clear();
			dat.open("grupa03.dat", ios::out | ios::in | ios::ate |ios::binary);
			ind.open("grupa04.ind",ios::out|ios::in|ios::ate|ios::binary);
			
		}
		brojaczapisa++;
		predmet.rednibroj=brojaczapisa;
		cout<<"Sifra predmeta:";cin>>predmet.sifrapredmeta;
		cout<<"Naziv predmeta:";unos(predmet.naziv);
		cout<<"Sifrra smjera:";cin>>predmet.sifrasmjera;
		cout<<"Broj prijava:";cin>>predmet.brojprijava;
		
		dat.write((char*)&predmet, sizeof(t_predmet));
		indeks.kljuc=predmet.sifrapredmeta;
		indeks.adresa=(int)dat.tellp()-sizeof(t_predmet);
		ind.write((char*)&indeks,sizeof(tindeks));
		dat.close();
		dat.clear();
		ind.close();
		ind.clear();
		preslozi_indeks((char *)"grupa04.ind",indeks);
		
}
void ispis(){
	t_predmet predmet;
	tindeks indeks;
	dat.open("grupa03.dat", ios::in | ios::binary);
	if(!dat){
		cout<<"Datoteka ne postoji, unesite sadrzaj."<<endl;
		return;
	}
	ind.open("grupa04.ind", ios::in | ios::binary);
	while(1){
		ind.read((char*)&indeks,sizeof(tindeks));
		if(ind.eof())break;
		dat.seekg(indeks.adresa);
		dat.read((char*)&predmet,sizeof(t_predmet));
		cout<<"Redni broj:"<<predmet.rednibroj<<endl;
		cout<<"Sifra predmeta:"<<predmet.sifrapredmeta<<endl;
		cout<<"Naziv:"<<predmet.naziv<<endl;
		cout<<"Sifra smjera:"<<predmet.sifrasmjera<<endl;
		cout<<"Broj prijava:"<<predmet.brojprijava<<endl;
	}
	dat.close();
	dat.clear();
	ind.close();
	ind.clear();
	
}
void statistika(){
	t_predmet predmet;
	int brojac=0;
	double avgkljuceva=0;
	int zbrojkljuceva=0;
	dat.open("grupa03.dat",ios::in |ios::binary);
	while(1){
		dat.read((char*)&predmet,sizeof(t_predmet));
		if(dat.eof()) break;
		zbrojkljuceva+=predmet.sifrapredmeta;
		brojac++;
	}
	avgkljuceva=(double)zbrojkljuceva/brojac;
	cout<<"Aritmeticka sredina kljuceva:"<<avgkljuceva<<endl;
	cout<<"UKUPAN zbroj zapisa::"<<brojac<<endl;
	dat.close();
	dat.clear();
}

void pretrazivanje(int sifrapredmeta){
	t_predmet predmet;
	tindeks indeks;
	int brojac=0,n,gore,dolje,poz;
	bool pronaden=false;
	dat.open("grupa03.dat", ios::in | ios::binary);
	if(!dat){
		cout<<"Datoteka ne postoji, unesite sadrzaj."<<endl;
		return;
	}else{
		dat.seekg(0,ios::end);
		n=dat.tellg()/sizeof(t_predmet);
		dat.close();
		dat.clear();
	}
	dat.open("grupa03.dat", ios::in|ios::binary);
	ind.open("grupa04.ind",ios::in|ios::binary);
	dolje=0;
	gore=n;
	while(1){
		poz=(gore+dolje)/2;
		ind.seekg(poz*sizeof(tindeks));
		ind.read((char*)&indeks,sizeof(tindeks));
		brojac++;
		if(indeks.kljuc==sifrapredmeta){
			dat.seekg(indeks.adresa);
			dat.read((char*)&predmet,sizeof(t_predmet));
			pronaden=true;
			cout<<"Redni broj:"<<predmet.rednibroj<<endl;
			cout<<"Sifra predmeta:"<<predmet.sifrapredmeta<<endl;
			cout<<"Naziv predmeta:"<<predmet.naziv<<endl;
			cout<<"Sifra smjera:"<<predmet.sifrasmjera<<endl;
			cout<<"Broj prijava:"<<predmet.brojprijava<<endl;
			break;
		}
		if(sifrapredmeta>indeks.kljuc)dolje=poz;
		else gore=poz;
		if(poz==(gore+dolje)/2)break;
	}
	dat.close();
	dat.clear();
	ind.close();
	ind.clear();
	if(!pronaden)cout<<"Sifra nije pronadena."<<endl;
	
}
 int main(){
	int izbor=0;
	int brojzapisa=0;
	int primarnikljuc=0;
	char kreiraj;
	do{
	dat.open("grupa03.dat", ios::in|ios::binary);
	if(!dat){
		cout<<"Datoteka ne postoji, zelite li ju kreirati d/n?"<<endl;
		cin>>kreiraj;
		if(kreiraj=='d'){
			brojzapisa=0;
			dat.open("grupa03.dat",ios::out|ios::binary);
			ind.open("grupa04.ind", ios::out | ios::binary);
			
	 }
 	
	}
	else{
			dat.seekg(0,ios::end);
			brojzapisa=dat.tellg()/sizeof(t_predmet);
			cout<<"Broj zapisa u datoteci:"<<brojzapisa<<endl;
			dat.close();
			dat.clear();
			break;
	}
	}while(kreiraj!= 'd');
	
	do{
		cout<<"IZBORNIK"<<endl;
		cout<<"Unesite 1 za rucni unos podataka u maticnu i indeksiranu datoteku."<<endl;
		cout<<"Unesite 2 za pretrazivanje indeksirane datoteke prema primarnom kljucu."<<endl;
		cout<<"Unesite 3 za ispis sadrzaja maticne datoteke uz pomoc indeksirane datoteke u redoslijedu primarnog kljuca."<<endl;
		cout<<"UNesite 4 za statistiku."<<endl;
		cout<<"unesite 9 za izlaz."<<endl;
		cin>>izbor;
		switch(izbor){
			case 1:unos();break;
			case 2:cout<<"Unesite primarni kljuc:";cin>>primarnikljuc;pretrazivanje(primarnikljuc);break;
			case 3:ispis();break;
			case 4:statistika();break;
			case 9:break;
			default:cout<<"Opcija ne postoji."<<endl;break;
		}
	}while(izbor!=9);
	
	return 0;
}
