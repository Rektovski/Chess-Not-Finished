// Chess - By Otar Murmanishvili
#include <bits/stdc++.h>
using namespace std;

string X[10][10];
short arr[10];
short movement[10]; // Check Line 11
short PawnLegendary[10]; // We use it to say that pawn made from 1-8 or otherwise.
short checkRunAttackDefendDefendbyalliance[10]; // Check line 22
/*
 * movement Array is to save which kind of errors do we have into movement rules
 * movement[0] - Player tried to kill king. None of figures can kill king instantly. It can be only Checked and Mated, both together.
 * movement[1] - King can't move. We use this in check mate checking...
 * movement[2] - King can't move from A to B because road is blocked...
 * movement[3] - Knight can't move from A to B...
 * movement[4] - Rock can't move from A to B...
 * movement[5] - Bishop can't move from A to B...
 * movement[6] - Pawn can't move from A to B...
 * movement[7] - Queen can't move from A to B...
 *
 *
 * checkRunAttackDefendDefendbyalliance[0] - We have Check!
 * checkRunAttackDefendDefendbyalliance[2] - Attack as check can't be denied by alliance. We can't kill attacker and we can't block his/her way to the king!(checks attack versions on Rock, Bishop, Queen.)
 * checkRunAttackDefendDefendbyalliance[3] - Figure which checked king is reinforced by alliance, so if something king can't kill him alone!
 *
 * arr[0]-arr[5]  Simple errors. Error0-Error5
 * movement[1] - Error 6 king can't move
 *
 * */

short XY=0;

// T is const variable for main While cycle. While it is true game is on. Otherwise game over.
bool T=true;
// We use this in checkIfKingControls function to count how many space does king control:
short G=0;
// Queen movement Error checker global variable
short Q=0;
// Mate
short Mate=0;
// Functions
// ************************************************************
void makeBoard();
void makeFigures();
void fillFreeSpace();
void helloAndTutorial();
void printBoard();
void makePostProcess();

short checkErrors(string F,string A,string B,short a,short b,short c,short d);
void error0(string F,short c,short d);
void error1(string F);
void error2(string F,string A,string B);
void error3(short a,short b,short c,short d);
void error4(string F,string A,short a,short b);
void error5(string F,string A,short a,short b);
short error6(string F,string A,string B,short a,short b,short c,short d);
short error7(string F,string A,string B,short a,short b,short c,short d);
void clearBoardFromXXKKXY();
void kingControls(string F,short a,short b);
void checkIfKingControls(short a,short b);
void targetingByBlackKing();
void targetingByBlackKnight();
void targetingByBlackRock();
void targetingByBlackBishop();
void targetingByBlackQueen();
void targetingByBlackPawn();
void targetingByWhiteKing();
void targetingByWhiteKnight();
void targetingByWhiteRock();
void targetingByWhiteBishop();
void targetingByWhiteQueen();
void targetingByWhitePawn();
void knightControls(string F,short a,short b,short c,short d);
void rockControls(string F,short a,short b,short c,short d);
void bishopControl(string F,short a,short b,short c,short d);
void queenControls(string F,short a,short b,short c,short d);
void pawnControls(string F,short a,short b,short c,short d);

// check and mate checking functions:
short makeCheck(string F,string A,string B,short a,short b,short c,short d);
void knightCheckKing(string F,string A,string B,short a,short b,short c,short d);
void rockCheckKing(string F,string A,string B,short a,short b,short c,short d);
void bishopCheckKing(string F,string A,string B,short a,short b,short c,short d);
void queenCheckKing(string F,string A,string B,short a,short b,short c,short d);
void pawnCheckKing(string F,string A,string B,short a,short b,short c,short d);
void makeDefend(string F,string A,string B,short a,short b,short c,short d);
void attackerIsReinforced(string F,string A,string B,short a,short b,short c,short d);
void attackerIsNotReinforcedButHeIsToFarToKill(string F,string A,string B,short a,short b,short c,short d);
// last function

// ************************************************************
// Functions

int main(){
    makePostProcess();
    short check=1,count=1;
    string F,A,B;
    short a,b,c,d;
    while(T){
        printBoard();
        if(check==1)cout<<count<<". White's Turn: \n",check=2;
        else cout<<count++<<". Black's Turn: \n",check=1;
        cin>>F;
        if(F=="exit"){cout<<"Thank you for playing our game. Have a nice day!\n";T=false;break;}
        else if(check==1 && F[0]!='B'){cout<<"It was White's turn!\n";T=false;break;}
        else if(check==2 && F[0]!='W'){cout<<"It was Black's turn!\n";T=false;break;}
        cin>>A>>B;
        a=9-(A[1]-'0'),b=A[0]-'a'+1,c=9-(B[1]-'0'),d=B[0]-'a'+1;
        // Checking All kind of errors before next step
        checkErrors(F,A,B,a,b,c,d);
        for(short i=0;i<10;++i)if(arr[i] || movement[i]){T=false;break;}
        if(Mate){cout<<"Check and Mate!\nGame Over!";T=false;break;}
        for(short i=0;i<10;++i)arr[i]=movement[i]=PawnLegendary[i]=checkRunAttackDefendDefendbyalliance[i]=0;
        if(F=="WP" && PawnLegendary[0]){
            PawnLegendary[0]=0;X[a][b]="--";
            cout<<"Choose new figure: R, N, B, Q\n";
            cin>>F;
            if(F=="R")X[c][d]="WR";
            else if(F=="N")X[c][d]="WN";
            else if(F=="B")X[c][d]="WB";
            else if(F=="Q")X[c][d]="WQ";
            else {cout<<"You chose wrong figure!\n";break;}
        }
        else if(F=="BP" && PawnLegendary[1]){
            PawnLegendary[1]=0;X[a][b]="--";
            cout<<"Choose new figure: R, N, B, Q\n";
            cin>>F;
            if(F=="R")X[c][d]="BR";
            else if(F=="N")X[c][d]="BN";
            else if(F=="B")X[c][d]="BB";
            else if(F=="Q")X[c][d]="BQ";
            else {cout<<"You chose wrong figure!\n";break;}
        }
        else X[c][d]=X[a][b],X[a][b]="--";
    }
}

// Functions
// ************************************************************
void makeBoard(){
    short i;
    for(i=0;i<=9;++i)X[0][i]=X[9][i]="00";
    for(i=1;i<=8;++i)X[i][0]=X[i][9]="00";
}
void makeFigures(){
    short i,j;
    for(i=2,j=1;j<=8;++j)X[i][j]="BP";
    for(i=7,j=1;j<=8;++j)X[i][j]="WP";
    X[8][1]=X[8][8]="WR";
    X[1][1]=X[1][8]="BR";
    X[8][2]=X[8][7]="WN";
    X[1][2]=X[1][7]="BN";
    X[8][3]=X[8][6]="WB";
    X[1][3]=X[1][6]="BB";
    X[8][4]="WQ",X[1][4]="BQ";
    X[8][5]="WK",X[1][5]="BK";
}
void fillFreeSpace(){
    short i,j;
    for(i=0;i<=9;++i){
        for(j=0;j<=9;++j){
            if(X[i][j]=="")X[i][j]="--";
        }
        cout<<endl;
    }
}
void printBoard(){
    cout<<"***********************\n";
    short i,j;
    for(i=1;i<=8;++i){
        for(j=1;j<=8;++j){
            cout<<X[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"***********************\n";
}
void helloAndTutorial(){
    cout<<"Hello, World.\n"
          "This's the most popular Indian game - Chess :)\n"
          "Let's start the game!\n\n"
          ""<<"Here is a little tutorial:\n\n"
              ""<<"Use user input service as \"WP e2 e4\".\n\n"
                  ""<<"First figure name (for example: W or B), then movement from "
                      "A coordinate to B coordinate (e2 e4)\n\n";
    cout<<"Now you will see figure names. Use them to choose figures:\n";
    cout<<"{\"WP\",\"WR\",\"WN\",\"WB\",\"WQ\",\"WK == ♔\"}\n"
          "{\"BP\",\"BR\",\"BN\",\"BB\",\"BQ\",\"BK\"}\n\n";
    cout<<"Now you will see coordinates. Use double combination of them to choose the coordinates:\n";
    cout<<"\"a1\",\"a2\",\"a3\",\"a4\",\"a5\",\"a6\",\"a7\",\"a8\",\n"
          "\"b1\",\"b2\",\"b3\",\"b4\",\"b5\",\"b6\",\"b7\",\"b8\",\n"
          "\"c1\",\"c2\",\"c3\",\"c4\",\"c5\",\"c6\",\"c7\",\"c8\",\n"
          "\"d1\",\"d2\",\"d3\",\"d4\",\"d5\",\"d6\",\"d7\",\"d8\",\n"
          "\"e1\",\"e2\",\"e3\",\"e4\",\"e5\",\"e6\",\"e7\",\"e8\",\n"
          "\"f1\",\"f2\",\"f3\",\"f4\",\"f5\",\"f6\",\"f7\",\"f8\",\n"
          "\"g1\",\"g2\",\"g3\",\"g4\",\"g5\",\"g6\",\"g7\",\"g8\",\n"
          "\"h1\",\"h2\",\"h3\",\"h4\",\"h5\",\"h6\",\"h7\",\"h8\"\n\n";
    cout<<"Good luck! :)\n\n";
}
void makePostProcess(){
    makeBoard();
    makeFigures();
    fillFreeSpace();
    helloAndTutorial();
}

// error Functions
// ************************************************************

void error0(string F,short c,short d){
    string s=X[c][d];
    if(F[0]==s[0])arr[0]=1,cout<<"Error 0. Same color figures can't attack each other! Next time choose from W to B or from B to W.\n";
}
void error1(string F){
    if(F[0]!='W' && F[0]!='B')arr[1]=1,cout<<"Error 1. There is no kind of color like that in game. Next time choose W as White or B as Black\n";
}
void error2(string F,string A,string B){
    if(F=="WK")cout<<"White King moves from "<<A<<" to "<<B<<endl;
    else if(F=="BK")cout<<"Black King moves from "<<A<<" to "<<B<<endl;
    else if(F=="WR")cout<<"White Rock moves from "<<A<<" to "<<B<<endl;
    else if(F=="BR")cout<<"Black Rock moves from "<<A<<" to "<<B<<endl;
    else if(F=="WN")cout<<"White Knight moves from "<<A<<" to "<<B<<endl;
    else if(F=="BN")cout<<"Black Knight moves from "<<A<<" to "<<B<<endl;
    else if(F=="WB")cout<<"White Bishop moves from "<<A<<" to "<<B<<endl;
    else if(F=="BB")cout<<"Black Bishop moves from "<<A<<" to "<<B<<endl;
    else if(F=="WQ")cout<<"White Queen moves from "<<A<<" to "<<B<<endl;
    else if(F=="BQ")cout<<"Black Queen moves from "<<A<<" to "<<B<<endl;
    else if(F=="WP")cout<<"White Pawn moves from "<<A<<" to "<<B<<endl;
    else if(F=="BP")cout<<"Black Pawn moves from "<<A<<" to "<<B<<endl;
    else arr[2]=1,cout<<"Error 2. There is no kind of figure like that in game. Read Tutorial!...\n";
}
void error3(short a,short b,short c,short d){
    if(a<1 || a>8 || b<1 || b>8 || c<1 || c>8 || d<1 || d>8)arr[3]=1,cout<<"Error 3. There is no such kind of coordinate on the board. Read the tutorial again!.";
}
void error4(string F,string A,short a,short b){
    if(X[a][b]=="--")arr[4]=1,cout<<"Error 4. Coordinate "<<A<<" you chose is empty!\n";
}
void error5(string F,string A,short a,short b){
    if(X[a][b]!=F)arr[5]=1,cout<<"Error 5. There is no figure like that on coordinate "<<A<<". Read the tutorial!\n";
}
short error6(string F,string A,string B,short a,short b,short c,short d){
    // Defensive Line for kings. None of figures can kill king instantly!!!
    if(X[c][d]=="WK" || X[c][d]=="BK"){movement[0]=1;return 0;}
    if(F=="WK"){
        kingControls(F,a,b);
        if(X[c][d]!="KK"){movement[2]=1,cout<<"White king can't go there, as he cant run so much!\n";clearBoardFromXXKKXY();return 0;}
        clearBoardFromXXKKXY();
        kingControls(F,a,b);
        targetingByBlackRock();
        targetingByBlackKnight();
        targetingByBlackBishop();
        targetingByBlackQueen();
        targetingByBlackKing();
        targetingByBlackPawn();
        checkIfKingControls(a,b);
        if(!G)movement[1]=1,cout<<"White king can't go there, because that area is under control of Black's Figure(s).\n";
        else G=0;
        clearBoardFromXXKKXY();

    }
    else if(F=="BK"){
        kingControls(F,a,b);
        targetingByWhiteRock();
        targetingByWhiteKnight();
        targetingByWhiteBishop();
        targetingByWhiteQueen();
        targetingByWhiteKing();
        targetingByWhitePawn();
        checkIfKingControls(a,b);
        if(!G)movement[1]=1,cout<<"Black king can't go there, because that area is under control of White's Figure(s).\n";
        else G=0;
        clearBoardFromXXKKXY();
        kingControls(F,a,b);
        if(X[c][d]!="KK")movement[2]=1,cout<<"Black king can't go there, as he cant run so much!\n";
        clearBoardFromXXKKXY();
    }
    // figures can't go there as it is far for them.
    else if(F=="WN" || F=="BN")knightControls(F,a,b,c,d);
    else if(F=="WR" || F=="BR")rockControls(F,a,b,c,d);
    else if(F=="WB" || F=="BB")bishopControl(F,a,b,c,d);
    else if(F=="WQ" || F=="BQ")queenControls(F,a,b,c,d);
    else pawnControls(F,a,b,c,d);
}
short error7(string F,string A,string B,short a,short b,short c,short d){
    makeCheck(F,A,B,a,b,c,d); //  qishi
    // can't Run function is already written as movement[1]==1 array; // gasaqcevi ar maqvs
    // dagrcha mefis mcdeloba rom tviton moklas magram mosaklavs rom vinme icavdes.
    if(checkRunAttackDefendDefendbyalliance[0]==1){
        makeDefend(F,A,B,a,b,c,d); // checkRunAttackDefendDefendbyalliance[2]==1
        attackerIsReinforced(F,A,B,a,b,c,d); // checkRunAttackDefendDefendbyalliance[3]==1
        attackerIsNotReinforcedButHeIsToFarToKill(F,A,B,a,b,c,d); // king could kill him if he/she was in king's attack zone but...

    }
}

// ************************************************************
// error Functions

short checkErrors(string F,string A,string B,short a,short b,short c,short d){
    error0(F,c,d); // Error 0 - Same color figures attacks each other.
    error1(F); // Error 1 - Color
    error2(F,A,B); // Error 2 - Figure's name
    error3(a,b,c,d); // Error 3 - Coordinate Error
    error4(F,A,a,b); // Error 4 - Empty starting coordinate
    error5(F,A,a,b); //  Error 5 - starting figure
    error6(F,A,B,a,b,c,d); // Error 6 - Movement Rule
    error7(F,A,B,a,b,c,d); //  Error 7 - Check and Mate
}

// for checking error6 we have here this functions:

// this functions check all other figures movements + killable zones availability
void knightControls(string F,short a,short b,short c,short d){
    // Knight can't move from A to B as it is too far for him
    if(!(a-2==c && b-1==d ||
          a-2==c && b+1==d ||
          a-1==c && b+2==d ||
          a+1==c && b+2==d ||
          a+2==c && b-1==d ||
          a+2==c && b+1==d ||
          a+1==c && b-2==d ||
          a-1==c && b-2==d  ))movement[3]=1,cout<<"Knight can't move from A to B as it is too far for it!\n";
}
void rockControls(string F,short a,short b,short c,short d){
    short i;
    for(i=a+1;X[i][b]!="00";++i){
        if(X[i][b]=="--")X[i][b]="XX";
        else break;
    }
    for(i=a-1;X[i][b]!="00";--i){
        if(X[i][b]=="--")X[i][b]="XX";
        else break;
    }
    for(i=b+1;X[a][i]!="00";++i){
        if(X[a][i]=="--")X[a][i]="XX";
        else break;
    }
    for(i=b-1;X[a][i]!="00";--i){
        if(X[a][i]=="--")X[a][i]="XX";
        else break;
    }
    if(!!(X[c+1][d]=="XX" || X[c-1][d]=="XX" || X[c][d+1]=="XX" || X[c][d-1]=="XX"))movement[4]=1,cout<<"Rock can't move from A to B!\n";
    clearBoardFromXXKKXY();
}
void bishopControl(string F,short a,short b,short c,short d){
    short i,j;
    for(i=a+1,j=b+1;X[i][j]!="00";++a,++b){
        if(X[i][j]=="--")X[i][j]="XX";
        else break;
    }
    for(i=a-1,j=b+1;X[i][j]!="00";--a,++b){
        if(X[i][j]=="--")X[i][j]="XX";
        else break;
    }
    for(i=a+1,j=b-1;X[i][j]!="00";++a,--b){
        if(X[i][j]=="--")X[i][j]="XX";
        else break;
    }
    for(i=a-1,j=b-1;X[i][j]!="00";--a,--b){
        if(X[i][j]=="--")X[i][j]="XX";
        else break;
    }
    if(!!(X[c+1][d+1]=="XX" || X[c+1][d-1]=="XX" || X[c-1][d+1]=="XX" || X[c-1][d-1]=="XX"))movement[5]=1,cout<<"Bishop can't move from A to B!\n";
    clearBoardFromXXKKXY();
}
void queenControls(string F,short a,short b,short c,short d){
    short i,j;
    for(i=a+1;X[i][b]!="00";++i){
        if(X[i][b]=="--")X[i][b]="XX";
        else break;
    }
    for(i=a-1;X[i][b]!="00";--i){
        if(X[i][b]=="--")X[i][b]="XX";
        else break;
    }
    for(i=b+1;X[a][i]!="00";++i){
        if(X[a][i]=="--")X[a][i]="XX";
        else break;
    }
    for(i=b-1;X[a][i]!="00";--i){
        if(X[a][i]=="--")X[a][i]="XX";
        else break;
    }
    for(i=a+1,j=b+1;X[i][j]!="00";++a,++b){
        if(X[i][j]=="--")X[i][j]="XX";
        else break;
    }
    for(i=a-1,j=b+1;X[i][j]!="00";--a,++b){
        if(X[i][j]=="--")X[i][j]="XX";
        else break;
    }
    for(i=a+1,j=b-1;X[i][j]!="00";++a,--b){
        if(X[i][j]=="--")X[i][j]="XX";
        else break;
    }
    for(i=a-1,j=b-1;X[i][j]!="00";--a,--b){
        if(X[i][j]=="--")X[i][j]="XX";
        else break;
    }
    if(X[c][d]!="XX")movement[7]=1,cout<<"Queen can't go there!\n";
    clearBoardFromXXKKXY();
}
void pawnControls(string F,short a,short b,short c,short d){
    if(F=="WP"){
        if(a-1!=c && b-1!=d && a-1!=c && b+1!=d && (X[a-1][b]=="--" && a-1!=c && b-1!=d) && (X[a-2][b]=="--" && a-2!=c && b!=d))movement[6]=1,cout<<"Pawn can't move from A to B!\n";
        if(a==7 && c<5 && b==d)movement[6]=1,cout<<"Pawn can't move from A to B!\n";
        if(b!=d-1 && b!=d && b!=d+1)movement[6]=1,cout<<"Pawn can't move from A to B!\n";
        if(c==1)PawnLegendary[0]=1;
        if(a==5 && c==5 && X[a][b-1]=="BP" && c==a-1 && d==b-1)X[a][b-1]="--";
        else if(a==5 && c==5 && X[a][b+1]=="BP" && c==a-1 && d==b+1)X[a][b+1]="--";
        else if(a==5 && c==4 && X[a][b+1]=="BP" && c==a-1 && d==b+1)X[a][b+1]="--";
        else if(a==5 && c==6 && X[a][b-1]=="BP" && c==a-1 && d==b-1)X[a][b-1]="--";
        else if(a==5 && c==6 && X[a][b+1]=="BP" && c==a-1 && d==b+1)X[a][b+1]="--";
        else if(a==5 && c==7 && X[a][b-1]=="BP" && c==a-1 && d==b-1)X[a][b-1]="--";
    }
    else if(F=="BP"){
        if(a+1!=c && b+1!=d && a+1!=c && b-1!=d && (X[a+1][b]=="--" && a+1!=c && b+1!=d) && (X[a+2][b]=="--" && a+2!=c && b!=d))movement[6]=1,cout<<"Pawn can't move from A to B!\n";
        if(a==2 && c>4 && b==d)movement[6]=1,cout<<"Pawn can't move from A to B!\n";
        if(b!=d-1 && b!=d && b!=d+1)movement[6]=1,cout<<"Pawn can't move from A to B!\n";
        if(c==8)PawnLegendary[1]=1;
        if(a==4 && c==5 && X[a][b-1]=="BP" && c==a+1 && d==b-1)X[a][b-1]="--";
        else if(a==4 && c==5 && X[a][b+1]=="BP" && c==a+1 && d==b+1)X[a][b+1]="--";
        else if(a==4 && c==4 && X[a][b+1]=="BP" && c==a+1 && d==b+1)X[a][b+1]="--";
        else if(a==4 && c==6 && X[a][b-1]=="BP" && c==a+1 && d==b-1)X[a][b-1]="--";
        else if(a==4 && c==6 && X[a][b+1]=="BP" && c==a+1 && d==b+1)X[a][b+1]="--";
        else if(a==4 && c==7 && X[a][b-1]=="BP" && c==a+1 && d==b-1)X[a][b-1]="--";
    }
}

// this functions check king's movements availability
void clearBoardFromXXKKXY(){
    short i,j;
    for(i=1;i<=8;++i){
        for(j=1;j<=8;++j){
            if(X[i][j]=="XX" || X[i][j]=="KK" || X[i][j]=="XY")X[i][j]="--";
        }
    }
}
void kingControls(string F,short a,short b){
    if(X[a-1][b-1]=="--")X[a-1][b-1]="KK";
    if(X[a-1][ b ]=="--")X[a-1][ b ]="KK";
    if(X[a-1][b+1]=="--")X[a-1][b+1]="KK";
    if(X[ a ][b-1]=="--")X[ a ][b-1]="KK";
    if(X[ a ][b+1]=="--")X[ a ][b+1]="KK";
    if(X[a+1][b-1]=="--")X[a+1][b-1]="KK";
    if(X[a-1][ b ]=="--")X[a-1][ b ]="KK";
    if(X[a-1][b+1]=="--")X[a-1][b+1]="KK";
}
void checkIfKingControls(short a,short b){
    if(X[a-1][b-1]=="KK")++G;
    if(X[a-1][ b ]=="KK")++G;
    if(X[a-1][b+1]=="KK")++G;
    if(X[ a ][b-1]=="KK")++G;
    if(X[ a ][b+1]=="KK")++G;
    if(X[a+1][b-1]=="KK")++G;
    if(X[a-1][ b ]=="KK")++G;
    if(X[a-1][b+1]=="KK")++G;
}
void targetingByBlackRock(){
    short i,j;
    for(i=1;i<=8;++i){
        for(j=1;j<=8;++j){
            if(X[i][j]=="BR"){
                short a;
                for(a=i+1;X[a][j]!="00";++a){
                    if(X[a][j]=="--")X[a][j]="XX";
                    else break;
                }
                for(a=i-1;X[a][j]!="00";--a){
                    if(X[a][j]=="--")X[a][j]="XX";
                    else break;
                }
                for(a=j+1;X[i][a]!="00";++a){
                    if(X[i][a]=="--")X[i][a]="XX";
                    else break;
                }
                for(a=j-1;X[i][a]!="00";--a){
                    if(X[i][a]=="--")X[i][a]="XX";
                    else break;
                }
            }
        }
    }
}
void targetingByBlackKnight(){
    short i,j;
    for(i=1;i<=8;++i){
        for(j=1;j<=8;++j){
            if(X[i][j]=="BN"){
                if(X[i-2][j-1]=="--")X[i-2][j-1]="XX";
                if(X[i-2][j+1]=="--")X[i-2][j+1]="XX";
                if(X[i-1][j+2]=="--")X[i-1][j+2]="XX";
                if(X[i+1][j+2]=="--")X[i+1][j+2]="XX";
                if(X[i+2][j+1]=="--")X[i+2][j+1]="XX";
                if(X[i+2][j-1]=="--")X[i+2][j-1]="XX";
                if(X[i-1][j-2]=="--")X[i-1][j-2]="XX";
                if(X[i+1][j-2]=="--")X[i+1][j-2]="XX";
            }
        }
    }
}
void targetingByBlackBishop(){
    short i,j;
    for(i=1;i<=8;++i){
        for(j=1;j<=8;++j){
            if(X[i][j]=="BB"){
                short a,b;
                for(a=i+1,b=j+1;X[a][b]!="00";++a,++b){
                    if(X[a][b]=="--")X[a][b]="XX";
                    else break;
                }
                for(a=i-1,b=j+1;X[a][b]!="00";--a,++b){
                    if(X[a][b]=="--")X[a][b]="XX";
                    else break;
                }
                for(a=i+1,b=j-1;X[a][b]!="00";++a,--b){
                    if(X[a][b]=="--")X[a][b]="XX";
                    else break;
                }
                for(a=i-1,b=j-1;X[a][b]!="00";--a,--b){
                    if(X[a][b]=="--")X[a][b]="XX";
                    else break;
                }
            }
        }
    }
}
void targetingByBlackQueen(){
    short i,j;
    for(i=1;i<=8;++i){
        for(j=1;j<=8;++j){
            if(X[i][j]=="BQ"){
                short a,b;
                for(a=i+1;X[a][j]!="00";++a){
                    if(X[a][j]=="--")X[a][j]="XX";
                    else break;
                }
                for(a=i-1;X[a][j]!="00";--a){
                    if(X[a][j]=="--")X[a][j]="XX";
                    else break;
                }
                for(a=j+1;X[i][a]!="00";++a){
                    if(X[i][a]=="--")X[i][a]="XX";
                    else break;
                }
                for(a=j-1;X[i][a]!="00";--a){
                    if(X[i][a]=="--")X[i][a]="XX";
                    else break;
                }
                for(a=i+1,b=j+1;X[a][b]!="00";++a,++b){
                    if(X[a][b]=="--")X[a][b]="XX";
                    else break;
                }
                for(a=i-1,b=j+1;X[a][b]!="00";--a,++b){
                    if(X[a][b]=="--")X[a][b]="XX";
                    else break;
                }
                for(a=i+1,b=j-1;X[a][b]!="00";++a,--b){
                    if(X[a][b]=="--")X[a][b]="XX";
                    else break;
                }
                for(a=i-1,b=j-1;X[a][b]!="00";--a,--b){
                    if(X[a][b]=="--")X[a][b]="XX";
                    else break;
                }
            }
        }
    }
}
void targetingByBlackPawn(){
    short i,j;
    for(i=1;i<=8;++i){
        for(j=1;j<=8;++j){
            if(X[i][j]=="BP"){
                if(X[i+1][j-1]=="--")X[i+1][j-1]="XX";
                if(X[i+1][j+1]=="--")X[i+1][j+1]="XX";
            }
        }
    }
}
void targetingByBlackKing(){
    short i,j;
    for(i=1;i<=8;++i){
        for(j=1;j<=8;++j){
            if(X[i][j]=="BK"){
                if(X[i-1][j-1]=="--")X[i-1][j-1]="XX";
                if(X[i-1][ j ]=="--")X[i-1][ j ]="XX";
                if(X[i-1][j+1]=="--")X[i-1][j+1]="XX";
                if(X[ i ][j-1]=="--")X[ i ][j-1]="XX";
                if(X[ i ][j+1]=="--")X[ i ][j+1]="XX";
                if(X[i+1][j-1]=="--")X[i+1][j-1]="XX";
                if(X[i-1][ j ]=="--")X[i-1][ j ]="XX";
                if(X[i-1][j+1]=="--")X[i-1][j+1]="XX";
            }
        }
    }
}
void targetingByWhiteRock(){
    short i,j;
    for(i=1;i<=8;++i){
        for(j=1;j<=8;++j){
            if(X[i][j]=="WR"){
                short a;
                for(a=i+1;X[a][j]!="00";++a){
                    if(X[a][j]=="--")X[a][j]="XX";
                    else break;
                }
                for(a=i-1;X[a][j]!="00";--a){
                    if(X[a][j]=="--")X[a][j]="XX";
                    else break;
                }
                for(a=j+1;X[i][a]!="00";++a){
                    if(X[i][a]=="--")X[i][a]="XX";
                    else break;
                }
                for(a=j-1;X[i][a]!="00";--a){
                    if(X[i][a]=="--")X[i][a]="XX";
                    else break;
                }
            }
        }
    }
}
void targetingByWhiteKnight(){
    short i,j;
    for(i=1;i<=8;++i){
        for(j=1;j<=8;++j){
            if(X[i][j]=="WN"){
                if(X[i-2][j-1]=="--")X[i-2][j-1]="XX";
                if(X[i-2][j+1]=="--")X[i-2][j+1]="XX";
                if(X[i-1][j+2]=="--")X[i-1][j+2]="XX";
                if(X[i+1][j+2]=="--")X[i+1][j+2]="XX";
                if(X[i+2][j+1]=="--")X[i+2][j+1]="XX";
                if(X[i+2][j-1]=="--")X[i+2][j-1]="XX";
                if(X[i-1][j-2]=="--")X[i-1][j-2]="XX";
                if(X[i+1][j-2]=="--")X[i+1][j-2]="XX";
            }
        }
    }
}
void targetingByWhiteBishop(){
    short i,j;
    for(i=1;i<=8;++i){
        for(j=1;j<=8;++j){
            if(X[i][j]=="WB"){
                short a,b;
                for(a=i+1,b=j+1;X[a][b]!="00";++a,++b){
                    if(X[a][b]=="--")X[a][b]="XX";
                    else break;
                }
                for(a=i-1,b=j+1;X[a][b]!="00";--a,++b){
                    if(X[a][b]=="--")X[a][b]="XX";
                    else break;
                }
                for(a=i+1,b=j-1;X[a][b]!="00";++a,--b){
                    if(X[a][b]=="--")X[a][b]="XX";
                    else break;
                }
                for(a=i-1,b=j-1;X[a][b]!="00";--a,--b){
                    if(X[a][b]=="--")X[a][b]="XX";
                    else break;
                }
            }
        }
    }
}
void targetingByWhiteQueen(){
    short i,j;
    for(i=1;i<=8;++i){
        for(j=1;j<=8;++j){
            if(X[i][j]=="WQ"){
                short a,b;
                for(a=i+1;X[a][j]!="00";++a){
                    if(X[a][j]=="--")X[a][j]="XX";
                    else break;
                }
                for(a=i-1;X[a][j]!="00";--a){
                    if(X[a][j]=="--")X[a][j]="XX";
                    else break;
                }
                for(a=j+1;X[i][a]!="00";++a){
                    if(X[i][a]=="--")X[i][a]="XX";
                    else break;
                }
                for(a=j-1;X[i][a]!="00";--a){
                    if(X[i][a]=="--")X[i][a]="XX";
                    else break;
                }
                for(a=i+1,b=j+1;X[a][b]!="00";++a,++b){
                    if(X[a][b]=="--")X[a][b]="XX";
                    else break;
                }
                for(a=i-1,b=j+1;X[a][b]!="00";--a,++b){
                    if(X[a][b]=="--")X[a][b]="XX";
                    else break;
                }
                for(a=i+1,b=j-1;X[a][b]!="00";++a,--b){
                    if(X[a][b]=="--")X[a][b]="XX";
                    else break;
                }
                for(a=i-1,b=j-1;X[a][b]!="00";--a,--b){
                    if(X[a][b]=="--")X[a][b]="XX";
                    else break;
                }
            }
        }
    }
}
void targetingByWhitePawn(){
    short i,j;
    for(i=1;i<=8;++i){
        for(j=1;j<=8;++j){
            if(X[i][j]=="WP"){
                if(X[i-1][j-1]=="--")X[i-1][j-1]="XX";
                if(X[i-1][j+1]=="--")X[i-1][j+1]="XX";
            }
        }
    }
}
void targetingByWhiteKing(){
    short i,j;
    for(i=1;i<=8;++i){
        for(j=1;j<=8;++j){
            if(X[i][j]=="WK"){
                if(X[i-1][j-1]=="--")X[i-1][j-1]="XX";
                if(X[i-1][ j ]=="--")X[i-1][ j ]="XX";
                if(X[i-1][j+1]=="--")X[i-1][j+1]="XX";
                if(X[ i ][j-1]=="--")X[ i ][j-1]="XX";
                if(X[ i ][j+1]=="--")X[ i ][j+1]="XX";
                if(X[i+1][j-1]=="--")X[i+1][j-1]="XX";
                if(X[i-1][ j ]=="--")X[i-1][ j ]="XX";
                if(X[i-1][j+1]=="--")X[i-1][j+1]="XX";
            }
        }
    }
}

// for checking check and mate functions || last error7
short makeCheck(string F,string A,string B,short a,short b,short c,short d){
    // Works on both colors!
    knightCheckKing(F,A,B,a,b,c,d);
    rockCheckKing(F,A,B,a,b,c,d);
    bishopCheckKing(F,A,B,a,b,c,d);
    queenCheckKing(F,A,B,a,b,c,d);
    pawnCheckKing(F,A,B,a,b,c,d);
}
void knightCheckKing(string F,string A,string B,short a,short b,short c,short d){
    if(F=="WN"){
        if(X[c-2][d-1]=="BK")checkRunAttackDefendDefendbyalliance[0]=1,cout<<"Check!\n";
        if(X[c-2][d+1]=="BK")checkRunAttackDefendDefendbyalliance[0]=1,cout<<"Check!\n";
        if(X[c-1][d+2]=="BK")checkRunAttackDefendDefendbyalliance[0]=1,cout<<"Check!\n";
        if(X[c+1][d+2]=="BK")checkRunAttackDefendDefendbyalliance[0]=1,cout<<"Check!\n";
        if(X[c+2][d-1]=="BK")checkRunAttackDefendDefendbyalliance[0]=1,cout<<"Check!\n";
        if(X[c+2][d+1]=="BK")checkRunAttackDefendDefendbyalliance[0]=1,cout<<"Check!\n";
        if(X[c-1][d-2]=="BK")checkRunAttackDefendDefendbyalliance[0]=1,cout<<"Check!\n";
        if(X[c+1][d-2]=="BK")checkRunAttackDefendDefendbyalliance[0]=1,cout<<"Check!\n";
    }
    else if(F=="BN"){
        if(X[c-2][d-1]=="WK")checkRunAttackDefendDefendbyalliance[0]=1,cout<<"Check!\n";
        if(X[c-2][d+1]=="WK")checkRunAttackDefendDefendbyalliance[0]=1,cout<<"Check!\n";
        if(X[c-1][d+2]=="WK")checkRunAttackDefendDefendbyalliance[0]=1,cout<<"Check!\n";
        if(X[c+1][d+2]=="WK")checkRunAttackDefendDefendbyalliance[0]=1,cout<<"Check!\n";
        if(X[c+2][d-1]=="WK")checkRunAttackDefendDefendbyalliance[0]=1,cout<<"Check!\n";
        if(X[c+2][d+1]=="WK")checkRunAttackDefendDefendbyalliance[0]=1,cout<<"Check!\n";
        if(X[c-1][d-2]=="WK")checkRunAttackDefendDefendbyalliance[0]=1,cout<<"Check!\n";
        if(X[c+1][d-2]=="WK")checkRunAttackDefendDefendbyalliance[0]=1,cout<<"Check!\n";
    }
}
void rockCheckKing(string F,string A,string B,short a,short b,short c,short d){
    short i;
    if(F=="WR"){
        for(i=c-1;i>=1;--i){
            if(X[i][d]=="BK"){checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";break;}
            else if(X[i][d]=="--")continue;
            else break;
        }
        for(i=c+1;i<=8;++i){
            if(X[i][d]=="BK"){checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";break;}
            else if(X[i][d]=="--")continue;
            else break;
        }
        for(i=d-1;i>=1;--i){
            if(X[c][i]=="BK"){checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";break;}
            else if(X[c][i]=="--")continue;
            else break;
        }
        for(i=d-1;i<=8;++i){
            if(X[c][i]=="BK"){checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";break;}
            else if(X[c][i]=="--")continue;
            else break;
        }
    }
    else if(F=="BR"){
        for(i=c-1;i>=1;--i){
            if(X[i][d]=="WK"){checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";break;}
            else if(X[i][d]=="--")continue;
            else break;
        }
        for(i=c+1;i<=8;++i){
            if(X[i][d]=="WK"){checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";break;}
            else if(X[i][d]=="--")continue;
            else break;
        }
        for(i=d-1;i>=1;--i){
            if(X[c][i]=="WK"){checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";break;}
            else if(X[c][i]=="--")continue;
            else break;
        }
        for(i=d-1;i<=8;++i){
            if(X[c][i]=="WK"){checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";break;}
            else if(X[c][i]=="--")continue;
            else break;
        }
    }
}
void bishopCheckKing(string F,string A,string B,short a,short b,short c,short d){
    short i,j;
    if(F=="WB"){
        for(i=c+1,j=d+1;X[c][d]!="00";++i,++j){
            if(X[c][d]=="BK"){checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";break;}
            else if(X[c][d]=="--")continue;
            else break;
        }
        for(i=c-1,j=d+1;X[c][d]!="00";--i,++j){
            if(X[c][d]=="BK"){checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";break;}
            else if(X[c][d]=="--")continue;
            else break;
        }
        for(i=c+1,j=d-1;X[c][d]!="00";++i,--j){
            if(X[c][d]=="BK"){checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";break;}
            else if(X[c][d]=="--")continue;
            else break;
        }
        for(i=c-1,j=d-1;X[c][d]!="00";--i,--j){
            if(X[c][d]=="BK"){checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";break;}
            else if(X[c][d]=="--")continue;
            else break;
        }
    }
    else if(F=="BB"){
        for(i=c+1,j=d+1;X[c][d]!="00";++i,++j){
            if(X[c][d]=="WK"){checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";break;}
            else if(X[c][d]=="--")continue;
            else break;
        }
        for(i=c-1,j=d+1;X[c][d]!="00";--i,++j){
            if(X[c][d]=="WK"){checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";break;}
            else if(X[c][d]=="--")continue;
            else break;
        }
        for(i=c+1,j=d-1;X[c][d]!="00";++i,--j){
            if(X[c][d]=="WK"){checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";break;}
            else if(X[c][d]=="--")continue;
            else break;
        }
        for(i=c-1,j=d-1;X[c][d]!="00";--i,--j){
            if(X[c][d]=="WK"){checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";break;}
            else if(X[c][d]=="--")continue;
            else break;
        }
    }
}
void queenCheckKing(string F,string A,string B,short a,short b,short c,short d){
    short i,j;
    if(F=="WQ"){
        // Horizontal && Vertical
        for(i=c-1;i>=1;--i){
            if(X[i][d]=="BK"){checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";break;}
            else if(X[i][d]=="--")continue;
            else break;
        }
        for(i=c+1;i<=8;++i){
            if(X[i][d]=="BK"){checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";break;}
            else if(X[i][d]=="--")continue;
            else break;
        }
        for(i=d-1;i>=1;--i){
            if(X[c][i]=="BK"){checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";break;}
            else if(X[c][i]=="--")continue;
            else break;
        }
        for(i=d-1;i<=8;++i){
            if(X[c][i]=="BK"){checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";break;}
            else if(X[c][i]=="--")continue;
            else break;
        }
        // Diagonals
        for(i=c+1,j=d+1;X[c][d]!="00";++i,++j){
            if(X[c][d]=="BK"){checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";break;}
            else if(X[c][d]=="--")continue;
            else break;
        }
        for(i=c-1,j=d+1;X[c][d]!="00";--i,++j){
            if(X[c][d]=="BK"){checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";break;}
            else if(X[c][d]=="--")continue;
            else break;
        }
        for(i=c+1,j=d-1;X[c][d]!="00";++i,--j){
            if(X[c][d]=="BK"){checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";break;}
            else if(X[c][d]=="--")continue;
            else break;
        }
        for(i=c-1,j=d-1;X[c][d]!="00";--i,--j){
            if(X[c][d]=="BK"){checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";break;}
            else if(X[c][d]=="--")continue;
            else break;
        }
    }
    else if(F=="BQ"){
        // Horizontal && Vertical
        for(i=c-1;i>=1;--i){
            if(X[i][d]=="WK"){checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";break;}
            else if(X[i][d]=="--")continue;
            else break;
        }
        for(i=c+1;i<=8;++i){
            if(X[i][d]=="WK"){checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";break;}
            else if(X[i][d]=="--")continue;
            else break;
        }
        for(i=d-1;i>=1;--i){
            if(X[c][i]=="WK"){checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";break;}
            else if(X[c][i]=="--")continue;
            else break;
        }
        for(i=d-1;i<=8;++i){
            if(X[c][i]=="WK"){checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";break;}
            else if(X[c][i]=="--")continue;
            else break;
        }
        // Diagonals
        for(i=c+1,j=d+1;X[c][d]!="00";++i,++j){
            if(X[c][d]=="WK"){checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";break;}
            else if(X[c][d]=="--")continue;
            else break;
        }
        for(i=c-1,j=d+1;X[c][d]!="00";--i,++j){
            if(X[c][d]=="WK"){checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";break;}
            else if(X[c][d]=="--")continue;
            else break;
        }
        for(i=c+1,j=d-1;X[c][d]!="00";++i,--j){
            if(X[c][d]=="WK"){checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";break;}
            else if(X[c][d]=="--")continue;
            else break;
        }
        for(i=c-1,j=d-1;X[c][d]!="00";--i,--j){
            if(X[c][d]=="WK"){checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";break;}
            else if(X[c][d]=="--")continue;
            else break;
        }
    }
}
void pawnCheckKing(string F,string A,string B,short a,short b,short c,short d){
    if(F=="WP"){
        if(X[c-1][d-1]=="BK")checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";
        if(X[c-1][d+1]=="BK")checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";
    }
    else if(F=="BP"){
        if(X[c-1][d-1]=="WK")checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";
        if(X[c-1][d+1]=="WK")checkRunAttackDefendDefendbyalliance[0]=1;cout<<"Check!\n";
    }
}

void makeDefend(string F,string A,string B,short a,short b,short c,short d){
    // Someone attack king
    // This function says 2 thing and both gives checkRunAttackDefendDefendbyalliance[2]'s element as 1
    // #1 can we kill figure which attacked on king without king
    // #2 can we block his/her way to the king
    short i,j,m,n;
    if(F[0]=='W'){
        // Black figures (not king) can't kill F figure, because they don't attack on that coordinates.
        targetingByBlackKnight();
        targetingByBlackRock();
        targetingByBlackBishop();
        targetingByBlackQueen();
        targetingByBlackPawn();
        if(X[c][d]!="XX")cout<<"Black figures (not king) can't kill "<<F<<"\n",checkRunAttackDefendDefendbyalliance[2]=1;
        clearBoardFromXXKKXY();
        // King/Knight not here!..
        // This part checks if I can defend king with alliance figure between attacking figure and my king.
        for(i=1;i<=8;++i){
            short k;
            for(j=1;j<=8;++j){
                if(X[i][j]=="BK"){k=1;break;}
            }
            if(k)break;
        }
        short XX=i,YY=j;
        if(F=="WR"){
            if(XX>c && YY==d){
                // king is on bottom
                for(m=c+1;X[m][YY]!="BK";++m)X[m][YY]="XY",++XY;
            }
            else if(XX<c && YY==d){
                // king is on top
                for(m=c-1;X[m][YY]!="BK";--m)X[m][YY]="XY",++XY;
            }
            else if(XX==c && YY<d){
                // king is on left
                for(m=d-1;X[XX][m]!="BK";--m)X[XX][m]="XY",++XY;
            }
            else if(XX==c && YY>d){
                // king is on right
                for(m=d+1;X[XX][m]!="BK";++m)X[XX][m]="XY",++XY;
            }
            targetingByBlackRock();
            targetingByBlackBishop();
            targetingByBlackQueen();
            targetingByBlackPawn();
            short q,w;
            for(q=1;q<=8;++q){
                for(w=1;w<=8;++w){
                    if(X[q][w]=="XY")--XY;
                }
            }
            if(!XY){cout<<"Black figures (not king) can't stay between "<<F<<" and king!\n",checkRunAttackDefendDefendbyalliance[2]=1;}
            clearBoardFromXXKKXY();
            XY=0;
        }
        else if(F=="WB"){
            if(XX>c && YY>d){
                // king is on bottom-right
                for(m=XX+1,n=YY+1;X[m][n]!="BK";++m,++n)X[m][n]="XY",++XY;
            }
            else if(XX>c && YY<d){
                // king is on bottom-left
                for(m=XX+1,n=YY-1;X[m][n]!="BK";++m,--n)X[m][n]="XY",++XY;
            }
            else if(XX<c && YY<d){
                // king is on top-left
                for(m=XX-1,n=YY-1;X[m][n]!="BK";--m,--n)X[m][n]="XY",++XY;
            }
            else if(XX<c && YY>d){
                // king is on top-right
                for(m=XX-1,n=YY+1;X[m][n]!="BK";--m,++n)X[m][n]="XY",++XY;
            }
            targetingByBlackRock();
            targetingByBlackBishop();
            targetingByBlackQueen();
            targetingByBlackPawn();
            short q,w;
            for(q=1;q<=8;++q){
                for(w=1;w<=8;++w){
                    if(X[q][w]=="XY")--XY;
                }
            }
            if(!XY){cout<<"Black figures (not king) can't stay between "<<F<<" and king!\n",checkRunAttackDefendDefendbyalliance[2]=1;}
            clearBoardFromXXKKXY();
            XY=0;
        }
        else if(F=="WQ"){
            if(XX>c && YY==d){
                // king is on bottom
                for(m=c+1;X[m][YY]!="BK";++m)X[m][YY]="XY",++XY;
            }
            else if(XX<c && YY==d){
                // king is on top
                for(m=c-1;X[m][YY]!="BK";--m)X[m][YY]="XY",++XY;
            }
            else if(XX==c && YY<d){
                // king is on left
                for(m=d-1;X[XX][m]!="BK";--m)X[XX][m]="XY",++XY;
            }
            else if(XX==c && YY>d){
                // king is on right
                for(m=d+1;X[XX][m]!="BK";++m)X[XX][m]="XY",++XY;
            }
            if(XX>c && YY>d){
                // king is on bottom-right
                for(m=XX+1,n=YY+1;X[m][n]!="BK";++m,++n)X[m][n]="XY",++XY;
            }
            else if(XX>c && YY<d){
                // king is on bottom-left
                for(m=XX+1,n=YY-1;X[m][n]!="BK";++m,--n)X[m][n]="XY",++XY;
            }
            else if(XX<c && YY<d){
                // king is on top-left
                for(m=XX-1,n=YY-1;X[m][n]!="BK";--m,--n)X[m][n]="XY",++XY;
            }
            else if(XX<c && YY>d){
                // king is on top-right
                for(m=XX-1,n=YY+1;X[m][n]!="BK";--m,++n)X[m][n]="XY",++XY;
            }
            targetingByBlackRock();
            targetingByBlackBishop();
            targetingByBlackQueen();
            targetingByBlackPawn();
            short q,w;
            for(q=1;q<=8;++q){
                for(w=1;w<=8;++w){
                    if(X[q][w]=="XY")--XY;
                }
            }
            if(!XY){cout<<"Black figures (not king) can't stay between "<<F<<" and king!\n",checkRunAttackDefendDefendbyalliance[2]=1;}
            clearBoardFromXXKKXY();
            XY=0;
        }
    }
    else if(F[0]=='B'){
        //White figures (not king) can't kill F figure, because they can't go on that coordinate.
        targetingByWhiteKnight();
        targetingByWhiteRock();
        targetingByWhiteBishop();
        targetingByWhiteQueen();
        targetingByWhitePawn();
        if(X[c][d]!="XX")cout<<"White figures (not king) can't kill "<<F<<"\n",checkRunAttackDefendDefendbyalliance[2]=1;
        clearBoardFromXXKKXY();
        // King/Knight not here!..
        // This part checks if I can defend king with alliance figure between attacking figure and my king.
        for(i=1;i<=8;++i){
            short k;
            for(j=1;j<=8;++j){
                if(X[i][j]=="BK"){k=1;break;}
            }
            if(k)break;
        }
        short XX=i,YY=j;
        if(F=="BR"){
            if(XX>c && YY==d){
                // king is on bottom
                for(m=c+1;X[m][YY]!="WK";++m)X[m][YY]="XY",++XY;
            }
            else if(XX<c && YY==d){
                // king is on top
                for(m=c-1;X[m][YY]!="WK";--m)X[m][YY]="XY",++XY;
            }
            else if(XX==c && YY<d){
                // king is on left
                for(m=d-1;X[XX][m]!="WK";--m)X[XX][m]="XY",++XY;
            }
            else if(XX==c && YY>d){
                // king is on right
                for(m=d+1;X[XX][m]!="WK";++m)X[XX][m]="XY",++XY;
            }
            targetingByBlackRock();
            targetingByBlackBishop();
            targetingByBlackQueen();
            targetingByBlackPawn();
            short q,w;
            for(q=1;q<=8;++q){
                for(w=1;w<=8;++w){
                    if(X[q][w]=="XY")--XY;
                }
            }
            if(!XY){cout<<"White figures (not king) can't stay between "<<F<<" and king!\n",checkRunAttackDefendDefendbyalliance[2]=1;}
            clearBoardFromXXKKXY();
            XY=0;
        }
        else if(F=="WB"){
            if(XX>c && YY>d){
                // king is on bottom-right
                for(m=XX+1,n=YY+1;X[m][n]!="WK";++m,++n)X[m][n]="XY",++XY;
            }
            else if(XX>c && YY<d){
                // king is on bottom-left
                for(m=XX+1,n=YY-1;X[m][n]!="WK";++m,--n)X[m][n]="XY",++XY;
            }
            else if(XX<c && YY<d){
                // king is on top-left
                for(m=XX-1,n=YY-1;X[m][n]!="WK";--m,--n)X[m][n]="XY",++XY;
            }
            else if(XX<c && YY>d){
                // king is on top-right
                for(m=XX-1,n=YY+1;X[m][n]!="WK";--m,++n)X[m][n]="XY",++XY;
            }
            targetingByBlackRock();
            targetingByBlackBishop();
            targetingByBlackQueen();
            targetingByBlackPawn();
            short q,w;
            for(q=1;q<=8;++q){
                for(w=1;w<=8;++w){
                    if(X[q][w]=="XY")--XY;
                }
            }
            if(!XY){cout<<"White figures (not king) can't stay between "<<F<<" and king!\n",checkRunAttackDefendDefendbyalliance[2]=1;}
            clearBoardFromXXKKXY();
            XY=0;
        }
        else if(F=="WQ"){
            if(XX>c && YY==d){
                // king is on bottom
                for(m=c+1;X[m][YY]!="WK";++m)X[m][YY]="XY",++XY;
            }
            else if(XX<c && YY==d){
                // king is on top
                for(m=c-1;X[m][YY]!="WK";--m)X[m][YY]="XY",++XY;
            }
            else if(XX==c && YY<d){
                // king is on left
                for(m=d-1;X[XX][m]!="WK";--m)X[XX][m]="XY",++XY;
            }
            else if(XX==c && YY>d){
                // king is on right
                for(m=d+1;X[XX][m]!="WK";++m)X[XX][m]="XY",++XY;
            }
            if(XX>c && YY>d){
                // king is on bottom-right
                for(m=XX+1,n=YY+1;X[m][n]!="WK";++m,++n)X[m][n]="XY",++XY;
            }
            else if(XX>c && YY<d){
                // king is on bottom-left
                for(m=XX+1,n=YY-1;X[m][n]!="WK";++m,--n)X[m][n]="XY",++XY;
            }
            else if(XX<c && YY<d){
                // king is on top-left
                for(m=XX-1,n=YY-1;X[m][n]!="WK";--m,--n)X[m][n]="XY",++XY;
            }
            else if(XX<c && YY>d){
                // king is on top-right
                for(m=XX-1,n=YY+1;X[m][n]!="WK";--m,++n)X[m][n]="XY",++XY;
            }
            targetingByBlackRock();
            targetingByBlackBishop();
            targetingByBlackQueen();
            targetingByBlackPawn();
            short q,w;
            for(q=1;q<=8;++q){
                for(w=1;w<=8;++w){
                    if(X[q][w]=="XY")--XY;
                }
            }
            if(!XY){cout<<"White figures (not king) can't stay between "<<F<<" and king!\n",checkRunAttackDefendDefendbyalliance[2]=1;}
            clearBoardFromXXKKXY();
            XY=0;
        }
    }
}
void attackerIsReinforced(string F,string A,string B,short a,short b,short c,short d){
    short i,j;
    if(F[0]=='W'){
        for(i=1;i<=8;++i){
            for(j=1;j<=8;++j){
                if(X[i][j]=="WK"){
                    if(X[i-1][j-1]==F)checkRunAttackDefendDefendbyalliance[3]=1;break;
                    if(X[i-1][ j ]==F)checkRunAttackDefendDefendbyalliance[3]=1;break;
                    if(X[i-1][j+1]==F)checkRunAttackDefendDefendbyalliance[3]=1;break;
                    if(X[ i ][j-1]==F)checkRunAttackDefendDefendbyalliance[3]=1;break;
                    if(X[ i ][j+1]==F)checkRunAttackDefendDefendbyalliance[3]=1;break;
                    if(X[i+1][j-1]==F)checkRunAttackDefendDefendbyalliance[3]=1;break;
                    if(X[i-1][ j ]==F)checkRunAttackDefendDefendbyalliance[3]=1;break;
                    if(X[i-1][j+1]==F)checkRunAttackDefendDefendbyalliance[3]=1;break;
                }
                else if(X[i][j]=="WN"){
                    if(X[i-2][j-1]==F)checkRunAttackDefendDefendbyalliance[3]=1;
                    if(X[i-2][j+1]==F)checkRunAttackDefendDefendbyalliance[3]=1;
                    if(X[i-1][j+2]==F)checkRunAttackDefendDefendbyalliance[3]=1;
                    if(X[i+1][j+2]==F)checkRunAttackDefendDefendbyalliance[3]=1;
                    if(X[i+2][j+1]==F)checkRunAttackDefendDefendbyalliance[3]=1;
                    if(X[i+2][j-1]==F)checkRunAttackDefendDefendbyalliance[3]=1;
                    if(X[i-1][j-2]==F)checkRunAttackDefendDefendbyalliance[3]=1;
                    if(X[i+1][j-2]==F)checkRunAttackDefendDefendbyalliance[3]=1;
                }
                else if(X[i][j]=="WR"){
                    short a;
                    for(a=i+1;X[a][j]!="00";++a){
                        if(X[a][j]=="--")continue;
                        else if(X[a][j]==F){checkRunAttackDefendDefendbyalliance[3]=1;break;}
                        else break;
                    }
                    for(a=i-1;X[a][j]!="00";--a){
                        if(X[a][j]=="--")continue;
                        else if(X[a][j]==F){checkRunAttackDefendDefendbyalliance[3]=1;break;}
                        else break;
                    }
                    for(a=j+1;X[i][a]!="00";++a){
                        if(X[a][j]=="--")continue;
                        else if(X[i][a]==F){checkRunAttackDefendDefendbyalliance[3]=1;break;}
                        else break;
                    }
                    for(a=j-1;X[i][a]!="00";--a){
                        if(X[a][j]=="--")continue;
                        else if(X[i][a]==F){checkRunAttackDefendDefendbyalliance[3]=1;break;}
                        else break;
                    }
                }
                else if(X[i][j]=="WB"){
                    short a,b;
                    for(a=i+1,b=j+1;X[a][b]!="00";++a,++b){
                        if(X[a][b]=="--")continue;
                        else if(X[a][b]==F){checkRunAttackDefendDefendbyalliance[3]=1;break;}
                        else break;
                    }
                    for(a=i-1,b=j+1;X[a][b]!="00";--a,++b){
                        if(X[a][b]=="--")continue;
                        else if(X[a][b]==F){checkRunAttackDefendDefendbyalliance[3]=1;break;}
                        else break;
                    }
                    for(a=i+1,b=j-1;X[a][b]!="00";++a,--b){
                        if(X[a][b]=="--")continue;
                        else if(X[a][b]==F){checkRunAttackDefendDefendbyalliance[3]=1;break;}
                        else break;
                    }
                    for(a=i-1,b=j-1;X[a][b]!="00";--a,--b){
                        if(X[a][b]=="--")continue;
                        else if(X[a][b]==F){checkRunAttackDefendDefendbyalliance[3]=1;break;}
                        else break;
                    }
                }
                else if(X[i][j]=="WQ"){
                    short a,b;
                    for(a=i+1;X[a][j]!="00";++a){
                        if(X[a][j]=="--")continue;
                        else if(X[a][j]==F){checkRunAttackDefendDefendbyalliance[3]=1;break;}
                        else break;
                    }
                    for(a=i-1;X[a][j]!="00";--a){
                        if(X[a][j]=="--")continue;
                        else if(X[a][j]==F){checkRunAttackDefendDefendbyalliance[3]=1;break;}
                        else break;
                    }
                    for(a=j+1;X[i][a]!="00";++a){
                        if(X[a][j]=="--")continue;
                        else if(X[i][a]==F){checkRunAttackDefendDefendbyalliance[3]=1;break;}
                        else break;
                    }
                    for(a=j-1;X[i][a]!="00";--a){
                        if(X[a][j]=="--")continue;
                        else if(X[i][a]==F){checkRunAttackDefendDefendbyalliance[3]=1;break;}
                        else break;
                    }
                    for(a=i+1,b=j+1;X[a][b]!="00";++a,++b){
                        if(X[a][b]=="--")continue;
                        else if(X[a][b]==F){checkRunAttackDefendDefendbyalliance[3]=1;break;}
                        else break;
                    }
                    for(a=i-1,b=j+1;X[a][b]!="00";--a,++b){
                        if(X[a][b]=="--")continue;
                        else if(X[a][b]==F){checkRunAttackDefendDefendbyalliance[3]=1;break;}
                        else break;
                    }
                    for(a=i+1,b=j-1;X[a][b]!="00";++a,--b){
                        if(X[a][b]=="--")continue;
                        else if(X[a][b]==F){checkRunAttackDefendDefendbyalliance[3]=1;break;}
                        else break;
                    }
                    for(a=i-1,b=j-1;X[a][b]!="00";--a,--b){
                        if(X[a][b]=="--")continue;
                        else if(X[a][b]==F){checkRunAttackDefendDefendbyalliance[3]=1;break;}
                        else break;
                    }
                }
                else if(X[i][j]=="WP")if(X[i-1][j-1]==F || X[i-1][j+1]==F)checkRunAttackDefendDefendbyalliance[3]=1;
            }
        }
    }
    else if(F[0]=='B'){
        for(i=1;i<=8;++i){
            for(j=1;j<=8;++j){
                if(X[i][j]=="BK"){
                    if(X[i-1][j-1]==F)checkRunAttackDefendDefendbyalliance[3]=1;break;
                    if(X[i-1][ j ]==F)checkRunAttackDefendDefendbyalliance[3]=1;break;
                    if(X[i-1][j+1]==F)checkRunAttackDefendDefendbyalliance[3]=1;break;
                    if(X[ i ][j-1]==F)checkRunAttackDefendDefendbyalliance[3]=1;break;
                    if(X[ i ][j+1]==F)checkRunAttackDefendDefendbyalliance[3]=1;break;
                    if(X[i+1][j-1]==F)checkRunAttackDefendDefendbyalliance[3]=1;break;
                    if(X[i-1][ j ]==F)checkRunAttackDefendDefendbyalliance[3]=1;break;
                    if(X[i-1][j+1]==F)checkRunAttackDefendDefendbyalliance[3]=1;break;
                }
                else if(X[i][j]=="BN"){
                    if(X[i-2][j-1]==F)checkRunAttackDefendDefendbyalliance[3]=1;
                    if(X[i-2][j+1]==F)checkRunAttackDefendDefendbyalliance[3]=1;
                    if(X[i-1][j+2]==F)checkRunAttackDefendDefendbyalliance[3]=1;
                    if(X[i+1][j+2]==F)checkRunAttackDefendDefendbyalliance[3]=1;
                    if(X[i+2][j+1]==F)checkRunAttackDefendDefendbyalliance[3]=1;
                    if(X[i+2][j-1]==F)checkRunAttackDefendDefendbyalliance[3]=1;
                    if(X[i-1][j-2]==F)checkRunAttackDefendDefendbyalliance[3]=1;
                    if(X[i+1][j-2]==F)checkRunAttackDefendDefendbyalliance[3]=1;
                }
                else if(X[i][j]=="BR"){
                    short a;
                    for(a=i+1;X[a][j]!="00";++a){
                        if(X[a][j]=="--")continue;
                        else if(X[a][j]==F){checkRunAttackDefendDefendbyalliance[3]=1;break;}
                        else break;
                    }
                    for(a=i-1;X[a][j]!="00";--a){
                        if(X[a][j]=="--")X[a][j]="XX";
                        else if(X[a][j]==F){checkRunAttackDefendDefendbyalliance[3]=1;break;}
                        else break;
                    }
                    for(a=j+1;X[i][a]!="00";++a){
                        if(X[i][a]=="--")X[i][a]="XX";
                        else if(X[i][a]==F){checkRunAttackDefendDefendbyalliance[3]=1;break;}
                        else break;
                    }
                    for(a=j-1;X[i][a]!="00";--a){
                        if(X[i][a]=="--")X[i][a]="XX";
                        else if(X[i][a]==F){checkRunAttackDefendDefendbyalliance[3]=1;break;}
                        else break;
                    }
                }
                else if(X[i][j]=="BB"){
                    short a,b;
                    for(a=i+1,b=j+1;X[a][b]!="00";++a,++b){
                        if(X[a][b]=="--")continue;
                        else if(X[a][b]==F){checkRunAttackDefendDefendbyalliance[3]=1;break;}
                        else break;
                    }
                    for(a=i-1,b=j+1;X[a][b]!="00";--a,++b){
                        if(X[a][b]=="--")continue;
                        else if(X[a][b]==F){checkRunAttackDefendDefendbyalliance[3]=1;break;}
                        else break;
                    }
                    for(a=i+1,b=j-1;X[a][b]!="00";++a,--b){
                        if(X[a][b]=="--")continue;
                        else if(X[a][b]==F){checkRunAttackDefendDefendbyalliance[3]=1;break;}
                        else break;
                    }
                    for(a=i-1,b=j-1;X[a][b]!="00";--a,--b){
                        if(X[a][b]=="--")continue;
                        else if(X[a][b]==F){checkRunAttackDefendDefendbyalliance[3]=1;break;}
                        else break;
                    }
                }
                else if(X[i][j]=="BQ"){
                    short a,b;
                    for(a=i+1;X[a][j]!="00";++a){
                        if(X[a][j]=="--")continue;
                        else if(X[a][j]==F){checkRunAttackDefendDefendbyalliance[3]=1;break;}
                        else break;
                    }
                    for(a=i-1;X[a][j]!="00";--a){
                        if(X[a][j]=="--")continue;
                        else if(X[a][j]==F){checkRunAttackDefendDefendbyalliance[3]=1;break;}
                        else break;
                    }
                    for(a=j+1;X[i][a]!="00";++a){
                        if(X[a][j]=="--")continue;
                        else if(X[i][a]==F){checkRunAttackDefendDefendbyalliance[3]=1;break;}
                        else break;
                    }
                    for(a=j-1;X[i][a]!="00";--a){
                        if(X[a][j]=="--")continue;
                        else if(X[i][a]==F){checkRunAttackDefendDefendbyalliance[3]=1;break;}
                        else break;
                    }
                    for(a=i+1,b=j+1;X[a][b]!="00";++a,++b){
                        if(X[a][b]=="--")continue;
                        else if(X[a][b]==F){checkRunAttackDefendDefendbyalliance[3]=1;break;}
                        else break;
                    }
                    for(a=i-1,b=j+1;X[a][b]!="00";--a,++b){
                        if(X[a][b]=="--")continue;
                        else if(X[a][b]==F){checkRunAttackDefendDefendbyalliance[3]=1;break;}
                        else break;
                    }
                    for(a=i+1,b=j-1;X[a][b]!="00";++a,--b){
                        if(X[a][b]=="--")continue;
                        else if(X[a][b]==F){checkRunAttackDefendDefendbyalliance[3]=1;break;}
                        else break;
                    }
                    for(a=i-1,b=j-1;X[a][b]!="00";--a,--b){
                        if(X[a][b]=="--")continue;
                        else if(X[a][b]==F){checkRunAttackDefendDefendbyalliance[3]=1;break;}
                        else break;
                    }
                }
                else if(X[i][j]=="BP")if(X[i-1][j-1]==F || X[i-1][j+1]==F)checkRunAttackDefendDefendbyalliance[3]=1;
            }
        }
    }
}
void attackerIsNotReinforcedButHeIsToFarToKill(string F,string A,string B,short a,short b,short c,short d){
    if(checkRunAttackDefendDefendbyalliance[0]==1){
        short i,j;
        if(F[0]=='W'){
            for(i=1;i<=8;++i){
                for(j=1;j<=8;++j){
                    if(X[i][j]=="BK"){
                        if(i-1==c && j-1==d && checkRunAttackDefendDefendbyalliance[3]==1)Mate=1;
                        if(i-1==c &&  j ==d && checkRunAttackDefendDefendbyalliance[3]==1)Mate=1;
                        if(i-1==c && j+1==d && checkRunAttackDefendDefendbyalliance[3]==1)Mate=1;
                        if( i ==c && j-1==d && checkRunAttackDefendDefendbyalliance[3]==1)Mate=1;
                        if( i ==c && j+1==d && checkRunAttackDefendDefendbyalliance[3]==1)Mate=1;
                        if(i+1==c && j-1==d && checkRunAttackDefendDefendbyalliance[3]==1)Mate=1;
                        if(i-1==c &&  j ==d && checkRunAttackDefendDefendbyalliance[3]==1)Mate=1;
                        if(i-1==c && j+1==d && checkRunAttackDefendDefendbyalliance[3]==1)Mate=1;
                    }
                    else if(checkRunAttackDefendDefendbyalliance[3]==0){
                        if(i-1==c && j-1==d)Mate=0;
                        if(i-1==c &&  j ==d)Mate=0;
                        if(i-1==c && j+1==d)Mate=0;
                        if( i ==c && j-1==d)Mate=0;
                        if( i ==c && j+1==d)Mate=0;
                        if(i+1==c && j-1==d)Mate=0;
                        if(i-1==c &&  j ==d)Mate=0;
                        if(i-1==c && j+1==d)Mate=0;
                    }
                    else Mate=1;
                }
            }
        }
        else if(F[0]=='B'){
            for(i=1;i<=8;++i){
                for(j=1;j<=8;++j){
                    if(X[i][j]=="WK"){
                        if(i-1==c && j-1==d && checkRunAttackDefendDefendbyalliance[3]==1)Mate=1;
                        if(i-1==c &&  j ==d && checkRunAttackDefendDefendbyalliance[3]==1)Mate=1;
                        if(i-1==c && j+1==d && checkRunAttackDefendDefendbyalliance[3]==1)Mate=1;
                        if( i ==c && j-1==d && checkRunAttackDefendDefendbyalliance[3]==1)Mate=1;
                        if( i ==c && j+1==d && checkRunAttackDefendDefendbyalliance[3]==1)Mate=1;
                        if(i+1==c && j-1==d && checkRunAttackDefendDefendbyalliance[3]==1)Mate=1;
                        if(i-1==c &&  j ==d && checkRunAttackDefendDefendbyalliance[3]==1)Mate=1;
                        if(i-1==c && j+1==d && checkRunAttackDefendDefendbyalliance[3]==1)Mate=1;
                    }
                    else if(checkRunAttackDefendDefendbyalliance[3]==0){
                        if(i-1==c && j-1==d)Mate=0;
                        if(i-1==c &&  j ==d)Mate=0;
                        if(i-1==c && j+1==d)Mate=0;
                        if( i ==c && j-1==d)Mate=0;
                        if( i ==c && j+1==d)Mate=0;
                        if(i+1==c && j-1==d)Mate=0;
                        if(i-1==c &&  j ==d)Mate=0;
                        if(i-1==c && j+1==d)Mate=0;
                    }
                    else Mate=1;
                }
            }
        }
    }
}
// ************************************************************
// Functions