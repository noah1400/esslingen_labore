import java.util.Scanner;

public class Heron {
    public static void main(String[] args) {
        Scanner eingabe = new Scanner(System.in);
//		System.out.print("Bitte geben Sie eine Zahl ein: ");
        double number = eingabe.nextDouble();
//		System.out.print("Anzahl Iterationen: ");
        double iteration = eingabe.nextDouble();
        double zwischenzahl = number;

        for (int i = 1; i < iteration + 1; i++) {
            double summe = (zwischenzahl + number/zwischenzahl)/2;
            summe = (double)Math.round(summe*100000)/100000;


            String text = Double.toString(summe);


            text = text.replace(".", ",");

            int counter=0;

            while(text.charAt(counter)!=',') {
                counter++;
            }

            for(int j = 0; j < 3 + counter; j++) {
                text = text + "0";
            }

            System.out.print(i + ". ");

            for (int o = 0; o < 6 + counter ; o++) { //Immer 5 Nachkommastellen
                System.out.print(text.charAt(o));
            }

            System.out.println();

            zwischenzahl = summe;
        }
        eingabe.close();
    }
}
