public class HalloWelt {

    public static void main(String[] args) {
        System.out.println("Geben Sie den Namen ein: ");
        java.util.Scanner scanner = new java.util.Scanner(System.in);
        String name = scanner.nextLine();
        scanner.close();
        System.out.println("Hallo, " + name + "!");
    }

}
