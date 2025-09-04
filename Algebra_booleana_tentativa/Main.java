import java.util.Scanner;

public class Main {
    static Scanner scanner = new Scanner(System.in);

    public static String formatarLinha(String linha, boolean[] variaveis){ // formatar linhas das Variaveis por 0 ou 1
        StringBuilder str = new StringBuilder();

        System.out.println("xx");
        
        for(int i =0; i< linha.length(); i++){
                if(linha.charAt(i) >= 'A' && linha.charAt(i) <= 'Z'){
                    str.append(variaveis[linha.charAt(i)-65] ? '1' : '0');
                }else{
                    str.append(linha.charAt(i));
                }

        }
        return str.toString();
    }

    public static String resolverOperadores(String str, int index){
        StringBuilder nova = new StringBuilder();

        System.out.println("a");
        
        int j = 0;
        for(j = index; str.charAt(j)!=')';j++){}
        char resposta = '0';
        char operador = str.charAt(index-1);

        switch (operador) {
            case't':
                if(str.charAt(index+1)=='0'){
                    resposta = '1';
                }
                index-=3;
                break;
            case'd':
                resposta = 1;

                for(int i = index+1;i<j;i++){
                    if(str.charAt(i)=='0'){
                        resposta='0';
                        i=j;
                    }
                }
                index-=3;
                break;
            case'r':
                resposta = '0';

                for(int i = index+1;i<j;i++){
                    if(str.charAt(i)=='1'){
                        resposta='1';
                        i=j;
                    }
                }
                break;
            default:
                break;
        }

        for(int i = 0; i<str.length();i++){
            if(i<index||i>j){
                nova.append(str.charAt(i));
            }else if(index==i){
                nova.append(resposta);
            }
        }
        return nova.toString();
    }

    public static String resolverExpressaoAuxi(String expressao, int index){
        System.out.println("teste 1");
        if(index==0){
             System.out.println("teste parada");
            return expressao;
        }else{
             System.out.println("teste 2");
            if(expressao.charAt(index)=='('){
                 System.out.println("teste parenteses");
                expressao = resolverOperadores(expressao, index);
                return resolverExpressaoAuxi(expressao, expressao.length());
            }
            return resolverExpressaoAuxi(expressao,index-1);
        }
    }

    public static String resolverExpressao(String expressao){
        return resolverExpressaoAuxi(expressao,expressao.length());
    }

    public static void main(String[]args){
        int num; // numero de variaveis

        while( (num = scanner.nextInt())!= 0){ // loop para rodar ate a condicição inicial ser 0
            // Lê os valores das variáveis (0 ou 1)
            boolean[] variaveis = new boolean[num];
            for (int i = 0; i < num; i++) {
                variaveis[i]=scanner.next("[0-9]").charAt(0) != '0';
            }
            
            System.out.println("inicio1");
            
            // Lê a expressão lógica
            String expressao = scanner.nextLine();

            System.out.println(expressao);
            
            // Formata a expressão substituindo variáveis por valores
            String formatada = formatarLinha(expressao, variaveis);

            System.out.println(formatada);

            //System.out.println(formatada);

            String resultado = resolverExpressao(formatada);

            System.out.println(resultado);
        }
        scanner.close();
    }
}
