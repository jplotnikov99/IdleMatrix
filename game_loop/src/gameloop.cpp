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
    gameState.currentNumber = gameState.pendingNumber;
    checkForUnlock();

    gameState.pendingNumber = gameState.currentNumber + gameState.additionNumber;
    accumulatedTimeForIncrement = 0;
    gameState.shouldIncrement = true;

    emit stateUpdated(gameState);
  }
}

void GameLoop::checkForUnlock() {
  if (!gameState.upgradeAdditionUnlocked && gameState.currentNumber >= 10) {
    gameState.upgradeAdditionUnlocked = true;
    emit unlockAvailable("Upgrade Addition");
  }
}

void GameLoop::onUpgradeClicked(QString upgradeName) {
  if (upgradeName == "Upgrade Addition" &&
      gameState.currentNumber >= gameState.additionUpgradeCost) {
    gameState.additionNumber += 1;
    gameState.currentNumber -= gameState.additionUpgradeCost;
    gameState.pendingNumber =
        gameState.currentNumber + gameState.additionNumber;
    gameState.additionUpgradeCost =
        static_cast<int>(gameState.additionUpgradeCost * 1.2);
    gameState.shouldIncrement = false;
    emit stateUpdated(gameState);
  }
}