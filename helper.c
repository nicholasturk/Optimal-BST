/*
name: Nicholas Sturk
email: nsturk@uoguelph.ca
id: 1058650
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "definitions.h"

int string_comparison(const void *a, const void *b) {
  return strcmp(*(char * const *)a, *(char * const *)b);
}

void optimal_bst(Word keys[]){

  /*initialize table base conditions*/
  int i;
  for(i = 1; i <= NUM_KEYS; i++){
    main_table[i][i - 1] = 0;
    main_table[i][i] = keys[i].probability;
    root_table[i][i] = i;  
  }

  /*ending condition*/
  main_table[NUM_KEYS + 1][NUM_KEYS] = 0;

  double minval, sum;
  int d, j, k, kmin, s;

  for(d = 1; d <= NUM_KEYS - 1; d++){
    for(i = 1; i <= NUM_KEYS - d; i++){
      j = i + d;
      minval = MAX_FLOAT;
      for(k = i; k <= j; k++){
        if(main_table[i][k - 1] + main_table[k + 1][j] < minval){
          minval = main_table[i][k - 1] + main_table[k + 1][j];
          kmin = k;
        }
      }
      root_table[i][j] = kmin;
      sum = 0;
      for(s = i; s <= j; s++){
        sum += keys[s].probability;
      }
      main_table[i][j] = minval + sum;
    }
  }
}

Node *new_node(Word *key){

  Node *new = (Node *)malloc(sizeof(Node));

  new->key = malloc(strlen(key->data));
  strcpy(new->key, key->data);
  new->probability = key->probability;
  new->left = new->right = NULL;

  return new;
}

Node *add_node(Node *root, Word key){

  if(!root){
    return new_node(&key);
  }

  if((strcmp(key.data, root->key)) < 0){
    root->left = add_node(root->left, key);
  } 

  else if((strcmp(key.data, root->key)) > 0){
    root->right = add_node(root->right, key);
  }

  return root;
}

void print_tree(Node *root){

  if(root){
    print_tree(root->left);
    printf("%s\n", root->key);
    print_tree(root->right);
  }
}

int find_highest(int start, int end){

  double highest = -1;
  int index = -1;

  int i;
  for(i = start; i <= end; i++){
    if(keys[i].probability > highest){
      highest = keys[i].probability;
      index = i;
    }
  }
  return index;
}
















