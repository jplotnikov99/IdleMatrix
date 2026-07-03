#pragma once

#include "increment_animator.hpp"
#include <QPropertyAnimation>
#include <QWidget>

class MainWindow : public QWidget {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);

  ~MainWindow() = default;

protected:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;

private:
  IncrementAnimator *incrementAnimator;
};