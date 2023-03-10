public class RussianMultiplication {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Bitte geben Sie genau zwei Zahlen als Parameter an.");
            return;
        }
        int a = Integer.parseInt(args[0]);
        int b = Integer.parseInt(args[1]);
        int[] halbierte = new int[32];
        int[] verdoppelt = new int[32];
        int index = 0;
        while (a >= 1) {
            halbierte[index] = a;
            verdoppelt[index] = b;
            a /= 2;
            b *= 2;
            index++;
        }
        System.out.println(args[0] + " * " + args[1]);
        int mc = (args[0] + " * " + args[1]).length();
        for (int i = 0; i < mc; i++) {
            System.out.print("-");
        }
        System.out.println();
        int summe = 0;
        int minSpace =  (mc-(""+halbierte[0]).length());
        for (int i = 0; i < index; i++) {
            
            System.out.printf("%d%"+minSpace+"d", halbierte[i], verdoppelt[i]);

            if (halbierte[i] % 2 == 0) {
                System.out.print(" X");
            } else {
                summe += verdoppelt[i];
            }
            System.out.println();
        }
        for (int i = 0; i < mc; i++) {
            System.out.print("=");
        }
        System.out.println();
        System.out.printf("%"+mc+"d", summe);
    }
}
