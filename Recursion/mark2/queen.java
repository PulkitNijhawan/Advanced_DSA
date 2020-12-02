import java.util.*;

public class queen {
    public static int queen1D(int tar, boolean[] boxes, String ans) {
        if (tar == 0) {
            System.out.println(ans);
            return 1;
        }
        int cnt = 0;
        for (int i = 0; i < boxes.length; i++) {

            if (!boxes[i]) {
                boxes[i] = true;
                cnt += queen1D(tar - 1, boxes, ans + "b" + (i + 1));
                boxes[i] = false;
            }

        }
        return cnt;
    }

    public static int queen1DCombi(int tar, int box, int boxes, String ans) {
        if (box > boxes || tar == 0) {
            if (tar == 0) {
                System.out.println(ans);
                return 1;
            }
            return 0;
        }
        int cnt = 0;
        cnt += queen1DCombi(tar - 1, box + 1, boxes, ans + "b" + box);
        cnt += queen1DCombi(tar, box + 1, boxes, ans);
        return cnt;
    }

    static int[][] dirA = { { 0, -1 }, { -1, -1 }, { -1, 0 }, { -1, 1 } };

    public static boolean isSafe(boolean[][] board, int x, int y) {
        for (int d = 0; d < dirA.length; d++) {
            for (int rad = 1; rad <= board.length; rad++) {
                int r = x + rad * dirA[d][0];
                int c = y + rad * dirA[d][1];

                if (r >= 0 && c >= 0 && r < board.length && c < board.length) {
                    if (board[r][c])
                        return false;
                } else
                    break;
            }
        }

        return true;
    }

    public static int nQueen(int tar, int idx, boolean[][] board, String ans) {
        if (tar == 0) {
            System.out.println(ans);
            return 1;
        }
        int cnt = 0;
        for (int i = idx; i < board.length * board[0].length; i++) {
            int x = i / board[0].length;
            int y = i % board[0].length;
            if (isSafe(board, x, y)) {
                board[x][y] = true;
                cnt += nQueen(tar - 1, i + 1, board, ans + "(" + x + "," + y + ") ");
                board[x][y] = false;
            }
        }
        return cnt;
    }

    static boolean[] row = new boolean[4];
    static boolean[] aDia = new boolean[7];
    static boolean[] dia = new boolean[7];
    static boolean[] col = new boolean[4];

    public static int nQueen02(int tar, int idx, String ans) {
        if (tar == 0) {
            System.out.println(ans);
            return 1;
        }
        int cnt = 0;
        for (int i = idx; i < 16; i++) {
            int x = i / 4;
            int y = i % 4;
            if (!row[x] && !col[y] && !dia[y - x + 3] && !aDia[x + y]) {
                row[x] = true;
                col[y] = true;
                dia[y - x + 3] = true;
                aDia[x + y] = true;
                cnt += nQueen02(tar - 1, i + 1, ans + "(" + x + "," + y + ") ");
                row[x] = false;
                col[y] = false;
                dia[y - x + 3] = false;
                aDia[x + y] = false;
            }
        }
        return cnt;
    }

    static int[][] kdirA = { { -2, 1 }, { -2, -1 }, { -1, 2 }, { -1, -2 }, { 2, 1 }, { 2, -1 }, { 1, 2 }, { 1, -2 } };

    public static boolean knightTour(int tar, int[][] board, int r,int c) {
        board[r][c]=tar;
        if (tar == board.length*board[0].length -1) {
            for (int[] arr : board) {
                for (int j : arr)
                    System.out.print(j + " ");
                System.out.println();
            }
            return true;
        }
        
        boolean res=false;
        for (int d = 0; d < kdirA.length; d++) {
            int x = r + kdirA[d][0];
            int y = c + kdirA[d][1];
            if (x >= 0 && y >= 0 && x < board.length && y < board[0].length && board[x][y] == -1) {
                
                res=res||knightTour(tar +1, board, x,y);
                
            }
        }
        board[r][c] = -1;
        return res;

    }

    

    public static void solve() {
        boolean[] boxes = new boolean[5];
        // boolean[][] board = new boolean[4][4];
        // for(Arrays.fill(board,)
        int[][] board = new int[5][6];
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[0].length; j++) {
                board[i][j] = -1;
            }
        }
        System.out.println(knightTour(0, board, 0,0));
    }

    public static void main(String[] args) {
        solve();
    }
}
