#define GamePackageName "com.ekkorr.cf" // define the game package name here please

bool noCost,addGold,addEnergy,win;
int teamDamage = 1;

long (*old_getUpdateEnergy)(void *instance,long energy);
long (*old_getUpdateGold)(void *instance,long gold);
void (*old_getOnUpdate)(void *instance,float time);
float (*old_getTeamDamage)(void *instance);
void (*allKillVictory)(void *instance,float time);

float getTeamDamage(void *instance){
    if (instance != NULL ){
        float damage = old_getTeamDamage(instance);
        float allDamage = damage *= teamDamage;
        return allDamage;
    }
    return old_getTeamDamage(instance);
}
void getOnUpdate(void *instance,float time){
    if(instance != NULL){
        if(win){
            return allKillVictory(instance,time);
        }
    }
    return old_getOnUpdate(instance,time);
}

long getUpdateGold(void *instance,long gold) {
    if(instance != NULL){
        if(noCost){
            if (gold < 0){
                    gold = 0;
            }
        }
        if(addGold){
            gold = 50000;
            LOGW("Success Add Gold 50K");
            addGold = false;
        }
    }
    return old_getUpdateGold(instance,gold);
}
long getUpdateEnergy(void *instance,long energy) {
    if (instance != NULL){
        if(noCost){
            if(energy < 0){
                energy = 0;
            }
        }
        if(addEnergy){
            energy = 50000;
            LOGW("Success Add Energy 50K");
            addEnergy = false;
        }
    }
    return old_getUpdateEnergy(instance,energy);
}
void Pointers() {
    // allKillVictory Assembly-Csharp->Ekkorr.CF.Battle->Battle -> AllKillVictory
    allKillVictory = (void(*)(void*, float)) (g_il2cppBaseMap.startAddress + string2Offset(OBFUSCATE("0xD509E0")));
}
void Hooks() {
    // Update Gold Assembly-Csharp->Ekkorr.CF.Battle->BattlePlayer -> UpdateGold
    // Update Energy Assembly-Csharp->Ekkorr.CF.Battle->BattlePlayer -> UpdateEnergy
    // OnUpdate Assembly-Csharp->Ekkorr.CF.Battle->Battle -> onUpdate
    // Update Energy Assembly-Csharp->Ekkorr.CF.Battle->EnemyPlayer -> UpdateEnergy

    HOOK("0xD6B944", getTeamDamage, old_getTeamDamage);
    HOOK("0xD50E44", getOnUpdate, old_getOnUpdate);
    HOOK("0xD68AE0", getUpdateEnergy, old_getUpdateEnergy);
    HOOK("0xD68AAC", getUpdateGold, old_getUpdateGold);
}

TextUnformatted(OBFUSCATE("Damage Tower Team And U:"));
SliderInt(OBFUSCATE(""), &teamDamage, 1, 100, OBFUSCATE("%d"), 0);
Checkbox(OBFUSCATE("Free Upgrade in Game"), &noCost);
Checkbox(OBFUSCATE("Auto Win"), &win);
TextUnformatted(OBFUSCATE("for add gold and energy u need upgrade something"));
if (Button(OBFUSCATE("Add Gold 50K"))) {
    addGold = true;
}
if (Button(OBFUSCATE("Add Energy 50K"))) {
    addEnergy = true;
}

