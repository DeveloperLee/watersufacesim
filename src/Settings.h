/**
 * @file    Settings.h
 *
 * This file contains various settings and enumerations that you will need to use in the various
 * assignments. The settings are bound to the GUI via static data bindings.
 */

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

struct Settings
{
    // fill in default values
    void loadDefaults();

    /** Shader parameters **/

    //Effect controller --> UI : Effect
    bool enableCloud, enableFog, enableLens, enableSnow, enableRain, enableShadow;

    //Water effect --> UI : Water
    float bigWave, smallWave, waveSpeedX, waveSpeedY;

    //Cloud effect --> UI : Cloud
    float cloudThickness, shadowHardness;

    //Camera adjust --> UI : Camera
    float camX, camY, wideAngle;
};

// The global Settings object, will be initialized by MainWindow
extern Settings settings;

#endif // SETTINGS_H
