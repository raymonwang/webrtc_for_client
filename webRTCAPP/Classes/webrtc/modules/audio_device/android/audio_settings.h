#ifndef __AUDIO_SETTINGS_H__
#define __AUDIO_SETTINGS_H__

#define AUDIO_SETTING_NUMBER	4

#define AUDIO_TYPE_INDEX	0
#define STREAM_TYPE_INDEX	1
#define MIC_TYPE_INDEX		2
#define USE_BUILDIN_AEC     3

#ifdef __cplusplus
extern "C" {
#endif



/*
 *
 * input:
 * phoneModel 
 *
 * output:
 * outSettings: audio type, stream type, and mic setting
 *
	 * audio type:
	 * 1）MODE_IN_CALL				2
	 * 2）MODE_IN_COMMUNICATION		3
	 * 3）MODE_NORMAL				0
	 *
	 * stream type:
	 * 1）STREAM_MUSIC				3
	 * 2）STREAM_VOICE_CALL			0
	 * 3）STREAM_SYSTEM				1
	 *
	 * mic Setting:
	 * 1）DEFAULT					0
	 * 2）MIC						1
	 * 3）VOICE_CALL					4
	 * 4）VOICE_COMMUNICATION		7
 */
void audio_settings(const char* phoneModel, int* outSettings);
bool setAudioSettingFromJNI(int modelTypeLength,int audioType,int streamType,int micType,bool useBuildInAec);

#ifdef __cplusplus
}
#endif

#endif //__AUDIO_SETTINGS_H__

