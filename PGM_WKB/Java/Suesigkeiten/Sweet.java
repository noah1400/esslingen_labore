public class Sweet {

    public static void main(String[] args) {
        System.out.println("Wie viele Gummibärchen?");
        java.util.Scanner scanner = new java.util.Scanner(System.in);
        int gummibaerchen = scanner.nextInt();
        System.out.println("Wie viele Karamellbonbon?");
        int karamellbonbon = scanner.nextInt();
        System.out.println("Wie viele Lakritzschnecke?");
        int lakritzschnecke = scanner.nextInt();
        System.out.println("Wie viele Schaum-Fruchtgummi-Frösche?");
        int schaumFruchtgummiFroesche = scanner.nextInt();
        scanner.close();
        double betrag = (gummibaerchen * 9.4 + karamellbonbon * 13.9 + lakritzschnecke * 16 + schaumFruchtgummiFroesche * 11.2) / 1000 * 26.16;
        System.out.printf("Betrag: %.2f", betrag);
    }

}
