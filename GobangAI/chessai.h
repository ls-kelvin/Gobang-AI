#ifndef CHESSAI_H
#define CHESSAI_H
#include <vector>
using std::pair,std::vector;

typedef pair<int,int> pos;

const int MAX=100001,MIN=-100001;
enum gameturn{P1,P2};
enum gameplayer{HUMAN,AI};
enum gamestate{STOP,BEGIN};
enum point_state{BLANK,BLACK,WHITE,BORDER};
enum score_type{
    OTHER,B5,W5,BL4,WL4,BB4,WB4,
    BL3,WL3,BB3,WB3,BL2,WL2,BB2,WB2,BB4H,WB4H,TYPE_NUM
};
struct Chessboard{
    int chess_state[17][17];
    int chess_type[TYPE_NUM];
    bool type_check[15][15][4];
    constexpr static int dx[8]={0,1,1,1,0,-1,-1,-1};
    constexpr static int dy[8]={1,1,0,-1,-1,-1,0,1};
    Chessboard();
    Chessboard(const Chessboard &a);
    int evaluate();
    void line_eva(int x,int y);
    bool islegal(int x, int y);
    bool hasNear(int x,int y);
    void clear();
};
struct node{
    Chessboard n_chess;
    int pre_score;
    int alpha=MIN,beta=MAX;
    pos down_place;
    node(const node&a):n_chess(a.n_chess),pre_score(a.pre_score),alpha(a.alpha),beta(a.beta),down_place(a.down_place){}
    node(Chessboard a,int pre_score=0):n_chess(a),pre_score(pre_score){}
    void getPossiblePoints(vector<node>& q,int color);
    bool operator<(const node&a)const{
        return pre_score<a.pre_score;
    }
    bool operator>(const node&a)const{
        return pre_score>a.pre_score;
    }
};
class chessAI
{
public:
    inline static float DEFFENCE_COE=1.01;
    inline static int DEPTH=4;
    inline static int weight[TYPE_NUM];
    Chessboard chessboard;
    chessAI();
    pos getBestPlace();
protected:
    void weight_init();
    void search(node& n,int depth=DEPTH);
};


#endif // CHESSAI_H
