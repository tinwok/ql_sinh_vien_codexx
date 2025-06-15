#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
struct date
{
   int ngay;
   int thang;
   int nam;
};
typedef struct date d;
struct SinhVien
{
    int id;
    char ten[50];
    char gioitinh[5];
    d ngaySinh; 
    int tuoi;
    float diemMon1;
    float diemMon2;
    float diemMon3;
    float diemTrungBinh;
    char hocLuc[50];
    char malop[50];

};
typedef struct SinhVien SV;

int hienMenu(){
    printf("\n== MENU ==\n");
    printf("1. Nhap danh sach sinh vien\n");
    printf("2. Xuat danh sach sinh vien\n");
    printf("3. Xuat danh sach sinh vien theo lop\n");
    printf("4. Sap xep danh sach sinh vien loai gioi\n");
    printf("5. Sap xep danh sach sinh vien theo DTB\n");
    printf("6. Sap xep danh sach sinh vien theo ten\n");
    printf("7. Xoa sinh vien theo ID\n");
    printf("8. Xuat File \n");
    printf("9. Doc file \n");
    printf("0. Thoat\n");
    printf(" ==  Nhap lua chon: ");
    int luaChon; 
    scanf("%d", &luaChon);
    return luaChon;
}
void xoaXuongDong(char *s){
   s[strcspn(s, "\n")] = '\0';
}

void nhapSinhVien(SV *x){
    printf("\n ID: " ); scanf("%d", &x->id);
    getchar(); 
    printf("Nhap ten: ");
    fgets(x->ten,sizeof(x->ten),stdin);
    xoaXuongDong(x->ten);
    printf("\nGioi Tinh: ");
    scanf("%s", x->gioitinh);
    getchar();
    printf("\nNhap ngay thang nam sinh: ");
    scanf("%d%d%d", &x->ngaySinh.ngay, &x->ngaySinh.thang, &x->ngaySinh.nam);
    getchar();
    printf("\nNhap diem mon 1: ");
    scanf("%f", &x->diemMon1);
    getchar();
    printf("\nNhap diem mon 2: ");
    scanf("%f", &x->diemMon2);
    getchar();
    printf("\nNhap diem mon 3: ");
    scanf("%f", &x->diemMon3);
    getchar();
    printf("\n Ma lop ");
    scanf("%s", x->malop);
    getchar();
} 

void inSinhVien(SV x){
    //    printf("\n--- Thong tin sinh vien ---\n");
    printf("ID: %d\n", x.id);
    printf("Ten: %s\n", x.ten);
    printf("Gioi tinh: %s\n", x.gioitinh);
    printf("Ngay sinh: %02d/%02d/%04d\n", x.ngaySinh.ngay, x.ngaySinh.thang, x.ngaySinh.nam);
    printf("Tuoi: %d\n", x.tuoi);
    printf("Diem Mon 1: %.2f\n", x.diemMon1);
    printf("Diem Mon 2: %.2f\n", x.diemMon2);
    printf("Diem Mon 3: %.2f\n", x.diemMon3);
    printf("Diem Trung Binh: %.2f\n", x.diemTrungBinh);
    printf("Hoc luc: %s\n", x.hocLuc);
    printf("Ma lop: %s\n", x.malop);
}
void tinhTuoi(SV *x){
    time_t TTIME = time(0);
    struct tm* NOW = localtime(&TTIME);
    int namHienTai = NOW->tm_year+1900;
    x->tuoi = namHienTai - x->ngaySinh.nam;
}
void tinhDiemTrungBinh(SV *x){
    x->diemTrungBinh = (x->diemMon1 + x->diemMon2 + x->diemMon3)/3;
}


void xepLoai(SV *x){
    if(x->diemTrungBinh >= 8.0)
        strcpy(x->hocLuc, "Gioi");
    else if(x->diemTrungBinh >= 6.5)
        strcpy(x->hocLuc, "Kha");
    else if(x->diemTrungBinh >= 5.0)
        strcpy(x->hocLuc, "Trung binh");
    else
        strcpy(x->hocLuc, "Yeu");
}

void capNhatSinhVien(SV *x){
     nhapSinhVien(x);
     tinhTuoi(x);
     tinhDiemTrungBinh(x);
     xepLoai(x);
}
void nhapDanhSachSinhVien(SV a[], int n ){
  for (int i = 0; i < n; i++)
  {
    printf("Nhap sinh vien thu %d", i + 1 );
    capNhatSinhVien(&a[i]);
  }
  
}
void inDanhSachSinhVien(SV a[], int n ){
  for (int i = 0; i < n; i++)
  {
    printf("-- Thong tin sinh vien thu: %d \n --", i + 1 );
    inSinhVien(a[i]);
  }
}

float timmax_DiemTrungBinh(SV a[], int n){
    float max = a[0].diemTrungBinh;
    for (int i = 0; i < n; i++)
    {
        if(max < a[i].diemTrungBinh){
            max = a[i].diemTrungBinh;
        }
    }
     return max;
}
 
int tim_Mintuoi(SV a[], int n){
    int min = a[0].tuoi;
    for (int i = 0; i < n; i++)
    {
        if(min > a[i].tuoi){
            min = a[i].tuoi;
        }
    }
    return min;
}

void xuat_SV_Gioi(SV a[], int n){
    printf("\n == Danh Sach Hoc Sinh Gioi == \n");
    for (int i = 0; i < n; i++)
    {
       if(strcmp(a[i].hocLuc, "Gioi") == 0){
        inSinhVien(a[i]);
       }
    } 
}
void xuat_SV_TheoLop(SV a[], int n, char lop[]){
    printf("\n == Sap xep sinh vien theo lop {%s}== \n", lop);
    for (int i = 0; i < n; i++)
    {
       if(strcmp(a[i].malop, lop) == 0){
        inSinhVien(a[i]);
        printf("\n");
       }
    } 
}

void tim_SV_theoTen(SV a[], int n, char ten[]){
    printf("\n == Sap xep sinh vien theo ten %s== \n", ten);
    for (int i = 0; i < n; i++)
    {
       if(strcmp(a[i].ten, ten) == 0){
        inSinhVien(a[i]);
        printf("\n");
       }
    } 
}

void xoa_SinhVien_ID(SV a[], int *n, int id){
    for (int i = 0; i < *n; i++)
    {
        if(a[i].id == id){
            for (int  j = i; j < *n - 1; j++)
            {
                a[j] = a[j + 1];    
            }
            (*n)--;
            i--;
        }
    }
    inDanhSachSinhVien(a, *n);
}

int sapXep_DS_DTB(const void *a, const void *b){
    SV *x = (SV*)a;
    SV *y = (SV*)b;
    return x->diemTrungBinh - y->diemTrungBinh;
}

int sapXep_DS_Ten(const void *a, const void *b){
    SV *x = (SV*)a;
    SV *y = (SV*)b;
    return strcmp(x->ten , y->ten);
}

void xuatFile(SV x[], int n){
    char tenFile[50];
    printf("Nhap ten file can luu: ");
    scanf("%s", tenFile);
    FILE *f = fopen(tenFile, "wb");
    if(f == NULL){
        printf("\n Loi roi ongn oi !!");
        return;
    }
    for (int i = 0; i < n; i++)
    {
        fwrite(&x[i], sizeof(SV), 1, f );
    }
    fclose(f);
}

void docFile( SV x[], int *n){
    char tenFile[50];
    printf("Nhap ten file can doc: ");
    scanf("%s", tenFile);
    FILE *f = fopen(tenFile, "rb");
    if(f == NULL){
        printf("File bi loi!!");
        return;
    }

    *n = 0;
    while (fread(&x[*n], sizeof(SV), 1, f))
    {
        (*n)++;
    }
    fclose(f);
}

int main(){
    SV x[100]; 
    int n;
    // float maxDTB = timmax_DiemTrungBinh(x, n);
    // printf("\n== Diem trung binh cao nhat la: %.2f == ", maxDTB);

    // int minTuoi = tim_Mintuoi(x, n);
    // printf("\n== Tuoi nho nhat la: %d ==", minTuoi);

    // xuat_SV_Gioi(x, n);

    // char s[20]; 
    // printf("\nNhap ma lop tim sinh vien: ");
    // scanf("%s", s);
    // xuat_SV_TheoLop(x, n, s);

    // char c[50];
    // printf("\nNhap ten can tim: ");
    // scanf("%s", c);
    // tim_SV_theoTen(x, n, c);
   

    // int d;
    // printf("\nNhap ID can xoa: "); 
    // scanf("%d", &d);
    // xoa_SinhVien_ID(x , &n, d);

    // printf("\nSap xep sinh vien theo DTB\n");
    // qsort(x, n, sizeof(SV), sapXep_DS_DTB);
    // inDanhSachSinhVien(x, n);

    // printf("\nSap xep sinh vien theo Ten\n");
    // qsort(x, n, sizeof(SV), sapXep_DS_Ten);
    //  inDanhSachSinhVien(x, n);
    int luachon;
    char s[20];
    int id;
    do
    {
        luachon = hienMenu();
        switch (luachon)
        {
        case 1:
            printf(" Nhap so luong sinh vien: ");
            scanf("%d", &n);
            nhapDanhSachSinhVien(x, n);
            break;
        case 2: 
            printf("\n == Danh sach sinh vien sau khi in ==\n");
            inDanhSachSinhVien(x, n);
             break;
        case 3: 
            printf("Nhap lop can tim sinh vien: ");
            scanf("%s", s);
            xuat_SV_TheoLop(x, n, s);
            break;
        case 4:
            xuat_SV_Gioi(x, n);
            break;
        case 5:
            printf("\nSap xep danh sach Sinh Vien theo DTB == \n");
            qsort(x, n, sizeof(SV), sapXep_DS_DTB);
            inDanhSachSinhVien(x, n);
            break;
        case 6:
            printf("\nSap xep danh sach Sinh Vien theo ten == \n");
            qsort(x, n, sizeof(SV), sapXep_DS_Ten);
            inDanhSachSinhVien(x, n);
            break;
        case 7:
            printf("Nhap id can xoa: ");
            scanf("%d", &id);
            printf("\nDanh sach sinh vien sau khi xoa ID: %d==  \n", id);
            xoa_SinhVien_ID(x, &n, id);
            break;
        case 8:
            xuatFile(x, n);
            break;
        case 9:
            docFile(x,&n);
            inDanhSachSinhVien(x, n);
            break;
        }
    
        
    } while (luachon > 0);

     return 0; 
}