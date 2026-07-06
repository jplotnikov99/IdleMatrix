#pragma once

struct GameState {
public:
  GameState() = default;

  int currentNumber = 0;
  int pendingNumber = 0;
  int additionNumber = 1;

  long incrementDelayInMs = 1300;
  
  bool upgradeAdditionUnlocked = false;

  ~GameState() = default;
};
