#include "upgradebuttonwidget.hpp"
#include "fontmanager.hpp"
#include <QStyle>
#include <qglobal.h>

UpgradeButtonWidget::UpgradeButtonWidget(const QString &displayName,
                                         QWidget *parent)
    : QWidget(parent) {
  setObjectName("upgradeButton");
  setAttribute(Qt::WA_StyledBackground, true);

  setFixedSize(160, 160);
  setCursor(Qt::PointingHandCursor);

  QString font = FontManager::inkFont();

  m_nameLabel = new QLabel(displayName, this);
  m_nameLabel->setStyleSheet(
      QString("color: #2b2b2b; font-size: 13px; font-weight: "
              "bold; letter-spacing: 1px; font-family: '%1';")
          .arg(font));

  m_levelLabel = new QLabel("Lv. 1", this);
  m_levelLabel->setStyleSheet(
      QString("color: #2b2b2b; font-size: 13px; font-weight: "
              "bold; letter-spacing: 1px; font-family: '%1';")
          .arg(font));

  m_valueLabel = new QLabel("+1", this);
  m_valueLabel->setStyleSheet(
      QString("color: #2b2b2b; font-size: 15px; font-weight: "
              "bold; letter-spacing: 1px; font-family: '%1';")
          .arg(font));

  m_costLabel = new QLabel("Cost: 10", this);
  m_costLabel->setStyleSheet(
      QString("color: #2b2b2b; font-size: 13px; font-weight: "
              "bold; letter-spacing: 1px; font-family: '%1';")
          .arg(font));

  auto *topRow = new QHBoxLayout();
  topRow->addWidget(m_nameLabel);
  topRow->addWidget(m_levelLabel);

  auto *layout = new QVBoxLayout(this);
  layout->setContentsMargins(12, 8, 12, 8);
  layout->setSpacing(2);
  layout->addLayout(topRow);
  layout->addWidget(m_valueLabel);
  layout->addWidget(m_costLabel);

  applyStyle(false);
}

void UpgradeButtonWidget::updateData(const UpgradeData &data) {
  m_valueLabel->setText(QString("+%1").arg(data.value));
  m_costLabel->setText(QString("Cost: %1").arg(data.cost));
  m_levelLabel->setText(QString("Lv. %1").arg(data.level));

  setEnabled(data.unlocked);
  setVisible(data.unlocked);
}

void UpgradeButtonWidget::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    emit clicked();
  }
}

void UpgradeButtonWidget::enterEvent(QEnterEvent *event) {
  Q_UNUSED(event);
  applyStyle(true);
}

void UpgradeButtonWidget::leaveEvent(QEvent *event) {
  Q_UNUSED(event);
  applyStyle(false);
}

void UpgradeButtonWidget::applyStyle(bool hovered) {
  QString border = hovered ? "#828080" : "#2b2b2b";
  setStyleSheet(
      QString("#upgradeButton { background-color: transparent; border: "
              "1px solid %1; border-radius: 8px; }")
          .arg(border));
}