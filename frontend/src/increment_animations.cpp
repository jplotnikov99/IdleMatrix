#include "increment_animations.hpp"
#include <cmath>

IncrementScalar::IncrementScalar(QPointF &center, qreal progress, int curNumber,
                                 int newNumber, int additionNumber) {
  constexpr qreal outwardsTime = 0.8;
  constexpr qreal inwardsTime = 0.95;

  characters.push_back({48, 1.0, QString::number(curNumber)});
  characters.push_back({28, 1.0, QString::number(additionNumber)});
  characters.push_back({48, 0., "+"});
  if (progress < outwardsTime) {
    qreal t = progress / outwardsTime;

    characters[0].x = center.x() - std::sqrt(t) * spread - 100;
    characters[0].y = center.y() - 50;

    characters[1].x = center.x() - 100;
    characters[1].y = center.y() - 110;

    characters[2].opacity = t;
    characters[2].x = center.x() - 100;
    characters[2].y = center.y() - 50;
  } else if (progress < inwardsTime) {
    qreal t = (progress - outwardsTime) / (inwardsTime - outwardsTime);

    characters[0].x = center.x() + (t - 1) * spread - 100;
    characters[0].y = center.y() - 50;

    characters[1].opacity = 1.0 - t;
    characters[1].x = center.x() - 100;
    characters[1].y = center.y() - 110 + t * t * 80;

    characters[2].opacity = 1.0 - t;
    characters[2].x = center.x() - 100;
    characters[2].y = center.y() - 50;
  } else {
    characters[0].x = center.x() - 100;
    characters[0].y = center.y() - 50;

    characters[1].opacity = 0;
    characters[1].x = center.x() - 100;
    characters[1].y = center.y() - 110;

    characters[2].opacity = 0;
    characters[2].x = center.x() - 100;
    characters[2].y = center.y() - 50;
  }
}