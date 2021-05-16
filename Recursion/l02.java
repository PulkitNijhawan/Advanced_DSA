import java.util.*;

public class l02 {
    public static void main(String[] args) {
        solve();
    }

    public static void solve() {
        int[] arr = { 2, 3, 5, 7 };
        System.out.println(permuInfi(arr, 10, " "));
        // // boolean[] visited=new boolean[arr.length];
        // int[][] board = new int[6][6];
        // for (int i = 0; i < board.length; i++) {
        // for (int j = 0; j < board[0].length; j++) {
        // board[i][j] = -1;
        // }
        // }

        // queen2D02(board, 4, 0, ""));

        // row=new boolean[4];
        // col=new boolean[4];
        // diag=new boolean[7];
        // adiag=new boolean[7];
        // int[] arr = {10, 20, 30, 40, 50, 60, 70, 80};
        // System.out.println(equiSet(arr, 1, 10, 0, "10", ""));
        // System.out.println(queen03(4,4, 4, 0, ""));
    }

    public static int permuInfi(int[] arr, int tar, String ans) {
        if (tar == 0) {
            System.out.println(ans);
            return 1;
        }
        int cnt = 0;
        for (int ele : arr) {
            if (tar - ele >= 0) {
                cnt += permuInfi(arr, tar - ele, ans + ele);
            }
        }
        return cnt;
    }

    public static int combiInfi(int[] arr, int tar, int idx, String ans) {
        if (tar == 0) {
            System.out.println(ans);
            return 1;
        }
        int cnt = 0;
        for (int i = idx; i < arr.length; i++) {
            if (tar - arr[i] >= 0) {
                cnt += combiInfi(arr, tar - arr[i], i, ans + arr[i]);
            }
        }
        return cnt;
    }

    public static int combi(int[] arr, int tar, int idx, String ans) {
        if (tar == 0) {
            System.out.println(ans);
            return 1;
        }
        int cnt = 0;
        for (int i = idx; i < arr.length; i++) {
            if (tar - arr[i] >= 0) {
                cnt += combi(arr, tar - arr[i], i + 1, ans + arr[i]);
            }
        }
        return cnt;
    }

    public static int permu(int[] arr, int tar, boolean[] visited, String ans) {
        if (tar == 0) {
            System.out.println(ans);
            return 1;
        }

        int cnt = 0;
        for (int i = 0; i < arr.length; i++) {
            if (!visited[i] && tar - arr[i] >= 0) {

                visited[i] = true;
                cnt += permu(arr, tar - arr[i], visited, ans + arr[i]);
                visited[i] = false;
            }
        }
        return cnt;
    }

    public static int combiInfi02(int[] arr, int tar, int idx, String ans) {
        if (idx == arr.length || tar == 0) {
            if (tar == 0) {
                System.out.println(ans);
                return 1;
            }
            return 0;
        }
        int cnt = 0;
        if (tar - arr[idx] >= 0) {
            cnt += combiInfi02(arr, tar - arr[idx], idx, ans + arr[idx]);
        }
        cnt += combiInfi02(arr, tar, idx + 1, ans);
        return cnt;
    }

    public static int combi02(int[] arr, int tar, int idx, String ans) {
        if (idx == arr.length || tar == 0) {
            if (tar == 0) {
                System.out.println(ans);
                return 1;
            }
            return 0;
        }
        int cnt = 0;
        if (tar - arr[idx] >= 0) {
            cnt += combi02(arr, tar - arr[idx], idx + 1, ans + arr[idx]);
        }
        cnt += combi02(arr, tar, idx + 1, ans);
        return cnt;
    }

    public static int permuInfi02(int[] arr, int tar, int idx, String ans) {
        if (idx == arr.length || tar == 0) {
            if (tar == 0) {
                System.out.println(ans);
                return 1;
            }
            return 0;
        }
        int cnt = 0;
        if (tar - arr[idx] >= 0) {
            cnt += permuInfi02(arr, tar - arr[idx], 0, ans + arr[idx]);
        }
        cnt += permuInfi02(arr, tar, idx + 1, ans);
        return cnt;
    }

    public static int permu02(int[] arr, int tar, int idx, boolean[] visited, String ans) {
        if (idx == arr.length || tar == 0) {
            if (tar == 0) {
                System.out.println(ans);
                return 1;
            }
            return 0;
        }
        int cnt = 0;
        if (!visited[idx] && tar - arr[idx] >= 0) {
            visited[idx] = true;
            cnt += permu02(arr, tar - arr[idx], 0, visited, ans + arr[idx]);
            visited[idx] = false;
        }
        cnt += permu02(arr, tar, idx + 1, visited, ans);
        return cnt;
    }

    // public static int qArr(int n,int q,String ans){
    // int cnt=0;
    // for(int i=;i<n;i++){
    // cnt+=qArr(n, q, ans+)
    // }
    // }

    public static int queen1D(int boxes, int tar, int idx, String ans) {
        if (tar == 0) {
            System.out.println(ans);
            return 1;
        }
        int cnt = 0;
        for (int i = idx; i <= boxes; i++) {
            cnt += queen1D(boxes, tar - 1, i + 1, ans + "b" + i + " ");
        }
        return cnt;
    }

    public static int queen2D(boolean[][] board, int tar, int idx, String ans) {
        if (tar == 0) {
            System.out.println(ans);
            return 1;
        }
        int cnt = 0;
        for (int i = idx; i < board.length * board.length; i++) {
            int r = i / board[0].length;
            int c = i % board[0].length;
            if (isSafe(board, r, c)) {
                board[r][c] = true;
                cnt += queen2D(board, tar - 1, i + 1, ans + "(" + r + "," + c + ")" + " ");
                board[r][c] = false;
            }
        }
        return cnt;
    }

    public static boolean isSafe(boolean[][] board, int row, int col) {
        int[][] dir = { { 0, -1 }, { -1, -1 }, { -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { 1, 0 }, { 1, -1 } };
        if (board[row][col])
            return false;
        for (int d = 0; d < dir.length; d++) {
            for (int mag = 1; mag <= board[0].length; mag++) {
                int x = row + mag * dir[d][0];
                int y = col + mag * dir[d][1];
                if (x >= 0 && y >= 0 && x < board.length && y < board.length) {
                    if (board[x][y]) {
                        return false;
                    }
                } else {
                    break;
                }

            }
        }
        return true;
    }

    public static int queen2D02(boolean[][] board, int tar, int idx, String ans) {
        if (idx == (board.length * board[0].length) - 1 || tar == 0) {
            if (tar == 0) {
                System.out.println(ans);
                return 1;
            }
            return 0;
        }
        int cnt = 0;
        int x = idx / board[0].length;
        int y = idx % board[0].length;
        if (isSafe(board, x, y)) {
            board[x][y] = true;
            int q = 4 - tar + 1;
            cnt += queen2D02(board, tar - 1, 0, ans + "Q" + q + ":" + "(" + x + "," + y + ") ");
            board[x][y] = false;

        }
        cnt += queen2D02(board, tar, idx + 1, ans);
        return cnt;

    }

    static int[][] dirK = { { 2, 1 }, { 1, 2 }, { -1, 2 }, { -2, 1 }, { -2, -1 }, { -1, -2 }, { 1, -2 }, { 2, -1 } };

    public static boolean knight_tour(int[][] board, int idx, int r, int c) {

        board[r][c] = idx;
        if (idx == board.length * board[0].length - 1) {
            for (int i = 0; i < board.length; i++) {
                for (int j = 0; j < board[0].length; j++) {
                    System.out.print(board[i][j] + " ");
                }
                System.out.println();
            }
            return true;
        }
        boolean res = false;
        for (int i = 0; i < dirK.length; i++) {
            int x = r + dirK[i][0];
            int y = c + dirK[i][1];
            if (x >= 0 && y >= 0 && x < board.length && y < board[0].length && board[x][y] == -1) {

                res = res || knight_tour(board, idx + 1, x, y);

            }
        }
        board[r][c] = -1;
        return res;
        // return;
    }

    static boolean[] row;
    static boolean[] col;
    static boolean[] diag;
    static boolean[] adiag;

    public static int queen03(int n, int m, int tar, int idx, String ans) {
        if (tar == 0) {
            System.out.println(ans);
            return 1;
        }
        int cnt = 0;
        for (int i = idx; i < n * m; i++) {
            int x = i / m;
            int y = i % m;
            if (!row[x] && !col[y] && !diag[x + y] && !adiag[x - y + m - 1]) {
                row[x] = true;
                col[y] = true;
                diag[x + y] = true;
                adiag[x - y + m - 1] = true;
                cnt += queen03(n, m, tar - 1, i + 1, ans + "(" + x + "," + y + ")" + " ");
                row[x] = false;
                col[y] = false;
                diag[x + y] = false;
                adiag[x - y + m - 1] = false;
            }
        }
        return cnt;
    }

    // ========================Equiset======================================================================================
    public static int equiSet(int[]arr, int idx, int set1, int set2, String set1S, String set2S)
{
    if (idx == arr.length)
    {
        // if (set1 == set2)
        // {
            System.out.println( set2S );
            return 1;
        // }

        // return 0;
    }
    
    int count = 0;
    count += equiSet(arr, idx + 1, set1 + arr[idx], set2, set1S + " " +arr[idx], set2S);
    count += equiSet(arr, idx + 1, set1, set2 + arr[idx], set1S, set2S + " " + arr[idx]);

    return count;
    

}
}