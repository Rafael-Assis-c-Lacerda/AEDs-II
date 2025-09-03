import java.util.Scanner;

public class Main {
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

    public static String removerEspacos(String str) {
        char[] chars = new char[str.length()];
        int count = 0;
        
        for (int i = 0; i < str.length(); i++) {
            char c = str.charAt(i);
            if (c != ' ') {
                chars[count++] = c;
            }
        }
        
        return new String(chars, 0, count);
    }

    public static int stringParaInt(String str) {
        int resultado = 0;
        for (int i = 0; i < str.length(); i++) {
            char c = str.charAt(i);
            if (c >= '0' && c <= '9') {
                resultado = resultado * 10 + (c - '0');
            }
        }
        return resultado;
    }

    public static String[] dividirPorVirgula(String str) {
        // Contar vírgulas no nível mais externo
        int countVirgulas = 0;
        int nivelParenteses = 0;
        
        for (int i = 0; i < str.length(); i++) {
            char c = str.charAt(i);
            if (c == '(') nivelParenteses++;
            else if (c == ')') nivelParenteses--;
            else if (c == ',' && nivelParenteses == 0) {
                countVirgulas++;
            }
        }
        
        String[] partes = new String[countVirgulas + 1];
        int start = 0;
        int parteIndex = 0;
        nivelParenteses = 0;
        
        for (int i = 0; i < str.length(); i++) {
            char c = str.charAt(i);
            
            if (c == '(') nivelParenteses++;
            else if (c == ')') nivelParenteses--;
            
            if (c == ',' && nivelParenteses == 0) {
                partes[parteIndex++] = str.substring(start, i);
                start = i + 1;
            }
        }
        
        // Adicionar a última parte
        if (start < str.length()) {
            partes[parteIndex] = str.substring(start);
        }
        
        return partes;
    }

    public static boolean processarAND(String interior, boolean[] valores) {
        String[] parametros = dividirPorVirgula(interior);
        
        boolean resultado = true;
        for (String param : parametros) {
            if (param != null && param.length() > 0) {
                resultado = resultado && avaliarExpressao(param, valores);
            }
        }
        return resultado;
    }
    
    public static boolean processarOR(String interior, boolean[] valores) {
        String[] parametros = dividirPorVirgula(interior);
        
        boolean resultado = false;
        for (String param : parametros) {
            if (param != null && param.length() > 0) {
                resultado = resultado || avaliarExpressao(param, valores);
            }
        }
        return resultado;
    }

    public static boolean avaliarExpressao(String expr, boolean[] valores) {
        boolean resultado = true;

        if (expr.length() == 1 && expr.charAt(0) >= 'A' && expr.charAt(0) <= 'Z') {
            int index = expr.charAt(0) - 'A';
            if (index < valores.length) {
                return valores[index];
            }
            return false;
        }

        // Verificar negação
        if (expr.startsWith("not(") && expr.endsWith(")")) {
            String interior = expr.substring(4, expr.length() - 1);
            resultado = !avaliarExpressao(interior, valores);
        }
        
        // Verificar AND
        if (expr.startsWith("and(") && expr.endsWith(")")) {
            String interior = expr.substring(4, expr.length() - 1);
            resultado = processarAND(interior, valores);
        }
        
        // Verificar OR
        if (expr.startsWith("or(") && expr.endsWith(")")) {
            String interior = expr.substring(3, expr.length() - 1);
            resultado = processarOR(interior, valores);
        }

        return resultado;
    }

    public static boolean resolverExpressao(String expressao, boolean[] valores){
        String exprSemEspacos = removerEspacos(expressao);
        return avaliarExpressao(exprSemEspacos, valores);
    }

    public static void main(String [] args ){

        boolean continuar = true;
        String flag = "0";
        
        while(continuar){

            String input = scanner.nextLine();

            // Separar a string manualmente
            int[] espacos = new int[50]; // Array para armazenar posicoes dos espaços
            int countEspacos = 0;

            if (compare(input, flag)) {
                continuar = false;
            }else{

                // Encontrar todos os espaços
                for (int i = 0; i < input.length(); i++) {
                    if (input.charAt(i) == ' ') {
                        espacos[countEspacos++] = i;
                    }
                }

                // Extrair números
                String numVariaveisStr = input.substring(0, espacos[0]);
                int numVariaveis = stringParaInt(numVariaveisStr);
                
                // Extrair valores das variáveis
                boolean[] valores = new boolean[numVariaveis];
                
                for (int i = 0; i < numVariaveis; i++) {
                    int start = espacos[i] + 1;
                    int end = (i < numVariaveis - 1) ? espacos[i + 1] : input.length();
                    String valorStr = input.substring(start, end);
                    valores[i] = (stringParaInt(valorStr) == 1);
                }

                // Extrair expressão (tudo depois do ultimo numero)
                String expressao = input.substring(espacos[numVariaveis] + 1);

                boolean resultado = resolverExpressao(expressao, valores);

                //printa resultado
                if(resultado){
                    System.out.println("1");
                }else{
                    System.out.println("0");
                }
            }
        }
        scanner.close();
    }
}