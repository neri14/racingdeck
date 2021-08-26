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
    enum class Wipers {
        Off,
        OnSpeed1,
        OnSpeed2,
        OnSpeed3
    };

    Headlights headlights = Headlights::Off;
    RainLight rainLight = RainLight::Off;
    Wipers wipers = Wipers::Off;
};