public class UrlSplitting {
    public static void main(String[] args) {
        java.util.Scanner scanner = new java.util.Scanner(System.in);

        // Eingabeaufforderung
        System.out.print("Url: ");
        String urlString = scanner.nextLine();

        try {
            // URL-Objekt erstellen
            java.net.URL url = new java.net.URL(urlString);

            // Protokoll, Domäne und Pfad auslesen
            String protocol = url.getProtocol();
            String domain = url.getHost();
            String path = url.getPath();

            // Ergebnis ausgeben
            System.out.println("Protokoll: " + protocol);
            System.out.println("Domäne: " + domain);
            System.out.println("Pfad: " + path);

        } catch (java.net.MalformedURLException e) {
            System.out.println("Ungültige URL eingegeben!");
        }

        scanner.close();
    }
}
