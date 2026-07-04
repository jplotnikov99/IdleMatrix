#include "main_window.hpp"
#include "increment_animations.hpp"
#include <QMouseEvent>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
  resize(1000, 1000);
  setStyleSheet("background-color: #222; color: white; font-family: Arial;");
  incrementAnimator = new IncrementAnimator(this);
  connect(incrementAnimator, &IncrementAnimator::animationStep, this,
          [this]() { update(); });
}

void MainWindow::onStateUpdated() {
  incrementAnimator->increment();
}

void MainWindow::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  QFont bigFont = painter.font();
  bigFont.setPointSize(48);

  QRectF fullRect = rect();
  QPointF center = fullRect.center();

  if (!incrementAnimator->isAnimating) {
    painter.setFont(bigFont);
    painter.drawText(fullRect, Qt::AlignCenter,
                     QString::number(incrementAnimator->number));
    return;
  }

  IncrementScalar incrementScalar(center, incrementAnimator->progress(),
                                  incrementAnimator->number,
                                  incrementAnimator->pendingNumber);

  const qreal spread = 80.0;
  qreal progress = incrementAnimator->progress();
  int number = incrementAnimator->number;
  int pending = incrementAnimator->pendingNumber;

  for (auto &character : incrementScalar.characters) {
    painter.setFont(QFont(painter.font().family(), character.fontSize));
    painter.setOpacity(character.opacity);
    painter.drawText(QRectF(character.x, character.y, 200, 100),
                     Qt::AlignCenter, character.text);
  }

  painter.setOpacity(1.0);
}