public class Schleifen {
    
    public static void main(String[] args) {
        System.out.println("Geben Sie die Zahl ein: ");
        java.util.Scanner scanner = new java.util.Scanner(System.in);
        int zahl = scanner.nextInt();
        scanner.close();
        for (int i = 0; i < zahl; i++) {
            System.out.println("Wiederholung");
        }
    }

}
