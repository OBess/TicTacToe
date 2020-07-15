#include "game.h"

//Initial
Game::Game()
{
    size = new QPoint(3, 3);
    setArea(3, 3);
    this->scoreBot = 0;
    this->scorePlayer = 0;
    this->oncePlayerBot = false;
    this->onceBot = false;
}

Game::~Game(){
    clearArea();
    delete size;
}
//End initial


//Setters
void Game::setOnceBotPlayer(bool once){
    this->oncePlayerBot = once;
}
//End setters


//Getters
QPoint Game::getSize(){
    if(this->size)
        return *this->size;
    return QPoint(0, 0);
}
int Game::getSizeRect(){
    return this->sizeRect;
}
char** Game::getMap(){
    return this->map;
}
bool Game::IsLeftMove(){
    for(int i = 0; i < this->size->rx(); i++)
        for(int j = 0; j < this->size->ry(); j++)
            if(this->map[i][j] == ' ')
                return false;
    return true;
}
bool Game::IsWinner(){
    return this->evelution(this->map) != 0;
}
int Game::getScoreBot(){
    return scoreBot;
}
int Game::getScorePlayer(){
    return scorePlayer;
}
//End getters


//Bot logic
int Game::minimax(char** map, bool turn, bool bot){
    if(this->IsLeftMove()) return 0;

    int bestScore = this->evelution(map, bot);
    if(bestScore != 0){
        return bestScore;
    }

    if(bot){
        //When bot vs bot
        if(turn){
            bestScore = NEG_INF;
            for(int i = 0; i <  this->size->rx(); i++){
                for(int j = 0; j < this->size->ry(); j++){
                    if(map[i][j] == ' '){
                        map[i][j] = this->SYM_X;
                        bestScore = std::max(bestScore, minimax(map, !turn, bot));
                        map[i][j] = ' ';
                        if(bestScore >= this->MIN){
                            return bestScore;
                        }
                    }
                }
            }
        }else{
            bestScore = POS_INF;
            for(int i = 0; i <  this->size->rx(); i++){
                for(int j = 0; j < this->size->ry(); j++){
                    if(map[i][j] == ' '){
                        map[i][j] = this->SYM_0;
                        bestScore = std::min(bestScore, minimax(map, !turn, bot));
                        map[i][j] = ' ';
                        if(bestScore <= this->MAX){
                            return bestScore;
                        }
                    }
                }
            }
        }
    }
    else{
        //When bot vs player
        if(turn){
            bestScore = NEG_INF;
            for(int i = 0; i <  this->size->rx(); i++){
                for(int j = 0; j < this->size->ry(); j++){
                    if(map[i][j] == ' '){
                        map[i][j] = this->SYM_0;
                        bestScore = std::max(bestScore, minimax(map, !turn, bot));
                        map[i][j] = ' ';
                        if(bestScore >= this->MIN){
                            return bestScore;
                        }
                    }
                }
            }
        }else{
            bestScore = POS_INF;
            for(int i = 0; i <  this->size->rx(); i++){
                for(int j = 0; j < this->size->ry(); j++){
                    if(map[i][j] == ' '){
                        map[i][j] = this->SYM_X;
                        bestScore = std::min(bestScore, minimax(map, !turn, bot));
                        map[i][j] = ' ';
                        if(bestScore <= this->MAX){
                            return bestScore;
                        }
                    }
                }
            }
        }
    }
    return bestScore;
}
void Game::nextMove(char** map, bool bot){
    int bestScore = NEG_INF;

    bestPoint.setX(0);
    bestPoint.setY(0);

    for(int i = 0; i <  this->size->rx(); i++){
        for(int j = 0; j < this->size->ry(); j++){
            if(map[i][j] == ' '){
                if(bot)
                    map[i][j] = this->SYM_X;
                else
                    map[i][j] = this->SYM_0;
                int newScore = minimax(map, false, bot);
                if(newScore >= bestScore){
                    bestScore = newScore;
                    bestPoint.setX(i);
                    bestPoint.setY(j);
                }
                map[i][j] = ' ';
            }
        }
    }
}
int Game::evelution(char** map, bool bot){
    int i;

    int k = bot ? -1: 1;

    for(i = 0; i < size->rx(); i++){
        if(map[i][0] ==  this->SYM_0 && map[i][1] ==  this->SYM_0 && map[i][2] ==  this->SYM_0)
            return MIN * k;
        if(map[i][0] ==  this->SYM_X &&  map[i][1] ==  this->SYM_X &&  map[i][2] ==  this->SYM_X)
            return MAX * k;
    }

    for(i = 0; i <  size->ry(); i++){
        if( map[0][i] ==  this->SYM_0 &&  map[1][i] ==  this->SYM_0 &&  map[2][i] ==  this->SYM_0)
            return MIN * k;
        if( map[0][i] ==  this->SYM_X &&  map[1][i] ==  this->SYM_X &&  map[2][i] ==  this->SYM_X)
            return MAX * k;
    }

    if( map[0][0] ==  this->SYM_0 &&  map[1][1] ==  this->SYM_0 &&  map[2][2] ==  this->SYM_0)
        return MIN * k;
    if( map[0][0] ==  this->SYM_X &&  map[1][1] ==  this->SYM_X &&  map[2][2] ==  this->SYM_X)
        return MAX * k;

    if( map[0][2] ==  this->SYM_0 &&  map[1][1] ==  this->SYM_0 &&  map[2][0] ==  this->SYM_0)
        return MIN * k;
    if( map[0][2] ==  this->SYM_X &&  map[1][1] ==  this->SYM_X &&  map[2][0] ==  this->SYM_X)
        return MAX * k;

    return 0;
}
//End bot logic


//Logics
void Game::updateScoreBot(){
    this->scoreBot++;
}
void Game::updateScorePlayer(){
    this->scorePlayer++;
}

void Game::reset(){
    this->oncePlayerBot = false;
    this->onceBot = true;
    this->clearArea();
    this->setArea(this->size->rx(), this->size->ry());
}
void Game::setPoint(int row, int col, char turn){
    this->map[row][col] = turn;
}

void Game::displayMatrix(char** map){
    std::cout << std::endl;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(map[i][j] == ' ')
                std::cout << '_' << ' ';
            else
                std::cout << map[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

void Game::setArea(int rows, int cols){
    this->map = new char*[rows];
    this->map[0] = new char[rows * cols];
    for(int i = 0; i < rows; ++i)
        this->map[i] = this->map[0] + i * cols;
    for(int i = 0; i < this->size->rx(); i++)
        for(int j = 0; j < this->size->ry(); j++)
            this->map[i][j] = ' ';
}
void Game::clearArea(){
    delete [] this->map[0];
    delete [] this->map;
}
char Game::getPoint(int row, int col){
    return this->map[row][col];
}
//End logics


//Game process
void Game::update(){
    int score = this->evelution(map);
    if(this->IsLeftMove() || score != 0){
        return;
    }

    if(this->onceBot){
        int x = rand() % 3;
        int y = rand() % 3;
        if(this->getPoint(x, y) != ' '){
            update();
            return;
        }
        this->setPoint(x, y, this->SYM_0);
        this->onceBot = false;
        return;
    }

    nextMove(this->map);
    setPoint(bestPoint.x(), bestPoint.y(), this->SYM_0);
}

void Game::updateOtherBot(){
    int score = this->evelution(map);
    if(this->IsLeftMove() || score != 0){
        return;
    }

    if(this->oncePlayerBot){
        srand (time(NULL));
        this->setPoint(rand() % 3, rand() % 3, this->SYM_X);
        this->oncePlayerBot = false;
        return;
    }

    nextMove(this->map, true);
    setPoint(bestPoint.x(), bestPoint.y(), this->SYM_X);
}
//End game process
