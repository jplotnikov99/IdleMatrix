#include "gameloop.hpp"

void GameLoop::start() {
  timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &GameLoop::tick);
  timer->start(16); // Approximately 60 FPS
  elapsedTimer.start();
}

void GameLoop::stop() {
  if (timer) {
    timer->stop();
  }
}

void GameLoop::tick() { 
    static qint64 accumulatedTimeForIncrement = 0;
    qint64 dt = elapsedTimer.restart();
    accumulatedTimeForIncrement += dt;

    if (accumulatedTimeForIncrement >= gameState.incrementDelayInMs) {
        accumulatedTimeForIncrement = 0;
        emit stateUpdated(gameState);
    }
}