#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 1000
#define DAI 200
#define DAI_MA 20
#define MA_DO_DAI 10
#define NAM_MIN 1900
#define GIA_MIN 50000
#define GIA_MAX 1000000
#define SO_LUONG_MAX 9999
#define DO_RONG_BANG 118
#define CHO_PHEP_MA "0123456789"
#define CHO_PHEP_TEN_NGUOI " .'-"
#define CHO_PHEP_CHUNG "0123456789 .,:'-()"
#define CHO_PHEP_THE_LOAI " .,:'-()"

#define SAP_TEN_AZ 1
#define SAP_GIA_TANG 2
#define SAP_GIA_GIAM 3
#define SAP_TON_GIAM 4

typedef struct {
    char maSach[DAI_MA];
    char tenSach[100];
    char tacGia[100];
    char theLoai[50];
    char nhaXuatBan[100];
    int namXuatBan;
    double giaSach;
    int soLuongTon;
    int soLuongDangMuon;
} Sach;

Sach danhSach[MAX];
int soSach = 0;

/* ===================== NHAP DU LIEU ===================== */

void docDong(char s[], int size) {
    if (fgets(s, size, stdin) == NULL) {
        printf("\nKet thuc nhap lieu. Thoat chuong trinh.\n");
        exit(0);
    }
    int len = (int)strlen(s);
    if (len > 0 && s[len - 1] == '\n') {
        s[len - 1] = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
}

void chuanHoaKhoangTrang(char s[]) {
    int j = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == ' ' && (j == 0 || s[j - 1] == ' ')) continue;
        s[j++] = s[i];
    }
    if (j > 0 && s[j - 1] == ' ') j--;
    s[j] = '\0';
}

int kiemTraKyTu(const char s[], const char choPhep[]) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (!isalpha((unsigned char)s[i]) && strchr(choPhep, s[i]) == NULL) {
            printf("Loi: ky tu khong hop le! Chi nhan chu cai khong dau va cac ky tu: [%s]\n", choPhep);
            return 0;
        }
    }
    return 1;
}

void docChuoi(const char cauHoi[], char s[], int size, const char choPhep[]) {
    while (1) {
        printf("%s", cauHoi);
        docDong(s, size);
        chuanHoaKhoangTrang(s);
        if (s[0] == '\0') printf("Loi: khong duoc de trong!\n");
        else if (kiemTraKyTu(s, choPhep)) return;
    }
}

int docSoNguyen(const char cauHoi[], int min, int max) {
    char buf[DAI];
    char thua;
    int x = 0;
    while (1) {
        printf("%s", cauHoi);
        docDong(buf, DAI);
        if (sscanf(buf, "%d %c", &x, &thua) != 1) {
            printf("Loi: phai nhap mot so nguyen!\n");
        } else if (x < min || x > max) {
            printf("Loi: gia tri phai tu %d den %d!\n", min, max);
        } else {
            return x;
        }
    }
}

double docSoThuc(const char cauHoi[], double min, double max) {
    char buf[DAI];
    char thua;
    double x = 0;
    while (1) {
        printf("%s", cauHoi);
        docDong(buf, DAI);
        if (sscanf(buf, "%lf %c", &x, &thua) != 1) {
            printf("Loi: phai nhap mot so!\n");
        } else if (!(x >= min && x <= max)) {
            printf("Loi: gia tri phai tu %.0f den %.0f!\n", min, max);
        } else {
            return x;
        }
    }
}

int hoiCoKhong(const char cauHoi[]) {
    char buf[DAI];
    while (1) {
        printf("%s (y/n): ", cauHoi);
        docDong(buf, DAI);
        if (strcmp(buf, "y") == 0 || strcmp(buf, "Y") == 0) return 1;
        if (strcmp(buf, "n") == 0 || strcmp(buf, "N") == 0) return 0;
        printf("Loi: chi nhap y hoac n!\n");
    }
}

int docMaSach(const char cauHoi[], char ma[]) {
    printf("(nhap 0 de quay lai)\n");
    while (1) {
        docChuoi(cauHoi, ma, DAI_MA, CHO_PHEP_MA);
        if (strcmp(ma, "0") == 0) return 0;
        if (strlen(ma) == MA_DO_DAI) return 1;
        printf("Loi: ma sach phai dung %d ky tu!\n", MA_DO_DAI);
    }
}

/* ===================== HAM HO TRO ===================== */

int layNamHienTai() {
    time_t t = time(NULL);
    struct tm now = *localtime(&t);
    return now.tm_year + 1900;
}

void dinhDangGia(double gia, char ketQua[]) {
    char so[40];
    sprintf(so, "%.0f", gia);
    int len = (int)strlen(so), j = 0;
    for (int i = 0; i < len; i++) {
        if (i > 0 && (len - i) % 3 == 0) ketQua[j++] = '.';
        ketQua[j++] = so[i];
    }
    ketQua[j] = '\0';
}

int timViTriTheoMa(const char ma[]) {
    for (int i = 0; i < soSach; i++) {
        if (strcmp(danhSach[i].maSach, ma) == 0) return i;
    }
    return -1;
}

void chuyenThuong(const char nguon[], char dich[]) {
    int i = 0;
    for (i = 0; nguon[i] != '\0'; i++) {
        dich[i] = (char)tolower((unsigned char)nguon[i]);
    }
    dich[i] = '\0';
}

int chuaChuoi(const char nguon[], const char tu[]) {
    char a[DAI], b[DAI];
    chuyenThuong(nguon, a);
    chuyenThuong(tu, b);
    return strstr(a, b) != NULL;
}

/* ===================== HIEN THI DANG BANG ===================== */

void inDuongKe() {
    for (int i = 0; i < DO_RONG_BANG; i++) putchar('-');
    putchar('\n');
}

void inTieuDe() {
    inDuongKe();
    printf("%-10s %-22s %-16s %-12s %-14s %-5s %12s %4s %4s %-10s\n",
           "Ma sach", "Ten sach", "Tac gia", "The loai", "NXB",
           "Nam", "Gia", "Ton", "Muon", "Tinh trang");
    inDuongKe();
}

void inSach(const Sach *s) {
    char gia[40];
    dinhDangGia(s->giaSach, gia);
    printf("%-10.10s %-22.22s %-16.16s %-12.12s %-14.14s %5d %12s %4d %4d %-10s\n",
           s->maSach, s->tenSach, s->tacGia, s->theLoai, s->nhaXuatBan,
           s->namXuatBan, gia, s->soLuongTon, s->soLuongDangMuon,
           s->soLuongTon > 0 ? "Con sach" : "Het sach");
}

void inMotSach(int vitri) {
    inTieuDe();
    inSach(&danhSach[vitri]);
}

void hienThiDanhSach() {
    if (soSach == 0) {
        printf("Danh sach chua co sach nao.\n");
        return;
    }
    inTieuDe();
    for (int i = 0; i < soSach; i++) inSach(&danhSach[i]);
    inDuongKe();
    printf("Tong cong: %d dau sach.\n", soSach);
}

/* ===================== THEM / SUA / XOA ===================== */

int hoiTimSach(const char cauHoi[]) {
    char ma[DAI_MA];
    if (!docMaSach(cauHoi, ma)) {
        printf("Da huy, quay lai menu.\n");
        return -1;
    }
    int vitri = timViTriTheoMa(ma);
    if (vitri == -1) {
        printf("Khong tim thay sach co ma \"%s\".\n", ma);
    }
    return vitri;
}

Sach nhapThongTinSach(const char ma[]) {
    Sach s;
    strcpy(s.maSach, ma);
    docChuoi("Ten sach: ", s.tenSach, sizeof(s.tenSach), CHO_PHEP_CHUNG);
    docChuoi("Tac gia: ", s.tacGia, sizeof(s.tacGia), CHO_PHEP_TEN_NGUOI);
    docChuoi("The loai: ", s.theLoai, sizeof(s.theLoai), CHO_PHEP_THE_LOAI);
    docChuoi("Nha xuat ban: ", s.nhaXuatBan, sizeof(s.nhaXuatBan), CHO_PHEP_CHUNG);
    s.namXuatBan = docSoNguyen("Nam xuat ban: ", NAM_MIN, layNamHienTai());
    s.giaSach = docSoThuc("Gia sach (VND): ", GIA_MIN, GIA_MAX);
    s.soLuongTon = docSoNguyen("So luong ton: ", 0, SO_LUONG_MAX);
    s.soLuongDangMuon = 0;
    return s;
}

int nhapSach(Sach *s) {
    char ma[DAI_MA];
    while (1) {
        if (!docMaSach("Ma sach: ", ma)) return 0;
        if (timViTriTheoMa(ma) == -1) break;
        printf("Loi: ma sach \"%s\" da ton tai!\n", ma);
    }
    *s = nhapThongTinSach(ma);
    return 1;
}

void themSach() {
    do {
        if (soSach >= MAX) {
            printf("Loi: danh sach da day (%d sach), khong the them!\n", MAX);
            return;
        }
        Sach moi;
        if (!nhapSach(&moi)) {
            printf("Da huy, quay lai menu.\n");
            return;
        }
        danhSach[soSach] = moi;
        soSach++;
        printf("Da them sach thanh cong.\n");
    } while (hoiCoKhong("Nhap tiep?"));
}

void capNhatSach() {
    int vitri = hoiTimSach("Nhap ma sach can cap nhat: ");
    if (vitri == -1) return;
    inMotSach(vitri);
    printf("Nhap thong tin moi (ma sach khong doi):\n");
    int dangMuon = danhSach[vitri].soLuongDangMuon;
    danhSach[vitri] = nhapThongTinSach(danhSach[vitri].maSach);
    danhSach[vitri].soLuongDangMuon = dangMuon;
    printf("Da cap nhat sach.\n");
}

void xoaSach() {
    int vitri = hoiTimSach("Nhap ma sach can xoa: ");
    if (vitri == -1) return;
    inMotSach(vitri);
    if (danhSach[vitri].soLuongDangMuon > 0) {
        printf("Khong the xoa: con %d cuon dang duoc muon!\n", danhSach[vitri].soLuongDangMuon);
        return;
    }
    if (!hoiCoKhong("Xac nhan xoa?")) {
        printf("Da huy xoa.\n");
        return;
    }
    memmove(&danhSach[vitri], &danhSach[vitri + 1], (size_t)(soSach - vitri - 1) * sizeof(Sach));
    soSach--;
    printf("Da xoa sach.\n");
}

/* ===================== MUON / TRA SACH ===================== */

void muonSach() {
    int vitri = hoiTimSach("Nhap ma sach can muon: ");
    if (vitri == -1) return;
    inMotSach(vitri);
    if (danhSach[vitri].soLuongTon == 0) {
        printf("Sach da het, khong the muon!\n");
        return;
    }
    int soLuong = docSoNguyen("Nhap so luong muon: ", 1, danhSach[vitri].soLuongTon);
    danhSach[vitri].soLuongTon -= soLuong;
    danhSach[vitri].soLuongDangMuon += soLuong;
    printf("Muon thanh cong %d cuon sach \"%s\".\n", soLuong, danhSach[vitri].tenSach);
    printf("Con ton: %d | Dang muon: %d\n",
           danhSach[vitri].soLuongTon, danhSach[vitri].soLuongDangMuon);
}

void traSach() {
    int vitri = hoiTimSach("Nhap ma sach can tra: ");
    if (vitri == -1) return;
    inMotSach(vitri);
    if (danhSach[vitri].soLuongDangMuon == 0) {
        printf("Sach nay khong co cuon nao dang duoc muon!\n");
        return;
    }
    int soLuong = docSoNguyen("Nhap so luong tra: ", 1, danhSach[vitri].soLuongDangMuon);
    danhSach[vitri].soLuongTon += soLuong;
    danhSach[vitri].soLuongDangMuon -= soLuong;
    printf("Tra thanh cong %d cuon sach \"%s\".\n", soLuong, danhSach[vitri].tenSach);
    printf("Con ton: %d | Dang muon: %d\n",
           danhSach[vitri].soLuongTon, danhSach[vitri].soLuongDangMuon);
}

/* ===================== TIM KIEM ===================== */

void inKetQua(int i, int *dem) {
    if ((*dem)++ == 0) inTieuDe();
    inSach(&danhSach[i]);
}

void ketThucLoc(int dem) {
    if (dem == 0) {
        printf("Khong tim thay sach phu hop.\n");
    } else {
        inDuongKe();
        printf("Tim thay %d sach.\n", dem);
    }
}

void locTheoChuoi(const char cauHoi[], const char choPhep[], size_t offset) {
    char tu[100];
    int dem = 0;
    docChuoi(cauHoi, tu, sizeof(tu), choPhep);
    for (int i = 0; i < soSach; i++) {
        if (chuaChuoi((const char *)&danhSach[i] + offset, tu)) inKetQua(i, &dem);
    }
    ketThucLoc(dem);
}

void timKiem() {
    printf("1. Theo ma sach\n2. Theo ten sach (chua tu khoa)\n3. Theo tac gia\n0. Quay lai\n");
    int chon = docSoNguyen("Chon: ", 0, 3);
    if (chon == 3) {
        locTheoChuoi("Nhap ten tac gia: ", CHO_PHEP_TEN_NGUOI, offsetof(Sach, tacGia));
    } else if (chon == 1) {
        int vt = hoiTimSach("Nhap ma sach: ");
        if (vt != -1) {
            inMotSach(vt);
            ketThucLoc(1);
        }
    } else if (chon == 2) {
        locTheoChuoi("Nhap ten sach (hoac 1 phan): ", CHO_PHEP_CHUNG, offsetof(Sach, tenSach));
    }
}

/* ===================== LOC SACH ===================== */

void locTheoKhoangGia() {
    int dem = 0;
    double minGia = docSoThuc("Nhap khoang gia thap nhat: ", 0, GIA_MAX);
    double maxGia = docSoThuc("Nhap khoang gia cao nhat: ", minGia, GIA_MAX);
    for (int i = 0; i < soSach; i++) {
        if (danhSach[i].giaSach >= minGia && danhSach[i].giaSach <= maxGia) {
            inKetQua(i, &dem);
        }
    }
    ketThucLoc(dem);
}

void locTheoNamXuatBan() {
    int dem = 0;
    int namTu = docSoNguyen("Nhap nam xuat ban tu nam: ", NAM_MIN, layNamHienTai());
    int namDen = docSoNguyen("Nhap den nam: ", namTu, layNamHienTai());
    for (int i = 0; i < soSach; i++) {
        if (danhSach[i].namXuatBan >= namTu && danhSach[i].namXuatBan <= namDen) {
            inKetQua(i, &dem);
        }
    }
    ketThucLoc(dem);
}

void locTheoSoLuong() {
    int dem = 0;
    printf("1. Con hang\n2. Het hang\n3. Duoi nguong\n");
    int chon = docSoNguyen("Chon: ", 1, 3);
    int nguong = chon == 3 ? docSoNguyen("Nhap nguong: ", 1, SO_LUONG_MAX) : 1;
    for (int i = 0; i < soSach; i++) {
        int ton = danhSach[i].soLuongTon;
        if (chon == 1 ? ton > 0 : ton < nguong) {
            inKetQua(i, &dem);
        }
    }
    ketThucLoc(dem);
}

void locKetHop() {
    char theLoai[50];
    int dem = 0;
    docChuoi("Nhap the loai: ", theLoai, sizeof(theLoai), CHO_PHEP_THE_LOAI);
    double minGia = docSoThuc("Nhap gia thap nhat: ", 0, GIA_MAX);
    double maxGia = docSoThuc("Nhap gia cao nhat: ", minGia, GIA_MAX);
    int namTu = docSoNguyen("Nhap nam xuat ban tu nam: ", NAM_MIN, layNamHienTai());
    int namDen = docSoNguyen("Nhap den nam: ", namTu, layNamHienTai());
    for (int i = 0; i < soSach; i++) {
        if (chuaChuoi(danhSach[i].theLoai, theLoai) &&
            danhSach[i].giaSach >= minGia &&
            danhSach[i].giaSach <= maxGia &&
            danhSach[i].namXuatBan >= namTu &&
            danhSach[i].namXuatBan <= namDen) {
            inKetQua(i, &dem);
        }
    }
    ketThucLoc(dem);
}

void locSach() {
    printf("1. The Loai\n");
    printf("2. Tac Gia\n");
    printf("3. Nha Xuat Ban\n");
    printf("4. Khoang Gia\n");
    printf("5. Nam Xuat Ban\n");
    printf("6. So Luong\n");
    printf("7. Ket Hop\n");
    printf("0. Thoat\n");
    int chon = docSoNguyen("Nhap lua chon: ", 0, 7);
    switch (chon) {
        case 1: locTheoChuoi("Nhap the loai: ", CHO_PHEP_THE_LOAI, offsetof(Sach, theLoai)); break;
        case 2: locTheoChuoi("Nhap ten tac gia: ", CHO_PHEP_TEN_NGUOI, offsetof(Sach, tacGia)); break;
        case 3: locTheoChuoi("Nhap nha xuat ban: ", CHO_PHEP_CHUNG, offsetof(Sach, nhaXuatBan)); break;
        case 4: locTheoKhoangGia(); break;
        case 5: locTheoNamXuatBan(); break;
        case 6: locTheoSoLuong(); break;
        case 7: locKetHop(); break;
        default: break;
    }
}

/* ===================== SAP XEP / THONG KE ===================== */

int canDoiCho(const Sach *a, const Sach *b, int tieuChi) {
    if (tieuChi == SAP_TEN_AZ) return strcmp(a->tenSach, b->tenSach) > 0;
    if (tieuChi == SAP_GIA_TANG) return a->giaSach > b->giaSach;
    if (tieuChi == SAP_GIA_GIAM) return a->giaSach < b->giaSach;
    if (tieuChi == SAP_TON_GIAM) return a->soLuongTon < b->soLuongTon;
    return 0;
}

void sapXepSach() {
    if (soSach == 0) {
        printf("Danh sach chua co sach nao.\n");
        return;
    }
    printf("1. Ten sach A-Z\n2. Gia tang dan\n3. Gia giam dan\n4. So luong ton giam dan\n0. Quay lai\n");
    int chon = docSoNguyen("Chon: ", 0, SAP_TON_GIAM);
    if (chon == 0) return;
    for (int i = 1; i < soSach; i++) {
        Sach tam = danhSach[i];
        int j = i - 1;
        while (j >= 0 && canDoiCho(&danhSach[j], &tam, chon)) {
            danhSach[j + 1] = danhSach[j];
            j--;
        }
        danhSach[j + 1] = tam;
    }
    printf("Da sap xep. Ket qua:\n");
    hienThiDanhSach();
}

void thongKeSach() {
    int tongTon = 0;
    int tongMuon = 0;
    int soHetSach = 0;
    double tongGiaTri = 0;
    for (int i = 0; i < soSach; i++) {
        tongTon += danhSach[i].soLuongTon;
        tongMuon += danhSach[i].soLuongDangMuon;
        if (danhSach[i].soLuongTon == 0) soHetSach++;
        tongGiaTri += danhSach[i].giaSach * (danhSach[i].soLuongTon + danhSach[i].soLuongDangMuon);
    }
    char tongGia[40];
    dinhDangGia(tongGiaTri, tongGia);
    printf("So dau sach              : %d\n", soSach);
    printf("Tong so cuon tren ke     : %d\n", tongTon);
    printf("Tong so cuon dang muon   : %d\n", tongMuon);
    printf("So dau sach da het       : %d\n", soHetSach);
    printf("Tong gia tri sach        : %s\n", tongGia);
}

/* ===================== MENU ===================== */

void hienThiMenu() {
    printf("\n========== QUAN LY SACH THU VIEN ==========\n");
    printf(" 1. Them sach\n");
    printf(" 2. Hien thi danh sach\n");
    printf(" 3. Tim kiem sach\n");
    printf(" 4. Cap nhat sach\n");
    printf(" 5. Xoa sach\n");
    printf(" 6. Muon sach\n");
    printf(" 7. Tra sach\n");
    printf(" 8. Loc sach\n");
    printf(" 9. Sap xep sach\n");
    printf("10. Thong ke\n");
    printf(" 0. Thoat\n");
    printf("===========================================\n");
}

int main() {
    int chon = 0;
    do {
        hienThiMenu();
        chon = docSoNguyen("Chon chuc nang: ", 0, 10);
        switch (chon) {
            case 1: themSach(); break;
            case 2: hienThiDanhSach(); break;
            case 3: timKiem(); break;
            case 4: capNhatSach(); break;
            case 5: xoaSach(); break;
            case 6: muonSach(); break;
            case 7: traSach(); break;
            case 8: locSach(); break;
            case 9: sapXepSach(); break;
            case 10: thongKeSach(); break;
            case 0: printf("Tam biet!\n"); break;
        }
    } while (chon != 0);
    return 0;
}
