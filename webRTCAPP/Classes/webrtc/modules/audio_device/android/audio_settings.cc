#include "audio_settings.h"
//#include "webrtc/modules/audio_device/android/audio_settings.h"
#include <string.h>
#include <android/log.h>

#define TAG "audio_settings"

/**

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

#define    MODE_NONE                    -1
#define    MODE_IN_CALL                2
#define    MODE_IN_COMMUNICATION        3
#define    MODE_NORMAL                    0

#define    STREAM_MUSIC                3
#define    STREAM_VOICE_CALL            0
#define    STREAM_SYSTEM                1

#define    DEFAULT                        0
#define    MIC                            1
#define    VOICE_CALL                    4
#define    VOICE_RECOGNITION            6
#define    VOICE_COMMUNICATION            7

#define MODEL_NUM					25


#ifdef __cplusplus
extern "C" {
#endif

int mystrcmp(const char *str1, int length1, const char *str2, int length2) {
    if (length1 != length2) {
        return -1;
    }
    int res = 0;
    for (int i = 0; i < length1; i++) {
        char c1 = *(str1 + i);
        char c2 = *(str2 + i);
        if (c1 != c2) {
            res = -1;
            break;
        }
    }
    return res;
}


/**
 * 通配符
 */
int mystrcmpRegular(const char *str1, int length1, const char *str2, int length2) {
    if (length1 != length2) {
        return -1;
    }
    int res = -1;
    for (int i = 0; i < length1; i++) {
        char c1 = *(str1 + i);
        char c2 = *(str2 + i);
        if (i < 3) {//第四个字符才有可能是通配符，前面必须匹配，否则无法决断是哪类机型
            if (c1 != c2) {
                res = -1;
                break;
            }
        } else {
            //todo:如果一直匹配,就不用匹配符
            if (c1 == c2) {
                if (i == (length1 - 1)) {
                    return 0;
                }
            } else if (*(str2 + length2 - 1) == '*') {
                if (c2 == '*') {
                    return 0;
                }
            } else {//SM-G9009W str2:SM-G9008W 倒数第二位比较
                return -1;
            }
        }
    }
    return res;
}

typedef struct {
    char const *modelType;
    int modelTypeLength;
    //in byte
    int audioType;
    int streamType;
    int micType;
    bool useBuildInAec;
} audio_setting;

static audio_setting settings[MODEL_NUM] = {
        {"GT-I9000",        8,          MODE_IN_COMMUNICATION, STREAM_VOICE_CALL, DEFAULT,             true},
        {"GT-N7100",        8,          MODE_IN_COMMUNICATION, STREAM_MUSIC,      VOICE_COMMUNICATION, false},
        {"HUAWEI NXT-AL10", 15,         MODE_IN_COMMUNICATION, STREAM_VOICE_CALL, VOICE_COMMUNICATION, true},
        {"m1 metal",        8,          MODE_IN_CALL,          STREAM_VOICE_CALL, DEFAULT,             true},
        {"SM-G9350",        8,          MODE_IN_COMMUNICATION, STREAM_VOICE_CALL, VOICE_RECOGNITION,   true},
        {"M681C",           5,          MODE_IN_CALL,          STREAM_VOICE_CALL, DEFAULT,             true},
        {"OPPO R7",         7,          MODE_IN_COMMUNICATION, STREAM_VOICE_CALL, DEFAULT,             true},
        {"OPPO R9tm",       9,          MODE_IN_COMMUNICATION, STREAM_MUSIC,      VOICE_COMMUNICATION, true},
        {"MX5",             3,          MODE_IN_COMMUNICATION, STREAM_MUSIC,      VOICE_COMMUNICATION, true},
        {"Le X620",         7,          MODE_IN_COMMUNICATION, STREAM_MUSIC,      VOICE_COMMUNICATION, true},
        {"m2 note",         7,          MODE_IN_COMMUNICATION, STREAM_VOICE_CALL, DEFAULT,             true},
        {"Redmi Note 3",    12,         MODE_IN_COMMUNICATION, STREAM_MUSIC,      VOICE_COMMUNICATION, true},
        {"MI NOTE LTE",     11,         MODE_IN_COMMUNICATION, STREAM_MUSIC,      VOICE_COMMUNICATION, true},
        {"MI 5",            4,          MODE_IN_COMMUNICATION, STREAM_MUSIC,      VOICE_COMMUNICATION, true},
        {"Redmi Note 2",    12,         MODE_IN_COMMUNICATION, STREAM_MUSIC,      VOICE_COMMUNICATION, true},
        {"OPPO A33m",       9,          MODE_IN_CALL,          STREAM_MUSIC,      VOICE_COMMUNICATION, true},
        {"OPPO R7s",        8,          MODE_IN_COMMUNICATION, STREAM_VOICE_CALL, VOICE_COMMUNICATION, true},
        {"MI 4LTE",         7,          MODE_IN_COMMUNICATION, STREAM_MUSIC,      VOICE_COMMUNICATION, true},
        {"A31",             3,          MODE_IN_COMMUNICATION, STREAM_VOICE_CALL, VOICE_COMMUNICATION, true},
        {"m1 note",         7,          MODE_IN_COMMUNICATION, STREAM_VOICE_CALL, VOICE_RECOGNITION,   false},
        {"GT-I9308",        8,          MODE_IN_COMMUNICATION, STREAM_MUSIC, VOICE_RECOGNITION,   false},
        {"vivo X7Plus",     11,         MODE_IN_COMMUNICATION, STREAM_VOICE_CALL, VOICE_RECOGNITION,   false},
        {"OPPO R9s",        8,          MODE_IN_COMMUNICATION, STREAM_VOICE_CALL, VOICE_RECOGNITION,   false},
        {"SM-G900***",      9,          MODE_IN_COMMUNICATION, STREAM_VOICE_CALL, VOICE_RECOGNITION,   false},
        {"SM-N900***",      9,          MODE_IN_COMMUNICATION, STREAM_VOICE_CALL, VOICE_COMMUNICATION, false}
};
//Todo:先使用 JNI 把这里面的几个值设置好，等调用 audio_settings 时再把这几个变量的值读取设置给手机
/**
 * 先为 globalAudioSetting 设置从服务器获取到的值，
 * 等调用 audio_settings 时再把这 globalAudioSetting 中的值设置给手机
 */
audio_setting globalAudioSetting;
bool flag = false;
bool setAudioSettingFromJNI(int modelTypeLength, int audioType, int streamType, int micType, bool useBuildInAec) {
    globalAudioSetting.modelTypeLength = modelTypeLength;
    globalAudioSetting.audioType = audioType;
    globalAudioSetting.streamType = streamType;
    globalAudioSetting.micType = micType;
    globalAudioSetting.useBuildInAec = useBuildInAec;
    flag = true;//表明globalAudioSetting被成功赋值
    return true;
}

void audio_settings(const char* phoneModel, int* outSettings) {
    if (flag) { //globalAudioSetting 被设置了数据，则以globalAudioSetting的数据为准，将globalAudioSetting的数据设置给手机
        outSettings[AUDIO_TYPE_INDEX] = globalAudioSetting.audioType;
        outSettings[STREAM_TYPE_INDEX] = globalAudioSetting.streamType;
        outSettings[MIC_TYPE_INDEX] = globalAudioSetting.micType;
        outSettings[USE_BUILDIN_AEC] = globalAudioSetting.useBuildInAec;
    }
    else { //globalAudioSetting 没有数据，以默认为主
        char buffer[16] = {0};
        for (int i = 0; i < MODEL_NUM; i++) {
            memset(buffer, 0, sizeof(buffer));
            strncpy(buffer, settings[i].modelType, strlen(settings[i].modelType));
            char *prefixType = strtok(buffer, "***");
            if (prefixType != nullptr && strstr(phoneModel, prefixType)) {
                outSettings[AUDIO_TYPE_INDEX] = settings[i].audioType;
                outSettings[STREAM_TYPE_INDEX] = settings[i].streamType;
                outSettings[MIC_TYPE_INDEX] = settings[i].micType;
                outSettings[USE_BUILDIN_AEC] = settings[i].useBuildInAec;
                return;
            }
            else if (strncasecmp(phoneModel, settings[i].modelType, strlen(phoneModel)) == 0) {
                outSettings[AUDIO_TYPE_INDEX] = settings[i].audioType;
                outSettings[STREAM_TYPE_INDEX] = settings[i].streamType;
                outSettings[MIC_TYPE_INDEX] = settings[i].micType;
                outSettings[USE_BUILDIN_AEC] = settings[i].useBuildInAec;
                return;
            }
        }
        outSettings[AUDIO_TYPE_INDEX] = MODE_IN_COMMUNICATION;
        outSettings[STREAM_TYPE_INDEX] = STREAM_MUSIC;
        outSettings[MIC_TYPE_INDEX] = VOICE_COMMUNICATION;
        outSettings[USE_BUILDIN_AEC] = false;
    }
}

#ifdef __cplusplus
}
#endif





