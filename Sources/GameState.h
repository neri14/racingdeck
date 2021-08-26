#pragma once

struct GameState {
    enum class Headlights {
        Off,
        LowBeam,
        HighBeam
    };
    enum class RainLight {
        Off,
        On
    };

    Headlights headlights = Headlights::Off;
    RainLight rainLight = RainLight::Off;
};