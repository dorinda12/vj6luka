//Mjerenje proteklog vremena u tisuæinkama sekundi 
#include <iostream>
#include <fstream>
#include <cstring>
#include <time.h>
using namespace std;
struct tindeks{
	int kljuc;
	int adresa;
};//tindeks
clock_t vrijeme1,vrijeme2;
double razlika;
double vrijeme_pocetak(){
  vrijeme1=clock();
	return (double)vrijeme1;
};
double vrijeme_kraj(){
	vrijeme2=clock();
	return (double)vrijeme2;
};
double vrijeme_proteklo(){
	razlika=vrijeme2-vrijeme1;
	return razlika;
};
//unos znakovnog niza
void unos(char *znakovni_niz)
{
	cin.getline(znakovni_niz, 150);
	if (cin.gcount()==1)
	  	 cin.getline (znakovni_niz,150);
};
void preslozi_indeks(char naziv_ind_dat[], tindeks spremi){
  tindeks indeks,pom;
  int nadjeno=0,brojac=0;
  fstream ind;
  ind.open (naziv_ind_dat,ios::in|ios::out|ios::binary);
  while(1){
    ind.seekg(brojac*sizeof(tindeks));
    brojac++;
    ind.read ((char *)&indeks,sizeof(tindeks));
    if (ind.eof())break;
    if ((indeks.kljuc>spremi.kljuc)&&(nadjeno==0)){
      nadjeno=1;
      ind.seekp((int)ind.tellg()-sizeof(tindeks));
      ind.write ((char *)&spremi,sizeof(tindeks));
      memcpy (&pom,&indeks,sizeof(tindeks));//spremanje tekuæeg zapisa
    }else if (nadjeno==1){
      ind.seekp((int)ind.tellg()-sizeof(tindeks));
      ind.write ((char *)&pom,sizeof(tindeks));
      memcpy (&pom,&indeks,sizeof(tindeks));//spremanje tekuæeg zapisa
    }//else
  }//while
  ind.close();ind.clear();
};//preslozi_indeks
int pretrazivanje_zapisa(char naziv_ind_dat[],int kljuc){// binarno pretraživanje zapisa
  tindeks indeks;
  int brojac=0, N,GORE,DOLJE,POZ;
  //1.utvrditi koliko je zapisa veæ u datoteci
  fstream ind;
  ind.open (naziv_ind_dat,ios::in|ios::binary);
  if (!ind){
    return -1;
  } else { // datoteka postoji
    ind.seekg (0, ios::end);
    N=ind.tellg()/sizeof(tindeks);
    ind.close();ind.clear();
  }
  ind.open (naziv_ind_dat,ios::in|ios::binary);
  DOLJE=0;GORE=N;
  while (1){
    POZ=(GORE+DOLJE)/2;
    ind.seekg(POZ*sizeof(tindeks));
    ind.read ((char *)&indeks, sizeof(tindeks));
    brojac++;
    if (indeks.kljuc==kljuc){
      return indeks.adresa; // vraæa adresu u matiènoj datoteci
    }//if
    if (kljuc>indeks.kljuc)
      DOLJE=POZ;
    else
      GORE=POZ;
    if (POZ==(GORE+DOLJE)/2)break;
  }//while
  ind.close();ind.clear();
  return -1; // zapis nije pronaðen
};//pretrazivanje_zapisa
void stanje_dat_objekta(fstream &dat){  //argument tipa fstream mora biti referenca!
  cout << "-----<Stanje datotecnog objekta>-----" << endl;
  if (dat.is_open() == false){
    cout << "Datoteka nije otvorena!" << endl;
    return;
    }

  cout << "Datotecni pokazivac za citanje: " << dat.tellg() << endl;
  cout << "Datotecni pokazivac za upis: " << dat.tellp() << endl;
  if (dat.eof()){
    cout << "Kraj datoteke!" << endl;
  }
  if (dat.good()){
    cout << "Datoteka je spremna za upis/citanje." << endl;
  } else {
    cout << "Datoteka trenutno nije spremna za upis/citanje." << endl;
  }
  cout << "Stanje zastavice pogreske: " << dat.rdstate() << endl;

  int pamti=dat.tellg();
  dat.seekg (0, ios::end); // relativna pozicija u odnosu na kraj datoteke
  cout << "Velicina datoteke (b): " << dat.tellg() << endl;
  dat.seekg(pamti);
};//stanje_dat_objekta

