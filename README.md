# ZK80mini_SD
　Katsumiさんが公開してくださっている素晴らしいNEC TK-80互換機 ZK-80miniにSDカードによるLOAD、SAVEとスピーカーを載せてみました。

　SDカードのアクセスには、ケンケンさんが公開してくださっているSDカードアクセスライブラリを用いています。

## 回路図
![回路図](https://github.com/yanataka60/ZK80mini_SD/blob/main/JPEG/schematic.jpg)


## 部品表
|番号|品名|数量|備考|
| ------------ | ------------ | ------------ | ------------ |
|U1|4桁7セグメントLED アノードコモン アノード共通接続|1|秋月電子通商 OSL40562-IRA|
|U2|4桁7セグメントLED カソードコモン カソード共通接続|1|秋月電子通商 OSL40562-LRA|
|U3|PIC32MX150F128B|1|マルツオンライン等|
|U4|低消費電力LDO 7333-A|1|オレンジピコショップ 秋月電子通商 S-812C33AY-B-Gでも可|
|J1|6Pinコネクタ|1||
|J2|Micro SD Card Kit|1|秋月電子通商 AE-microSD-LLCNV|
|J3|マイクロUSBコネクタ 電源供給用|1|秋月電子通商 MRUSB-2B-D14NI-S306|
|J4|14P(2×7P) コネクタ|1|ケーブルで繋ぐならボックスヘッダー、直差しするならピンソケット|
|S1 S2|3Pスライドスイッチ|2||
|R1|カーボン抵抗 1/6W 330Ω|1||
|R2 R3 R4 R5|カーボン抵抗 1/6W 100Ω|4||
|R6 R7 R8 R9|カーボン抵抗 1/6W 10kΩ|4||
|C1|電解コンデンサ 16v10μF|1||
|C2 C3 C4|積層セラミックコンデンサ 0.1μF|3||
|C5 C6|積層セラミックコンデンサ 10μF|2||
|LS1|圧電スピーカー(圧電サウンダ)(13mm)|1|秋月電子通商 PKM13EPYH4000-A0|
||キーボード|1|オレンジピコショップ ZK-80-KB 組立てキット|

## その他必要なもの
|品名|
| ------------ |
|Microchip社のPICマイコン書き込み機 PICKit3等|

## PIC書き込み環境
|名称	|
| ------------ |
|MPLAB X IDE|
|MPLAB XC32compiler V1.21|

## PICへの書き込み
MPLABフォルダに２通りのコンパイル済みバイナリを用意しています。

　zk80mini_8080.hex(CPU 8080)

　zk80mini_z80.hex(CPU Z80)

このバイナリを使うのであればMPLAB X IDE付属のMPLAB X IPEにより書き込んでください。

コンパイルしたい方はMPLAB/zk80mini_SDフォルダのプロジェクトをMPLAB X IDEでコンパイルして書き込んでください。

## バイナリに含まれるTK-80互換モニタープログラムについて
ZK80miniオリジナルに含まれるTK-80互換モニタープログラムをそのまま使用しています。

詳しくはオリジナルのreadme.txtを参照してください。

## 使い方
　使い方の基本はTK-80と同様です。

　ROM $0000-$02FF(768Byte)

　RAM $8000-$F1FF(28KByte)

## SAVE
　ファイルNo(xxxx)を8000～FFFFの16進数4桁で入力して「STORE DATA」キーを押します。

　メモリ 8000h～F1FFhまでをxxxx.ZK8としてセーブします。セーブ範囲は固定となっていて指定はできません。

　SDカードには、ファイルNo(xxxx).ZK8という名前で保存されます。

　SDカードに同じファイルNoのZK8ファイルがあった場合には上書きされます。

　ファイルNo、0000～7FFFまでは上書きによる消失を防ぐため読み出し専用のファイルNoになっています。

　ファイルNo、8000～FFFFは読み書き自由です。

　ZK8形式は、ヘッダ情報等が付加されていないファイル長28,672Byteのベタなバイナリファイルです。

## LOAD
　ファイルNo(xxxx)を0000～FFFFの16進数4桁で入力して「LOAD DATA」キーを押します。

　正常にLOADされた場合は、LED ADDRESS表示部にLOAD開始アドレス、LED DATA表示部にLOAD終了アドレスが表示されます。

　LOADするファイルの拡張子はZK8、TK8、BIN、BTK、HEXに対応しており、違う拡張子で同じファイルNoのファイルがSDカードに保存されていた場合には次の順に検索されます。

　　　検索順：ZK8 -> TK8 -> BIN -> BTK -> HEX

### ZK8、TK8、BIN
　すべて、ヘッダ情報等が付加されていないベタなバイナリファイル。

　SDカードから読み込まれたファイルはメモリの8000hからファイル長分LOADされます。

　ただし、メモリへの書き込みアドレスが83C0H～83FFH、F200H～FFFFHまでの範囲の読み出しデータはメモリに書き込まれません。

### BTK
　バイナリファイル本体データの先頭に2Byteの開始アドレス、2Byteの終了アドレス合計4Byteを付加した形になっているファイル。

　SDカードから読み込まれたファイルは開始アドレスから終了アドレスまでLOADされます。

　ただし、メモリへの書き込みアドレスが83C0H～83FFH、F200H～FFFFHまでの範囲の読み出しデータはメモリに書き込まれません。

### HEX
　インテルHEX形式のファイル。

　SDカードから読み込まれたファイルはインテルHEX形式に基づいてLOADされます。

　ただし、メモリへの書き込みアドレスが83C0H～83FFH、F200H～FFFFHまでの範囲の読み出しデータはメモリに書き込まれません。

### 注意
　SDカードにアクセスしていなければ電源ON時でもSDカードの抜き差しは可能ですが、再挿入後にはZK80miniをリセットしてください。

## 免責事項
　このツールを参考にして行った事による、いかなる不具合に関しても、私は責任を持ちません。各自、自己責任のもとで作業を行ってください。

## 著作権について
KUT KiCad Connector footprint libraryは、The MIT License (MIT)、

それ以外は、すべてLGPL v2.0の元配布します。

## 謝辞
　ZK80miniを公開してくださったKatsumi様

　SDカードアクセスライブラリを公開してくださったケンケン様

　ありがとうございました。
