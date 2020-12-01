#include<iostream>
#include<list>

using namespace std;

class Set
{
    list<int> *data;
    int size;

    Set()
    {
        size = 100;//tamallo de arreglo 100
        data = new int[size];//se crea el arreglo
    }

    Set(int s)
    {
        size = s;
        data = new int[size];
    }

    int hash(int value)
    {
        return value%size;//calcula posicion
    }

    void insert(int value)
    {
        int pos = hash(value);//calcula posicion
        for (int val:data[pos])//vamos a tomar cada valor dentro de data
        {
            if(val == value)
            {
                return;
            }
        }
        data[pos].push_back(value);//insertar valor en arreglo
    }

    bool find(int value)
    {
        int pos = hash(value);//calcula posicion
        for (int val:data[pos])//vamos a tomar cada valor dentro de data
        {
            if(val == value)
            {
                return true;
            }
        }
        return false;
    }

    void print()
    {
        for(int i=0; i<size; i++)
        {
            cout << "[" << i << "]";
            for(auto j=data[i].begin(); j!=data[i].end(); j++)
            {
                cout << *j << ",";
            }
            cout << endl;
        }
    }
};

int main()
{
    Set s(9);
    s.insert(5);
    s.insert(15);
    s.insert(3);
    s.insert(3);
    s.print();
    cout << s.find(3) << endl;
    return 0;
}

