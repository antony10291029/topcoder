import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Solution {
    public Solution() {
    }
    public String getHint(String secret, String guess) {
        int bulls = 0, cows = 0;
        int[] vis = new int[secret.length()];
        for (int i = 0; i < secret.length(); ++i) {
            vis[i] = 0;
        }
        for (int i = 0; i < secret.length(); ++i) {
            if (secret.charAt(i) == guess.charAt(i)) {
                ++bulls;
            } else {
                ++vis[secret.charAt(i) - '0'];
            }
        }
        for (int i = 0; i < guess.length(); ++i) {
            if (secret.charAt(i) != guess.charAt(i)) {
                if (vis[guess.charAt(i) - '0'] > 0) {
                    --vis[guess.charAt(i) - '0'];
                    ++cows;
                }
            }
        }
        String res = "" + bulls + "A" + cows + "B";
        return res;

    }

    public void main() {
        int[] nums = new int[] { 9, 6, 1, 8 };
        System.out.println(new Solution().getHint("111", "110"));
    }

    public static void main(String[] args) {
        new Solution().main();
    }
}