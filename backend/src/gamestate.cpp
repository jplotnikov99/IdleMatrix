#include "gamestate.hpp"

bool saveGameState(const GameState &state, const QString &filePath) {
  QJsonDocument doc(state.toJson());

  QFile file(filePath);
  if (!file.open(QIODevice::WriteOnly)) {
    return false;
  }
  file.write(doc.toJson());
  return true;
}

bool loadGameState(GameState &outState, const QString &filePath) {
  QFile file(filePath);
  if (!file.open(QIODevice::ReadOnly)) {
    return false; 
  }

  QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
  if (!doc.isObject()) {
    return false;
  }

  outState = GameState::fromJson(doc.object());
  return true;
}