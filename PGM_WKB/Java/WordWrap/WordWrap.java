/*
 * This does not get marked as passed, the test which fais is:
 * Input: "zahl1zahl2" 6
 * Output: zahl1z
 *         ahl2
 * Expected: zahl1
 *           zahl2
 * Despite the fact that the output is correct.
 */

public class WordWrap {

    public static void main(String[] args) {
        String s = args[0];
        int n = Integer.parseInt(args[1]);
        
        String[] words = s.split(" ");
        java.util.List<String> result = prepare(words, n);
        int lineLength = 0;
        String line = "";
        for (int i = 0; i < result.size(); i++) {
            String word = result.get(i);
            if (lineLength + word.length() > n) {
                System.out.println(line);
                line = "";
                lineLength = 0;
            }
            line += word + " ";
            lineLength += word.length() + 1;
            if (i == result.size() - 1) {
                System.out.println(line);
            }
        }
    }

    private static java.util.List<String> prepare(String[] words, int n) {
        java.util.List<String> result = new java.util.ArrayList<String>();
        for (String word: words) {
            if (word.length() > n) {
                result.add(word.substring(0, n));
                result.addAll(split(word.substring(n), n, new java.util.ArrayList<String>()));
            } else {
                result.add(word);
            }
        }
        return result;
    }

    private static java.util.List<String> split(String s, int n, java.util.ArrayList<String> result) {
        if (s.length() <= n) {
            result.add(s);
            return result;
        } else {
            result.add(s.substring(0, n));
            return split(s.substring(n), n, result);
        }
    }

}
