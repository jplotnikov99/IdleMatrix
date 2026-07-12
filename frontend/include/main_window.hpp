#pragma once

#include "gamestate.hpp"
#include "increment_animator.hpp"
#include "upgradebuttonwidget.hpp"
#include <QPropertyAnimation>
#include <QPushButton>
#include <QWidget>
#include <qpixmap.h>

class MainWindow : public QWidget {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);

  ~MainWindow();

public slots:
  void onStateUpdated(const GameState &state);
  void onUpgradeUnlockAvailable(const QString &unlockName);

protected:
  void paintEvent(QPaintEvent *event) override;

signals:
  void upgradeClicked(QString upgradeName);

private:
  QPixmap paperTexture;
  IncrementAnimator *incrementAnimator;
  UpgradeButtonWidget *upgradeAdditionButton;
  GameState currentGameState;
};