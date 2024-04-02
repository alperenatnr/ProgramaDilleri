package bagli_sirala;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

//Mehmet Alperen Ataner 02210224023
//Programı çalıştırmak için, txt dosyasının bulunduğu dizini kopyalayip yapıştırırsanız
//doğru sonuç alacaksınız.:)
//Programa Dilleri dersi 2.ödevi.

class BagliListeElemani {
    int veri;
    int adres;
    BagliListeElemani sonraki;

    public BagliListeElemani(int veri, int adres) {
        this.veri = veri;
        this.adres = adres;
        this.sonraki = null;
    }
}

class BagliListe {
    BagliListeElemani baslangic;

    public BagliListe() {
        this.baslangic = null;
    }

    public void elemanEkle(int veri, int adres) {
        BagliListeElemani yeniEleman = new BagliListeElemani(veri, adres);

        if (baslangic == null) {
            baslangic = yeniEleman;
        } else {
            BagliListeElemani temp = baslangic;
            while (temp.sonraki != null) {
                temp = temp.sonraki;
            }
            temp.sonraki = yeniEleman;
        }
    }

    public void sirala() {
        BagliListeElemani current = baslangic;
        BagliListeElemani index = null;
        int temp;

        if (baslangic == null) {
            return;
        } else {
            while (current != null) {
                index = current.sonraki;

                while (index != null) {
                    if (current.adres > index.adres) {
                        temp = current.veri;
                        current.veri = index.veri;
                        index.veri = temp;

                        temp = current.adres;
                        current.adres = index.adres;
                        index.adres = temp;
                    }
                    index = index.sonraki;
                }
                current = current.sonraki;
            }
        }
    }

    public void yazdir() {
        BagliListeElemani temp = baslangic;
        while (temp != null) {
            System.out.println(temp.veri + " " + temp.adres);
            temp = temp.sonraki;
        }
    }
}

public class Bagli_Sirala {

    
    public static void main(String[] args) {
        BagliListe liste = new BagliListe();
        Scanner scanner = new Scanner(System.in);

        System.out.print("Dosya adını girin: ");
        String dosyaAdi = scanner.nextLine();

        try {
            File dosya = new File(dosyaAdi);
            Scanner dosyaOkuyucu = new Scanner(dosya);

            while (dosyaOkuyucu.hasNextLine()) {
                int sayi = Integer.parseInt(dosyaOkuyucu.nextLine());
                // Adres taklidi olarak, sayının tersini alıyoruz.
                int adres = Integer.parseInt(new StringBuilder(String.valueOf(sayi)).reverse().toString());
                liste.elemanEkle(sayi, adres);
            }
            dosyaOkuyucu.close();
        } catch (FileNotFoundException e) {
            System.out.println("Dosya bulunamadı.");
            e.printStackTrace();
        }

        liste.sirala();
        liste.yazdir();
    }
    
}
