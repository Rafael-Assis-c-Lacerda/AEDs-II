import java.util.Scanner;

public class Main{
    static Scanner scanner = new Scanner(System.in);

    public static boolean compare(String str1, String str2) { //função que compara duas strings
            boolean resposta = true;

            if (str1.length() != str2.length()) { //verifica o tamnho, dependendo ja da falso
                resposta = false;
            }else{
                boolean diferente = false;
                int i = 0;

                while (i < str1.length() && !diferente) { //while que passa por todos os caracteres
                    if (str1.charAt(i) != str2.charAt(i)) { //verifica se letra por letra é igual
                        diferente = true;
                        resposta = false;
                    }
                i++;
                }
            }
        return resposta;
    }

    public static boolean anagrama(String str1, String str2){
        boolean resultado = true;
        
        // Ignora maiúsculas/minúsculas
        str1 = str1.toLowerCase();
        str2 = str2.toLowerCase();

        if(str1.length()!=str2.length()){
            resultado = false;
        }else{
            // Contar frequência dos caracteres para str1 e str2
            int[] freq = new int[256];

            // Incrementa para str1
            for (int i = 0; i < str1.length(); i++) {
                freq[str1.charAt(i)]++;
            }

            // Decrementa para s2
            for (int i = 0; i < str2.length(); i++) {
                freq[str2.charAt(i)]--;
            }

            for(int i = 0; i<256; i++){
                if(freq[i]!= 0){
                    resultado = false;
                }
            }
        }
        return resultado;
    }

    public static void main(String [] args){
        String flag = "FIM"; //string de termino
        boolean continuar = true; //flag booleana


        while(continuar){ //loop para continuar até encontrar o FIM

            String str = scanner.nextLine();

            StringBuilder sb = new StringBuilder();

            String[] palavras = new String[2];

            int j = 0;
            for(int i = 0; i<str.length(); i++){
                if(str.charAt(i)!=' ' && str.charAt(i)!='-'){
                    char c = str.charAt(i);
                    sb.append(c);
                }else{
                    if (sb.length() > 0) { // só adiciona se tiver algo
                        palavras[j] = sb.toString();
                        j++;
                        sb.setLength(0); // limpa o StringBuilder para próxima palavra
                    }
                }
            }

            // Para pegar a última palavra após o loop, se existir
            if (sb.length() > 0 && j < 2) {
                palavras[j] = sb.toString();
            }

            if(compare(str, flag)) { //verifica ocorrencia do FIM e decide se o programa acaba
                continuar = false;
            }else{ //printa respostas
                boolean resposta = anagrama(palavras[0], palavras[1]);

                if(resposta){
                    System.out.println("SIM");
                }else{
                    //System.out.println("NÃO"); 
                    MyIO.println("NÃO"); // Tive que utilizar por conta do verde nao aceitar o ~

                }
            }

        }
	scanner.close();
   }
}