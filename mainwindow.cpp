#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <QList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    setFixedSize(QSize(800, 600));
    ui->setupUi(this);
    setMouseTracking(true);

    TH = new TextureHolder();
    GM = new GameManager(TH, rect());
    GUI = new GameUI(GM, rect());

    curTime = chr::steady_clock::now();
    fpsCheckTime = chr::steady_clock::now();

    timer = new QTimer(this);
    timer->connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(frameDeltaTimeMS);
}

MainWindow::~MainWindow()
{
    delete ui;
}

const QColor skyColor = QColor(15, 5, 35);

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(painter.Antialiasing, true);

    painter.setBrush(QBrush(skyColor));
    painter.drawRect(rect());
    painter.setBrush(QBrush(Qt::GlobalColor::transparent));

    painter.save();
    // inverting coordinate system
    painter.translate(this->rect().bottomLeft());
    painter.scale(1, -1);

    GM->render(&painter);

    painter.restore();

    GUI->drawUI(&painter);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(!event) return;

    Qt::Key keyPressed = Qt::Key(event->key());
    switch (keyPressed) {
    case Qt::Key_Left:
        input[0] = true;
        break;
    case Qt::Key_Right:
        input[1] = true;
        break;
    case Qt::Key_Space:
        input[2] = true;
        break;
    default:
        break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(!event) return;

    Qt::Key keyPressed = Qt::Key(event->key());
    switch (keyPressed) {
    case Qt::Key_Left:
        input[0] = false;
        break;
    case Qt::Key_Right:
        input[1] = false;
        break;
    case Qt::Key_Space:
        input[2] = false;
        break;
    default:
        break;
    }
}

void MainWindow::update()
{
    displayFPS();

    int deltaTime_mS;
    auto chronoDelta = (chr::steady_clock::now()-curTime);
    deltaTime_mS = chr::duration_cast<chr::microseconds>(chronoDelta).count();
    const float mS_to_S = 0.000001;
    float deltaTimeFloat = deltaTime_mS*mS_to_S;
    //qDebug() << deltaTimeFloat;
    curTime = chr::steady_clock::now();

    GM->handleInputs(input);
    GM->enumerate(deltaTimeFloat, rect());
    GM->checkCollisions();
    GM->move();
    repaint();
}

void MainWindow::displayFPS()
{
    if(elapsedFrames >= fpsCalcFramesThreshold)
    {
        int timeMS = chr::duration_cast<chr::microseconds>(chr::steady_clock::now() - fpsCheckTime).count();

        qDebug() << "FPS: " << (float) fpsCalcFramesThreshold / (timeMS*0.000001);

        fpsCheckTime = chr::steady_clock::now();
        elapsedFrames = 0;
    }
    else elapsedFrames++;
}
