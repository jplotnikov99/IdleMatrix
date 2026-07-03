#include "increment_animations.hpp"

IncrementScalar::IncrementScalar(QPointF &center, qreal progress, int curNumber,
                                 int newNumber) {
  characters.push_back({48, 1.0, QString::number(curNumber)});
  characters.push_back({28, 1.0, "1"});
  characters.push_back({48, 0., "+"});
  if (progress < 0.5) {
    qreal t = progress / 0.5;

    characters[0].x = center.x() - t * spread - 100;
    characters[0].y = center.y() - 50;

    characters[1].x = center.x() - 100;
    characters[1].y = center.y() - 110;

    characters[2].opacity = t;
    characters[2].x = center.x() - 100;
    characters[2].y = center.y() - 50;
  } else {
    qreal t = (progress - 0.5) / 0.5;
    characters[0].x = center.x() - spread + t * spread - 100;
    characters[0].y = center.y() - 50;

    characters[1].opacity = 1.0 - t;
    characters[1].x = center.x() - 100;
    characters[1].y = center.y() - 110 + t * t * 80;

    characters[2].opacity = 1.0 - t;
    characters[2].x = center.x() - 100;
    characters[2].y = center.y() - 50;
  }
}