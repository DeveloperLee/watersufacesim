#include "Settings.h"
#include <QFile>
#include <QSettings>

Settings settings;

void Settings::loadSettingsOrDefaults()
{
    // Set the default values below
    QSettings s;

    enableCloud = s.value("enableCloud", false).toBool();
    cloudThickness = s.value("cloudThickness", 1.f).toFloat();
    enableFog = s.value("enableFog", false).toBool();
}

void Settings::saveSettings()
{
    QSettings s;

    s.setValue("enableCloud", enableCloud);
    s.setValue("cloudThickness", cloudThickness);
    s.setValue("enableFog", enableFog);
}

