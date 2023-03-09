public class ZahlenAddieren {
    
    public static void main(String[] args) {
        System.out.println("Geben Sie die erste Zahl ein: ");
        java.util.Scanner scanner = new java.util.Scanner(System.in);
        int zahl1 = scanner.nextInt();
        System.out.println("Geben Sie die zweite Zahl ein: ");
        int zahl2 = scanner.nextInt();
        scanner.close();
        System.out.println(zahl1 + zahl2);
    }

}
