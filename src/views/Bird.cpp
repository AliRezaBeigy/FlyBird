#include "Bird.h"
#include "Pipe.h"
#include <QKeyEvent>
#include <QGraphicsScene>

Bird::Bird(Game *game, int sceneWidth, int sceneHeight, QGraphicsItem *parent) : game{game},
                                                                                 QGraphicsPixmapItem(parent) {
    setFlags(GraphicsItemFlag::ItemIsFocusable);
    setFocus();

    auto pixmap = new QPixmap(":/images/bird-1");
    auto scaledPixmap = pixmap->scaled(79, 65);
    setPixmap(scaledPixmap);

    frames.append(new QPixmap(scaledPixmap));
    pixmap = new QPixmap(":/images/bird-2");
    scaledPixmap = pixmap->scaled(79, 65);
    frames.append(new QPixmap(scaledPixmap));

    winingTimer = new QTimer();
    winingTimer->setInterval(100);
    connect(winingTimer, &QTimer::timeout, this, &Bird::wining);
    winingTimer->start();

    auto x = sceneWidth / 2 - scaledPixmap.width() / 2;
    auto y = sceneHeight / 2 - scaledPixmap.height() / 2;

    heightAnimator = new QPropertyAnimation(this, "height", this);
    heightAnimator->setStartValue(y);
    heightAnimator->setEndValue(y);
    heightAnimator->setDuration(500);
    heightAnimator->start();
    connect(heightAnimator, &QPropertyAnimation::finished, this, &Bird::gravity);

    groundY = sceneHeight - 100;

    setPos(x, y);
}

void Bird::wining() {
    setPixmap(*frames.at(frame));
    frame = (frame + 1) % 2;
}

void Bird::gravity() {
    heightAnimator->stop();
    heightAnimator->setStartValue(y());
    heightAnimator->setEndValue(groundY);
    heightAnimator->setDuration(1000);
    heightAnimator->setEasingCurve(QEasingCurve::InQuad);
    heightAnimator->start();
}

void Bird::jump() {
    heightAnimator->stop();
    heightAnimator->setStartValue(y());
    heightAnimator->setEndValue(y() - 100);
    heightAnimator->setDuration(500);
    heightAnimator->setEasingCurve(QEasingCurve::OutQuad);
    heightAnimator->start();
}

void Bird::keyPressEvent(QKeyEvent *event) {
    QGraphicsItem::keyPressEvent(event);

    if (event->key() == Qt::Key::Key_Space) {
        jump();
    }
}

Bird::~Bird() {
    qDeleteAll(frames);
    delete winingTimer;
    delete heightAnimator;
}

void Bird::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QGraphicsPixmapItem::paint(painter, option, widget);
    QList<QGraphicsItem *> list = collidingItems();

    for (QGraphicsItem *i: list) {
        Pipe *item = dynamic_cast<Pipe *>(i);
        if (item != NULL) {
            game->stopGame();
        }
    }
}

void Bird::stopBird() {
    winingTimer->stop();
    heightAnimator->stop();
}
