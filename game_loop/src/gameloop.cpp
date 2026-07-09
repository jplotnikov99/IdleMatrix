#include "gameloop.hpp"
#include "gamestate.hpp"

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
    gameState.number.current = gameState.number.pending;
    checkForUpgradeUnlock();

    for (auto it : gameState.upgrades) {
      gameState.number.pending = it.computePendingNumber(
          gameState.number.current, gameState.number.pending);
    }

    accumulatedTimeForIncrement = 0;
    gameState.shouldIncrement = true;

    emit stateUpdated(gameState);
  }
}

void GameLoop::checkForUpgradeUnlock() {
  for (auto &it : gameState.upgrades) {
    if (!it.unlocked && gameState.number.current >= it.cost) {
      it.unlocked = true;
      emit upgradeUnlockAvailable(it.name);
    }
  }
}

void GameLoop::onUpgradeClicked(QString upgradeName) {
  for (auto &it : gameState.upgrades) {
    if (upgradeName == it.name && gameState.number.current >= it.cost) {
      it.value += it.valueIncreasePerUpgrade;
      gameState.number.current -= it.cost;
      gameState.number.pending = gameState.number.current + it.value;
      it.cost = static_cast<int>(it.cost * it.costMultPerUpgrade);
      gameState.shouldIncrement = false;
      emit stateUpdated(gameState);
    }
  }
}