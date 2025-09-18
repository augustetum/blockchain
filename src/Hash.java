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

        List<String> splittedString = usingSplitMethod(input, 7);
        for (String i : splittedString){
            System.out.println(i);
        }



    }

    public static List<String> usingSplitMethod(String text, int n) {
        String[] results = text.split("(?<=\\G.{" + n + "})");

        return Arrays.asList(results);
    }


}