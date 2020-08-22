#include "vector.hpp"
#include <limits>
#include <algorithm>
#include <iostream>

// Construir lista vazia, mas com capacidade máxima informada.
vector::vector(unsigned int capacidade) {
    this->vetor = new int[capacidade];
    this->tamanho = 0;
    this->capacidade = capacidade;
}

// Construir lista com "tamanho" cópias do valor "inicial".
vector::vector(unsigned int tamanho, int inicial) {
    this->vetor = new int[tamanho];
    this->capacidade = tamanho;
    this->tamanho = tamanho;

    for(unsigned int i = 0; i < tamanho; i++) {
        this->vetor[i] = inicial;
    }
}


// --- Métodos de "Coleção" ---


// Inserir "elemento" na coleção. Sempre deve executar a inserção.
// FIXME Fazer realocação quando não houver espaço.
// NOTE  Observe que aumentar em apenas uma unidade não nos alivia da pressão que tínhamos antes...
void vector::inserir(int elemento) {

    //caso o tamanho seja maior que a capacidade, o mesmo vetor será realocado (com a primeira expressão aps realloc, não ser perdido os elementos já presentes no vetor após a realocação)
    if(this->tamanho >= this->capacidade){
        this -> vetor = (int*) realloc (this -> vetor, sizeof(int) * (this -> capacidade * 2));
       //this-> vetor[tamanho/2] = elemento;

       if(!this->tamanho){ //caso nao tenha tamanho suficiente abandona a execução do programa
            return;
        } else {
            this->capacidade = capacidade *2;
            this->vetor[tamanho] = elemento;
            this->tamanho++;
       }
    }else{
        this->vetor[tamanho] = elemento; //caso o vetor tenha tamanho suficiente ele aloca o elemento e aumenta em 1 o tamanho
        this->tamanho++;
    }
}

// Remover "elemento" da coleção.
// Retornar indicativo de sucesso da remoção.
// NOTE Necessário preservar a ordem relativa dos que restarem.
bool vector::remover(int elemento) {

    if(this->tamanho == 0) return false;

    bool elementoPertence = pertence(elemento);
    unsigned int indiceDoElemento = 0;


    if(elementoPertence == false){
        return false;
    }else{
        indiceDoElemento = obter_indice_de(elemento);
           if(indiceDoElemento == std::numeric_limits<unsigned int>::max()){
                return false;
           }else{
                for(int i = indiceDoElemento; i < this->tamanho; i++){
                    this->vetor[i-1] = this->vetor[i];
                }
                this->tamanho--;
                return true;
           }
           return false;
    }
}



// Determinar se "elemento" é um dos elementos ainda na coleção.
bool vector::pertence(int elemento) {

    if(this->tamanho == 0) return false;

    for(int i=0; i < this->tamanho; i++){
        if(vetor[i] == elemento) return true;
    }

    return false;
}


// --- Métodos de "Lista" ---

// Inserir "elemento" na lista de forma que ele passe a constar no índice "indice".
// NOTE Necessário preservar a ordem relativa dos demais elementos.
void vector::inserir_em(unsigned int indice, int elemento) {

    if (this->tamanho == this->capacidade) return;


        int indiceParaFor = indice;
        int indiceQueNaoAnda = indice; //guarda o valor do indice para que nao seja contado no for

            for (int elementoVetor = this->tamanho; elementoVetor >= indiceParaFor; elementoVetor--) { //o for vai deslocar os elementos apenas que forem maior/igual ao indice passado pra inserção
                this->vetor[elementoVetor + 1] = this->vetor[elementoVetor]; //deslocando os elementos pra frente a partir do indice que foi passado para a insercao
            }

            this->vetor[indiceQueNaoAnda] = elemento; //na posicao que esta desalocada e nao andou no for, o vetor nesta posicao vai receber o elemento
            this->tamanho++; //aumenta em o tamanho do vetor

}

// Remover o elemento associado a "indice".
// Retornar indicativo de sucesso da remoção.
bool vector::remover_de(unsigned int indice) {
    //primeiro caso de erro: nao remover caso a lista esteja vazia
    if (this->tamanho == 0){
        return false;
    }

    if(indice >= this->tamanho) return false; //caso o indice passado seja maior que o tamanho da lista, ele no está presente na lista, é falso
        //int indiceParaFor = indice;
        //int indiceQueNaoAnda = indice;

            for ( int elementoVetor = indice+1; elementoVetor < this->tamanho; elementoVetor++) { //o for vai deslocar os elementos apenas que forem maior/igual ao indice passado pra inserção
                this->vetor[elementoVetor - 1] = this->vetor[elementoVetor]; //deslocando os elementos pra tras partir do indice que foi passado para a remoção
            }

            this->tamanho--; //reduz em 1 o tamanho
            return true;
}

// Retornar o valor associado ao índice "indice".
// NOTE Quando o índice for inválido, retornar `std::numeric_limits<int>::max()`
//      (forma de obter o maior valor representável).
int vector::obter_elemento_em(unsigned int indice) {

    if(indice >= this->tamanho) return std::numeric_limits<int>::max(); //como o tamanho da lista é vazio, nao ha como retornar indice da lista

    if(this->tamanho == 0) return std::numeric_limits<int>::max();

    unsigned int i = 0;
        while(i <= this->tamanho){
            if(i == indice){
                return vetor[i];
            }
            i++;
        }
    return std::numeric_limits<int>::max();
}

// Retornar o índice associado a "elemento".
// NOTE Quando o índice for inválido, retornar `std::numeric_limits<unsigned int>::max()`
//      (forma de obter o maior valor representável).
unsigned int vector::obter_indice_de(int elemento) {

    bool indiceAssociado;
    if(this->tamanho == 0) return std::numeric_limits<unsigned int>:: max();

    indiceAssociado = pertence(elemento);

    if(!indiceAssociado){
        return false;
    } else {
        for( int i = 0; i < this-> tamanho; i++){
            if(vetor[i] == elemento) return vetor[i];
        }
    }
    //return std::numeric_limits<unsigned int>::max();
}
