import numpy.linalg

from Matrix2D import Matrix2D
from Matrix3D import Matrix3D
from vector import Vector3D,Vector2D,Vector
from copy import deepcopy
import numpy as np


class GaussianMethod:
    """Клас для реалізації розвязання лінійних рівнянь методом Гоуса"""
    def __init__(self, matrix, vector = None):
        """
        :param matrix: SquareMatrix
        :param vector: Vector; may be None if we want to just calculate the inverse
        """
        self.matrix = matrix
        self.vector = vector
    def solve(self):
        """Метод розвязання рівняння
        return: list
        """
        # Створюємо копії матриці і вектора для того щоб вони залишилися незмінними
        matrix = deepcopy(self.matrix)
        vector = deepcopy(self.vector)
        print(matrix)
        for i in range(matrix.dimension):
            if matrix[i, i] != 1: #Робимо найлівіший коефіцєнт одиницею
                if matrix[i] == Vector([0 for k in range(self.matrix.dimension)]):
                    # Якщо маємо нульовий рядок, то буде або безліч або 0 розвязків
                    if vector[i]!=0:
                        return "No solutions"
                    else:
                        return "Infinetely many solutions"
                const = 1/matrix[i, i]
                matrix = self.multiply_row(matrix, i, const)
                vector[i] = vector[i]*const
            for j in range(matrix.dimension): #Робимо нулі під одиницею
                if i!=j:
                    if matrix[j, i] != 0:
                        const = -matrix[j, i]
                        matrix = self.add_to_i_row_j_row_multiplied_const(matrix, j, i, const)
                        vector[j] = vector[j] + vector[i]*const
        #Повертаємо результат у вигляді списку. Розвязки заокруглені до сотень
        return list([round(vector[i],2) for i in range(len(vector))])

    def multiply_row(self, matrix, indx, const):
        """Функція для множення рядка на число.
        Те ж саме що функція додавання до i-го рядку j-го рядку помноженого на константу тільки i=j
        return: SquareMatrix
        """
        return self.add_to_i_row_j_row_multiplied_const(matrix, indx,indx,const)

    def add_to_i_row_j_row_multiplied_const(self, matrix, i, j, const):
        """
        Функція додавання до і-го рядку j-го рядку помноженого на константу
        return: SquareMatrix
        """
        unit = [[1 if i == j else 0 for j in range(self.matrix.dimension)] for i in range(self.matrix.dimension)]
        unit[i][j] = const
        transvection = type(matrix)(unit)
        return transvection*matrix

    def find_inverse(self):
        """
        Знаходження оберненої матриці
        :return: SquareMatrix
        """
        # Створюємо копії матриці для того щоб вона залишилася незмінною
        # matrix = deepcopy(self.matrix)
        # # unit: одична матриця, яка стане оберненою для заданої матриці
        # unit = type(self.matrix)([[1 if i == j else 0 for j in range(self.matrix.dimension)] for i in range(self.matrix.dimension)])
        # for i in range(matrix.dimension):
        #     if matrix[i][i] != 1: #Робимо найлівіший коефіцєнт одиницею
        #         if matrix[i] == Vector([0 for k in range(matrix.dimension)]):
        #             # Якщо маємо нульовий рядок, то оберненої матриці не буде
        #             return "Inverse doesn't exist"
        #         const = 1/matrix[i, i]
        #         matrix = self.multiply_row(matrix, i, const)
        #         unit = self.multiply_row(unit, i, const)
        #     for j in range(matrix.dimension): #Робимо нулі під одиницею
        #         if i!=j:
        #             if self.matrix[j, i] != 0:
        #                 const = -matrix[j, i]
        #                 matrix = self.add_to_i_row_j_row_multiplied_const(matrix, j, i, const)
        #                 unit = self.add_to_i_row_j_row_multiplied_const(unit, j, i, const)
        # print(unit)
        # return round(unit,3)

        matrix_list = [[self.matrix[i, j] for j in range(self.matrix.dimension)] for i in range(self.matrix.dimension)]
        np_matrix = np.array(matrix_list, dtype=float)
        try:
            inv_matrix = np.linalg.inv(np_matrix)
        except numpy.linalg.LinAlgError:
            return "The matrix isn't invertible"
        else:
            return round(type(self.matrix)(inv_matrix), 2)


if __name__ == '__main__':
    # matrix = Matrix2D([[2, 7], [3, -1]])
    # vector = Vector2D([11, 5])
    # matrix1 = Matrix3D([[3,0,2], [4, 5 ,1], [6,-5, 0]])
    # s1 = GaussianMethod(matrix)
    # inverse = s1.find_inverse()
    # s2 = GaussianMethod(matrix1)
    # inverse1 = s2.find_inverse()
    # print(round(matrix*inverse,1))
    # print(round(matrix1*inverse1, 1))
    print(len([i for i in range(0,-2)]))


