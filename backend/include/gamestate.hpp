#pragma once

#include "datastructures.hpp"
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>
#include <qjsonobject.h>
#include <qmap.h>
#include <vector>

struct GameState {
public:
  GameState() = default;

  NumberData number;
  std::vector<UpgradeData> upgrades;

  int incrementDelayInMs = 1300;

  bool shouldIncrement = true;

  QJsonObject toJson() const {
    QJsonObject obj;

    obj["number"] = number.toJson();

    QJsonObject upgradesObj;
    for (auto &it : upgrades) {
      upgradesObj[it.name] = it.toJson();
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
      state.upgrades.push_back(UpgradeData::fromJson(it.value().toObject()));
    }

    return state;
  }

  ~GameState() = default;
};

bool saveGameState(const GameState &state, const QString &filePath);

bool loadGameState(GameState &outState, const QString &filePath);
