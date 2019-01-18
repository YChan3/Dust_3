#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void convertToUpperCase(char * temp) {
  char * name;
  name = strtok(temp,":");

  // Convert to upper case
  char *s = name;
  while (*s) {
    *s = toupper((unsigned char) *s);
    s++;
  }

}

char * fWinr(int max){
  FILE *fp;
  FILE *fa;
  char input[256];
  char input2[256];
  char input3[256];
  char input4[256];
  char ans[256];

  struct player{
  	char id[10];
  	char name[50];
  	int score;
  };

  /* opening file for reading */
  fp = fopen("PlayerAnswers.txt" , "r");

  int i = 1;
  struct player p1;
  struct player p2;
  struct player p3;
  struct player p4;

  char *token;

  fgets(input, 256, fp);
  p1.score = 0;
  token = strtok(input, ":");
  strcpy(p1.id, token);
  token = strtok(NULL, ":");
  token = strtok(token, "\n");
  strcpy(p1.name, token);

  fgets(input, 256, fp);
  p2.score = 0;
  token = strtok(input, ":");
  strcpy(p2.id, token);
  token = strtok(NULL, ":");
  token = strtok(token, "\n");
  strcpy(p2.name, token);

  fgets(input, 256, fp);
  p3.score = 0;
  token = strtok(input, ":");
  strcpy(p3.id, token);
  token = strtok(NULL, ":");
  token = strtok(token, "\n");
  strcpy(p3.name, token);

  fgets(input, 256, fp);
  p4.score = 0;
  token = strtok(input, ":");
  strcpy(p4.id, token);
  token = strtok(NULL, ":");
  token = strtok(token, "\n");
  strcpy(p4.name, token);

  fa = fopen("answers.txt" , "r");

  while(max--){
    fgets(ans, 256, fa);
    int counter = 4;
    while(counter--){
      fgets(input, 256, fp);
      strcpy(input2, input);
      strcpy(input3, input);
      strcpy(input4, input);
      token = strtok(input, ":");
      if(strcmp(p1.id, token) == 0){
        token = strtok(NULL, ":");
        token = strtok(token, "\n");
        convertToUpperCase(token);
        if(strcmp(token, strtok(ans, "\n")) == 0){
          p1.score += 1;
        }
      }
      token = strtok(input2, ":");
      if(strcmp(p2.id, token) == 0){
        token = strtok(NULL, ":");
        token = strtok(token, "\n");
        convertToUpperCase(token);
        if(strcmp(token, strtok(ans, "\n")) == 0){
          p1.score += 1;
        }
      }
      token = strtok(input3, ":");
      if(strcmp(p3.id, token) == 0){
        token = strtok(NULL, ":");
        token = strtok(token, "\n");
        convertToUpperCase(token);
        if(strcmp(token, strtok(ans, "\n")) == 0){
          p1.score += 1;
        }
      }
      token = strtok(input4, ":");
      if(strcmp(p4.id, token) == 0){
        token = strtok(NULL, ":");
        token = strtok(token, "\n");
        convertToUpperCase(token);
        if(strcmp(token, strtok(ans, "\n")) == 0){
          p1.score += 1;
        }
      }
    }
  }
  fclose(fa);
  fclose(fp);
  struct player w1;
  struct player w2;
  if(p1.score > p2.score){
    strcpy(w1.name, p1.name);
    w1.score = p1.score;
  }else{
    strcpy(w1.name, p2.name);
    w1.score = p2.score;
  }
  if(p3.score > p4.score){
    strcpy(w2.name, p3.name);
    w2.score = p3.score;
  }else{
    strcpy(w2.name, p4.name);
    w2.score = p4.score;
  }
  char *str_to_ret = malloc(sizeof(char) * 50);
  if(w1.score > w2.score){
    strcpy(str_to_ret, w1.name);
    return(str_to_ret);
  }
  strcpy(str_to_ret, w2.name);
  return(str_to_ret);
}

int main(){
  printf("%s\n",fWinr(1));
}
