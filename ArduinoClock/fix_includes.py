import os

# Map of filename -> new relative path from src/
new_locations = {
    'State2.hpp': 'state/State2.hpp',
    'StateManager2.hpp': 'state/StateManager2.hpp',
    'ClockView.hpp': 'state/views/ClockView.hpp',
    'ClockSleep.hpp': 'state/views/ClockSleep.hpp',
    'ClockEdit2.hpp': 'state/edit/ClockEdit2.hpp',
    'HourEdit2.hpp': 'state/edit/HourEdit2.hpp',
    'MinutesEdit2.hpp': 'state/edit/MinutesEdit2.hpp',
    'Timer.hpp': 'timer/Timer.hpp',
    'BlinkTimer.hpp': 'timer/BlinkTimer.hpp',
    'TimePoint.hpp': 'timer/TimePoint.hpp',
    'Button.hpp': 'button/Button.hpp',
    'Button2.hpp': 'button/Button2.hpp',
    'ClockChime.hpp': 'clock/ClockChime.hpp',
    'ClockEngine.hpp': 'clock/ClockEngine.hpp',
    'ClockEngineAdvance.hpp': 'clock/ClockEngineAdvance.hpp',
    'ClockLight.hpp': 'clock/ClockLight.hpp',
    'TTSDisplay.h': 'utils/TTSDisplay.h',
    'TTSTime.h': 'utils/TTSTime.h',
    'TTSTemp.h': 'utils/TTSTemp.h',
    'LowPower.h': 'utils/LowPower.h',
    'KamaFilter.h': 'utils/KamaFilter.h',
    'Utils.hpp': 'utils/Utils.hpp',
    'Streaming.h': 'utils/Streaming.h'
}

src_dir = os.path.abspath('src')

for root, dirs, files in os.walk(src_dir):
    for file in files:
        if file.endswith('.hpp') or file.endswith('.cpp') or file.endswith('.h'):
            filepath = os.path.join(root, file)
            with open(filepath, 'r') as f:
                lines = f.readlines()
            
            changed = False
            for i, line in enumerate(lines):
                if line.strip().startswith('#include "'):
                    # Extract the included path
                    start = line.find('"') + 1
                    end = line.find('"', start)
                    inc_path = line[start:end]
                    
                    # Ignore if it's not a relative path or doesn't have directory traversing
                    # Wait, if we just extract the basename, we know where it is now
                    basename = os.path.basename(inc_path)
                    if basename in new_locations:
                        # Compute relative path from current file's directory to the new location
                        target_abs = os.path.join(src_dir, new_locations[basename])
                        current_dir = os.path.dirname(filepath)
                        new_rel = os.path.relpath(target_abs, current_dir)
                        
                        # Fix Windows paths to forward slashes just in case
                        new_rel = new_rel.replace('\\', '/')
                        
                        if new_rel != inc_path:
                            lines[i] = line[:start] + new_rel + line[end:]
                            changed = True
                            print(f"{filepath}: {inc_path} -> {new_rel}")
            
            if changed:
                with open(filepath, 'w') as f:
                    f.writelines(lines)
