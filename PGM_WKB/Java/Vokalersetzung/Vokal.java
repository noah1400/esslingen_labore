public class Vokal {

    public static void main(String[] args) {
        System.out.println("Text: ");
        java.util.Scanner scanner = new java.util.Scanner(System.in);
        String text = scanner.nextLine();
        System.out.println("Vokal: ");
        String vokal = scanner.nextLine();
        scanner.close();
        String text2 = text.replaceAll("[aeiouAEIOU]", vokal);
        System.out.println(text2);
    }
    
}
