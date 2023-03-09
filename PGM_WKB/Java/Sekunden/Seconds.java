public class Seconds {
    public static void main(String[] args) {
        java.util.Scanner scanner = new java.util.Scanner(System.in);

        // Eingabeaufforderung
        System.out.print("Sekunden: ");
        int seconds = scanner.nextInt();

        // Minuten und Sekunden berechnen
        int minutes = seconds / 60;
        int remainingSeconds = seconds % 60;

        // Ergebnis ausgeben
        System.out.println(minutes + " Minuten und " + remainingSeconds + " Sekunden");

        scanner.close();
    }
}
