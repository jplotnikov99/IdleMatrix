#pragma once

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>

class GameLoop : public QObject {
  Q_OBJECT
public:
  explicit GameLoop(QObject *parent = nullptr) : QObject(parent) {}
  ~GameLoop() = default;

public slots:
  void start();
  void stop();
  void tick();

signals:
  void stateUpdated();

private:
  QTimer *timer = nullptr;
  QElapsedTimer elapsedTimer;
};