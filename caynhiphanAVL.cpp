#include <iostream>
using namespace std;

struct Nut {
    int khoa;
    Nut* trai;
    Nut* phai;
    int chieuCao;
};

int layChieuCao(Nut* nut) {
    return nut ? nut->chieuCao : 0;
}

int layHeSoCanBang(Nut* nut) {
    return nut ? layChieuCao(nut->trai) - layChieuCao(nut->phai) : 0;
}

Nut* taoNut(int khoa) {
    Nut* nut = new Nut();
    nut->khoa = khoa;
    nut->trai = nut->phai = nullptr;
    nut->chieuCao = 1;
    return nut;
}

Nut* xoayPhai(Nut* y) {
    Nut* x = y->trai;
    Nut* T2 = x->phai;
    
    x->phai = y;
    y->trai = T2;
    
    y->chieuCao = max(layChieuCao(y->trai), layChieuCao(y->phai)) + 1;
    x->chieuCao = max(layChieuCao(x->trai), layChieuCao(x->phai)) + 1;
    
    return x;
}

Nut* xoayTrai(Nut* x) {
    Nut* y = x->phai;
    Nut* T2 = y->trai;
    
    y->trai = x;
    x->phai = T2;
    
    x->chieuCao = max(layChieuCao(x->trai), layChieuCao(x->phai)) + 1;
    y->chieuCao = max(layChieuCao(y->trai), layChieuCao(y->phai)) + 1;
    
    return y;
}

Nut* chen(Nut* nut, int khoa) {
    if (!nut) return taoNut(khoa);
    
    if (khoa < nut->khoa)
        nut->trai = chen(nut->trai, khoa);
    else if (khoa > nut->khoa)
        nut->phai = chen(nut->phai, khoa);
    else
        return nut;
    
    nut->chieuCao = 1 + max(layChieuCao(nut->trai), layChieuCao(nut->phai));
    
    int canBang = layHeSoCanBang(nut);
    
    if (canBang > 1 && khoa < nut->trai->khoa)
        return xoayPhai(nut);
    
    if (canBang < -1 && khoa > nut->phai->khoa)
        return xoayTrai(nut);
    
    if (canBang > 1 && khoa > nut->trai->khoa) {
        nut->trai = xoayTrai(nut->trai);
        return xoayPhai(nut);
    }
    
    if (canBang < -1 && khoa < nut->phai->khoa) {
        nut->phai = xoayPhai(nut->phai);
        return xoayTrai(nut);
    }
    
    return nut;
}

void duyetTruoc(Nut* goc) {
    if (goc) {
        cout << goc->khoa << " ";
        duyetTruoc(goc->trai);
        duyetTruoc(goc->phai);
    }
}

int main() {
    Nut* goc = nullptr;
    goc = chen(goc, 10);
    goc = chen(goc, 20);
    goc = chen(goc, 30);
    goc = chen(goc, 40);
    goc = chen(goc, 50);
    goc = chen(goc, 25);
    
    cout << "Duyet truoc cua cay AVL: ";
    duyetTruoc(goc);
    
    return 0;
}
