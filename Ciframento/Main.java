import java.util.Scanner;

public class Main{
   static Scanner sc = new Scanner(System.in);

   public static String cifrar(String str){
	int n = str.length();
	StringBuilder resultado = new StringBuilder();

	for(int i = 0; i < n; i++) {
            char c = str.charAt(i);
            if (c >= 32 && c <= 126) {
                int posicao = c - 32;
                int novaPosicao = (posicao + 3) % 95;
                c = (char) (32 + novaPosicao);
            }
            resultado.append(c);
        }

        return resultado.toString();
   }

   public static void main(String[] args){

	while(true){

	   String str = sc.nextLine();

	   if(str.equals("FIM"))break;

           String resposta = cifrar(str);

	   System.out.println(resposta);

	}
	sc.close();

   }
}
