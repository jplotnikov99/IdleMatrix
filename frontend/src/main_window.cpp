#include "main_window.hpp"
#include "increment_animations.hpp"
#include "upgradebuttonwidget.hpp"
#include <QMouseEvent>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
  resize(1000, 1000);
  setStyleSheet("background-color: #222; color: white; font-family: Arial;");

  incrementAnimator = new IncrementAnimator(this);
  connect(incrementAnimator, &IncrementAnimator::animationStep, this,
          [this]() { update(); });

  upgradeAdditionButton = new UpgradeButtonWidget("Addition", this);
  upgradeAdditionButton->move(20, 20);
  connect(upgradeAdditionButton, &UpgradeButtonWidget::clicked, this,
          [this]() { emit upgradeClicked("Addition"); });
}

void MainWindow::onStateUpdated(const GameState &state) {
  currentGameState = state;
  upgradeAdditionButton->updateData(currentGameState.upgrades["Addition"]);
  if (state.shouldIncrement) {
    incrementAnimator->increment(currentGameState);
  }
}

void MainWindow::onUpgradeUnlockAvailable(const QString &unlockName) {
  if (unlockName == "Addition") {
    upgradeAdditionButton->show();
  }
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
                     QString::number(currentGameState.number.current));
    return;
  }

  IncrementScalar incrementScalar(center, incrementAnimator->progress(),
                                  currentGameState.number.current,
                                  currentGameState.number.pending,
                                  currentGameState.upgrades["Addition"].value);
  const qreal spread = 80.0;
  qreal progress = incrementAnimator->progress();

  for (auto &character : incrementScalar.characters) {
    painter.setFont(QFont(painter.font().family(), character.fontSize));
    painter.setOpacity(character.opacity);
    painter.drawText(QRectF(character.x, character.y, 200, 100),
                     Qt::AlignCenter, character.text);
  }

  painter.setOpacity(1.0);
}

MainWindow::~MainWindow() {
  QString saveDir =
      QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
  QDir().mkpath(saveDir); // ensure the directory exists
  QString savePath = saveDir + "/savegame.json";
  saveGameState(currentGameState, savePath);
  delete incrementAnimator;
  delete upgradeAdditionButton;
}