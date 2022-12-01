// NPlayer
// Token: 0x060045C8 RID: 17864 RVA: 0x00017070 File Offset: 0x00015270
[Token(Token = "0x60045C8")]
[Address(RVA = "0x770CC8", Offset = "0x770CC8", VA = "0x770CC8")]
public NTeamFlag get_TeamFlag()
{
	return NTeamFlag.None;
}

// NPlayer
// Token: 0x0600461E RID: 17950 RVA: 0x00002053 File Offset: 0x00000253
[Token(Token = "0x600461E")]
[Address(RVA = "0x783A54", Offset = "0x783A54", VA = "0x783A54")]
public void TakeDamage(NVitalDealType vitalDealType, int adDamage, int apDamage, bool notiBuff, NPlayer attPlayer, NSkillInstance skillInst, bool printDamage = true, bool chkCHD = false)
{
}



bool god;
int sliderValue = 1,nilai = 0;
int (*teamflag)(void *instance);
bool (*old_get_undectect)(void *instance);
void (*old_get_takedamage)(void *instance,int NVitalDealType , int adDamage, int apDamage, bool notiBuff,void *NPlayer, void *NSkillInstance, bool printDamage, bool chkCHD);
void get_takedamage(void *instance,int NVitalDealType, int adDamage, int apDamage, bool notiBuff,void *NPlayer, void *NSkillInstance, bool printDamage, bool chkCHD){
    if (instance != NULL){
        int team = teamflag(instance);
        if(team == 1 && god){
            return old_get_takedamage(instance,NVitalDealType,adDamage * 0,apDamage * 0,notiBuff,NPlayer,NSkillInstance,true,false);
        }
        if (team == 2 && sliderValue > 1){
            return old_get_takedamage(instance,NVitalDealType,adDamage * nilai,apDamage * nilai,notiBuff,NPlayer,NSkillInstance,true,false);
        }
        return old_get_takedamage(instance,NVitalDealType,adDamage,apDamage,notiBuff,NPlayer,NSkillInstance,true,false);
    }
}
bool get_undetect(void *instance){
    if(instance != NULL){
        return false;
    }
}

 HOOK_LIB("libil2cpp.so", "0x8B375C", get_undetect, old_get_undectect);
    HOOK_LIB("libil2cpp.so", "0x783A54", get_takedamage, old_get_takedamage);
    teamflag = (int (*)(void *)) getAbsoluteAddress(targetLibName, 0x770CC8);
    
    const char *features[] = {
            OBFUSCATE("Category_The Category"), //Not counted
            OBFUSCATE("Toggle_GOD MODE"),
            OBFUSCATE("RichTextView_<big> <font color='red'>Noted x2 = x20 Read this!!!</font>"),
            OBFUSCATE("SeekBar_Damage X_1_5")
            
    switch (featNum) {        
            case 0:
            god = boolean;
            //PATCH_LIB_SWITCH("libil2cpp.so", "0x783A54", "12 07 A0 E3 1E FF 2F E1", boolean);
            //Toast(env, obj, OBFUSCATE("Cheat Actived"), ToastLength::LENGTH_SHORT);
            break;
        case 1:
            if (value == 2){
                nilai = 20;
            }
            if (value == 3){
                nilai = 30;
            }
            if (value == 4){
                nilai = 40;
            }
            if (value == 5){
                nilai = 50;
            }
            sliderValue = value;
            break;
            }
            }
