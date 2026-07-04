#pragma once

#include "increment_animator.hpp"
#include "gamestate.hpp"
#include <QPropertyAnimation>
#include <QWidget>

class MainWindow : public QWidget {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);

  ~MainWindow() = default;

public slots:
  void onStateUpdated(const GameState &state);

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  IncrementAnimator *incrementAnimator;
};