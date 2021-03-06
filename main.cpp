#include<iostream>
#include<list>
#include<fstream>
#include <algorithm>

//ajuste: calcular o grau do vertice logo ap�s a leitura para facilitar nas outras duas fu��es;
//ajuste2: na fun��o do grau um dos for's era desnecess�rio e tava bugando o V05;
//ajuste3: separei o calculo do grau em uma fun��o separa para poder usar a mesma na de sequencia;

using namespace std;

int menu(){
    cout << "Digite a opcao desejada:\n\n";
    cout << "1- Arvore Geradora Minima\n";
    cout << "2- Grau vertice\n";
    cout << "3- Vertices finais\n";
    cout << "4- incidencia\n";
    cout << "5- Circuito\n";
    cout << "6- Sequencia de graus\n";
    cout << "7- Sair\n";
    int op;
    cin >> op;
    return op;

}

struct dados{
    int numero_v; // n�mero do v�rtice
    string rotulo;
    int numero_aresta;
    string rotulo_aresta;
    string v_inicial; // v�rtice inicial
    string v_final; // v�rtice final
    int custo;
    int grau;
};

struct arvore{
    string vertice;
    int distancia;
    string pai;
    string ar;
};

bool leitura_arq(list<dados> &grafo){
    ifstream arq;
    dados aux;
    int qtd;

    arq.open("grafo.txt");

    if(!arq){
        cout << "Erro ao abrir o arquivo!\n";
        return 0;
    }

    if(arq >> aux.numero_v){
        qtd = aux.numero_v;
        for(int i=0; i<qtd; i++){
            arq >> aux.rotulo;
            grafo.push_back(aux);
        }
    }

    if(arq >> aux.numero_aresta){
        qtd = aux.numero_aresta;
            for(int j=0; j<qtd; j++){
                arq >> aux.rotulo_aresta >> aux.v_inicial >> aux.v_final >> aux.custo;
                grafo.push_back(aux);
            }
    }

    return 0;
}

int calculo_grau(list<dados> grafo, string vertice){

    string v = vertice;
    int acum=0;

    for(auto it=grafo.begin(); it!=grafo.end(); it++){
        if(v == it->v_inicial || v == it->v_final){
            acum++;
        }
    }

    return acum;
}

bool grau(list<dados> grafo){
    string vertice;
    cout << "Digite o nome do vertice desejado: ";
    cin >> vertice;
    int g=0;

    cout << "\nGrau de " << vertice << ": ";

    g = calculo_grau(grafo, vertice);

    if(g>0) cout << g << endl << endl;

    if(g==0) cout << "Vertice inexistente\n" << endl << endl;

    return 0;
}

bool incidente(list<dados> grafo){
    dados aux;
    cout << "Digite o nome da aresta desejada: ";
    cin >> aux.rotulo_aresta;

    for(auto it=grafo.begin(); it!=grafo.end(); it++){
        if(aux.rotulo_aresta == it->rotulo_aresta){
            cout << it->v_inicial << "," << it->v_final << endl;
        }
    }

    return 0;
}

bool vertice_final(list<dados> &grafo){
    int cont, vf;
    list<dados>::iterator p=grafo.begin();
    string v;
    cont = p->numero_v;
   // cout << p->numero_v << endl;
    //cout << cont << endl;
    while(cont--){
        v = p->rotulo;
      //  cout << v << endl;
        vf = 0;
        for(auto it=grafo.begin(); it!=grafo.end(); it++){
            if(v == it->v_inicial || v == it->v_final){
                vf ++;
               // cout << vf << endl;
            }
        }
        p++;
    }
    if(vf==1){
            cout << "Vertice final: " << v << endl;

        }
        else{
            cout << "Nao ha vertices finais no grafo\n\n";
        }
}

bool sequencia(list<dados> grafo){

    int g=0, i=0, acum=0;

    for(auto it=grafo.begin(); it!=grafo.end(); it++){
        if(it->rotulo_aresta.size()>0) break;
        if(it->rotulo.size()>0){
            acum++;
        }
    }

    int vet[acum];

    cout << "\nG={";


    for(auto it=grafo.begin(); it!=grafo.end(); it++){
        if(it->rotulo_aresta.size()>0) break;
        g=calculo_grau(grafo, it->rotulo);
        vet[i]=g;
        i++;
    }

    sort(vet, vet+acum);

    for(i=0;i<acum;i++)
    {
        if(i>0) cout << ",";
        cout << vet[i];
    }

    cout << "}\n" << endl;
    return 0;
}

bool circuito(list<dados> &grafo){
    int cont;
    int acum = 0;
    list<dados>::iterator p=grafo.begin();
    string v;


        v = p->rotulo;

        for(auto it=grafo.begin(); it!=grafo.end(); it++){
            if(v != it->v_final && it->rotulo_aresta.size()>0){
                cout << it->v_inicial << " - ";
                cout << it->rotulo_aresta << " - ";
                acum++;
                p++;
            }
            else
                if(v == it->v_final && acum >= 2){
                cout << it->v_inicial << " - ";
                cout << it->rotulo_aresta << " - " << it->v_final << "." << endl;
                break;
                }
        }

    cout << endl;
}
bool menor_custo(list<dados> &grafo, list<arvore> &avm, string &vi){
    list<dados>::iterator f = grafo.begin();
    arvore ab;
    int inc =0;
    for(auto it=grafo.begin(); it!=grafo.end(); it++){
        if(vi == it->v_inicial || vi == it->v_final){
            inc ++;
        }
    }
    f = grafo.begin();
    int menor = f->custo;
    cout << f->custo << endl;
    for(int i=0; i<inc; i++){
        if(menor>f->custo) menor = f->custo;

        f++;
    }
        cout << menor << endl;
        f = grafo.begin();
        ab.distancia = menor;
    for(auto it=grafo.begin(); it!=grafo.end(); it++){
        if(menor == it->custo)
        ab.ar = it->rotulo_aresta;
    }
        avm.push_back(ab);
        cout << ab.pai << " " << ab.distancia << " " << ab.ar << endl;
}

bool arvore_minima(list<dados> grafo){
    list<arvore> avm;
    arvore al;
    list<dados>::iterator g = grafo.begin();
    int cont = g->numero_v;
    while(cont--){
        al.vertice = g->rotulo;
        avm.push_back(al);
        g++;
        cout << al.vertice << endl;
    }
    cout << "Digite o vertice inicial da arvore: ";
    string vi;
    cin >> vi;

    al.pai = vi;

    avm.push_back(al);

    menor_custo(grafo, avm, vi);


}

int main(){

    int op;
    list<dados> grafo;

    leitura_arq(grafo);

    do{
        op = menu();
        switch(op){
            case 1:
                arvore_minima(grafo);
                break;
            case 2:
                grau(grafo);
                break;
            case 3:
                vertice_final(grafo);
                break;
            case 4:
                incidente(grafo);
                break;
            case 5:
                circuito(grafo);
                break;
            case 6:
                sequencia(grafo);
                break;

            default:
        cout<<"Opcao invalida";
        break;
    }
    }while(op!=7);

    return 0;
}
