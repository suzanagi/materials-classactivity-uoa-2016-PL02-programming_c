#include <stdio.h>
#define N 10

typedef struct{
  int bomb;      /* 地雷の有無(0=無、1=有) */
  int bombCount; /* 周辺の地雷の数 */
  int open;      /* 開いているかどうか(0=閉、1=開) */
  int flag;      /* 旗の有無(0=無、1=有) */
}Status;

typedef struct{
  Status status[N][N]; /* 盤面 */
  int flagCount;       /* 全ての配置した旗の数 */
  int correctCount;    /* 正しい配置をした旗の数 */
  int bombs;           /* 設置する地雷の数 */
}Map;

void Initialize(Map*);
int Judge(Map*);
void View(Map);
void Open(Map*);

int main(){
  
  
  Map map;
  
  //マップデータの初期化
  Initialize(&map);
  
  //ゲームループ
  while(1){
    //配置した旗の数と設置してある地雷の数を表示
    printf("\nFlag/Bomb:%d/%d\n",___,___);
    View(___);
    if(Judge(___)==1)break;
  }

  Open(___);
  View(___);

  return 0;
}

/*
 *マップデータの初期化を行う関数
 *引数   :Map*
 *戻り値 :なし
 */
void Initialize(Map *map){
  /* 変数宣言 */
  int i,j,x,y;

  /* 乱数による地雷数の設定 */
  ________;
  map->bombs = __;

  map->flagCount = 0;
  map->correctCount = 0;
  

  /* 盤面(Status[N][N])内の要素の初期化 */
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      map->status[i][j].bomb = _;
      map->status[i][j].open = _;
      map->status[i][j].flag = _;
    }
  }
  tmp=0;
  while(1){
    /* 地雷を配置する位置を乱数で設定 */
    x = _____;
    y = _____;
    /* 配置箇所が被ってないかを確認 */
    if(_____________){
      map->status[x][y].bomb = _;
      tmp++;
    }
    if(______)break;
  }
  /* 周辺の地雷の数を検索 */
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      tmp=0;
      for(x=-1;x<2;x++){
	for(y=-1;y<2;y++){
	  if( (i+x>=0 && i+x<N) && (j+y>=0 && j+y<N))
            tmp += ___;
        }
      }
      map->status[i][j].bombCount = tmp;
    }
  }
}

/*
 *座標を入力し、判定を行う関数
 *引数   :Map*
 *戻り値 :int(判定の結果:0=続行,1=終了)
 */
int Judge(Map *map){
  /* 変数宣言 */
  int i,x,y;

  /* 入力を行う
   * 変数iに何をするか、xにX座標、yにY座標をそれぞれ入力 
   */
  printf("Input : i(0=open/1=flag) x y \nInput : ");
  scanf("%d",__);
  if(___)return 1;
  scanf("%d %d",__,__);
  
  if(0<=x&&x<N && 0<=y&&y<N){
    /* 盤面を開くとき */
    if(i==0){
      /* 指定された座標に旗が立っていなければ開く */
      if(_____){
	__________;
	
        /* 開いた箇所に地雷があれば終了 */
	if(_____){
	  printf("\nBOMB!!\n");
	  return 1;
	}
      }
    }
    /* 旗を設置するとき */
    else if(i==1){
      /* 指定された座標が開いてなければ旗の状態を変更 */
      if(______){
	map->status[y][x].flag = ____;

        /* 旗を置いたとき旗の総数を増やし、削除したときは減らす。 
         * また、正しく旗が置かれているかも判定し、カウントする。 */
	if(____){
	  _____;
	  if(map->status[y][x].bomb==1){//地雷上の時
	    ___;
	  }
	}else{
	  _____;
	  if(map->status[y][x].bomb==1){//地雷上の時
	    ___;
	  }
	}
      }
    }
  }
  
  /* クリア判定 */
  if(_____){
    printf("\n--CLEAR--\n");
    return 1;
  }
  
  return 0;
}

/*
 *盤面をコンソール上に表示する関数
 *引数   :Map
 *戻り値 :なし
 */
void View(Map map){
  /* 変数宣言 */
  int i,j;

  printf("\n");
  printf("\\ ");
  for(i=0;i<N;i++){
    printf("%d",i);
  }
  printf("\n \\==========\n");
  for(i=0;i<N;i++){
    printf("%d|",i);
    for(j=0;j<N;j++){
      /* 開いていない時 */
      if(____){
	if(____){
	  printf("F");
	}else{
	  printf("-");
	}
      }
      /* 開いている時 */
      else{
	if(____){
	  printf("x");
	}else{
	  printf("%d",____);
	}
      }
    }
    printf("|\n");
  }
  printf("  ==========\n\n");

}


/*
 *盤面の地雷が配置してある箇所をすべて開く関数
 *引数   :Map*
 *戻り値 :なし
 */
void Open(Map *map){
  /* 変数宣言 */
  int i,j;
  
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      if(map->status[i][j].bomb==1){
	map->status[i][j].open=1;
      }
    }
  }
}
