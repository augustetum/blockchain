import java.math.BigInteger;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class Hash {
    public static void main(String[] args){

        System.out.println("Hash generatorius");
        System.out.println("-----------------");
        System.out.println("Įveskite norimą hashuoti tekstą / simbolius");

        Scanner in = new Scanner(System.in);
        String input = in.nextLine();

        int[] resultList = {0, 0, 0, 0, 0, 0, 0, 0};

        List<String> splitString = usingSplitMethod(input, 8);

        String hash = "";

        System.out.println(hash);

    }

    //Splits the input string into equally sized substrings
    public static List<String> usingSplitMethod(String text, int n) {
        String[] results = text.split("(?<=\\G.{" + n + "})");

        return Arrays.asList(results);
    }

    //Turns String into a hexadecimal
    public String toHex(String arg) {
        return String.format("%040x", new BigInteger(1, arg.getBytes(StandardCharsets.UTF_8)));
    }
}