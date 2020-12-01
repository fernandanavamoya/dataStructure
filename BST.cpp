#include <iostream>
using namespace std;

template <class T>
class Nodo
{
	public:
	T value;
	Nodo<T> *izq;
	Nodo<T> *der;
	
	Nodo()
	{
		value=NULL;
		izq=NULL;
		der=NULL;
	}
	
	Nodo(T val)
	{
		value=val;
		izq=NULL;
		der=NULL;
	}
};

template <class T>
class BST
{
public:
	Nodo<T> *root;
	
	BST()
	{
		root=NULL;
	}
	
	void insertar(T value)
	{
		Nodo<T> *nuevo=new Nodo<T>(value);
		if(root==NULL)
		{
			root=nuevo;
		}
		else
		{
			insertar(nuevo, root);
		}
	}
	
	void insertar(Nodo<T> *nuevo, Nodo<T> *temp)
	{
		if(nuevo->value==temp->value)//si el valor es igual, terminamos
		{	
			return;
		}
		else if(nuevo->value<temp->value)//si el valor es menor que el valor de temp
		{
			if(temp->izq==NULL)//si el izquierdo es nulo, ahi agregamos
			{
				temp->izq=nuevo;
			}
			else
			{
				insertar(nuevo, temp->izq); //sino, temp=temp->izq
			}
		}
		else //si el valor es mayor que el valor de temp
		{
			if(temp->der==NULL) //si el derecho es nulo, ahi agregamos
			{
				temp->der=nuevo;
			}
			else
			{
				insertar(nuevo, temp->der);//sino, temp=temp->der
			}
		}
	}
	
	void inorder(){
		inorder(root);
		cout<<endl;
	} 
	
	void inorder(Nodo<T> *temp)
	{
		if(temp!=NULL)
		{
			inorder(temp->izq);
			cout<<temp->value<<" ";
			inorder(temp->der);
		}
	}
		
	Nodo<T> *buscarIterativo(T value)
	{
		Nodo<T> *temp=root;
		while(temp!=NULL)
		{
			if(temp->value==value)
			{
				return temp;
			}
			else if(value < temp->value)
			{
				temp = temp->izq;
			}
			else
			{
				temp = temp->der;
			}
		}
		return NULL;
	}
	
	bool buscarRecursivo(T value)
	{
		if(root==NULL)
		{
			return false;
		}
		else
		{
			return buscarRecursivo(value, root);
		}
	}
	
	bool buscarRecursivo(T value, Nodo<T> *temp)
	{
		if(temp==NULL)
		{
			return false;
		}
		else if(temp->value==value)
		{
			return true;
		}
		else if(value<temp->value)
		{
			return buscarRecursivo(value, temp->izq);
		}
		else
		{
			return buscarRecursivo(value, temp->der);
		}
	}
	
	void eliminar(T value)
	{
		if(root==NULL)
		{
			return;
		}
		else{
			root=eliminar(value, root);
		}
	}
	
	Nodo<T> *eliminar(T value, Nodo<T> *temp)
	{
		if(temp==NULL)
		{
			return NULL;
		}
		else if(value<temp->value)
		{
			temp->izq=eliminar(value, temp->izq);
		}
		else if(value>temp->value)
		{
			temp->der=eliminar(value, temp->der);
		}
		//Si el valor es igual
		else 
		{
			if(temp->izq == NULL && temp->der == NULL) //si el nodo es una hoja
			{
				delete temp;
				return NULL;
			}
			else if(temp->izq != NULL && temp->der == NULL) //temp tiene hijo izquierdo pero no derecho
			{
				Nodo<T> *regresar=temp->izq;
				delete temp;
				return regresar;
			}
			else if(temp->izq==NULL &&temp->der!=NULL)
			{
				Nodo<T> *regresar=temp->der;
				delete temp;
				return regresar;
			}
			else //el nodo a borrar tiene 2 hijos
			{
				Nodo<T> *sucesor=temp->der;
				while(sucesor->izq!=NULL)
				{
					sucesor=sucesor->izq;
				}
				temp->value=sucesor->value;
				temp->der=eliminar(temp->value, temp->der);
			}
		}
		return temp;
	}
	
	//PROFUNDIDAD DE UN NODO
	int profundidad(T value)
	{
		Nodo<T> *temp=root;
		int prof=0;
		while(temp!=NULL)
		{
			if(temp->value==value)
			{
				return prof;
			}
			else if(value<temp->value)
			{
				temp=temp->izq;
				prof++;
			}
			else
			{
				temp=temp->der;
				prof++;
			}
		}
		return -1; //no existe en el arbol
	}

	//ALTURA DE UN NODO
	int altura(T value)
	{
		Nodo<T> *temp=root;
		int alt=0;
		while(temp!=NULL)
		{
			if(temp->value==value)
			{
				return altura(temp);
			}
			else if(value<temp->value)
			{
				temp=temp->izq;
			}
			else
			{
				temp=temp->der;
				alt++;
			}
		}
		return -1; //no existe en el arbol
	}

	//ALTURA DE UN ARBOL
	int alturaArbol()
	{
		if(root!=NULL)
		{
			return altura(root);
		}
		return -1;
	}

	int altura(Nodo<T> *temp)
	{
		if(temp==NULL)
		{
			return 0;
		}
		else
		{
			int aIzq=altura(temp->izq);
			int aDer=altura(temp->der);
			if(aIzq>aDer)
			{
				return aIzq+1;
			}
			else
			{
				return aDer+1;
			}
		}
	}

	//DESCENDIENTES DE UN NODO
	void descendientes(T value)
	{
		if(root == NULL)
		{
			cout << "No tiene descendientes" << endl;
		}
		else
		{
			descendientes(value, root);
		}		
	}

	bool descendientes(T value, Nodo<T> *temp)
	{
		//si no tiene descendientes
		if(temp == NULL)
		{
			cout << temp->value << ",";
			return false;
		}

		else if(temp->value == value)
		{
			if(temp->izq != NULL)
			{
				return descendientes(value, temp->izq);
				cout << temp->izq->value << ",";
			}
			else if (temp->der != NULL)
			{
				return descendientes(value, temp->der);
				cout << temp->izq->value << ",";
			}
			return false;	
		}

		else if (temp->izq != NULL)
		{
			return descendientes(value, temp->izq);
			cout << temp->value << ",";
			return descendientes(value, temp->der);
			return true;
		}
		
		else if(value < temp->value) //buscar lado izquierdo
		{
			return descendientes(value, temp->izq);
		}
		else if(value > temp->value) //buscar lado derecho
		{
			return descendientes(value, temp->der); 
		}

		return false;
	}
	
	//TODOS LOS ANCESTROS DE UN NODO
	void ancestros(T value)
	{
		ancestros(value, root);
	}

	bool ancestros(T value, Nodo<T> *temp)
	{
		if(temp == NULL)
		{
			return false;
		}
		else if(temp->value == value)
		{
			return true;
		}
		else if(ancestros(value, temp->izq) || ancestros(value, temp->der))
		{
			cout << temp->value << ",";
			return true;
		}
		return false;
	}

	//CHECA SI UN NODO ES ANCESTRO DE OTRO
	void checarAncestro(T ancestro, T descendiente)
	{
		if(checarAncestro(ancestro, descendiente, root) == true)
		{
			cout << ancestro << " es ancestro de " << descendiente << endl;
		}
		else
		{
			cout << ancestro << " NO es ancestro de " << descendiente << endl;
		}	
	}

	bool checarAncestro(T ancestro, T descendiente, Nodo<T> *temp)
	{
		if(temp == NULL)
		{
			return false;
		}
		else if(temp->value == descendiente)
		{
			return true;
		}
		else if(checarAncestro(ancestro, descendiente, temp->izq) || checarAncestro(ancestro, descendiente, temp->der))
		{
			return true;
		}
		return false;
	}

	int buscarNivel(T buscado, int nivel, Nodo<T> *temp)
	{
		if(temp == NULL)
		{
			return 0;
		}
		else if(buscado < temp->value)
		{
			nivel++;
			return buscarNivel(buscado, nivel, temp->izq);
		}
		else if(buscado > temp->value)
		{
			nivel++;
			return buscarNivel(buscado, nivel, temp->der);
		}
		else if(temp->value == buscado)
		{
			return nivel;
		}
		return 0;
	}

	//NODOS EN MISMO NIVEL
	void mismoNivel(T buscado)
	{
		int nivel = buscarNivel(buscado, 0, root);
		mismoNivel(root, 0, nivel);
		cout << endl;
	}
	
	void mismoNivel(Nodo<T> *temp, int nivel, T nivelBuscado)
	{
		if(temp!=NULL)
		{			
			if(nivelBuscado == nivel)
			{
				cout << temp->value << " ";
			}
			else
			{
				mismoNivel(temp->der, nivel+1, nivelBuscado);
				mismoNivel(temp->izq, nivel+1, nivelBuscado);
			}			
		}
	}

	//NODOS HERMANOS
	void hermano(T value)
	{
		if(root == NULL)
		{
			cout << "No tiene hermano" << endl;;
		}
		else
		{
			hermano(value, root);
		}	
	}

	bool hermano(T value, Nodo<T> *temp)
	{
		if(temp == NULL && temp->value == value)
		{
			cout << "No tiene hermano" << endl;
			return false;
		}		
		//si el hermano esta del lado derecho
		else if(temp->izq != NULL && temp->izq->value == value)
		{
			cout << "El hermano de " << value << " es: " << temp->der->value << endl;
			return true;
		}
		//si el hermano esta del lado izquierdo
		else if(temp->der != NULL && temp->der->value == value)
		{
			cout << "El hermano de " << value << " es: " << temp->izq->value << endl;
			return true;
		}
		else if(value < temp->value) //buscar lado izquierdo
		{
			return hermano(value, temp->izq);
		}
		else
		{
			return hermano(value, temp->der); //buscar lado derecho
		}
		return false;
	}

	//CHECAR SI DOS NODOS SON HEMANOS
	void hermanos(T value1, T value2)
	{
		if(hermanos(value1, value2, root) == true)
		{
			cout << value1 << " y " << value2 << " son hermanos" << endl;
		}
		else
		{
			cout << value1 << " y " << value2 << " NO son hermanos" << endl;
		}	
	}

	bool hermanos(T value1, T value2, Nodo<T> *temp)
	{
		if(temp == NULL)
		{
			return false;
		}		
		//checa hijos del temp
		else if(temp->izq->value == value1 && temp->der->value == value2)
		{
			return true;
		}
		else if(temp->izq->value == value2 && temp->der->value == value1)
		{
			return true;
		}
		else if(value1 < temp->value)
		{
			return hermanos(value1, value2, temp->izq);
		}
		else if(value1 > temp->value)
		{
			return hermanos(value1, value2, temp->der);
		}
		return false;
	}

	void inorderNivel(int buscado)
	{
		inorderNivel(root, 2, buscado);
		cout<<endl;
	}
	
	void inorderNivel(Nodo<T> *temp, int nivel, int nivelBuscado)
	{
		if(temp!=NULL)
		{
			inorderNivel(temp->izq, nivel+1, nivelBuscado);
			if(nivelBuscado==nivel)
			{
				cout<<temp->value<<" ";
			}
			inorderNivel(temp->der, nivel+1, nivelBuscado);
		}
	}
};

int main(){
	BST<int> tree;
	tree.insertar(50);
	tree.insertar(20);
	tree.insertar(70);
	tree.insertar(10);
	tree.insertar(30);
	tree.insertar(60);
	tree.insertar(80);	

	/*1*/ cout << "Profundidad de 10: " << tree.profundidad(10) << endl;
	/*2*/ cout << "Altura de 20: " << tree.altura(20) << endl;
	/*3*/ cout << "Altura del arbol: " << tree.alturaArbol() << endl;
	/*5*/ cout << "Ancestros de 10: "; tree.ancestros(10); cout << endl;
	/*6*/ tree.checarAncestro(50,10);
	/*7*/ cout << "Nodos en el mismo nivel que 10: "; tree.mismoNivel(10);
	/*9*/ tree.hermanos(10,30);
	/*10*/ tree.hermano(20);
	return 0;
}