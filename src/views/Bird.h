#ifndef FLYBIRD_BIRD_H
#define FLYBIRD_BIRD_H

#include <QList>
#include <QTimer>
#include <QObject>
#include <QPropertyAnimation>
#include <QGraphicsPixmapItem>
#include "../Game.h"

class Bird : public QObject, public QGraphicsPixmapItem {
Q_OBJECT
    Q_PROPERTY(qreal height READ y WRITE setY)

private:
    Game *game;
    int frame{};
    int groundY{};
    QTimer *winingTimer;
    QList<QPixmap *> frames{};

    QPropertyAnimation *heightAnimator;

public:
    Bird(Game *game, int sceneWidth, int sceneHeight, QGraphicsItem *parent = nullptr);

    ~Bird();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void jump();

protected:
    void keyPressEvent(QKeyEvent *event) override;

public slots:

    void wining();

    void gravity();
    void stopBird();
};


#endif //FLYBIRD_BIRD_H
