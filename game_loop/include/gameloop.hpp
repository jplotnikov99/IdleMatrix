#pragma once

#include "datastructures.hpp"
#include "gamestate.hpp"
#include <QElapsedTimer>
#include <QObject>
#include <QTimer>

class GameLoop : public QObject {
  Q_OBJECT
public:
  explicit GameLoop(GameState &state, QObject *parent = nullptr)
      : QObject(parent), gameState(state) {
    if (gameState.upgrades.size() == 0) {
      gameState.number = NumberData{1, 1};
      gameState.upgrades.push_back(
          UpgradeData{"Addition", 1, 10, 0, 1, 1.2, true,
                      [](int current, int value) { return current + value; }});
      gameState.upgrades.push_back(
          UpgradeData{"Tickspeed", 1, 100, 0, -10, 1.2, false});
    }
  }
  ~GameLoop() = default;

public slots:
  void start();
  void stop();
  void tick();
  void checkForUpgradeUnlock();
  void onUpgradeClicked(QString upgradeName);

signals:
  void stateUpdated(const GameState &state);
  void upgradeUnlockAvailable(const QString &unlockName);

private:
  GameState &gameState;
  QTimer *timer = nullptr;
  QElapsedTimer elapsedTimer;
};