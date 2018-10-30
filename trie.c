#include <stdio.h>
#include <stdlib.h>

//build Trie w. NODES (rpsnt. letters of a word)
struct Node{
    int wordflag;                    // = true (1), for final-letters of *word
    struct Node *alpha[26];          //platform to build NODE of next-letter in *word
};
typedef struct Node Node;


//Inits a "Vacuum" NODE ...        that doesn't YET have links to existing-&-future NODES
Node* createNode(){
    Node* node = (Node*)malloc(sizeof(Node));
    node->wordflag=0;
    
    //create null SUB-NODES (a b c ... z) - may be init'd to complete *word
    for(int l=0; l<26; l++)
        node->alpha[l] = NULL;        
    return node;
}


int search_insert_delete(Node *node, char *mode, char *word){    // all 3 funcs traverse through Trie
    
    // Execute Trie-traversal funcs...
    while(*word){
        int index=(*word|('A'^'a'))-'a';
        //Word INSERTION (if it is absent)
        if(!node->alpha[index]){
            if(*mode == 'i'){
                node->alpha[index] = createNode();
            } else{
                printf("word d.n.e");
                return 0;
            }
        }
        // => next NODE...           (traversal)  
        node=node->alpha[index];
        word++;
    }
    
            //  ...       trie has traversed to END-NODE 
            
    //Configure WORDFLAG
    if(!node->wordflag){
        if(*mode == 'i'){
            printf("setting wordflag...");
            node->wordflag=1;       // set positive @ END-NODE of inserted WORD
            return 1;
        }
        // 0-wordflag @ END-NODE = word d.n.e 
        else if(*mode == 's' || *mode == 'd'){    
            printf("word not found: constituent NODE (%c) d.n.e", *word);  
            return 0;
        }
    } else if(*mode == 'd'){
        node->wordflag=0;                 // semantically "delete" *word
        return 1;
    } else {
        printf("word succesfully found");
        return 1;
    }
    return 1;
}

int main(void){
    Node* root = createNode();      //root node, points to 1st NODE
    
    for(int i=0; i<100; i++){
        //take user arg
        printf("\n\nselect MODE: \n i = insert \n s = search \n d = delete\n");
        char *mode = malloc(sizeof(char));
        scanf(" %s", mode);
        
        printf("type a word to execute on:  \n");
        char *word = malloc(sizeof(char)*45);
        scanf("%44s", word);
        
        int result = search_insert_delete(root, mode, word);
        if(result == 1)
            printf("\n%s-action sucessful",mode);
        else
            printf("\n%s-action FAILED",mode);
    }
}