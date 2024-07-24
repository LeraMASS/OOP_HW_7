#include <iostream>
#include <cstdlib>
#include <ctime>

template <typename T>
class Matrix {
private:
    T** data;      // Указатель на двумерный массив
    int rows;      // Количество строк
    int cols;      // Количество столбцов

public:
    // Конструктор
    Matrix(int r, int c) : rows(r), cols(c) {
        data = new T * [rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new T[cols];
        }
    }

    // Деструктор
    ~Matrix() {
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    // Метод для заполнения матрицы с клавиатуры
    void fillFromInput() {
        std::cout << "Введите элементы матрицы " << rows << " x " << cols << ":\n";
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cin >> data[i][j];
            }
        }
    }

    // Метод для заполнения матрицы случайными значениями
    void fillRandom(int min = 0, int max = 100) {
        std::srand(std::time(0));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                data[i][j] = min + std::rand() % (max - min + 1);
            }
        }
    }

    // Метод для отображения матрицы
    void display() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // Метод для поиска максимального элемента
    T findMax() const {
        T maxElement = data[0][0];
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (data[i][j] > maxElement) {
                    maxElement = data[i][j];
                }
            }
        }
        return maxElement;
    }

    // Метод для поиска минимального элемента
    T findMin() const {
        T minElement = data[0][0];
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (data[i][j] < minElement) {
                    minElement = data[i][j];
                }
            }
        }
        return minElement;
    }

    // Перегрузка оператора сложения
    Matrix<T> operator+(const Matrix<T>& other) {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrices dimensions must be the same for addition.");
        }
        Matrix<T> result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }
};

// Пример использования
int main() {
    setlocale(LC_ALL, "RU");
    Matrix<int> mat1(2, 3);
    mat1.fillFromInput();
    mat1.display();

    Matrix<int> mat2(2, 3);
    mat2.fillRandom();
    mat2.display();

    Matrix<int> mat3(2, 3);
    mat3.fillRandom();
    mat3.display();

    Matrix<int> sum = mat2 + mat3;
    std::cout << "Сумма матриц:\n";
    sum.display();

    std::cout << "Максимальный элемент в первой матрице: " << mat1.findMax() << std::endl;
    std::cout << "Минимальный элемент во второй матрице: " << mat2.findMin() << std::endl;

    return 0;
}