#pragma once

#include "increment_animator.hpp"
#include "gamestate.hpp"
#include <QPropertyAnimation>
#include <QWidget>
#include <QPushButton>

class MainWindow : public QWidget {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);

  ~MainWindow();

public slots:
  void onStateUpdated(const GameState &state);
  void onUnlockAvailable(const QString &unlockName);

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  IncrementAnimator *incrementAnimator;
  QPushButton *upgradeAdditionButton;
  GameState currentGameState;
};