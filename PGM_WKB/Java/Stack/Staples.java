public class Staples {
    public static void main(String[] args) {
        Stack stack = new Stack();
        java.util.Scanner scanner = new java.util.Scanner(System.in);

        while (true) {
            String input = scanner.nextLine().trim();

            if (input.isEmpty()) {
                break;
            }

            if (input.startsWith("push ")) {
                String value = input.substring(5);
                stack.push(value);
            } else if (input.equals("pop")) {
                String value = stack.pop();
                System.out.println(value);
            } else {
                System.out.println("Invalid command");
            }
        }
    }
}

class Stack {
    private Node top;

    public void push(String value) {
        Node node = new Node(value);
        node.next = top;
        top = node;
    }

    public String pop() {
        if (top == null) {
            return null;
        }

        String value = top.value;
        top = top.next;
        return value;
    }

    private static class Node {
        private String value;
        private Node next;

        public Node(String value) {
            this.value = value;
        }
    }
}