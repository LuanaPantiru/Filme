#include <iostream>
using namespace std;
class Nod
{
protected:
	int info;
public:
	Nod(int info) { this->info = info; }
	int geti() { return info; }
	~Nod() {}
};
class Nod_ABC :public Nod
{
	Nod_ABC *st;
	Nod_ABC *dr;
public:
	Nod_ABC(int info = 0) :Nod(info) {}
	void add(Nod_ABC *rad, int x);
	Nod_ABC *gets() { return st; }
	Nod_ABC *getd() { return dr; }
	friend class ABC;
	~Nod_ABC() { delete st; delete dr; }
};
class Nod_fiu_frate :public Nod
{
	int copii;
	Nod *leg[10];
public:
	Nod_fiu_frate(int copii = 0, Nod *leg1[10] = NULL, int info=0) :Nod(info)
	{
		this->copii = copii;
		for (int i = 0; i < copii; i++)
		{
			leg[i] = new Nod(leg1[i]->geti());
		}
	}
	int getc() { return copii; }
	void formare(Nod_ABC *nod, Nod_fiu_frate *&lista);
	void vizualizare(Nod_fiu_frate *lista);
	Nod_fiu_frate operator =(Nod_fiu_frate *lista);
	~Nod_fiu_frate() {
		for (int i = 0; i < copii; i++)
			delete leg[i];
	}
};
class Arbori
{
public:
	virtual void afisare(ostream &o) = 0;
};
class ABC :public Arbori
{
	Nod_ABC *rad;
public:
	friend istream & operator >> (istream &i, ABC &abc);
	void SRD(const Nod_ABC *rad);
	void RSD(const Nod_ABC *rad);
	void SDR(const Nod_ABC *rad);
	void afisare(ostream &o)
	{
		cout << "Inordine: ";
		SRD(rad);
		cout << endl << "Preordine: ";
		RSD(rad);
		cout << endl << "Postordine: ";
		SDR(rad);
	}
	friend class AB_oarecare;
};
class AB_oarecare :public Arbori
{
	Nod_fiu_frate *lista;
	ABC abc;
public:
	AB_oarecare operator =(ABC &abc);
	void rsd(Nod_ABC *rad,Nod_fiu_frate *lista);
	void afisare(ostream &o)
	{
		rsd(abc.rad, lista);
	}
};
void Nod_ABC::add(Nod_ABC *rad, int x)
{
	Nod_ABC *aux;
	if (rad->info > x)
	{
		if (rad->st == NULL)
		{
			aux=new Nod_ABC(x);
			rad->st = aux;
		}
		else add(rad->st, x);
	}
	else if(rad->info < x)
	{
		if (rad->dr == NULL)
		{
			aux = new Nod_ABC(x);
			rad->dr = aux;
		}
		else add(rad->dr, x);
	}
}
Nod_fiu_frate Nod_fiu_frate::operator=(Nod_fiu_frate *lista)
{
	copii = lista->getc();
	info = lista->info;
	for (int i = 0; i < copii; i++)
		leg[i] = lista->leg[i];
	return *this;
}
void Nod_fiu_frate::formare(Nod_ABC *rad, Nod_fiu_frate *&lista)
{
	Nod *v[10];
	//if (lista != NULL) delete[]lista;
	if (rad->gets()== NULL || rad->getd() == NULL)
	{
		if (rad->gets() == NULL && rad->getd() == NULL)
			lista = new Nod_fiu_frate(0, 0, rad->geti());
		else if (rad->gets() != NULL)
		{
			v[0] = new Nod(rad->gets()->geti());
			lista = new Nod_fiu_frate(1, v, rad->geti());
		}
		else if (rad->getd() != NULL)
		{
			v[0] = new Nod(rad->getd()->geti());
			lista = new Nod_fiu_frate(1, v, rad->geti());
		}
	}
	else
	{
		v[0] = new Nod(rad->gets()->geti());
		v[1] = new Nod(rad->getd()->geti());
		lista = new Nod_fiu_frate(2, v, rad->geti());
	}
}
istream &operator >>(istream &i, ABC &abc)
{
	int n;
	int x;
	if (abc.rad != NULL)
		delete &abc;
	cout << "Numarul de noduri este: ";
	cin >> n;
	cout << "Nodurile sunt: ";
	for (int j = 0; j < n; j++)
	{
		i >> x;
		if (j == 0)
		{
			abc.rad = new Nod_ABC(x);
		}
		else abc.rad->add(abc.rad, x);
	}
	return i;
}
void ABC::SRD(const Nod_ABC *rad)
{
	if (rad!=NULL)
	{
		SRD(rad->st);
		cout<< rad->info<<" ";
		SRD(rad->dr);
	}
}
void ABC::RSD(const Nod_ABC *rad)
{
	if (rad != NULL)
	{
		cout << rad->info << " ";
		RSD(rad->st);
		RSD(rad->dr);
	}
}
void ABC::SDR(const Nod_ABC *rad)
{
	if (rad != NULL)
	{
		SDR(rad->st);
		SDR(rad->dr);
		cout << rad->info << " ";
	}
}
void Nod_fiu_frate::vizualizare(Nod_fiu_frate *lista)
{
	int n = lista->copii;
	if (n == 0)
	{
		cout << endl << lista->info << " este nod frunza";
	}
	else
	{
		cout << endl << "Nodul " << lista->info << " are urmatorii copii: ";
		for (int i = 0; i < n; i++)
		{
			cout << lista->leg[i]->geti()<<" ";
		}
	}
	
}
AB_oarecare AB_oarecare::operator =(ABC &abc)
{
	this->abc = abc;
	return *this;
}
void AB_oarecare::rsd(Nod_ABC *rad, Nod_fiu_frate *lista)
{
	if (rad != NULL)
	{
		lista->formare(rad, lista);
		lista->vizualizare(lista);
		rsd(rad->gets(), lista);
		rsd(rad->getd(), lista);
	}
}
ostream & operator << (ostream &o, Arbori &a)
{
	a.afisare(o);
	return o;
}
int main()
{
	ABC abc;
	cin >> abc;
	cout << abc;
	AB_oarecare ab;
	ab = abc;
	cout << ab;
	return 0;
}

