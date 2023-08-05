from vector import Vector, Vector3D, Vector2D
from abc import ABC, abstractmethod
from MatrixIterator import *
from MatrixError import *



class SquareMatrix(ABC):
    """Клас квадратних матриць. Для створення треба ввести елементи матриці"""
    def __init__(self, data: list):
        """
        :self._dimension: private attribute of dimension
        :param data: 2-dimensional list
        """
        self._data = data
        if not self.is_square():   # if the matrix isn't square, raise an error
            raise ValueError("The matrix isn't square")
        self._dimension = len(self._data)

    def __iter__(self):
        """
        Making matrix iterable
        :return: MatrixIterator type
        """
        return MatrixIterator(self)

    @property
    def dimension(self):
        """Повертаємо розмірність"""
        return self._dimension

    def __add__(self, other):
        """
        :param other: SquareMatrix or Vector or int, float type
        :return: SquareMatrix type
        """
        dim = self.dimension
        if isinstance(other, SquareMatrix):  # Додавання матриць
            if other.dimension == dim:
                return type(self)([[self[i, j] + other[i, j] for j in range(dim)] for i in range(dim)])
            else:  # Породження помилки у разі різної розмірності
                raise MatrixOperationError("Can't add matrices of different dimensions", self, other)
        elif isinstance(other, Vector):  # Додавання вектора кожного стовпця матриці
            if dim == len(other):
                return type(self)([[self[j, i] + other[j] for i in range(dim)] for j in range(dim)])
            else:
                raise MatrixOperationError("Can't add a vector to a matrix with different dimension", self, other)
        elif isinstance(other, int) or isinstance(other, float):  # Додавання числа до кожного елемента
            return type(self)([[self[j, i] + other for i in range(dim)] for j in range(dim)])
        else:  # Породженння помилки у разі додавання іншого типу
            raise MatrixOperationError(f"Can't add {type(other)} type to a matrix", self, other)

    def __mul__(self, other):
        """
        :param other: SquareMatrix or Vector or int, float type
        :return: SquareMatrix type
        """
        dim = self.dimension
        if isinstance(other, SquareMatrix):  # Множення матриць
            if other.dimension == dim:
                res = []  # тут буде результуяча матриця
                for i in range(dim):
                    row = []
                    for j in range(dim):  # рядок першої матриці множимо на стопчик другої
                        row.append(self[i]*Vector([other[x][j] for x in range(dim)]))
                    res.append(row)  # додаємо рядок до результату
                return type(self)(res)
            else:  # Породження помилки у разі різної розмірності
                raise MatrixOperationError("Can't multiply square matrices of different dimensions", self, other)
        elif isinstance(other, Vector):  # Множення матриці на вектор. Результат - вектор
            if dim == len(other):
                res = [sum(self[i][j] * other[j] for j in range(dim)) for i in range(dim)]
                return type(other)(res)
            else:
                raise MatrixOperationError("The length of the vector is not the same as of the matrix", self, other)
        elif isinstance(other, int) or isinstance(other, float):  # Множення матриці на число
            return type(self)([[self[j, i] * other for i in range(dim)] for j in range(dim)])
        else:  # Породженння помилки у разі додавання іншого типу
            raise MatrixOperationError(f"Can't add {type(other)} type to a matrix", self, other)

    def __round__(self, n):
        for i in range(self.dimension):
            for j in range(self.dimension):
                self[i,j] = round(self[i,j], n)
        return self

    def __getitem__(self, indeces):
        """
        get item from the matrix
        :param indeces: tuple(when we want to get an element), int(when we want to get a row)
        :return: Vector or int
        """
        try:
            if isinstance(indeces, tuple):  # Повертаємо елемент матриці
                return self._data[indeces[0]][indeces[1]]
            elif isinstance(indeces, int):  # Повертаємо рядок матриці
                if len(self._data[indeces]) == 2:
                    return Vector2D(self._data[indeces])
                else:
                    return Vector3D(self._data[indeces])
        except IndexError:
            # Перевірка на випадок якщо користувач введе не той індекс
            raise IndexError("The index is out of range")

    def __setitem__(self, indeces, value):
        """
        Changing element of the matrix
        :param indeces:
        :param value: tuple(when we want to change an element), int(when we want to change a row)
        :return:
        """
        try:
            if isinstance(indeces, tuple):  # Змінюємо елемент матриці
                self._data[indeces[0]][indeces[1]] = value
            elif isinstance(indeces, int):  # Змінюємо рядок матриці
                self._data[indeces] = value
        except IndexError:
            # Перевірка на випадок якщо користувач введе не той індекс
            raise IndexError("The index is out of range")

    def __str__(self):
        """
        printing matrix, raise ValueError if not square
        :return: str
        """
        if not self.is_square():
            raise ValueError("The matrix isn't square. Can't be printed")
        return "\n".join([''.join(["{}   ".format(el) for el in row]) for row in self._data])

    def max(self):
        """
            :return: max element of the matrix
            """
        max_el = 0
        for el in self:
            if el > max_el:
                max_el = el
        return max_el

    def min(self):
        """
        :return: min of the matrix
        """
        min_el = self[0, 0]
        for el in self:
            if el < min_el:
                min_el = el
        return min_el

    def sum_mean(self):
        """
        :return: sum and mean of the matrix elements
        """
        sum_matr = 0
        for el in self:
            sum_matr += el
        return sum_matr, sum_matr / self.dimension ** 2

    @abstractmethod
    def __call__(self):
        """
        Calculating the determinant
        :return: int
        """
        pass

    @abstractmethod
    def _is_degenerate(self):
        """
        check whether the matrix is degenerate
        :return:
        """
        pass

    def replace_column(self, new_column: tuple, old_column: int):
        """
        replace the column of the matrix with other elements
        :param new_column: tuple
        :param old_column: int
        :return:
        """
        for i, row in enumerate(self._data):
            row[old_column] = new_column[i]

    @classmethod
    def keyboard_input(cls, dimension: int):
        """
        input matrix data from keyboard
        :param dimension: int
        :return: Square_Matrix
        """
        data = []
        for i in range(dimension):
            row = input(f'Enter the {i+1}-th row: ').split()
            data.append(list(map(int, row)))
        return cls(data)

    @classmethod
    def file_input(cls, file):
        """
        input matrix data from file
        :param file: file
        :return: Square_Matrix
        """
        with open(file, "r") as matrix_file:
            data = []
            for number, line in enumerate(matrix_file):
                row = line.split()
                data.append(list(map(int, row)))
            return cls(data)

    def is_square(self):
        """
        checking if the matrix is square
        :return: list 
        """
        return all([True if len(row) == len(self._data) else False for row in self._data])


if __name__ == "__main__":
    pass