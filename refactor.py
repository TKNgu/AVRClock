import os
import glob

replacements = {
    "ClockEngine": "TimeManager",
    "ClockEngineAdvance": "AdvancedTimeManager",
    "ClockLight": "LightController",
    "ArrayMax": "MovingMaxFilter",
    "ClockChime": "ChimeController",
    "arrayMax": "movingMaxFilter",
    "clockEngine_": "timeManager_",
    "clockLight_": "lightController_",
    "clockChime_": "chimeController_",
    "CLOCKENGINE_HPP": "TIMEMANAGER_HPP",
    "CLOCKLIGHT_HPP": "LIGHTCONTROLLER_HPP",
    "CLOCKCHIME_HPP": "CHIMECONTROLLER_HPP",
    # Function renames
    ".check(": ".updateLoop(",
    ".update(": ".calculateBrightness(",
    ".updateGlobal(": ".commitDailyMaxLight(",
    ".getValueMax(": ".getMovingMax(",
}

def process_file(filepath):
    with open(filepath, 'r') as f:
        content = f.read()
    
    # Specific targeted function renames inside class declarations
    content = content.replace("void check(const unsigned long);", "void updateLoop(const unsigned long);")
    content = content.replace("void update(int);", "void calculateBrightness(int);")
    content = content.replace("void updateGlobal();", "void commitDailyMaxLight();")
    content = content.replace("float update(unsigned);", "float addValue(unsigned);")
    content = content.replace("float getValueMax();", "float getMovingMax();")
    content = content.replace("bool check();", "bool shouldChime();")
    
    content = content.replace("void ClockLight::check(", "void LightController::updateLoop(")
    content = content.replace("void ClockLight::update(", "void LightController::calculateBrightness(")
    content = content.replace("void ClockLight::updateGlobal(", "void LightController::commitDailyMaxLight(")
    content = content.replace("float ArrayMax::update(", "float MovingMaxFilter::addValue(")
    content = content.replace("float ArrayMax::getValueMax(", "float MovingMaxFilter::getMovingMax(")
    content = content.replace("bool ClockChime::check(", "bool ChimeController::shouldChime(")
    
    for old, new in replacements.items():
        content = content.replace(old, new)
        
    with open(filepath, 'w') as f:
        f.write(content)

src_files = glob.glob('ArduinoClock/src/**/*.cpp', recursive=True) + \
            glob.glob('ArduinoClock/src/**/*.hpp', recursive=True) + \
            ['ArduinoClock/ArduinoClock.ino']

for f in src_files:
    process_file(f)

# Rename files
os.rename("ArduinoClock/src/clock/ClockEngine.hpp", "ArduinoClock/src/clock/TimeManager.hpp")
os.rename("ArduinoClock/src/clock/ClockEngine.cpp", "ArduinoClock/src/clock/TimeManager.cpp")
os.rename("ArduinoClock/src/clock/ClockLight.hpp", "ArduinoClock/src/clock/LightController.hpp")
os.rename("ArduinoClock/src/clock/ClockLight.cpp", "ArduinoClock/src/clock/LightController.cpp")
os.rename("ArduinoClock/src/clock/ClockChime.hpp", "ArduinoClock/src/clock/ChimeController.hpp")
os.rename("ArduinoClock/src/clock/ClockChime.cpp", "ArduinoClock/src/clock/ChimeController.cpp")
