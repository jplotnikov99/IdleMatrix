#pragma once

#include "gamestate.hpp"
#include <QElapsedTimer>
#include <QObject>
#include <QTimer>

class GameLoop : public QObject {
  Q_OBJECT
public:
  explicit GameLoop(GameState &state, QObject *parent = nullptr)
      : QObject(parent), gameState(state) {}
  ~GameLoop() = default;

public slots:
  void start();
  void stop();
  void tick();

signals:
  void stateUpdated(const GameState &state);

private:
  GameState &gameState;
  QTimer *timer = nullptr;
  QElapsedTimer elapsedTimer;
};