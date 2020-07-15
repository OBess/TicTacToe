#include "panel.h"

//Initial
Panel::Panel(QWidget *parent, int offset) : QWidget(parent), FONTSIZE(parent->width()/6)
{
    resize(parent->width() - offset, parent->height());
    sizeRect.setX(this->width()/game.getSize().rx());
    sizeRect.setY(this->height()/game.getSize().ry());
    setMouseTracking(true);

    this->parent = parent;
    this->once = true;
    this->toggle = false;
}

Panel::~Panel(){}

void Panel::initButton(QPushButton* btn, std::string text, int width, int height, int posX, int posY){
    btn->setText(QString(text.c_str()));
    btn->setGeometry(posX, posY, width, height);
}

void Panel::initLabel(QLabel *lbl, std::string text, int posX, int posY){
    lbl->setText(QString(text.c_str()));
    lbl->setFont(QFont("Roboto", 8, QFont::Bold));
    lbl->setGeometry(posX, posY, 100, 30);
}

void Panel::initRadioButton(QRadioButton *rb, std::string text, int posX, int posY){
    rb->setText(QString(text.c_str()));
    rb->setFont(QFont("Roboto", 8, QFont::Bold));
    rb->setGeometry(posX, posY, 100, 30);
}
//End initial


//Setters
void Panel::setResetBTN(QPushButton* pb){
    this->resetBTN = pb;
}
void Panel::setScoreBotLBL(QLabel *lbl){
    this->scoreBotLBL = lbl;
}
void Panel::setScorePlayerLBL(QLabel *lbl){
    this->scorePlayerLBL = lbl;
}
void Panel::setBotVSBotRB(QRadioButton *rb){
    this->botVSbotRB = rb;
}
void Panel::setBotVSbot(bool toggle){
    this->toggle = toggle;
    this->resetGame();
}
//End setters


//All events of widget
void Panel::paintEvent(QPaintEvent *e){
    Q_UNUSED(e);
    QPainter qp(this);
    draw(&qp);
}

void Panel::mousePressEvent(QMouseEvent *e){
    if(this->game.getPoint(e->y()/this->sizeRect.ry(), e->x()/this->sizeRect.rx()) == ' ' && !this->game.IsLeftMove() && !this->game.IsWinner()){
        this->game.setPoint(e->y()/this->sizeRect.ry(), e->x()/this->sizeRect.rx(), this->game.SYM_X);
        repaint();
        QThread::msleep(500);
        this->game.update();
        repaint();
    }
}
//End all events of widget


//Logics
void Panel::resetGame(){
    this->game.reset();
    this->update();
    this->once = true;
    if(this->toggle){
        this->game.setOnceBotPlayer(true);
        std::thread(&Panel::gameBotVSBOT, &game, this, &toggle).detach();
    }
}

void Panel::gameBotVSBOT(Game* game, Panel* panel, bool* toggle){
    while (!game->IsLeftMove() && !game->IsWinner()) {
        if(!(*toggle)) break;
        game->updateOtherBot();
        panel->update();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        if(!(*toggle)) break;
        game->update();
        panel->update();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
//End logics


//Output
void Panel::updateCusotmUI(){
    this->initButton(resetBTN, "Reset", 50, 30, 425, 350);
    this->initLabel(scoreBotLBL, "Score BOT 0", 405, 20);
    this->initLabel(scorePlayerLBL, "Score Player 0", 405, 35);
    this->initRadioButton(botVSbotRB, "Bot VS Bot", 405, 50);
}

void Panel::updateScores(){
    this->scoreBotLBL->setText("Score BOT " + QString(std::to_string(this->game.getScoreBot()).c_str()));
    this->scorePlayerLBL->setText("Score Player " + QString(std::to_string(this->game.getScorePlayer()).c_str()));
}

void Panel::draw(QPainter *qp){
    qp->setPen(QPen(Qt::black, 10, Qt::SolidLine));

    qp->fillRect(0, 0, this->width(), this->height(), QBrush(Qt::gray));

    int i, j;
    for (i = 1; i < this->game.getSize().rx(); i++) {
        qp->drawLine(this->sizeRect.rx()*i, 0, sizeRect.rx()*i, this->height());
    }
    qp->drawLine(this->sizeRect.rx()*i, 0, this->sizeRect.rx()*i, this->height());
    for (j = 1; j < this->game.getSize().ry(); j++) {
        qp->drawLine(0, this->sizeRect.ry()*j, this->width(), this->sizeRect.ry()*j);
    }

    QFont font("Roboto", QFont::Bold);
    qp->setFont(font);

    for(i = 0; i < this->game.getSize().rx(); i++){
        for(j = 0; j < this->game.getSize().ry(); j++){
            if(this->game.getMap()[i][j] == this->game.SYM_0){
                qp->drawText(j*this->sizeRect.rx() + this->sizeRect.rx()/4, i*this->sizeRect.ry() + this->sizeRect.ry() - this->sizeRect.ry()/5, "0");
            }else if(this->game.getMap()[i][j] == this->game.SYM_X){
                qp->drawText(j*this->sizeRect.rx() + this->sizeRect.rx()/4, i*this->sizeRect.ry() + this->sizeRect.ry() - this->sizeRect.ry()/5, "X");
            }
        }
    }

    if(this->game.IsLeftMove() || this->game.IsWinner()){
        if(once){
            int score = this->game.evelution(this->game.getMap());
            if(score == this->game.MIN) this->game.updateScoreBot();
            else if(score == this->game.MAX) this->game.updateScorePlayer();

            this->updateScores();
            once = false;
        }

        qp->setOpacity(0.7);
        qp->fillRect(0, 0, this->width(), this->height(), QBrush(Qt::black));

        qp->setOpacity(1);
        qp->setPen(QPen(QBrush(Qt::red), 10));

        font.setPixelSize(Panel::FONTSIZE - 15);
        qp->setFont(font);
        QFontMetrics fm(font);
        int textWidth = fm.horizontalAdvance("WOM X");

        if(this->game.evelution(this->game.getMap()) == this->game.MAX)
            qp->drawText(this->width()/2 - textWidth/2, this->height()/2, "WON X");
        else if(this->game.evelution(this->game.getMap()) == this->game.MIN)
            qp->drawText(this->width()/2 - textWidth/2, this->height()/2, "WON 0");
        else{
            textWidth = fm.horizontalAdvance("DRAW X0");
            qp->drawText(this->width()/2 - textWidth/2, this->height()/2, "DRAW 0X");
        }
    }
}
//End Output
