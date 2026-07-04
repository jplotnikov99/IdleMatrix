#include "increment_animator.hpp"

IncrementAnimator::IncrementAnimator(QObject *parent)
    : QObject(parent)
{
    m_animation = new QPropertyAnimation(this, "progress", this);
    m_animation->setDuration(900);
    m_animation->setStartValue(0.0);
    m_animation->setEndValue(1.0);
    m_animation->setEasingCurve(QEasingCurve::InOutQuad);

    connect(m_animation, &QPropertyAnimation::finished, this, [this]() {
        number = pendingNumber;
        isAnimating = false;
        emit animationStep();
    });
}

void IncrementAnimator::setProgress(qreal progress)
{
    m_progress = progress;
    emit animationStep();
}

void IncrementAnimator::increment(const GameState &state)
{
    m_animation->setDuration(state.incrementDelayInMs);
    if (isAnimating) {
        // snap current animation to completion, then chain the next one
        m_animation->stop();
        number = pendingNumber;
        isAnimating = false;
    }

    pendingNumber = number + 1;
    isAnimating = true;
    m_animation->start();
}