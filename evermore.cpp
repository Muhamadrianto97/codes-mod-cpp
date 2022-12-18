[Token(Token = "0x6000426")]
[Address(RVA = "0x734E9C", Offset = "0x734E9C", VA = "0x734E9C")]
public float AddUltimateCharge(float amount)
{
	return 0f;
}

public void AddManaToTeam(BattleTeam team, int amount, bool refreshSkills = true)
{
  //player = 0
  //enemy = 1
}

[Token(Token = "0x6000429")]
[Address(RVA = "0x73B844", Offset = "0x73B844", VA = "0x73B844")]
public bool StartTurn()
{
	return default(bool);
  //is character
  [Token(Token = "0x4000421")]
[FieldOffset(Offset = "0x116")]
[ReadOnly]
public bool isCharacter;
  
  //attack
  [Token(Token = "0x400040A")]
[FieldOffset(Offset = "0xC0")]
[ReadOnly]
public float attackMod;
  
  //critical chance
  [Token(Token = "0x4000408")]
[FieldOffset(Offset = "0xB8")]
[ReadOnly]
public float criticalChanceMod;
  
  //health point
  [Token(Token = "0x40003FC")]
[FieldOffset(Offset = "0x88")]
[ReadOnly]
public int currHealthPoint;
}

bool addmana,ultimate,criticalchance,onehit,godmode;
void (*old_mana)(void *instance,int team,int amount,bool refreshSkills);
float (*old_ultimate)(void *instance,float amount);
bool (*old_startturn)(void *instance);

float get_ultimate(void *instance,float amount){
    if(instance != NULL){
        bool ischaracter = *(bool *) ((uint64_t) instance + 0x116);
        if(ultimate && ischaracter){
            return old_ultimate(instance,10);
        }
        return old_ultimate(instance,amount);
    }
}
void get_mana(void *instance,int team,int amount) {
    if (instance != NULL) {
        if (addmana) {
            return old_mana(instance,0,10,true);
        }
    }
    return old_mana(instance,team,amount,true);
}
bool startturn(void *instance){
     if(instance != NULL){
         bool ischaracter = *(bool *) ((uint64_t) instance + 0x116);
         if (onehit && !ischaracter) {
                 *(int *) ((uint64_t) instance + 0x88) = 1;
         }
         if (!ischaracter && godmode){
             *(float *) ((uint64_t) instance + 0xC0) = 0.0f;
         }
         if (criticalchance && ischaracter){
             *(float *) ((uint64_t) instance + 0xB8) = 100.0f;
         }
     }
     return old_startturn(instance);
}

    HOOK_LIB("libil2cpp.so", "0x5EB29C", get_mana, old_mana);
    HOOK_LIB("libil2cpp.so", "0x734E9C", get_ultimate, old_ultimate);
    HOOK_LIB("libil2cpp.so", "0x73B844", startturn,old_startturn);


OBFUSCATE("Category_The Category"), //Not counted
OBFUSCATE("RichTextView_NOTE :"
                      "<br /><font color='red'>ONE HIT ACTIVE AFTER ENEMY HIT</font>"),
            OBFUSCATE("ButtonOnOff_infinite Mana"),
            OBFUSCATE("ButtonOnOff_Infinite Ultimate"),
            OBFUSCATE("ButtonOnOff_One Hit"),
            OBFUSCATE("ButtonOnOff_God Mode"),
            OBFUSCATE("ButtonOnOff_Always Critical")
 }
switch (featNum) {
        case 0:
            addmana = boolean;
            break;
        case 1:
            ultimate = boolean;
            break;
        case 2:
            onehit = boolean;
            break;
        case 3:
            godmode = boolean;
            break;
        case 4:
            criticalchance = boolean;
            break;
}
