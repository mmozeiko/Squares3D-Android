rem adb uninstall lv.bubu.Squares3D
adb install -r bin\Game-debug.apk
adb shell am start -a android.intent.action.MAIN -n mmozeiko.Squares3D/lv.bubu.Squares3D.Game
