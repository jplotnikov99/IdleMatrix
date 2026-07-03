#include "main_window.hpp"
#include <QMouseEvent>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
  resize(1000, 1000);
  setStyleSheet("background-color: #222; color: white; font-family: Arial;");
  incrementAnimator = new IncrementAnimator(this);
  connect(incrementAnimator, &IncrementAnimator::animationStep, this,
          [this]() { update(); });
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    incrementAnimator->increment();
  }
}

void MainWindow::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  QFont bigFont = painter.font();
  bigFont.setPointSize(48);
  QFont smallFont = painter.font();
  smallFont.setPointSize(28);

  QRectF fullRect = rect();
  QPointF center = fullRect.center();

  if (!incrementAnimator->isAnimating) {
    painter.setFont(bigFont);
    painter.drawText(fullRect, Qt::AlignCenter,
                     QString::number(incrementAnimator->number));
    return;
  }

  const qreal spread = 80.0;
  qreal progress = incrementAnimator->progress();
  int number = incrementAnimator->number;
  int pending = incrementAnimator->pendingNumber;

  if (progress < 0.5) {
    qreal t = progress / 0.5;

    qreal oldX = center.x() - t * spread;
    painter.setFont(bigFont);
    painter.setOpacity(1.0);
    painter.drawText(QRectF(oldX - 100, center.y() - 50, 200, 100),
                     Qt::AlignCenter, QString::number(number));

    painter.setOpacity(t);
    painter.drawText(QRectF(center.x() - 100, center.y() - 50, 200, 100),
                     Qt::AlignCenter, "+");

    painter.setFont(smallFont);
    painter.drawText(QRectF(center.x() - 100, center.y() - 130, 200, 80),
                     Qt::AlignCenter, "1");
  } else {
    qreal t = (progress - 0.5) / 0.5;

    qreal oldX = (center.x() - spread) + t * spread;
    painter.setFont(bigFont);
    painter.setOpacity(1.0 - t);
    painter.drawText(QRectF(oldX - 100, center.y() - 50, 200, 100),
                     Qt::AlignCenter, QString::number(number));

    painter.setOpacity(1.0 - t);
    painter.drawText(QRectF(center.x() - 100, center.y() - 50, 200, 100),
                     Qt::AlignCenter, "+");

    qreal oneY = (center.y() - 130) + t * 80;
    painter.setFont(smallFont);
    painter.setOpacity(1.0 - t);
    painter.drawText(QRectF(center.x() - 100, oneY, 200, 80), Qt::AlignCenter,
                     "1");

    painter.setFont(bigFont);
    painter.setOpacity(t);
    painter.drawText(QRectF(center.x() - 100, center.y() - 50, 200, 100),
                     Qt::AlignCenter, QString::number(pending));
  }

  painter.setOpacity(1.0);
}