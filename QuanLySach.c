
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 1000
#define DAI 200

typedef struct {
    char maSach[20];
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

int laRong(const char s[]) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] != ' ') return 0;
    }
    return 1;
}

void docChuoi(const char cauHoi[], char s[], int size) {
    while (1) {
        printf("%s", cauHoi);
        docDong(s, size);
        if (!laRong(s)) return;
        printf("Loi: khong duoc de trong!\n");
    }
}

int docSoNguyen(const char cauHoi[], int min, int max) {
    char buf[DAI];
    char thua;
    int x;
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
    double x;
    while (1) {
        printf("%s", cauHoi);
        docDong(buf, DAI);
        if (sscanf(buf, "%lf %c", &x, &thua) != 1) {
            printf("Loi: phai nhap mot so!\n");
        } else if (!(x >= min && x <= max)) {
            printf("Loi: gia tri phai tu %.2f den %.2f!\n", min, max);
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

/* ===================== HAM HO TRO ===================== */

int layNamHienTai() {
    time_t t = time(NULL);
    struct tm now = *localtime(&t);
    return now.tm_year + 1900;
}


void layTinhTrang(Sach s, char ketQua[]) {
    if (s.soLuongTon > 0) {
        strcpy(ketQua, "Con sach");
    } else {
        strcpy(ketQua, "Het sach");
    }
}


int timViTriTheoMa(const char ma[]) {
    for (int i = 0; i < soSach; i++) {
        if (strcmp(danhSach[i].maSach, ma) == 0) return i;
    }
    return -1;
}

void chuyenThuong(const char nguon[], char dich[]) {
    int i;
    for (i = 0; nguon[i] != '\0'; i++) {
        char c = nguon[i];
        if (c >= 'A' && c <= 'Z') c = (char)(c + 32);
        dich[i] = c;
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
    for (int i = 0; i < 118; i++) putchar('-');
    putchar('\n');
}

void inTieuDe() {
    inDuongKe();
    printf("%-10s %-22s %-16s %-12s %-14s %-5s %12s %4s %4s %-10s\n",
           "Ma sach", "Ten sach", "Tac gia", "The loai", "NXB",
           "Nam", "Gia", "Ton", "Muon", "Tinh trang");
    inDuongKe();
}

void inSach(Sach s) {
    char tinhTrang[20];
    layTinhTrang(s, tinhTrang);
    printf("%-10.10s %-22.22s %-16.16s %-12.12s %-14.14s %5d %12.2f %4d %4d %-10s\n",
           s.maSach, s.tenSach, s.tacGia, s.theLoai, s.nhaXuatBan,
           s.namXuatBan, s.giaSach, s.soLuongTon, s.soLuongDangMuon, tinhTrang);
}

void hienThiDanhSach()) {
    if (soSach == 0) {
        printf("Danh sach chua co sach nao.\n");
        return;
    }
    inTieuDe();
    for (int i = 0; i < soSach; i++) inSach(danhSach[i]);
    inDuongKe();
    printf("Tong cong: %d dau sach.\n", soSach);
}

/* ===================== THEM / SUA / XOA ===================== */

Sach nhapThongTinSach(const char ma[]) {
    Sach s;
    strcpy(s.maSach, ma);
    docChuoi("Ten sach: ", s.tenSach, 100);
    docChuoi("Tac gia: ", s.tacGia, 100);
    docChuoi("The loai: ", s.theLoai, 50);
    docChuoi("Nha xuat ban: ", s.nhaXuatBan, 100);
    s.namXuatBan = docSoNguyen("Nam xuat ban: ", 1000, layNamHienTai());
    s.giaSach = docSoThuc("Gia sach: ", 0, 99999999);
    s.soLuongTon = docSoNguyen("So luong ton: ", 0, 9999);
    s.soLuongDangMuon = 0;
    return s;
}

Sach nhapSach() {
    char ma[20];
    while (1) {
		printf("===========================================\n");
        docChuoi("Ma sach: ", ma, 20);
        if (timViTriTheoMa(ma) == -1) break;
        printf("Loi: ma sach \"%s\" da ton tai!\n", ma);
    }
    return nhapThongTinSach(ma);
}

void themSach() {
	
    do {
        if (soSach >= MAX) {
            printf("Loi: danh sach da day (%d sach), khong the them!\n", MAX);
            return;
        }
        danhSach[soSach] = nhapSach();
        soSach++;
        printf("Da them sach thanh cong.\n");
    } while (hoiCoKhong("Nhap tiep?"));
}

void capNhatSach() {
    char ma[20];
    docChuoi("Nhap ma sach can cap nhat: ", ma, 20);
    int vt = timViTriTheoMa(ma);
    if (vt == -1) {
        printf("Khong tim thay sach co ma \"%s\".\n", ma);
        return;
    }
    inTieuDe();
    inSach(danhSach[vt]);
    printf("Nhap thong tin moi (ma sach khong doi):\n");
    int dangMuon = danhSach[vt].soLuongDangMuon;
    danhSach[vt] = nhapThongTinSach(ma);
    danhSach[vt].soLuongDangMuon = dangMuon;
    printf("Da cap nhat sach.\n");
}

void xoaSach() {
    char ma[20];
    docChuoi("Nhap ma sach can xoa: ", ma, 20);
    int vt = timViTriTheoMa(ma);
    if (vt == -1) {
        printf("Khong tim thay sach co ma \"%s\".\n", ma);
        return;
    }
    inTieuDe();
    inSach(danhSach[vt]);
    if (danhSach[vt].soLuongDangMuon > 0) {
        printf("Khong the xoa: con %d cuon dang duoc muon!\n", danhSach[vt].soLuongDangMuon);
        return;
    }
    if (!hoiCoKhong("Xac nhan xoa?")) {
        printf("Da huy xoa.\n");
        return;
    }
    for (int i = vt; i < soSach - 1; i++) {
        danhSach[i] = danhSach[i + 1];
    }
    soSach--;
    printf("Da xoa sach.\n");
}

/* ===================== TIM KIEM / LOC ===================== */

void ketThucLoc(int dem) {
    if (dem == 0) {
        printf("Khong tim thay sach phu hop.\n");
    } else {
        inDuongKe();
        printf("Tim thay %d sach.\n", dem);
    }
}

void timKiem() {
    printf("1. Theo ma sach\n2. Theo ten sach (chua tu khoa)\n0. Quay lai\n");
    int chon = docSoNguyen("Chon: ", 0, 2);
    if (chon == 1) {
        char ma[20];
        docChuoi("Nhap ma sach: ", ma, 20);
        int vt = timViTriTheoMa(ma);
        if (vt == -1) {
            printf("Khong tim thay sach co ma \"%s\".\n", ma);
        } else {
            inTieuDe();
            inSach(danhSach[vt]);
            ketThucLoc(1);
        }
    } else if (chon == 2) {
        char tu[100];
        int dem = 0;
        docChuoi("Nhap ten sach (hoac 1 phan): ", tu, 100);
        for (int i = 0; i < soSach; i++) {
            if (chuaChuoi(danhSach[i].tenSach, tu)) {
                if (dem == 0) inTieuDe();
                inSach(danhSach[i]);
                dem++;
            }
        }
        ketThucLoc(dem);
    }
}

/* ===================== SAP XEP / THONG KE ===================== */

void thongKeSach() {
    int tongTon = 0, tongMuon = 0, soHetSach = 0;
    double tongGiaTri = 0;
    for (int i = 0; i < soSach; i++) {
        tongTon += danhSach[i].soLuongTon;
        tongMuon += danhSach[i].soLuongDangMuon;
        if (danhSach[i].soLuongTon == 0) soHetSach++;
        tongGiaTri += danhSach[i].giaSach * (danhSach[i].soLuongTon + danhSach[i].soLuongDangMuon);
    }
    printf("So dau sach              : %d\n", soSach);
    printf("Tong so cuon tren ke     : %d\n", tongTon);
    printf("Tong so cuon dang muon   : %d\n", tongMuon);
    printf("So dau sach da het       : %d\n", soHetSach);
    printf("Tong gia tri sach        : %.2f\n", tongGiaTri);
}

/* ===================== MENU ===================== */

void hienThiMenu() {
    printf("\n========== QUAN LY SACH THU VIEN ==========\n");
    printf(" 1. Them sach\n");
    printf(" 2. Hien thi danh sach\n");
    printf(" 3. Tim kiem sach\n");
    printf(" 4. Cap nhat sach\n");
    printf(" 5. Xoa sach\n");
    printf(" 6. Thong ke\n");
    printf(" 0. Thoat\n");
    printf("===========================================\n");
}

int main() {
    int chon;
    do {
        hienThiMenu();
        chon = docSoNguyen("Chon chuc nang: ", 0, 6);
        switch (chon) {
            case 1: themSach(); break;
            case 2: hienThiDanhSach(); break;
            case 3: timKiem(); break;
            case 4: capNhatSach(); break;
            case 5: xoaSach(); break;
            case 6: thongKeSach(); break;
            case 0: printf("Tam biet!\n"); break;
        }
    } while (chon != 0);
    return 0;
}
