#include "header.h"

Trie initTrie(int id, int nrAdr, char **adrRezolv, int nrUtilizatori, int *utilizatori) {
	Trie trie = malloc(sizeof(struct trie));
	trie->id = id;
	trie->nrAdr = nrAdr;
	trie->adrRezolv = adrRezolv;
	trie->nrUtilizatori = nrUtilizatori;
	trie->utilizatori = utilizatori;
	trie->child = NULL;
	trie->sibling = NULL;
	trie->father = NULL;

	return trie;
}

int noOfKids(Trie trie) {
	Trie tmp;
	tmp = trie->child;
	int nr = 0;
	while(tmp != NULL)
	{
		tmp = tmp->sibling;
		nr++;
	}
	return nr;
}

Trie insertChild(Trie trie, int id, int nrAdr, char **adrRezolv, int nrUtilizatori, int *utilizatori) {
	Trie new_child = initTrie(id, nrAdr, adrRezolv, nrUtilizatori, utilizatori);

	if(trie == NULL)
	{
		trie = new_child;
		return trie;
	}
	else if(trie->child == NULL){
		trie->child = new_child;
		new_child->father = trie;
		return trie;
	}
	else
	{
		Trie tmp = trie->child;
		while(tmp->sibling != NULL)
			tmp = tmp->sibling;
		tmp->sibling = new_child;
		new_child->father = trie;
		return trie;
	}

}
Trie findNode(Trie trie, int id)
{
	if(trie == NULL)
		return NULL;
	if(trie->id == id)
		return trie;
	else
	{
		Trie auxCopil = trie->child, auxFrate = trie->child, temp;
		auxCopil = findNode(auxCopil, id);
		if(auxCopil != NULL)
			return auxCopil;
		while(auxFrate != NULL){
			temp = findNode(auxFrate->sibling, id);
			if(temp != NULL)
				return temp;
			auxFrate = auxFrate->sibling;
		}
	}

	return NULL;

}
int checkUser(Trie trie, int utilizator)
{
	int i;
	for(i = 0; i < trie->nrUtilizatori; i++){
		if(trie->utilizatori[i] == utilizator)
			return 1;
	}
	return 0;
}

Trie findNodeOfUser(Trie trie, int utilizator)
{
	if(trie == NULL)
		return NULL;
	if(checkUser(trie, utilizator))
		return trie;
	else
	{
		Trie auxCopil = trie->child, auxFrate = trie->child, temp;
		auxCopil = findNodeOfUser(auxCopil, utilizator);
		if(auxCopil != NULL)
			return auxCopil;
		while(auxFrate != NULL){
			temp = findNodeOfUser(auxFrate->sibling, utilizator);
			if(temp != NULL)
				return temp;
			auxFrate = auxFrate->sibling;
		}	
	}
	

	
	

	return NULL;

}

//functii folosite pentru vizualizarea grafului
/*void drawTrieHelper(Trie trie, FILE* stream) {
	Trie tmp;
	if (trie == NULL) {
		return;
	}
	fprintf(stream, "    %ld[label=\"%d\", fillcolor=red]\n", (intptr_t) trie, trie->id);
	
	tmp = trie->child;

	while (tmp != NULL) {
		fprintf(stream, "    %ld -> %ld \n", (intptr_t) trie, (intptr_t) tmp);
		drawTrieHelper(tmp, stream);
		tmp = tmp->sibling;
	}
}

void drawTrie(Trie trie, char *fileName) {
	FILE* stream = fopen("test.dot", "w");
	char buffer[SIZE];
	fprintf(stream, "digraph TRIE {\n");
	fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=yellow];\n");
	if (!trie)
		fprintf(stream, "\n");
	else if (!trie->child)
		fprintf(stream, "    %ld [label=\"%d\"];\n", (intptr_t) trie, trie->id);
	else
		drawTrieHelper(trie, stream);
	fprintf(stream, "}\n");
	fclose(stream);
	sprintf(buffer, "dot test.dot | neato -n -Tpng -o %s", fileName);
	system(buffer);
}



*/