/* Tweet cleanser:
 * Removes non-alphanumeric characters from tweets
 *
 * Skeleton code written by Yi Han and Jianzhong Qi, April 2019
 * Edited by Dechao Sun (980546), finishing stages 1 to 4.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* stage numbers */
#define STAGE_NUM_ONE 1 
#define STAGE_NUM_TWO 2
#define STAGE_NUM_THREE 3
#define STAGE_NUM_FOUR 4
#define STAGE_NUM_FIVE 5
#define STAGE_HEADER "Stage %d\n==========\n"	/* stage header format string */

#define MAX_TWEET_LENGTH 280					/* maximum length of a tweet */
#define MAX_NUM_TWEETS 100						/* maximum number of tweets */
#define FLAG_START_NOT_MEET_STAR 1         /* when flag_start not meet a '*' */
#define FLAG_START_MEET_STAR 0        		   /* when flag_start meet a '*' */
#define FLAG_STAR_MEET_A_STAR 0   			    /* when flag_star meet a '*' */
#define FLAD_STAR_NOT_MEET_A_STAR 1        /* when flag_star not meet a '*' */
#define IS_CONTAINED 0				  /* source tweet is in the target tweet */
#define NOT_CONTAINED 1			  /* source tweet is not in the target tweet */

typedef char tweet_t[MAX_TWEET_LENGTH+1];		/* a tweet */

/****************************************************************/

/* function prototypes */
void read_one_tweet(tweet_t one_tweet, int max_len);
void print_stage_header(int stage_num);
void tweet_tolower(tweet_t one_tweet);
void tweet_remove(tweet_t one_tweet);
void remove_star(tweet_t one_tweet);
int is_contained(tweet_t source_tweet, tweet_t target_tweet);
int str_len(tweet_t one_tweet);

void stage_one(tweet_t one_tweet);
void stage_two(tweet_t tweets[], int *num_tweets);
void stage_three(tweet_t tweets[], int num_tweets);
void stage_four(tweet_t tweets[], int num_tweets);
void stage_five(tweet_t tweets[], int num_tweets);

/* add your own function prototypes here */


/****************************************************************/

/* main function controls all the action, do NOT modify this function */
int
main(int argc, char *argv[]) {
	/* to hold all input tweets */
	tweet_t tweets[MAX_NUM_TWEETS];	
	/* to hold the number of input tweets */
	int num_tweets = 0;					

	/* stage 1: reading the first tweet */
	stage_one(tweets[num_tweets]); 
	num_tweets++;
	
	/* stage 2: removing non-alphanumeric characters */
	stage_two(tweets, &num_tweets);
	
	/* stage 3: removing extra asterisks and finding the longest tweet */ 
	stage_three(tweets, num_tweets);
	
	/* stage 4: finding the non-contained tweets */
	stage_four(tweets, num_tweets);
	
	/* stage 5: sorting the tweets */
	stage_five(tweets, num_tweets);
	
	/* all done; take some rest */
	return 0;
}

/* read a line of input into one_tweet */
void
read_one_tweet(tweet_t one_tweet, int max_len) {
	int i = 0, c;
	
	while (((c = getchar()) != EOF) && (c != '\n') && (c != '\r')) {
		if (i < max_len) {
			one_tweet[i++] = c;
		} else {
			printf("Invalid input line, toooooooo long.\n");
			exit(EXIT_FAILURE);
		}
	}
	one_tweet[i] = '\0';
}

/* print stage header given stage number */
void 
print_stage_header(int stage_num) {
	printf(STAGE_HEADER, stage_num);
}

/****************************************************************/
/* add your code below */

/* scan a tweet and convert all English letters into lowercase */
void 
tweet_tolower(tweet_t one_tweet) {
	/* add code here to convert English letters in one_tweet into lowercase */
	int i;
	for(i=0; i < MAX_TWEET_LENGTH; i++){
		if (one_tweet[i] == '\0'){
			break;
		}
		else{
			/* using ASCII number table adding 32 change capitalise to lower 
			case */
			if (isalpha(one_tweet[i])){
				if (one_tweet[i]>='A' && one_tweet[i]<='Z'){
					one_tweet[i] = one_tweet[i]+32;
				}
			}
		}
	}
					
}


/* scan a tweet and remove all non-alphanumeric characters */
void
tweet_remove(tweet_t one_tweet){
	int i=0;
	int j=0;
	while(one_tweet[i]){
		if(isalpha(one_tweet[i]) || one_tweet[i]=='*'||
			(one_tweet[i]>='0' && one_tweet[i] <='9')){
		/* scan the one_tweet and if it's  a number or letter then add 
		to the one_tweet */
			one_tweet[j] = one_tweet[i];
			j++;
		}
		i++;
	}
	one_tweet[j]='\0';
	/*end one_tweet */
}

	


/* scan a tweet and remove stars */
void
remove_star(tweet_t one_tweet){
	char result_tweet[MAX_TWEET_LENGTH+1];
	int str_len = strlen(one_tweet);
	int start= FLAG_START_NOT_MEET_STAR;
	int star = FLAG_STAR_MEET_A_STAR;
	int i = 0;
	int j = 0;
	/* set up two flags start and star as control condition */
	while(i<str_len){
		/* if first element is not '*' change flag start from 1 to 0 and start  
		add first element to result_tweet.
		If first element is '*',function do nothing. */
		if(start == FLAG_START_NOT_MEET_STAR){
			if(one_tweet[i] != '*'){
				start = FLAG_START_MEET_STAR;
				result_tweet[j] = one_tweet[i];
				j++;
			}
		}
		/* when scaning reach to '*' change flag star from 0 to 1 */
		/* for the tail '*', the funtion scaned a '*' change flag to 1 but 
		it cannot get any letters or numbers. Therefore it will not add to 
		result_string */
		else if(one_tweet[i] == '*' && star == 0){
			star = FLAD_STAR_NOT_MEET_A_STAR;
		}
		/* from pervious if star equal to 1 which means there is a '*' have 
		been scaned, and next element is not '*'. Adding a '*' and the ith 
		element to the result_tweet, which could ignore how many '*' between 
		two letters or numbers and add a '*' directly. */
		else if(star == FLAD_STAR_NOT_MEET_A_STAR && one_tweet[i] != '*'){
			star = FLAG_STAR_MEET_A_STAR;
			result_tweet[j] = '*';
			j++;
			result_tweet[j] = one_tweet[i];
			j++;
		}
		/* adding normal letters and numbers to result_tweet */
		else if(one_tweet[i] != '*'){
			result_tweet[j] = one_tweet[i];
			j++;
		}
		result_tweet[j]='\0';
		/*end result_tweet */
		i++;
	}
	/* change one_tweet to result_tweet */
	strcpy(one_tweet,result_tweet);
}


/* scan two tweets and compare whether they are the same */
int 
is_contained(tweet_t source_tweet, tweet_t target_tweet){
	int i = 0;
	int j = 0;
	/* loop until source and target tweet reach to '\0' */
	while (source_tweet[i] != '\0' && target_tweet[j] != '\0'){
		/* check ith and (i+1)th elements of source tweet and jth and (j+1)th 
		elements oftarget tweet are the same.
		Keep moving to next element */
		if (target_tweet[j] == source_tweet[i] && 
			target_tweet[j+1] == source_tweet[i+1]){
			i++;
			}
			j++;
	}
	/* source_tweet is not in the target tweet return 1 */
	if (source_tweet[i] != '\0'){
		return NOT_CONTAINED;
	}
	/* source_tweet is in the target tweet return 0 */
	else{
		return IS_CONTAINED;
	}
}
			


/* find length of one_tweet (prepare for stage 4) */
int 
str_len(tweet_t one_tweet){
	int len = 0;
	int i;
	for (i = 0; one_tweet[i] != '\0'; i++){
		len++;
	}
	return len;
}



/****************************************************************/	

/* stage 1: reading the first tweet */
void 
stage_one(tweet_t one_tweet) {
	/* print stage header */
	print_stage_header(STAGE_NUM_ONE);
	
	/* add code to call the read_one_tweet function to read the first tweet */ 
	read_one_tweet(one_tweet, MAX_TWEET_LENGTH);
	
	/* add code into the tweet_tolower function 
	 * to convert English letters into lowercase 
	 */
	tweet_tolower(one_tweet);
	
	/* print result */
	printf("%s\n\n", one_tweet);
}

/* stage 2: removing non-alphanumeric characters */
void 
stage_two(tweet_t tweets[], int *num_tweets) {
	/* add code for stage 2 */
	/* print stage header */
	print_stage_header(STAGE_NUM_TWO);
	/*remove non-alphanumeric characters for the first tweet */
	tweet_remove(tweets[0]);
	/* while loop unitl tweets is not empty */
	while(strlen(tweets[*num_tweets-1])!=0 && *num_tweets < MAX_NUM_TWEETS){
		/* read the tweet, change to lower case and remove non_alphanumeric
		characters */
		read_one_tweet(tweets[*num_tweets],MAX_TWEET_LENGTH);
		tweet_tolower(tweets[*num_tweets]);
		tweet_remove(tweets[*num_tweets]);
		/* print the result */
		printf("%s\n",tweets[*num_tweets-1]);
		*num_tweets+=1;
	}		
	printf("\n");
}

/* stage 3: removing extra asterisks and finding the longest tweet */ 
void 
stage_three(tweet_t tweets[], int num_tweets) {
	/* add code for stage 3 */
	int i;
	int max_strlen;
	int max_index = 0;
	/* print stage header */
	print_stage_header(STAGE_NUM_THREE);
	/* remove star for the first tweet */
	remove_star(tweets[0]);
	/* assmue the longest tweet is the first tweet */
	max_strlen = strlen(tweets[0]);
	/* loop the every tweet */
	for(i = 0; i < num_tweets-1; i++){
		/* remove star for the ith tweet */
		remove_star(tweets[i]);
		/* find the max_strlen */
		if (strlen(tweets[i]) > max_strlen){
			max_strlen = strlen(tweets[i]);
			/* find the index for the max_strlen */
			max_index = i;
		}
		/* print the result */
		printf("%s\n",tweets[i]);
	}
	/* print the result */
	printf("Total: %d\n",num_tweets-1);
	printf("Longest: %s\n",tweets[max_index]);
	printf("Length: %d\n",max_strlen);
	printf("\n");
}



/* stage 4: finding the non-contained tweets */
void 
stage_four(tweet_t tweets[], int num_tweets) {
	/* add code for stage 4 */
	int i;
	int j;
	/* set up a flag contained */
	int contained = 1;
	/* initialize number of tweets is subsequence */
	int non_contained = 0;
	/* print stage header */
	print_stage_header(STAGE_NUM_FOUR);
	for(i = 0; i < num_tweets-1; i++){
		/* reinitialize contained to 1 after the every loop */
		contained = 1; 
		for (j = 0; j < num_tweets-1; j++){
			if (j != i){
				/* there is only one case which is tweets[i] is shorter than 
				tweets[j] and tweets[i] is in the tweets[j] do not 
				need to print out */
				if (str_len(tweets[i]) <= str_len(tweets[j])){
					if(is_contained(tweets[i],tweets[j]) == IS_CONTAINED){
						contained = 0;
						/* add number of tweets is subsequence */
						non_contained++;
					}
				}
			}
		
		}
		
		if(contained == 1) {
			/* print the result when flag contained equal to 1 */
			printf("%s\n",tweets[i]);
		}
	
	}
	/* print the non_contained which is number_tweets minus 1 minus 
	number of tweets is subsequence */
	printf("Non-contained: %d\n", num_tweets-1-non_contained);
	printf("\n");
}
						
/* "algorithms are fun"	*/
	
	


/* stage 5: sorting the tweets */
void 
stage_five(tweet_t tweets[], int num_tweets) {
	/* add code for stage 5 (optional stage) */
	print_stage_header(STAGE_NUM_FIVE);
	
}
/* "algorithms are fun" */
