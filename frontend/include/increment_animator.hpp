#pragma once

#include <QObject>
#include <QPropertyAnimation>

class IncrementAnimator: public QObject {
  Q_OBJECT
  Q_PROPERTY(qreal progress READ progress WRITE setProgress)
public:
  explicit IncrementAnimator(QObject *parent = nullptr);

  int number = 0;
  int pendingNumber = 0;
  qreal m_progress = 0.0;
  bool isAnimating = false;

  qreal progress() const { return m_progress; }
  void setProgress(qreal progress);

  ~IncrementAnimator() = default;

public slots:
  void increment();

signals:
  void animationStep(); // fired every time something visual needs to change

private:
  QPropertyAnimation *m_animation;
};
