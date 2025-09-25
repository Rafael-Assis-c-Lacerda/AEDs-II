import java.util.Random;
import java.util.Scanner;
import java.util.Arrays;

public class Main {
    static Scanner scanner = new Scanner(System.in);

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

    public static int median(int[] array, int esq, int dir) {
        int mid = (esq + dir) / 2;
        int a = array[esq];
        int b = array[mid];
        int c = array[dir];
        
        if (a > b) {
            if (a < c) return esq;
            else if (b > c) return mid;
            else return dir;
        } else {
            if (b < c) return mid;
            else if (a > c) return esq;
            else return dir;
        }
    }

    public static void quicksortMedian(int[] array, int esq, int dir) {
        if (esq >= dir) return;

        // Escolhe pivô pela mediana de três e move para o início
        int med = median(array, esq, dir);
        swap(array, esq, med); // move a mediana para o início
        int pivo = array[esq];

        int i = esq + 1;  // Começa de esq + 1, já que o pivô está na posição esq
        int j = dir;

        while (i <= j) {
            // Encontre um elemento maior que o pivô
            while (i <= dir && array[i] < pivo) i++;
            // Encontre um elemento menor que o pivô
            while (j >= esq && array[j] > pivo) j--;

            if (i <= j) {
                swap(array, i, j);
                i++;
                j--;
            }
        }

        // Coloca o pivô na posição correta
        swap(array, esq, j);

        // Recursão nas duas metades
        quicksortMedian(array, esq, j - 1);
        quicksortMedian(array, j + 1, dir);
    }

    // Gera arrays para teste
    public static int[] generateRandomArray(int size) {
        Random rand = new Random();
        int[] array = new int[size];
        for (int i = 0; i < size; i++) {
            array[i] = rand.nextInt(size * 2);
        }
        return array;
    }

    public static int[] generateSortedArray(int size) {
        int[] array = new int[size];
        for (int i = 0; i < size; i++) {
            array[i] = i;
        }
        return array;
    }

    public static int[] generateAlmostSortedArray(int size) {
        int[] array = generateSortedArray(size);
        Random rand = new Random();
        int swaps = Math.max(1, size / 100);
        for (int i = 0; i < swaps; i++) {
            int idx1 = rand.nextInt(size);
            int idx2 = rand.nextInt(size);
            swap(array, idx1, idx2);
        }
        return array;
    }

    // Função para clonar array para evitar alterar o original durante testes
    public static int[] cloneArray(int[] original) {
        return Arrays.copyOf(original, original.length);
    }
    public static void main(String[] args) {
        // Criação do array e escolha do tamanho
        int[] array;
        int size = 10000;

        // Gera o array original
        //array = generateRandomArray(size);
        //array = generateSortedArray(size);
        array = generateAlmostSortedArray(size);

        // Quicksort com pivô aleatório
        long start = System.nanoTime();
        int[] copyForRandomQuicksort = cloneArray(array);
        quicksort(copyForRandomQuicksort, 0, copyForRandomQuicksort.length - 1);
        long end = System.nanoTime();
        long duration = end - start;
        System.out.println("Tempo para Quicksort Aleatório com tamanho de array " + size + ": " + duration / 1_000_000.0 + " ms");

        // Quicksort com pivô no início
        start = System.nanoTime();
        int[] copyForStartQuicksort = cloneArray(array);
        quicksortFirst(copyForStartQuicksort, 0, copyForStartQuicksort.length - 1);
        end = System.nanoTime();
        duration = end - start;
        System.out.println("Tempo para Quicksort com Pivô no Início com tamanho de array " + size + ": " + duration / 1_000_000.0 + " ms");

        // Quicksort com pivô no final
        start = System.nanoTime();
        int[] copyForEndQuicksort = cloneArray(array);
        quicksortLast(copyForEndQuicksort, 0, copyForEndQuicksort.length - 1);
        end = System.nanoTime();
        duration = end - start;
        System.out.println("Tempo para Quicksort com Pivô no Final com tamanho de array " + size + ": " + duration / 1_000_000.0 + " ms");

        // Quicksort com pivô mediana de três
        start = System.nanoTime();
        int[] copyForMedianQuicksort = cloneArray(array);
        quicksortMedian(copyForMedianQuicksort, 0, copyForMedianQuicksort.length - 1);
        end = System.nanoTime();
        duration = end - start;
        System.out.println("Tempo para Quicksort com Mediana de Três com tamanho de array " + size + ": " + duration / 1_000_000.0 + " ms");

        scanner.close();
    }
}