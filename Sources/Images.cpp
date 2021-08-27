#include "Images.h"
#include "ImagesGen.h"

namespace Images {
    const std::string& getImage(GameState::Headlights headlights)
    {
        switch (headlights) {
        case (GameState::Headlights::Off):
            return Consts::headlightsOff;
        case (GameState::Headlights::LowBeam):
            return Consts::headlightsLowBeam;
        case (GameState::Headlights::HighBeam):
            return Consts::headlightsHighBeam;
        default:
            return Consts::headlightsOff;
        }
    }
    const std::string& getImage(GameState::RainLight rainLight)
    {
        switch (rainLight) {
        case (GameState::RainLight::Off):
            return Consts::rainLightOff;
        case (GameState::RainLight::On):
            return Consts::rainLightOn;
        default:
            return Consts::rainLightOff;
        }
    }
    const std::string& getImage(GameState::Wipers wipers)
    {
        switch (wipers) {
        case (GameState::Wipers::Off):
            return Consts::wipersOff;
        case (GameState::Wipers::OnSpeed1):
            return Consts::wipersOn1;
        case (GameState::Wipers::OnSpeed2):
            return Consts::wipersOn2;
        case (GameState::Wipers::OnSpeed3):
            return Consts::wipersOn3;
        default:
            return Consts::wipersOff;
        }
    }
} // namespace Images