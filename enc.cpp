/*void selection_SortEn(clienteEn *inicio)
{
    clienteEn *aux = new clienteEn;
    clienteEn *maior = inicio->proximo;
    aux = maior->proximo;
    int i = 1;
    while(aux->nome != "")
    {
        if(aux->rg > maior->rg)
        {
            maior->proximo = aux;
            aux->anterior = maior;
            maior = aux;
        }
        else
        {
            clienteEn *aux2 = new clienteEn;
            aux2 = maior->anterior;
            maior->proximo = aux->proximo;
            while(aux2 != NULL && aux->rg < aux2->rg)
            {
                aux2 = aux2->anterior;
            }
            if(aux2!=NULL)
            {
                aux->proximo = aux2->proximo;
                aux2->proximo->anterior = aux;
                aux2->proximo = aux;
                aux->anterior = aux2;
            }
            else
            {
                aux->proximo->anterior = aux->anterior;
                inicio->proximo->anterior = aux;
                aux->proximo = inicio->proximo;
                aux->anterior = NULL;
                inicio->proximo = aux;
            }

        }
        imprimeUsuariosEn(*inicio);
        getchar();
        system("cls");
        aux = maior->proximo;
    }
}*/