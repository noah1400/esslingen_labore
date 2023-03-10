public class SmallAndBig {
    public static void main(String[] args) {
        java.util.Scanner scanner = new java.util.Scanner(System.in);
        System.out.print("Wieviele Zahlen möchtest du eingeben: ");
        int count = scanner.nextInt();

        int[] numbers = new int[count];
        for (int i = 0; i < count; i++) {
            System.out.printf("Zahl %d: ", i + 1);
            numbers[i] = scanner.nextInt();
        }

        int smallest = numbers[0];
        int biggest = numbers[0];
        for (int i = 1; i < count; i++) {
            if (numbers[i] < smallest) {
                smallest = numbers[i];
            }
            if (numbers[i] > biggest) {
                biggest = numbers[i];
            }
        }

        System.out.printf("Die größte Zahl ist: %d%n", biggest);
        System.out.printf("Die kleinste Zahl ist: %d%n", smallest);
    }
}