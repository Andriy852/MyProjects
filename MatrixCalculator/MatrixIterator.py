class MatrixIterator:
    def __init__(self, matrix):
        """
        :param matrix: element of SquareMatrix type
        """
        self.matrix = matrix
        self.row_number = 0
        self.column_number = 0
    def __next__(self):
        try:
            result = self.matrix[self.row_number, self.column_number]
            self.column_number += 1
            return result
        except IndexError:
            if self.row_number < self.matrix.dimension:
                self.row_number += 1 #go to the next row
                self.column_number = 0
                return self.__next__()
            else:
                raise StopIteration
