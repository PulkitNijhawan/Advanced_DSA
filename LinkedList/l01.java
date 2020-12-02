import java.util.*;

public class l01 {
    public static class linkedlist {
        public class Node {
            int data;
            Node next;

            Node(int d) {
                this.data = d;
                this.next = null;
            }
        }

        Node head = null;
        Node tail = null;
        int size = 0;

        public int size() {
            return this.size;
        }

        public boolean isEmpty() {
            return this.size == 0;
        }
        @Override
        public String toString(){
            Node curr=head;
            String rv="";
            while(curr.next!=null){
                rv+=(curr.data);
                curr=curr.next;
            }
            return rv;
        }
        public void addFirst(int d) {
            Node n = new Node(d);
            if (this.size == 0) {
                this.head = n;
                this.tail = n;
            } else {
                n.next = head;
                this.head = n;
            }
            this.size++;
        }

        public void addLast(int d) {
            Node n = new Node(d);
            if (this.size == 0) {
                this.head = n;
                this.tail = n;
            } else {
                this.tail.next = n;
                tail = n;
            }
            this.size++;
        }

        public int removeFirst() {
            if (this.size == 0) {
                System.out.println("Exception");
                return -1;
            }
            Node rn = head;
            if (size == 1) {
                head = null;
                tail = null;
            } else {
                head = head.next;
                rn.next = null;
            }
            this.size--;
            return rn.data;
        }

        public Node getAt(int i) {
            Node itr = head;
            while (i-- > 0) {
                itr = itr.next;
            }
            return itr;
        }

        public int removeLast() {
            if (this.size == 0) {
                System.out.println("Exception");
                return -1;
            }
            Node rn = tail;
            if (this.size == 1) {
                head = null;
                tail = null;
            } else {
                Node scndLast = getAt(this.size - 2);
                scndLast.next = null;
                tail = scndLast;
            }
            this.size--;
            return rn.data;
        }

        public void addAt(int pos, int d) {
            if (pos > this.size || pos < 0)
                return;
            if (pos == 0)
                addFirst(d);
            else if (pos == this.size)
                addLast(d);
            else {
                Node n = new Node(d);
                Node prev = getAt(pos - 1);
                n.next = prev.next;
                prev.next = n;
                this.size++;
            }
        }

        public int removeAt(int pos) {
            if (pos >= this.size || pos < 0)
                return -1;
            if (pos == 0)
                return removeFirst();
            else if (pos == this.size - 1)
                return removeLast();
            else {
                Node prev = getAt(pos - 1);
                Node curr = prev.next;
                prev.next = curr.next;
                curr.next = null;
                this.size--;
                return curr.data;
            }
        }
    }
}