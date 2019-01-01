# SLDPCMコマンドラインコンバータ  
* これはナニ?  
SLDPCM(Shift Logarithmic Differential Pulse-code Modulation)は敷香技術研究所(以降『敷香技研』)が  
開発した高速にデコードできる音声コーデックです。  
これは過去に敷香技研が公開していたPythonのソースコードをもとに、Libsndfileを使いyosiがC++に移植したものです。  

* コンパイル  
`gcc sldenc.c -o sldenc.exe`  
`gcc sldconv.c -o sldconv.exe`  
**Libsndfileがインストールされている環境が必要です**  

* 使い方  
`SLDENC <inputfile> <outputfile>`(WAV版)  
SLDCONV(RAWデータ版:Libsndfile不使用)も同様です。  
**ただし、どちらも入力するファイルは符号付16ビットのモノラルあるいはステレオでなければなりません。**
***
# SLDPCM CLI Converter    
* What is this ?  
The SLDPCM (Shift Logarithmic Differential Pulse-Code Modulation) is a high-speed audio codec  
developed by Siska Technical Research Laboratory (hereinafter "STRL").  
This program is based on Python source code which STRL had published in the past (that site is closed),  
I ported to C++ using Libsndfile.  

* How to build  
`gcc sldenc.c -o sldenc.exe`  
`gcc sldconv.c -o sldconv.exe`  
**Libsndfile is required for build these.**  

* How to use  
`SLDENC <inputfile> <outputfile>`(WAV version)  
SLDCONV(RAW data version: Libsndfile not used) is same too.  
**However, inputfile for both versions must be signed 16 bit format, monaural or stereo.**
