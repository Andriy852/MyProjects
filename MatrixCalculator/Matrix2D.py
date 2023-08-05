from square_matrix import *


class Matrix2D(SquareMatrix):
    """Клас матриці розмірності 2"""
    def __init__(self, data: list):
        if len(data) != 2: #Перевірка чи матриця розмірності 2
            raise ValueError("The matrix isn't 2D")
        super().__init__(data)

    def __call__(self):
        """Рахуємо детермінант для розмірності 2"""
        if not self.is_square():
            raise ValueError("Matrix is not square")
        return self._data[0][0]*self._data[1][1]-self._data[0][1]*self._data[1][0]

    def _is_degenerate(self):
        """Перевірка на виродженість"""
        return self() == 0

    @classmethod
    def keyboard_input(cls, dimension=2):
        return super().keyboard_input(dimension)


if __name__ == "__main__":
    a = Matrix2D([[12, 10],[1, 2]])
    print(a)
#     # b = Matrix2D([[9, 8], [3, 4]])
#     # c = a + b
#     # d = a + 10
#     # vec = Vector([10,5])
#     # print(c)
#     # print(d)
#     # b_vec = b + vec
#     # a_vec = a + vec
#     # print(b_vec)
#     # print(a_vec)
    print(a.max())
