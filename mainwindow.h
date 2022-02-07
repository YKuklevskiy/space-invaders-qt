#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gameobject.h"
#include "spaceship.h"
#include "gamemanager.h"
#include "textureholder.h"
#include "gameui.h"
#include <QTime>
#include <chrono>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#define chr std::chrono

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent *event);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);


public slots:
    void update();

private:
    Ui::MainWindow *ui;

    TextureHolder* TH = nullptr;
    GameManager* GM = nullptr;
    GameUI* GUI = nullptr;
    bool input[3] = {0, 0, 0}; // left, right, space

    // for gameloop
    const int frameDeltaTimeMS = 8; // target is approximately 125 fps
    QTimer* timer = nullptr;
    chr::time_point<chr::steady_clock> curTime;

    // just for fps display
    chr::time_point<chr::steady_clock> fpsCheckTime;
    short elapsedFrames = 0;
    const short fpsCalcFramesThreshold = 120;
    void displayFPS();

};
#endif // MAINWINDOW_H
