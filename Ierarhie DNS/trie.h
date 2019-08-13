#define SIZE 200

typedef struct trie {
	int id;
	int nrAdr;
	char **adrRezolv;
	int nrUtilizatori;
	int *utilizatori;
	struct trie *child;
	struct trie *sibling;
	struct trie *father;
} *Trie;

Trie initTrie(int id, int nrAdr, char **adrRezolv, int nrUtilizatori, int *utilizatori);
int noOfKids(Trie trie);
Trie insertChild(Trie trie, int id, int nrAdr, char **adrRezolv, int nrUtilizatori, int *utilizatori);
/*void drawTrie(Trie trie, char *fileName);
void drawTrieHelper(Trie trie, FILE* stream);*/
Trie findNodeOfUser(Trie trie, int utilizator);
Trie findNode(Trie trie, int id);
int checkUser(Trie trie, int utilizator);