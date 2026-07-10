#pragma once

#include <QJsonObject>

struct NumberData {
  int current = 0;
  int pending = 0;

  QJsonObject toJson() const {
    QJsonObject obj;
    obj["current"] = current;
    obj["pending"] = pending;
    return obj;
  }

  static NumberData fromJson(const QJsonObject &obj) {
    NumberData data;
    data.current = obj["current"].toInt();
    data.pending = obj["pending"].toInt();
    return data;
  }
};

struct UpgradeData {
  QString name;
  int value;
  int cost;
  int level;
  int valueIncreasePerUpgrade;
  double costMultPerUpgrade;
  bool unlocked;

  QJsonObject toJson() const {
    QJsonObject obj;
    obj["name"] = name;
    obj["value"] = value;
    obj["cost"] = cost;
    obj["level"] = level;
    obj["valueIncreasePerUpgrade"] = valueIncreasePerUpgrade;
    obj["costMultPerUpgrade"] = costMultPerUpgrade;
    obj["unlocked"] = unlocked;
    return obj;
  }

  static UpgradeData fromJson(const QJsonObject &obj) {
    UpgradeData data;
    data.name = obj["name"].toString();
    data.value = obj["value"].toInt();
    data.cost = obj["cost"].toInt();
    data.level = obj["level"].toInt();
    data.valueIncreasePerUpgrade = obj["valueIncreasePerUpgrade"].toInt();
    data.costMultPerUpgrade = obj["costMultPerUpgrade"].toDouble();
    data.unlocked = obj["unlocked"].toBool();
    return data;
  }
};