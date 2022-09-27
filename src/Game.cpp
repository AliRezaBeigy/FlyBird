#include "Game.h"
#include "views/Bird.h"
#include "views/Background.h"
#include <QGraphicsView>

Game::Game() {
    showFullScreen();
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    auto gameScene = new QGraphicsScene(this);
    setScene(gameScene);
    gameScene->setBackgroundBrush(QColor("#FEF0CF"));

    auto playground = new QGraphicsView();
    playground->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    playground->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    playground->setFrameShape(QFrame::NoFrame);

    playgroundScene = new QGraphicsScene(this);
    playground->setScene(playgroundScene);

    auto background = new Background(width(), height());
    playgroundScene->addItem(background);

    auto backgroundWidth = background->boundingRect().width();
    playgroundScene->setSceneRect(0, 0, backgroundWidth, height());
    playground->setFixedSize(backgroundWidth, height());
    playground->move(width() / 2 - backgroundWidth / 2, 0);
    gameScene->addWidget(playground);
    playground->setFocus();

    auto bird = new Bird(this, playgroundScene->width(), playgroundScene->height());
    playgroundScene->addItem(bird);

    connect(this, &Game::gameStopped, bird, &Bird::stopBird);
    connect(this, &Game::gameStopped, background, &Background::stopBackground);

    pipeGeneratorTimer = new QTimer();
    pipeGeneratorTimer->setInterval(2000);
    QObject::connect(pipeGeneratorTimer, &QTimer::timeout, this, &Game::AddPipe);
    pipeGeneratorTimer->start();
}

void Game::AddPipe() {
    pipes.append(new Pipe(playgroundScene->width(), playgroundScene->height()));
    playgroundScene->addItem(pipes.last());
    connect(this, &Game::gameStopped, pipes.last(), &Pipe::stopPipe);
}


void Game::stopGame() {
    if (isGameOver == true)
        return;
    isGameOver = true;
    pipeGeneratorTimer->stop();
    emit gameStopped();

    scene()->addRect(0, 0, width(), height(), QPen(), QColor::fromRgb(25, 25, 25, 65));
    auto gameOverItem = scene()->addPixmap(QPixmap(":/images/game-over"));
    gameOverItem->setPos(width() / 2 - gameOverItem->pixmap().width() / 2,
                         height() / 2 - gameOverItem->pixmap().width() / 2);
}
