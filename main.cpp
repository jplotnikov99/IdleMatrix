#include "gameloop.hpp"
#include "main_window.hpp"
#include <QApplication>
#include <QThread>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QThread gameLoopThread;
  GameLoop gameLoop;
  gameLoop.moveToThread(&gameLoopThread);

  MainWindow window;

  QObject::connect(&gameLoopThread, &QThread::started, &gameLoop,
                   &GameLoop::start);
  QObject::connect(&gameLoop, &GameLoop::stateUpdated, &window,
                   &MainWindow::onStateUpdated);

  gameLoopThread.start();
  window.show();

  int result = app.exec();

  QMetaObject::invokeMethod(&gameLoop, "stop", Qt::QueuedConnection);
  gameLoopThread.quit();
  gameLoopThread.wait();

  return result;
}