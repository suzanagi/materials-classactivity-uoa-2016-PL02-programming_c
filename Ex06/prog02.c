#include <stdio.h>
#include <ctype.h> /* 関数toupperを使うため */

void printFavoriteVegetable(char *);

int main() {
  char *vegetables[]={"tomate", "cabbage", "eggplant"};
  int i;

  printf("Suppose that we now have (0) %s, (1) %s, (2) %s.\n",
                                    vegetables[0],vegetables[1],vegetables[2]);
  printf("Which do you like?\n");
  printf("Input 0, 1, or 2: ");
  scanf("%d",&i);
  
  if(0 <= i && i <= 2) { /* i が 0-2 の範囲になければエラーを避けるため何もしない */
    printFavoriteVegetable(vegetables[i]);
  }  
  return 0;
}

void printFavoriteVegetable(char *favoritevegetable) {
  
  printf("%c",toupper(*favoritevegetable)); /* 最初の文字を大文字で出力 */
  printf("%s",favoritevegetable + 1); /* 二文字目以降を出力 */
  printf(" is your favorite vegetable!\n");
  
}                                             
