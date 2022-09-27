#include "src/Game.h"
#include <QPushButton>
#include <QApplication>
#include <ctime>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    srand(time(nullptr));

    auto game = new Game();
    game->show();

    return QApplication::exec();
}
