#include <QSettings>
#include <QString>
#include <QVariant>
#include <cstring>

#include <constants.h>

#ifndef _WIN32
#include <unistd.h>
#endif
#include <QStandardPaths>
#include <QDir>
#include <QFile>

QSettings* settings;
QSettings* settingsDefault;
void settings_init() {
#ifdef _WIN32
    QString cfgDir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    QDir().mkpath(cfgDir);
    QString settingsFile = cfgDir + "/pardus-pen.ini";
#else
    QString settingsFile = QString(getenv("HOME"))+"/.config/pardus-pen.conf";
#endif
    settings = new QSettings(settingsFile, QSettings::IniFormat);
    settingsDefault = new QSettings("://tr.org.pardus.pen.default.conf", QSettings::IniFormat);
    // version check
    int ver = 0;
    int ver_default = settingsDefault->value("version").toInt();
    if(settings->contains("version")){
        ver = settings->value("version").toInt();
    }
    if(ver < ver_default){
        delete settings;
        QFile::remove(settingsFile);
        settings = new QSettings(settingsFile, QSettings::IniFormat);
        settings->setValue("version", ver_default);
    }
}

QString get_string(const char* name) {
    QString value;
    if(settings->contains(QString::fromUtf8(name))){
        value = settings->value(QString::fromUtf8(name)).toString();
    } else {
        value = settingsDefault->value(QString::fromUtf8(name)).toString();
    }
    return value;
}

QString get_default_string(const char* name) {
    QString value;
    if(settingsDefault->contains(QString::fromUtf8(name))){
        value = settingsDefault->value(QString::fromUtf8(name)).toString();
    }
    return value;
}
bool get_bool(const char* name) {
    bool value;
    if(settings->contains(QString::fromUtf8(name))){
        value = settings->value(QString::fromUtf8(name)).toBool();
    } else {
        value = settingsDefault->value(QString::fromUtf8(name)).toBool();
    }
    return value;
}

void set_bool(const char* name, bool value) {
    settings->setValue(QString::fromUtf8(name), value);
    settings->sync();
}

void set_string(const char* name, QString value) {
    settings->setValue(QString::fromUtf8(name), value);
    settings->sync();
}

int get_int(const char* name) {
    int value;
    if(settings->contains(QString::fromUtf8(name))){
        value = settings->value(QString::fromUtf8(name)).toInt();
    } else {
        value = settingsDefault->value(QString::fromUtf8(name)).toInt();
    }
    return value;
}

void set_int(const char* name, int value) {
    settings->setValue(QString::fromUtf8(name), value);
    settings->sync();
}
