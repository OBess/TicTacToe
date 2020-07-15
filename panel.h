#ifndef PANEL_H
#define PANEL_H

#include "game.h"

#include <QWidget>
#include <QPoint>
#include <QPushButton>
#include <QLabel>
#include <QRadioButton>
#include <QPainter>
#include <QMouseEvent>
#include <QThread>

class Panel : public QWidget
{
public:
    Panel(QWidget *parent, int offset);
    ~Panel();

    void setResetBTN(QPushButton* pb);
    void setScoreBotLBL(QLabel *lbl);
    void setScorePlayerLBL(QLabel *lbl);
    void setBotVSBotRB(QRadioButton *rb);
    void setBotVSbot(bool toggle);

    void updateCusotmUI();

    void resetGame();

    const int FONTSIZE;
protected:
    void paintEvent(QPaintEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;

private:
    void initButton(QPushButton* btn, std::string text, int width, int height, int posX, int posY);
    void initLabel(QLabel *lbl, std::string text, int posX, int posY);
    void initRadioButton(QRadioButton *rb, std::string text, int posX, int posY);
    void updateScores();
    void draw(QPainter *qp);

    static void gameBotVSBOT(Game* game, Panel* panel, bool* toggle);

    Game game;

    QWidget* parent;
    QPoint sizeRect;

    QPushButton* resetBTN;
    QLabel* scoreBotLBL;
    QLabel* scorePlayerLBL;
    QRadioButton* botVSbotRB;

    bool toggle;
    bool once;
};

#endif // PANEL_H
