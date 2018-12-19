# SLDPCM  
SLDPCM(Shift Logarithmic Differential Pulse-code Modulation)は敷香技術研究所(以降『敷香技研』)が  
開発した高速にデコードできる音声コーデックです。  
これは過去に敷香技研が公開していたPythonのソースコードをもとに、Libsndfileを使いyosiがC++に移植したものです。  

* コンパイル  
`gcc sldenc.c -o sldenc.exe`  
`gcc sldconv.c -o sldconv.exe`  
**Libsndfileがインストールされている環境が必要です**  

* 使い方  
`SLDENC <inputfile> <outputfile>`  
SLDCONVも同様です。  
**ただし、どちらも入力するファイルは符号付16ビットのモノラルあるいはステレオでなければなりません。**
