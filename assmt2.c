 /* Edited by Dechao Sun (980546), finishing stages 1 to 4 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

/*****************************************************************************/


#define SIZE_ORIGINAL_WORD 21    /* size of a original_word */
#define SIZE_WORD_FORM 101		/* size of a word_from string */
#define SIZE_DISTINCT_WORD 21	/* size of a distinct_word */


/*****************************************************************************/
/* structs for the assmt2 */
/* creat a struct named dict_t include 3 arrays and 1 integer number */

typedef struct{
	int score;
	char *original_word;
	char *word_form;
	char *distinct_word;
}dict_t;

/* creat a linked list set the data_t as dict_t */
typedef dict_t* data_t;

typedef struct node node_t;
/* set a node with two parts which are data and next */
struct node {
    data_t data;
    node_t *next;
};
/* set up head and foot nodes in linked list */
typedef struct {
    node_t *head;
    node_t *foot;
} list_t;

/*****************************************************************************/

/* function prototypes */
list_t *make_empty_list(void);
dict_t *make_empty_dict(void);
void stage_one(list_t* array,list_t* lst);
void stage_two(list_t* array,int *word_count);
void stage_three(list_t* lst, int *count);
void stage_four(list_t* array, list_t* lst,int word_count, int count);
void read_input(list_t* array,list_t* lst);
list_t *insert_at_foot(list_t *list, data_t value);
list_t *insert_at_head(list_t *list, data_t value);
void word_remove(char* word);
void print_result(list_t* lst,int count);
void list_free(list_t* array,list_t* lst);


/*****************************************************************************/

int 
main(int argc, char *argv[]) {
    list_t *array;
    list_t *lst;
    /* number of original word */
    int word_count = 1;
    /* number of distinct word */
    int count = 0;
    /* create two linked list named array and lst */
    array = make_empty_list();
    lst = make_empty_list();
    /* stage 1: print the first combination that contain three parts */
    /* original_word, score and word_form */
    stage_one(array,lst);
    
    /* stage 2: analyze input and print out total number of words, average 
    score and average number of characters */
    stage_two(array,&word_count);
    
    /* stage 3: reading the sentence, store into lst (linked lsit) word by 
    word and print it out */
    stage_three(lst, &count);
    
    /* stage 4: linking array and lst together, printing out word with 
    related score */
    stage_four(array, lst, word_count, count);
    
    /* free two linked lists and struct dict_t which is data_t in 
    every node */
    list_free(array, lst);
    free(array);
    free(lst);
    return 0;
}


/*****************************************************************************/
/* source code make_empty_list, insert_at_head and insert_at_foot
	from Moffat, A. (2013). Programming, Problem Solving,
	and Abstraction with C. Pearson.
	ISBN 9781486010974. (A revised edition of the 2003 book) */

list_t
*make_empty_list(void) {
    list_t *list;
    list = (list_t*)malloc(sizeof(*list));
    assert(list!=NULL);
    list->head = list->foot = NULL;
    return list;
}



list_t
*insert_at_head(list_t *list, data_t value) {
	node_t *new;
	new = (node_t*)malloc(sizeof(*new));
	assert(list!=NULL && new!=NULL);
	new -> data = value;
	new -> next = list->head;
	list -> head = new;
	if (list -> foot == NULL) {
		/* this is the first insertion into the list */
		list->foot = new;
	}
	return list;
}




list_t
*insert_at_foot(list_t *list, data_t value) {
    node_t *new;
    new = (node_t*)malloc(sizeof(*new));
    assert(list!=NULL && new!=NULL);
    new->data = make_empty_dict();
    strcpy(new-> data -> word_form, value -> word_form);
    strcpy(new-> data -> original_word, value -> original_word);
    strcpy(new-> data -> distinct_word, value -> distinct_word);
    new -> data-> score = value -> score;
    new -> next = NULL;
    if (list -> foot == NULL) {
        /* this is the first insertion into the list */
        list -> head = list -> foot = new;
    } else {
        list -> foot -> next = new;
        list -> foot = new;
    }
    return list;
}


/*****************************************************************************/


/* create a empty dict which is a struct. */
dict_t
*make_empty_dict(void) {
    dict_t *dict;
    /* malloc memory space for dict */
    dict = (dict_t*)malloc(sizeof(*dict));
    assert(dict != NULL);
    /* initialize score to be 0 and */
    dict -> score = 0;
    /* initialize memory space for 3 arrays according to 
    number of characters */ 
    dict -> original_word = (char *)malloc(sizeof(char*)*SIZE_ORIGINAL_WORD);
    dict -> word_form = (char *)malloc(sizeof(char*)*SIZE_WORD_FORM);
    dict -> distinct_word = (char *)malloc(sizeof(char*)*SIZE_DISTINCT_WORD);
    return dict;
}




/* read input and store words into linked list */
void
read_input(list_t* array, list_t* lst){
	dict_t* dict;
	/* create a empty struct */
	dict = make_empty_dict();
	/* read 3 input resperctively */
	while(scanf("%s%d%s",dict->original_word, &dict->score, 
		dict->word_form)==3){
		/* remove all non-alpha and non-star characters for original_word 
		and word_form */
		word_remove(dict->original_word);
		word_remove(dict->word_form);
		/* insert three elements into linked list named array */
		array = insert_at_foot(array,dict);
	
	}
	/* read the sentence */
	while(scanf("%s", dict -> distinct_word) == 1){
		/* insert into another linked list named array */
		lst = insert_at_foot(lst,dict);
	}
	free(dict);
}




/* remove all non-alpha and non-star characters */
void
word_remove(char* word){
	int i=0;
	int j=0;
	while(word[i]){
		if(isalpha(word[i]) || (word[i] == '*')){
			word[j] = word[i];
			/* scan the word and if it's a number or letter then add 
		to the word */
			j++;
		}
		i++;
	}
	word[j]='\0';
	/* end the word */
}




/* print result for stage 4 */
void
print_result(list_t* lst,int count){
	int i;
	int final_score = 0;
	/* initialize final_score equal to 0 */
	node_t * node;
	node = lst -> head;
	for (i = 0; i < count; i++){
		/* loop through every disctinct word */
		final_score += node -> data -> score;
		/* add score together */
		printf("%-25s%d\n", node -> data -> distinct_word,
			node -> data -> score);
		/* print distinct word */
		node = node -> next;
	}
	printf("Overall score:           %d\n\n",final_score);
	/* print final_score */
}
	



/* free memory space for linked list (array and lst) and struct dict_t */
void
list_free(list_t* array,list_t* lst){
	/* set up four pointer for two linked list */
	node_t * node_a; 
	node_t * node_af; 
	node_t * node_l; 
	node_t * node_lf;
	assert(lst != NULL);
	assert(array != NULL);
	node_a = array -> head;
	node_l = lst -> head;
	while(node_a != NULL){
		/* loop through every node in array until reaching NULL */
		node_af = node_a -> next;
		/* let pointer node_af point to next node of node_a */ 
		/* dict_t is data_t in every in linked list */
		/* free strcut (dict_t) for curr node which is node_a */
		free(node_a -> data -> original_word);
		free(node_a -> data -> word_form);
		free(node_a -> data -> distinct_word);
		/* free node_a */
		free(node_a);
		node_a = node_af;
	}
	while(node_l != NULL){
		/* using the same method to free linked list (lst) */
		node_lf = node_l -> next;
		free(node_l -> data -> original_word);
		free(node_l -> data -> word_form);
		free(node_l -> data -> distinct_word);
		free(node_l);
		node_l = node_lf;
	}
}
	
	
/*****************************************************************************/	
		

 /* stage 1: print the first combination that contain three parts */
 /* original_word, score and word_form */
void
stage_one(list_t* array,list_t* lst){
	node_t * node;
	/* read input and inesert into array by read_input function */
	read_input(array,lst);
	node = array -> head;
	/* print result for stage 1 */
	printf("=========================Stage 1=========================\n");
	printf("First word: %s\n",node -> data -> original_word);
	printf("Sentiment score: %d\n",node -> data -> score);
	printf("Forms: %s\n\n",node -> data -> word_form);
}





/* stage 2: analyze input and print out total number of words, average 
    score and average number of characters */
void 
stage_two(list_t* array, int *word_count){
	int num_score = array -> head -> data -> score;
	/* initialize str_len as the length of the first original word */
	int str_len = strlen(array -> head -> data -> original_word);
	double average_num;
	double average_score;
	node_t * node;
	node = array -> head;
	while ( node -> next != NULL){
		/* loop through every node in array until reaching NULL */
		node = node -> next;
		str_len += strlen(node -> data -> original_word);
		/* add up the total length of words */
		num_score += node -> data -> score;
		/* count the number of original_word */
		*word_count += 1;
	}
	/* calculate average number of characters and score */
	/* times (1.0) for getting double as result */
	average_num = (1.0) * str_len / (*word_count);
	average_score = (1.0) * num_score / (*word_count);
	/* print the result for stage 2 */
	printf("=========================Stage 2=========================\n");
	printf("Number of words: %d\n", *word_count);
	printf("Average number of characters: %.2f\n", average_num);
	printf("Average sentiment score: %.2f\n\n", average_score);
}

		




/* stage 3: reading the sentence, store into lst (linked lsit) word by 
    word and print it out */
void
stage_three(list_t* lst, int *count){
	node_t * node; 
	node = lst -> head;
	printf("=========================Stage 3=========================\n");
	while ( node != NULL){
		/* print every distinct word */
		printf("%s\n", node -> data -> distinct_word);
		node = node -> next;
		/* count the number of distinct_word  */
		*count += 1;
	} 
	printf("\n");
}






 /* stage 4: linking array and lst together, printing out word with 
    related score */
void 
stage_four(list_t* array, list_t* lst, int word_count, int count){
	int i, j;
	node_t * node_a; 
	node_t * node_l; 
	node_a = array -> head;
	node_l = lst -> head;
	printf("=========================Stage 4=========================\n");
	/* uisng two for loops to go through every original_word and 
	distinct_word */
	for (i = 0; i < count; i++){
		node_a = array -> head;
		/* set the every score for distinct_word as 0 */
		node_l -> data -> score = 0;
		for (j = 0; j< word_count; j++){
			/* using strcmp the test whether original_word and 
			distinct word are the same */
			if(strcmp(node_a -> data -> original_word, 
				node_l -> data -> distinct_word) == 0){
			/* if two words ara the same, adding original_word score to 
			distinct_word score */
				node_l -> data -> score = node_a -> data -> score;
				break;
			}
			/* move to next node */
			node_a = node_a -> next;
		}
		/* move to next node */
		node_l = node_l -> next;
	}
	/* using print_result funtion to print out the final result */
	print_result(lst,count);
}
	
	
/* "algorithms are fun" */
/* "algorithms are fun" */
/* "algorithms are fun" */