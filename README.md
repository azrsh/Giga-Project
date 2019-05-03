# Giga-Project
このリポジトリは, RCJ2019和歌山大会サッカーライトウェイト部門に出場したKORRDETのプログラム置き場です.  
主に部活の後輩向けのつもりで公開していますが, そのほかのロボカッパーの方が閲覧しても構いません.
## フォルダ構成
リポジトリ直下の各フォルダには, それぞれのマイコン用のプログラムが格納されています.  
### Giga_v1
メインマイコン用プログラム. 使用したマイコンはteensy3.5. teensyduinoを用いて開発.
### BallSensorUnit_2018_v1
ボールセンサユニット用プログラム. 使用したマイコンはatmega328p. arduino uno用ブートローダーで開発. 
### GyroSensorUnit_v1
ジャイロユニット用プログラム. arduino nanoまたはその互換機を使用（本来はメイン基板のatmega328pを使用するはずだった）. 
### UIUnit_v1
ユーザーインターフェースユニット用プログラム. UIユニットの制作が間に合わなかったため大会時点では未使用.
## 開発環境
OS : windows 10  
Compile : ArduinoIDE 1.89  
(ArduinoIDEは「外部エディタを使用する」を有効化して使用)  
Editor : Visual Stdio Code  
(C/C++とArduinoの拡張を使用)  
VCS : git  
VCS Host : github
