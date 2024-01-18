#include "chessai.h"
#include <cstring>
#include <algorithm>
bool Chessboard::islegal(int x, int y) {
    if (chess_state[x][y] == BLANK)
        return true;
    return false;
}

bool Chessboard::hasNear(int x, int y)
{

    for(int i=0;i<8;i++){
        int nx=x+dx[i],ny=y+dy[i];

        if(chess_state[nx][ny]==BLACK||chess_state[nx][ny]==WHITE)
            return true;
    }
    return false;
}

void Chessboard::clear()
{
    for(int j=0;j<17;j++){
        chess_state[0][j]=BORDER;
        chess_state[16][j]=BORDER;
    }
    for(int j=1;j<16;j++){
        chess_state[j][0]=BORDER;
        chess_state[j][16]=BORDER;
    }
    for (int i = 1; i <= 15; i++)
        for (int j = 1; j <= 15; j++)
            chess_state[i][j] = BLANK;
}
Chessboard::Chessboard()
{
    this->clear();
}

Chessboard::Chessboard(const Chessboard &a) {
    for(int j=0;j<17;j++){
        chess_state[0][j]=BORDER;
        chess_state[16][j]=BORDER;
    }
    for(int j=1;j<16;j++){
        chess_state[j][0]=BORDER;
        chess_state[j][16]=BORDER;
    }
    for (int i = 1; i <= 15; i++)
        for (int j = 1; j <= 15; j++)
            chess_state[i][j] = a.chess_state[i][j];
}

int Chessboard::evaluate()
{
    memset(type_check,0,sizeof(type_check));
    memset(chess_type,0,sizeof(chess_type));
    for(int i=1;i<=15;i++)
        for(int j=1;j<=15;j++)
            if(chess_state[i][j]==BLACK||chess_state[i][j]==WHITE){
                line_eva(i,j);
            }
    int score[2]={0,0};
    if(chess_type[B5]) return -100000;
    if(chess_type[W5]) return 100000;
    for(int i=0;i<2;i++){
        while(chess_type[BL4+i]){
            score[i]+=20000;
            chess_type[BL4+i]--;
        }
        while(chess_type[BB4+i]+chess_type[BB4H+i]>1){
            score[i]+=20000;
            if(chess_type[BB4+i]>1)
                chess_type[BB4+i]-=2;
            else if(chess_type[BB4H+i]>1)
                chess_type[BB4H+i]-=2;
            else{
                chess_type[BB4+i]--;chess_type[BB4+i]--;
            }
        }
        while(chess_type[BB4+i]+chess_type[BB4H+i]&&chess_type[BL3+i]){
            score[i]+=19000;
            if(chess_type[BB4+i])
                chess_type[BB4+i]--;
            else if(chess_type[BB4H+i])
                chess_type[BB4H+i]--;
            chess_type[BL3+i]--;
        }
        while(chess_type[BL3+i]>1){
            score[i]+=18000;
            chess_type[BL3+i]-=2;
        }
    }
    for(int i=BB4;i<TYPE_NUM;i++){
        if(i&1)
            score[0]+=chessAI::weight[i]*chess_type[i];
        else
            score[1]+=chessAI::weight[i]*chess_type[i];
    }
    return score[1]-score[0]*chessAI::DEFFENCE_COE;
}

void Chessboard::line_eva(int x,int y)
{
    for(int i=0;i<4;i++){
        if(!type_check[x][y][i]){
            int color=chess_state[x][y];
            int c1=1;
            int bx=x-dx[i],by=y-dy[i];
            int cx=x+dx[i],cy=y+dy[i];
            while(chess_state[cx][cy]==color){
                c1++;
                type_check[cx][cy][i]=true;
                cx+=dx[i];cy+=dy[i];
            }
            if(c1>=5){
                chess_type[B5+color-1]++;
                return;
            }
            if(chess_state[cx][cy]!=BLANK){
                if(chess_state[bx][by]!=BLANK)
                    continue;
                if(c1==4){
                    chess_type[BB4+color-1]++;
                    continue;
                }
                bx-=dx[i];by-=dy[i];
                if(chess_state[bx][by]!=BLANK)
                    continue;
                if(c1==3){
                    chess_type[BB3+color-1]++;
                    continue;
                }
                if(c1==2&&chess_state[bx-dx[i]][by-dy[i]]==BLANK){
                    chess_type[BB2+color-1]++;
                    continue;
                }
            }
            else{
                if(c1==4){
                    if(chess_state[bx][by]==BLANK){
                        chess_type[BL4+color-1]++;
                        continue;
                    }
                    else{
                        chess_type[BB4+color-1]++;
                        continue;
                    }
                }
                if(c1==3){
                    if(chess_state[bx][by]==BLANK){
                        if(chess_state[bx-dx[i]][by-dy[i]]!=BLANK&&chess_state[cx+dx[i]][cy+dy[i]]!=BLANK){
                            chess_type[BB3+color-1]++;
                            continue;
                        }
                        chess_type[BL3+color-1]++;
                        continue;
                    }
                    else{
                        chess_type[BB3+color-1]++;
                        continue;
                    }
                }
                int c2=0,b2=0,ex=cx+dx[i],ey=cy+dy[i];
                if(chess_state[ex][ey]==BLANK){
                    b2=1;
                    ex+=dx[i];ey+=dy[i];
                }
                while(chess_state[ex][ey]==color){
                    c2++;
                    type_check[ex][ey][i]=true;
                    ex+=dx[i];ey+=dy[i];
                }
                if(c2>=5){
                    chess_type[B5+color-1]++;
                    return;
                }
                if(c1+c2>=4){
                    if(b2==0){
                        if(chess_state[bx][by]==BLANK&&chess_state[ex][ey]==BLANK){
                            chess_type[BB4H+color-1]++;
                            continue;
                        }
                        chess_type[BB4+color-1]++;
                        continue;
                    }
                    else{
                        chess_type[BB3+color-1]++;
                        continue;
                    }
                }
                if(c1+c2==3){
                    if(chess_state[bx][by]==BLANK){
                        if(chess_state[ex][ey]==BLANK&&b2==0){
                            chess_type[BL3+color-1]++;
                            continue;
                        }
                        chess_type[BB3+color-1]++;
                        continue;
                    }
                    else{
                        if(chess_state[ex][ey]==BLANK){
                            chess_type[BB3+color-1]++;
                            continue;
                        }
                    }
                }
                if(c1+c2==2){
                    if(chess_state[bx][by]==BLANK){
                        if(chess_state[ex][ey]==BLANK){
                            chess_type[BL2+color-1]++;
                            continue;
                        }
                        chess_type[BB2+color-1]++;
                        continue;
                    }
                    else{
                        if(chess_state[ex][ey]==BLANK){
                            chess_type[BB2+color-1]++;
                            continue;
                        }
                    }
                }
            }
        }
    }
}


chessAI::chessAI()
{
    weight[0]=0;
    for(int i=0;i<2;i++){
        weight[B5+i]=100000;
        weight[BL4+i]=20000;
        weight[BB4+i]=180;
        weight[BL3+i]=100;
        weight[BB3+i]=40;
        weight[BL2+i]=25;
        weight[BB2+i]=10;
        weight[BB4H+i]=200;
    }
}

pos chessAI::getBestPlace()
{
    node root(chessboard);
    search(root);
    pos ans=root.down_place;
    return ans;
}


void chessAI::search(node& n, int depth)
{
    if(depth==0){
        n.alpha=n.pre_score;
        return ;
    }
    else if((depth&1)==0){
        vector<node> q;
        n.getPossiblePoints(q,WHITE);
        sort(q.begin(),q.end(),std::less<node>());
        while(!q.empty()){
            node child=q.back();
            q.pop_back();
            if(child.pre_score==100000){
                n.alpha=child.pre_score;
                if(depth==DEPTH)
                    n.down_place=child.down_place;
                return;
            }
            child.alpha=n.alpha;
            search(child,depth-1);
            if(child.beta>n.alpha){
                n.alpha=child.beta;
                if(depth==DEPTH)
                    n.down_place=child.down_place;
            }
            if(n.beta<=n.alpha){
                return ;
            }
        }
    }
    else if((depth&1)==1){
        vector<node> q;
        n.getPossiblePoints(q,BLACK);
        sort(q.begin(),q.end(),std::greater<node>());
        while(!q.empty()){
            node child=q.back();
            q.pop_back();
            if(child.pre_score==-100000){
                n.beta=child.pre_score;
                return;
            }
            child.beta=n.beta;
            search(child,depth-1);
            if(child.alpha<n.beta){
                n.beta=child.alpha;
            }
            if(n.beta<=n.alpha){
                return ;
            }
        }
    }
}

void node::getPossiblePoints(vector<node>& q,int color)
{
    for(int i=1;i<=15;i++)
        for(int j=1;j<=15;j++)
            if(n_chess.islegal(i,j)&&n_chess.hasNear(i,j)){
                Chessboard child_chess(n_chess);
                child_chess.chess_state[i][j]=color;
                int score=child_chess.evaluate();
                node tmp(child_chess,score);
                tmp.down_place={i,j};
                q.push_back(tmp);
            }
}


