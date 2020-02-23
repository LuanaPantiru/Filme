#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Film
{
	string titlu,tip;
	double durata;
	double cost;
public:
	double get_c() { return cost; }
	string get_t() { return titlu; }
	void set_c(double c) { cost = c; }
	Film(string titlu="", string tip="", double durata=0,double cost=0)
	{
		this->titlu=titlu;
		this->tip=tip;
		this->durata = durata;
		this->cost = cost;
	}
	~Film()
	{
		titlu.clear();
		tip.clear();
		durata = 0;
		cost = 0;
	}
	Film operator=(Film f);
	friend istream & operator >> (istream &i, Film &f);
	friend ostream & operator << (ostream &o, Film &f);
};
int cautare(vector<Film*>f, string x)
{
	int l = f.size();
	for (int i = 0; i < l; i++)
		if (f[i]->get_t() == x) return i;
	return -1;
}
class Personal
{
protected:
	string titlu_f;
	string cnp;
	string nume;
	int rol;
public:
	string get_t() { return titlu_f; }
	string get_c() { return cnp; }
	int get_r() { return rol; }
	Personal(string titlu_f="", string cnp="", string nume="",int rol=0)
	{
		this->titlu_f = titlu_f;
		this->cnp=cnp;
		this->nume=nume;
		this->rol = rol;
	}
	~Personal()
	{
		titlu_f.clear();
		cnp.clear();
		nume.clear();
		rol = 0;
	}
	virtual double salar(Film *f,double s)
	{
		if(rol==-2) return 0.05*f->get_c();
		if(rol==-1) return 0.1*f->get_c() + s;
		if(rol==1) return 2*0.1*f->get_c();
		return 0.1*f->get_c();
	}
	virtual void citire(istream &i)
	{
		cout << "|NUME CNP FILM ROL|";
		cin >> nume >> cnp >> titlu_f>>rol;
	}
	virtual void afisare(ostream& o)
	{
		cout << nume << " " << cnp;
	}
};
class Actor:public Personal
{
	unsigned n;
public:
	void set_n(unsigned x) { n = x; }
	Actor(string titlu_f="", string cnp="", string nume="", unsigned n=0) :Personal(titlu_f,cnp,nume) 
	{
		this->n = n;
	}
	void citire(istream &i)
	{
		cout << "|NUME CNP FILM|";
		cin >> nume >> cnp >> titlu_f;
		cout << "Este personaj principal? 0/1";
		cin >> n;
	}
	void afiseaza(ostream &o)
	{
		cout << nume << " " << cnp;
		if (n == 1) cout << " personaj principal";
		else cout << " personaj";
	}
	
};
class Regizor :public Personal
{ 
	double salar_fix;
public:
	void set_s(double s) { salar_fix = s; }
	Regizor(string titlu_f="", string cnp="", string nume="",double salar_fix=0):Personal(titlu_f, cnp, nume)
	{
		this->salar_fix = salar_fix;
	}
	void citire(istream &i)
	{
		cout << "|NUME CNP FILM|";
		cin >> nume >> cnp >> titlu_f;
		cout << "Salariu fix este: ";
		cin >> salar_fix;
	}
	void afisare(ostream &o)
	{
		cout << nume << " " << cnp << " " << titlu_f<<" "<<salar_fix<<" RON";
	}
}; 
istream & operator>>(istream & i, Personal & p)
{
	p.citire(i);
	return i;
}
ostream & operator<<(ostream & o, Personal & p)
{
	p.afisare(o);
	return o;
}
template <class T> class FirmaDistributie
{
	static T nrpers;
	static T nractor;
	vector <Film *> movie;
	vector <Personal*> pers;
public:
	void add_film()
	{
		Film *f=new Film;
		cin >> (*f);
		movie.push_back(f);
	}
	void add_pers()
	{
		Personal *p=new Personal;
		cin >> (*p);
		pers.push_back(p);
		try {
			if (p->get_c().size() != 13) throw 13;
			else throw p;
		}
		catch (Personal* y)
		{
			if (cautare(movie, y->get_t())==-1)
			{
				cout << "Datele pentru filmul " << y->get_t();
				string tip;
				double durata;
				double cost;
				cin >> tip >> durata >> cost;
				Film *f = new Film(y->get_t(), tip, durata, cost);
				movie.push_back(f);
			}
			nr_angajati(y);
		}
		catch (...)
		{
			cout << "CNP incorect\n";
			pers.pop_back();
		}
	}
	void nr_angajati(Personal *p)
	{
		nrpers++;
		if (p->get_r() >=0)
		{
			Actor *a;
			a= static_cast<Actor*>(p);
			if (a!=0)
			{
				nractor++;
				a->set_n(a->get_r());
				pers.pop_back();
				pers.push_back(a);
				int t = cautare(movie, a->get_t());
				double c;
				c = a->salar(movie[t],0);
				movie[t]->set_c(movie[t]->get_c() - c);
				cout << "Transformat in actor\n";
			}
		}
		else if(p->get_r()==-1)
		{
			Regizor *r;
			r = static_cast<Regizor*>(p);
			if (r!=0)
			{
				cout << "Salariul fix este: ";
				double s;
				cin >> s;
				r->set_s(s);
				pers.pop_back();
				pers.push_back(r);
				int t = cautare(movie, r->get_t());
				double c;
				c = r->salar(movie[t],s);
				movie[t]->set_c(movie[t]->get_c() - c);
			}
			
		}
		else
		{
			int t = cautare(movie, p->get_t());
			double c;
			c = p->salar(movie[t],0);
			movie[t]->set_c(movie[t]->get_c() - c);
		}
	}
	int cautare_prin(string x)
	{
		int m;
		m = pers.size();
		for (int i = 0; i < m; i++)
			if (pers[i]->get_t() == x && pers[i]->get_r() == 1) return 1;
		return 0;
	}
	void afis()
	{
		int n = movie.size();
		for (int i = n-1; i >=0; i--)
		{
			try
			{
				if (movie[i]->get_c() < 0) throw movie[i]->get_c();
				if (cautare_prin(movie[i]->get_t())==0) throw movie[i]->get_t();
				throw movie[i];
			}
			catch (double x)
			{
				cout << "Filmul " << movie[i]->get_t()<< " a iesit pe minus "<<x;
			}
			catch (string z)
			{
				cout << "Filmul " << z << " nu are personaje principale\n";
				movie.pop_back();
			}
			catch (Film *y)
			{
				cout << "Filmul " << y->get_t();
				if (y->get_c() == 0) cout<< " nu a adus profit";
				else cout << " a adus profit";
				cout << '\n';
				cout << (*y);
				int l = pers.size();
				cout << "Distributie:\n";
				for (int j = 0; j < l; j++)
					if (pers[j]->get_t() == y->get_t())
					{
						if (pers[j]->get_r() >= 0)
						{
							Actor *a;
							a = static_cast<Actor*>(pers[j]);
							cout << (*a)<<", ";
						}
						else if (pers[j]->get_r() == -1)
						{
							Regizor *r;
							r = static_cast<Regizor*>(pers[j]);
							cout << (*r)<<", ";
						}
						else cout << (*pers[j]) << ", ";
					}
				cout << '\n';
			}
			catch(...)
			{
				cout << "eroare";
			}
			
		}
	}
};
template <class T>
T FirmaDistributie <T> ::nrpers = 0;
template <class T>
T FirmaDistributie <T>::nractor = 0;
template<> class FirmaDistributie<unsigned>
{
	static unsigned nractorp;
	vector<Film*>movie;
	vector<Actor*>act;
public:
	void add_film()
	{
		Film *f = new Film;
		cin >> (*f);
		movie.push_back(f);
	}
	void add_pers()
	{
		Actor *p = new Actor;
		cin >> (*p);
		if (p->get_r() == 1)
		{
			act.push_back(p);
			try {
				if (p->get_c().size() != 13) throw 13;
				else throw p;
			}
			catch (Actor* y)
			{
				if (cautare(movie, y->get_t()) == -1)
				{
					cout << "Datele pentru filmul " << y->get_t();
					string tip;
					double durata;
					double cost;
					cin >> tip >> durata >> cost;
					Film *f = new Film(y->get_t(), tip, durata, cost);
					movie.push_back(f);
				}
				nr_angajati(y);
			}
			catch (...)
			{
				cout << "CNP incorect\n";
				act.pop_back();
			}
		}
	}
	void nr_angajati(Actor *p)
	{
		nractorp++;
		int t = cautare(movie, p->get_t());
		double c;
		c = p->salar(movie[t],0);
		movie[t]->set_c(movie[t]->get_c() - c);
	}
	int cautare_prin(string x)
	{
		int m;
		m = act.size();
		for (int i = 0; i < m; i++)
			if (act[i]->get_t() == x && act[i]->get_r() == 1) return 1;
		return 0;
	}
	void afis()
	{
		int n = movie.size();
		for (int i = n - 1; i >= 0; i--)
		{
			try
			{
				if (movie[i]->get_c() < 0) throw movie[i]->get_c();
				if (cautare_prin(movie[i]->get_t()) == 0) throw movie[i]->get_t();
				throw movie[i];
			}
			catch (double x)
			{
				cout << "Filmul " << movie[i]->get_t() << " a iesit pe minus " << x;
			}
			catch (string z)
			{
				cout << "Filmul " << z << " nu are personaje principale\n";
				movie.pop_back();
			}
			catch (Film *y)
			{
				cout << "Filmul " << y->get_t();
				if (y->get_c() == 0) cout << " nu a adus profit";
				else cout << " a adus profit";
				cout << '\n';
				cout << (*y);
				int l = act.size();
				cout << "Distributie:\n";
				for (int j = 0; j < l; j++)
					if (act[i]->get_t() == y->get_t()) cout << (*act[i]);
				cout << '\n';
			}

		}
	}
};
unsigned FirmaDistributie<unsigned>::nractorp = 0;
int main()
{
	int n,m;
	FirmaDistributie<int>firma;
	cin >> m;
	for(int i=0;i<m;i++)
		firma.add_film();
	cin >> n;
	for (int i = 0; i < n; i++)
		firma.add_pers();
	firma.afis();
	system("pause");
}

Film Film::operator=(Film f)
{
	titlu.clear();
	titlu=f.titlu;
	tip.clear();
	tip=f.tip;
	durata = f.durata;
	cost = f.cost;
	return *this;
}

istream &operator >> (istream & i, Film & f)
{
	cout << "|Titlu tip durata cost|";
	i >> f.titlu >> f.tip>> f.durata>> f.cost;
	return i;
}

ostream & operator<<(ostream & o, Film & f)
{
	o << f.titlu << ", " << f.tip << ", " << f.durata << " min, " << f.cost << " lei";
	o << endl;
	return o;
}

