#pragma once

#include "datastructures.hpp"
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>
#include <qjsonobject.h>
#include <qmap.h>

struct GameState {
public:
  GameState() = default;

  NumberData number;
  QMap<QString, UpgradeData> upgrades;

  int incrementDelayInMs = 1300;

  bool shouldIncrement = true;

  QJsonObject toJson() const {
    QJsonObject obj;

    obj["number"] = number.toJson();

    QJsonObject upgradesObj;
    for (auto it = upgrades.constBegin(); it != upgrades.constEnd(); ++it) {
      upgradesObj[it.key()] = it.value().toJson();
    }
    obj["upgrades"] = upgradesObj;

    return obj;
  }

  static GameState fromJson(const QJsonObject &obj) {
    GameState state;
    state.number = NumberData::fromJson(obj["number"].toObject());

    QJsonObject upgradesObj = obj["upgrades"].toObject();
    for (auto it = upgradesObj.constBegin(); it != upgradesObj.constEnd();
         ++it) {
      state.upgrades[it.key()] = UpgradeData::fromJson(it.value().toObject());
    }

    return state;
  }

  ~GameState() = default;
};

bool saveGameState(const GameState &state, const QString &filePath);

bool loadGameState(GameState &outState, const QString &filePath);
