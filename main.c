/*
name: Nicholas Sturk
email: nsturk@uoguelph.ca
id: 1058650
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definitions.h"

int main(){

  char buffer[256];
  char *words[NUM_WORDS];

  FILE *fp = fopen("data_7.txt", "r");

  /*obtain words*/
  int i;
  for(i = 0; i < NUM_WORDS; i++){
    fscanf(fp, "%s", buffer);
    words[i] = malloc(strlen(buffer));
    strcpy(words[i], buffer);
  }

  /*sort words*/
  qsort(words, NUM_WORDS, sizeof(char *), string_comparison);

  /*place unique words in key array*/
  int frequency;
  int count = 0;
  for(i = 0; i < NUM_WORDS - 1; i++){
    frequency = 0;
    while(strcmp(words[i], words[i + 1]) == 0){
      frequency++;
      i++;
      if(i == NUM_WORDS - 1){
        break;
      }
    }

    frequency++;
    count++;

    /*add to keys with frequency and probability*/
    keys[count].data = words[i];
    keys[count].probability = (double)frequency / (NUM_WORDS);
  }

  optimal_bst(keys);

  char input[256];
  printf("\n--Q1 - optimal_bst --\n");
  printf("Enter a key: ");
  scanf("%s", input);

  int root, row, column;
  float val;

  row = 1;
  column = NUM_KEYS;

  do{

    /*intialize root and value to main tree root */
    root = root_table[row][column];
    val = main_table[row][column];

    if(!keys[root].data){
      printf("Not found.\n\n");
      break;
    }

    printf("Compared with '%s' (%f), ", keys[root].data, val);

    /*compare values and adjust indexes*/
    if(strcmp(keys[root].data, input) > 0){
      printf("go left subtree.\n");
      column = root - 1;

    } else if(strcmp(keys[root].data, input) < 0){
      printf("go right subtree.\n");
      row = root + 1;

    } else{
      printf("found.\n\n");
      break;
    }

  } while(1);

  printf("\n--Q2 - greedy_bst--\n");
  printf("Enter a key: ");
  scanf("%s", input);

  int start = 1, end = NUM_KEYS;
  int index = find_highest(start, end);

  do{

    if(!keys[index].data || start > end){
      printf("Not found.\n\n");
      break;
    }

    printf("Compared with '%s' (%f), ", keys[index].data, keys[index].probability);

    if(strcmp(keys[index].data, input) > 0){
      printf("go left subtree.\n");
      end = index - 1;
      index = find_highest(start, end);

    } else if(strcmp(keys[index].data, input) < 0){
      printf("go right subtree.\n");
      start = index + 1;
      index = find_highest(start, NUM_KEYS);

    } else{
      printf("found.\n\n");
      break;
    }

  } while(1);

  return 0;
}







