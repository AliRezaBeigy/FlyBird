#ifndef FLYBIRD_BACKGROUND_H
#define FLYBIRD_BACKGROUND_H

#include <QTimer>
#include <QGraphicsPixmapItem>

class Background : public QObject, public QGraphicsPixmapItem {
Q_OBJECT

private:
    int currentX{};
    QTimer *moveTimer;
    int screenWidth{};
    int screenHeight{};
    QPixmap *scaledImage{};
    bool initialized{false};

public:
    Background(int screenWidth, int screenHeight, QGraphicsItem *parent = nullptr);

    ~Background();


public slots:

    void stopBackground();

    void moveBackground();
};


#endif //FLYBIRD_BACKGROUND_H
