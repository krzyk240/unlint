#include <iostream>
#include <vector>
//#include "unlint.h"

#define DEBUG

using namespace std;

typedef long long int lli;
const lli BASE=1000000000000000000LL;
const int BS2=1000000000;
const char LEN=18;

class num
{
public:
	struct fmod
	{
		lli pom1, pom2;
		fmod(){}
		~fmod(){}
	};
	std::vector<lli> w;
	num(): w(1,0){}
	~num(){}
	num(const lli& _x): w(1,_x){}
	num(const num& _n): w(_n.w){}
	void kas0();
	void swap(num& _n){w.swap(_n.w);}
	num& operator++();
	num& operator--();
	num& operator+=(const num&);
	num& operator-=(const num&);
	num& operator*=(const lli&);
	void gen_mod(vector<fmod>&) const;
	num& mult(const lli&, const vector<fmod>&);
	void to_old_type(vector<int>&) const;
	num& from_old_type(vector<int>&) const;
	num& operator*=(const num&);
	num& operator/=(const num&);
	num& operator%=(const num&);
	void nwd(const num&);
	num& pow(const num&);
	bool operator<(const num&) const;
	bool operator>(const num&) const;
	bool operator<=(const num&) const;
	bool operator>=(const num&) const;
	bool operator==(const num&) const;
	bool operator!=(const num&) const;
};

void /*unlint::*/num::kas0()
{
	vector<lli>::iterator i=w.end()-1;
	while(i!=w.begin() && *i==0) --i;
	++i;
	w.erase(i, w.end());
}


num& /*unlint::*/num::operator++()
{
	vector<lli>::iterator i=w.begin();
	while(i!=w.end())
	{
		++*i;
		if(*i<BASE) return *this;
		*i-=BASE;
		++i;
	}
	w.push_back(1);
return *this;
}

num& /*unlint::*/num::operator--()
{
	vector<lli>::iterator i=w.begin();
	while(i!=w.end())
	{
		--*i;
		if(*i>=0) break;
		*i+=BASE;
		++i;
	}
	kas0();
return *this;
}

num& /*unlint::*/num::operator+=(const num& _n)
{
	int s=_n.w.size(), i=0;
	if(s>w.size()) w.resize(s);
	bool add=false;
	for(; i<s; ++i)
	{
		w[i]+=_n.w[i];
		if(add) ++w[i];
		if(w[i]>=BASE)
		{
			w[i]-=BASE;
			add=true;
		}
		else add=false;
	}
	if(add)
	{
		if(i==s) w.push_back(add);
		else
		{
			for(;i<s; ++i)
			{
				++w[i];
				if(w[i]<BASE) break;
				w[i]-=BASE;
			}
			if(i==s) w.push_back(add);
		}
	}
return *this;
}

num& /*unlint::*/num::operator-=(const num& _n)
{
	int s=_n.w.size(), i=0;
	bool add=false;
	for(; i<s; ++i)
	{
		w[i]-=_n.w[i];
		if(add) --w[i];
		if(w[i]<0)
		{
			w[i]+=BASE;
			add=true;
		}
		else add=false;
	}
	if(add)
	{
		s=w.size();
		for(;i<s; ++i)
		{
			--w[i];
			if(w[i]>=0) break;
			w[i]+=BASE;
		}
	}
	kas0();
return *this;
}

num& /*unlint::*/num::operator*=(const lli& _lcb)
{
	if(_lcb==0){vector<lli>(1).swap(w);return *this;}
	lli p1=_lcb/BS2, p2=_lcb-p1*BS2, add=0, pom1, pom2, pom3, add1;
	for(vector<lli>::iterator i=w.begin(); i!=w.end(); ++i)
	{
		pom1=*i/BS2;
		pom2=*i-pom1*BS2;
		*i=add+p2*pom2;
		add1=add=0;
		if(*i>=BASE){++add;*i-=BASE;}
		add1=pom1*p2+pom2*p1;
		pom3=add1/BS2;
		*i+=(add1-pom3*BS2)*BS2;
		while(*i>=BASE)
		{
			++add;
			*i-=BASE;
		}
		add+=pom3+pom1*p1;
	}
	if(add) w.push_back(add);
return *this;
}

void /*unlint::*/num::gen_mod(vector<num::fmod>& _k) const
{
	int wl=w.size();
	_k.resize(wl);
	for(int i=0; i<wl; ++i)
	{
		_k[i].pom1=w[i]/BS2;
		_k[i].pom2=w[i]-_k[i].pom1*BS2;
	}
}

num& /*unlint::*/num::mult(const lli& _lcb, const vector<num::fmod>& _t)
{
	if(_lcb==0){vector<lli>(1).swap(w);return *this;}
	int tl=_t.size();
	w.resize(tl);
	lli p1=_lcb/BS2, p2=_lcb-p1*BS2, add=0, pom3, add1;
	for(int i=0; i<tl; ++i)
	{
		w[i]=add+p2*_t[i].pom2;
		add1=add=0;
		if(w[i]>=BASE){++add;w[i]-=BASE;}
		add1=_t[i].pom1*p2+_t[i].pom2*p1;
		pom3=add1/BS2;
		w[i]+=(add1-pom3*BS2)*BS2;
		while(w[i]>=BASE)
		{
			++add;
			w[i]-=BASE;
		}
		add+=pom3+_t[i].pom1*p1;
	}
	if(add) w.push_back(add);
return *this;
}

void old_kas0(vector<int>& _n)
{
	vector<lli>::iterator i=_n.end()-1;
	while(i!=_n.begin() && *i==0) --i;
	++i;
	_n.erase(i, _n.end());
}

void num::to_old_type(vector<int>& _n) const
{
	int wl=w.size();
	_n.resize(wl<<1);
	for(int i=0; i<wl; ++i)
	{
		_n[i<<1]=w[i]/BS2;
		_n[1+i<<1]=w[i]-_n[i<<1]*BS2;
	}
	old_kas0(_n);
}

num& num::from_old_type(vector<int>& _n) const
{
	int nl=_n.size();
	w.resize((1+nl)>>1);
	for(int i=0; i<nl; i+=2)
		w[i>>1]=_n[i];
	for(int i=1; i<nl; i+=2)
		w[i>>1]=_n[i]*BS2;
return *this;
}

num& /*unlint::*/num::operator*=(const num& b)
{
	num lol=0, _n;
	lli bl=b.w.size();
	vector<num::fmod> t;
	b.gen_mod(t);
	for(int q=0; q<w.size(); ++q)
	{
		_n.mult(w[q], t);
		//k.w.insert(k.w.begin(),i,0);
		//lol+=k;
		int s=_n.w.size(), i=0;
		if(s+q>lol.w.size()) lol.w.resize(s+q);
		bool add=false;
		for(; i<s; ++i)
		{
			lol.w[i+q]+=_n.w[i];
			if(add) ++lol.w[i+q];
			if(lol.w[i+q]>=BASE)
			{
				lol.w[i+q]-=BASE;
				add=true;
			}
			else add=false;
		}
		if(add)
		{
			if(i==s) lol.w.push_back(add);
			else
			{
				for(;i<s; ++i)
				{
					++lol.w[i+q];
					if(lol.w[i+q]<BASE) break;
					lol.w[i+q]-=BASE;
				}
				if(i==s) lol.w.push_back(add);
			}
		}
	}
	swap(lol);
	kas0();
return *this;
}

void div(vector<int>& a, vector<int>& b)
{
	int al=a.size(), bl=b.size(), iws=al-bl;
	if(bl==1 && b[0]==1) return;
	else
	{
		bool is_grader;
		if(al<bl) is_grader=false;
		else if(al>bl) is_grader=true;
		else
		{
			int i=bl-1;
			while(i>=0 && a[i+iws]==b[i])
				--i;
			if(i<0 || a[i+iws]>b[i]) is_grader=true;
			else is_grader=false;
		}
		if(!is_grader)
		{
			vector<int>(1,0).swap(a);
			return;
		}
	}
	int al=a.size(), bl=b.size(), iws=al-bl;
	vector<int> w(iws+1), g;
	while(iws>=0)
	{
		bool is_grader;
		if(al-iws<bl) is_grader=false;
		else if(al-iws>bl) is_grader=true;
		else
		{
			int i=bl-1;
			while(i>=0 && a[i+iws]==b[i])
				--i;
			if(i<0 || a[i+iws]>b[i]) is_grader=true;
			else is_grader=false;
		}
		if(is_grader)
		{
			int down=1, up=BS2-1, mean;
			while(down<up)
			{
				mean=1+(down+up)>>1;
				//g=b*mean;
				{
					int gl=g.size();
					lli tmp, add=0;
					for (int i=0; i<gl; ++i)
                    {
                        tmp=static_cast<lli>(g[i])*mean+add;
                        add=tmp/BS2;
                        g[i]=tmp-add*BS2;
                    }
                    if(add>0) g.push_back(add);
                    old_kas0(g);
                }
				int gl=g.size();
				if(al-iws<gl) is_grader=true;
				else if(al-iws>gl) is_grader=false;
				else
				{
					int i=gl-1;
					while(i>=0 && a[i+iws]==g[i])
						--i;
					if(i<0) is_grader=false;
					else if(g[i]>a[i+iws]) is_grader=true;
					else is_grader=false;
				}
				if(is_grader) up=--mean;
				else down=mean;
			}
			//g=b*down;
			{
				int gl=g.size();
				lli tmp, add=0;
				for (int i=0; i<gl; ++i)
				{
					tmp=static_cast<lli>(g[i])*down+add;
					add=tmp/BS2;
					g[i]=tmp-add*BS2;
				}
				if(add>0) g.push_back(add);
				old_kas0(g);
			}
			int gl=g.size();
			bool add=false;
			for(int i=0; i<gl; ++i)
			{
				a[i+iws]-=g[i]+add;
				if(a[i+iws]<0)
				{
					a[i+iws]+=BASE;
					add=true;
				}
				else add=false;
			}
			for(int i=gl+iws; i<al; ++i)
			{
				--a[i];
				if(a[i]<0) a[i]+=BASE;
				else break;
			}
			old_kas0(a);
			al=a.size();
			w[iws]=down;
		}
		--iws;
	}
	a.swap(w);
	old_kas0(a);
}

void mod(vector<int>& a, vector<int>& b)
{
	int al=a.size(), bl=b.size(), iws=al-bl;
	if(bl==1 && b[0]==1)
	{
		vector<int>(1,0).swap(a);
		return;
	}
	else
	{
		bool is_grader;
		if(al<bl) is_grader=false;
		else if(al>bl) is_grader=true;
		else
		{
			int i=bl-1;
			while(i>=0 && a[i+iws]==b[i])
				--i;
			if(i<0 || a[i+iws]>b[i]) is_grader=true;
			else is_grader=false;
		}
		if(!is_grader) return;
	}
	vector<int> w(iws+1), g;
	while(iws>=0)
	{
		bool is_grader;
		if(al-iws<bl) is_grader=false;
		else if(al-iws>bl) is_grader=true;
		else
		{
			int i=bl-1;
			while(i>=0 && a[i+iws]==b[i])
				--i;
			if(i<0 || a[i+iws]>b[i]) is_grader=true;
			else is_grader=false;
		}
		if(is_grader)
		{
			int down=1, up=BS2-1, mean;
			while(down<up)
			{
				mean=1+(down+up)>>1;
				//g=b*mean;
				{
					int gl=g.size();
					lli tmp, add=0;
					for (int i=0; i<gl; ++i)
                    {
                        tmp=static_cast<lli>(g[i])*mean+add;
                        add=tmp/BS2;
                        g[i]=tmp-add*BS2;
                    }
                    if(add>0) g.push_back(add);
                    old_kas0(g);
                }
				int gl=g.size();
				if(al-iws<gl) is_grader=true;
				else if(al-iws>gl) is_grader=false;
				else
				{
					int i=gl-1;
					while(i>=0 && a[i+iws]==g[i])
						--i;
					if(i<0) is_grader=false;
					else if(g[i]>a[i+iws]) is_grader=true;
					else is_grader=false;
				}
				if(is_grader) up=--mean;
				else down=mean;
			}
			//g=b*down;
			{
				int gl=g.size();
				lli tmp, add=0;
				for (int i=0; i<gl; ++i)
				{
					tmp=static_cast<lli>(g[i])*down+add;
					add=tmp/BS2;
					g[i]=tmp-add*BS2;
				}
				if(add>0) g.push_back(add);
				old_kas0(g);
			}
			int gl=g.size();
			bool add=false;
			for(int i=0; i<gl; ++i)
			{
				a[i+iws]-=g[i]+add;
				if(a[i+iws]<0)
				{
					a[i+iws]+=BASE;
					add=true;
				}
				else add=false;
			}
			for(int i=gl+iws; i<al; ++i)
			{
				--a[i];
				if(a[i]<0) a[i]+=BASE;
				else break;
			}
			old_kas0(a);
			al=a.size();
			w[iws]=down;
		}
		--iws;
	}
	old_kas0(a);
}

num& /*unlint*/num::operator/=(const num& _n)
{
	if(operator<(_n))
	{
		vector<lli>(1,0).swap(w);
		return *this;
	}
	else if(_n.w.size()==1 && _n.w[0]==1) return *this;
	int wl=w.size(), nl=_n.w.size(), iws=wl-nl;
	vector<num::fmod> nmd;
	_n.gen_mod(nmd);
	num k, w;
	w.w.resize(iws+1);
	bool is_grader;
	while(iws>=0)
	{
		if(wl-iws<nl) is_grader=false;
		else if(wl-iws>nl) is_grader=true;
		else
		{
			int i=nl-1;
			while(i>=0 && w[i+iws]==_n.w[i])
				--i;
			if(i<0 || w[i+iws]>_n.w[i]) is_grader=true;
			else is_grader=false;
		}
		if(is_grader)
		{
			lli down=0, up=BASE-1, mean;
			while(down<up)
			{
				mean=1+(down+up)>>1;
				k.mult(mean, nmd);
				int kl=k.w.size();
				if(wl-iws<kl) is_grader=true;
				else if(wl-iws>kl) is_grader=false;
				else
				{
					int i=kl-1;
					while(i>=0 && w[i+iws]==k.w[i])
						--i;
					if(i<0) is_grader=false;
					else if(k.w[i]>w[i+iws]) is_grader=true;
					else is_grader=false;
				}
				if(is_grader) up=--mean;
				else down=mean;
			}
			k.mult(down, nmd);
			int gl=k.w.size();
			bool add=0;
			for(int i=0; i<gl; ++i)
			{
				w[i+iws]-=k.w[i];
				if(add) --w[i+iws];
				if(w[i+iws]<0)
				{
					w[i+iws]+=BASE;
					add=true;
				}
				else add=false;
			}
			for(int i=gl+iws; i<wl; ++i)
			{
				if(add) --w[i];
				if(w[i]<0)
				{
					w[i]+=BASE;
					add=true;
				}
				else break;
			}
			kas0();
			wl=w.size();
			w.w[iws]=down;
		}
		--iws;
	}
	w.kas0();
	swap(w);
return *this;
}

num& /*unlint*/num::operator%=(const num& _n)
{
	if(operator<(_n))
		return *this;
	else if(_n.w.size()==1 && _n.w[0]==1)
	{
		vector<lli>(1,0).swap(w);
		return *this;
	}
	int wl=w.size(), nl=_n.w.size(), iws=wl-nl;
	vector<num::fmod> nmd;
	_n.gen_mod(nmd);
	num k;
	bool is_grader;
	while(iws>=0)
	{
		if(wl-iws<nl) is_grader=false;
		else if(wl-iws>nl) is_grader=true;
		else
		{
			int i=nl-1;
			while(i>=0 && w[i+iws]==_n.w[i])
				--i;
			if(i<0 || w[i+iws]>_n.w[i]) is_grader=true;
			else is_grader=false;
		}
		if(is_grader)
		{
			lli down=0, up=BASE-1, mean;
			while(down<up)
			{
				mean=1+(down+up)>>1;
				k.mult(mean, nmd);
				int kl=k.w.size();
				if(wl-iws<kl) is_grader=true;
				else if(wl-iws>kl) is_grader=false;
				else
				{
					int i=kl-1;
					while(i>=0 && w[i+iws]==k.w[i])
						--i;
					if(i<0) is_grader=false;
					else if(k.w[i]>w[i+iws]) is_grader=true;
					else is_grader=false;
				}
				if(is_grader) up=--mean;
				else down=mean;
			}
			k.mult(down, nmd);
			int gl=k.w.size();
			bool add=0;
			for(int i=0; i<gl; ++i)
			{
				w[i+iws]-=k.w[i];
				if(add) --w[i+iws];
				if(w[i+iws]<0)
				{
					w[i+iws]+=BASE;
					add=true;
				}
				else add=false;
			}
			for(int i=gl+iws; i<wl; ++i)
			{
				if(add) --w[i];
				if(w[i]<0)
				{
					w[i]+=BASE;
					add=true;
				}
				else break;
			}
			kas0();
			wl=w.size();
		}
		--iws;
	}
return *this;
}

void echo(const num&);

void /*unlint::*/num::nwd(const num& _n)
{
	num b=_n, zero(0), c;
	int i=0;
	while(b!=zero)
	{
		c.swap(*this);
		c%=b;
		swap(b);
		b.swap(c);
	}
}

bool /*unlint::*/num::operator<(const num& _n) const
{
	int i=w.size();
	if(i<_n.w.size()) return true;
	else if(i>_n.w.size()) return false;
	--i;
	while(i>=0 && w[i]==_n.w[i])
		--i;
	if(i<0) return false;
	if(w[i]>_n.w[i]) return false;
return true;
}

bool /*unlint::*/num::operator>(const num& _n) const
{
return _n<*this;
}

bool /*unlint::*/num::operator<=(const num& _n) const
{
return !(_n<*this);
}

bool /*unlint::*/num::operator>=(const num& _n) const
{
return !operator<(_n);
}

bool /*unlint::*/num::operator==(const num& _n) const
{
	int i=w.size();
	if(i!=_n.w.size()) return false;
	--i;
	while(i>=0 && w[i]==_n.w[i])
		--i;
	if(i<0) return true;
return false;
}

bool /*unlint::*/num::operator!=(const num& _n) const
{
return !operator==(_n);
}

void echo(const num& a)
{
	int k=a.w.size()-1;
	cout << a.w[k];
	for(int i=--k; i>=0; i--)
	{
		cout.width(LEN);
		cout.fill('0');
		cout << a.w[i];
	}
}

void get(num& a)
{
	vector<lli>().swap(a.w);
	string str;
	cin >> str;
	lli pom;
	for(int i=str.size(); i>0; i-=LEN)
	{
		pom=0;
		for(int j=max(0,i-LEN); j<i; ++j)
		{
			pom*=10;
			pom+=str[j]-'0';
		}
		a.w.push_back(pom);
	}
	a.kas0();
}
/*
class lol
{
public:
	vector<char> w;
	void get();
	void echo();
	void kas0();
	lol& operator%=(const lol&);
};

void lol::kas0()
{
	vector<char>::iterator i=w.end()-1;
	while(i!=w.begin() && *i==0) --i;
	++i;
	w.erase(i, w.end());
}

void lol::get()
{
	string a;
	cin >> a;
	w.resize(a.size());
	vector<char>::iterator wi=w.begin();
	for(int i=a.size()-1; i>=0; --i,++wi)
		*wi=a[i]-'0';
}

void lol::echo()
{
	for(int i=w.size()-1; i>=0; --i)
		cout << static_cast<char>(w[i]+'0');
}

lol& lol::operator%=(const lol& _n)
{
	int nl=_n.w.size(), wl=w.size(), iws=wl-nl;
	vector<char> tab[10];
	tab[1]=_n.w;
	for(int i=2; i<10; ++i)
	{
		tab[i].resize(nl);
		char add=0;
		for(int j=0; j<nl; ++j)
		{
			tab[i][j]=i*_n.w[j]+add;
			add=tab[i][j]/10;
			tab[i][j]-=10*add;
		}
		if(add) tab[i].push_back(add);
	}
	bool is_grader;
	while(iws>=0)
	{
		if(wl-iws<nl) is_grader=false;
		else if(wl-iws>nl) is_grader=true;
		else
		{
			int i=nl-1;
			while(i>=0 && w[i+iws]==_n.w[i])
				--i;
			if(i<0 || w[i+iws]>_n.w[i]) is_grader=true;
			else is_grader=false;
		}
		if(is_grader)
		{
			int down=1, up=9, mean;
			while(down<up)
			{
				mean=1+(down+up)>>1;
				int kl=tab[mean].size();
				if(wl-iws<kl) is_grader=true;
				else if(wl-iws>kl) is_grader=false;
				else
				{
					int i=kl-1;
					while(i>=0 && w[i+iws]==tab[mean][i])
						--i;
					if(i<0) is_grader=false;
					else if(tab[mean][i]>w[i+iws]) is_grader=true;
					else is_grader=false;
				}
				if(is_grader) up=--mean;
				else down=mean;
			}
			int gl=tab[up].size();
			bool add=false;
			for(int i=0; i<gl; ++i)
			{
				w[i+iws]-=tab[up][i];
				if(add) --w[i+iws];
				if(w[i+iws]<0)
				{
					w[i+iws]+=10;
					add=true;
				}
				else add=false;
			}
			for(int i=gl+iws; i<wl; ++i)
			{
				if(add) --w[i];
				if(w[i]<0)
				{
					w[i]+=10;
					add=true;
				}
				else break;
			}
			kas0();
			wl=w.size();
		}
		--iws;
	}
return *this;
}
*/
int main()
{
	num a;
	num b;
	get(a);
	get(b);
	a%=b;//a.nwd(b);
	echo(a);
	cout << endl;
return 0;
}
