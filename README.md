# M5CrowWatch
Caw Caw watch<br />
鳩時計から鳩を追い出してカラスに変更しました。<br />
時刻規正はNTPを使用しているのでWifi環境必須です。ごめんち<br />
<br />
使い方<br />
data/config.txt<br />
記入例を消す<br />
1行目にSSID<br />
2行目にWiFiのパスワードを記入してください<br />
<br />
音声と画像とconfigを書き込む https://github.com/me-no-dev/arduino-esp32fs-plugin<br />
これを参考にESP32FSでSPIFFSにアップロード<br />
<br />
<br />
使用素材<br />
カラスボイス https://taira-komori.jpn.org/animals01.html<br />
カラス写真 CrowPilot撮影（画像単体での無断使用禁止、等プログラム内で使用してください。）<br />
<br />
Crow Watch<br />
How to use<br />
download this repository<br />
emacs ./data/config.txt<br />
erase example lines<br />
put your SSID line 1<br />
put your password line 2<br />
<br />
setup ESP32FS<br />
https://github.com/me-no-dev/arduino-esp32fs-plugin<br />
upload ./data/*<br />
<br />
caw caw caw<br />


