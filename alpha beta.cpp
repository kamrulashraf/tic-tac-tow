#include <bits/stdc++.h>
using namespace  std;

#define N 3000000
#define inf 2e9
#define rep(i,x,y)  for(int i = x ; i< y ; i++)
#define F(i,x)  for(int i = 0 ; i< x ; i++)
#define ff first
#define ss second
#define pii pair < int , int>
#define ll long long
#define ull unsigned ll
#define MP make_pair
#define PB push_back
#define sca(a) scanf("%d",&a)
#define scaa(a,b) scanf("%d%d",&a,&b)
#define scaaa(a,b,c) scanf("%d%d%d",&a,&b,&c)
const long long MOD[] = {1000000007LL, 2117566807LL};
const long long BASE[] = {1572872831LL, 1971536491LL};
int counter = 0;
class node
{
     public:
	 int r, c, val;
	 node(int a , int b, int cc){
        r = a;
        c = b;
        val = cc;
	 }

	 node(){
        r = 0;
        c = 0;
        val = 0;
	 }

};

class ticTactoe
{

    public:
	int board[3][3] , r , c;

    ticTactoe(){
        memset(board,-1,sizeof board);
        r = 3 , c = 3;
    }


    bool isBoardFull(){
       F(i,r) F(j,c) if(board[i][j]==-1) return false;
       return true;
    }

    int checkForWin(){
    	int winner = -1;
    	F(i,r) if(checkRowCol(board[i][0],board[i][1],board[i][2])) winner = board[i][0];
    	F(i,r) if(checkRowCol(board[0][i],board[1][i],board[2][i])) winner = board[0][i];
    	if(checkRowCol(board[0][0],board[1][1],board[2][2])) winner = board[0][0];
    	if(checkRowCol(board[0][2],board[1][1],board[2][0])) winner = board[1][1];
    	if(isBoardFull()) winner = 0;
    	return winner;

    }

    bool isValidCell(int r , int c){
    	if(r >=  0 && r < 3 && c >= 0 && c < 3) return true;
    	return false;
    }

    bool checkRowCol(int a , int b , int c){
    	 if(a == b && b == c && a != -1) return true;
    	 return false;
    }

    void printBoard(){
           for(int i = 0 ; i< r ; i++){
              if(i)
           	   printf("_____\n");


           	   for(int j = 0 ; j< c ; j++){
           	   	   if(j) printf("|");
           	   	   if(board[i][j] != -1) printf("%c",board[i][j]);
           	   	   else printf(" ");

           	   }

           	   printf("\n");
           }

           printf("\n\n");
    }




};



class player
{
	int val;
	string massage;
public:
    player(){
    	val = -1;
    	massage = "YOUR'S TURNS";
    }

    ticTactoe movePlayer(ticTactoe const realBoard){
          printf("%s\n",massage.c_str());
          ticTactoe ret = realBoard;
          int r , c;
          while(1){
             scaa(r,c);
             r--; c--;
             if(ret.isValidCell(r,c) == true){
                 ret.board[r][c] = '0';
                 break;
             }
          }

          return ret;

    }
};


node maxAlgo(ticTactoe a, int alpha , int beta);

node minAlgo(ticTactoe a, int alpha , int beta){


	ticTactoe ret = a , temp;
    node mmin;
    mmin.val = inf;


    if(a.checkForWin() == '0'){
        return node(0,0,-1);
    }
    if(a.checkForWin() == 'x'){
        return node(0,0,1);
    }
    if(a.checkForWin() == 0){
    	return node(0,0,0);
    }

    for(int i = 0 ; i< 3 ; i++){
    	for(int j = 0 ; j< 3 ; j++){

    		temp = ret;
    		if(a.board[i][j] == -1){
                temp.board[i][j] = '0';
                node save = maxAlgo(temp,alpha,beta);

                beta = min(save.val,beta);
                if(save.val < mmin.val){
                     mmin = save;
                     mmin.r = i;
                     mmin.c = j;
                }
                if( alpha >= beta){
                    counter++;
                    return mmin;
                }

    		}
    	}
    }

    return mmin;
}
node maxAlgo(ticTactoe a, int alpha , int beta){
   int copyAlpha = alpha , copyBeta = beta;
   ticTactoe ret = a , temp;
   node mmax;
   mmax.val = -inf;

//   cout << a.isBoardFull() << endl;

   if(a.checkForWin() == '0'){
        return node(0,0,-1);
    }
    if(a.checkForWin() == 'x'){
        return node(0,0,1);
    }
    if(a.checkForWin() == 0){
        return node(0,0,0);
    }



   for(int i = 0 ; i< 3 ; i++){
           for(int j = 0 ; j< 3 ; j++){
               if(ret.board[i][j] == -1){
               	  temp = ret;
               	  temp.board[i][j] = 'x';

                  node save = minAlgo(temp,alpha,beta);


               	  if(save.val > mmax.val){

               	  	 mmax = save;
               	  	 mmax.r = i;
               	  	 mmax.c = j;
               	  }

                  alpha = max(alpha,mmax.val);
               	  if(alpha >= beta){
               	     counter++;
                     return mmax;
               	  }

               }
           }
   }

   return mmax;
}

class computer
{
	 int val;
	 string massage;
	public:
	 computer(){
	 	val = 1;
	 	massage = "COMPUTER TURNS";
	 }

	 ticTactoe moveComputer(ticTactoe realBoard){
	    printf("%s\n",massage.c_str());
	 	ticTactoe ret = realBoard;
	 	int alpha = -inf;
	 	int beta = inf;
	 	node save = maxAlgo(realBoard, alpha, beta);
	 	ret.board[save.r][save.c] = 'x';

	 	return ret;
     }
};


int main()
{
    ticTactoe realBoard;
    realBoard.printBoard();
    player p;
    computer com;

    int toss = rand()%2;


    int turn = 0;
    while(realBoard.isBoardFull() == false){

        turn = (turn&1);
        if(turn == toss){
        	realBoard=p.movePlayer(realBoard);
        }
        else{
            realBoard=com.moveComputer(realBoard);
        }
        realBoard.printBoard();
        int save = realBoard.checkForWin();
        if(save == 'x'){
           printf("COMPUTER WIN\n");
           break;
        }
        else if(save == '0'){
           printf("YOU WIN\n");
           break;
        }
        turn++;
    }
    if(realBoard.checkForWin() == 0){
        printf("DRAW\n");
    }

    cout << counter << endl;



}
