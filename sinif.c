#include <stdio.h>
#include <string.h>

// String Kopyalama Fonksiyonu
void stringKopyala(char *hedef, const char *kaynak)
{
    while (*kaynak)
    {
        *hedef = *kaynak;
        hedef++;
        kaynak++;
    }
    *hedef = '\0';
}

// Kendi string uzunluğu bulma fonksiyonumuz
int benim_strlen(const char *str)
{
    int uzunluk = 0;
    while (str[uzunluk] != '\0')
    {
        uzunluk++;
    }
    return uzunluk;
}

// Kendi string karşılaştırma fonksiyonumuz
int benim_strncmp(const char *str1, const char *str2, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (str1[i] != str2[i])
        {
            return str1[i] - str2[i];
        }
        if (str1[i] == '\0')
        {
            return 0;
        }
    }
    return 0;
}

// Kendi karakter arama fonksiyonumuz
char *benim_strchr(char *str, char c)
{
    while (*str)
    {
        if (*str == c)
        {
            return str;
        }
        str++;
    }
    return NULL;
}

// Kendi alt dizge arama fonksiyonumuz
char *benim_strstr(char *buyukDize, const char *kucukDize)
{
    int kucukDize_uzunluk = benim_strlen(kucukDize);
    int buyukDize_uzunluk = benim_strlen(buyukDize);

    for (int i = 0; i <= buyukDize_uzunluk - kucukDize_uzunluk; i++)
    {
        int j;
        for (j = 0; j < kucukDize_uzunluk; j++)
        {
            if (buyukDize[i + j] != kucukDize[j])
            {
                break;
            }
        }
        if (j == kucukDize_uzunluk)
        {
            return &buyukDize[i];
        }
    }
    return NULL;
}

// Yardımcı fonksiyon: satırdaki boşlukları kaldır
void bosluklariTemizle(char *str)
{
    char *son;

    // Başındaki boşlukları kaldır
    while (*str == ' ')
        str++;

    // Sonundaki boşlukları kaldır
    son = str + benim_strlen(str) - 1;
    while (son > str && *son == ' ')
        son--;

    *(son + 1) = '\0';
}

// Değişken adını al
// Değişken adını al
void degiskenAdiniAl(char *satir, char *degiskenAdi)
{
    char *basla = satir;

    // Eğer "private" kelimesi varsa, onu atla
    if (benim_strstr(satir, "private") != NULL)
    {
        basla = benim_strstr(satir, "private") + benim_strlen("private");
    }

    // Değişken adını al
    while (*basla != ' ')
    {
        basla++;
    }
    basla++; // İlk boşluğu atla

    // Değişken adını kopyala
    while (*basla != ';')
    {
        if (*basla != ' ' && *basla != '\n' && *basla != '\r')
        {
            *degiskenAdi = *basla;
            degiskenAdi++;
        }
        else if (*basla == ' ')
        {
            *degiskenAdi = ' ';
            degiskenAdi++;
        }
        basla++;
    }
    *degiskenAdi = '\0'; // Dizi sonunu işaretle
}

// Sınıf tanımını struct tanımına dönüştürme fonksiyonu
void sinifiYapiyaDonustur(FILE *dosya)
{
    char satir[256];
    char yapiAdi[50];
    char anaYapiAdi[50];
    int sinifIci = 0;

    while (fgets(satir, sizeof(satir), dosya))
    {
        bosluklariTemizle(satir);

        // Sınıf tanımının başlangıcı
        if (benim_strncmp(satir, "class ", 6) == 0)
        {
            sinifIci = 1;
            if (benim_strstr(satir, "extends") != NULL)
            {
                sscanf(satir, "class %s extends %s {", yapiAdi, anaYapiAdi);
                char *acParantez = benim_strchr(yapiAdi, '{');
                if (acParantez)
                {
                    *acParantez = '\0';
                }
                char *acParantez2 = benim_strchr(anaYapiAdi, '{');
                if (acParantez2)
                {
                    *acParantez2 = '\0';
                }
                printf("struct %s : %s {\n", yapiAdi, anaYapiAdi);
            }
            else
            {
                sscanf(satir, "class %s {", yapiAdi);
                char *acParantez = benim_strchr(yapiAdi, '{');
                if (acParantez)
                {
                    *acParantez = '\0';
                }
                printf("struct %s {\n", yapiAdi);
            }
        }
        // Sınıf tanımının bitişi
        else if (benim_strncmp(satir, "}", 1) == 0 && sinifIci)
        {
            sinifIci = 0;
            printf("};\n\n");
        }
        // Sınıf özellikleri
        else if (sinifIci)
        {
            if (benim_strstr(satir, "private") != NULL)
            {
                char degiskenAdi[50];
                degiskenAdiniAl(satir, degiskenAdi);
                printf("    %s;\n", degiskenAdi);
            }
            else
            {
                printf("    %s;\n", satir);
            }
        }
    }
}

int main()
{
    char dosyaAdi[100];
    printf("Sınıf tanım dosyasının ismini girin: ");
    scanf("%s", dosyaAdi);

    FILE *dosya = fopen(dosyaAdi, "r");
    if (dosya == NULL)
    {
        perror("Dosya açılamadı");
        return 1;
    }

    // Sınıf tanımlarını struct tanımlarına dönüştür
    sinifiYapiyaDonustur(dosya);

    fclose(dosya);

    // Bu örnekte, struct tanımları dosyadan okunarak çıktıya yazdırılır,
    // ancak tanımlanan struct'ları doğrudan kodda kullanamayız.
    // Bunun yerine sabit struct tanımları kullanarak örnekler oluşturuy
    // Sabit struct tanımları
    struct Araba
    {
        char marka[50];
        char model[50];
        int yil;
    };

    struct ElektrikliAraba
    {
        struct Araba; // Kalıtımın bir şekilde simüle edilmesi
        int batarya;
    };

    // Struct örneklerini oluştur ve kullan
    struct Araba arabam;
    stringKopyala(arabam.marka, "Toyota");
    stringKopyala(arabam.model, "Corolla");
    arabam.yil = 2020;

    printf("Araba: %s %s, Yıl: %d\n", arabam.marka, arabam.model, arabam.yil);

    struct ElektrikliAraba elektrikliArabam;
    stringKopyala(elektrikliArabam.marka, "Tesla");
    stringKopyala(elektrikliArabam.model, "Model S");
    elektrikliArabam.yil = 2022;
    elektrikliArabam.batarya = 100;

    printf("Elektrikli Araba: %s %s, Yıl: %d, Batarya: %d kWh\n",
           elektrikliArabam.marka, elektrikliArabam.model, elektrikliArabam.yil, elektrikliArabam.batarya);

    return 0;
}
