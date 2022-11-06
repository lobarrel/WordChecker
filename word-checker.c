#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED   'R'
#define BLACK 'B'
#define MAX_LEN 17
#define ZEROCHAR '-'
#define NUM_SYMBOLS 78


typedef struct RBNode{
    char color;
    struct RBNode * parent; //parent
    struct RBNode * right; //right child
    struct RBNode * left; //left child
    char word[];
} RBNode;


struct RBNode  T_Nil_Node;
RBNode* T_Nil = &T_Nil_Node;

typedef struct List{
    char * word;
    struct List * next;
} List;



//FUNZIONI LISTA

List* push(List* head, char* w, int len){
    List* tmp;

    tmp = (List*) malloc(sizeof(List));
    tmp->word = (char*) malloc(len+1);
    strcpy(tmp->word, w);

    tmp -> next = head;
    head = tmp;

    return head;
}

List* insertInList(List* head, char* w, int len){
    List* n;
    List* p;

    if((n = (List*) malloc(sizeof(List)))){
        if((n->word = (char*) malloc(len+1))) {
            strcpy(n->word, w);

            if (head == NULL || strcmp(head->word, n->word) >= 0) {
                n->next = head;
                head = n;
            } else {
                p = head;
                while (p->next != NULL && strcmp(p->next->word, n->word) < 0) {
                    p = p->next;
                }
                n->next = p->next;
                p->next = n;
            }
        }else printf("errore allocazione");
    }else printf("errore allocazione");

    return head;
}

List* emptyList(List* head){
    List* del;
    while(head != NULL){
        del = head;
        head = head->next;
        free(del->word);
        free(del);
    }
    return head;
}




//FUNZIONI RED-BLACK TREE

RBNode* newRBNode(char * w, int len)
{

    RBNode *temp = (RBNode*) malloc(sizeof(RBNode)+len+1);
    //temp->word = (char*) malloc(len+1);
    strcpy(temp->word, w);
    temp->color  = RED;
    temp->left   = NULL;
    temp->right  = NULL;
    temp->parent = NULL;

    return temp;
}

RBNode* RBMaximum(RBNode* x){
    while(x->right != T_Nil){
        x = x->right;
    }
    return x;
}
RBNode* RBPredecessor(RBNode* x){
    RBNode* y;
    if(x->left != T_Nil){
        return RBMaximum(x->left);
    }
    y = x->parent;
    while(y != T_Nil && x == y->left){
        x = y;
        y = y->parent;
    }
    return y;
}
RBNode* RBMinimum(RBNode* x){
    while(x->left != T_Nil){
        x = x->left;
    }
    return x;
}
RBNode* RBSuccessor(RBNode* x){
    RBNode* y;
    if(x->right != T_Nil){
        return RBMinimum(x->right);
    }
    y = x->parent;
    while(y != T_Nil && x == y->right){
        x = y;
        y = y->parent;
    }
    return y;
}

void rotateLeft(RBNode** T, RBNode* x)
{
    RBNode *y  = x->right;
    x->right = y->left;
    if (y->left != T_Nil)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == T_Nil)
        *T = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left   = x;
    x->parent = y;
}
void rotateRight(RBNode** T, RBNode* y)
{
    RBNode *x  = y->left;
    y->left  = x->right;
    if (x->right != T_Nil)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == T_Nil)
        *T = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left  = x;
    x->right  = y;
    y->parent = x;
}

void RBInsertFixup(RBNode** T, RBNode* z)
{
    RBNode* y;
    while(z->parent->color == RED)
    {
        if(z->parent == z->parent->parent->left)
        {
            y = z->parent->parent->right;
            if(y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else if(z == z->parent->right)
            {
                z = z->parent;
                rotateLeft(T,z);

            }else {
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateRight(T, z->parent->parent);
            }
        }
        else
        {
            y = z->parent->parent->left;
            if(y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else if(z == z->parent->left)
            {
                z = z->parent;
                rotateRight(T,z);

            }else {
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateLeft(T, z->parent->parent);
            }
        }
    }
    (*T)->color = BLACK;
}
void RBInsert(RBNode** T, char * w, int len)
{
    RBNode* z = newRBNode(w, len);
    RBNode* y =  T_Nil;
    RBNode* x = *T;

    // Find where to Insert new node Z into the binary search tree
    while (x != T_Nil) {
        y = x;
        if (strcmp(z->word, x->word)<0)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == T_Nil)
        *T = z;
    else if (strcmp(z->word, y->word)<0)
        y->left  = z;
    else
        y->right = z;

    // Init z as a red leaf
    z->left  = T_Nil;
    z->right = T_Nil;
    z->color = RED;

    // Ensure the Red-Black property is maintained
    RBInsertFixup(T, z);
}

int searchWord(RBNode* x, char * w){
    int trovata = 0;
    int r;
    while(x != T_Nil && trovata == 0){
        r = strcmp(w, x->word);
        if(r == 0)
            trovata = 1;
        else if(r<0)
            x = x->left;
        else
            x = x->right;
    }

    return trovata;
}



//FUNZIONI WORD-CHECKER

void confrontaParole(const char* r, char* p, char * output, int** v, int len, int* min, int* ex){
    int i, j, h;
    int curr_count, tmp_count;
    char currChar;
    int tmp[NUM_SYMBOLS];

    for(i = 0; i < NUM_SYMBOLS; i++)
        tmp[i] = 0;

    for(i = 0; r[i] != '\0'; i++){
        if(r[i] == p[i]){
            tmp[p[i]-ZEROCHAR]++;
            output[i] = '+';
            for(h = 0; h < NUM_SYMBOLS; h++)
                if(h != p[i]-ZEROCHAR)
                    v[h][i] = 0;
        }else {
            output[i] = 'x';
        }
    }

    for(i = 0; r[i] != '\0'; i++){
        if(output[i] == 'x'){
            currChar = p[i];
            curr_count = 0;
            for(j = 0; r[j] != '\0'; j++){
                if(r[j] == currChar && (output[j] != '+')) {
                    curr_count++;
                }
            }
            //tmp[idx(currChar)] += curr_count;
            tmp_count = curr_count;

            for(j = 0; r[j] != '\0'; j++){
                if(p[j] == currChar && (output[j] == 'x')){
                    if(tmp_count > 0){
                        tmp_count--;
                        output[j] = '|';
                        tmp[p[i]-ZEROCHAR]++;
                        v[currChar-ZEROCHAR][j] = 0;
                    }else{
                        output[j] = '/';
                        if(curr_count == 0 && tmp[currChar-ZEROCHAR] == 0) {
                            ex[currChar-ZEROCHAR] = 0;
                            for (h = 0; h < len; h++)
                                v[currChar-ZEROCHAR][h] = 0;
                        }
                        else {
                            v[currChar-ZEROCHAR][j] = 0;
                            ex[currChar-ZEROCHAR] = tmp[currChar-ZEROCHAR];
                        }
                    }
                }
            }
        }
    }

    for(i = 0; i < NUM_SYMBOLS; i++)
        if(tmp[i] > min[i])
            min[i] = tmp[i];
}

void stampaFiltrate(List* head){
    List* tmp;
    for(tmp = head; tmp != NULL; tmp = tmp->next){
        fprintf(stdout, "%s\n", tmp->word);
    }
}
void stampaAmmissibili(RBNode* x){

    RBNode* curr = RBMinimum(x);
    while(curr != T_Nil){
        fprintf(stdout, "%s\n", curr->word);
        curr = RBSuccessor(curr);
    }
}

int isCompatibile(char* w, int** v, const int* min, const int* ex){
    int tmp[NUM_SYMBOLS];
    int i, compatibile;

    for(i = 0; i < NUM_SYMBOLS; i++)
        tmp[i] = 0;
    compatibile = 1;

    for(i = 0; w[i] != '\0'; i++){
        if(v[w[i]-ZEROCHAR][i] == 0)
            compatibile = 0;
        tmp[w[i]-ZEROCHAR]++;
    }
    for(i = 0; i < NUM_SYMBOLS && compatibile; i++){
        if((min[i] > 0 && tmp[i] < min[i]) || (ex[i] > -1 && tmp[i] > ex[i]))
            compatibile = 0;
    }
    return compatibile;
}

List* filtra1(RBNode* root, List* head, int** v, int* min, int* ex, int * count, int len) {

    RBNode* curr = RBMaximum(root);
    while (curr != T_Nil) {
        if (isCompatibile(curr->word, v, min, ex)) {
            head = push(head, curr->word, len);
            (*count)++;
        }
        curr = RBPredecessor(curr);
    }
    return head;
}
List* filtra2(List* head, int** v, int* min, int* ex, int * count){

    List* tmp;
    List* del;
    while(head != NULL && isCompatibile(head->word, v, min, ex) == 0){
        del = head;
        head = head->next;
        free(del->word);
        free(del);
        (*count)--;
    }
    tmp = head;
    while(tmp != NULL && tmp->next != NULL){
        while(tmp->next != NULL && isCompatibile(tmp->next->word, v, min, ex) == 0){
            del = tmp->next;
            tmp->next = del->next;
            free(del->word);
            free(del);
            (*count)--;
        }
        tmp = tmp->next;
    }
    return head;
}




int main() {

    int k;
    int num_tentativi, i, j, first_time, count_filtrate;
    char word[MAX_LEN];
    RBNode * ammissibili = T_Nil;
    List * filtrate = NULL;
    int ** vincoli;
    int min_count[NUM_SYMBOLS], ex_count[NUM_SYMBOLS];
    char * parola_rif, * res;
    int fine_partita;
    int unused __attribute__((unused));




    unused = fscanf(stdin, "%d\n", &k);

    //ALLOCAZIONI
    parola_rif = (char*)malloc(sizeof(char) * (k));
    res = (char*)malloc(sizeof(char) * (k));
    vincoli = (int**)malloc(sizeof(int*)*NUM_SYMBOLS);
    for(i = 0; i<NUM_SYMBOLS; i++)
        vincoli[i] = (int*)malloc(sizeof(int) * k);



    while(fscanf(stdin, "%s", word) != EOF){

        //INSERIMENTO DIZIONARIO
        if(word[0] != '+'){
            RBInsert(&ammissibili, word, k);
        }


            //NUOVA PARTITA
        else if(word[1] == 'n'){

            for(i = 0; i < NUM_SYMBOLS; i++){
                min_count[i] = 0;
                ex_count[i] = -1;
                for(j = 0; j < k; j++)
                    vincoli[i][j] = 1;
            }
            i = 0;
            fine_partita = 0;
            first_time = 1;



            unused = fscanf(stdin, "%s", parola_rif);
            unused = fscanf(stdin, "%d\n", &num_tentativi);
            while(fine_partita == 0){
                unused = fscanf(stdin, "%s", word);
                if(word[0] != '+'){

                    if (strcmp(word, parola_rif) == 0) {
                        fprintf(stdout, "ok\n");
                        fine_partita = 1;
                    }else if (searchWord(ammissibili, word)) {
                        confrontaParole(parola_rif, word, res, vincoli, k, min_count, ex_count);

                        if(first_time){
                            count_filtrate = 0;
                            filtrate = filtra1(ammissibili, filtrate, vincoli, min_count, ex_count, &count_filtrate, k);
                            first_time = 0;
                        }else{
                            filtrate = filtra2(filtrate, vincoli, min_count, ex_count, &count_filtrate);
                        }

                        i++;
                        fprintf(stdout, "%s\n%d\n", res, count_filtrate);


                        if (i >= num_tentativi) {
                            fprintf(stdout, "ko\n");
                            fine_partita = 1;
                        }

                    }else {
                        fprintf(stdout, "not_exists\n");
                    }
                }

                else if(word[1] == 'i'){
                    unused = fscanf(stdin, "%s", word);
                    while (word[0] != '+') {
                        RBInsert(&ammissibili, word, k);
                        if(first_time == 0){
                            if (isCompatibile(word, vincoli, min_count, ex_count)) {
                                filtrate = insertInList(filtrate, word, k);
                                count_filtrate++;
                            }
                        }
                        unused = fscanf(stdin, "%s", word);
                    }
                }

                else if (word[1] == 's') {
                    if(first_time){
                        stampaAmmissibili(ammissibili);
                    }else{
                        stampaFiltrate(filtrate);
                    }
                }
            }
            filtrate = emptyList(filtrate);
        }


            //INSERIMENTO NUOVE PAROLE
        else if(word[1] == 'i'){
            unused = fscanf(stdin, "%s", word);
            while (word[0] != '+') {
                RBInsert(&ammissibili, word, k);
                unused = fscanf(stdin, "%s", word);
            }
        }
    }

    free(parola_rif);
    free(vincoli);
    free(res);

    return 0;
}
