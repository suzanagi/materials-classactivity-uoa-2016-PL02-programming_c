
/* [各ファイルの上部にはこんな感じでコメントと日付を書いてください]
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
int stage[21][12]; /* [ステージの範囲] */
int block[4][4];   /* [ブロックの大きさの範囲] */
int field[21][12]; /* [プレイ画面の範囲] */
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
int nextblock = 0; /* [のブロックの種類用。0~6の乱数を入れる] */
int block_type;    /* ブロックの種類用。0~6の乱数を入れる */
int level = 1;     /* [レベルを1で初期化] */
int point = 0;     /* [合計ポイントを0で初期化] */
int toffset = 0;   /* 最下段までブロックが行った時に下ボタンを押した時に加算されるタイマー */
/* 関数プロトタイプ宣言 */
void Initialize();          /* ゲーム起動直後の初期設定を行う関数。画面と壁のデータを初期化 */
int CreateBlock(); /* [新しいブロックを生成して次のブロックに発生させる] */
void ShowGameField(); /* [field[][]の中身に応じて、画面を描画する] */
void ControlBlock(); /* [キー入力に応じてブロックに移動や回転等の処理を行わせる] */
int CheckOverlap(int, int); /*[ 落下中のブロックが壁や固定済みブロックに接触していないか判別 ]*/
void MoveBlock(int, int); /*[ 落下中ブロックを一旦消して、任意の座標に移動させる] */
int TurnRightBlock(); /* [ブロックの右回転を処理する] */
int TurnLeftBlock(); /* [ブロックの左回転を処理する] */
void DropBlock(); /* [ブロックを落下させる。下に移動できない場合ブロックをその位置に固定] */
void LockBlock(); /* [着地したブロックを固定済みブロックに加える関数] */
void CheckLines(); /* [ブロックが横一列にそろえばそこを消去後、上のブロックをそこに下ろす] */
int kbhit(); /* [キーボードを1回ヒットしたかどうかの判定 ]*/
int GetTimeOfLevel(int); /* [レベル毎の時間設定] */
void GameStart();	/* [ゲームスタート時のスプライト表示 ]*/
/*
 * メイン関数
 */
int main() {
/* キーボードの入力を隠すための処理 */
system("stty echo -icanon min 1 time 0");
/* 時間をカウント */
int time = 0;
/* [ゲームスタート時のスプライト表示] */
GameStart();
/* [ゲーム起動直後の初期設定を行う関数。画面と壁のデータを初期化] */
Initialize();
/* [gameoverにならなかったら] */
while (!gameover) {
/* キー入力があればそれに応じて操作 */
if (kbhit()) {
ControlBlock();
}
/* [ブロック落下や時間の処理] */
if (time < GetTimeOfLevel(level)) {
time += toffset + 1; /* 時間経過 */
toffset = 0;
} else {
DropBlock(); /* [ブロックを落下] */
time = 0;
}
}
/* キーボードの入力設定を元に戻す */
system("stty echo icanon min 1 time 0");
return 0;
}
/*
 *  [ゲーム起動直後の初期設定を行う関数]
 *  Initialize()
 */
void Initialize() {
int i, j; /* forループ制御用変数 */
/* [壁を設定しステージをつくる] */
for (i = 0; i <= 20; i++) {
for (j = 0; j <= 11; j++) {
if ((j == 0) || (j == 11) || (i == 20)) {
field[i][j] = stage[i][j] = 9;
} else {
field[i][j] = stage[i][j] = 0;
}
}
}
/* [次のブロックを生成する種類を決める] */
srand((unsigned) time(NULL ));
nextblock = rand() % 7;
/* [新しいブロックを生成して次のブロックに発生] */
CreateBlock();
/* [field[][]の中身に応じて、画面を映し出す] */
ShowGameField();
}
/*
 *  [新しいブロックを生成して次のブロックに発生させる関数]
 *  CreateBlock()
 *  帰り値: [ゲームオーバーの場合 = 1,それ以外 = 0]
 */
int CreateBlock() {
int i, j; /* forループ制御用の変数 */
/* ブロックの座標を初期位置にリセット */
y = 0;
x = 4;
/* [nextblockをblock_typeに代入] */
block_type = nextblock;
//srand((unsigned)time(NULL));
nextblock = rand() % 7;
/* [新しいブロックを生成] */
for (i = 0; i < 4; i++) {
for (j = 0; j < 4; j++) {
block[i][j] = 0;
block[i][j] = block_list[block_type][i][j];
}
}
/* [stage[i][j + 4] + block[i][j]をfield[i][j + 4]に代入する処理] */
for (i = 0; i < 4; i++) {
for (j = 0; j < 4; j++) {
field[i][j + 4] = stage[i][j + 4] + block[i][j];
/*ゲームオーバーになるかの判断*/
if (field[i][j + 4] > 1) {
gameover = 1;
return 1;
}
}
}
return 0;
}
/*
 *  field[][]の中身に応じて、画面を描画する関数
 *  ShowGameField()
 */
void ShowGameField() {
int i, j; /* forループ制御用変数 */
/* 画面を一旦クリア */
system("clear");
/* [field[][]の中身に応じて、画面を映し出す] */
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
/* [□行消しの回数表示させる] */
printf("\n１行消し：%d回 ２行消し：%d回 ３行消し：%d回 ４行消し：%d回\n", oneline, twoline,threeline, fourline);
/* [ゲームオーバーになった場合 □行消し、レベル、スコアを表示させる] */
if (gameover) {
system("clear");
printf("\nYour Lines:\n１行消し：%d回 ２行消し：%d回 ３行消し：%d回 ４行消し：%d回\nYour Level: %d\nYour Scoure: %12d\n\nGAME OVER\n\n", oneline, twoline, threeline, fourline, level, point);
}
}
/*
* キー入力に応じてブロックに移動や回転等の処理を行わせる
 * ControlBlock()
 */
void ControlBlock() {
char key; /* [キー入力に対応する変数として宣言] */
/* [キー入力された文字を読み込む] */
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
/* [ブロックが壁等に被るかの判断] */
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
 * [ * 落下中ブロックを一旦消して、任意の座標に移動させる関数]
 * MoveBlock()
 * 引数: int x2[ブロックを格納している4x4の配列の左上のx座標]
 */
void MoveBlock(int x2, int y2) {
int i, j; /* forループ制御用変数 */
/* [落下中のブロックを一旦消す作業をする] */
for (i = 0; i < 4; i++) {
for (j = 0; j < 4; j++) {
field[y + i][x + j] -= block[i][j];
}
}
/* [座標を代入] */
x = x2;
y = y2;
/* [任意の座標に移動させる] */
for (i = 0; i < 4; i++) {
for (j = 0; j < 4; j++) {
field[y + i][x + j] += block[i][j];
}
}
/* field[][]の中身に応じて、画面を描画する */
ShowGameField();
}
/*
 * [ブロックの右回転を処理する関数]
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
/* [元のブロックの形を代入する] */
for (i = 0; i < 4; i++) {
for (j = 0; j < 4; j++) {
block[i][j] = tmp[3 - j][i];
}
}
/* [壁際での右回転の処理する] */
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
/* [回転前のブロックを消去] */
for (i = 0; i < 4; i++) {
for (j = 0; j < 4; j++) {
field[y + i][x + j] -= tmp[i][j];
}
}
/* 壁分の移動 */
x = x + offset;
/* [回転後のブロックを加る] */
for (i = 0; i < 4; i++) {
for (j = 0; j < 4; j++) {
field[y + i][x + j] += block[i][j];
}
}
/* field[][]の中身に応じて、画面を描画する */
ShowGameField();
return 0;
}
/*
 * [ブロックの左回転を処理する関数]
 * TurnLeftBlock()
 * 戻り値: [int]
 * ブロック左回転の重なりチェックはこの中で行っている.
 * 壁蹴り1マス分実装（但し、テトリス棒は除く.
 */
int TurnLeftBlock() {
int i, j; /* forループ制御用 */
int tmp[4][4]; /* [一時的に置いておく配列] */
int offset = 0;
/* [元のブロックの形を代入] */
for (i = 0; i < 4; i++) {
for (j = 0; j < 4; j++) {
tmp[i][j] = block[i][j];
}
}
/* [左回転したブロックを代入] */
for (i = 0; i < 4; i++) {
for (j = 0; j < 4; j++) {
block[i][j] = tmp[j][3 - i];
}
}
/* [壁際での左回転の処理] */
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
/* [回転前のブロックを消す] */
for (i = 0; i < 4; i++) {
for (j = 0; j < 4; j++) {
field[y + i][x + j] -= tmp[i][j];
}
}
/* 壁蹴り分の移動 */
x = x + offset;
/* [回転後のブロックを加える] */
for (i = 0; i < 4; i++) {
for (j = 0; j < 4; j++) {
field[y + i][x + j] += block[i][j];
}
}
/* [  /* field[][]の中身に応じて、画面を描画する ]*/
ShowGameField();
return 0;
}
/*
 * [ブロックを落下させる。下に移動できない場合ブロックをその位置に固定する関数]
 * DropBlock()
 */
void DropBlock() {
/* [落下中のブロックが壁や固定済みブロックに接触していない場合] */
if (!CheckOverlap(x, y + 1)) {
MoveBlock(x, y + 1);
}
/* [他のブロックと当たった場合] */
else {
LockBlock();
CreateBlock();
ShowGameField();
}
}
/*
 * [着地したブロックを固定済みブロックに加える関数]
 * LockBlock()
 */
void LockBlock() {
int i, j; /* forループ制御用変数 */
/* [着地したブロックを固定する] */
for (i = 0; i < 21; i++) {
for (j = 0; j < 12; j++) {
stage[i][j] = field[i][j];
}
}
/* [ブロックが横一列にそろえばそこを消去後、上のブロックをそこに下ろす] */
CheckLines();
/* [着地し消去後を代入] */
for (i = 0; i < 21; i++) {
for (j = 0; j < 12; j++) {
field[i][j] = stage[i][j];
}
}
}
/*
 * [ブロックが横一列にそろえばそこを消去後、上のブロックをそこに下ろす関数]
 * CheckLines()
 */
void CheckLines() {
int i, j, k; /* forループ制御用 */
int comp; /* 横一列がそろっていれば１、一つでも隙間があると０になる */
int lines = 0; /* 同時に消したラインの数 */
while (1) {
for (i = 0; i < 20; i++) {
comp = 1;
/* [横一列に隙間があるか判断] */
for (j = 1; j < 11; j++) {
if (stage[i][j] == 0) {
comp = 0;
}
}
/* [横一列に隙間があるか判断] */
if (comp == 1)
break;
}
/* [横一列に隙間があった場合] */
if (comp == 0)
break;
/* [横一列が揃っていた場合linesをインクリメント] */
lines++;
/* [横一列揃っていたところを消去する] */
for (j = 1; j < 11; j++) {
stage[i][j] = 0;
}
/* [上のブロックをそこに下におろす処理] */
for (k = i; k > 0; k--) {
for (j = 1; j < 11; j++) {
stage[k][j] = stage[k - 1][j];
}
}
}
/* [消したラインの数に応じて++する] */
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
/* [消したラインの数に応じたポイントの計算] */
point = oneline * 100 + twoline * 400 + threeline * 900 + fourline * 1600;
/* [ポイントに応じたレベルの設定] */
level = (int) (point / 2000.0) + 1;
/* [最高レベルを15に設定する] */
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
struct termios oldt, newt; /* termosで保持する構造体 */
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
 * [キーボードが押されたかどうかの判定を返す関数]
 * GetTimeOfLevel
 * 戻り値: [キーボードが押された場合 = 1, other = 0]
 * 引数: [int level]
 */
int GetTimeOfLevel(int level) {
if (level >= 1 && level <= 15)
return FPS * lvspeed[level - 1];
else
return 5 * FPS;
}
/*
 * [ゲームスタート時のスプライト表示の関数]
 * GameStart()
 */
void GameStart() {
FILE* fp; /* [ファイルポインタの宣言] */
char string[60]; /* [スプライト用の配列設定] */
char sprite[1000]; /* [スプライト用の配列設定] */
char ch; /* [入力されるキーの変数] */
int ret;
int flag = 1; /* ゲームセンターっぽく点滅させるためのフラグ管理 */
int time = 9999; /* タイマー */
/* [ファイルオープン] */
fp = fopen("sprite.txt", "r");
/* [spriteへファイルの書きだし] */
fscanf(fp, "%s", sprite);
while ((ret = fscanf(fp, "%s", string)) != EOF) {
strcat(sprite, "\n");
strcat(sprite, string); /* [文字列を連結する] */
}
/* [ファイルを閉じる] */
fclose(fp);
/* スプライト表示 */
while (1) {
/* タイマーがカンストするたびに更新  */
if (time > 80 * FPS) {
/* 一度消去 */
system("clear");
/* [spriteを表示] */
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
if (ch == 'q') { /* [qが入力されたら終了してgameoverに1代入される] */
gameover = 1;
break;
} else if (ch == ' ') { /* [スペースが入力された場合,ループを抜けゲームスタート] */
break;
}
}
/* [timeを++する] */
time++;
}
/* [returnをする] */
return;
}
