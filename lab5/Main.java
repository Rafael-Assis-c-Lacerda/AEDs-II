import java.util.Random;
import java.util.Arrays;

public class Main {

    //função swap
    public static void swap(int [] array, int i, int j) {
		int temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}


    //diferentes quicksorts
    public static void quicksort(int [] array,int esq, int dir){
        int i = esq, j = dir;

        Random rand = new Random();
        int pivoIndex = rand.nextInt(dir - esq + 1) + esq;

        int pivo = array[pivoIndex];
        while (i <= j) {
            while (array[i] < pivo) i++;
            while (array[j] > pivo) j--;
            if (i <= j) {
                swap(array, i, j);
                i++;
                j--;
            }
        }
        if (esq < j)  quicksort(array, esq, j);
        if (i < dir)  quicksort(array, i, dir);
    }

    public static void quicksortFirst(int [] array,int esq, int dir){
        int i = esq, j = dir;
        int pivo = array[esq];
        while (i <= j) {
            while (array[i] < pivo) i++;
            while (array[j] > pivo) j--;
            if (i <= j) {
                swap(array, i, j);
                i++;
                j--;
            }
        }
        if (esq < j)  quicksortFirst(array, esq, j);
        if (i < dir)  quicksortFirst(array, i, dir);
    }

    public static void quicksortLast(int [] array,int esq, int dir){
        int i = esq, j = dir;
        int pivo = array[dir];
        while (i <= j) {
            while (array[i] < pivo) i++;
            while (array[j] > pivo) j--;
            if (i <= j) {
                swap(array, i, j);
                i++;
                j--;
            }
        }
        if (esq < j)  quicksortLast(array, esq, j);
        if (i < dir)  quicksortLast(array, i, dir);
    }

    public static void quickSortMedian(int array[], int left, int right) {
        int i = left, j = right;
        int a = array[left], b = array[(left + right) / 2], c = array[right];
        int pivo;
        if ((a >= b && a <= c) || (a <= b && a >= c)) pivo = a;
        else if ((b >= a && b <= c) || (b <= a && b >= c)) pivo = b;
        else pivo = c;

        while(i <= j) {
            while(array[i] < pivo) i++;
            while(array[j] > pivo) j--;
            if(i <= j) {
                swap(array, i, j);
                i++;
                j--;
            }
        }
        if(left < j) quickSortMedian(array, left, j);
        if(i < right) quickSortMedian(array, i, right);
    }

    // ---------- UTILITÁRIOS ----------

    public static void ordenado(int array[], int n) {
        for (int i = 0; i < n; i++) {
            array[i] = i;
        }
    }

    public static void random(int array[], int n) {
        Random rand = new Random();
        ordenado(array, n);
        for (int i = 0; i < n; i++) {
            swap(array, i, rand.nextInt(n));
        }
    }

    public static void meioOrdenado(int array[], int n) {
        Random rand = new Random();
        ordenado(array, n);
        for (int i = 0; i < n / 2; i++) {
            swap(array, i, rand.nextInt(n));
        }
    }

    public static long now() {
        return System.nanoTime();
    }

    // Função para clonar array para evitar alterar o original durante testes
    public static int[] cloneArray(int[] original) {
        return Arrays.copyOf(original, original.length);
    }
    public static void main(String args[]) {
        // Tamanhos que queremos testar
        int[] tamanhos = {100, 1000, 10000};

        for (int n : tamanhos) {
            
            int[] arrayOrdenado = new int[n];
            ordenado(arrayOrdenado, n);

            int[] arrayMeioOrdenado = new int[n];
            meioOrdenado(arrayMeioOrdenado, n);

            int[] arrayAleatorio = new int[n];
            random(arrayAleatorio, n);
            
            int[][] cenarios = {arrayOrdenado, arrayMeioOrdenado, arrayAleatorio};
            String[] nomesCenarios = {"Array Ordenado", "Array Meio Ordenado", "Array Aleatório"};

            System.out.println("\n#####################################################");
            System.out.println("   INICIANDO TESTES PARA N = " + n);
            System.out.println("#####################################################");

            for (int i = 0; i < cenarios.length; i++) {
                System.out.println("-----------------------------------------------------");
                System.out.println("CENARIO: " + nomesCenarios[i]);
                System.out.println("-----------------------------------------------------");

                int[] original = cenarios[i];
                long inicio, fim;

                // Pivô Primeiro
                int[] copia1 = Arrays.copyOf(original, n);
                inicio = now();
                quicksortFirst(copia1, 0, n - 1);
                fim = now();
                System.out.printf("Pivo Primeiro:   %.3f ms.\n", (fim - inicio) / 1_000_000.0);

                // Pivô Último
                int[] copia2 = Arrays.copyOf(original, n);
                inicio = now();
                quicksortLast(copia2, 0, n - 1);
                fim = now();
                System.out.printf("Pivo Ultimo:     %.3f ms.\n", (fim - inicio) / 1_000_000.0);

                // Pivô Aleatório
                int[] copia3 = Arrays.copyOf(original, n);
                inicio = now();
                quicksort(copia3, 0, n - 1);
                fim = now();
                System.out.printf("Pivo Aleatorio:  %.3f ms.\n", (fim - inicio) / 1_000_000.0);

                // Mediana de Três
                int[] copia4 = Arrays.copyOf(original, n);
                inicio = now();
                quickSortMedian(copia4, 0, n - 1);
                fim = now();
                System.out.printf("Mediana de Tres: %.3f ms.\n", (fim - inicio) / 1_000_000.0);
            }
        }
    }
}