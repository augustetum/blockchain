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

        int length = input.length(); //Paima input'o ilgį
        int splitLength = length / 10; //Kokio ilgio bus kiekviena dalis

        List<String> hashuojami = usingSplitMethod(input, splitLength); //Splittina input į dalis


        int count = 1;
        for (String x : hashuojami){
            String hexas = toHex(x);
            char[] chr = hexas.toCharArray();
            double kodas = 0;
            for (char i : chr) {
                kodas += (int) i;
            }
            kodas += (x.charAt(0)+count);
            count+= x.charAt(0);
            System.out.println(addFirstLastNum(kodas));
        }





    }

    //Splits the input string into equally sized substrings
    public static List<String> usingSplitMethod(String text, int n) {
        String[] results = text.split("(?<=\\G.{" + n + "})");

        return Arrays.asList(results);
    }

    //Turns String into a hexadecimal
    public static String toHex(String arg) {
        return String.format("%040x", new BigInteger(1, arg.getBytes(StandardCharsets.UTF_8)));
    }


    public static int addFirstLastNum(double number) {
        String numStr = String.valueOf((long) number);
        int firstTwo = Integer.parseInt(numStr.substring(0, 2));
        int lastTwo = Integer.parseInt(numStr.substring(numStr.length() - 2));

        return firstTwo + lastTwo;
    }
}