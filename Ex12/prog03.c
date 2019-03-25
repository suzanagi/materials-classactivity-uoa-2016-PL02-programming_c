#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int x;        /* アリの位置（横） */
  int y;        /* アリの位置（縦） */
  char dir;     /* 'R'右向きか 'D'左向きか */
  int in;       /* 1:アリは盤上にいる 0:既に盤外に出ている */
}AntPos;

int main(int argc, char *argv[])
{
  int w, h, n;  /* 幅、高さ、初期状態でのアリの数 */
  int t=0;      /* 時間ステップのカウンタ */
  int i, j, num;
  AntPos *ant;
  FILE *ifile;

  if (argc < 2) {
    printf( "error: input file name is required!\n");
    exit(1);
  }

  /* ファイルオープン */
  if((ifile = fopen(argv[1],"r")) == NULL){
    printf("Cannot open file %s\n",argv[1]);
    exit(1);
  }

  /* ファイルの1行目から盤の幅w、高さh、アリの数nを読み込む */
  fscanf(ifile,"%d%d%d",&w,&h,&n);

      /*確認用
      printf("w=%d ,h=%d ,n=%d\n",w,h,n);
      */

  /* アリの情報を収めておく構造体配列を動的に確保 */
  ant = (AntPos *)malloc(n * sizeof(AntPos));

      /*確認用
      printf("ant = %d bytes\n",n * sizeof(AntPos));
      printf("AntPos = %d bytes\n",sizeof(AntPos));
      */

  /* ファイルから各アリの位置と向きを読み込む。なお、文字型を読む時は
     " %c"のように%c手前にスペースを入れると、R/D手前のスペースを読み飛ばせる。
     読み込めたら、確認のため読んだ情報を標準出力に出力 */
  for(i = 0; i < n; i++){
    fscanf(ifile,"%d %d %c",&ant[i].x ,&ant[i].y ,&ant[i].dir);
    printf("%d %d %c\n",ant[i].x ,ant[i].y ,ant[i].dir);
  }
      /*確認用
	for(i = 0; i < n; i++){
	  printf("ant%d x:%d, y:%d dir:%c\n",i ,ant[i].x ,ant[i].y ,ant[i].dir);
	}
      */

  /* 1ステップごとのループ。盤上にいるアリの数が0になったら終了 */
    /* 時間の更新、アリの座標の更新、アリが盤の外に出たかどうかのチェックと表示、
       2匹のアリが同じマスにいるかどうかのチェックと（必要なら）向きの更新 */
  
  /*初期ではアリがすべて盤上にいるため、すべてのアリのinステータスを1にする*/
  for(i = 0; i < n; i++) ant[i].in = 1;

  /*以下ステップごとのループ*/
  for(t = 1; ; t++){

    /*アリの数numは毎ターン0にする*/
    num = 0;

    /*アリを1匹ずつループ*/
    for(i = 0; i < n; i++){
      /*アリが盤上にいれば処理をする*/
      if(ant[i].in == 1){
	/*アリを1マスすすめる*/
	if(ant[i].dir == 'R'){//右向きの場合
	  ant[i].x++;
	}
	else if(ant[i].dir == 'D'){//下向きの場合
	  ant[i].y++;
	}
	else{//なんかよくわかんない場合
	  printf("unsigned direction: ant%d(%c)\n",i ,ant[i].dir);
	  exit(8);
	}
	
	/*アリが盤面の外にでたら、inステータスを0にする*/
	if(ant[i].x > w || ant[i].y > h){
	  ant[i].in = 0;
	  printf("Time = %d: ",t);
	  /*iは0からカウントしているため+1して表示*/
	  printf("Ant %d has gone out to (%d,%d)\n",i + 1 ,ant[i].x ,ant[i].y);
	}
	
	/*i番目のアリが盤上にいればnumに加算する*/
	num += ant[i].in;
      }
      else continue;  
      /*アリがすでに出て行ったなら処理はしない*/
    }

    /*2匹以上のアリの位置が同じで
      かつ白のマスならすべてのアリの方向を変える*/
    /*i以下のjの数はすでに比較されているため総当たりは必要ない*/
    for(i = 0; i < n - 1; i++){
      for(j = i + 1; j < n; j++){
	if(ant[i].x == ant[j].x){ //2匹のアリのx座標が同じ
	  if(ant[i].y == ant[j].y){//かつ2匹のアリのy座標が同じ

	    /*経過表示
	    printf("座標まで一致(i:%d j:%d)\n",i,j);
	    */

	    if((ant[i].x + ant[i].y) % 2 == 0){//かつ2匹のアリは白座標にいる

	      /*経過表示
	      printf("反転なう(i:%d j:%d)\n",i,j);
	      */

	      /*ant[i]の向きを反転*/
	      if(ant[i].dir == 'R') ant[i].dir = 'D';
	      else ant[i].dir = 'R';
	      /*ant[j]の向きを反転*/
	      if(ant[j].dir == 'R') ant[j].dir = 'D';
	      else ant[j].dir = 'R';
	    }
	    else continue; //2匹のアリは黒座標にいる
	  }
	  else continue; //とくに位置はかぶってない
	}
	else continue; //とくに位置はかぶってない
      }
    }

    /*確認のための経過表示
    printf("status:   (t:%d)\n",t);
    for(i = 0; i < n; i++)
      printf("Ant%d x:%d y:%d direction:%c\n",i ,ant[i].x ,ant[i].y ,ant[i].dir);
    */

    /*アリがすべて盤上から出て行ったら終了*/
    if(num == 0) break;
  }

  return 0;
}
