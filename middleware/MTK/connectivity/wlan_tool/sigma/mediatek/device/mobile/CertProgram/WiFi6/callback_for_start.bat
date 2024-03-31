@echo off
:preconfig

adb shell /data/bin/iwpriv wlan0 set_sw_ctrl 0xa0400000 0x1
adb shell "echo 0xff:0x2f > /proc/net/wlan/dbgLevel"

echo Adjust socket buffer window size to MAX 8MB
adb shell "echo 8388608 > /proc/sys/net/core/wmem_default"
adb shell "cat /proc/sys/net/core/wmem_default"

:preconfig_done
adb shell getprop | findstr ro.vendor.wlan.gen | findstr gen4m > nul && goto connac_performance_mode
goto end

:connac_performance_mode
adb shell "svc power stayon true"
adb shell "echo 0 0 > /proc/ppm/policy/ut_fix_freq_idx"
adb shell "echo 100 > /proc/perfmgr/eas/debug_ta_boost"

goto end

:end

