#include <iostream>
#include <unordered_map>

using namespace std;

template <class T>
class SNode
{
public:
    T value;
    SNode *next;
    SNode() {}
    SNode(T val)
    {
        value = val;
        next = 0;
    }
};

template <class T>
class Stack
{
private:
    SNode<T> *head;

public:
    Stack() { head = 0; }
    void push(T value)
    {
        SNode<T> *t = new SNode<T>(value);
        t->next = head;
        head = t;
    }

    T pop()
    {
        SNode<T> *t = head;
        if (head->next)
            head = head->next;
        else
            head = 0;
        T val = t->value;
        delete t;
        return val;
    }

    //funcion que checa si el stack esta empty
    bool isEmpty()
    {
        if (head)
            return false;
        return true;
    }
};

template <class T>
class QNode
{
public:
    T value;
    QNode *next;
    QNode *prev;
    QNode(){};
    QNode(T val)
    {
        value = val;
        next = NULL;
        prev = NULL;
    }
};

template <class T>
class Queue
{
public:
    QNode<T> *front;
    QNode<T> *back;
    Queue()
    {
        front = NULL;
        back = NULL;
    }

    //agrega values al queue
    void enqueue(T value)
    {
        QNode<T> *nuevo = new QNode<T>(value);
        if (back == NULL)
        {
            back = nuevo;
            front = back;
        }
        else
        {
            back->next = nuevo;
            nuevo->prev = back;
            back = nuevo;
        }
    }

    //regresa el primer valor del queue
    T dequeue()
    {
        QNode<T> *t = front;
        if (front->next)
            front = front->next;
        else
            front = back = 0;
        T value = t->value;
        delete t;
        return value;
    }

    //chehca si el queue esta vacio
    bool isEmpty()
    {
        if (back)
        {
            return false;
        }
        return true;
    }
};

template <class T>
class Nodo
{
public:
    T value;
    bool visited;
    unordered_map<Nodo<T> *, int> siguientes;

    Nodo(T val)
    {
        value = val;
        visited = false; //si ya fue visitado
    }

    //agrega un arco dirigido con peso
    void agregarArcoDirigidoConPeso(Nodo<T> *sig, int peso)
    {
        if (siguientes.find(sig) == siguientes.end())
            siguientes[sig] = peso;
    }

    //agrega un arco dirigido con peso de 1
    void agregarArcoDirigido(Nodo<T> *sig)
    {
        agregarArcoDirigidoConPeso(sig, 1);
    }

    void imprimirNodo()
    {
        cout << value << ":";
        for (auto nodoSiguiente : siguientes)
        {
            cout << nodoSiguiente.first->value << "," << nodoSiguiente.second << ";";
        }
        cout << endl;
    }
};

template <class T>
class Graph
{
public:
    unordered_map<T, Nodo<T> *> nodos;

    void agregarNodo(T value)
    {
        if (nodos.find(value) == nodos.end())
        {
            Nodo<T> *nuevo = new Nodo<T>(value);
            nodos[value] = nuevo;
        }
    }

    //agrega un arco dirigido de nodo1 a nodo2 con peso
    void agregarArcoDirigidoConPeso(T nodo1, T nodo2, int peso)
    {
        if (nodos.find(nodo1) != nodos.end() && nodos.find(nodo2) != nodos.end())
        {
            nodos[nodo1]->agregarArcoDirigidoConPeso(nodos[nodo2], peso);
        }
        else
        {
            cout << "Alguno de los 2 nodos no se encuentra en el grafo" << endl;
        }
    }

    //agrega un arco dirigido de nodo1 a nodo2 con peso de 1
    void agregarArcoDirigido(T nodo1, T nodo2)
    {
        agregarArcoDirigidoConPeso(nodo1, nodo2, 1);
    }

    //agrega un arco dirigido de nodo1 a nodo2 con peso y viceversa
    void agregarArcoConPeso(T nodo1, T nodo2, int peso)
    {
        agregarArcoDirigidoConPeso(nodo1, nodo2, peso);
        agregarArcoDirigidoConPeso(nodo2, nodo1, peso);
    }

    //agrega un arco dirigido de nodo1 a nodo2 con peso de 1 y viceversa
    void agregarArco(T nodo1, T nodo2)
    {
        agregarArcoConPeso(nodo1, nodo2, 1);
    }

    void imprimirGrafo()
    {
        for (auto parValorNodo : nodos)
        {
            parValorNodo.second->imprimirNodo();
        }
    }

    //BREATH FRIST SEARCJ
    bool BFS(T v1, T v2)
    {
        quitarVisita();
        Queue<T> adyacentes; //queue de nodos adyacentes al nodo actual (temp)
        adyacentes.enqueue(v1);
        while (adyacentes.isEmpty() == false) //miestras el queue no este vacio
        {
            T temp = adyacentes.dequeue();
            //cout << temp << endl;
            nodos[temp]->visited = true; //es visitado
            if (temp == v2)
            {
                return true; //termina while
            }
            else
            {
                for (auto t : nodos[temp]->siguientes)
                {
                    if (t.first->visited == false) //si no ha sido visitado
                    {
                        adyacentes.enqueue(t.first->value); //agrega al queue
                    }
                }
            }
        }
        return false; //si no lo encuentra regresa false
    }

    //DEPTH FIRST SEARCH
    bool DFS(T nodo1, T nodo2)
    {
        quitarVisita();
        Stack<T> adyacentes;                  //crea un stack s
        adyacentes.push(nodo1);               //agrega nodo actual
        while (adyacentes.isEmpty() == false) //miestra el stack no este vacio
        {
            T temp = adyacentes.pop();
            //cout << temp << endl;
            nodos[temp]->visited = true; //es visitado
            if (temp == nodo2)
            {
                return true; //se encuentra y regresa true
            }
            else
            {
                for (auto t : nodos[temp]->siguientes)
                {
                    if (t.first->visited == false) //si no han sido visitados
                    {
                        adyacentes.push(t.first->value); //se agrega el stack
                    }
                }
            }
        }
        return false; //si no lo encuentra regresa false
    }

    void quitarVisita()
    {
        for (auto t : nodos)
        {
            t.second->visited = false;
        }
    }
};

int main()
{
    Graph<string> g;
    g.agregarNodo("CDMX");
    g.agregarNodo("Tlaxcala");
    g.agregarNodo("Puebla");
    g.agregarNodo("Toluca");
    g.agregarArcoDirigidoConPeso("CDMX", "Tlaxcala", 50);
    g.agregarArcoConPeso("CDMX", "CDMX", 20);
    g.agregarArcoConPeso("CDMX", "Puebla", 100);
    g.agregarArco("Puebla", "Puebla");
    g.imprimirGrafo();
    bool x = g.DFS("CDMX", "Puebla");
    if (x == true)
        cout << "si" << endl;
    else
        cout << "no" << endl;

    x = g.BFS("CDMX", "Toluca");
    if (x == true)
        cout << "si" << endl;
    else
        cout << "no" << endl;
}