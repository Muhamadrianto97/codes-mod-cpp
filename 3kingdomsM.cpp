// cBattleDamage
// Token: 0x06001368 RID: 4968 RVA: 0x00007290 File Offset: 0x00005490
[Token(Token = "0x6001368")]
[Address(RVA = "0x6B2990", Offset = "0x6B2990", VA = "0x6B2990")]
public static bool GetCri(cHeroInfo attacker, cHeroInfo target)
{
	return default(bool);
}
public static long GetDamage(cHeroInfo attacker, cHeroInfo target, cBattleSkill skill)
{
	return 0L;
}
public static bool GetEvasion(cHeroInfo attacker, cHeroInfo target, cBattleSkill skill)
{
	return default(bool);
}

// cHeroInfo
// Token: 0x0600154B RID: 5451 RVA: 0x00008418 File Offset: 0x00006618
[Token(Token = "0x600154B")]
[Address(RVA = "0x7453A0", Offset = "0x7453A0", VA = "0x7453A0")]
public bool get_IsEnemy()
{
	return default(bool);
}


bool critical,evasion,item;
int sliderValue = 1,nilai = 0;
int (*old_getitemamount)(void *instance);
bool(*old_getcritical)(void *instance,void *attacker,void *target);
bool(*old_getevasion)(void *instance,void *attacker,void *target,void *skill);
long (*old_getdamage)(void *instance,void *attacker,void *target,void *skill);
bool (*get_enemy)(void *instance);


bool getcritical(void *instance,void *attacker,void *target) {
    if (instance != NULL && critical) {
    bool enemy = get_enemy(instance);
    if(!enemy){
    return true;
    }
    }
    return old_getcritical(instance,attacker,target);
}

bool getevasion(void *instance,void *attacker,void *target,void *skill) {
    if (instance != NULL && evasion) {
    bool enemy = get_enemy(instance);
    if(enemy){
    return true;
    }else{
    return false;
    }
    }
    return old_getevasion(instance,attacker,target,skill);
}
long getdamage(void *instance,void *attacker,void *target,void *skill) {
    if (instance != NULL && sliderValue > 1) {
    bool enemy = get_enemy(instance);
    if(!enemy){
    return old_getdamage(instance,attacker,target,skill) * nilai;
    }
    }
    return old_getdamage(instance,attacker,target,skill);
}

 HOOK_LIB("libil2cpp.so", "0x6B2990", getcritical, old_getcritical);
    HOOK_LIB("libil2cpp.so", "0x6B2DF0", getevasion, old_getevasion);
    HOOK_LIB("libil2cpp.so", "0x6B34DC", getdamage, old_getdamage);
    get_enemy = (bool (*)(void *)) getAbsoluteAddress(targetLibName, 0x7453A0);

OBFUSCATE("Category_The Category"), //Not counted
            OBFUSCATE("SeekBar_Damage x_1_10"),
            OBFUSCATE("ButtonOnOff_Always Critical"),
            OBFUSCATE("ButtonOnOff_Always Dodge"),
            OBFUSCATE("RichTextView_<big> <font color='red'>Noted x2 = x4 x3 = x6... x5 = x10!!!</font>")
              
              
              case 0:
            sliderValue = value;
            nilai = sliderValue * 2;
            break;
        case 1:
            critical = boolean;
            break;
        case 2:
            evasion = boolean;
            break;
        case 3:
            item = boolean;
            break;
