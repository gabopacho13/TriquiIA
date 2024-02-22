#include <iostream>

using namespace std;

struct par
{
    int indice;
    double costo;

    par& operator = (const par &p)
    {
        indice = p.indice;
        costo = p.costo;
        return *this;
    }

    bool operator == (const par &p) const
    {
        return (indice == p.indice);
    }

    friend ostream& operator << (ostream &o, const par &p)
    {
        o << "(" << p.indice << "," << p.costo << ")";
        return o;
    }
};
