#include <QPainter>
#include "Background.h"

Background::Background(int screenWidth, int screenHeight, QGraphicsItem *parent) : QGraphicsPixmapItem(parent),
                                                                                   screenWidth{screenWidth},
                                                                                   screenHeight{screenHeight} {
    moveTimer = new QTimer();
    moveTimer->setInterval(50);
    connect(moveTimer, &QTimer::timeout, this, &Background::moveBackground);
    moveTimer->start();

    QPixmap pixmap(":/images/bg");
    pixmap = pixmap.scaled(pixmap.width(), screenHeight, Qt::KeepAspectRatioByExpanding);
    scaledImage = new QPixmap(pixmap);
    pixmap = pixmap.copy(0, 0, pixmap.width() / 2, screenHeight);
    setPixmap(pixmap);

    setPos(0, 0);
}

void Background::moveBackground() {
    if (scaledImage == nullptr)
        return;
    currentX = (currentX + 5) % scaledImage->width();

    QPixmap croppedImage;
    auto remindingWidth = scaledImage->width() - currentX;
    if (currentX < scaledImage->width() / 2) {
        croppedImage = scaledImage->copy(currentX, 0,
                                         scaledImage->width() / 2, scaledImage->height());
    } else {
        croppedImage = scaledImage->copy(currentX, 0,
                                         remindingWidth, scaledImage->height());
    }

    QPixmap result(QSize(scaledImage->width() / 2, scaledImage->height()));
    QPainter painter(&result);

    painter.drawPixmap(0, 0, croppedImage);
    if (currentX >= scaledImage->width() / 2) {
        auto imageWidth = scaledImage->width() / 2 - remindingWidth;
        auto image = scaledImage->copy(0, 0, imageWidth, scaledImage->height());
        painter.drawPixmap(remindingWidth, 0, image);
    }

    setPixmap(result);
}

Background::~Background() {
    delete moveTimer;
    delete scaledImage;
}

void Background::stopBackground() {
    moveTimer->stop();
}
