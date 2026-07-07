#pragma once

#include <QJsonObject>
#include <QFile>
#include <QJsonDocument>
#include <QStandardPaths>
#include <QDir>

struct GameState {
public:
  GameState() = default;

  int currentNumber = 0;
  int pendingNumber = 0;
  int additionNumber = 1;
  int additionUpgradeCost = 10;

  int incrementDelayInMs = 1300;

  bool shouldIncrement = true;

  bool upgradeAdditionUnlocked = false;

  QJsonObject toJson() const {
    QJsonObject obj;
    obj["currentNumber"] = currentNumber;
    obj["additionNumber"] = additionNumber;
    obj["additionUpgradeCost"] = additionUpgradeCost;
    obj["incrementDelayInMs"] = incrementDelayInMs;
    return obj;
  }

  static GameState fromJson(const QJsonObject &obj) {
    GameState state;
    state.currentNumber = obj["currentNumber"].toInt();
    state.pendingNumber = state.currentNumber; // Ensure pendingNumber is initialized
    state.additionNumber = obj["additionNumber"].toInt();
    state.additionUpgradeCost = obj["additionUpgradeCost"].toInt();
    state.incrementDelayInMs = obj["incrementDelayInMs"].toInt();
    return state;
  }

  ~GameState() = default;
};

bool saveGameState(const GameState &state, const QString &filePath);

bool loadGameState(GameState &outState, const QString &filePath);
