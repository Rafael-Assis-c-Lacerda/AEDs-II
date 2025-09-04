import java.util.Scanner;

public class Main {
    static Scanner scanner = new Scanner(System.in);

    public static String formatarLinha(String linha, boolean[] variaveis){ // formatar linhas das Variaveis por 0 ou 1
        StringBuilder str = new StringBuilder();
        
        for(int i =0; i< linha.length(); i++){
            if(linha.charAt(i)!= ' '){
                if(linha.charAt(i) >= 'A' && linha.charAt(i) <= 'Z'){
                    str.append(variaveis[linha.charAt(i)-65] ? '1' : '0');
                }else{
                    str.append(linha.charAt(i));
                }
            }
        }
        return str.toString();
    }

    public static String resolverOperadores(String str, int index) {
        StringBuilder nova = new StringBuilder();
        
        // Encontrar o fechamento do parêntese
        int j = index;
        int nivel = 1;
        while (nivel > 0 && j < str.length() - 1) {
            j++;
            if (str.charAt(j) == '(') nivel++;
            if (str.charAt(j) == ')') nivel--;
        }
        
        // Encontrar o início do operador
        int inicioOperador = index - 1;
        while (inicioOperador >= 0 && Character.isLetter(str.charAt(inicioOperador))) {
            inicioOperador--;
        }
        inicioOperador++;
        
        String operador = str.substring(inicioOperador, index);
        String conteudo = str.substring(index + 1, j);
        
        char resposta = '0';
        
        switch (operador) {
            case "not":
                if (conteudo.equals("0")) {
                    resposta = '1';
                }
                break;
            case "and":
                resposta = '1';
                for (int i = 0; i < conteudo.length(); i++) {
                    if (conteudo.charAt(i) == '0') {
                        resposta = '0';
                        break;
                    }
                }
                break;
            case "or":
                resposta = '0';
                for (int i = 0; i < conteudo.length(); i++) {
                    if (conteudo.charAt(i) == '1') {
                        resposta = '1';
                        break;
                    }
                }
                break;
            default:
                break;
        }

        // Construir a nova string
        for (int i = 0; i < str.length(); i++) {
            if (i < inicioOperador || i > j) {
                nova.append(str.charAt(i));
            } else if (i == inicioOperador) {
                nova.append(resposta);
            }
        }
        return nova.toString();
    }

    public static String resolverExpressaoAuxi(String expressao, int index) {
        if (index < 0) {
            return expressao;
        } else {
            if (expressao.charAt(index) == '(') {
                expressao = resolverOperadores(expressao, index);
                return resolverExpressaoAuxi(expressao, expressao.length() - 1);
            }
            return resolverExpressaoAuxi(expressao, index - 1);
        }
    }

    public static String resolverExpressao(String expressao){
        return resolverExpressaoAuxi(expressao,expressao.length()-1);
    }

    public static void main(String[]args){
        int num; // numero de variaveis

        while( (num = scanner.nextInt())!= 0){ // loop para rodar ate a condicição inicial ser 0
            // Lê os valores das variáveis (0 ou 1)
            boolean[] variaveis = new boolean[num];
            for (int i = 0; i < num; i++) {
                variaveis[i]=scanner.next("[0-9]").charAt(0) != '0';
            }
            
            
            // Lê a expressão lógica
            String expressao = scanner.nextLine();
            
            // Formata a expressão substituindo variáveis por valores
            String formatada = formatarLinha(expressao, variaveis);


            String resultado = resolverExpressao(formatada);

            System.out.println(resultado);
        }
        scanner.close();
    }
}