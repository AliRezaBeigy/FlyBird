#ifndef FLYBIRD_PIPE_H
#define FLYBIRD_PIPE_H

#include <QTimer>
#include <QObject>
#include <QPropertyAnimation>
#include <QGraphicsPixmapItem>

class Pipe : public QObject, public QGraphicsPixmapItem {
Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)

private:
    QPropertyAnimation *moveAnimator;

public:
    Pipe(int sceneWidth, int sceneHeight, QGraphicsItem *parent = nullptr);

    ~Pipe();


public slots:

    void stopPipe();
    void deletePipe();
};


#endif //FLYBIRD_PIPE_H
