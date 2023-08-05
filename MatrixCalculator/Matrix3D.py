from square_matrix import SquareMatrix
from Matrix2D import Matrix2D


class Matrix3D(SquareMatrix):
    """Клас квадратної матриці розмірності 3"""
    def __init__(self, data=None):
        if len(data) != 3: #Перевірка чи у матриці розмірність 3
            raise ValueError("The matrix isn't 3D")
        super().__init__(data)

    def __call__(self):
        """Рахуємо детермінант для розмірності 3"""
        det = 0
        for i, row in enumerate(self._data):
            truncated_matrix = self._data[:i] + self._data[i + 1:]
            truncated_matrix = [truncated_matrix[0][1:], truncated_matrix[1][1:]]
            minor_matrix = Matrix2D(truncated_matrix)  # Вирізаємо матрицю, щоб порахувати мінор
            det += row[0]*(-1)**(i+2)*minor_matrix()
        return det

    def _is_degenerate(self):
        """Перевірка на виродженість"""
        return self() == 0

    @classmethod
    def keyboard_input(cls, dimension=3):
        return super().keyboard_input(dimension)


if __name__ == "__main__":
    a = Matrix3D.keyboard_input()
    print(a)
    b = Matrix2D.file_input("matrices.txt")
    print(b)
