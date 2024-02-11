#include <bits/stdc++.h>
#define MAX 100000
#define MIN -100000
#define limit 11 //precisa ser ímpar
using namespace std;

int checharTab(string inTab){
    int v1 = 0, v2 = 0, c = 0, a = 0; 

    for (char i : inTab){
        if (i - '0' < 0 || i - '0' > 4){
            return 0;
        }
        
        if (i == '1'){
            v1++;
            continue;
        }

        if (i == '2'){
            v2++;
            continue;
        }

        if (i == '3'){
            a++;
            continue;
        }
 
        if (i == '4'){
            c++;
            continue;
        }
    }
    return v1 == 1 && v2 == 1 && c >= 0 && c <= 1 && a >= 0 && a <= 1;
}

int  minMax(int jogador, int pj[2][2], int pc[2], int pa[2], int vidas[2], int municoes[2], int defesa[2], int n){

    if (vidas[!jogador] <= 0 && n % 2){
        return MAX;
    }

    if (vidas[jogador] <= 0 && n % 2 == 0){
        return MIN;
    }

    if (n == limit){
        if (vidas[jogador] < vidas[!jogador]){
            if (abs(pj[jogador][0] - pc[0]) + abs(pj[jogador][1] - pc[1]) < abs(pj[!jogador][0] - pc[0]) + abs(pj[!jogador][1] - pc[1]))
            {
                if (abs(pj[jogador][0] - pa[0]) + abs(pj[jogador][1] - pa[1]) < abs(pj[!jogador][0] - pa[0]) + abs(pj[!jogador][1] - pa[1]))
                {
                    return 1;
                }
                else{
                    return 2;
                }

            }
            else{
                if (abs(pj[jogador][0] - pa[0]) + abs(pj[jogador][1] - pa[1]) < abs(pj[!jogador][0] - pa[0]) + abs(pj[!jogador][1] - pa[1]))
                {
                    return 3;
                }
                else{
                    return 4;
                }
            }
        }
        else{
            if (abs(pj[jogador][0] - pc[0]) + abs(pj[jogador][1] - pc[1]) < abs(pj[!jogador][0] - pc[0]) + abs(pj[!jogador][1] - pc[1]))
            {
                if (abs(pj[jogador][0] - pa[0]) + abs(pj[jogador][1] - pa[1]) < abs(pj[!jogador][0] - pa[0]) + abs(pj[!jogador][1] - pa[1]))
                {
                    return 2;
                }
                else{
                    return 3;
                }
            }
            else{
                if (abs(pj[jogador][0] - pa[0]) + abs(pj[jogador][1] - pa[1]) < abs(pj[!jogador][0] - pa[0]) + abs(pj[!jogador][1] - pa[1]))
                {
                    return 3;
                }
                else{
                    return 5;
                }               
            }

        }
    }

    if (pj[jogador][0] == pc[0] && pj[jogador][1] == pc[1]){
        vidas[jogador] = 9;
        pc[0] = -1;
        pc[1] = -1;
    }

    if (pj[jogador][0] == pa[0] && pj[jogador][1] == pa[1]){
        municoes[jogador] = 5;
        pa[0] = -1;
        pa[1] = -1;
    }

    int p;
    if (n % 2){
        vector<int> m(6, MIN);
        //ataque
        if (abs(pj[jogador][0] - pj[!jogador][0]) == 1 && abs(pj[jogador][1] - pj[!jogador][1]) == 1){
            int mm = municoes[jogador], mv = vidas[!jogador];
            if (municoes[jogador]){
                vidas[!jogador] -= 2 - defesa[!jogador];
                municoes[jogador]--;
            }
            else{
                vidas[!jogador] -= 1 - defesa[!jogador];
            }
            defesa[0] = 0; defesa[1] = 0;
            m[0] = minMax(jogador, pj, pc, pa, vidas, municoes, defesa, n + 1);
            municoes[jogador] = mm, vidas[!jogador] = mv;
        }
        defesa[0] = 0; defesa[1] = 0;

        //superior
        if (pj[jogador][0] > 0 && pj[jogador][1] != pj[!jogador][1] && pj[jogador][0] - 1 != pj[!jogador][0]){
            pj[jogador][0]--;
            m[1] = minMax(jogador, pj, pc, pa, vidas, municoes, defesa, n + 1);
            pj[jogador][0]++;
        }

        //direita
        if (pj[jogador][1] < 4 && pj[jogador][1] + 1 != pj[!jogador][1] && pj[jogador][0] != pj[!jogador][0]){
            pj[jogador][1]++;
            m[2] = minMax(jogador, pj, pc, pa, vidas, municoes, defesa, n + 1);
            pj[jogador][1]--;
        }

        //inferior
        if (pj[jogador][0] < 4 && pj[jogador][1] != pj[!jogador][1] && pj[jogador][0] + 1 != pj[!jogador][0]){
            pj[jogador][0]++;
            m[3] = minMax(jogador, pj, pc, pa, vidas, municoes, defesa, n + 1);
            pj[jogador][0]--;
        }

        //esquerda
        if (pj[jogador][1] > 0 && pj[jogador][1] - 1 != pj[!jogador][1] && pj[jogador][0] != pj[!jogador][0]){
            pj[jogador][1]--;
            m[4] = minMax(jogador, pj, pc, pa, vidas, municoes, defesa, n + 1);
            pj[jogador][1]++;
        }

        //defesa
        if (abs(pj[jogador][0] - pj[!jogador][0]) == 1 && abs(pj[jogador][1] - pj[!jogador][1]) == 1){
            defesa[jogador] = 1;
            m[5] = minMax(jogador, pj, pc, pa, vidas, municoes, defesa, n + 1);
        }
        p = *max_element(m.begin(), m.end());
    }
    else{
        vector<int> m(6, MAX);
        jogador = !jogador;
        //ataque
        if (abs(pj[jogador][0] - pj[!jogador][0]) == 1 && abs(pj[jogador][1] - pj[!jogador][1]) == 1){
            int mm = municoes[jogador], mv = vidas[!jogador];
            if (municoes[jogador]){
                vidas[!jogador] -= 2 - defesa[!jogador];
                municoes[jogador]--;
            }
            else{
                vidas[!jogador] -= 1 - defesa[!jogador];
            }
            defesa[0] = 0; defesa[1] = 0;
            m[0] = minMax(jogador, pj, pc, pa, vidas, municoes, defesa, n + 1);
            municoes[jogador] = mm, vidas[!jogador] = mv;
        }
        defesa[0] = 0; defesa[1] = 0;

        //superior
        if (pj[jogador][0] > 0 && pj[jogador][1] != pj[!jogador][1] && pj[jogador][0] - 1 != pj[!jogador][0]){
            pj[jogador][0]--;
            m[1] = minMax(jogador, pj, pc, pa, vidas, municoes, defesa, n + 1);
            pj[jogador][0]++;
        }

        //direita
        if (pj[jogador][1] < 4 && pj[jogador][1] + 1 != pj[!jogador][1] && pj[jogador][0] != pj[!jogador][0]){
            pj[jogador][1]++;
            m[2] = minMax(jogador, pj, pc, pa, vidas, municoes, defesa, n + 1);
            pj[jogador][1]--;
        }

        //inferior
        if (pj[jogador][0] < 4 && pj[jogador][1] != pj[!jogador][1] && pj[jogador][0] + 1 != pj[!jogador][0]){
            pj[jogador][0]++;
            m[3] = minMax(jogador, pj, pc, pa, vidas, municoes, defesa, n + 1);
            pj[jogador][0]--;
        }

        //esquerda
        if (pj[jogador][1] > 0 && pj[jogador][1] - 1 != pj[!jogador][1] && pj[jogador][0] != pj[!jogador][0]){
            pj[jogador][1]--;
            m[4] = minMax(jogador, pj, pc, pa, vidas, municoes, defesa, n + 1);
            pj[jogador][1]++;
        }

        //defesa
        if (abs(pj[jogador][0] - pj[!jogador][0]) == 1 && abs(pj[jogador][1] - pj[!jogador][1]) == 1){
            defesa[jogador] = 1;
            m[5] = minMax(jogador, pj, pc, pa, vidas, municoes, defesa, n + 1);
        }
        jogador = !jogador;
        p = *min_element(m.begin(), m.end());        
    }
    return p;
}

void jogada(int jogador, int pj[2][2], int pc[2], int pa[2], int vidas[2], int municoes[2], int defesa[2], int n){
    vector<int> m(6, MIN - 1);
        //ataque
        if (abs(pj[jogador][0] - pj[!jogador][0]) <= 1 && abs(pj[jogador][1] - pj[!jogador][1]) <= 1){
            int mm = municoes[jogador], mv = vidas[!jogador];
            if (municoes[jogador]){
                vidas[!jogador] -= 2 - defesa[!jogador];
                municoes[jogador]--;
            }
            else{
                vidas[!jogador] -= 1 - defesa[!jogador];
            }
            defesa[0] = 0; defesa[1] = 0;
            m[0] = minMax(jogador, pj, pc, pa, vidas, municoes, defesa, n + 1);
            municoes[jogador] = mm, vidas[!jogador] = mv;
        }
        defesa[0] = 0; defesa[1] = 0;

        //superior
        if (pj[jogador][0] > 0 && pj[jogador][1] != pj[!jogador][1] && pj[jogador][0] - 1 != pj[!jogador][0]){
            pj[jogador][0]--;
            m[1] = minMax(jogador, pj, pc, pa, vidas, municoes, defesa, n + 1);
            pj[jogador][0]++;
        }

        //direita
        if (pj[jogador][1] < 4 && pj[jogador][1] + 1 != pj[!jogador][1] && pj[jogador][0] != pj[!jogador][0]){
            pj[jogador][1]++;
            m[2] = minMax(jogador, pj, pc, pa, vidas, municoes, defesa, n + 1);
            pj[jogador][1]--;
        }

        //inferior
        if (pj[jogador][0] < 4 && pj[jogador][1] != pj[!jogador][1] && pj[jogador][0] + 1 != pj[!jogador][0]){
            pj[jogador][0]++;
            m[3] = minMax(jogador, pj, pc, pa, vidas, municoes, defesa, n + 1);
            pj[jogador][0]--;
        }

        //esquerda
        if (pj[jogador][1] > 0 && pj[jogador][1] - 1 != pj[!jogador][1] && pj[jogador][0] != pj[!jogador][0]){
            pj[jogador][1]--;
            m[4] = minMax(jogador, pj, pc, pa, vidas, municoes, defesa, n + 1);
            pj[jogador][1]++;
        }

        //defesa
        if (abs(pj[jogador][0] - pj[!jogador][0]) == 1 && abs(pj[jogador][1] - pj[!jogador][1]) == 1){
            defesa[jogador] = 1;
            m[5] = minMax(jogador, pj, pc, pa, vidas, municoes, defesa, n + 1);
        }   
        int p = distance(m.begin(), max_element(m.begin(), m.end()));

        if (p == 0){
            cout << "Ataque" << endl;
        }

        if (p == 1){
            cout << "Mover para cima" << endl;
        }

        if (p == 2){
            cout << "Mover para direita" << endl;
        }


        if (p == 3){
            cout << "Mover para baixo" << endl;
        }

        if (p == 4){
            cout << "Mover para esquerda" << endl;
        }

        if (p == 5){
            cout << "Defesa" << endl;
        }
        
        return;
}

int main(int argc, char *argv[]) {

    if (argc != 7){
        cout << "Erro: numero de argumentos invalido" << endl;
        return 1;
    }

    if (argv[1][0] != '1' && argv[1][0] != '2' || argv[1][1] != '\0'){
        cout << "Erro: numero de jogador invalido" << endl;
        return 2;
    }

    int jogador = argv[1][0] - '0';
    string inTab = argv[2];

    if (inTab.size() != 25 || ! checharTab(inTab)){
        cout << "Erro: tabuleiro invalido" << endl;
        return 3;
    }

    if (argv[3][0] - '0' < 0 || argv[3][0] - '0' > 9 || argv[6][1] != '\0'){
        cout << "Erro: numero de vidas invalido" << endl;
        return 4;
    }

    if (argv[4][0] - '0' < 0 || argv[4][0] - '0' > 9 || argv[6][1] != '\0'){
        cout << "Erro: numero de vidas invalido" << endl;
        return 4;
    }

    if (argv[5][0] - '0' < 0 || argv[5][0] - '0' > 5 || argv[5][1] != '\0'){
        cout << "Erro: numero de municoes invalido" << endl;
        return 4;
    }

    if (argv[6][0] - '0' < 0 || argv[6][0] - '0' > 5 || argv[6][1] != '\0'){
        cout << "Erro: numero de municoes invalido" << endl;
        return 4;
    }

    if (!(!(argv[6][0] - '0') && !(argv[6][0] - '0') || !(argv[6][0] - '0') != !(argv[6][0] - '0'))){
        cout << "Erro: numero de municoes invalido" << endl;
        return 4;
    }

    if (!(!(argv[6][0] - '0') != !(argv[6][0] - '0')) && inTab.find('3') == inTab.find('\0')){
        cout << "Erro: numero de municoes invalido" << endl;
        return 4;
    }

    if (!(!(argv[6][0] - '0') && !(argv[6][0] - '0')) && inTab.find('3') != inTab.find('\0')){
        cout << "Erro: numero de municoes invalido" << endl;
        return 4;
    }

    int vidas[2] = {argv[3][0] - '0', argv[4][0] - '0'}, municoes[2] = {argv[5][0] - '0', argv[6][0] - '0'};
    int pj[2][2] = {{(int) inTab.find('1') / 5, (int) inTab.find('1') % 5}, {(int) inTab.find('2')  / 5, (int) inTab.find('2') % 5}}; 
    int pc[2], pa[2];
    if (inTab.find('4') == inTab.find('\0')){
        pc[0] = -1;
        pc[1] = -1;
    }
    else{
        pc[0] = inTab.find('4') / 5;
        pc[1] = inTab.find('4') - 1 % 5;
    }

    if (inTab.find('3') == inTab.find('\0')){
        pc[0] = -1;
        pc[1] = -1;
    }
    else{
        pc[0] = inTab.find('3') - 1 / 5;
        pc[1] = inTab.find('3') - 1 % 5;
    }

    int defesa[2] = {0, 0};

    jogada(jogador - 1, pj, pc, pa, vidas, municoes, defesa, 0);
}