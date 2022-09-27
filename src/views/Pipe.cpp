#include "Pipe.h"
#include <QPainter>
#include <QGraphicsScene>

Pipe::Pipe(int sceneWidth, int sceneHeight, QGraphicsItem *parent) {
    QPixmap scaledPipe(":/images/pipe");
    scaledPipe = scaledPipe.scaled(scaledPipe.width(), sceneHeight, Qt::KeepAspectRatioByExpanding);

    auto pipe = new QPixmap(scaledPipe);
    pipe->fill(QColor::fromRgb(0, 0, 0, 0));

    QPainter painter(pipe);

    auto padding = 300;
    auto spaceHeight = 300;
    auto spaceY = (rand() % (sceneHeight - padding * 2)) + padding;

    auto topPipe = scaledPipe.copy(0, 0, scaledPipe.width(), spaceY);
    auto rotateTransform = QTransform();
    rotateTransform.rotate(180);
    topPipe = topPipe.transformed(rotateTransform);
    painter.drawPixmap(0, 0, topPipe);

    auto bottomPipeHeight = scaledPipe.height() - (spaceY + spaceHeight);
    auto bottomPipe = scaledPipe.copy(0, 0, scaledPipe.width(), bottomPipeHeight);
    painter.drawPixmap(0, spaceY + spaceHeight, bottomPipe);

    setPixmap(*pipe);
    setPos(sceneWidth, 0);

    moveAnimator = new QPropertyAnimation(this, "x", this);
    moveAnimator->setStartValue(sceneWidth);
    moveAnimator->setEndValue(-1 * scaledPipe.width());
    moveAnimator->setDuration(3000);
    moveAnimator->start();
    connect(moveAnimator, &QPropertyAnimation::finished, this, &Pipe::deletePipe);
}

Pipe::~Pipe() {
    delete moveAnimator;
}

void Pipe::deletePipe() {
    delete this;
}

void Pipe::stopPipe() {
    moveAnimator->stop();
}
