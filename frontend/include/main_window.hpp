#pragma once

#include "gamestate.hpp"
#include "increment_animator.hpp"
#include <QPropertyAnimation>
#include <QPushButton>
#include <QWidget>

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

signals:
  void upgradeClicked(QString upgradeName);

private:
  IncrementAnimator *incrementAnimator;
  QPushButton *upgradeAdditionButton;
  GameState currentGameState;
};