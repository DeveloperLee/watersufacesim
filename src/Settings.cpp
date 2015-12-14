#include "Settings.h"
#include <QFile>
//#include <QSettings>

Settings settings;

void Settings::loadDefaults()
{
    enableFog = false;
    enableCloud = false;
    enableRain = false;
    enableSnow = false;
    enableLens = false;
    bigWave = 3.0;
    smallWave = 0.9;
    waveSpeedX = 0.17;
    waveSpeedY = -0.12;
    cloudThickness = 4.f;
    shadowHardness = 0.95;
    camX = 200.0;
    camY = 100.0;
    wideAngle = 0.9;
}

