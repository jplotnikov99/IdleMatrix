#pragma once

#include <QJsonObject>
#include <functional>
#include <iostream>

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

static const QMap<QString, std::function<int(int, int)>> kRuleRegistry = {
    {"Addition", [](int c, int v) { return c + v; }},
    {"Tickspeed", [](int c, int v) { return c * v; }},
};

struct UpgradeData {
  QString name;
  int value;
  int cost;
  int numberOfUpgrades;
  int valueIncreasePerUpgrade;
  double costMultPerUpgrade;
  bool unlocked;

  std::function<int(int, int)> rule;

  int computePendingNumber(int currentNumber, int pendingNumber) const {
    if (unlocked) {
      std::cout << name.toStdString() << "\n";
      std::cout << value << "\n";
      return rule(currentNumber, value);
    }
    return pendingNumber;
  }

  QJsonObject toJson() const {
    QJsonObject obj;
    obj["name"] = name;
    obj["value"] = value;
    obj["cost"] = cost;
    obj["numberOfUpgrades"] = numberOfUpgrades;
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
    data.numberOfUpgrades = obj["numberOfUpgrades"].toInt();
    data.valueIncreasePerUpgrade = obj["valueIncreasePerUpgrade"].toInt();
    data.costMultPerUpgrade = obj["costMultPerUpgrade"].toDouble();
    data.unlocked = obj["unlocked"].toBool();
    data.rule = kRuleRegistry[data.name];
    return data;
  }
};