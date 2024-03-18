package gramerodevi;

import java.util.Scanner;

public class gramer{

    private static final String[] ozneler = {"Ben", "Sen", "Hasan", "Nurşah", "Elif", "Abdulrezzak", "Şehribanu", "Zeynelabidin", "Naki"};
    private static final String[] nesneler = {"Bahçe", "Okul", "Park", "Sınıf", "Yarın", "Pazartesi", "Salı", "Çarşamba", "Perşembe", "Cuma", "Cumartesi", "Pazar", "Merkez", "Ev", "Kitap", "Defter", "Güneş", "Beydağı"};
    private static final String[] yuklemeler = {"Gitmek", "Gelmek", "Okumak", "Yazmak", "Yürümek", "Görmek"};

    public static void main(String[] args) {
        // Kullanıcıdan ifadeyi al
        Scanner scanner = new Scanner(System.in);
        System.out.print("İfadeyi girin: ");
        String ifade = scanner.nextLine();
        scanner.close();

        // İfadeyi kontrol et ve sonucu yazdır
        if (ifadeyiKontrolEt(ifade)) {
            System.out.println("EVET");
        } else {
            System.out.println("HAYIR");
        }
    }

    // İfadeyi kontrol eden fonksiyon
    private static boolean ifadeyiKontrolEt(String ifade) {
        // İfadeyi boşluklardan ayır
        String[] kelimeler = ifade.trim().split("\\s+");

        // Eğer ifadede üç kelime yoksa, gramer uymaz
        if (kelimeler.length != 3) {
            return false;
        }

        // Özne, nesne ve yüklem sırasını kontrol et
        if (!ozneUygun(kelimeler[0]) || !nesneUygun(kelimeler[1]) || !yuklemUygun(kelimeler[2])) {
            return false;
        }

        return true;
    }

    // Öznenin gramerdeki uygunluğunu kontrol eden fonksiyon
    private static boolean ozneUygun(String kelime) {
        for (String ozne : ozneler) {
            if (ozne.equals(kelime)) {
                return true;
            }
        }
        return false;
    }

    // Nesnenin gramerdeki uygunluğunu kontrol eden fonksiyon
    private static boolean nesneUygun(String kelime) {
        for (String nesne : nesneler) {
            if (nesne.equals(kelime)) {
                return true;
            }
        }
        return false;
    }

    // Yüklemin gramerdeki uygunluğunu kontrol eden fonksiyon
    private static boolean yuklemUygun(String kelime) {
        for (String yuklem : yuklemeler) {
            if (yuklem.equals(kelime)) {
                return true;
            }
        }
        return false;
    }
}

