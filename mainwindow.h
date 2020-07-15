#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPainter>
#include "panel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_resetBTN_clicked();

    void on_botVSbotRB_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    Panel* panel;

    const int winW = 500;
    const int winH = 400;
    const int offset = 100;
};
#endif // MAINWINDOW_H
