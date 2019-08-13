#include "header.h"

List citire(int *n)
{
    FILE *fisier;
    fisier = fopen("tree.in", "rt");
    FILE *fisier1;
    fisier1 = fopen("users.in", "rt");

    List list = NULL; //voi crea o lista care contine toate datele necesare, fiecare elem din lista va
                    //va deveni mai tarziu un nod in graful meu
    int i, id, parinte, nrAdreseRezolvabile, j,nrUtilizatori, nrUtilizatoriNod, **utilizatori, *utilizatoriAux;
    char *adresa, **adrRezolv;
    adresa = malloc(10 * sizeof(char));//vector auxiliar folosit pentru stocarea adresei la citire
    utilizatori = malloc(2 * sizeof(int *)); //folosesc o matrice cu 2 linii
    
    fscanf(fisier1, "%d", &nrUtilizatori);
    utilizatori[0] = malloc(nrUtilizatori * sizeof(int));//vector folosit pentru utilizatori propriu-zisi
    utilizatori[1] = malloc(nrUtilizatori * sizeof(int));//vector folosit pentru serverul caruia sunt asociati
    
    for(j = 0; j < nrUtilizatori; j++)
    {
        fscanf(fisier1, "%d %d", &utilizatori[0][j], &utilizatori[1][j]); // citirea continutului users.in
    }

    fscanf(fisier, "%d", n);
    for(i = 0; i < *n; i++)
    {
        //citesc toatele datele
        fscanf(fisier, "%d %d %d", &id, &parinte, &nrAdreseRezolvabile);
        adrRezolv = malloc(nrAdreseRezolvabile * (sizeof(char *)));

        for(j = 0; j < nrAdreseRezolvabile; j++)
        {
            fscanf(fisier, "%s", adresa);
            adrRezolv[j] = strdup(adresa);
        }
        
        nrUtilizatoriNod = 0;
        for(j = 0; j < nrUtilizatori; j++)
        {
            if(utilizatori[1][j] == id)
                nrUtilizatoriNod++;
        }
        utilizatoriAux = malloc(nrUtilizatoriNod * sizeof(int));
        int cont = 0;
        for(j = 0; j < nrUtilizatori; j++)
        {
            if(utilizatori[1][j] == id)
                utilizatoriAux[cont++] = utilizatori[0][j];//adaug utilizatorii nodului curent si ii adaug unui
                                                            //vector auxiliar
        }
        //adaug toate datele in lista mea
        list = addLast(list, id, parinte, nrAdreseRezolvabile, adrRezolv, nrUtilizatoriNod, utilizatoriAux);


    }

    fclose(fisier);
    fclose(fisier1);
    free(adresa);
    free(utilizatori[0]);
    free(utilizatori[1]);
    free(utilizatori);

    return list;    
}

Trie genGraph_si_afisare(List list, int n, Queue *queFrunze)
{
    //am facut afisarea in tandem cu initializarea grafului
    FILE *fisier1;
    fisier1 = fopen("tree.out", "w");

    //in queFrunze, vor fi stocate toate frunzele la sfarsitul initializarii grafului
    *queFrunze = dequeue(*queFrunze);//necesar intrucat prima valoare este gunoi de la initializare

    int cont = 1; //contor pentru numarul de noduri adaugate in graf
    List auxList = list;
    Trie DNS_graph = NULL;
    Queue que = NULL;

    //initializare graf cu nodul 0
    while(auxList != NULL)
    {
        if(auxList->parinte == -1)
        {
            DNS_graph = initTrie(list->id, list->nrAdr, list->adrRezolv, list->nrUtilizatori, list->utilizatori);
            que = initQueue(0, DNS_graph);
        }
        auxList = auxList->next;

    }

    Trie auxDNS_graph = DNS_graph;
    
    //creez graful si afisez
    while(cont < n)
    {
        List temp = list;
        int ok = 0;
        auxDNS_graph = que->head->nod;
        fprintf(fisier1,"%d", que->head->nod->id);
        
        while(temp != NULL)
        {
            //sunt 2 ramuri datorita modului de implementare a grafului (Trie)
            //fiecare nod are un copil, restul de copii find frati ai copilului
            //primul if este pentru adaugare copil, al doilea pentru frati
            if(temp->parinte == que->head->data && ok == 0)
            {
                que->head->nod = insertChild(que->head->nod, temp->id, temp->nrAdr, temp->adrRezolv, temp->nrUtilizatori, temp->utilizatori);
                auxDNS_graph = auxDNS_graph->child;
                fprintf(fisier1," %d", auxDNS_graph->id);
                que = enqueue(que, temp->id, auxDNS_graph);
                cont++;
                ok = 1;
                temp = temp->next;
            }
            if(temp != NULL && temp->parinte == que->head->data && ok == 1)
            {
                que->head->nod = insertChild(que->head->nod, temp->id, temp->nrAdr, temp->adrRezolv, temp->nrUtilizatori, temp->utilizatori);
                auxDNS_graph = auxDNS_graph->sibling;   
                fprintf(fisier1, " %d", auxDNS_graph->id);
                que = enqueue(que, temp->id, auxDNS_graph);
                cont++;
            }
            if(temp != NULL)
                temp = temp->next;
        }   
        fprintf(fisier1, "\n");
        if(!ok)
            *queFrunze = enqueue(*queFrunze, first(que), NULL);
        que = dequeue(que);
    }

    while(!(isEmptyQueue(que)))//afisez si ultimele elem ramase in coada(frunze)
    {
        fprintf(fisier1, "%d\n", que->head->nod->id);
        *queFrunze = enqueue(*queFrunze, first(que), NULL);
        que = dequeue(que);
    }
    
    fclose(fisier1);
    return DNS_graph;
}

void initializareIerarhie(Trie DNS_graph, Queue *queFrunze, List list)
{
    /*
     Ajutat de coada de frunza creata mai devreme adaug adresele copilului care lipsesc din parinte, 
     si adaug parintele in coada
     Stiu ca adaug mai multi parinti deci fac verificari inutile si ca poate fi optimizat usor
     dar mi-am dozat timpul prost si mai sunt 30 de minute pana la deadline deci nu mai am timp
    */
    while(!(isEmptyQueue(*queFrunze)))
    {
        Trie copchil = findNode(DNS_graph, first(*queFrunze)); // gasesc nodul primului elem din coada
        Trie figuraPaterna = copchil->father; //parintele nodului
        int i, j, ok;

        for(i = 0; i < copchil->nrAdr; i++)
        {
            ok = 0;
            //verific daca exista adresa in parinte
            for(j = 0; j < figuraPaterna->nrAdr; j++)
                if(strcmp(copchil->adrRezolv[i],figuraPaterna->adrRezolv[j]) == 0)
                    ok = 1;
            
            //adaug adresa 
           if(ok != 1)
            {
                figuraPaterna->adrRezolv = realloc(figuraPaterna->adrRezolv, (figuraPaterna->nrAdr+1)*sizeof(char *));
                figuraPaterna->adrRezolv[figuraPaterna->nrAdr] = strdup(copchil->adrRezolv[i]);
                figuraPaterna->nrAdr++;
            }

            
        }
        //adaug parintele in coada
        if(copchil->id != 0)
            *queFrunze = enqueue(*queFrunze, figuraPaterna->id, NULL);
        *queFrunze = dequeue(*queFrunze);

        while(first(*queFrunze) == 0)
            dequeue(*queFrunze);

    }

    //afisarea nodurilor cu toate adresele adaugate 
    //ajutat de o coada pentru a parcurge toate nodurile
    Queue que = NULL;
    List auxList = list;
    while(auxList != NULL)
    {
        if(auxList->parinte == -1)
        {
            que = initQueue(0, NULL);
        }
        auxList = auxList->next;
    }
    FILE *fisier1;
    fisier1 = fopen("hierarchy.out", "w");
    while(!(isEmptyQueue(que)))
    {
        Trie nod = findNode(DNS_graph, first(que));
        int i;
        fprintf(fisier1, "%d", nod->id);
        for(i = 0; i < nod->nrAdr; i++)
            fprintf(fisier1, " %s", nod->adrRezolv[i]); 
        List auxList = list;
        while(auxList != NULL)
        {
            if(auxList->parinte == nod->id)
            {
                que = enqueue(que, auxList->id, NULL);
            }
            auxList = auxList->next;
        }
        if(que->size != 1)
            fprintf(fisier1, "\n");
        que = dequeue(que);

    }
    fclose(fisier1);
}

void cereriUtilizatori(Trie DNS_graph)
{

    FILE *fisier;
    fisier = fopen("queries.in", "rt");

    FILE *output;
    output = fopen("queries.out", "wt");

    int nrQueries, i;
    fscanf(fisier, "%d", &nrQueries);

    int user_id;
    char comanda, garbage;
    char *adresa;

    adresa = malloc(10 * sizeof(char));
    fscanf(fisier, "%c", &garbage); //necesar pentru citire corecta
    
    Trie nodUtilizator = NULL;
    Trie nodPicat = NULL;
    int primulNod = 0;
    for(i = 0; i < nrQueries; i++)
    {
        fscanf(fisier, "%c", &comanda);
        //citesc datele in functie de comanda
        if(comanda == 'q'){ 
            fscanf(fisier, "%d", &user_id);
            fscanf(fisier, "%s", adresa);
            fscanf(fisier, "%c", &garbage); 
        }
        if(comanda == 'f')
        {
            fscanf(fisier, "%d", &user_id);
            fscanf(fisier, "%c", &garbage); 
        }
        
        
        if(comanda == 'q')
        {
            nodUtilizator = findNodeOfUser(DNS_graph, user_id); //gasesc nodul utilizatorului
            fprintf(output, "%d", nodUtilizator->id);
            primulNod = 0; //necesar pentru afisare(se tine cont de spatii)
            int ok = 0;
            while(ok == 0)
            {
                int j;
                for(j = 0; j < nodUtilizator->nrAdr; j++)
                    if(strcmp(adresa, nodUtilizator->adrRezolv[j]) == 0) //verific daca exista adresa in nodul curent
                        ok = 1;

                if(primulNod != 0)
                    fprintf(output, " %d", nodUtilizator->id); //afisez nodul in care sunt
                
                if(ok == 0)
                {
                    nodUtilizator->adrRezolv = realloc(nodUtilizator->adrRezolv, (nodUtilizator->nrAdr+1)*sizeof(char *));//daca nu exista fac cache
                    nodUtilizator->adrRezolv[nodUtilizator->nrAdr] = strdup(adresa);
                    nodUtilizator->nrAdr++;
                    nodUtilizator = nodUtilizator->father; //urc in parinte
                }

                primulNod = 1;
            }
            fprintf(output, "\n");    
        }

        if(comanda == 'f')
        {
            //daca cade un nod, doar mut utilizatorii in parinte si schimb legaturile grafului

            nodPicat = findNode(DNS_graph, user_id);

            if(nodPicat != NULL) //in cazul in care acelas nod "cade" de 2 ori
            {
                Trie parinte = nodPicat->father;
                int cont = parinte->nrUtilizatori, i;

                //copiez adresele
                parinte->nrUtilizatori += nodPicat->nrUtilizatori;
                parinte->utilizatori = realloc(parinte->utilizatori, parinte->nrUtilizatori * sizeof(int));

                for(i = cont; i < parinte->nrUtilizatori; i++)
                    parinte->utilizatori[i] = nodPicat->utilizatori[i - cont];

                //modific legaturile
                Trie auxNod = nodPicat;
                Trie auxCopil = nodPicat->child;
                while(auxNod->sibling != NULL)
                    auxNod = auxNod->sibling;

                auxNod->sibling = nodPicat->child;

                while(auxCopil != NULL)
                {
                    auxCopil->father = nodPicat->father;
                    auxCopil = auxCopil->sibling;
                }
            }
        }

    }

    

    fclose(fisier);
    fclose(output); 
}

int main()
{
    int n;
    List list = citire(&n);
    Queue queFrunze = initQueue(-1, NULL);
    Trie DNS_graph = genGraph_si_afisare(list, n, &queFrunze); //task 1
    initializareIerarhie(DNS_graph, &queFrunze, list); //task 2
    cereriUtilizatori(DNS_graph);//task3 + bonus
    

    return 0;
}