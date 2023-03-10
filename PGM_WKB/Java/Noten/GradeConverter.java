public class GradeConverter {
    public static void main(String[] args) {
        java.util.Map<String, Integer> gradeToPointsMap = new java.util.HashMap<>(){{
            put("1+", 15);
            put("1", 14);
            put("1-", 13);
            put("2+", 12);
            put("2", 11);
            put("2-", 10);
            put("3+", 9);
            put("3", 8);
            put("3-", 7);
            put("4+", 6);
            put("4", 5);
            put("4-", 4);
            put("5+", 3);
            put("5", 2);
            put("5-", 1);
            put("6", 0);
        }};
        java.util.Map<Integer, String> pointsToGradeMap = new java.util.HashMap<>(){{
            put(15, "1+");
            put(14, "1");
            put(13, "1-");
            put(12, "2+");
            put(11, "2");
            put(10, "2-");
            put(9, "3+");
            put(8, "3");
            put(7, "3-");
            put(6, "4+");
            put(5, "4");
            put(4, "4-");
            put(3, "5+");
            put(2, "5");
            put(1, "5-");
            put(0, "6");
        }};

        java.util.Scanner scanner = new java.util.Scanner(System.in);
        System.out.print("Umrechnungsmodus: ");
        String mode = scanner.nextLine();
        switch(mode){
            case "N":
                System.out.print("Wert: ");
                String grade = scanner.nextLine();
                System.out.println(gradeToPointsMap.get(grade));
                break;
            case "P":
                System.out.print("Wert: ");
                int points = scanner.nextInt();
                System.out.println(pointsToGradeMap.get(points));
                break;
            default:
                System.out.println("Falsche Eingabe");
        }

    }
}