#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sndfile.h>

int Write_Sld(char *filename, unsigned char *data, unsigned char ch, unsigned long rate, unsigned long datasize)
{
	int i;
	FILE *fp;

	unsigned char header_buf[0x10]; //ヘッダを格納する
	unsigned short vers;
	
	if((fp = fopen(filename, "wb")) == NULL){
		fprintf(stderr, "Error: %s could not open.", filename);
		return 1;
	}

	vers = 130;

	header_buf[0] = 'S';
	header_buf[1] = 'L';
	header_buf[2] = 'D';
	memcpy(header_buf + 3, &vers, sizeof(vers));
	memcpy(header_buf + 5, &(rate), 2);
	memcpy(header_buf + 8, &(ch), 1);
	memcpy(header_buf + 9, &(datasize), sizeof(datasize));
	header_buf[13] = 0;
	header_buf[14] = 0;
	header_buf[15] = 0;

	fwrite(header_buf, sizeof(unsigned char), 0x10, fp);
	fwrite(data, sizeof(unsigned char), datasize, fp);		//データ部分を全て書き込む

	fclose(fp);

	return 0;
}


int chkrng(short n) // 範囲チェック
{
	if (n <= -32768)
	{
		return -32768;
	} else if (n >= 32767)
	{
		return 32767;
	} else {
		return n;
	};
};

int tableconv2(short n) //変換テーブル1
{
	if(n >= 16384){
    	return 15;
	}
	else if( n >= 8192)
	{
    	return 14;
	}
	else if( n >= 4096)
	{
    	return 13;
	}
	else if( n >= 2048)
	{
    	return 12;
	}
	else if( n >= 1024)
	{
    	return 11;
	}
	else if( n >=  512)
	{
    	return 10;
	}
	else if( n >=  256)
	{
    	return 9;
	}
	else if( n >= -255)
	{
    	return 8;
	}
	else if( n >= -511)
	{
    	return 7;
	}
	else if( n >= -1023)
	{
    	return 6;
	}
	else if( n >=-2047)
	{
    	return 5;
	}
	else if( n >=-4095)
	{
    	return 4;
	}
	else if( n >=-8191)
	{
    	return 3;
	}
	else if( n >=-16383)
	{
    	return 2;
	}
	else if( n >=-32767)
	{
    	return 1;
	}
	else
	{
    	return 0;
	}
}

int tableconv(short n) //変換テーブル2
{
	if(n >= 16384){
    	return 16384;
	}
	else if( n >= 8192)
	{
    	return 8192;
	}
	else if( n >= 4096)
	{
    	return 4096;
	}
	else if( n >= 2048)
	{
    	return 2048;
	}
	else if( n >= 1024)
	{
    	return 1024;
	}
	else if( n >=  512)
	{
    	return 512;
	}
	else if( n >=  256)
	{
    	return 256;
	}
	else if( n >= -255)
	{
    	return 0;
	}
	else if( n >= -511)
	{
    	return -256;
	}
	else if( n >= -1023)
	{
    	return -512;
	}
	else if( n >=-2047)
	{
    	return -1024;
	}
	else if( n >=-4095)
	{
    	return -2048;
	}
	else if( n >=-8191)
	{
    	return -4096;
	}
	else if( n >=-16383)
	{
    	return -8192;
	}
	else if( n >=-32767)
	{
    	return -16384;
	}
	else
	{
    	return -32768;
	}
}

int main(int argc, char *argv[]) //メインルーチン
{
	if(argc != 3){ //何も指定されなければ使い方を表示
		fprintf(stdout, "\nSLDPCM COMMANDLINE ENCODER VER. 2.0\n\n");
		fprintf(stdout, "\tOriginal code by Siska Technology Research Laboratory\n");
		fprintf(stdout, "\tReprogram by yosi (Y.C.S.)\n\n");
		fprintf(stdout, "\tSpecial thanks:\n\t\tTwitter, Inc.\n\t\tniwango, inc.\n\t\tIRC@2ch 'omoneta' Channel members\n\n");
		fprintf(stdout, "Usage: SLDENC <inputfile> <outputfile>\n");
		exit(1);
	}

	//変数定義
	// 0=右チャンネルまたはモノラル 1=左チャンネル

	SNDFILE *snd;
	
	SF_INFO sfinfo_rd;
	
	memset(&sfinfo_rd,0,sizeof(sfinfo_rd));
	
	signed short tmp[2],sigma[2],delta[2],a[2],b[2],c;
	unsigned char out[2];
	unsigned char *output;
	signed short *input;
	int cnt;

	//ここから処理

	fprintf(stdout, "\nSLDPCM COMMANDLINE ENCODER VER. 2.0\n\n");
	fprintf(stdout, "\tOriginal code by Siska Technology Research Laboratory\n");
	fprintf(stdout, "\tReprogram by yosi (Y.C.S.)\n\n");
	fprintf(stdout, "\tSpecial thanks:\n\t\tTwitter, Inc.\n\t\tniwango, inc.\n\t\tIRC@2ch 'omoneta' Channel members\n\n");


	fprintf(stderr, "Reading...\n");
	if((snd = sf_open(argv[1], SFM_READ, &sfinfo_rd)) == NULL){
		exit(1);
	}

	fprintf(stderr, "Encoding...\n");

	delta[0]=9;
	delta[1]=9;
	sigma[0]=0;
	sigma[1]=0;

	if((sfinfo_rd.format) == 0x010002){
		
		input = (signed short *)malloc( sizeof( signed short ) * (sfinfo_rd.frames * sfinfo_rd.channels) );
		output = (unsigned char *)malloc( sizeof( unsigned char ) * sfinfo_rd.frames );
		sf_readf_short(snd, input, sfinfo_rd.frames) ;
		
		if(sfinfo_rd.channels == 1)
		{
			for(cnt=0;cnt<sfinfo_rd.frames;cnt++){
				tmp[0]=(input[cnt]);

				delta[0]=tmp[0]-sigma[0];
				a[0]=tableconv(delta[0]);
				b[0]=tableconv2(delta[0]);
				sigma[0]=chkrng(sigma[0]+a[0]);
				out[0]=b[0];
				c=out[0]*16;

				output[cnt]=c+out[0];
			}
		}
		if(sfinfo_rd.channels == 2)
		{
			for(cnt=0;cnt<sfinfo_rd.frames;cnt++){
				tmp[0]=(input[2*cnt]);
				tmp[1]=(input[2*cnt+1]);

				delta[0]=tmp[0]-sigma[0];
				a[0]=tableconv(delta[0]);
				b[0]=tableconv2(delta[0]);
				sigma[0]=chkrng(sigma[0]+a[0]);
				out[0]=b[0];

				delta[1]=tmp[1]-sigma[1];
				a[1]=tableconv(delta[1]);
				b[1]=tableconv2(delta[1]);
				sigma[1]=chkrng(sigma[1]+a[1]);
				out[1]=b[1];
				c=out[0]*16;

				output[cnt]=c+out[1];
			}
		}
	}else{
		fprintf(stderr, "Non 16-bit un-compressed wave !\n");
		exit(1);
	}

	if(Write_Sld(argv[2],output,sfinfo_rd.channels,sfinfo_rd.samplerate,sfinfo_rd.frames) != 0)
	{
		exit(1);
	}

	fprintf(stdout, "Complete !\n");

	sf_close (snd);

	return 0;
}

