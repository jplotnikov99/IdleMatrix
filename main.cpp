#include "gameloop.hpp"
#include "gamestate.hpp"
#include "main_window.hpp"
#include <QApplication>
#include <QThread>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QString saveDir =
      QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
  QDir().mkpath(saveDir); // ensure the directory exists
  QString savePath = saveDir + "/savegame.json";

  GameState gameState, loadedState;

  bool isLoaded = loadGameState(loadedState, savePath);

  if (isLoaded) {
    gameState = loadedState;
  }

  QThread gameLoopThread;
  GameLoop gameLoop(gameState, isLoaded);
  gameLoop.moveToThread(&gameLoopThread);

  MainWindow window;

  QObject::connect(&gameLoopThread, &QThread::started, &gameLoop,
                   &GameLoop::start);
  QObject::connect(&gameLoop, &GameLoop::stateUpdated, &window,
                   &MainWindow::onStateUpdated);
  QObject::connect(&gameLoop, &GameLoop::upgradeUnlockAvailable, &window,
                   &MainWindow::onUpgradeUnlockAvailable);
  QObject::connect(&window, &MainWindow::upgradeClicked, &gameLoop,
                   &GameLoop::onUpgradeClicked);

  gameLoopThread.start();
  window.show();

  int result = app.exec();

  QMetaObject::invokeMethod(&gameLoop, "stop", Qt::QueuedConnection);
  gameLoopThread.quit();
  gameLoopThread.wait();

  return result;
}