#ifndef __TTS_CORE_H__
#define __TTS_CORE_H__

#define	MAX_KEY_LEN		128


typedef enum _ttsFormat
{
	FORMAT_PCM = 0,
	FORMAT_WAV,
	FORMAT_MP3
} ttsFormat;

typedef enum _ttsVoice
{
	VOICE_WOMAN = 0,
	VOICE_MAN,
	VOICE_WOMAN2
} ttsVoice;

typedef struct _ttsParam
{
	char		appKey[MAX_KEY_LEN];	// Ali: appKey, Baidu: appID, Tong: appID
	char		token[MAX_KEY_LEN];		// Ali: token, Baidu: apiKey, Tong: appKey
	char		sKey[MAX_KEY_LEN];		// Ali: null, Baidu: secretKey, Tong: null
	char		ip[MAX_PATH];			// Ali: IP gateway, Baidu: null, Tong: null
	char		file[MAX_PATH];
	ttsFormat	format;
	ttsVoice	voice;
	int			sample_rate;
	int			volume;
	int			speech_rate;
	int			pitch_rate;
} ttsParam;

void InitCurlGlobal();
void ClearCurlGlobal();
ttsParam *CreateTtsParams(const char *aKey, const char *token, const char *sKey, const char *ip);
void RelaseTtsParams(ttsParam *pParam);
int SetFileName(ttsParam *pParam, const char *fileName);
void SetSpeechTone(ttsParam *pParam, const ttsVoice voice);
void SetFileFormat(ttsParam *pParam, const ttsFormat format);
void SetSampleRate(ttsParam *pParam, const int rate);
void SetSpeechVolume(ttsParam *pParam, const int vol);
void SetTalkSpeed(ttsParam *pParam, const int speed);
void SetTalkPitch(ttsParam *pParam, const int pitch);
int AliTextToSpeech(ttsParam *pParam, const char *text);
int BaiBuTextToSpeech(ttsParam *pParam, const char *text);
int ThsTextToSpeech(ttsParam *pParam, const char *text);

#endif
