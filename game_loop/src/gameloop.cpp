#include "gameloop.hpp"

void GameLoop::start() {
  timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &GameLoop::tick);
  timer->start(1000); // Approximately 60 FPS
  elapsedTimer.start();
}

void GameLoop::stop() {
  if (timer) {
    timer->stop();
  }
}

void GameLoop::tick() { 
    emit stateUpdated();
}