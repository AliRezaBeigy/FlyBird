#ifndef FLYBIRD_GAME_H
#define FLYBIRD_GAME_H

#include <QList>
#include "views/Pipe.h"
#include <QGraphicsView>

class Game : public QGraphicsView {
Q_OBJECT

private:
    bool isGameOver{false};
    QList<Pipe *> pipes{};
    QTimer *pipeGeneratorTimer;
    QGraphicsScene *playgroundScene;

public:
    Game();

    void stopGame();

signals:

    void gameStopped();

public slots:

    void AddPipe();
};


#endif //FLYBIRD_GAME_H
