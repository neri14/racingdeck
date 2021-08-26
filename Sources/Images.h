#pragma once

#include <string>
#include "GameState.h"

namespace Images {

    const std::string& getImage(GameState::Headlights headlights);
    const std::string& getImage(GameState::RainLight rainLight);
    const std::string& getImage(GameState::Wipers wipers);

} // namespace Images
