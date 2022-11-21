import java.util.Scanner;

public class RömischeZahlen {

    public static void main(String[] args) {

        Scanner scan = new Scanner(System.in);
        System.out.print("Zahl: ");
        int eingabe = scan.nextInt();
        dezimalZuRömisch(eingabe);

        scan.close();
    }

    public static void dezimalZuRömisch(int zahl) {

        int[] dezimal = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
        String[] römisch = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };

        StringBuilder röm = new StringBuilder();

        for (int i = 0; i < dezimal.length; i++) {
            while (zahl >= dezimal[i]) {
                zahl -= dezimal[i];
                röm.append(römisch[i]);
            }
        }
        System.out.println(röm.toString());
    }
    
}