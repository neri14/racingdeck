#pragma once

namespace ACC {
    namespace raw {
        // Based on ACCSharedMemoryDocumentationV1.7.6.pdf from https://www.assettocorsa.net/forum/index.php?threads/acc-shared-memory-documentation.59965/

        enum class Flag : int {
            No = 0,
            Blue = 1,
            Yellow = 2,
            Black = 3,
            White = 4,
            Chequered = 5,
            Penalty = 6,
            Green = 7,
            Orange = 8
        };

        enum class Penalty : int {
            None = 0,
            DriveThrough_Cutting = 1,
            StopAndGo_10_Cutting = 2,
            StopAndGo_20_Cutting = 3,
            StopAndGo_30_Cutting = 4,
            Disqualified_Cutting = 5,
            RemoveBestLaptime_Cutting = 6,

            DriveThrough_PitSpeeding = 7,
            StopAndGo_10_PitSpeeding = 8,
            StopAndGo_20_PitSpeeding = 9,
            StopAndGo_30_PitSpeeding = 10,
            Disqualified_PitSpeeding = 11,
            RemoveBestLaptime_PitSpeeding = 12,

            Disqualified_IgnoredMandatoryPit = 13,

            PostRaceTime = 14,
            Disqualified_Trolling = 15,
            Disqualified_PitEntry = 16,
            Disqualified_PitExit = 17,
            Disqualified_WrongWay = 18,

            DriveThrough_IgnoredDriverStint = 19,
            Disqualified_IgnoredDriverStint = 20,

            Disqualified_ExceededDriverStintLimit = 21
        };

        enum class Session : int {
            Unknown = -1,
            Practice = 0,
            Qualify = 1,
            Race = 2,
            HotLap = 3,
            TimeAttack = 4,
            Drift = 5,
            Drag = 6,
            HotStint = 7,
            HotStintSuperpole = 8
        };

        enum class Status : int {
            Off = 0,
            Replay = 1,
            Live = 2,
            Pause = 3
        };

        enum class Wheels : int {
            FrontLeft = 0,
            FrontRight = 1,
            RearLeft = 2,
            RearRight = 3
        };

        enum class TrackGrip : int {
            Green = 0,
            Fast = 1,
            Optimum = 2,
            Greasy = 3,
            Damp = 4,
            Wet = 5,
            Flooded = 6
        };

        enum class RainIntensity : int {
            NoRain = 0,
            Drizzle = 1,
            LightRain = 2,
            MediumRain = 3,
            HeavyRain = 4,
            Thunderstorm = 5
        };


#pragma pack(push)
#pragma pack(4)

        struct SPageFilePhysics
        {
            int packetId = 0;
            float gas = 0;
            float brake = 0;
            float fuel = 0;
            int gear = 0;
            int rpm = 0;
            float steerAngle = 0;
            float speedKmh = 0;
            float velocity[3];
            float accG[3];
            float wheelSlip[4];
            float wheelLoad[4]; //unused in ACC
            float wheelsPressure[4];
            float wheelAngularSpeed[4];
            float tyreWear[4]; //unused in ACC
            float tyreDirtyLevel[4]; //unused in ACC
            float tyreCoreTemp[4];
            float camberRAD[4]; //unused in ACC
            float suspensionTravel[4];
            float drs = 0; //unused in ACC
            float tc = 0;
            float heading = 0;
            float pitch = 0;
            float roll = 0;
            float cgHeight; //unused in ACC
            float carDamage[5]; //front 0, rear 1, left 2, right 3, center 4
            int numberOfTyresOut = 0; //unused in ACC
            int pitLimiterOn = 0;
            float abs = 0;
            float kersCharge = 0; //unused in ACC
            float kersInput = 0; //unused in ACC
            int autoShifterOn = 0;
            float rideHeight[2]; //unused in ACC
            float turboBoost = 0;
            float ballast = 0; //unused in ACC
            float airDensity = 0; //unused in ACC
            float airTemp = 0;
            float roadTemp = 0;
            float localAngularVel[3];
            float finalFF = 0;
            float performanceMeter = 0; //unused in ACC

            int engineBrake = 0; //unused in ACC
            int ersRecoveryLevel = 0; //unused in ACC
            int ersPowerLevel = 0; //unused in ACC
            int ersHeatCharging = 0; //unused in ACC
            int ersIsCharging = 0; //unused in ACC
            float kersCurrentKJ = 0; //unused in ACC

            int drsAvailable = 0; //unused in ACC
            int drsEnabled = 0; //unused in ACC

            float brakeTemp[4];
            float clutch = 0;

            float tyreTempI[4]; //unused in ACC
            float tyreTempM[4]; //unused in ACC
            float tyreTempO[4]; //unused in ACC

            int isAIControlled;

            float tyreContactPoint[4][3]; //[FL,FR,RL,RR][x,y,z]
            float tyreContactNormal[4][3]; //[FL,FR,RL,RR][x,y,z]
            float tyreContactHeading[4][3]; //[FL,FR,RL,RR][x,y,z]

            float brakeBias = 0;

            float localVelocity[3];

            int P2PActivations = 0; //unused in ACC
            int P2PStatus = 0; //unused in ACC

            int currentMaxRpm = 0; //unused in ACC

            float mz[4]; //unused in ACC
            float fx[4]; //unused in ACC
            float fy[4]; //unused in ACC
            float slipRatio[4];
            float slipAngle[4];

            int tcinAction = 0; //unused in ACC
            int absInAction = 0; //unused in ACC
            float suspensionDamage[4]; //unused in ACC
            float tyreTemp[4]; //unused in ACC

            float waterTemp = 0;

            float brakePressure[4];
            int frontBrakeCompound = 0;
            int rearBrakeCompound = 0;
            float padLife[4];
            float discLife[4];

            int ignitionOn = 0;
            int isEngineRunning = 0;

            float kerbVibration = 0;
            float slipVibrations = 0;
            float gVibrations = 0;
            float absVibrations = 0;
        };


        struct SPageFileGraphic
        {
            int packetId = 0;
            Status status = Status::Off;
            Session session = Session::Practice;
            wchar_t currentTime[15];
            wchar_t lastTime[15];
            wchar_t bestTime[15];
            wchar_t split[15];
            int completedLaps = 0;
            int position = 0;
            int iCurrentTime = 0; //ms
            int iLastTime = 0; //ms
            int iBestTime = 0; //ms
            float sessionTimeLeft = 0;
            float distanceTraveled = 0;
            int isInPit = 0;
            int currentSectorIndex = 0;
            int lastSectorTime = 0; //ms
            int numberOfLaps = 0;
            wchar_t tyreCompound[33];
            float replayTimeMultiplier = 0; //unused in ACC
            float normalizedCarPosition = 0;

            int activeCars = 0;
            float carCoordinates[60][3];
            int carID[60];
            int playerCarID = 0;
            float penaltyTime = 0;
            Flag flag = Flag::No;
            Penalty penalty = Penalty::None;
            int idealLineOn = 0;
            int isInPitLane = 0;

            float surfaceGrip = 0;
            int mandatoryPitDone = 0;

            float windSpeed = 0;
            float windDirection = 0;

            int isSetupMenuVisible = 0;

            int mainDisplayIndex = 0;
            int secondaryDisplayIndex = 0;
            int TC = 0;
            int TCCut = 0;
            int EngineMap = 0;
            int ABS = 0;
            int fuelXLap = 0; //fuel per lap
            int rainLights = 0;
            int flashingLights = 0;
            int lightsStage = 0;
            float exhaustTemperature = 0.0f;
            int wiperLV = 0; //current wiper stage
            int DriverStintTotalTimeLeft = 0; //ms
            int DriverStintTimeLeft = 0; //ms
            int rainTyres = 0;

            int sessionIndex = 0;
            float usedFuel = 0;

            wchar_t deltaLapTime[15];
            int iDeltaLapTime = 0; //ms
            wchar_t estimatedLapTime[15];
            int iEstimatedLapTime = 0; //ms
            int isDeltaPositive = 0;
            int iSplit = 0; //last split [ms]
            int isValidLap = 0;

            float fuelEstimatedLaps = 0; //laps on current fuel
            wchar_t trackStatus[33];
            int missingMandatoryPits = 0;
            float clock = 0; //time of day [s]

            int directionLightsLeft = 0;
            int directionLightsRight = 0;

            int globalYellow = 0;
            int globalYellow1 = 0;
            int globalYellow2 = 0;
            int globalYellow3 = 0;
            int globalWhite = 0;
            int globalGreen = 0;
            int globalChequered = 0;
            int globalRed = 0;

            int mfdTyreSet = 0;
            float mfdFuelToAdd = 0;
            float mfdTyrePressureLF = 0;
            float mfdTyrePressureRF = 0;
            float mfdTyrePressureLR = 0;
            float mfdTyrePressureRR = 0;

            TrackGrip trackGripStatus = TrackGrip::Green;
            RainIntensity rainIntensity = RainIntensity::NoRain;
            RainIntensity rainIntensityIn10min = RainIntensity::NoRain;
            RainIntensity rainIntensityIn30min = RainIntensity::NoRain;

            int currentTyreSet = 0;
            int strategyTyreSet = 0;
        };


        struct SPageFileStatic
        {
            wchar_t smVersion[15];
            wchar_t acVersion[15];

            // session static info
            int numberOfSessions = 0;
            int numCars = 0;
            wchar_t carModel[33];
            wchar_t track[33];
            wchar_t playerName[33];
            wchar_t playerSurname[33];
            wchar_t playerNick[33];
            int sectorCount = 0;

            // car static info
            float maxTorque = 0; //unused in ACC
            float maxPower = 0; //unused in ACC
            int	maxRpm = 0;
            float maxFuel = 0;
            float suspensionMaxTravel[4]; //unused in ACC
            float tyreRadius[4]; //unused in ACC
            float maxTurboBoost = 0; //unused in ACC

            float deprecated_1 = -273; //unused in ACC
            float deprecated_2 = -273; //unused in ACC

            int penaltiesEnabled = 0;

            float aidFuelRate = 0;
            float aidTireRate = 0;
            float aidMechanicalDamage = 0;
            int aidAllowTyreBlankets = 0;
            float aidStability = 0;
            int aidAutoClutch = 0;
            int aidAutoBlip = 0; //always true in ACC

            int hasDRS = 0; //unused in ACC
            int hasERS = 0; //unused in ACC
            int hasKERS = 0; //unused in ACC
            float kersMaxJ = 0; //unused in ACC
            int engineBrakeSettingsCount = 0; //unused in ACC
            int ersPowerControllerCount = 0; //unused in ACC
            float trackSPlineLength = 0; //unused in ACC
            wchar_t trackConfiguration[33]; //unused in ACC
            float ersMaxJ = 0; //unused in ACC

            int isTimedRace = 0; //unused in ACC
            int hasExtraLap = 0; //unused in ACC

            wchar_t carSkin[33]; //unused in ACC
            int reversedGridPositions = 0; //unused in ACC
            int pitWindowStart = 0; //ms?
            int pitWindowEnd = 0; //ms?
            int isOnline = 0;

            wchar_t dryTyresName[33];
            wchar_t wetTyresName[33];
        };


#pragma pack(pop)
    } // namespace raw
} // namespace ACC