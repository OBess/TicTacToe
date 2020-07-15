#include "mainwindow.h"
#include "ui_mainwindow.h"

//Initial
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    resize(winW, winH);
    setMinimumSize(winW, winH);
    setMaximumSize(winW, winH);

    panel = new Panel(this, offset);
    panel->setResetBTN(ui->resetBTN);
    panel->setScoreBotLBL(ui->scoreBot);
    panel->setScorePlayerLBL(ui->scorePlayer);
    panel->setBotVSBotRB(ui->botVSbotRB);
    panel->updateCusotmUI();
}

MainWindow::~MainWindow()
{
    delete panel;
    delete ui;
}
//End initial

//Slots
void MainWindow::on_resetBTN_clicked()
{
    panel->resetGame();
}
void MainWindow::on_botVSbotRB_toggled(bool checked)
{
    panel->setBotVSbot(checked);
}
//End slots
