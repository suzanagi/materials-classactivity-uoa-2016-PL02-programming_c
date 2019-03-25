#include <stdio.h>
#include <string.h>

int checkString(char *);

int main()
{
  int i;
  char newsstring[7][15]={"Good News", "Cool News", "Happy News", "Bad News",
                       "Sweet News", "Sad News", "Wonderful News"};

  for(i = 0; i < 7; i++) {
    /* If a string contains the patterns "Bad" or "Sad", 
       replace it with the new string "GOOD News". */

    switch(checkString(newsstring[i])){
    case 0: 
      strcpy(newsstring[i],"GOOD News");
      break;
    case 1:
      break;
    default:
      printf("error!\n");
      break;
    }

  }
  /* Print out the result */
  printf("--\n");
  for(i = 0; i < 7; i++) printf("%2d %s\n",i ,newsstring[i]);
  printf("--\n");
  
  return 0;
}


/* Check whether a string contains the patterns "Bad" or "Sad" 
   at the first 3 characters using strncmp function */
/* Refer to the command "man strcmp" for the strncmp function. */
int checkString(char *str)
{//3文字がBadまたはSadと一致した場合に0を返す
  int i;
  char three[4];

  for(i = 0; i < 3; i++){
    three[i] = str[i];
  }

  if(strcmp(three,"Bad") == 0 || strcmp(three,"Sad") == 0)
    return 0;
  else 
    return 1;
}
