public class Pascal {
    
    public static void main(String[] args) {
        System.out.println("Geben Sie die Größe des Pascalschen Dreiecks ein: ");
        java.util.Scanner scanner = new java.util.Scanner(System.in);
        int size = scanner.nextInt();
        scanner.close();
        int[][] pascal = new int[size][];
        for (int i = 0; i < size; i++) {
            pascal[i] = new int[i + 1];
            pascal[i][0] = 1;
            pascal[i][i] = 1;
            for (int j = 1; j < i; j++) {
                pascal[i][j] = pascal[i - 1][j - 1] + pascal[i - 1][j];
            }
        }
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < pascal[i].length; j++) {
                System.out.print(pascal[i][j] + " ");
            }
            System.out.println();
        }
    }

}
