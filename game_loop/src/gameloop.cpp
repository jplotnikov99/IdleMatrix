#include "gameloop.hpp"
#include "datastructures.hpp"
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

    gameState.number.pending =
        gameState.number.current + gameState.upgrades["Addition"].value;

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
  UpgradeData *clickedUpgrade = &gameState.upgrades[upgradeName];
  if (gameState.number.current >= clickedUpgrade->cost) {
    gameState.number.current -= clickedUpgrade->cost;
    clickedUpgrade->value += clickedUpgrade->valueIncreasePerUpgrade;
    gameState.number.pending = gameState.number.current + clickedUpgrade->value;

    clickedUpgrade->cost = static_cast<int>(clickedUpgrade->cost *
                                            clickedUpgrade->costMultPerUpgrade);
    ++clickedUpgrade->level;

    gameState.shouldIncrement = false;
    emit stateUpdated(gameState);
  }
}