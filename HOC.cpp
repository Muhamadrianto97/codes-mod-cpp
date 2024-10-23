#include <list>
#include <vector>
#include <string.h>
#include <pthread.h>
#include <thread>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>
#include "Includes/Logger.h"
#include "Includes/obfuscate.h"
#include "Includes/Utils.h"
#include "KittyMemory/MemoryPatch.h"
#include "Menu/Setup.h"

//Target lib here
#define targetLibName OBFUSCATE("libil2cpp.so")

#include "Includes/Macros.h"
bool deathstrike,nodamage,morexp,attackspeed,distance,ricochet,multishot;
void (*old_Update)(void *instance);
void (*old_addxp)(void *instance,int addexp,bool boost);
bool (*get_IsAI)(void *instance);
bool isDefaultInitialized = false;

void get_addxp(void *instance,int addexp,bool boost){
    if(instance != NULL){
        bool ai = get_IsAI(instance);
        if(!ai && morexp){
            return old_addxp(instance,addexp * 2,boost);
        }
    }
    return old_addxp(instance,addexp,boost);
}

void get_Update(void *instance){
    static float defaultDeathstrikeValue;
    static float defaultNoDamageValue1, defaultNoDamageValue2;
    static float defaultAttackSpeedValue;
    static float defaultDistanceValue1, defaultDistanceValue2;
    static int defaultRicochetValue;
    static int defaultMultishotValue;

    if(instance != NULL){
        //Gameplay.Characters.CharacterEntity.characterBaseData (Field)
        void *characterBaseData = *(void**)((uint64_t)instance + 0x24);
        bool ai = get_IsAI(instance);
        if(characterBaseData != NULL && !ai) {
            // Cek apakah nilai default sudah diambil
            if (!isDefaultInitialized) {
                // Ambil nilai default dari memory
                defaultDeathstrikeValue = *(float *)((uint64_t)characterBaseData + 0xF8);
                defaultNoDamageValue1 = *(float *)((uint64_t)characterBaseData + 0x104);
                defaultNoDamageValue2 = *(float *)((uint64_t)characterBaseData + 0x108);
                defaultAttackSpeedValue = *(float *)((uint64_t)characterBaseData + 0xE0);
                defaultDistanceValue1 = *(float *)((uint64_t)characterBaseData + 0x58);
                defaultDistanceValue2 = *(float *)((uint64_t)characterBaseData + 0x8C);
                defaultRicochetValue = *(int *)((uint64_t)characterBaseData + 0x60);
                defaultMultishotValue = *(int *)((uint64_t)characterBaseData + 0x68);

                isDefaultInitialized = true; // Tandai bahwa nilai default sudah diambil
            }
            if (deathstrike) {
                *(float *) ((uint64_t) characterBaseData + 0xF8) = 100.0f;
            } else{
                *(float *) ((uint64_t) characterBaseData + 0xF8) = defaultDeathstrikeValue;
            }
            if (nodamage) {
                *(float *) ((uint64_t) characterBaseData + 0x104) = 100.0f;
                *(float *) ((uint64_t) characterBaseData + 0x108) = 100.0f;
            } else{
                *(float *) ((uint64_t) characterBaseData + 0x104) = defaultNoDamageValue1;
                *(float *) ((uint64_t) characterBaseData + 0x108) = defaultNoDamageValue2;
            }
            if (attackspeed) {
                *(float *) ((uint64_t) characterBaseData + 0xE0) = 5.0f;
            }else{
                *(float *) ((uint64_t) characterBaseData + 0xE0) = defaultAttackSpeedValue;
            }
            if (distance) {
                *(float *) ((uint64_t) characterBaseData + 0x58) = 20.0f;
                *(float *) ((uint64_t) characterBaseData + 0x8C) = 20.0f;
            }else{
                *(float *) ((uint64_t) characterBaseData + 0x58) = defaultDistanceValue1;
                *(float *) ((uint64_t) characterBaseData + 0x8C) = defaultDistanceValue2;
            }
            if (ricochet) {
                *(int *) ((uint64_t) characterBaseData + 0x60) = 20;
            }else{
                *(int *) ((uint64_t) characterBaseData + 0x60) = defaultRicochetValue;
            }
            if (multishot) {
                *(int *) ((uint64_t) characterBaseData + 0x68) = 10;
            }else{
                *(int *) ((uint64_t) characterBaseData + 0x68) = defaultMultishotValue;
            }
        }
    }
    return old_Update(instance);
}

// we will run our hacks in a new thread so our while loop doesn't block process main thread
void *hack_thread(void *) {
    LOGI(OBFUSCATE("pthread created"));

    //Check if target lib is loaded
    do {
        sleep(1);
    } while (!isLibraryLoaded(targetLibName));

    //Anti-lib rename
    /*
    do {
        sleep(1);
    } while (!isLibraryLoaded("libYOURNAME.so"));*/

    LOGI(OBFUSCATE("%s has been loaded"), (const char *) targetLibName);

#if defined(__aarch64__) //To compile this code for arm64 lib only. Do not worry about greyed out highlighting code, it still works
    // Hook example. Comment out if you don't use hook
    // Strings in macros are automatically obfuscated. No need to obfuscate!

#else //To compile this code for armv7 lib only.
    //  Gameplay.Characters.PlayerController.FixedUpdate
    HOOK_LIB("libil2cpp.so", "0x174DD00", get_Update, old_Update);

    // Gameplay.Characters.PlayerController.AddXp
    HOOK_LIB("libil2cpp.so", "0x174AA94", get_addxp, old_addxp);

    // Gameplay.Characters.CharacterEntity.get_IsAI
    get_IsAI = (bool (*)(void *)) getAbsoluteAddress(targetLibName, 0x16F4E48);

    LOGI(OBFUSCATE("Done"));
#endif

    //Anti-leech
    /*if (!iconValid || !initValid || !settingsValid) {
        //Bad function to make it crash
        sleep(5);
        int *p = 0;
        *p = 0;
    }*/

    return NULL;
}

// Do not change or translate the first text unless you know what you are doing
// Assigning feature numbers is optional. Without it, it will automatically count for you, starting from 0
// Assigned feature numbers can be like any numbers 1,3,200,10... instead in order 0,1,2,3,4,5...
// ButtonLink, Category, RichTextView and RichWebView is not counted. They can't have feature number assigned
// Toggle, ButtonOnOff and Checkbox can be switched on by default, if you add True_. Example: CheckBox_True_The Check Box
// To learn HTML, go to this page: https://www.w3schools.com/

jobjectArray GetFeatureList(JNIEnv *env, jobject context) {
    jobjectArray ret;

    const char *features[] = {
            OBFUSCATE("Category_The Category"), //Not counted
            OBFUSCATE("Toggle_1 hit mati"),
            OBFUSCATE("Toggle_Damage Musuh 1"),
            OBFUSCATE("Toggle_Exp Kali 2"),
            OBFUSCATE("Toggle_Jarak Tembak Jauh"),
            OBFUSCATE("Toggle_Attack Speed Cepat"),
            OBFUSCATE("Toggle_Setiap Nembak Mantul"),
            OBFUSCATE("Toggle_MultiShot x10")
    };

    //Now you dont have to manually update the number everytime;
    int Total_Feature = (sizeof features / sizeof features[0]);
    ret = (jobjectArray)
            env->NewObjectArray(Total_Feature, env->FindClass(OBFUSCATE("java/lang/String")),
                                env->NewStringUTF(""));

    for (int i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));

    return (ret);
}

void Changes(JNIEnv *env, jclass clazz, jobject obj,
             jint featNum, jstring featName, jint value,
             jboolean boolean, jstring str) {

    LOGD(OBFUSCATE("Feature name: %d - %s | Value: = %d | Bool: = %d | Text: = %s"), featNum,
         env->GetStringUTFChars(featName, 0), value,
         boolean, str != NULL ? env->GetStringUTFChars(str, 0) : "");

    //BE CAREFUL NOT TO ACCIDENTLY REMOVE break;

    switch (featNum) {
        case 0:
            deathstrike = boolean;
            break;
        case 1:
            nodamage = boolean;
            break;
        case 2:
            morexp = boolean;
            break;
        case 3:
            distance = boolean;
            break;
        case 4:
            attackspeed = boolean;
            break;
        case 5:
            ricochet = boolean;
            break;
        case 6:
            multishot = boolean;
            break;
            
    }
}

__attribute__((constructor))
void lib_main() {
    // Create a new thread so it does not block the main thread, means the game would not freeze
    pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);
}

int RegisterMenu(JNIEnv *env) {
    JNINativeMethod methods[] = {
            {OBFUSCATE("Icon"), OBFUSCATE("()Ljava/lang/String;"), reinterpret_cast<void *>(Icon)},
            {OBFUSCATE("IconWebViewData"),  OBFUSCATE("()Ljava/lang/String;"), reinterpret_cast<void *>(IconWebViewData)},
            {OBFUSCATE("IsGameLibLoaded"),  OBFUSCATE("()Z"), reinterpret_cast<void *>(isGameLibLoaded)},
            {OBFUSCATE("Init"),  OBFUSCATE("(Landroid/content/Context;Landroid/widget/TextView;Landroid/widget/TextView;)V"), reinterpret_cast<void *>(Init)},
            {OBFUSCATE("SettingsList"),  OBFUSCATE("()[Ljava/lang/String;"), reinterpret_cast<void *>(SettingsList)},
            {OBFUSCATE("GetFeatureList"),  OBFUSCATE("()[Ljava/lang/String;"), reinterpret_cast<void *>(GetFeatureList)},
    };

    jclass clazz = env->FindClass(OBFUSCATE("com/android/support/Menu"));
    if (!clazz)
        return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;
    return JNI_OK;
}

int RegisterPreferences(JNIEnv *env) {
    JNINativeMethod methods[] = {
            {OBFUSCATE("Changes"), OBFUSCATE("(Landroid/content/Context;ILjava/lang/String;IZLjava/lang/String;)V"), reinterpret_cast<void *>(Changes)},
    };
    jclass clazz = env->FindClass(OBFUSCATE("com/android/support/Preferences"));
    if (!clazz)
        return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;
    return JNI_OK;
}

int RegisterMain(JNIEnv *env) {
    JNINativeMethod methods[] = {
            {OBFUSCATE("CheckOverlayPermission"), OBFUSCATE("(Landroid/content/Context;)V"), reinterpret_cast<void *>(CheckOverlayPermission)},
    };
    jclass clazz = env->FindClass(OBFUSCATE("com/android/support/Main"));
    if (!clazz)
        return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;

    return JNI_OK;
}

extern "C"
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    vm->GetEnv((void **) &env, JNI_VERSION_1_6);
    if (RegisterMenu(env) != 0)
        return JNI_ERR;
    if (RegisterPreferences(env) != 0)
        return JNI_ERR;
    if (RegisterMain(env) != 0)
        return JNI_ERR;
    return JNI_VERSION_1_6;
}
