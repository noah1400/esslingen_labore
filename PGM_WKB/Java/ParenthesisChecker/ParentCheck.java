public class ParentCheck {

    public static void main(String[] args) {
        try (java.util.Scanner scanner = new java.util.Scanner(System.in)) {
            System.out.print("Zeile: ");
            String line = scanner.nextLine();
            boolean result = areBracketsBalanced(line);
            System.out.println(result);
        }
    }

    public static boolean areBracketsBalanced(String line) {
        Stack<Character> stack = new Stack<Character>();
        for (int i = 0; i < line.length(); i++) {
            char c = line.charAt(i);
            if (c == '(' || c == '{' || c == '[') {
                stack.push(c);
            } else if (c == ')' || c == '}' || c == ']') {
                if (stack.isEmpty()) {
                    return false;
                }
                char top = stack.pop();
                if ((c == ')' && top != '(') || (c == '}' && top != '{') || (c == ']' && top != '[')) {
                    return false;
                }
            }
        }
        return stack.isEmpty();
    }

    private static class Stack<T> {
        private int size;
        private Node<T> top;

        public Stack() {
            size = 0;
            top = null;
        }

        public void push(T data) {
            Node<T> node = new Node<T>(data);
            node.next = top;
            top = node;
            size++;
        }

        public T pop() {
            if (isEmpty()) {
                throw new java.lang.RuntimeException();
            }
            T value = top.value;
            top = top.next;
            size--;
            return value;
        }

        public boolean isEmpty() {
            return size == 0;
        }

        private static class Node<T> {
            private T value;
            private Node<T> next;

            public Node(T value) {
                this.value = value;
                this.next = null;
            }
        }
    }

}
