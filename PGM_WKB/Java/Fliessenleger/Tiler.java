import java.util.Scanner;

public class Tiler {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Fliesenmaße abfragen
        int tileWidth = scanner.nextInt();
        int tileLength = scanner.nextInt();

        // Bodenmaße abfragen
        int floorWidth = scanner.nextInt() * 10;  // in mm umrechnen
        int floorLength = scanner.nextInt() * 10;  // in mm umrechnen

        // Fugenabstand abfragen
        int gap = scanner.nextInt();

        // Fliesenanzahl berechnen
        int numTiles = (int) Math.ceil((double) floorWidth / (tileWidth + gap)) * (int) Math.ceil((double) floorLength / (tileLength + gap));


        // Ergebnis ausgeben
        System.out.println("Fliesen benötigt: " + numTiles);

        scanner.close();
    }
}
