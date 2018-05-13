#pragma once

#include <memory>


class Scene {
public:
  int width = 0;
  int height = 0;

  Scene (void);

  void draw (void);
};
