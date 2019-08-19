#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>




typedef struct{
	int score;
	char *original_word;
	char *word_form;
	char *distinct_word;
}dict_t;


typedef dict_t* data_t;

typedef struct node node_t;

struct node {
    data_t data;
    node_t *next;
};

typedef struct {
    node_t *head;
    node_t *foot;
} list_t;


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




int 
main(int argc, char *argv[]) {
    list_t *array;
    list_t *lst;
    int word_count = 1;
    int count = 0;
    array = make_empty_list();
    lst = make_empty_list();
    stage_one(array,lst);
    stage_two(array,&word_count);
    stage_three(lst, &count);
    stage_four(array, lst, word_count, count);
    list_free(array, lst);
    return 0;
}



dict_t
*make_empty_dict(void) {
    dict_t *dict;
    dict = (dict_t*)malloc(sizeof(*dict));
    assert(dict != NULL);
    dict->score = 0;
    dict -> original_word = (char *)malloc(sizeof(char*)*20);
    dict -> word_form = (char *)malloc(sizeof(char*)*100);
    dict -> distinct_word = (char *)malloc(sizeof(char*)*20);
    return dict;
}




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







void
read_input(list_t* array, list_t* lst){
	dict_t* dict;
	dict = make_empty_dict();
	while(scanf("%s%d%s",dict->original_word, &dict->score, dict->word_form)==3){
		word_remove(dict->original_word);
		word_remove(dict->word_form);
		array = insert_at_foot(array,dict);
		//printf("%s",dict -> original_word);
	
	}
	while(scanf("%s", dict -> distinct_word) == 1){
		lst = insert_at_foot(lst,dict);
	}
}




void
word_remove(char* word){
	int i=0;
	int j=0;
	while(word[i]){
		if(isalpha(word[i]) || (word[i] == '*')){
			word[j] = word[i];
			j++;
		}
		i++;
	}
	word[j]='\0';
}




void
print_result(list_t* lst,int count){
	int i;
	int final_score = 0;
	node_t * node = (node_t*)malloc(sizeof(node));
	node = lst -> head;
	for (i = 0; i < count; i++){
		final_score += node -> data -> score;
		printf("%-25s%d\n", node -> data -> distinct_word,node -> data -> score);
		node = node -> next;
	}
	printf("Overall score:           %d\n\n",final_score);
}
	


void
list_free(list_t* array,list_t* lst){
	node_t * node_a; 
	node_t * node_af; 
	node_t * node_l; 
	node_t * node_lf;
	assert(lst != NULL);
	assert(array != NULL);
	node_a = array -> head;
	node_l = lst -> head;
	while(node_a != NULL){
		node_af = node_a -> next;
		free(node_a);
		node_a = node_af;
	}
	while(node_l != NULL){
		node_lf = node_l -> next;
		free(node_l);
		node_l = node_lf;
	}
}
	
	
	
		



void
stage_one(list_t* array,list_t* lst){
	node_t * node;
	read_input(array,lst);
	node = array -> head;
	printf("=========================Stage 1=========================\n");
	printf("First word: %s\n",node -> data -> original_word);
	printf("Sentiment score: %d\n",node -> data -> score);
	printf("Forms: %s\n\n",node -> data -> word_form);
}



void 
stage_two(list_t* array, int *word_count){
	int num_score = array -> head -> data -> score;
	int str_len = strlen(array -> head -> data -> original_word);
	double average_num;
	double average_score;
	node_t * node = (node_t*)malloc(sizeof(node));
	node = array -> head;
	while ( node -> next != NULL){
		node = node -> next;
		str_len += strlen(node -> data -> original_word);
		num_score += node -> data -> score;
		*word_count += 1;
	}
	average_num = (1.0) * str_len / (*word_count);
	average_score = (1.0) * num_score / (*word_count);
	printf("=========================Stage 2=========================\n");
	printf("Number of words: %d\n", *word_count);
	printf("Average number of characters: %.2f\n", average_num);
	printf("Average sentiment score: %.2f\n\n", average_score);
}

		
	 	 
void
stage_three(list_t* lst, int *count){
	node_t * node; 
	node = lst -> head;
	printf("=========================Stage 3=========================\n");
	while ( node != NULL){
		printf("%s\n", node -> data -> distinct_word);
		node = node -> next;
		*count += 1;
	} 
	printf("\n");
}


void 
stage_four(list_t* array, list_t* lst, int word_count, int count){
	int i, j;
	node_t * node_a; 
	node_t * node_l; 
	node_a = array -> head;
	node_l = lst -> head;
	printf("=========================Stage 4=========================\n");
	for (i = 0; i < count; i++){
		node_a = array -> head;
		node_l -> data -> score = 0;
		for (j = 0; j< word_count; j++){
			if(strcmp(node_a -> data -> original_word, node_l -> data -> distinct_word) == 0){
				node_l -> data -> score = node_a -> data -> score;
				break;
			}
			node_a = node_a -> next;
		}
		node_l = node_l -> next;
	}
	print_result(lst,count);
}
	
	
	
	
	
	
	
	


