/* [ファイルの上部にはこんな感じでコメントと日付を書いてください]
 * consoletetris.c
 *
 *  Created on: 20XX/XX/XX
 *      Author: Your Name
 */

/* インクルードヘッダ */
#include <stdio.h>   /* Standard IO */
#include <stdlib.h>  /* Standard Library */
#include <string.h>  /* String */
#include <time.h>    /* Time: ランダムの生成のために必要 */
#include <termios.h> /* TermiOS: 非同期通信のための汎用ターミナルインターフェース  */
#include <unistd.h>  /* UNIX標準定数・型 */
#include <fcntl.h>   /* ファイルコントロール */
#define BLOCKS 7      /* ブロックの種類 */
#define ONEPOINT 100  /* 1行のみのポイント */
#define TWOPOINT 400  /* 同時消し2行のポイント */
#define THRPOINT 900  /* 同時消し3行のポイント */
#define FORPOINT 1600 /* 同時消し4行のポイント */
#define FPS      2000 /* 落下速度調整: Macだと2000, Unixだと1500くらい？ */
/* グローバル変数 */
int stage[21][12]; /* [ここにコメントを記入] */
int block[4][4];   /* [ここにコメントを記入] */
int field[21][12]; /* [ここにコメントを記入] */
int block_list[BLOCKS][4][4] = { /* ７種類のブロックのデータ */
  { { 0, 1, 0, 0 }, { 0, 1, 0, 0 }, { 0, 1, 0, 0 }, { 0, 1, 0, 0 } },   /* I */
  { { 0, 0, 0, 0 }, { 0, 1, 1, 0 }, { 0, 1, 0, 0 }, { 0, 1, 0, 0 } },   /* L */
  { { 0, 0, 1, 0 }, { 0, 1, 1, 0 }, { 0, 1, 0, 0 }, { 0, 0, 0, 0 } },   /* 逆S */
  { { 0, 1, 0, 0 }, { 0, 1, 1, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 0 } },   /* S */
  { { 0, 0, 0, 0 }, { 0, 1, 0, 0 }, { 1, 1, 1, 0 }, { 0, 0, 0, 0 } },   /* T */
  { { 0, 0, 0, 0 }, { 0, 1, 1, 0 }, { 0, 1, 1, 0 }, { 0, 0, 0, 0 } },   /* O */
  { { 0, 0, 0, 0 }, { 0, 1, 1, 0 }, { 0, 0, 1, 0 }, { 0, 0, 1, 0 } } }; /* 逆L */
int lvspeed[15] = { 200, 180, 160, 140, 120, 105, 90, 75, 60, 50, 40, 30, 20, 15, 10 }; /* 落下速度 */
int y = 0;         /* ブロックの画面上でのy座標 */
int x = 4;         /* ブロックの画面上でのx座標 */
int oneline, twoline, threeline, fourline; /* 消したラインの数 */
int gameover = 0;  /* ゲームオーバー判定。新しいブロックが初期位置に置けなければ1になる。 */
int nextblock = 0; /* [ここにコメントを記入] */
int block_type;    /* ブロックの種類用。0~6の乱数を入れる */
int level = 1;     /* [ここにコメントを記入] */
int point = 0;     /* [ここにコメントを記入] */
int toffset = 0;   /* 最下段までブロックが行った時に下ボタンを押した時に加算されるタイマー */
/* 関数プロトタイプ宣言 */
void Initialize();          /* ゲーム起動直後の初期設定を行う関数。画面と壁のデータを初期化 */
int CreateBlock();          /* [ここにコメントを記入] */
void ShowGameField();       /* [ここにコメントを記入] */
void ControlBlock();        /* [ここにコメントを記入] */
int CheckOverlap(int, int); /* [ここにコメントを記入] */
void MoveBlock(int, int);   /* [ここにコメントを記入] */
int TurnRightBlock();       /* [ここにコメントを記入] */
int TurnLeftBlock();        /* [ここにコメントを記入] */
void DropBlock();           /* [ここにコメントを記入] */
void LockBlock();           /* [ここにコメントを記入] */
void CheckLines();          /* [ここにコメントを記入] */
int kbhit();                /* キーボードを1回ヒットしたかどうかの判定 */
int GetTimeOfLevel(int);    /* [ここにコメントを記入] */
void GameStart();           /* [ここにコメントを記入] */
/*
 * メイン関数
 */
int main() {
  /* キーボードの入力を隠すための処理 */
  system("stty echo -icanon min 1 time 0");
  /* 時間をカウント */
  int time = 0;
  /* [ここにコメントを記入] */
  GameStart();
  /* [ここにコメントを記入] */
  Initialize();
  /* [ここにコメントを記入] */
  while (!gameover) {
    /* キー入力があればそれに応じて操作 */
    if (kbhit()) {
      ControlBlock();
    }
    /* [ここにコメントを記入] */
    if (time < GetTimeOfLevel(level)) {
      time += toffset + 1; /* 時間経過 */
      toffset = 0;
    } else {
      DropBlock(); /* [ここにコメントを記入] */
      time = 0;
    }
  }
  /* キーボードの入力設定を元に戻す */
  system("stty echo icanon min 1 time 0");
  return 0;
}
/*
 *  [ここにコメントを記入]
 *  Initialize()
 */
void Initialize() {
  int i, j; /* forループ制御用変数 */
  /* [ここにコメントを記入] */
  for (i = 0; i <= 20; i++) {
    for (j = 0; j <= 11; j++) {
      if ((j == 0) || (j == 11) || (i == 20)) {
	field[i][j] = stage[i][j] = 9;
      } else {
	field[i][j] = stage[i][j] = 0;
      }
    }
  }
  /* [ここにコメントを記入] */
  srand((unsigned) time(NULL ));
  nextblock = rand() % 7;
  /* [ここにコメントを記入] */
  CreateBlock();
  /* [ここにコメントを記入] */
  ShowGameField();
}
/*
 *  [ここにコメントを記入]
 *  CreateBlock()
 *  帰り値: [ここにコメントを記入]
 */
int CreateBlock() {
  int i, j; /* forループ制御用の変数 */
  /* ブロックの座標を初期位置にリセット */
  y = 0;
  x = 4;
  /* [ここにコメントを記入] */
  block_type = nextblock;
  //srand((unsigned)time(NULL));
  nextblock = rand() % 7;
  /* [ここにコメントを記入] */
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      block[i][j] = 0;
      block[i][j] = block_list[block_type][i][j];
    }
  }
  /* [ここにコメントを記入] */
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      field[i][j + 4] = stage[i][j + 4] + block[i][j];
      /* [ここにコメントを記入] */
      if (field[i][j + 4] > 1) {
	gameover = 1;
	return 1;
      }
    }
  }
  return 0;
}
/*
 *  [ここにコメントを記入]
 *  ShowGameField()
 */
void ShowGameField() {
  int i, j; /* forループ制御用変数 */
  /* 画面を一旦クリア */
  system("clear");
  /* [ここにコメントを記入] */
  for (i = 0; i < 21; i++) {
    for (j = 0; j < 12; j++) {
      switch (field[i][j]) {
      case 0:
	printf("　");
	break;
      case 9:
	printf("囗");
	break;
      default:
	printf("圖");
	break;
      }
    }
    /* 右サイド表示部分 */
    /* 2-7行目: 次ブロック   */
    if (i == 1)
      printf("　　囗ＮＥＸＴ囗");
    else if (i >= 2 && i <= 5) {
      printf("　　囗");
      for (j = 0; j < 4; j++) {
	switch (block_list[nextblock][i - 2][j]) {
	case 0:
	  printf("　");
	  break;
	default:
	  printf("圖");
	  break;
	}
      }
      printf("囗");
    } else if (i == 6)
      printf("　　囗囗囗囗囗囗");
    /* 9行目〜14行目 操作説明 */
    else if (i == 8)
      printf("　　←　右移動");
    else if (i == 9)
      printf("　　→　左移動");
    else if (i == 10)
      printf("　　↓　下移動");
    else if (i == 11)
      printf("　　Ｚキー　左回転");
    else if (i == 12)
      printf("　　Ｘキー　右回転");
    else if (i == 13)
      printf("　　Ｑキー　終了");
    /* 16行目〜18行目 レベルとスコア表示 */
    else if (i == 15)
      printf("　　囗囗囗ＳＣＯＲＥ囗囗囗");
    else if (i == 16)
      printf("　　囗 LV:%2d/%10d 囗", level, point);
    else if (i == 17)
      printf("　　囗囗囗囗囗囗囗囗囗囗囗");
    /* 各行の改行 */
    printf("\n");
  }
  /* [ここにコメントを記入] */
  printf("\n１行消し：%d回 ２行消し：%d回 ３行消し：%d回 ４行消し：%d回\n", oneline, twoline,threeline, fourline);
  /* [ここにコメントを記入] */
  if (gameover) {
    system("clear");
    printf("\nYour Lines:\n１行消し：%d回 ２行消し：%d回 ３行消し：%d回 ４行消し：%d回\nYour Level: %d\nYour Scoure: %12d\n\nGAME OVER\n\n", oneline, twoline, threeline, fourline, level, point);
  }
}
/*
 * [ここにコメントを記入]
 * ControlBlock()
 */
void ControlBlock() {
  char key; /* [ここにコメントを記入] */
  /* [ここにコメントを記入] */
  key = getchar();
  /* キーに応じて各方向へブロックを移動したり、回転させたりする */
  /* qキー: ゲーム終了（強制GameOver） */
  /* zキー: ブロック左回転                          */
  /* xキー: ブロック右回転                          */
  /* ←キー: 左移動 (ESC]C)        */
  /* →キー: 右移動 (ESC]D)        */
  /* ↓キー: 下移動 (ESC]B)        */
  switch (key) {
  case 'q':
    gameover = 1;
    ShowGameField();
    break;
  case 'z':
    TurnLeftBlock();
    break;
  case 'x':
    TurnRightBlock();
    break;
  case 27:
    key = getchar();
    if (key == 91) {
      key = getchar();
      switch (key) {
      case 'B': /* Down */
	if (!CheckOverlap(x, y + 1)) {
	  MoveBlock(x, y + 1);
	} else {
	  toffset = 300 * FPS; /* 一番下まで行たときに下ボタン押したら次のブロック */
	}
	break;
      case 'C': /* Left */
	if (!CheckOverlap(x + 1, y)) {
	  MoveBlock(x + 1, y);
	}
	break;
      case 'D': /* Right */
	if (!CheckOverlap(x - 1, y)) {
	  MoveBlock(x - 1, y);
	}
	break;
      default:
	break;
      }
    }
    break;
  default:
    break;
  }
}
/* [関数コメント例]
 * 被りのチェックを行う関数
 * CheckOverlap()
 * 戻り値: int: もし壁等に被る場合 = 1, それ以外 = 0.
 * 引数: int x2: ブロックを格納している4x4の配列の左上のx座標
 * int y2:  ブロックを格納している4x4の配列の左上のy座標
 */
int CheckOverlap(int x2, int y2) {
  int i, j; /* forループ制御用変数 */
  /* [ここにコメントを記入] */
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      if (block[i][j]) {
	if (stage[y2 + i][x2 + j] != 0) {
	  return 1;
	}
      }
    }
  }
  return 0;
}
/*
 * [ここにコメントを記入]
 * MoveBlock()
 * 引数: [ここにコメントを記入]
 */
void MoveBlock(int x2, int y2) {
  int i, j; /* forループ制御用変数 */
  /* [ここにコメントを記入] */
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      field[y + i][x + j] -= block[i][j];
    }
  }
  /* [ここにコメントを記入] */
  x = x2;
  y = y2;
  /* [ここにコメントを記入] */
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      field[y + i][x + j] += block[i][j];
    }
  }
  /* [ここにコメントを記入] */
  ShowGameField();
}
/*
 * [ここにコメントを記入]
 * TurnRightBlock()
 * 戻り値: [ここにコメントを記入]
 * ブロック右回転の重なりチェックはこの中で行っている .
 * 壁蹴り1マス分実装（但し、テトリス棒は除く.
 */
int TurnRightBlock() {
  int i, j; /* forループ制御用 */
  int tmp[4][4]; /* [ここにコメントを記入] */
  int offset = 0;
  /* [ここにコメントを記入] */
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      tmp[i][j] = block[i][j];
    }
  }
  /* [ここにコメントを記入] */
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      block[i][j] = tmp[3 - j][i];
    }
  }
  /* [ここにコメントを記入] */
  if (CheckOverlap(x, y)) {
    /* 壁蹴り左壁 */
    if (!CheckOverlap(x + 1, y) && block_type != 0)
      offset = 1;
    /* 壁蹴り右壁 */
    else if (!CheckOverlap(x - 1, y) && block_type != 0)
      offset = -1;
    /* ダメだと戻す */
    else {
      for (i = 0; i < 4; i++) {
	for (j = 0; j < 4; j++) {
	  block[i][j] = tmp[i][j];
	}
      }
      return 1;
    }
  }
  /* [ここにコメントを記入] */
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      field[y + i][x + j] -= tmp[i][j];
    }
  }
  /* 壁蹴り分の移動 */
  x = x + offset;
  /* [ここにコメントを記入] */
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      field[y + i][x + j] += block[i][j];
    }
  }
  /* [ここにコメントを記入] */
  ShowGameField();
  return 0;
}
/*
 * [ここにコメントを記入]
 * TurnLeftBlock()
 * 戻り値: [ここにコメントを記入]
 * ブロック左回転の重なりチェックはこの中で行っている.
 * 壁蹴り1マス分実装（但し、テトリス棒は除く.
 */
int TurnLeftBlock() {
  int i, j; /* forループ制御用 */
  int tmp[4][4]; /* [ここにコメントを記入] */
  int offset = 0;
  /* [ここにコメントを記入] */
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      tmp[i][j] = block[i][j];
    }
  }
  /* [ここにコメントを記入] */
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      block[i][j] = tmp[j][3 - i];
    }
  }
  /* [ここにコメントを記入] */
  if (CheckOverlap(x, y)) {
    /* 壁蹴り左壁 */
    if (!CheckOverlap(x + 1, y) && block_type != 0)
      offset = 1;
    /* 壁蹴り右壁 */
    else if (!CheckOverlap(x - 1, y) && block_type != 0)
      offset = -1;
    /* ダメだと戻す */
    else {
      for (i = 0; i < 4; i++) {
	for (j = 0; j < 4; j++) {
	  block[i][j] = tmp[i][j];
	}
      }
      return 1;
    }
  }
  /* [ここにコメントを記入] */
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      field[y + i][x + j] -= tmp[i][j];
    }
  }
  /* 壁蹴り分の移動 */
  x = x + offset;
  /* [ここにコメントを記入] */
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      field[y + i][x + j] += block[i][j];
    }
  }
  /* [ここにコメントを記入] */
  ShowGameField();
  return 0;
}
/*
 * [ここにコメントを記入]
 * DropBlock()
 */
void DropBlock() {
  /* [ここにコメントを記入] */
  if (!CheckOverlap(x, y + 1)) {
    MoveBlock(x, y + 1);
  }
  /* [ここにコメントを記入] */
  else {
    LockBlock();
    CreateBlock();
    ShowGameField();
  }
}
/*
 * [ここにコメントを記入]
 * LockBlock()
 */
void LockBlock() {
  int i, j; /* forループ制御用変数 */
  /* [ここにコメントを記入] */
  for (i = 0; i < 21; i++) {
    for (j = 0; j < 12; j++) {
      stage[i][j] = field[i][j];
    }
  }
  /* [ここにコメントを記入] */
  CheckLines();
  /* [ここにコメントを記入] */
  for (i = 0; i < 21; i++) {
    for (j = 0; j < 12; j++) {
      field[i][j] = stage[i][j];
    }
  }
}
/*
 * [ここにコメントを記入]
 * CheckLines()
 */
void CheckLines() {
  int i, j, k; /* forループ制御用 */
  int comp; /* 横一列がそろっていれば１、一つでも隙間があると０になる */
  int lines = 0; /* 同時に消したラインの数 */
  while (1) {
    for (i = 0; i < 20; i++) {
      comp = 1;
      /* [ここにコメントを記入] */
      for (j = 1; j < 11; j++) {
	if (stage[i][j] == 0) {
	  comp = 0;
	}
      }
      /* [ここにコメントを記入] */
      if (comp == 1)
	break;
    }
    /* [ここにコメントを記入] */
    if (comp == 0)
      break;
    /* [ここにコメントを記入] */
    lines++;
    /* [ここにコメントを記入] */
    for (j = 1; j < 11; j++) {
      stage[i][j] = 0;
    }
    /* [ここにコメントを記入] */
    for (k = i; k > 0; k--) {
      for (j = 1; j < 11; j++) {
	stage[k][j] = stage[k - 1][j];
      }
    }
  }
  /* [ここにコメントを記入] */
  switch (lines) {
  case 1:
    oneline++;
    break;
  case 2:
    twoline++;
    break;
  case 3:
    threeline++;
    break;
  case 4:
    fourline++;
    break;
  default:
    break;
  }
  /* [ここにコメントを記入] */
  point = oneline * 100 + twoline * 400 + threeline * 900 + fourline * 1600;
  /* [ここにコメントを記入] */
  level = (int) (point / 2000.0) + 1;
  /* [ここにコメントを記入] */
  if (level > 15)
    level = 15;
}
/*
 *  キーボードが押されたかどうかの判定を返す関数
 * kbhit()
 * 返り値: キーボードが押された場合 = 1, 他 = 0
 * この関数は難しいので、『そういうものだ』としてください
 */
int kbhit(void) {
  //  struct termios oldt, newt; /* termosで保持する構造体 */
  int ch;                    /* 確認する文字 */
  int oldf;                  /* ファイル状態 */
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);   /* ファイル操作状態の取得 */
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK); /* 文字取得状態待ちの解除 */
  ch = getc(stdin); /* 文字取得 */
  fcntl(STDIN_FILENO, F_SETFL, oldf);      /* ファイル操作の状態を元に戻す（Unlock） */
  /* 文字が取得されたかどうかを検査 */
  if (ch != EOF) {
    ungetc(ch, stdin); /* 文字がとれていたら判定のために文字をバッファに戻す */
    return 1;
  }
  return 0;
}
/*
 * [ここにコメントを記入]
 * GetTimeOfLevel
 * 戻り値: [ここにコメントを記入]
 * 引数: [ここにコメントを記入]
 */
int GetTimeOfLevel(int level) {
  if (level >= 1 && level <= 15)
    return FPS * lvspeed[level - 1];
  else
    return 5 * FPS;
}
/*
 * [ここにコメントを記入]
 * GameStart()
 */
void GameStart() {
  FILE* fp; /* [ここにコメントを記入] */
  char string[60]; /* [ここにコメントを記入] */
  char sprite[1000]; /* [ここにコメントを記入] */
  char ch; /* [ここにコメントを記入] */
  int ret;
  int flag = 1; /* ゲームセンターっぽく点滅させるためのフラグ管理 */
  int time = 9999; /* タイマー */
  /* [ここにコメントを記入] */
  fp = fopen("sprite.txt", "r");

  /* [ここにコメントを記入] */
  fscanf(fp, "%s", sprite);
  while ((ret = fscanf(fp, "%s", string)) != EOF) {
    strcat(sprite, "\n");
    strcat(sprite, string); /* [ここにコメントを記入] */
  }
  /* [ここにコメントを記入] */
  fclose(fp);
  /* スプライト表示 */
  while (1) {
    /* タイマーがカンストするたびに更新  */
    if (time > 80 * FPS) {
      /* 一度消去 */
      system("clear");
      /* [ここにコメントを記入] */
      printf("%s\n\n", sprite);
      /* プログラミングコースのクレジット */
      printf("\n    2012 Programming C Course\n\n");
      if (flag == 1) {
	/* 点滅させる所 */
	printf("     PUSH SPACE KEY TO START\n");
      }
      /* 点滅フラグ */
      flag *= -1;
      /* タイマーを戻す */
      time = 0;
    }
    /* キーレスポンスの設定 */
    if (kbhit()) {
      ch = getchar();
      if (ch == 'q') { /* [ここにコメントを記入] */
	gameover = 1;
	break;
      } else if (ch == ' ') { /* [ここにコメントを記入] */
	break;
      }
    }
    /* [ここにコメントを記入] */
    time++;
  }
  /* [ここにコメントを記入] */
  return;
}
