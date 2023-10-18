#define GamePackageName "com.ekkorr.cf" // define the game package name here please

bool noCost,addGold,addEnergy;

long (*old_getUpdateEnergy)(void *instance,long energy);
long (*old_getUpdateGold)(void *instance,long gold);

long getUpdateGold(void *instance,long gold) {
    if(instance != NULL){
        if(noCost){
            if (gold < 0){
                    gold = 0;
            }
        }
        if(addGold){
            gold = 50000;
            LOGW("Berhasil Tambah Gold 50K");
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
            LOGW("Berhasil Tambah Gold 50K");
            addEnergy = false;
        }
    }
    return old_getUpdateEnergy(instance,energy);
}
void Hooks() {
    // update Gold Assembly-Csharp->Ekkorr.CF.Battle->BattlePlayer -> UpdateGold
    // update Gold Assembly-Csharp->Ekkorr.CF.Battle->BattlePlayer -> UpdateEnergy
    HOOK("0xD68AE0", getUpdateEnergy, old_getUpdateEnergy);
    HOOK("0xD68AAC", getUpdateGold, old_getUpdateGold);
}

Checkbox(OBFUSCATE("Free Upgrade in Game"), &noCost);
                if (Button(OBFUSCATE("Add Gold"))) {
                    // code for button action
                    addGold = true;
                }
                if (Button(OBFUSCATE("Add Energy"))) {
                    // code for button action
                    addEnergy = true;
                }

