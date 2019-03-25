/* 
 *  consoletetris.c (prog04.c)
 *
 *  Created on: 2017/1/19
 *      Author: Yuta Nemoto
 */

/* インクルードヘッダ */
#include <stdio.h>   /* Standard IO */
#include <stdlib.h>  /* Standard Library */
#include <string.h>  /* String */
#include <time.h>    /* Time: ランダムの生成のために必要 */
#include <termios.h> /* TermiOS: 非同期通信のための汎用ターミナルインターフェース */
#include <unistd.h>  /* UNIX標準定数・型 */
#include <fcntl.h>   /* ファイルコントロール */
#define BLOCKS 7      /* ブロックの種類 */
#define ONEPOINT 100  /* 1行のみのポイント */
#define TWOPOINT 400  /* 同時消し2行のポイント */
#define THRPOINT 900  /* 同時消し3行のポイント */
#define FORPOINT 1600 /* 同時消し4行のポイント */
#define FPS      2000 /* 落下速度調整: Macだと2000, Unixだと1500くらい？ */
/* グローバル変数 */
int stage[21][12]; /* 下枠を含む縦21ブロック x 左右を含む横12ブロック のステージ情報を格納する配列 */
int block[4][4];   /* ブロックの形を保存する配列(ブロックの左右の長さは最大で4) */
int field[21][12]; /* 下枠を含む縦21ブロック x 左右を含む横12ブロック のフィールドを格納する配列 */
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
int nextblock = 0; /* 次のブロックの種類を格納する */
int block_type;    /* ブロックの種類用。0~6の乱数を入れる */
int level = 1;     /* プレイヤーレベル初期値1に設定する */
int point = 0;     /* プレイヤーのスコアを初期値0で設定 */
int toffset = 0;   /* 最下段までブロックが行った時に下ボタンを押した時に加算されるタイマー */
/* 関数プロトタイプ宣言 */
void Initialize();          /* ゲーム起動直後の初期設定を行う関数。画面と壁のデータを初期化 */
int CreateBlock();          /* ブロックを生成し次のブロックに格納する */
void ShowGameField();       /* 配列fieldから画面を描画する */
void ControlBlock();        /* キーの入力からブロックの回転、移動の処理をする */
int CheckOverlap(int, int); /* 操作中のブロックが壁、他ブロックに接触していない
			       かを確認する */
void MoveBlock(int, int);   /* 操作中のブロックを一旦消去し、指定の座標に移動する */
int TurnRightBlock();       /* ブロックを右回転する */
int TurnLeftBlock();        /* ブロックを左回転する */
void DropBlock();           /* ブロックを下移動させる。それ以上下移動ができなければその位置に固定 */
void LockBlock();           /* 着地したブロックを固定済みのブロックに追加する */
void CheckLines();          /* 横一列が揃っていればラインを消す処理をする
			     　また消したラインの上のブロックを下に落とす*/
int kbhit();                /* キーボードを1回ヒットしたかどうかの判定 */
int GetTimeOfLevel(int);    /* レベルごとのブロック落下時間を取得する */
void GameStart();           /* ゲーム開始時のスプライト表示 */
/*
 * メイン関数
 */
int main() {
  /* キーボードの入力を隠すための処理 */
  system("stty echo -icanon min 1 time 0");
  /* 時間をカウント */
  int time = 0;
  /* ゲーム開始時のスプライト表示を行う */
  GameStart();
  /* 画面と壁の情報を初期化する */
  Initialize();
  /* ゲームオーバーでなければ続ける処理 */
  while (!gameover) {
    /* キー入力があればそれに応じて操作 */
    if (kbhit()) {
      ControlBlock();
    }
    /* ブロックの落下と時間の処理 */
    if (time < GetTimeOfLevel(level)) {
      time += toffset + 1; /* 時間経過 */
      toffset = 0;
    } else {
      DropBlock(); /* ブロックを落下させる */
      time = 0;
    }
  }
  /* キーボードの入力設定を元に戻す */
  system("stty echo icanon min 1 time 0");
  return 0;
}
/*
 *  引数:なし 返り値:なし
 *　画面と壁のデータを初期化する
 *  Initialize()
 */
void Initialize() {
  int i, j; /* forループ制御用変数 */
  /* ループでマスを指定し、ステージの枠に該当するマスなら
     ブロックの情報を壁に初期化する。それ以外は空白にする。
     ループはi行j列のマスを指定するために回している。*/
  for (i = 0; i <= 20; i++) {
    for (j = 0; j <= 11; j++) {
      if ((j == 0) || (j == 11) || (i == 20)) {
	field[i][j] = stage[i][j] = 9;
      } else {
	field[i][j] = stage[i][j] = 0;
      }
    }
  }
  /* 疑似乱数から次のブロック生成の種類を決定する */
  srand((unsigned) time(NULL ));
  nextblock = rand() % 7;
  /* 次のブロックを生成し、次のブロックに入れる */
  CreateBlock();
  /* 二次元配列fieldから画面を構成する */
  ShowGameField();
}
/*
 *  次のブロックを生成し、次のブロックに入れる
 *  CreateBlock()
 *  帰り値: ゲームオーバーの判定なら1, そうでなければ0
 */
int CreateBlock() {
  int i, j; /* forループ制御用の変数 */
  /* ブロックの座標を初期位置にリセット */
  y = 0;
  x = 4;
  /* 生成されたブロック番号を次のブロックのステータスにいれる */
  block_type = nextblock;
  //srand((unsigned)time(NULL));
  nextblock = rand() % 7;
  /* 新しいブロックを生成する */
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      block[i][j] = 0;
      block[i][j] = block_list[block_type][i][j];
    }
  }
  /* stage[i][j+4]とblock[i][j]を足しfield[i][j+4]に代入 */
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      field[i][j + 4] = stage[i][j + 4] + block[i][j];
      /* 画面の上限を超えたらゲームオーバーの判定 */
      if (field[i][j + 4] > 1) {
	gameover = 1;
	return 1;
      }
    }
  }
  return 0;
}
/*
 *  2次元配列fieldから画面を描画する
 *  ShowGameField()
 */
void ShowGameField() {
  int i, j; /* forループ制御用変数 */
  /* 画面を一旦クリア */
  system("clear");
  /* fieldの情報からゲームフィールドを出力する */
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
  /* 消した行の数ごとのカウントを表示する */
  printf("\n１行消し：%d回 ２行消し：%d回 ３行消し：%d回 ４行消し：%d回\n", oneline, twoline,threeline, fourline);
  /* ゲームが終了したら、消した行ごとの回数とレベル、スコアを出力する */
  if (gameover) {
    system("clear");
    printf("\nYour Lines:\n１行消し：%d回 ２行消し：%d回 ３行消し：%d回 ４行消し：%d回\nYour Level: %d\nYour Scoure: %12d\n\nGAME OVER\n\n", oneline, twoline, threeline, fourline, level, point);
  }
}
/*
 * キー入力からブロックの移動、回転などの処理をする
 * ControlBlock()
 */
void ControlBlock() {
  char key; /* 入力キーの情報を格納する文字型変数 */
  /* 標準入力からキーコントロールを受け取りkeyに格納 */
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
  /* ブロックがステージのブロック、壁に重なっていたら1を返す */
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
 * 操作中のブロックを消去し、指定の座標に移動させる
 * MoveBlock()
 * 引数: ブロックを格納している配列の左上を操作された方向に移動した先のx座標(x2)
 * 　　と、格納する配列の左上のy座標(y2)
 */
void MoveBlock(int x2, int y2) {
  int i, j; /* forループ制御用変数 */
  /* 落下中のブロックをフィールドから消去する */
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      field[y + i][x + j] -= block[i][j];
    }
  }
  /* 操作しているブロックの移動先の座標を代入する */
  x = x2;
  y = y2;
  /* field配列のブロック情報を書き換え移動させる */
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      field[y + i][x + j] += block[i][j];
    }
  }
  /* フィールドに出力する */
  ShowGameField();
}
/*
 * ブロックを右に回転する
 * TurnRightBlock()
 * 戻り値: 壁蹴りできたなら0,壁蹴りできなかったら1を返す.
 * ブロック右回転の重なりチェックはこの中で行っている .
 * 壁蹴り1マス分実装（但し、テトリス棒は除く.
 */
int TurnRightBlock() {
  int i, j; /* forループ制御用 */
  int tmp[4][4]; /* 回転前のブロック情報を格納しておく */
  int offset = 0;
  /* 回転前のブロック情報をtmpに格納する */
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      tmp[i][j] = block[i][j];
    }
  }
  /* ブロックを反転し右か移転処理を行う */
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      block[i][j] = tmp[3 - j][i];
    }
  }
  /* ステージ内の他ブロックや壁に操作ブロックが重なった場合の処理 */
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
  /* 壁蹴りしたためフィールドから回転前のブロックを消去する */
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      field[y + i][x + j] -= tmp[i][j];
    }
  }
  /* 壁蹴り分の移動 */
  x = x + offset;
  /* フィールドに壁蹴り後のブロックを格納する */
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      field[y + i][x + j] += block[i][j];
    }
  }
  /* 壁蹴り処理を行ったフィールドを出力する */
  ShowGameField();
  return 0;
}
/*
 * ブロックの向きを左に回転させる
 * TurnLeftBlock()
 * 戻り値: [ここにコメントを記入]
 * ブロック左回転の重なりチェックはこの中で行っている.
 * 壁蹴り1マス分実装（但し、テトリス棒は除く.
 */
int TurnLeftBlock() {
  int i, j; /* forループ制御用 */
  int tmp[4][4]; /* ブロックの情報を保持する4x4の2次元配列 */
  int offset = 0;
  /* 2次元配列tmpにブロックの情報をコピーする */
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      tmp[i][j] = block[i][j];
    }
  }
  /* tmpを転置して縦軸を反転させたものをblockにコピーする。 */
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      block[i][j] = tmp[j][3 - i];
    }
  }
  /* ブロックが壁にはみ出ていた場合の処理 */
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
  /* フィールドから回転前のブロックを消去する */
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      field[y + i][x + j] -= tmp[i][j];
    }
  }
  /* 壁蹴り分の移動 */
  x = x + offset;
  /* フィールドに壁蹴り後のブロックを格納する */
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      field[y + i][x + j] += block[i][j];
    }
  }
  /* 壁蹴り後のフィールドを出力する */
  ShowGameField();
  return 0;
}
/*
 * ブロックを落下させる処理をする
 * DropBlock()
 */
void DropBlock() {
  /* 下にブロックがなければ下にブロックを移動させる */
  if (!CheckOverlap(x, y + 1)) {
    MoveBlock(x, y + 1);
  }
  /* 着地したならブロックを固定し次のブロックを生成、フィールドを出力する */
  else {
    LockBlock();
    CreateBlock();
    ShowGameField();
  }
}
/*
 * 着地したブロックをステージの固定ブロックに加える
 * LockBlock()
 */
void LockBlock() {
  int i, j; /* forループ制御用変数 */
  /* フィールドの状態をstageに格納する */
  for (i = 0; i < 21; i++) {
    for (j = 0; j < 12; j++) {
      stage[i][j] = field[i][j];
    }
  }
  /* 列が揃って処理するか確認し、消去できたら上列のブロックを落とす */
  CheckLines();
  /* fieldを更新する(消去した後の状態を代入) */
  for (i = 0; i < 21; i++) {
    for (j = 0; j < 12; j++) {
      field[i][j] = stage[i][j];
    }
  }
}
/*
 * 列を消せるかの判定と列を消す処理をする
 * CheckLines()
 */
void CheckLines() {
  int i, j, k; /* forループ制御用 */
  int comp; /* 横一列がそろっていれば１、一つでも隙間があると０になる */
  int lines = 0; /* 同時に消したラインの数 */
  while (1) {
    for (i = 0; i < 20; i++) {
      comp = 1;
      /* 空白マスであればcompを0にすることで
	 ステージ情報からi行j列が埋まっているかを判定する */
      for (j = 1; j < 11; j++) {
	if (stage[i][j] == 0) {
	  comp = 0;
	}
      }
      /* 列が揃い消えるならループを抜ける */
      if (comp == 1)
	break;
    }
    /* 隙間があり列が揃っていなかったらループを抜ける */
    if (comp == 0)
      break;
    /* 列が揃っているからlineのカウントを増やす */
    lines++;
    /* 揃った列を消す */
    for (j = 1; j < 11; j++) {
      stage[i][j] = 0;
    }
    /* 消えた列へ上の列を詰める */
    for (k = i; k > 0; k--) {
      for (j = 1; j < 11; j++) {
	stage[k][j] = stage[k - 1][j];
      }
    }
  }
  /* 消したラインの数で区分に従い消去ラインのカウンタを増やす */
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
  /* 消去ラインのカウンタからポイントを算出する */
  point = oneline * 100 + twoline * 400 + threeline * 900 + fourline * 1600;
  /* 算出したポイントからレベルを判定する */
  level = (int) (point / 2000.0) + 1;
  /* レベル判定が15以上になっても15を上限とする */
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
 * レベルごとにブロックの落下時間を返す
 * GetTimeOfLevel
 * 戻り値: ブロックの落下する速さ
 * 引数: プレイヤーレベル
 */
int GetTimeOfLevel(int level) {
  if (level >= 1 && level <= 15)
    return FPS * lvspeed[level - 1];
  else
    return 5 * FPS;
}
/*
 * ゲームスタート時のスプライト表示をする
 * GameStart()
 * 戻り値:なし
 * 引数:なし 
 */
void GameStart() {
  FILE* fp; /* ファイルポインタを宣言 */
  char string[60]; /* spriteから読み取り付け足す文字列を格納する配列 */
  char sprite[1000]; /* ファイルから読み込んだスプライトを格納する配列 */
  char ch; /* 入力されるキーを格納する文字型変数 */
  int ret;
  int flag = 1; /* ゲームセンターっぽく点滅させるためのフラグ管理 */
  int time = 9999; /* タイマー */
  /* ディレクトリ内に置いたsprite.txtを読み取りファイルとして開く */
  fp = fopen("sprite.txt", "r");

  /* sprite.txtから文字列情報を読み取り文字型配列spriteに格納 */
  fscanf(fp, "%s", sprite);
  while ((ret = fscanf(fp, "%s", string)) != EOF) {
    strcat(sprite, "\n");
    strcat(sprite, string); /* さらにスプライトから読み取った文字列を配列spriteに連結していく */
  }
  /* 開いたsprite.txtのファイルポインタをfcloseする */
  fclose(fp);
  /* スプライト表示 */
  while (1) {
    /* タイマーがカンストするたびに更新  */
    if (time > 80 * FPS) {
      /* 一度消去 */
      system("clear");
      /* スプライトを出力する */
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
      if (ch == 'q') { /* qが押された場合の処理(終了) */
	gameover = 1;
	break;
      } else if (ch == ' ') { /* スペースが入力された時の処理(ゲーム開始) */
	break;
      }
    }
    /* タイマーを更新 */
    time++;
  }
  /* 返り値はない */
  return;
}
