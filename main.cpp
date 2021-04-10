#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
using namespace std;

string arquivo="NomeRG10.txt";
string arquivonovoseq="NomeRG10Seq_modificado.txt";
string arquivonovoenc="NomeRG10Enc_modificado.txt";

//97148076

struct PessoaRGSeq{
	string nome;
	int rg;
};

struct PessoaRGEnc{
	string nome;
	int rg;
	struct PessoaRGEnc* proximo=NULL;
};

int tamanhoarquivo(void){
	int i=0;

	string line;
	ifstream myfile (arquivo);
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
    	{
			i++;
		}
	myfile.close();
	}

	else cout << "Unable to open file";

	return i;
}

void imprimesequencial(int i, PessoaRGSeq listaPessoas[]){
    int n=0;

    while(n<i)
    {
        cout << listaPessoas[n].nome<<", "<<listaPessoas[n].rg<<endl;
        n++;
    }
}

void imprimeencadeada(PessoaRGEnc *inicio){
    PessoaRGEnc *rodando;

	rodando=inicio->proximo;
	while(rodando!=NULL)
	{
		cout << rodando->nome<<", "<<rodando->rg<<endl;
		rodando=rodando->proximo;
	}
}

PessoaRGSeq * armazenaarquivoSeq(int i, PessoaRGSeq listaPessoas[]){
    auto start = std::chrono::high_resolution_clock::now();

	int pos, cont=0, n=0, movimentacao=0, comparacao=0;

	string line;
	ifstream myfile (arquivo);
	if (myfile.is_open())
	{
	    comparacao++;
		while ( getline (myfile,line) )
    	{
			pos = line.find(',');
            listaPessoas[cont].nome = line.substr(0, pos);
			movimentacao++;
            listaPessoas[cont].rg = stoi(line.substr(pos+1));
			movimentacao++;
            cont++;
            comparacao++;
		}
	myfile.close();
	}

	cout << "Lista Sequencial\n";
    imprimesequencial(i, listaPessoas);

	auto result = std::chrono::high_resolution_clock::now() - start;
    long long microsegundos = std::chrono::duration_cast<std::chrono::microseconds>(result).count();
    cout << "A execucao sequencial demorou " << microsegundos << " microsegundo(s)" << endl;
	cout << "Foram feitas " << movimentacao << " movimentacao(oes)" << endl;
	cout << "Foram feitas " << comparacao << " comparacao(oes)" << endl;

	return listaPessoas;
}

void armazenaarquivoEnc(PessoaRGEnc *inicio){
    auto start = std::chrono::high_resolution_clock::now();

	int pos, cont=0, movimentacao=0, comparacao=0;
	string line;

	PessoaRGEnc *listaPessoasRGEnc = new PessoaRGEnc, *lista2;
	inicio->proximo=listaPessoasRGEnc;
	movimentacao++;

	ifstream myfile (arquivo);
	if (myfile.is_open())
	{
	    comparacao++;
		while ( getline (myfile,line) )
    	{
			pos = line.find(',');
            listaPessoasRGEnc->nome = line.substr(0, pos);
			movimentacao++;
            listaPessoasRGEnc->rg = stoi(line.substr(pos+1));
			movimentacao++;
			lista2 = new PessoaRGEnc;
			listaPessoasRGEnc->proximo = lista2;
			movimentacao++;
			listaPessoasRGEnc = lista2;
			movimentacao++;
			comparacao++;
		}
	myfile.close();
	}
	listaPessoasRGEnc=NULL;

	cout << "Lista Encadeada\n";
	imprimeencadeada(inicio);

	auto result = std::chrono::high_resolution_clock::now() - start;
    long long microsegundos = std::chrono::duration_cast<std::chrono::microseconds>(result).count();
    cout << "A execucao encadeada demorou " << microsegundos << " microsegundos(s)" << endl;
	cout << "Foram feitas " << movimentacao << " movimentacao(oes)" << endl;
	cout << "Foram feitas " << comparacao << " comparacao(oes)" << endl;

}

PessoaRGSeq * inseririnicioseq(int i, PessoaRGSeq listaPessoasSeq[]){
    auto start = std::chrono::high_resolution_clock::now();

    PessoaRGSeq *novo = new PessoaRGSeq, *aux = new PessoaRGSeq;
    int cont=0, n=0, movimentacao=0, comparacao=0;

    cout << "\nInsira o nome:";
    cin >> novo->nome;
    cout << "Insira o RG:";
    cin >> novo->rg;

	aux->nome='0';
	aux->rg=0;

    while(cont<i+1){
        aux->nome=listaPessoasSeq[cont].nome;
		aux->rg=listaPessoasSeq[cont].rg;
		movimentacao++;

        listaPessoasSeq[cont].nome=novo->nome;
		listaPessoasSeq[cont].rg=novo->rg;
		movimentacao++;

        novo->nome=aux->nome;
		novo->rg=aux->rg;
		movimentacao++;
		cont++;
		comparacao++;
    }

    i++;
	imprimesequencial(i, listaPessoasSeq);

	auto result = std::chrono::high_resolution_clock::now() - start;
    long long microsegundos = std::chrono::duration_cast<std::chrono::microseconds>(result).count();
    cout << "A execucao sequencial demorou " << microsegundos << " microsegundo(s)" << endl;
	cout << "Foram feitas " << movimentacao << " movimentacao(oes)" << endl;
	cout << "Foram feitas " << comparacao << " comparacao(oes)" << endl;

	return listaPessoasSeq;
}

void inseririnicioenc(PessoaRGEnc *inicio){
	auto start = std::chrono::high_resolution_clock::now();

	PessoaRGEnc *novo = new PessoaRGEnc, *listaPessoasRGEnc = new PessoaRGEnc, *lista;
	int movimentacao=0, comparacao=0;

    cout << "\nInsira o nome:";
    cin >> listaPessoasRGEnc->nome;
    cout << "Insira o RG:";
    cin >> listaPessoasRGEnc->rg;

	listaPessoasRGEnc->proximo = inicio->proximo;
	movimentacao++;

	inicio->proximo=listaPessoasRGEnc;
	movimentacao++;

	imprimeencadeada(inicio);

	auto result = std::chrono::high_resolution_clock::now() - start;
    long long microsegundos = std::chrono::duration_cast<std::chrono::microseconds>(result).count();
    cout << "A execucao encadeada demorou " << microsegundos << " microsegundos(s)" << endl;
	cout << "Foram feitas " << movimentacao << " movimentacao(oes)" << endl;
	cout << "Foram feitas " << comparacao << " comparacao(oes)" << endl;
}

PessoaRGSeq * inserirfimseq(int i, PessoaRGSeq listaPessoasSeq[]){
    auto start = std::chrono::high_resolution_clock::now();

	int n=0, movimentacao=0, comparacao=0;

    cout << "\nInsira o nome:";
    cin >> listaPessoasSeq[i].nome;
    cout << "Insira o RG:";
    cin >> listaPessoasSeq[i].rg;

    i++;
	imprimesequencial(i, listaPessoasSeq);

	auto result = std::chrono::high_resolution_clock::now() - start;
    long long microsegundos = std::chrono::duration_cast<std::chrono::microseconds>(result).count();
    cout << "A execucao sequencial demorou " << microsegundos << " microsegundo(s)" << endl;
	cout << "Foram feitas " << movimentacao << " movimentacao(oes)" << endl;
	cout << "Foram feitas " << comparacao << " comparacao(oes)" << endl;

	return listaPessoasSeq;
}

void inserirfimenc(PessoaRGEnc *inicio){
	auto start = std::chrono::high_resolution_clock::now();

	PessoaRGEnc *listaPessoasEnc = new PessoaRGEnc, *lista;
	int flag=0, movimentacao=0, comparacao=0;

    cout << "\nInsira o nome:";
    cin >> listaPessoasEnc->nome;
    cout << "Insira o RG:";
    cin >> listaPessoasEnc->rg;

	lista=inicio->proximo;
	movimentacao++;
	while(flag==0)
	{
	    comparacao++;
		 if(lista->proximo->nome == "")
		{
			lista->proximo=listaPessoasEnc;
			movimentacao++;
			flag=1;
			comparacao++;
		}
		lista=lista->proximo;
		movimentacao++;
	}

	imprimeencadeada(inicio);

	auto result = std::chrono::high_resolution_clock::now() - start;
    long long microsegundos = std::chrono::duration_cast<std::chrono::microseconds>(result).count();
    cout << "A execucao encadeada demorou " << microsegundos << " microsegundos(s)" << endl;
	cout << "Foram feitas " << movimentacao << " movimentacao(oes)" << endl;
	cout << "Foram feitas " << comparacao << " comparacao(oes)" << endl;
}

PessoaRGSeq * inserirNseq(int i, PessoaRGSeq listaPessoasSeq[]){
	PessoaRGSeq *novo = new PessoaRGSeq, *aux = new PessoaRGSeq;
    int cont, n, contador=0, movimentacao=0, comparacao=0;

	cout << "\nInsira a posicao em que deseja colocar o novo registro:";
	cin >> n;

	auto start = std::chrono::high_resolution_clock::now();

    cout << "\nInsira o nome:";
    cin >> novo->nome;
    cout << "Insira o RG:";
    cin >> novo->rg;

	aux->nome='0';
	movimentacao++;
	aux->rg='0';
	movimentacao++;

	cont=n-1;
	movimentacao++;

    while(cont<i+1){
        aux->nome=listaPessoasSeq[cont].nome;
		movimentacao++;
		aux->rg=listaPessoasSeq[cont].rg;
		movimentacao++;

        listaPessoasSeq[cont].nome=novo->nome;
		movimentacao++;
		listaPessoasSeq[cont].rg=novo->rg;
		movimentacao++;

        novo->nome=aux->nome;
		movimentacao++;
		novo->rg=aux->rg;
		movimentacao++;
		cont++;
		comparacao++;
    }

    i++;
	imprimesequencial(i, listaPessoasSeq);

	auto result = std::chrono::high_resolution_clock::now() - start;
    long long microsegundos = std::chrono::duration_cast<std::chrono::microseconds>(result).count();
    cout << "A execucao sequencial demorou " << microsegundos << " microsegundo(s)" << endl;
	cout << "Foram feitas " << movimentacao << " movimentacao(oes)" << endl;
	cout << "Foram feitas " << comparacao << " comparacao(oes)" << endl;

	return listaPessoasSeq;
}

void inserirNenc(PessoaRGEnc *inicio){
	int cont=1, n, movimentacao=0, comparacao=0;

	cout << "\nInsira a posicao em que deseja colocar o novo registro:";
	cin >> n;

	auto start = std::chrono::high_resolution_clock::now();

	PessoaRGEnc *listaPessoasEnc = new PessoaRGEnc, *lista, *penultimo, *rodando;

    cout << "\nInsira o nome:";
    cin >> listaPessoasEnc->nome;
    cout << "Insira o RG:";
    cin >> listaPessoasEnc->rg;

	lista=inicio->proximo;
	penultimo=inicio;
	movimentacao++;
	while((lista!=NULL) && (cont<n))
	{
		penultimo=lista;
		movimentacao++;
		lista=lista->proximo;
		movimentacao++;
		cont++;
		comparacao++;
	}
	penultimo->proximo=listaPessoasEnc;
	movimentacao++;
	listaPessoasEnc->proximo=lista;
	movimentacao++;

	imprimeencadeada(inicio);

	auto result = std::chrono::high_resolution_clock::now() - start;
    long long microsegundos = std::chrono::duration_cast<std::chrono::microseconds>(result).count();
    cout << "A execucao encadeada demorou " << microsegundos << " microsegundos(s)" << endl;
	cout << "Foram feitas " << movimentacao << " movimentacao(oes)" << endl;
	cout << "Foram feitas " << comparacao << " comparacao(oes)" << endl;
}

PessoaRGSeq * removerinicioseq(int i, PessoaRGSeq listaPessoasSeq[]){
	auto start = std::chrono::high_resolution_clock::now();

    int cont=1, n=0, movimentacao=0, comparacao=0;

    while(cont<=i){
        comparacao++;
		if(cont==i)
		{
			listaPessoasSeq[cont].nome=' ';
			movimentacao++;
			listaPessoasSeq[cont].rg=' ';
			movimentacao++;
			comparacao++;

		}
		else
		{
			listaPessoasSeq[cont-1].nome=listaPessoasSeq[cont].nome;
			movimentacao++;
			listaPessoasSeq[cont-1].rg=listaPessoasSeq[cont].rg;
			movimentacao++;
			comparacao++;
		}
		cont++;
	}

	i--;
	imprimesequencial(i, listaPessoasSeq);

	auto result = std::chrono::high_resolution_clock::now() - start;
    long long microsegundos = std::chrono::duration_cast<std::chrono::microseconds>(result).count();
    cout << "A execucao sequencial demorou " << microsegundos << " microsegundo(s)" << endl;
	cout << "Foram feitas " << movimentacao << " movimentacao(oes)" << endl;
	cout << "Foram feitas " << comparacao << " comparacao(oes)" << endl;

	return listaPessoasSeq;
}

void removerinicioenc(PessoaRGEnc *inicio){
	auto start = std::chrono::high_resolution_clock::now();

	PessoaRGEnc *listaPessoasEnc = new PessoaRGEnc, *lista, *rodando;
	int flag=0, movimentacao=0, comparacao=0;

	lista=inicio->proximo;
	movimentacao++;

	lista=lista->proximo;
	movimentacao++;

	inicio->proximo=lista;

	imprimeencadeada(inicio);

	auto result = std::chrono::high_resolution_clock::now() - start;
    long long microsegundos = std::chrono::duration_cast<std::chrono::microseconds>(result).count();
    cout << "A execucao encadeada demorou " << microsegundos << " microsegundos(s)" << endl;
	cout << "Foram feitas " << movimentacao << " movimentacao(oes)" << endl;
	cout << "Foram feitas " << comparacao << " comparacao(oes)" << endl;
}

PessoaRGSeq * removerfimseq(int i, PessoaRGSeq listaPessoasSeq[]){
	auto start = std::chrono::high_resolution_clock::now();

	int n=0, movimentacao=0, comparacao=0;

    listaPessoasSeq[i-1].nome=' ';
	movimentacao++;
	listaPessoasSeq[i-1].rg=' ';
	movimentacao++;

	i--;
	imprimesequencial(i, listaPessoasSeq);

	auto result = std::chrono::high_resolution_clock::now() - start;
    long long microsegundos = std::chrono::duration_cast<std::chrono::microseconds>(result).count();
    cout << "A execucao sequencial demorou " << microsegundos << " microsegundo(s)" << endl;
	cout << "Foram feitas " << movimentacao << " movimentacao(oes)" << endl;
	cout << "Foram feitas " << comparacao << " comparacao(oes)" << endl;

	return listaPessoasSeq;
}

void removerfimenc(PessoaRGEnc *inicio){
	auto start = std::chrono::high_resolution_clock::now();

	PessoaRGEnc *listaPessoasEnc = new PessoaRGEnc, *lista, *rodando;
	int flag=0, movimentacao=0, comparacao=0;

	lista=inicio->proximo;
	movimentacao++;
	while(flag==0)
	{
	    comparacao++;
		if(lista->proximo->proximo == NULL)
		{
			lista->proximo=NULL;
			movimentacao++;
			flag=1;
			comparacao++;
		}
		lista=lista->proximo;
		movimentacao++;
	}

	imprimeencadeada(inicio);

	auto result = std::chrono::high_resolution_clock::now() - start;
    long long microsegundos = std::chrono::duration_cast<std::chrono::microseconds>(result).count();
    cout << "A execucao encadeada demorou " << microsegundos << " microsegundos(s)" << endl;
	cout << "Foram feitas " << movimentacao << " movimentacao(oes)" << endl;
	cout << "Foram feitas " << comparacao << " comparacao(oes)" << endl;
}

PessoaRGSeq * removerNseq(int i, PessoaRGSeq listaPessoasSeq[]){
	int cont, n, contador=0, movimentacao=0, comparacao=0;

	cout << "\nInsira a posicao em que deseja remover um registro:";
	cin >> n;

	auto start = std::chrono::high_resolution_clock::now();

	cont=n-1;
	movimentacao++;

    while(cont<=i-1){
        comparacao++;
		if(cont==i-1)
		{
			listaPessoasSeq[cont].nome=' ';
			movimentacao++;
			listaPessoasSeq[cont].rg=' ';
			movimentacao++;
			comparacao++;

		}
		else
		{
			listaPessoasSeq[cont].nome=listaPessoasSeq[cont+1].nome;
			movimentacao++;
			listaPessoasSeq[cont].rg=listaPessoasSeq[cont+1].rg;
			movimentacao++;
			comparacao++;
		}
		cont++;
	}

	i--;
	imprimesequencial(i, listaPessoasSeq);

	auto result = std::chrono::high_resolution_clock::now() - start;
    long long microsegundos = std::chrono::duration_cast<std::chrono::microseconds>(result).count();
    cout << "A execucao sequencial demorou " << microsegundos << " microsegundo(s)" << endl;
	cout << "Foram feitas " << movimentacao << " movimentacao(oes)" << endl;
	cout << "Foram feitas " << comparacao << " comparacao(oes)" << endl;

	return listaPessoasSeq;
}

void removerNenc(PessoaRGEnc *inicio){
	int cont=0, n, movimentacao=0, comparacao=0;

	cout << "\nInsira a posicao em que deseja remover um registro:";
	cin >> n;

	auto start = std::chrono::high_resolution_clock::now();

	PessoaRGEnc *listaPessoasEnc = new PessoaRGEnc, *lista, *penultimo, *rodando;

	lista=inicio->proximo;
	movimentacao++;
	while((lista!=NULL) && (cont<n-1))
	{
	    comparacao++;
		penultimo=lista;
		movimentacao++;
		lista=lista->proximo;
		movimentacao++;
		cont++;
	}
	penultimo->proximo=lista->proximo;
	movimentacao++;

	imprimeencadeada(inicio);

	auto result = std::chrono::high_resolution_clock::now() - start;
    long long microsegundos = std::chrono::duration_cast<std::chrono::microseconds>(result).count();
    cout << "A execucao encadeada demorou " << microsegundos << " microsegundos(s)" << endl;
	cout << "Foram feitas " << movimentacao << " movimentacao(oes)" << endl;
	cout << "Foram feitas " << comparacao << " comparacao(oes)" << endl;

}

void procurarRGseq(int i, PessoaRGSeq listaPessoasSeq[]){
	int n=0, flag=0, movimentacao=0, comparacao=0, rg;

	cout << "\nInsira o RG que deseja procurar: ";
	cin >> rg;
	//7237709
	auto start = std::chrono::high_resolution_clock::now();

	while(n<i){
        comparacao++;
		if(listaPessoasSeq[n].rg==rg)
		{
		    comparacao++;
			flag=1;
			break;
		}
		n++;
	}

	if(flag==1)
    {
		cout << "\n" << n+1 << " - " << listaPessoasSeq[n].nome << ", " << listaPessoasSeq[n].rg << endl;
		comparacao++;
    }
	else if(flag==0)
    {
		cout << "\nNao foi possivel encontrar o RG desejado" << endl;
        comparacao++;
	}

	auto result = std::chrono::high_resolution_clock::now() - start;
    long long microsegundos = std::chrono::duration_cast<std::chrono::microseconds>(result).count();
    cout << "A execucao sequencial demorou " << microsegundos << " microsegundo(s)" << endl;
	cout << "Foram feitas " << movimentacao << " movimentacao(oes)" << endl;
	cout << "Foram feitas " << comparacao << " comparacao(oes)" << endl;
}

void procurarRGenc(PessoaRGEnc *inicio){
	auto start = std::chrono::high_resolution_clock::now();

	PessoaRGEnc *rodando;
	int cont=0, movimentacao=0, flag=0, comparacao=0, rg;

	//7237709
	cout << "\nInsira o RG que deseja procurar: ";
	cin >> rg;

	rodando=inicio->proximo;
	movimentacao++;
	while(rodando->proximo!=NULL)
	{
	    comparacao++;
		if(rodando->rg==rg)
        {
            comparacao++;
			flag=1;
			break;
		}
		cont++;
		rodando=rodando->proximo;
		movimentacao++;
	}


	if(flag==1)
    {
        cout << "\n" << cont+1 << " - " << rodando->nome<<", "<<rodando->rg<<endl;
        comparacao++;
    }
	else if(flag==0)
    {
		cout << "\nNao foi possivel encontrar o RG desejado" << endl;
		comparacao++;
    }

	auto result = std::chrono::high_resolution_clock::now() - start;
    long long microsegundos = std::chrono::duration_cast<std::chrono::microseconds>(result).count();
    cout << "A execucao encadeada demorou " << microsegundos << " microsegundo(s)" << endl;
	cout << "Foram feitas " << movimentacao << " movimentacao(oes)" << endl;
	cout << "Foram feitas " << comparacao << " comparacao(oes)" << endl;
}

void salvaralteracoesseq(int i, PessoaRGSeq listaPessoasSeq[]){
    int n=0;

    ofstream myfile (arquivonovoseq);
    if (myfile.is_open())
    {
        while(n<i)
        {
            myfile << listaPessoasSeq[n].nome << "," << listaPessoasSeq[n].rg << endl;
            n++;
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    cout << "Alteracoes sequenciais salvas" << endl;
}

void salvaralteracoesenc(PessoaRGEnc *inicio){
    PessoaRGEnc *rodando;

    ofstream myfile (arquivonovoenc);
    if (myfile.is_open())
    {
        rodando=inicio->proximo;
        while(rodando->proximo!=NULL)
        {
            myfile << rodando->nome<<","<<rodando->rg<<endl;
            rodando=rodando->proximo;
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    cout << "Alteracoes encadeadas salvas" << endl;
}

void ordenaselectionseq(int i, PessoaRGSeq listaPessoasSeq[]){
	auto start = std::chrono::high_resolution_clock::now();

	int contador1=0, contador2, aux1, posicao,movimentacao=0,comparacao=0;
	PessoaRGSeq *aux2 = new PessoaRGSeq;
	aux2->nome="";
	aux2->rg=0;

	while(contador1<i){
		aux1=listaPessoasSeq[contador1].rg;
		movimentacao++;
		contador2=contador1+1;
		while(contador2<i){
			if(listaPessoasSeq[contador2].rg<aux1){
				aux1=listaPessoasSeq[contador2].rg;
				posicao=contador2;
				comparacao++;
			}
			contador2++;
		}
		aux2->nome=listaPessoasSeq[contador1].nome;
		aux2->rg=listaPessoasSeq[contador1].rg;
		movimentacao++;
		listaPessoasSeq[contador1].nome=listaPessoasSeq[posicao].nome;
		listaPessoasSeq[contador1].rg=listaPessoasSeq[posicao].rg;
		movimentacao++;
		listaPessoasSeq[posicao].nome=aux2->nome;
		listaPessoasSeq[posicao].rg=aux2->rg;
		movimentacao++;

		imprimesequencial(i, listaPessoasSeq);
		cout<<"\n";
		contador1++;
	}

	auto result = std::chrono::high_resolution_clock::now() - start;
    long long microsegundos = std::chrono::duration_cast<std::chrono::microseconds>(result).count();
    cout << "A execucao encadeada demorou " << microsegundos << " microsegundo(s)" << endl;
	cout << "Foram feitas " << movimentacao << " movimentacao(oes)" << endl;
	cout << "Foram feitas " << comparacao << " comparacao(oes)" << endl;
}

void ordenainsertionseq(int i, PessoaRGSeq listaPessoasSeq[]){
	auto start = std::chrono::high_resolution_clock::now();

	int aux1, n, movimentacao=0,comparacao=0;
	PessoaRGSeq *aux2=new PessoaRGSeq;
	aux2->nome="";
	aux2->rg=0;

	if(listaPessoasSeq[0].rg>listaPessoasSeq[1].rg){
		aux2->nome=listaPessoasSeq[0].nome;
		aux2->rg=listaPessoasSeq[0].rg;
		movimentacao++;
		listaPessoasSeq[0]=listaPessoasSeq[1];
		movimentacao++;
		listaPessoasSeq[1].nome=aux2->nome;
		listaPessoasSeq[1].rg=aux2->rg;
		movimentacao++;

		comparacao++;
		imprimesequencial(i, listaPessoasSeq);
	}

	n=2;

	while (n<=i){

	}

	auto result = std::chrono::high_resolution_clock::now() - start;
    long long microsegundos = std::chrono::duration_cast<std::chrono::microseconds>(result).count();
    cout << "A execucao encadeada demorou " << microsegundos << " microsegundo(s)" << endl;
	cout << "Foram feitas " << movimentacao << " movimentacao(oes)" << endl;
	cout << "Foram feitas " << comparacao << " comparacao(oes)" << endl;
}

int main (void){
	int i = tamanhoarquivo(), cont=0, escolha, n=0, ordena;
	PessoaRGSeq *listaPessoasSeq = new PessoaRGSeq[i+10];
	PessoaRGEnc inicio, *listaPessoasEnc;

	cout << "Listas iniciais" << endl;
    listaPessoasSeq = armazenaarquivoSeq(i, listaPessoasSeq);
    cout << '\n';
    armazenaarquivoEnc(&inicio);
    cout << '\n';

	do{
		cout << "\nEscolha a alteracao que deseja fazer:" << endl;
		cout << "1-Inserir registro no inicio da lista" << endl;
		cout << "2-Inserir registro no fim da lista" << endl;
		cout << "3-Inserir registro na posicao N" << endl;
		cout << "4-Remover registro do inicio da lista" << endl;
		cout << "5-Remover registro do fim da lista" << endl;
		cout << "6-Remover registro da posicao N" << endl;
		cout << "7-Procurar registro N" << endl;
		cout << "8-Sair" << endl;

		cout << "Insira o numero da sua escolha: ";
		cin >> escolha;

        switch(escolha){
            case(1):
                listaPessoasSeq = inseririnicioseq(i, listaPessoasSeq);
				inseririnicioenc(&inicio);
				i++;
				break;
            case(2):
                listaPessoasSeq = inserirfimseq(i, listaPessoasSeq);
                inserirfimenc(&inicio);
				i++;
				break;
            case(3):
                listaPessoasSeq = inserirNseq(i, listaPessoasSeq);
                inserirNenc(&inicio);
				i++;
				break;
            case(4):
                listaPessoasSeq = removerinicioseq(i, listaPessoasSeq);
                removerinicioenc(&inicio);
				i--;
				break;
            case(5):
                listaPessoasSeq = removerfimseq(i, listaPessoasSeq);
                removerfimenc(&inicio);
				i--;
				break;
            case(6):
                listaPessoasSeq = removerNseq(i, listaPessoasSeq);
                removerNenc(&inicio);
				i--;
				break;
            case(7):
                procurarRGseq(i, listaPessoasSeq);
                procurarRGenc(&inicio);
            case(8):
                break;
        }
	}while(escolha!=8);

	cout << "\nFormas de ordenação:" << endl;
	cout << "1-Selection sort" << endl;
	cout << "2-Insertion sort" << endl;
	cout << "\nEscolha a forma de ordenação crescente que deseja:" << endl;
	cin >> ordena;

	if(ordena==1){
		ordenaselectionseq(i, listaPessoasSeq);
		//ordenaselectionenc();
	}
	else if(ordena==2){
		ordenainsertionseq(i, listaPessoasSeq);
		//ordenainsertionenc();
	}
	else{
		cout << "Forma de ordenação invalida." << endl;
	}

	cout << "Salvando alteracoes . . ." << endl;
	//salvaralteracoesseq(i, listaPessoasSeq);
	//salvaralteracoesenc(&inicio);

	return 0;
}