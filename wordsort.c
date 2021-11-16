//Veronica Martucci
//COP3502 Fall 2021
//P5: Word Sorting, Searching
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int arrIDX;

//This struct stores the information for one tree node
typedef struct treeNodeData{
  char word[21];
  int freq;
  int height;

}treeNodeData;

typedef struct treeNode{
  struct treeNodeData *data;
  struct treeNode* left;
  struct treeNode* right;

}treeNode;

//This function inserts a new node for the new word that was inputted
treeNode *insert(treeNode *root, char string[], int currDepth){

  //base case: Create new node and return the pointer to it
  if(root == NULL){

    treeNode *temp = malloc(sizeof(treeNode));
    treeNodeData *temp2 = malloc(sizeof(treeNodeData));

    strcpy(temp2 -> word, string);

    temp2 -> freq = 1;
    temp2 -> height = currDepth;
    temp -> left = NULL;
    temp -> right = NULL;
    temp -> data = temp2;

    return temp;
  }

  //if string matches word in node increase freqency.
  if(strcmp(root -> data -> word, string) == 0){

    root -> data -> freq++;
    return root;
  }

  //Insert on left side
  if(strcmp(string, root -> data -> word) < 0){

    root -> left = insert(root -> left, string, currDepth + 1);
  }
  //insert on the right
  else{

    root -> right = insert(root -> right, string,currDepth + 1);
  }

  return root;
}

//This function finds the frequency and height of the word that was inputted
void query(treeNode *root, char string[], int arr[]){

    if(root == NULL){
      arr[0] = -1;
      arr[1] = -1;
      return;
    }

    //if string matches the word in node, print freq and height of that word.
    if(strcmp(root -> data -> word, string) == 0){
      arr[0] = root -> data -> freq;
      arr[1] = root -> data -> height;

      return;
    }

    if(strcmp(string, root -> data -> word) < 0){
      query(root -> left, string, arr);
    }
    else{
      query(root -> right, string, arr);
    }
}

//This function copies the tree nodes into an array
void createArr(treeNode *root, treeNodeData *arr){

  if(root == NULL){
    return;
  }

  createArr(root -> left, arr);
  arr[arrIDX++] = *root -> data;
  createArr(root -> right, arr);
}

//This function takes the partly sorted array and sorts
//the entire array in alphabetical order
void merge(treeNodeData *arr, int low, int mid, int high){

    int length = high - low + 1;

    treeNodeData *temp = (treeNodeData*)calloc(length, sizeof(treeNodeData));

    int mergePos = 0;
    int leftPos = low;
    int rightPos = mid;

    while((leftPos < mid) || (rightPos <= high)){

      if(rightPos > high || (leftPos < mid && arr[leftPos].freq < arr[rightPos].freq)){

        temp[mergePos] = arr[leftPos];
        leftPos++;
        mergePos++;
      }
      else{

        temp[mergePos] = arr[rightPos];
        rightPos++;
        mergePos++;
      }
    }

    for(int i = low; i <= high; i++){

      arr[i] = temp[i - low];
    }

    free(temp);
}

//This function sorts the array using merge sort
void mergeSort(treeNodeData *arr, int low, int high){

  int mid;

  if(low < high){

    mid = (low + high) / 2;

    //Sort first half of array
    mergeSort(arr, low, mid);
    //Sort second half of array
    mergeSort(arr, mid + 1, high);
    //merge both halves of the array into one.
    merge(arr, low, mid + 1, high);
  }
}

//This function prints out the words and freq starting with
//the word that has the highest frequency
void printResult(treeNodeData *arr){

  while(arrIDX > 0){

    printf("%s %d\n", arr[arrIDX - 1].word, arr[arrIDX - 1].freq);
    arrIDX--;
  }
}

int main(){

  int numWords, action;
  scanf("%d", &numWords);
  treeNode *tree = NULL;

  for(int i = 0; i < numWords; i++){

    char string[21];
    scanf("%d %s", &action, string);

    //if action = 1, insert node
    if(action == 1){

      tree = insert(tree, string, 0);
    }
    //if action = 2, print the frequency and height
    else if(action == 2){

      int answer[2];

      query(tree, string, answer);
      printf("%d %d\n", answer[0], answer[1]);
    }
  }

  arrIDX = 0;
  treeNodeData *arr = malloc(2000000 * sizeof(treeNodeData));

  createArr(tree, arr);
  mergeSort(arr, 0, arrIDX - 1);
  printResult(arr);

  free(tree);
  free(arr);

  return 0;
}
