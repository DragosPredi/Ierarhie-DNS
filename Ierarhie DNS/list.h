
typedef struct list {
	int id;
	int parinte;
	int nrAdr;
	char **adrRezolv;
	int nrUtilizatori;
	int *utilizatori;
	struct list *next;
	struct list *prev;
}*List;

List initList(int id, int parinte, int nrAdr, char **adrRezolv, int nrUtilizatori, int *utilizatori);
List addFirst(List list, int id, int parinte, int nrAdr, char **adrRezolv);
void printList(List list);
void sortList(List list);
List addLast(List list, int id, int parinte, int nrAdr, char **adrRezolv, int nrUtilizatori, int *utilizatori);
List deleteItem(List l, int id);
List freeList(List list);
