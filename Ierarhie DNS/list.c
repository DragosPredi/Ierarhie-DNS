#include "header.h"

List initList(int id, int parinte, int nrAdr, char **adrRezolv, int nrUtilizatori, int *utilizatori)
{
	List list;
	list = (List) malloc(sizeof(struct list));
	list->id = id;
	list->parinte = parinte;
	list->nrAdr = nrAdr;
	list->adrRezolv = adrRezolv;
	list->nrUtilizatori = nrUtilizatori;
	list->utilizatori = utilizatori;
	list->next = NULL;
	list->prev = NULL;
	return list;
}

List addLast(List list, int id, int parinte, int nrAdr, char **adrRezolv, int nrUtilizatori, int *utilizatori)
{
	List new, tmp;

	if (list == NULL)
		return initList(id, parinte, nrAdr, adrRezolv, nrUtilizatori, utilizatori);
	new = initList(id, parinte, nrAdr, adrRezolv, nrUtilizatori, utilizatori);
	tmp = list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	return list;
}

List deleteItem(List l, int id) {
	if(l == NULL) {
		return NULL;
	} else {
		List tmp = l, prev;
		if(tmp->id == id) {
			l = l->next;
			free(tmp);
			l->prev = NULL;
			return l;
		} else {
			prev = tmp;
			tmp = tmp->next;
		}
		while(tmp != NULL) {
			if(tmp->id == id) {
				prev->next = tmp->next;
				if (tmp->next != NULL)
					tmp->next->prev = prev;
				free(tmp);
				return l;
			}
			prev = tmp;
			tmp = tmp->next;
		}
		return l;
	}
}

List freeList(List list)
{
	List tmp;

	if (list == NULL)
		return list;
	while (list != NULL) {
		tmp = list;
		list = list->next;
		free(tmp);
	}
	return NULL;
}


void printList(List list)
{
	while(list != NULL)
	{
		printf("%d %d %d ", list->id, list->parinte, list->nrAdr);
		int i;
		for(i = 0; i < list->nrAdr; i++)
			printf("%s ", list->adrRezolv[i]);
		printf("\n");
		list = list->next;
	}
}