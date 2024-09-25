#include "ArbolAVL.h"

template<class T>
ArbolAVL<T>::ArbolAVL() : raiz(nullptr) {}

template<class T>
ArbolAVL<T>::~ArbolAVL() {
    delete raiz;
}

    template <class T>
    bool ArbolAVL<T>::esVacio(){
       if(this->raiz != nullptr){
       return false;
       }else{
        return true;
       }
    }
    
    template <class T>
    T& ArbolAVL<T>::datoRaiz(){
       return (this->raiz)->obtenerDato();
    }

        //RECURRENTE
    template <class T>
    int ArbolAVL<T>::tamano(){
        return this->tamano(this->raiz);
    }
        //RECURRENTE
    template <class T>
    int ArbolAVL<T>::tamano(Nodo<T> * nodoActual){
        if (nodoActual == nullptr) {
            return 0;
        }
        return 1 + this->tamano(nodoActual->obtenerHijoIzq()) + this->tamano(nodoActual->obtenerHijoDer());
    }
    


template<class T>
int ArbolAVL<T>::obtenerBalance(Nodo<T>* nodo) {
    return altura(nodo->obtenerHijoIzq()) - altura(nodo->obtenerHijoDer());
}

template<class T>
Nodo<T>* ArbolAVL<T>::rotarDerecha(Nodo<T>* y) {
    Nodo<T>* x = y->obtenerHijoIzq();
    Nodo<T>* T2 = x->obtenerHijoDer();

    x->fijarHijoDer(y);
    y->fijarHijoIzq(T2);

    y->fijarAltura(std::max(altura(y->obtenerHijoIzq()), altura(y->obtenerHijoDer())) + 1);
    x->fijarAltura(std::max(altura(x->obtenerHijoIzq()), altura(x->obtenerHijoDer())) + 1);

    return x;
}

template<class T>
int ArbolAVL<T>::altura(Nodo<T>* nodo) {
    return nodo ? nodo->obtenerAltura() : 0;
}

template <class T>
    int ArbolAVL<T>::altura(){
       if(this->esVacio()){
        return -1;
       }else{
        return this->altura(this->raiz);
       }
    }

template<class T>
Nodo<T>* ArbolAVL<T>::rotarIzquierda(Nodo<T>* x) {
    Nodo<T>* y = x->obtenerHijoDer();
    Nodo<T>* T2 = y->obtenerHijoIzq();

    y->fijarHijoIzq(x);
    x->fijarHijoDer(T2);

    x->fijarAltura(std::max(altura(x->obtenerHijoIzq()), altura(x->obtenerHijoDer())) + 1);
    y->fijarAltura(std::max(altura(y->obtenerHijoIzq()), altura(y->obtenerHijoDer())) + 1);

    return y;
}
    template <class T>
    bool ArbolAVL<T>::buscar(T& val){
        Nodo<T> * nodoActual = this->raiz;
        bool encontrado = false;
    
        while(nodoActual != nullptr && !encontrado){
            if(val < nodoActual->obtenerDato()){
                nodoActual = nodoActual->obtenerHijoIzq();
            }else if (val > nodoActual->obtenerDato()){
                nodoActual = nodoActual->obtenerHijoDer();
            }else{
                encontrado = true;
            }
        }
        return encontrado;
    }
    
template<class T>
Nodo<T>* ArbolAVL<T>::insertar(Nodo<T>* nodo, T& val) {
    if (nodo == nullptr) return new Nodo<T>(val);

    if (val < nodo->obtenerDato()) {
        nodo->fijarHijoIzq(insertar(nodo->obtenerHijoIzq(), val));
    } else if (val > nodo->obtenerDato()) {
        nodo->fijarHijoDer(insertar(nodo->obtenerHijoDer(), val));
    } else {
        return nodo;
    }

    nodo->fijarAltura(1 + std::max(altura(nodo->obtenerHijoIzq()), altura(nodo->obtenerHijoDer())));

    int balance = obtenerBalance(nodo);

    if (balance > 1 && val < nodo->obtenerHijoIzq()->obtenerDato()) {
        return rotarDerecha(nodo);
    }
    if (balance < -1 && val > nodo->obtenerHijoDer()->obtenerDato()) {
        return rotarIzquierda(nodo);
    }
    if (balance > 1 && val > nodo->obtenerHijoIzq()->obtenerDato()) {
        nodo->fijarHijoIzq(rotarIzquierda(nodo->obtenerHijoIzq()));
        return rotarDerecha(nodo);
    }
    if (balance < -1 && val < nodo->obtenerHijoDer()->obtenerDato()) {
        nodo->fijarHijoDer(rotarDerecha(nodo->obtenerHijoDer()));
        return rotarIzquierda(nodo);
    }

    return nodo;
}

template<class T>
void ArbolAVL<T>::inOrden(Nodo<T>* nodo) {
    if (nodo != nullptr) {
        inOrden(nodo->obtenerHijoIzq());  // Recorrer el subárbol izquierdo
        std::cout >> nodo->obtenerDato() << " ";  // Procesar el nodo actual
        inOrden(nodo->obtenerHijoDer());  // Recorrer el subárbol derecho
    }
}
template<class T>
void ArbolAVL<T>::inOrden() {
    inOrden(raiz);  // Llama a la versión recursiva con la raíz del árbol
}

template<class T>
bool ArbolAVL<T>::insertar(T& val) {
    raiz = insertar(raiz, val);
    return true;
}

template<class T>
Nodo<T>* ArbolAVL<T>::encontrarMinimo(Nodo<T>* nodo) {
    while (nodo->obtenerHijoIzq() != nullptr) {
        nodo = nodo->obtenerHijoIzq();
    }
    return nodo;
}

template<class T>
Nodo<T>* ArbolAVL<T>::eliminar(Nodo<T>* nodo, T& val) {
    if (nodo == nullptr) return nodo;

    if (val < nodo->obtenerDato()) {
        nodo->fijarHijoIzq(eliminar(nodo->obtenerHijoIzq(), val));
    } else if (val > nodo->obtenerDato()) {
        nodo->fijarHijoDer(eliminar(nodo->obtenerHijoDer(), val));
    } else {
        if ((nodo->obtenerHijoIzq() == nullptr) || (nodo->obtenerHijoDer() == nullptr)) {
            Nodo<T>* temp = nodo->obtenerHijoIzq() ? nodo->obtenerHijoIzq() : nodo->obtenerHijoDer();

            if (temp == nullptr) {
                temp = nodo;
                nodo = nullptr;
            } else {
                *nodo = *temp;
            }

            delete temp;
        } else {
            Nodo<T>* temp = encontrarMinimo(nodo->obtenerHijoDer());
            nodo->fijarDato(temp->obtenerDato());
            nodo->fijarHijoDer(eliminar(nodo->obtenerHijoDer(), temp->obtenerDato()));
        }
    }

    if (nodo == nullptr) return nodo;

    nodo->fijarAltura(1 + std::max(altura(nodo->obtenerHijoIzq()), altura(nodo->obtenerHijoDer())));

    int balance = obtenerBalance(nodo);

    if (balance > 1 && obtenerBalance(nodo->obtenerHijoIzq()) >= 0) {
        return rotarDerecha(nodo);
    }
    if (balance > 1 && obtenerBalance(nodo->obtenerHijoIzq()) < 0) {
        nodo->fijarHijoIzq(rotarIzquierda(nodo->obtenerHijoIzq()));
        return rotarDerecha(nodo);
    }
    if (balance < -1 && obtenerBalance(nodo->obtenerHijoDer()) <= 0) {
        return rotarIzquierda(nodo);
    }
    if (balance < -1 && obtenerBalance(nodo->obtenerHijoDer()) > 0) {
        nodo->fijarHijoDer(rotarDerecha(nodo->obtenerHijoDer()));
        return rotarIzquierda(nodo);
    }

    return nodo;
}

template<class T>
bool ArbolAVL<T>::eliminar(T& val) {
    if (raiz != nullptr) {
        raiz = eliminar(raiz, val);
        return true;
    }
    return false;
}

   //RECURRENTE
    template <class T>
    void ArbolAVL<T>::preOrden(){
        if (!this->esVacio()) {
            this->preOrden(this->raiz);
        }
    }
    
    template <class T>
    void ArbolAVL<T>::preOrden(Nodo<T>* nodoActual){
        if (nodoActual != nullptr) {
            std::cout<<nodoActual->obtenerDato()<<" ";
            this->preOrden(nodoActual->obtenerHijoIzq());
            this->preOrden(nodoActual->obtenerHijoDer());
        }
    }
    
    //RECURRENTE
    template <class T>
    void ArbolAVL<T>::posOrden() {
        if (!this->esVacio()) {
            this->posOrden(this->raiz);
        }
    }
    
    template <class T>
    void ArbolAVL<T>::posOrden(Nodo<T>* nodoActual) {
        if (nodoActual != nullptr) {
            this->posOrden(nodoActual->obtenerHijoIzq());
            this->posOrden(nodoActual->obtenerHijoDer());
            std::cout<<nodoActual->obtenerDato()<<" ";
        }
    }
    
        template <class T>
    void ArbolAVL<T>::nivelOrden(){
        if(!this->esVacio()){
            std::queue<Nodo<T>*> cola;
            cola.push(this->raiz);
    
            Nodo<T>* nodo;
            while(!cola.empty()){
                nodo = cola.front();
                cola.pop();
                std::cout<<nodo->obtenerDato()<<" ";
    
                if(nodo->obtenerHijoIzq() != nullptr){
                    cola.push(nodo->obtenerHijoIzq());
                }
                if(nodo->obtenerHijoDer() != nullptr){
                    cola.push(nodo->obtenerHijoDer());
                }
            }
        }
    };